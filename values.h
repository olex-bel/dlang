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

enum ValueType { VINT32, VSTRING };

class AbstractValue {
public:
    virtual ValueType type() = 0;
    virtual std::string toString() const = 0;
    virtual void copyData(AbstractValue* val) = 0;
};

class Int32Value: public AbstractValue
{
    int32_t data;
    
public:
    virtual void copyData(AbstractValue* val);
    void setValue(int32_t num) { data = num; };
    int32_t value() { return data; };
    virtual ValueType type() { return VINT32; };
    virtual std::string toString() const 
    {
        return boost::lexical_cast<std::string>(data);
    };
};

class StringValue: public AbstractValue
{
    std::string data;
    
public:
    virtual void copyData(AbstractValue* val);
    void setValue(std::string str) { data = str; };
    std::string value() { return data; };
    virtual ValueType type() { return VSTRING; };
    virtual std::string toString() const
    {
        return data;
    };
};

#endif	/* VALUES_H */

