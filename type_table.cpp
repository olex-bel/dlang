#include "type_table.h"
#include <iostream>

TypeTable::TypeTable()
{
    table["int"] = new Int32Type();
    table["string"] = new StringType();
}

AbstractType* TypeTable::prototype(std::string name)
{
    TableStore::iterator it;
    AbstractType* type = 0;
    
    if ( table.find(name) != table.end() ){ 
        type = table[name];
    }
    
    return type;
}