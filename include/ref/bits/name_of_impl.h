//
// name_of_impl.h
//
//  Created on: 13.03.2017
//      Author: ho11owman
//

#ifndef NAME_OF_IMPL_H_
#define NAME_OF_IMPL_H_ 1

#include "ref/bits/fwd.h"
#include "ref/bits/preprocessor.h"

/// define name_of for void type
REGISTER_REF_NAME_OF_AS(void,                   "void");

/// define name_of for std::nullptr_t type
REGISTER_REF_NAME_OF_AS(std::nullptr_t,        "nullptr");

/// define name_of for bool type
REGISTER_REF_NAME_OF_AS(bool,                   "bool");

/// define name_of for character types
REGISTER_REF_NAME_OF_AS(signed char,            "signed char");
REGISTER_REF_NAME_OF_AS(unsigned char,          "unsigned char");
REGISTER_REF_NAME_OF_AS(char,                   "char");
REGISTER_REF_NAME_OF_AS(wchar_t,                "wchar_t");
REGISTER_REF_NAME_OF_AS(char16_t,               "char16_t");
REGISTER_REF_NAME_OF_AS(char32_t,               "char32_t");

/// define name_of for integer types
REGISTER_REF_NAME_OF_AS(short int,              "short int");
REGISTER_REF_NAME_OF_AS(unsigned short int,     "unsigned short int");

REGISTER_REF_NAME_OF_AS(int,                    "int");
REGISTER_REF_NAME_OF_AS(unsigned int,           "unsigned int");

REGISTER_REF_NAME_OF_AS(long int,               "long int");
REGISTER_REF_NAME_OF_AS(unsigned long int,      "unsigned long int");

REGISTER_REF_NAME_OF_AS(long long int,          "long long int");
REGISTER_REF_NAME_OF_AS(unsigned long long int, "unsigned long long int");

/// define name_of for floating point types
REGISTER_REF_NAME_OF_AS(float,                  "float");
REGISTER_REF_NAME_OF_AS(double,                 "double");
REGISTER_REF_NAME_OF_AS(long double,            "long double");

#endif /* NAME_OF_IMPL_H_ */
