#include "type_table.h"

bool TypeTable::add(std::string id, ValueInfo::ValueType type)
{
    bool result; 
    
    if ( (result = (table.find(id) == table.end())) ){
        ValueInfo vinf;
        
        vinf.type = type;
        switch ( type ){
            case ValueInfo::VINT32:
                vinf.value = new Int32Value();
                break;
            case ValueInfo::VSTRING:
                vinf.value = new StringValue();
                break;
        }
        
        table[id] = vinf;
    }
    
    return result;
}

bool TypeTable::exists(std::string id)
{
    return table.find(id) != table.end();
}

ValueInfo TypeTable::value(std::string id)
{
    return table[id];
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
