/*
 * Beans.h
 *
 *  Created on: 09.02.2017
 *      Author: ho11owman
 */

#ifndef BEANS_H_
#define BEANS_H_

#include "acf/ref/bean_traits.h"

class Beans
{
public:
    Beans ();
    virtual
    ~Beans ();
};

class BasicBaseClass
{
private:
    bool m_bool_v;
};

ACF_REF_NAME(BasicBaseClass);

ACF_REF_INDEX(BasicBaseClass, 0);
ACF_REF_MEM_NAME(BasicBaseClass, 0, bool_value);

#endif /* BEANS_H_ */
