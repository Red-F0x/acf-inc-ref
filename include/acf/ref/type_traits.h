/*
 * type_traits.h
 *
 *  Created on: 03.02.2017
 *      Author: ho11owman
 */

#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

#include "acf/ref/bits/type_traits.hpp"

namespace acf {

namespace ref {

template <std::size_t tt_value>
    using size_constant = std::integral_constant<std::size_t, tt_value>;

template <typename Type>
    struct name
    {
        static constexpr char value[] { "" };
        using type = decltype(value);
    };

template <typename Type>
    constexpr char name<Type>::value[];

template <typename Type>
    constexpr const char* name_v { acf::ref::name<Type>::value };

template <typename Type>
    using name_t = typename acf::ref::name<Type>::type;

template <typename Type>
    struct name_size : public acf::ref::size_constant<
            std::experimental::extent_v<std::remove_reference_t<acf::ref::name_t<Type>>>- 1>
    {
    };

template <typename Type>
    constexpr bool name_size_v = acf::ref::name_size<Type>::value;

template <typename Type>
    struct is_name_empty : public std::bool_constant<(acf::ref::name_size_v<Type> == 0)>
    {
    };

template <typename Type>
    constexpr bool is_name_empty_v = acf::ref::is_name_empty<Type>::value;

template <typename Type>
    struct is_supported : public std::bool_constant<!acf::ref::is_name_empty_v<Type>>
    {
    };

template <typename Type>
    constexpr bool is_supported_v = acf::ref::is_supported<Type>::value;

}  // namespace ref

}  // namespace acf

#endif /* TYPE_TRAITS_H_ */
