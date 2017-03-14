//
// name_of_impl.h
//
//  Created on: 13.03.2017
//      Author: ho11owman
//

#ifndef NAME_OF_IMPL_H_
#define NAME_OF_IMPL_H_ 1

#include "ref/bits/fwd.h"
#include "ref/bits/preprocessor.h"

namespace ref {

template <>
struct name_of<void>
{
    static constexpr char value[] { "void" };
    using type = decltype(value);
};

constexpr char name_of<void>::value[];

template <>
struct name_of<decltype(nullptr)>
{
    static constexpr char value[] = { "nullptr" };
    using type = decltype(value);
};

constexpr char name_of<decltype(nullptr)>::value[];

template <>
struct name_of<bool>
{
    static constexpr char value[] = { "bool" };
    using type = decltype(value);
};

constexpr char name_of<bool>::value[];

template <>
struct name_of<signed char>
{
    static constexpr char value[] = { "signed char" };
    using type = decltype(value);
};

constexpr char name_of<signed char>::value[];

template <>
struct name_of<unsigned char>
{
    static constexpr char value[] = { "unsigned char" };
    using type = decltype(value);
};

constexpr char name_of<unsigned char>::value[];

template <>
struct name_of<char>
{
    static constexpr char value[] = { "char" };
    using type = decltype(value);
};

constexpr char name_of<char>::value[];

template <>
struct name_of<wchar_t>
{
    static constexpr char value[] = { "wchar_t" };
    using type = decltype(value);
};

constexpr char name_of<wchar_t>::value[];

template <>
struct name_of<char16_t>
{
    static constexpr char value[] = { "char16_t" };
    using type = decltype(value);
};

constexpr char name_of<char16_t>::value[];

template <>
struct name_of<char32_t>
{
    static constexpr char value[] = { "char32_t" };
    using type = decltype(value);
};

constexpr char name_of<char32_t>::value[];

template <>
struct name_of<short int>
{
    static constexpr char value[] = { "short int" };
    using type = decltype(value);
};

constexpr char name_of<short int>::value[];

template <>
struct name_of<unsigned short int>
{
    static constexpr char value[] = { "unsigned short int" };
    using type = decltype(value);
};

constexpr char name_of<unsigned short int>::value[];

template <>
struct name_of<int>
{
    static constexpr char value[] = { "int" };
    using type = decltype(value);
};

constexpr char name_of<int>::value[];

template <>
struct name_of<unsigned int>
{
    static constexpr char value[] = { "unsigned int" };
    using type = decltype(value);
};

constexpr char name_of<unsigned int>::value[];

template <>
struct name_of<long int>
{
    static constexpr char value[] = { "long int" };
    using type = decltype(value);
};

constexpr char name_of<long int>::value[];

template <>
struct name_of<unsigned long int>
{
    static constexpr char value[] = { "unsigned long int" };
    using type = decltype(value);
};

constexpr char name_of<unsigned long int>::value[];

template <>
struct name_of<long long int>
{
    static constexpr char value[] = { "long long int" };
    using type = decltype(value);
};

constexpr char name_of<long long int>::value[];

template <>
struct name_of<unsigned long long int>
{
    static constexpr char value[] = { "unsigned long long int" };
    using type = decltype(value);
};

constexpr char name_of<unsigned long long int>::value[];

template <>
struct name_of<float>
{
    static constexpr char value[] = { "float" };
    using type = decltype(value);
};

constexpr char name_of<float>::value[];

template <>
struct name_of<double>
{
    static constexpr char value[] = { "double" };
    using type = decltype(value);
};

constexpr char name_of<double>::value[];

template <>
struct name_of<long double>
{
    static constexpr char value[] = { "long double" };
    using type = decltype(value);
};

constexpr char name_of<long double>::value[];

}

#endif /* NAME_OF_IMPL_H_ */
