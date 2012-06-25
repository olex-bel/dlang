/* 
 * File:   method.h
 * Author: konung
 *
 * Created on 18 Июнь 2012 г., 23:32
 */

#ifndef METHOD_H
#define	METHOD_H

#include <cstddef>
#include <boost/shared_ptr.hpp>

class AbstractValue;

class AbstractMethod{
public:
    virtual boost::shared_ptr<AbstractValue> operator()() = 0;
    virtual void setParam(size_t num, AbstractValue* value) = 0;
};



#endif	/* METHOD_H */

