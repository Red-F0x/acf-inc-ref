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

constexpr bool cstr_eq(const char* t_one, const char* t_two)
{
  return (*t_one && *t_two) ? (*t_one == *t_two && cstr_eq(t_one + 1, t_two + 1)) : (!*t_one && !*t_two);
}

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
