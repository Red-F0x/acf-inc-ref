/*
 * type_traits.hpp
 *
 *  Created on: 09.02.2017
 *      Author: ho11owman
 */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include "acf/ref/bits/preprocessor.hpp"

namespace acf {

namespace ref {

template <typename Type>
    struct name;

template <>
    struct name<void>
    {
        static constexpr char value[] { "void" };
        using type = decltype(value);
    };

constexpr char name<void>::value[];

template <>
    struct name<decltype(nullptr)>
    {
        static constexpr char value[] = { "nullptr" };
        using type = decltype(value);
    };

template <>
    struct name<bool>
    {
        static constexpr char value[] = { "bool" };
        using type = decltype(value);
    };

template <>
    struct name<signed char>
    {
        static constexpr char value[] = { "signed char" };
        using type = decltype(value);
    };

template <>
    struct name<unsigned char>
    {
        static constexpr char value[] = { "unsigned char" };
        using type = decltype(value);
    };

template <>
    struct name<char>
    {
        static constexpr char value[] = { "char" };
        using type = decltype(value);
    };

template <>
    struct name<wchar_t>
    {
        static constexpr char value[] = { "wchar_t" };
        using type = decltype(value);
    };

template <>
    struct name<char16_t>
    {
        static constexpr char value[] = { "char16_t" };
        using type = decltype(value);
    };

template <>
    struct name<char32_t>
    {
        static constexpr char value[] = { "char32_t" };
        using type = decltype(value);
    };

template <>
    struct name<short int>
    {
        static constexpr char value[] = { "short int" };
        using type = decltype(value);
    };

template <>
    struct name<unsigned short int>
    {
        static constexpr char value[] = { "unsigned short int" };
        using type = decltype(value);
    };

template <>
    struct name<int>
    {
        static constexpr char value[] = { "int" };
        using type = decltype(value);
    };

template <>
    struct name<unsigned int>
    {
        static constexpr char value[] = { "unsigned int" };
        using type = decltype(value);
    };

template <>
    struct name<long int>
    {
        static constexpr char value[] = { "long int" };
        using type = decltype(value);
    };

template <>
    struct name<unsigned long int>
    {
        static constexpr char value[] = { "unsigned long int" };
        using type = decltype(value);
    };

template <>
    struct name<long long int>
    {
        static constexpr char value[] = { "long long int" };
        using type = decltype(value);
    };

template <>
    struct name<unsigned long long int>
    {
        static constexpr char value[] = { "unsigned long long int" };
        using type = decltype(value);
    };

template <>
    struct name<float>
    {
        static constexpr char value[] = { "float" };
        using type = decltype(value);
    };

template <>
    struct name<double>
    {
        static constexpr char value[] = { "double" };
        using type = decltype(value);
    };

template <>
    struct name<long double>
    {
        static constexpr char value[] = { "long double" };
        using type = decltype(value);
    };

}  // namespace ref

}  // namespace acf

#endif /* TYPE_TRAITS_HPP_ */
