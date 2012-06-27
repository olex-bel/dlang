/* 
 * File:   values.h
 * Author: konung
 *
 * Created on 18 Июнь 2012 г., 19:27
 */

#ifndef VALUES_H
#define	VALUES_H

#include <stdint.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include "method.h"

enum ValueType { VINT32, VSTRING, VDOUBLE };

class AbstractValue {
protected:
    std::map<std::string, AbstractMethod*> methods;
    
public:
    virtual ValueType type() = 0;
    virtual std::string toString() const = 0;
    virtual void copyData(AbstractValue* val) = 0;
    virtual void setVal(AbstractValue* val) = 0;
    virtual boost::shared_ptr<AbstractValue> clone() = 0;
    virtual AbstractMethod* getMethod(std::string name);
};

class StringValue: public AbstractValue
{
    std::string data;
    
public:
    StringValue();
    virtual void copyData(AbstractValue* val);
    void setValue(std::string str) { data = str; };
    std::string value() { return data; };
    virtual ValueType type() { return VSTRING; };
    virtual std::string toString() const
    {
        return data;
    };
    virtual void setVal(AbstractValue* val);
    virtual boost::shared_ptr<AbstractValue> clone();
};

#endif	/* VALUES_H */

