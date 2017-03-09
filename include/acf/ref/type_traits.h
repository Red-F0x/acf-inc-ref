///
/// type_traits.h
///
///  Created on: 03.02.2017
///      Author: ho11owman
///

#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

#include "acf/ref/bits/type_traits.hpp"

namespace ref
{

template <std::size_t tt_value>
using size_constant = std::integral_constant<std::size_t, tt_value>;

template <typename Type>
struct name_of
{
    static constexpr char value[] { "" };
    using type = decltype(value);
};

template <typename Type>
constexpr char name_of<Type>::value[];

template <typename Type>
constexpr const char* name_of_v { ref::name_of<Type>::value };

template <typename Type>
using name_of_t = typename ref::name_of<Type>::type;

template <typename Type>
struct name_size: public ref::size_constant<((std::experimental::extent_v<std::remove_reference_t<ref::name_of_t<Type>>>) - 1)>
{
};

template <typename Type>
constexpr bool name_size_v = ref::name_size < Type > ::value;

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

#endif /* TYPE_TRAITS_H_ */
