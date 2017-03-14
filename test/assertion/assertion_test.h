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
//        decltype(nullptr),
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

void is_complete_test();
void has_value_test();
void is_named();


#endif /* ASSERTION_TEST_H_ */
