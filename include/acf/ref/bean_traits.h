///
/// \file include/acf/ref/bean_traits.h
///
///  Created on: 09.02.2017
///      Author: ho11owman
///

#ifndef BEAN_TRAITS_H_
#define BEAN_TRAITS_H_

#include <functional>

#include "acf/ref/type_traits.h"

namespace acf
{

namespace ref
{

template <typename Type>
struct is_bean;

template <typename Type, std::size_t tp_index>
struct index_impl :
                    public acf::ref::size_constant<tp_index>
{
};

template <typename Type, std::size_t tp_index>
struct index :
               public acf::ref::index_impl<Type, std::numeric_limits<std::size_t>::max()>
{
};

template <typename Type, std::size_t tp_index>
constexpr std::size_t index_v = acf::ref::index<Type, tp_index>::value;

namespace
{

template <typename Type, std::size_t tt_index>
constexpr bool is_indexed_impl_0()
{
    return acf::ref::index_v<Type, tt_index> != std::numeric_limits<std::size_t>::max();
}

template <typename Type, std::size_t tt_index>
constexpr bool is_indexed_impl()
{
    return is_indexed_impl_0<Type, tt_index>();
}

} // anonym

template <typename Type, std::size_t tt_index = 0>
struct is_indexed :
                    public std::bool_constant<is_indexed_impl<Type, tt_index>()>
{
};

template <typename Type, std::size_t tp_index = 0>
constexpr bool is_indexed_v = acf::ref::is_indexed<Type, tp_index>::value;

template <typename Type, std::size_t tp_index>
constexpr auto size_impl() -> std::enable_if_t<!(acf::ref::is_indexed_v<Type, tp_index>), std::size_t>
{
    return 0;
}

template <typename Type, std::size_t tp_index>
constexpr auto size_impl() -> std::enable_if_t<(acf::ref::is_indexed_v<Type, tp_index>), std::size_t>
{
    return 1 + size_impl<Type, tp_index + 1>();
}

template <typename Type>
struct size :
              public acf::ref::size_constant<size_impl<Type, 0>()>
{
};

template <typename Type>
constexpr std::size_t size_v = acf::ref::size<Type>::value;

template <typename Type>
struct is_bean :
                 public std::bool_constant<(acf::ref::is_supported_v < Type > &&(acf::ref::size_v<Type> > 0))>
{
};

template <typename Type>
constexpr bool is_bean_v = acf::ref::is_bean<Type>::value;

///
///
/// \todo in namespace
template <typename Type>
struct class_of_impl;

template <typename Res, typename Class>
struct class_of_impl<Res Class::*>
{
    using type = Class;
};

template <typename Type>
struct class_of :
                  public class_of_impl<Type>
{
};

template <typename Type>
using class_of_t = typename acf::ref::class_of<Type>::type;

/// \todo in namespace
template <typename Type>
struct extract_args_impl;

template <typename Res, typename Class, typename ... Args>
struct extract_args_impl<Res (Class::*)(Args&&...) const>
{
    using type = std::tuple<Args...>;
};

/// \todo add constrains
template <typename Type>
struct extract_args :
                      public extract_args_impl<Type>
{
};

template <typename Type>
using extract_args_t = typename acf::ref::extract_args<Type>::type;

template <typename Index, typename Type, Type tt_value>
struct execute_asseccor
{
    using index_type = Index;
    using value_type = Type;

    static constexpr value_type value = tt_value;

    using class_type = acf::ref::class_of_t<Type>;
    using result_type = decltype((std::declval<class_type>().*value)());
    using args_tuple = acf::ref::extract_args_t<Type>;
};

template <typename Index, typename Type, Type tt_value>
constexpr typename execute_asseccor<Index, Type, tt_value>::value_type execute_asseccor<Index, Type, tt_value>::value;

namespace details
{

template <typename Index, typename Type, Type tt_value>
class read_asseccor_impl :
                           public acf::ref::execute_asseccor<Index, Type, tt_value>
{
    using base_type = acf::ref::execute_asseccor<Index, Type, tt_value>;

public:
    static_assert(!std::experimental::is_void_v<typename base_type::result_type>);

    using member_type = typename base_type::result_type;
    //acf::ref::class_of_t<Type>;
};

} // anonym

template <typename Index>
struct read_asseccor;
// : public acf::ref::execute_asseccor

namespace details
{

template <typename Index, typename Type, Type tt_value>
class write_asseccor_impl :
                            public acf::ref::execute_asseccor<Index, Type, tt_value>
{
    using base_type = acf::ref::execute_asseccor<Index, Type, tt_value>;

public:
    /// \todo add constrains

    using member_type = acf::ref::class_of_t<Type>;
};

} // anonym

template <typename Index>
struct write_asseccor;
// : public acf::ref::execute_asseccor

///
/// \see read_asseccor
///
//template <typename Asseccor>
//struct assecc_result : public assecc_result_impl<Asseccor>
//{
//};
//
//template <typename Asseccor>
//using assecc_result_t = typename acf::ref::assecc_result<Asseccor>::type;

namespace
{

template <typename Type>
struct assecc_argument_impl;

template <typename ResType, typename Class, typename Arg>
struct assecc_argument_impl<ResType (Class::*)(Arg)>
{
    using type = Arg;
};

//template <typename ResType, typename Class, typename... Args>
//struct assecc_argument_impl<ResType (Class::*)(Args...)>
//{
//    using type = std::tuple<Args...>;
//};

}// anonym

template <typename Asseccor>
struct assecc_argument :
                         public assecc_argument_impl<typename Asseccor::value_type>
{
};

template <typename Asseccor>
using assecc_argument_t = typename assecc_argument<Asseccor>::type;

///
///
///
namespace
{

template <typename Asseccor, typename Bean, typename ... Args>
constexpr auto invoke_impl(Bean&& t_bean, Args&&... t_args) // -> void
        -> std::enable_if_t<(std::experimental::is_void_v<typename Asseccor::result_type>), typename Asseccor::result_type>
{
    std::invoke(std::forward<typename Asseccor::value_type>(Asseccor::value), std::forward<Args>(t_args)...);
}

template <typename Asseccor, typename Bean, //= typename Asseccor::result_type,
        typename ... Args>
constexpr auto invoke_impl(Bean&& t_bean, Args&&... t_args) // -> Res
        -> std::enable_if_t<!(std::experimental::is_void_v<typename Asseccor::result_type>), typename Asseccor::result_type>
{
    return std::invoke(
    /*std::forward<typename Asseccor::value_type>(*/Asseccor::value/*)*/, std::forward<Bean>(t_bean),
            std::forward<Args>(t_args)...);
}

} // anonym

template <typename Index, typename Bean>
constexpr auto invoke_read(Bean&& t_bean) -> typename read_asseccor<Index>::result_type
//-> decltype(invoke_impl<read_asseccor<Index>, Bean>(std::forward<Bean>(t_bean)))
{
    return invoke_impl<read_asseccor<Index>>(std::forward<Bean>(t_bean));
}

//template <typename Index, typename Bean, typename Type = >
//constexpr auto invoke_write(Bean&& t_bean, Type&& t_arg) -> void
//{
//    invoke_impl<write_asseccor<Index>>(std::forward<Bean>(t_bean), std::forward<Arg>(t_arg));
//}

}
// namespace ref

}// namespace acf

#endif /* BEAN_TRAITS_H_ */
