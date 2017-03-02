/*
 * Beans.h
 *
 *  Created on: 09.02.2017
 *      Author: ho11owman
 */

#ifndef BEANS_H_
#define BEANS_H_

#include "acf/ref/bean_traits.h"

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
    bool bool_value() const { return m_bool_v; }
};

ACF_REF_NAME(BasicBaseClass);

ACF_REF_INDEX(BasicBaseClass, 0);
ACF_REF_MEM_NAME(BasicBaseClass, 0, bool_value);

namespace acf
{

namespace ref
{

template <>
struct read_asseccor<acf::ref::index<BasicBaseClass, 0>> :
    public details::read_asseccor_impl<acf::ref::index<BasicBaseClass, 0>, decltype(&BasicBaseClass::bool_value), &BasicBaseClass::bool_value>
{
};

}
 // namespace ref

}// namespace acf

#endif /* BEANS_H_ */
