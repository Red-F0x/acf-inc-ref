//
// assertion_test.h
//
//  Created on: 13.03.2017
//      Author: ho11owman
//

#ifndef ASSERTION_TEST_H_
#define ASSERTION_TEST_H_ 1

#include <tuple>

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

template <template <typename > class Trait, typename Type, bool tt_negate = false>
class assertion_trigger;

template <template <typename > class Trait, typename ... Types, bool tt_negate>
class assertion_trigger<Trait, std::tuple<Types...>, tt_negate>
{
    template <typename Type>
    static constexpr bool check()
    {
        return (tt_negate ? !(Trait<Type>::value) : (Trait<Type>::value));
    }

    template <typename Type>
    void impl()
    {
        static_assert(check<Type>(), "");
    }

    void eat();

public:
    void operator()()
    {
        (impl<Types>(), ...);
    }
};

namespace {

template <typename Type>
constexpr bool is_eq(Type&& t_value1, Type&& t_value2)
{
    return (t_value1 == t_value2);
}

template <std::size_t tt_index, typename Char, std::size_t tt_size, typename Type = const Char&[tt_size]>
constexpr bool cstr_eq_impl(Type t_cstr_1, Type t_cstr_2)
{
    return is_eq(t_cstr_1[0], t_cstr_2[0]);
}

}  // namespace anonym

template <typename Type>
constexpr bool cstr_eq(Type&& t_cstr1, Type&& t_cstr2)
{
    return cstr_eq_impl<0>(std::forward<Type>(t_cstr1), std::forward<Type>(t_cstr2));
}

template <typename NameOf, typename Type>
constexpr bool check_name(Type&& t_cstr)
{
    return cstr_eq(NameOf::value, std::forward<Type>(t_cstr));
}

void is_complete_test();
void has_value_test();
void has_value_type_test();
void is_named_test();
void is_name_of_test();
void is_bean_test();
void bean_size_test();

#endif /* ASSERTION_TEST_H_ */
