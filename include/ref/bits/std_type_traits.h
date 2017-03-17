//
// std_type_traits.h
//
//  Created on: 21.02.2017
//      Author: ho11owman
//

#ifndef STD_TYPE_TRAITS_H_
#define STD_TYPE_TRAITS_H_ 1

#if __has_include(<experimental/type_traits>)
#
#  include <experimental/type_traits>
#
#elif __has_include(<type_traits>)
#
#  include <type_traits>
#
#endif

namespace ref {

///
/// The Type is depended from Dependency if:
/// - the Type has member from type Dependency* (pointer)
///
/// first step construct Dependency
/// second step construct Type
///
template <typename Type, typename... Dependency>
struct dependet_construct;

}  // namespace ref

#endif /* STD_TYPE_TRAITS_H_ */
