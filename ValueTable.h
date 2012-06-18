/* 
 * File:   ValueTable.h
 * Author: konung
 *
 * Created on 18 Июнь 2012 г., 20:05
 */

#ifndef VALUETABLE_H
#define	VALUETABLE_H

#include <string>
#include <map>
#include "values.h"
#include "types.h"

class ValueTable {
public:
    bool add(std::string name, AbstractType* type);
    bool exists(std::string name);
    bool del(std::string name);
    AbstractValue* value(std::string name);
    
private:
    std::map<std::string, AbstractValue*> table;
};

extern ValueTable* globalValueTable;

#endif	/* VALUETABLE_H */

