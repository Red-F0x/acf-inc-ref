//
// type_traits.h
//
//  Created on: 12.03.2017
//      Author: ho11owman
//

#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_ 1

#include "ref/bits/std_type_traits.h"

namespace ref {

template <typename Type>
struct type_t
{
    using type = Type;
};

/// http://stackoverflow.com/questions/13842468/comma-in-c-c-macro
template <typename Type, typename Ignore = void, typename = Ignore(Type)>
struct argument_type : public ref::type_t <Type>
{
};

template <typename Void>
struct argument_type<Void()> : public ref::type_t<void>
{
};

/// help trait
template <std::size_t tt_value>
using size_constant = std::integral_constant<std::size_t, tt_value>;

namespace {

///
/// detect compete type (impl)
///
template <typename Type, bool tt_value>
class is_complete_impl
{
    template <typename Target, typename = decltype(std::declval<Target>().~Target())>
    static std::true_type test(int);

    template <typename >
    static std::false_type test(...);
public:
    using type = decltype(test<Type>(0));
};

template <typename Type>
class is_complete_impl<Type, true>
{
public:
    using type = std::true_type;
};

} // namespace anonym

///
/// detect compete type
///
template <typename Type>
struct is_complete : public is_complete_impl<Type, std::is_fundamental<Type>::value>::type
{
};

template <typename Type>
constexpr bool is_complete_v = is_complete<Type>::value;

///
/// detect symbot value in type (impl)
///
namespace {

/*
template <typename Type>
class has_value_impl
{
    template <typename Target, typename = decltype(Target::value)>
    static std::true_type test(int);

    template <typename >
    static std::false_type test(...);
public:
    using type = decltype(test<Type>(0));
};*/

template <typename Type, typename = void>
struct has_value_impl : public std::false_type
{
};

template <typename Type>
struct has_value_impl<Type, std::void_t<decltype(&Type::value)>> : public std::true_type
{
};

}  // namespace anonym

///
/// detect symbot value in type
///
template <typename Type>
struct has_value :public has_value_impl<Type>//::type
{
};

template <typename Type>
constexpr bool has_value_v = has_value<Type>::value;

namespace {

template <typename Type, typename = void>
struct has_value_type_impl : public std::false_type
{
};

template <typename Type>
struct has_value_type_impl<Type, std::void_t<typename Type::value_type>> : public std::true_type
{
};

}  // namespace anonym

template <typename Type>
struct has_value_type : public has_value_type_impl<Type>
{
};

template <typename Type>
constexpr bool has_value_type_v = has_value_type<Type>::value;

}  // namespace ref

#endif /* TYPE_TRAITS_H_ */
