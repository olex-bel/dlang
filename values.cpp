#include "values.h"

AbstractMethod* AbstractValue::getMethod(std::string name)
{
    AbstractMethod* mthd = 0;
    if ( methods.find(name) != methods.end() )
        mthd =  methods[name];
    else
        throw "Method undefined";
    
    return mthd;
}

Int32Value::Int32Value()
:AbstractValue()
{
    methods["operator="] = new AssigmnentInt32();
    methods["operator+"] = new AddInt32();
    methods["operator-"] = new SubInt32();
    methods["operator*"] = new MulInt32();
    methods["operator/"] = new DivInt32();
    methods["operator-u"] = new UnaryMinusInt32();
}

void Int32Value::copyData(AbstractValue* val)
{
    if ( this->type() != val->type() )
        throw "Variable must be the same type";
    
    Int32Value* intVal = dynamic_cast<Int32Value*>(val);
    setValue(intVal->value());
}

void Int32Value::setVal(AbstractValue* val)
{
    if ( this->type() != val->type() )
        throw "Variable must be the same type";
    
    Int32Value* intVal = dynamic_cast<Int32Value*>(val);
    setValue(intVal->value());
}

boost::shared_ptr<AbstractValue> Int32Value::clone()
{
    Int32Value* intVal = new Int32Value();
    intVal->setValue(this->value());
    
    boost::shared_ptr<AbstractValue> ptr(intVal);
    
    return ptr;
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

boost::shared_ptr<AbstractValue> AssigmnentInt32::operator()()
{    
    if ( !left | !right )
        throw "Agument not set";
    
    left->setValue(right->value());
    boost::shared_ptr<AbstractValue> result = left->clone();    
    
    return result;
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

boost::shared_ptr<AbstractValue> UnaryMinusInt32::operator ()()
{
    boost::shared_ptr<AbstractValue> result = val->clone();
    
    dynamic_cast<Int32Value*>(result.get())->setValue(val->value() * -1);
    
    return result;
}

void UnaryMinusInt32::setParam(size_t num, AbstractValue* value)
{
    if ( value->type() != VINT32 )
        throw "Invalid agument type";
    
    if ( num == 1 ) val = dynamic_cast<Int32Value*>(value);
    else
        throw "Out of agument range";
}

boost::shared_ptr<AbstractValue> AddInt32::operator ()()
{
    Int32Value* result = new Int32Value();
    
    result->setValue(left->value() + right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

void AddInt32::setParam(size_t num, AbstractValue* value)
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

boost::shared_ptr<AbstractValue> SubInt32::operator ()()
{
    Int32Value* result = new Int32Value();
    
    result->setValue(left->value() - right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

void SubInt32::setParam(size_t num, AbstractValue* value)
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

boost::shared_ptr<AbstractValue> MulInt32::operator ()()
{
    Int32Value* result = new Int32Value();
    
    result->setValue(left->value() * right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

void MulInt32::setParam(size_t num, AbstractValue* value)
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

boost::shared_ptr<AbstractValue> DivInt32::operator ()()
{
    Int32Value* result = new Int32Value();
    
    if ( right->value() == 0 )
        throw "Div by zero";
    
    result->setValue(left->value() / right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

void DivInt32::setParam(size_t num, AbstractValue* value)
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
