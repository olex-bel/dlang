#include "values.h"

AbstractMethod* AbstractValue::getMethod(std::string name)
{
    AbstractMethod* mthd = 0;
    if ( methods.find(name) != methods.end() )
        mthd =  methods[name];
    
    return mthd;
}

Int32Value::Int32Value()
:AbstractValue()
{
    methods["operator="] = new AssigmnentInt32();
}

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

AbstractValue* AssigmnentInt32::operator()()
{    
    if ( !left | !right )
        throw "Agument not set";
    
    left->setValue(right->value());
}

void AssigmnentInt32::setParam(size_t num, AbstractValue* value)
{
    
    if ( value->type() != VINT32 )
        throw "Invalid agument type";
    
    switch ( num ){
        case 1:
            left = dynamic_cast<Int32Value*>(value);
            break;
        case 2:
            right = dynamic_cast<Int32Value*>(value);
            break;
        default:
            throw "Out of agument range";
    }
}
