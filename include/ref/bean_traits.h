///
/// \file include/acf/ref/bean_traits.h
///
///  Created on: 09.02.2017
///      Author: ho11owman
///

#ifndef BEAN_TRAITS_H_
#define BEAN_TRAITS_H_

#include <functional>
#include <limits>

#include "ref/bits/name_of.h"
#include "ref/bits/index.h"

namespace ref
{

///
/// detect bean type
///
template <typename Type>
struct is_bean :
                 public std::bool_constant<(
                         ref::is_named<Type>::value &&
                         std::is_class<Type>::value &&
                         std::is_default_constructible<Type>::value &&
                         std::is_destructible<Type>::value)>
{
};

template <typename Type>
constexpr bool is_bean_v = ref::is_bean<Type>::value;








namespace {

template <typename Type>
struct bean_size_impl
{
    static_assert(is_bean<Type>::value, "given type is not a bean");

    using type = ref::size_constant<(0)>;
};

}  // namespace anonymus

template <typename Type>
struct bean_size : public bean_size_impl<Type>::type
{
};

template <typename Type>
struct is_bean_empty : public std::bool_constant<(bean_size<Type>::value == 0)>
{
};

template <typename Type>
constexpr bool is_bean_empty_v = ref::is_bean_empty<Type>::value;

//namespace
//{

//template <typename Type, std::size_t tt_index>
//constexpr bool is_indexed_impl_0()
//{
//    /// \todo add constrains
//    return ref::index_v<Type, tt_index> != std::numeric_limits<std::size_t>::max();
//}

//template <typename Type, std::size_t tt_index>
//constexpr bool is_indexed_impl()
//{
//    return is_indexed_impl_0<Type, tt_index>();
//}

//} // anonym

//template <typename Type, std::size_t tt_index = 0>
//struct is_indexed :
//                    public std::bool_constant<is_indexed_impl<Type, tt_index>()>
//{
//};

//template <typename Type, std::size_t tp_index = 0>
//constexpr bool is_indexed_v = ref::is_indexed<Type, tp_index>::value;

template <typename Type, std::size_t tp_index>
constexpr auto size_impl() -> std::enable_if_t<!(ref::is_indexed_v<Type, tp_index>), std::size_t>
{
    return 0;
}

template <typename Type, std::size_t tp_index>
constexpr auto size_impl() -> std::enable_if_t<(ref::is_indexed_v<Type, tp_index>), std::size_t>
{
    return 1 + size_impl<Type, tp_index + 1>();
}

template <typename Type>
struct size :
              public ref::size_constant<size_impl<Type, 0>()>
{
};

template <typename Type>
constexpr std::size_t size_v = ref::size<Type>::value;

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
using class_of_t = typename ref::class_of<Type>::type;

/// \todo in namespace
template <typename Type>
struct extract_args_impl;

template <typename Res, typename Class, typename ... Args>
struct extract_args_impl<Res (Class::*)(Args...) const>
{
    using type = std::tuple<Args...>;
};

template <typename Res, typename Class, typename ... Args>
struct extract_args_impl<Res (Class::*)(Args...)>
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
using extract_args_t = typename ref::extract_args<Type>::type;

template <typename Index, typename Type, Type tt_value>
class execute_asseccor
{
    template <typename Tuple>
    struct forward;

public:
    using index_type = Index;
    using value_type = Type;

    static constexpr value_type value = tt_value;

