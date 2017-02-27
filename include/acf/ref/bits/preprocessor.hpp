/*
 * preprocessor.hpp
 *
 *  Created on: 09.02.2017
 *      Author: ho11owman
 */

#ifndef PREPROCESSOR_HPP_
#define PREPROCESSOR_HPP_

//http://en.cppreference.com/w/cpp/preprocessor
#include "acf/std_type_traits.h"

#define ACF_REF_NAME(Type)                          \
namespace acf {                                     \
                                                    \
namespace ref {                                     \
                                                    \
template <>                                         \
struct name<Type>                                   \
{                                                   \
    static constexpr char value[] = #Type;          \
    using type = decltype(value);                   \
};                                                  \
                                                    \
constexpr char name<Type>::value[];                 \
                                                    \
}                                                   \
                                                    \
}

#define ACF_REF_INDEX(Type, tt_index)               \
namespace acf {                                     \
                                                    \
namespace ref {                                     \
                                                    \
template <>                                         \
struct index<Type, tt_index> :                      \
    public acf::ref::index_impl<Type, tt_index> {}; \
                                                    \
}                                                   \
                                                    \
}

#define ACF_REF_MEM_NAME(Type, tt_index, tt_name)                \
namespace acf {                                                  \
                                                                 \
namespace ref {                                                  \
                                                                 \
template <>                                                      \
struct name<acf::ref::index<Type, tt_index>>                     \
{                                                                \
    static constexpr char value[] = #tt_name;                    \
    using type = decltype(value);                                \
};                                                               \
                                                                 \
constexpr char name<acf::ref::index<Type, tt_index>>::value[];   \
                                                                 \
}                                                                \
                                                                 \
}

#endif /* PREPROCESSOR_HPP_ */
