/*
 * main.cpp
 *
 *  Created on: 03.02.2017
 *      Author: ho11owman
 */
#include <iostream>
#include <iomanip>
#include <experimental/string_view>
#include <string>
#include <sstream>
#include <cassert>

#include "assertion_test.h"
#include "ref/bean_traits.h"

//#define ACF_REF_TO_STRING(...) #__VA_ARGS__
//#define ACF_REF_EXPAND(...) __VA_ARGS__

#define ACF_REF_ASSERTION_TEST_SIZE_EQ_0(Type) \
        size_eq_0<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_SIZE_GT_0(Type) \
        size_gt_0<Type>(#Type)

#define ACF_REF_ASSERTION_TEST_STR_EQ(Type, TypeName) \
        str_eq<Type>(#Type, #TypeName);

#define ACF_REF_ASSERTION_TEST_STR_NEQ(Type) \
        str_neq<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(Type) \
        name_size_gt_0<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_NAME_SIZE_EQ_0(Type) \
        name_size_eq_0<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(Type) \
        name_not_empty<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_NAME_EMPTY(Type) \
        name_empty<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_SUPPORTED(Type) \
        supported<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_NOT_SUPPORTED(Type) \
        not_supported<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_NOT_BEAN(Type) \
        not_bean<Type>(#Type);

#define ACF_REF_ASSERTION_TEST_BEAN(Type) \
        bean<Type>(#Type);

template <typename Stream, typename Char = typename Stream::char_type, typename StreamSize = typename Stream::streamsize>
constexpr Stream internal_manip(Stream&& t_stream, Char&& t_fill, StreamSize t_width)
{
    t_stream << std::internal;
    t_stream.fill(t_fill);
    t_stream.width(t_width);

    return t_stream;
}

template <typename Stream, typename Char = typename Stream::char_type, typename StreamSize = typename Stream::streamsize>
constexpr Stream left_manip(Stream&& t_stream, Char&& t_fill, StreamSize t_width)
{
    t_stream << std::left;
    std::cout.fill(t_fill);
    std::cout.width(t_width);

    return t_stream;
}

template <typename Stream, typename Char = typename Stream::char_type, typename StreamSize = typename Stream::streamsize>
constexpr Stream right_manip(Stream&& t_stream, Char&& t_fill, StreamSize t_width)
{
    t_stream << std::right;
    std::cout.fill(t_fill);
    std::cout.width(t_width);

    return t_stream;
}

template <typename Stream, typename Type>
constexpr void write_to_stream(Stream&& t_stream, Type&& t_value)
{
    t_stream << t_value;
}

template <typename Stream, typename ... Types>
constexpr void log(Stream&& t_stream, Types&&... t_value)
{
    std::stringstream t_ss { };
    //((t_ss << t_value), ...);
    (write_to_stream(std::forward<Stream>(t_ss), std::forward<Types>(t_value)), ...);
    t_stream << t_ss.str();
}

template <typename Type>
constexpr void size_eq_0(std::experimental::string_view t_type_name)
{
    static_assert((ref::size_v<Type> == 0));

    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::size_v<", t_type_name, "> == 0)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void size_gt_0(std::experimental::string_view t_type_name)
{
    static_assert((ref::size_v<Type> > 0));

    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::size_v<", t_type_name, "> > 0)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type, typename Target>
constexpr void str_eq(std::experimental::string_view t_type_name, Target&& t_target)
{
//    static_assert((std::is_same<ref::name_of_t<Type>, std::remove_reference_t<decltype(t_target)>>::value));

    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::name_t<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void str_neq(std::experimental::string_view t_type_name)
{
//    static_assert((std::is_same<ref::name_of_t<Type>, std::remove_reference_t<decltype("")>>::value));

    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::name_t<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void name_size_gt_0(std::experimental::string_view t_type_name)
{
//    static_assert((ref::name_size_v<Type> > 0));

    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::name_size_v<", t_type_name, "> > 0)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void name_size_eq_0(std::experimental::string_view t_type_name)
{
    static_assert((ref::name_size_v<Type> == 0));

    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::name_size_v<", t_type_name, "> == 0)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void name_not_empty(std::experimental::string_view t_type_name)
{
//    static_assert(!(ref::is_name_empty_v<Type>));

    log(left_manip(std::cout, '-', 50), "- test \'", "!(acf::ref::name_size_v<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void name_empty(std::experimental::string_view t_type_name)
{
    static_assert((ref::is_name_empty_v<Type>));

    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::name_size_v<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void supported(std::experimental::string_view t_type_name)
{
//    static_assert((ref::is_supported_v<Type>));
    log(left_manip(std::cout, '-', 50), "- test \'", "(acf::ref::is_supported_v<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void not_supported(std::experimental::string_view t_type_name)
{
    static_assert(!(ref::is_supported_v<Type>));
    log(left_manip(std::cout, '-', 50), "- test \'", "!(acf::ref::is_supported_v<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void not_bean(std::experimental::string_view t_type_name)
{
//    static_assert(!(ref::is_bean_v<Type>));
    log(left_manip(std::cout, '-', 50), "- test \'", "!(acf::ref::is_bean_v<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

template <typename Type>
constexpr void bean(std::experimental::string_view t_type_name)
{
//    static_assert((ref::is_bean_v<Type>));
    log(left_manip(std::cout, '-', 50), "- test \'", "!(acf::ref::is_bean_v<", t_type_name, ">)");
    log(right_manip(std::cout, '-', 10), " done", '\n');
}

struct some_type
{
};

template <typename Stream, typename Type>
constexpr void deco_on_type(Stream&& t_stream, Type&& t_value)
{
    t_stream << t_value;
}

template <typename Stream>
constexpr void deco_on_type(Stream&& t_stream, bool t_value)
{
    t_stream << std::boolalpha << t_value << std::noboolalpha;
}

template <typename Type>
constexpr auto decorate(Type&& t_value)
{
    std::stringstream l_ss;

    deco_on_type(l_ss, t_value); //l_ss << t_value;

    return l_ss.str();
}

template <std::size_t tt_index, typename Bean>
constexpr void to_string_member(Bean&& t_bean)
{
    using id = ref::index<Bean, tt_index>;

    ref::member_type<id> l_mw { };

    std::cout << '[' << l_mw.index() << ']' << '(' << l_mw.name() << ')' << '{' << decorate(l_mw.value(t_bean)) << '}'
            << '\n';
}

template <typename Bean, std::size_t ... tt_indexes>
constexpr void to_string_impl(Bean&& t_bean, std::index_sequence<tt_indexes...>)
{
(to_string_member<tt_indexes>(std::forward<Bean>(t_bean)), ...);
}

template <typename Bean>
constexpr void to_string(Bean&& t_bean)
{
//std::cout << ref::name_of_v<Bean> << '[' << ref::size_v<Bean> << ']' << '\n';
std::cout << '{' << '\n';
//to_string_impl(std::forward<Bean>(t_bean), std::make_index_sequence<ref::size_v<Bean>> { });
std::cout << '}' << '\n';
}

int main(int t_argc, char* t_argv[])
{
is_complete_test();
has_value_test();
has_value_type_test();
is_named_test();
is_bean_test();

std::cout << "run test from \'" << t_argv[0] << "\' argc \'" << t_argc << '\'' << '\n';

std::cout << "assertion test" << '\n';

ACF_REF_ASSERTION_TEST_SIZE_EQ_0(void);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(decltype(nullptr));
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(bool);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(signed char);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(unsigned char);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(char);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(wchar_t);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(char16_t);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(char32_t);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(int);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(signed);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(unsigned);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(short);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(long);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(long long);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(float);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(double);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(long double);
ACF_REF_ASSERTION_TEST_SIZE_EQ_0(some_type);

//ACF_REF_ASSERTION_TEST_SIZE_GT_0(BasicBaseClass);

std::cout << "- test \'ref::size<?>\' - OK" << '\n';

ACF_REF_ASSERTION_TEST_STR_EQ(void, void);
ACF_REF_ASSERTION_TEST_STR_EQ(decltype(nullptr), nullptr);
ACF_REF_ASSERTION_TEST_STR_EQ(bool, bool);
ACF_REF_ASSERTION_TEST_STR_EQ(signed char, signed char);
ACF_REF_ASSERTION_TEST_STR_EQ(unsigned char, unsigned char);
ACF_REF_ASSERTION_TEST_STR_EQ(char, char);
ACF_REF_ASSERTION_TEST_STR_EQ(wchar_t, wchar_t);
ACF_REF_ASSERTION_TEST_STR_EQ(char16_t, char16_t);
ACF_REF_ASSERTION_TEST_STR_EQ(char32_t, char32_t);
ACF_REF_ASSERTION_TEST_STR_EQ(int, int);
ACF_REF_ASSERTION_TEST_STR_EQ(unsigned int, unsigned int);
ACF_REF_ASSERTION_TEST_STR_EQ(long int, long int);
ACF_REF_ASSERTION_TEST_STR_EQ(unsigned long int, unsigned long int);
ACF_REF_ASSERTION_TEST_STR_EQ(long long int, long long int);
ACF_REF_ASSERTION_TEST_STR_EQ(unsigned long long int, unsigned long long int);
ACF_REF_ASSERTION_TEST_STR_EQ(float, float);
ACF_REF_ASSERTION_TEST_STR_EQ(double, double);
ACF_REF_ASSERTION_TEST_STR_EQ(long double, long double);
ACF_REF_ASSERTION_TEST_STR_NEQ(some_type);

//ACF_REF_ASSERTION_TEST_STR_EQ(BasicBaseClass, BasicBaseClass);

std::cout << "- test \'sdk::name<?>\' - OK" << '\n';

ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(void);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(decltype(nullptr));
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(bool);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(signed char);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(unsigned char);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(char);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(wchar_t);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(char16_t);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(char32_t);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(int);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(signed);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(unsigned);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(short);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(long);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(long long);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(float);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(double);
ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(long double);
ACF_REF_ASSERTION_TEST_NAME_SIZE_EQ_0(some_type);

//ACF_REF_ASSERTION_TEST_NAME_SIZE_GT_0(BasicBaseClass);

std::cout << "- test \'sdk::name_size_v<?>\' - OK" << '\n';

ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(void);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(decltype(nullptr));
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(bool);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(signed char);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(unsigned char);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(char);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(wchar_t);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(char16_t);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(char32_t);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(int);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(signed);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(unsigned);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(short);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(long);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(long long);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(float);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(double);
ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(long double);
ACF_REF_ASSERTION_TEST_NAME_EMPTY(some_type);

//ACF_REF_ASSERTION_TEST_NAME_NOT_EMPTY(BasicBaseClass);

std::cout << "- test \'sdk::is_name_empty_v<?>\' - OK" << '\n';

ACF_REF_ASSERTION_TEST_SUPPORTED(void);
ACF_REF_ASSERTION_TEST_SUPPORTED(decltype(nullptr));
ACF_REF_ASSERTION_TEST_SUPPORTED(bool);
ACF_REF_ASSERTION_TEST_SUPPORTED(signed char);
ACF_REF_ASSERTION_TEST_SUPPORTED(unsigned char);
ACF_REF_ASSERTION_TEST_SUPPORTED(char);
ACF_REF_ASSERTION_TEST_SUPPORTED(wchar_t);
ACF_REF_ASSERTION_TEST_SUPPORTED(char16_t);
ACF_REF_ASSERTION_TEST_SUPPORTED(char32_t);
ACF_REF_ASSERTION_TEST_SUPPORTED(int);
ACF_REF_ASSERTION_TEST_SUPPORTED(signed);
ACF_REF_ASSERTION_TEST_SUPPORTED(unsigned);
ACF_REF_ASSERTION_TEST_SUPPORTED(short);
ACF_REF_ASSERTION_TEST_SUPPORTED(long);
ACF_REF_ASSERTION_TEST_SUPPORTED(long long);
ACF_REF_ASSERTION_TEST_SUPPORTED(float);
ACF_REF_ASSERTION_TEST_SUPPORTED(double);
ACF_REF_ASSERTION_TEST_SUPPORTED(long double);
ACF_REF_ASSERTION_TEST_NOT_SUPPORTED(some_type);

//ACF_REF_ASSERTION_TEST_SUPPORTED(BasicBaseClass);

std::cout << "- test \'sdk::is_supported_v<?>\' - OK" << '\n';

ACF_REF_ASSERTION_TEST_NOT_BEAN(void);
ACF_REF_ASSERTION_TEST_NOT_BEAN(decltype(nullptr));
ACF_REF_ASSERTION_TEST_NOT_BEAN(bool);
ACF_REF_ASSERTION_TEST_NOT_BEAN(signed char);
ACF_REF_ASSERTION_TEST_NOT_BEAN(unsigned char);
ACF_REF_ASSERTION_TEST_NOT_BEAN(char);
ACF_REF_ASSERTION_TEST_NOT_BEAN(wchar_t);
ACF_REF_ASSERTION_TEST_NOT_BEAN(char16_t);
ACF_REF_ASSERTION_TEST_NOT_BEAN(char32_t);
ACF_REF_ASSERTION_TEST_NOT_BEAN(int);
ACF_REF_ASSERTION_TEST_NOT_BEAN(signed);
ACF_REF_ASSERTION_TEST_NOT_BEAN(unsigned);
ACF_REF_ASSERTION_TEST_NOT_BEAN(short);
ACF_REF_ASSERTION_TEST_NOT_BEAN(long);
ACF_REF_ASSERTION_TEST_NOT_BEAN(long long);
ACF_REF_ASSERTION_TEST_NOT_BEAN(float);
ACF_REF_ASSERTION_TEST_NOT_BEAN(double);
ACF_REF_ASSERTION_TEST_NOT_BEAN(long double);
ACF_REF_ASSERTION_TEST_NOT_BEAN(some_type);

//ACF_REF_ASSERTION_TEST_BEAN(BasicBaseClass);

std::cout << "- test \'sdk::is_bean_v<?>\' - OK" << '\n';

std::cout << ref::index_v<void, 0> << '\n';
std::cout << ref::index_v<some_type, 0> << '\n';
//std::cout << ref::index_v<BasicBaseClass, 0> << '\n';

std::cout << ref::is_indexed_v<void> << '\n';
std::cout << ref::is_indexed_v<some_type> << '\n';
//std::cout << ref::is_indexed_v<BasicBaseClass> << '\n';

//using id = ref::index<BasicBaseClass, 0>;
//static_assert(std::experimental::is_same_v<ref::read_asseccor<id>::index_type, id>);
//static_assert(std::experimental::is_same_v<ref::read_asseccor<id>::value_type, bool (BasicBaseClass::*)() const>);
//static_assert(ref::read_asseccor<id>::value == (bool (BasicBaseClass::*)() const) &BasicBaseClass::bool_value);

//static_assert(std::experimental::is_same_v<ref::write_asseccor<id>::index_type, id>);

//BasicBaseClass l_bbc { };
//ref::member_type<id> l_mem { };
//l_mem.value(l_bbc, false);
//to_string(std::forward<BasicBaseClass>(l_bbc));
}

class CompleteType {};
class IncompleteType;

void is_complete_test()
{
    assertion_trigger<ref::is_complete, supported_types> {}();
    assertion_trigger<ref::is_complete, std::tuple<CompleteType>> {}();
    assertion_trigger<ref::is_complete, std::tuple<IncompleteType>, true> {}();
}

class NoValueType {};
class HasValueType
{
public:
static constexpr bool value = true;
using value_type = bool;
};

void has_value_test()
{
    assertion_trigger<ref::has_value, supported_types, true> {}();
    assertion_trigger<ref::has_value, std::tuple<NoValueType>, true> {}();
    assertion_trigger<ref::has_value, std::tuple<HasValueType>> {}();
}

void has_value_type_test()
{
    assertion_trigger<ref::has_value_type, supported_types, true> {}();
    assertion_trigger<ref::has_value_type, std::tuple<NoValueType>, true> {}();
    assertion_trigger<ref::has_value_type, std::tuple<HasValueType>> {}();
}

class NoNamedType {};

void is_named_test()
{
    assertion_trigger<ref::is_named, supported_types> {}();
    assertion_trigger<ref::is_named, std::tuple<NoNamedType>, true> {}();
}

void is_name_of_test()
{
    static_assert(check_name<ref::name_of<void>>("void"), "");
    assert(check_name<ref::name_of<void>>("void"));
}

void is_bean_test()
{
    assertion_trigger<ref::is_bean, supported_types, true> {}();
}

void bean_size_test()
{
//    static_assert(!(ref::bean_size<void>::value > 0), "");
}

