//
// index.h
//
//  Created on: 22.03.2017
//      Author: ho11owman
//

#ifndef INDEX_H_
#define INDEX_H_ 1

#include "ref/bits/type_traits.h"
#include "ref/bits/fwd.h"
#include "ref/bits/preprocessor.h"

namespace ref {

namespace {

template <typename Type, typename = void>
struct has_bean_type_impl : public std::false_type
{
};

template <typename Type>
struct has_bean_type_impl<Type, std::void_t<typename Type::bean_type>> : public std::true_type
{
};

}  // namespace anonym

template <typename Type>
struct has_bean_type : public has_bean_type_impl<Type>
{
};

template <typename Type>
constexpr bool has_bean_type_v = has_bean_type<Type>::value;

namespace {

template <typename Index, bool tt_is_complete = false>
struct is_indexed_impl : public std::false_type
{
};

template <typename Index>
struct is_indexed_impl<Index, true> : public std::bool_constant<(
        ref::has_value<Index>::value &&
        ref::has_value_type<Index>::value &&
        ref::has_bean_type<Index>::value &&
        ref::is_bean<typename Index::bean_type>::value)>
{
};

} // namespace anonym

namespace {

template <typename Type, std::size_t tp_index>
struct index_impl :
                    public ref::size_constant<tp_index>
{
    using bean_type = Type;
};

} // namespace anonym

template <typename Type, std::size_t tp_index>
struct index :
               public ref::index_impl<Type, std::numeric_limits<std::size_t>::max()>
{
};

template <typename Type, std::size_t tp_index>
constexpr std::size_t index_v = ref::index<Type, tp_index>::value;

}  // namespace ref



#endif /* INDEX_H_ */
