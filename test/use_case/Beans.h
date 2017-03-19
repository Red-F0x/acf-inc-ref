/*
 * Beans.h
 *
 *  Created on: 09.02.2017
 *      Author: ho11owman
 */

#ifndef BEANS_H_
#define BEANS_H_

//#include "ref/bean_traits.h"
#include "ref/bits/fwd.h"
#include "ref/bits/preprocessor.h"

class BasicBeanClass
{
private:
    bool m_bool_v { true };

public:
    BasicBeanClass() = default;
    BasicBeanClass(const BasicBeanClass&) = default;
    BasicBeanClass(BasicBeanClass&&) = default;
    virtual ~BasicBeanClass() = default;

public:
    bool bool_value() const
    {
        return m_bool_v;
    }
    void bool_value(bool t_value)
    {
        m_bool_v = t_value;
    }
};

REGISTER_REF_NAME_OF(BasicBeanClass);

REGISTER_REF_MEM_INDEX(BasicBeanClass, 0);
REGISTER_REF_MEM_NAME_OF(BasicBeanClass, 0, bool_value);

namespace ref
{

template <>
struct read_asseccor<ref::index<BasicBeanClass, 0>> :
                                                           public details::read_asseccor_impl<
                                                                   ref::index<BasicBeanClass, 0>,
                                                                   bool (BasicBeanClass::*)() const,
                                                                   (bool (BasicBeanClass::*)() const) &BasicBeanClass::bool_value>
{
};

} // namespace ref

namespace ref
{

template <>
struct write_asseccor<ref::index<BasicBeanClass, 0>> :
                                                            public details::write_asseccor_impl<
                                                                    ref::index<BasicBeanClass, 0>,
                                                                    void (BasicBeanClass::*)(bool),
                                                                    (void (BasicBeanClass::*)(bool)) &BasicBeanClass::bool_value>
{
};

} // namespace ref

#endif /* BEANS_H_ */
