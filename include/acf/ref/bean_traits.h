/*
 * bean_traits.h
 *
 *  Created on: 09.02.2017
 *      Author: ho11owman
 */

#ifndef BEAN_TRAITS_H_
#define BEAN_TRAITS_H_

#include "acf/ref/type_traits.h"

namespace acf {

namespace ref {

template <typename Type>
    struct is_bean;

template <typename Type, std::size_t tp_index>
    struct index_impl : public acf::ref::size_constant<tp_index>
    {
    };

template <typename Type, std::size_t tp_index>
    struct index : public acf::ref::index_impl<Type, std::numeric_limits<std::size_t>::max ()>
    {
    };

template <typename Type, std::size_t tp_index>
    constexpr std::size_t index_v = acf::ref::index<Type, tp_index>::value;

namespace {

template <typename Type, std::size_t tt_index>
constexpr bool is_indexed_impl_0()
{
    return acf::ref::index_v<Type, tt_index> != std::numeric_limits<std::size_t>::max ();
//    return (acf::ref::index_v<Type, tt_index> != std::numeric_limits<std::size_t>::max ()) : true : false;
}

template <typename Type, std::size_t tt_index>
constexpr bool is_indexed_impl()
{
    return is_indexed_impl_0<Type, tt_index>();
}

//template <typename Type, std::size_t tt_impl_index>
//constexpr bool is_indexed_impl(std::size_t tt_index)
//{
//    return acf::ref::index_v<Type, tt_index> != std::numeric_limits<std::size_t>::max () && is_indexed_impl<Type, tt_impl_index + 1>();
////    return (acf::ref::index_v<Type, tt_index> != std::numeric_limits<std::size_t>::max ()) : true : false;
//}

}

template <typename Type, std::size_t tt_index = 0>
    struct is_indexed : public std::bool_constant<is_indexed_impl<Type, tt_index>()>
//            (acf::ref::index_v<Type, tp_index> != std::numeric_limits<std::size_t>::max ())>
    {
    };

template <typename Type, std::size_t tp_index = 0>
    constexpr bool is_indexed_v = acf::ref::is_indexed<Type, tp_index>::value;

template <typename Type, std::size_t tp_index>
    constexpr auto
    size_impl () -> std::enable_if_t<!(acf::ref::is_indexed_v<Type, tp_index>), std::size_t>
    {
        return 0;
    }

template <typename Type, std::size_t tp_index>
    constexpr auto
    size_impl () -> std::enable_if_t<(acf::ref::is_indexed_v<Type, tp_index>), std::size_t>
    {
        return 1 + size_impl<Type, tp_index + 1> ();
    }

template <typename Type>
    struct size : public acf::ref::size_constant<size_impl<Type, 0> ()>
    {
    };

template <typename Type>
    constexpr std::size_t size_v = acf::ref::size<Type>::value;

template <typename Type>
    struct is_bean : public std::bool_constant<(acf::ref::is_supported_v < Type > &&(acf::ref::size_v<Type> > 0))>
    {
    };

template <typename Type>
    constexpr bool is_bean_v = acf::ref::is_bean<Type>::value;

}  // namespace ref

}  // namespace acf

#endif /* BEAN_TRAITS_H_ */
