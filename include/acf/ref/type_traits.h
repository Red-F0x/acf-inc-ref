///
/// type_traits.h
///
///  Created on: 03.02.2017
///      Author: ho11owman
///

#ifndef TYPE_TRAITS_H__
#define TYPE_TRAITS_H__

#include <ref/bits/name_of.h>

#include "acf/ref/bits/preprocessor.hpp"

namespace ref
{

//template <typename Type>
//struct name_of
//{
//    static constexpr char value[] { "" };
//    using type = decltype(value);
//};
//
//template <typename Type>
//constexpr char name_of<Type>::value[];
//
//template <typename Type>
//constexpr const char* name_of_v { ref::name_of<Type>::value };
//
//template <typename Type>
//using name_of_t = typename ref::name_of<Type>::type;

template <typename Type>
struct is_name_empty :
                       public std::bool_constant<(ref::name_size_v<Type> == 0)>
{
};

template <typename Type>
constexpr bool is_name_empty_v = ref::is_name_empty<Type>::value;

template <typename Type>
struct is_supported :
                      public std::bool_constant<!ref::is_name_empty_v<Type>>
{
};

template <typename Type>
constexpr bool is_supported_v = ref::is_supported<Type>::value;

}  // namespace ref

#endif /* TYPE_TRAITS_H__ */
