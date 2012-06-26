#include "values.h"
#include "operators.hpp"

AbstractMethod* AbstractValue::getMethod(std::string name)
{
    AbstractMethod* mthd = 0;
    if ( methods.find(name) != methods.end() )
        mthd =  methods[name];
    else
        throw "Method undefined";
    
    return mthd;
}

StringValue::StringValue()
{
    methods["operator="] = new AssigmnentOperator<StringValue>();
    methods["operator+"] = new AddOperator<StringValue>();
}

void StringValue::copyData(AbstractValue* val)
{
    if ( this->type() != val->type() )
        throw "Variable must be the same type";
    
    StringValue* strVal = dynamic_cast<StringValue*>(val);
    setValue(strVal->value());
}

void StringValue::setVal(AbstractValue* val)
{
    if ( this->type() != val->type() )
        throw "Variable must be the same type";
    
    StringValue* strVal = dynamic_cast<StringValue*>(val);
    setValue(strVal->value());
}


boost::shared_ptr<AbstractValue> StringValue::clone()
{
    StringValue* strVal = new StringValue();
    strVal->setValue(this->value());
    
    boost::shared_ptr<AbstractValue> ptr(strVal);
    
    return ptr;
}
