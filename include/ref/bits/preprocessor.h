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

#ifndef PREPROCESSOR_H_
#define PREPROCESSOR_H_ 1

///
/// \def ACF_REF_NAME(Type)
/// specialize template class name for given \a Type
///
#define REGISTER_REF_NAME_OF_AS(Type, Name)                         \
namespace ref {                                                     \
                                                                    \
template <>                                                         \
struct name_of<argument_type<void(Type)>::type>                     \
{                                                                   \
    static constexpr char value[] { Name };                         \
    using value_type = decltype(value);                             \
};                                                                  \
                                                                    \
constexpr char name_of<argument_type<void(Type)>::type>::value[];   \
                                                                    \
}

//template <>
//struct name_of<void>
//{
//    static constexpr char value[] { "void" };
//    using value_type = decltype(value);
//};
//
//constexpr char name_of<void>::value[];

///
/// \def REGISTER_REF_NAME_OF(Type)
/// specialize template class name for given \a Type
///
#define REGISTER_REF_NAME_OF(Type)                                  \
        REGISTER_REF_NAME_OF_AS(Type, #Type)

///
/// \def REGISTER_REF_MEM_INDEX(Type, tt_index)
/// specialize template class index for given \a Type and \a tt_index
///
#define REGISTER_REF_MEM_INDEX(Type, tt_index)                      \
namespace ref {                                                     \
                                                                    \
template <>                                                         \
struct index<Type, tt_index> :                                      \
    public ref::index_impl<Type, tt_index> {};                      \
                                                                    \
}

///
/// \def REGISTER_REF_MEM_NAME_OF(Type, tt_index, tt_name)
/// specialize template class name for given \a Type and \a tt_index \a tt_name
///
#define REGISTER_REF_MEM_NAME_OF(Type, tt_index, tt_name)           \
        REGISTER_REF_NAME_OF_AS((ref::index<Type, tt_index>), #tt_name)

#endif /* PREPROCESSOR_H_ */
