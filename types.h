/* 
 * File:   types.h
 * Author: konung
 *
 * Created on 18 Июнь 2012 г., 19:25
 */

#ifndef TYPES_H
#define	TYPES_H

#include "values.h"

class AbstractType{
public:
    virtual AbstractValue* create() = 0;
};

class Int32Type: public AbstractType
{    
public:
    virtual AbstractValue* create();
};

class StringType: public AbstractType
{
public:
    virtual AbstractValue* create();
};

#endif	/* TYPES_H */

