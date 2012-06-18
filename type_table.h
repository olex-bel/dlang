/* 
 * File:   type_table.h
 * Author: konung
 *
 * Created on 14 Июнь 2012 г., 23:53
 */

#ifndef TYPE_TABLE_H
#define	TYPE_TABLE_H

#include <string>
#include <map>
#include "types.h"

typedef std::map<std::string, AbstractType*> TableStore;

class TypeTable
{
     TableStore table;
    
public:
    TypeTable();
    AbstractType* prototype(std::string name);
};

extern TypeTable* globalTypeTable;

#endif	/* TYPE_TABLE_H */

