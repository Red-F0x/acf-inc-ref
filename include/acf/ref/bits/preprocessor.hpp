///
/// \file include/acf/ref/bits/preprocessor.hpp
///
///  Created on: 09.02.2017
///      Author: ho11owman
///
/// \brief macro group for registering class and class members
///
/// For more information how to work with c++ preprocessor use
/// <a href="http://en.cppreference.com/w/cpp/preprocessor">this link</a>.
///

#ifndef PREPROCESSOR_HPP_
#define PREPROCESSOR_HPP_

#include "acf/std_type_traits.h"

///
/// \def ACF_REF_NAME(Type)
/// specialize template class name for given \a Type
///
#define ACF_REF_NAME(Type)                                          \
namespace ref {                                                     \
                                                                    \
template <>                                                         \
struct name_of<Type>                                                \
{                                                                   \
    static constexpr char value[] = { #Type };                      \
    using type = decltype(value);                                   \
};                                                                  \
                                                                    \
constexpr char name_of<Type>::value[];                              \
                                                                    \
}

///
/// \def ACF_REF_INDEX(Type, tt_index)
/// specialize template class index for given \a Type and \a tt_index
///
#define ACF_REF_INDEX(Type, tt_index)                               \
namespace ref {                                                     \
                                                                    \
template <>                                                         \
struct index<Type, tt_index> :                                      \
    public ref::index_impl<Type, tt_index> {};                      \
                                                                    \
}

///
/// \def ACF_REF_MEM_NAME(Type, tt_index, tt_name)
/// specialize template class name for given \a Type and \a tt_index \a tt_name
///
#define ACF_REF_MEM_NAME(Type, tt_index, tt_name)                   \
namespace ref {                                                     \
                                                                    \
template <>                                                         \
struct name_of<ref::index<Type, tt_index>>                          \
{                                                                   \
    static constexpr char value[] = #tt_name;                       \
    using type = decltype(value);                                   \
};                                                                  \
                                                                    \
constexpr char name_of<ref::index<Type, tt_index>>::value[];        \
                                                                    \
}

#endif /* PREPROCESSOR_HPP_ */
