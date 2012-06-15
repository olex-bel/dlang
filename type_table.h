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

class AbstractValue {};

struct ValueInfo{
    enum ValueType { VINT32, VSTRING };
    
    ValueType type;
    AbstractValue* value;
};

class Int32Value: public AbstractValue
{
    int32_t data;
};

class StringValue: public AbstractValue
{
    std::string data;
};


class TypeTable
{
    std::map<std::string, ValueInfo> table;
    
public:
    bool add(std::string id, ValueInfo::ValueType type);
    bool exists(std::string id);
    ValueInfo value(std::string id);
};

extern TypeTable* globalTypeTable;

#endif	/* TYPE_TABLE_H */

