//
// assertion_test.h
//
//  Created on: 13.03.2017
//      Author: ho11owman
//

#ifndef ASSERTION_TEST_H_
#define ASSERTION_TEST_H_ 1

#include <tuple>
#include "ref/bits/type_traits.h"

/// @todo maby exctra assertion test' list???
constexpr bool cstr_eq(const char* t_one, const char* t_two)
{
  return (*t_one && *t_two) ? (*t_one == *t_two && cstr_eq(t_one + 1, t_two + 1)) : (!*t_one && !*t_two);
}

template <template <typename > class Trait, typename Type, bool tt_negate = false>
class assertion_trigger;

template <template <typename > class Trait, typename ... Types, bool tt_negate>
class assertion_trigger<Trait, std::tuple<Types...>, tt_negate>
{
    template <typename Type>
    struct check
    {
        static constexpr bool value = (tt_negate ? !(Trait<Type>::value) : (Trait<Type>::value));
    };

//    template <typename Type, typename TT = Trait<Type>, typename ValueType = typename TT::value_type>
//    constexpr auto check_eq(ValueType&& t_value)
//    {
//        return struct {
//            static constexpr bool value = cstr_eq(TT::value, std::forward<ValueType>(t_value));
//        } ();
//    };

public:
    constexpr void operator()() const
    {
        static_assert(ref::conjunction<check<Types>...>::value, "");
    }

    template <typename... Values>
    constexpr void operator()(Values&&... t_values) const
    {
//        static_assert(ref::conjunction<check_eq<Types>(t_values)...>::value, "");
//        static_assert(ref::conjunction<check<Types>...>::value, "");
    }

//    template <typename Type, typename TT = Trait<Type>>
//    constexpr void operator()(typename TT::value_type&& t_value) const
//    {
//        static_assert(cstr_eq(Type::value, t_value), "");
//    }
};

using supported_types = std::tuple<
void,
decltype(nullptr),
bool,
signed char,
unsigned char,
char,
wchar_t,
char16_t,
char32_t,
short int,
unsigned short int,
int,
unsigned int,
long int,
unsigned long int,
long long int,
unsigned long long int,
float,
double,
long double>;

template <typename NameOf>
constexpr bool check_name(const char* t_cstr)
{
    return cstr_eq(NameOf::value, t_cstr);
}

void is_complete_test();
void has_value_test();
void has_value_type_test();
void is_named_test();
void is_name_of_test();
void is_bean_test();
void bean_size_test();

#endif /* ASSERTION_TEST_H_ */
