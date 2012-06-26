/* 
 * File:   number_value.hpp
 * Author: konung
 *
 * Created on 25 Июнь 2012 г., 23:28
 */

#ifndef NUMBER_VALUE_HPP
#define	NUMBER_VALUE_HPP

#include <string>
#include <boost/lexical_cast.hpp>
#include "values.h"
#include "operators.hpp"


template<typename T, ValueType TypeID>
class NumberValue: public AbstractValue
{
    T data;
    
public:
    NumberValue();
    virtual void copyData(AbstractValue* val);
    void setValue(T val);
    T value();
    virtual ValueType type() { return TypeID; };
    virtual std::string toString() const;
    virtual void setVal(AbstractValue* val);
    virtual boost::shared_ptr<AbstractValue> clone();
};

template<typename T, ValueType TypeID>
NumberValue<T, TypeID>::NumberValue()
{
    methods["operator="] = new AssigmnentOperator<NumberValue<T, TypeID> >();
    methods["operator+"] = new AddOperator<NumberValue<T, TypeID> >();
    methods["operator-"] = new SubOperator<NumberValue<T, TypeID> >();
    methods["operator*"] = new MulOperator<NumberValue<T, TypeID> >();
    methods["operator/"] = new DivOperator<NumberValue<T, TypeID> >();
    methods["operator-u"] = new UnaryMinusOperator<NumberValue<T, TypeID> >();
}

/* absolute interface*/
template<typename T, ValueType TypeID>
void NumberValue<T, TypeID>::copyData(AbstractValue* val)
{
    setVal(val);
}

template<typename T, ValueType TypeID>
void NumberValue<T, TypeID>::setValue(T val)
{
    data = val;
}

template<typename T, ValueType TypeID>
T NumberValue<T, TypeID>::value()
{
    return data;
}

template<typename T, ValueType TypeID>
std::string NumberValue<T, TypeID>::toString() const
{
    return boost::lexical_cast<std::string>(data);
}

template<typename T, ValueType TypeID>
void NumberValue<T, TypeID>::setVal(AbstractValue* val)
{
    if ( this->type() != val->type() )
        throw "Variable must be the same type";
    
    NumberValue<T, TypeID>* numVal = dynamic_cast<NumberValue<T, TypeID>*>(val);
    setValue(numVal->value());
}

template<typename T, ValueType TypeID>
boost::shared_ptr<AbstractValue> NumberValue<T, TypeID>::clone()
{
    NumberValue<T, TypeID>* numVal = new NumberValue<T, TypeID>();
    numVal->setValue(this->value());
    
    boost::shared_ptr<AbstractValue> ptr(numVal);
    
    return ptr;
}

#endif	/* NUMBER_VALUE_HPP */

