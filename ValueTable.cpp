/* 
 * File:   ValueTable.cpp
 * Author: konung
 * 
 * Created on 18 Июнь 2012 г., 20:05
 */

#include "ValueTable.h"

bool ValueTable::add(std::string name, AbstractType* type)
{
    bool result;
    
    if (result = (table.find(name) == table.end()) )
        table[name] = type->create();
    
    return result;
}

bool ValueTable::exists(std::string name)
{
    return table.find(name) != table.end();
}

bool ValueTable::del(std::string name)
{
    return false;
}

AbstractValue* ValueTable::value(std::string name)
{
    AbstractValue* val = 0;
    
    if ( table.find(name) != table.end() )
        val = table[name];
    
    return val;
}