    using class_type = ref::class_of_t<Type>;
    using args_tuple = ref::extract_args_t<Type>;

private:
    template <typename ... Args>
    struct forward<std::tuple<Args...>>
    {
        using type = decltype((std::declval<class_type>().*value)(std::forward<Args>(std::declval<Args>())...));
    };

public:
    using result_type = typename forward<args_tuple>::type;
    //decltype((std::declval<class_type>().*value)());
};

template <typename Index, typename Type, Type tt_value>
constexpr typename execute_asseccor<Index, Type, tt_value>::value_type execute_asseccor<Index, Type, tt_value>::value;

namespace details
{

template <typename Index, typename Type, Type tt_value>
class read_asseccor_impl :
                           public ref::execute_asseccor<Index, Type, tt_value>
{
    using base_type = ref::execute_asseccor<Index, Type, tt_value>;

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
                            public ref::execute_asseccor<Index, Type, tt_value>
{
    using base_type = ref::execute_asseccor<Index, Type, tt_value>;

public:
    /// \todo add constrains

    using arg_type = std::tuple_element_t<0, typename base_type::args_tuple>;
    using member_type = ref::class_of_t<Type>;
};

} // namespace details

template <typename Index>
struct write_asseccor;
// : public acf::ref::execute_asseccor

template <typename Index, typename Bean>
constexpr auto invoke_read(Bean&& t_bean) -> typename read_asseccor<Index>::result_type;

template <typename Index, typename Bean, typename Type>
constexpr auto invoke_write(Bean&& t_bean, Type&& t_value) -> void;

template <typename Index>
class member_type;

template <typename Bean, std::size_t tt_index>
class member_type<ref::index<Bean, tt_index>> final
{
    using bean_type = Bean;
    static constexpr std::size_t index_v = tt_index;
    using index_type = ref::index<bean_type, index_v>;

    using type = member_type<index_type>;

    using name_of_type = ref::name_of<index_type>;
    using read_asseccor_type = read_asseccor<index_type>;
    using write_asseccor_type = write_asseccor<index_type>;

public:
    constexpr member_type(const type&) = delete;
    constexpr member_type(type&&) = delete;
    constexpr type& operator=(const type&) = delete;
    constexpr type& operator=(type&&) = delete;

    constexpr member_type() = default;
    ~member_type() = default;

    constexpr auto index() -> decltype(index_type::value) const
    {
        return index_type::value;
    }
    constexpr auto name() -> decltype(name_of_type::value) const
    {
        return name_of_type::value;
    }
    constexpr auto value(const bean_type& t_bean) -> typename read_asseccor_type::result_type const
    {
        return ref::invoke_read<index_type>(t_bean);
    }
    constexpr auto value(bean_type& t_bean, typename write_asseccor_type::arg_type t_value) -> void
    {
        ref::invoke_write<index_type>(t_bean, t_value);
    }

};

///
/// \see read_asseccor
///

namespace
{

template <typename Type>
struct assecc_argument_impl;

template <typename ResType, typename Class, typename Arg>
struct assecc_argument_impl<ResType (Class::*)(Arg)>
{
    using type = Arg;
};

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
constexpr auto invoke_impl(Bean&& t_bean, Args&&... t_args)
        -> std::enable_if_t<(std::experimental::is_void_v<typename Asseccor::result_type>), typename Asseccor::result_type>
{
    std::invoke(Asseccor::value, std::forward<Bean>(t_bean), std::forward<Args>(t_args)...);
}

template <typename Asseccor, typename Bean, typename ... Args>
constexpr auto invoke_impl(Bean&& t_bean, Args&&... t_args)
        -> std::enable_if_t<!(std::experimental::is_void_v<typename Asseccor::result_type>), typename Asseccor::result_type>
{
    return std::invoke(Asseccor::value, std::forward<Bean>(t_bean), std::forward<Args>(t_args)...);
}

} // anonym

template <typename Index, typename Bean>
constexpr auto invoke_read(Bean&& t_bean) -> typename read_asseccor<Index>::result_type
//-> decltype(invoke_impl<read_asseccor<Index>, Bean>(std::forward<Bean>(t_bean)))
{
    return invoke_impl<read_asseccor<Index>>(std::forward<Bean>(t_bean));
}

template <typename Index, typename Bean, typename Type>
constexpr auto invoke_write(Bean&& t_bean, Type&& t_value) -> void
{
    invoke_impl<write_asseccor<Index>>(std::forward<Bean>(t_bean), std::forward<Type>(t_value));
}

} // namespace ref

#endif /* BEAN_TRAITS_H_ */
