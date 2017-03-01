///
/// \file include/acf/ref/bean_traits.h
///
///  Created on: 09.02.2017
///      Author: ho11owman
///

#ifndef BEAN_TRAITS_H_
#define BEAN_TRAITS_H_

#include "acf/ref/type_traits.h"

namespace acf
{

namespace ref
{

template <typename Type>
struct is_bean;

template <typename Type, std::size_t tp_index>
struct index_impl: public acf::ref::size_constant<tp_index>
{
};

template <typename Type, std::size_t tp_index>
struct index: public acf::ref::index_impl<Type,
        std::numeric_limits<std::size_t>::max()>
{
};

template <typename Type, std::size_t tp_index>
constexpr std::size_t index_v = acf::ref::index<Type, tp_index>::value;

namespace
{

template <typename Type, std::size_t tt_index>
constexpr bool is_indexed_impl_0()
{
    return acf::ref::index_v<Type, tt_index>
            != std::numeric_limits<std::size_t>::max();
}

template <typename Type, std::size_t tt_index>
constexpr bool is_indexed_impl()
{
    return is_indexed_impl_0<Type, tt_index>();
}

} // anonym

template <typename Type, std::size_t tt_index = 0>
struct is_indexed: public std::bool_constant<is_indexed_impl<Type, tt_index>()>
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
struct size: public acf::ref::size_constant<size_impl<Type, 0>()>
{
};

template <typename Type>
constexpr std::size_t size_v = acf::ref::size<Type>::value;

template <typename Type>
struct is_bean: public std::bool_constant<
        (acf::ref::is_supported_v<Type> &&(acf::ref::size_v<Type> > 0))>
{
};

template <typename Type>
constexpr bool is_bean_v = acf::ref::is_bean<Type>::value;

///
///
///
namespace
{

template <typename Index, typename Type, Type tt_value>
struct read_asseccor_impl
{
    using index_type = Index;
    using value_type = Type;

    static constexpr value_type value = tt_value;
};

} // anonym

template <typename Index>
struct read_asseccor;

namespace
{

template <typename Index, typename Type, Type tt_value>
struct write_asseccor_impl
{
    using index_type = Index;
    using value_type = Type;

    static constexpr value_type value = tt_value;
};

} // anonym

template <typename Index>
struct write_asseccor;

namespace
{

template <typename Type>
struct assecc_result_impl;

template <typename ResType, typename Class>
struct assecc_result_impl<ResType Class::*>
{
    using type = ResType;
};

} // anonym

template <typename Asseccor>
struct assecc_result : public assecc_result_impl<typename Asseccor::value_type>
{
};

template <typename Asseccor>
using assecc_result_t = typename assecc_result<Asseccor>::type;

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

} // anonym

template <typename Asseccor>
struct assecc_argument : public assecc_argument_impl<typename Asseccor::value_type>
{
};

template <typename Asseccor>
using assecc_argument_t = typename assecc_argument<Asseccor>::type;

///
///
///
namespace
{

template <typename Asseccor, typename... Args>
constexpr auto invoke_impl(Args&&... t_args)
    -> std::enable_if_t<(std::is_void_v<assecc_result_t<Asseccor>>), assecc_result_t<Asseccor>>
{
    std::invoke(std::forward<typename Asseccor::value_type>(Asseccor::value), std::forward<Args>(t_args)...);
}

template <typename Asseccor, typename... Args>
constexpr auto invoke_impl(Args&&... t_args)
    -> std::enable_if_t<!(std::is_void_v<assecc_result_t<Asseccor>>), assecc_result_t<Asseccor>>
{
    return std::invoke(std::forward<typename Asseccor::value_type>(Asseccor::value), std::forward<Args>(t_args)...);
}

} // anonym

template <typename Index, typename Bean>
constexpr auto invoke_read(Bean&& t_bean)
    -> decltype(invoke_impl<read_asseccor<Index>>(std::forward<Bean>(t_bean)))
{
    return invoke_impl<read_asseccor<Index>>(std::forward<Bean>(t_bean));
}

template <typename Index, typename Bean, typename Arg = assecc_argument_t<write_asseccor<Index>>>
constexpr void invoke_write(Bean&& t_bean, Arg&& t_arg)
{
    invoke_impl<write_asseccor<Index>>(std::forward<Bean>(t_bean), std::forward<Arg>(t_arg));
}

} // namespace ref

}  // namespace acf

#endif /* BEAN_TRAITS_H_ */
