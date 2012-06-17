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