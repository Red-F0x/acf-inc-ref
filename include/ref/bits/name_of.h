//
// name_of_traits.h
//
//  Created on: 12.03.2017
//      Author: ho11owman
//

#ifndef NAME_OF_H_
#define NAME_OF_H_ 1

#include "ref/bits/fwd.h"
#include "ref/bits/type_traits.h"

namespace ref {

namespace {

template <typename Type>
struct is_named_impl : public std::bool_constant<ref::is_complete_v<Type>>
{
};

}  // namespace anonym

template <typename Type>
struct is_named : public is_named_impl<ref::name_of<Type>>
{
};

template <typename Type>
constexpr bool is_named_v = is_named<Type>::value;

namespace {

template <typename Type, bool tt_named = false>
struct name_size_impl : public ref::size_constant<0>
{
};

template <typename Type>
struct name_size_impl<Type, true> :
    public ref::size_constant<((std::extent<std::remove_reference_t<typename Type::type>>::value) - 1)>
{
};

}  // namespace anonym

template <typename Type>
struct name_size: public name_size_impl<name_of<Type>, is_named_v<Type>>
//ref::size_constant<((std::experimental::extent_v<std::remove_reference_t<ref::name_of_t<Type>>>) - 1)>
{
};

template <typename Type>
constexpr bool name_size_v = ref::name_size < Type > ::value;

///////////////
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



#endif /* NAME_OF_H_ */
