/*
 * Beans.h
 *
 *  Created on: 09.02.2017
 *      Author: ho11owman
 */

#ifndef BEANS_H_
#define BEANS_H_

#include "ref/bean_traits.h"

class BasicBaseClass
{
private:
    bool m_bool_v { true };

public:
    BasicBaseClass() = default;
    BasicBaseClass(const BasicBaseClass&) = default;
    BasicBaseClass(BasicBaseClass&&) = default;
    virtual ~BasicBaseClass() = default;

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

REGISTER_REF_NAME_OF(BasicBaseClass);

REGISTER_REF_MEM_INDEX(BasicBaseClass, 0);
REGISTER_REF_MEM_NAME_OF(BasicBaseClass, 0, bool_value);

namespace ref
{

template <>
struct read_asseccor<ref::index<BasicBaseClass, 0>> :
                                                           public details::read_asseccor_impl<
                                                                   ref::index<BasicBaseClass, 0>,
                                                                   bool (BasicBaseClass::*)() const,
                                                                   (bool (BasicBaseClass::*)() const) &BasicBaseClass::bool_value>
{
};

} // namespace ref

namespace ref
{

template <>
struct write_asseccor<ref::index<BasicBaseClass, 0>> :
                                                            public details::write_asseccor_impl<
                                                                    ref::index<BasicBaseClass, 0>,
                                                                    void (BasicBaseClass::*)(bool),
                                                                    (void (BasicBaseClass::*)(bool)) &BasicBaseClass::bool_value>
{
};

} // namespace ref

#endif /* BEANS_H_ */
