#include "values.h"

void Int32Value::copyData(AbstractValue* val)
{
    if ( this->type() != val->type() )
        throw "Variable must be the same type";
    
    Int32Value* intVal = dynamic_cast<Int32Value*>(val);
    setValue(intVal->value());
}

void StringValue::copyData(AbstractValue* val)
{
    if ( this->type() != val->type() )
        throw "Variable must be the same type";
    
    StringValue* strVal = dynamic_cast<StringValue*>(val);
    setValue(strVal->value());
}

