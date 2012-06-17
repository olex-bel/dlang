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
#include <stdint.h>
#include <boost/lexical_cast.hpp>

class AbstractValue {
public:
    virtual int type() = 0;
    virtual std::string toString() const = 0;
    virtual void copyData(AbstractValue* val) = 0;
};

struct ValueInfo{
    enum ValueType { VINT32, VSTRING };
    
    ValueType type;
    AbstractValue* value;
};

class Int32Value: public AbstractValue
{
    int32_t data;
    
public:
    virtual void copyData(AbstractValue* val);
    void setValue(int32_t num) { data = num; };
    int32_t value() { return data; };
    virtual int type() { return ValueInfo::VINT32; };
    virtual std::string toString() const 
    {
        return boost::lexical_cast<std::string>(data);
    };
};

class StringValue: public AbstractValue
{
    std::string data;
    
public:
    virtual void copyData(AbstractValue* val);
    void setValue(std::string str) { data = str; };
    std::string value() { return data; };
    virtual int type() { return ValueInfo::VSTRING; };
    virtual std::string toString() const
    {
        return data;
    };
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

