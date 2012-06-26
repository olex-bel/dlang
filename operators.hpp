/* 
 * File:   operators.hpp
 * Author: konung
 *
 * Created on 26 Июнь 2012 г., 16:06
 */

#ifndef OPERATORS_HPP
#define	OPERATORS_HPP

#include "method.h"
#include <values.h>
#include <boost/shared_ptr.hpp>

template <typename T>
class AssigmnentOperator: public AbstractMethod
{
    T* left;
    T* right;
    
public:
    virtual boost::shared_ptr<AbstractValue> operator()();
    virtual void setParam(size_t num, AbstractValue* value);
};

template <typename T>
class UnaryMinusOperator: public AbstractMethod
{
    T* val;
    
public:
    virtual boost::shared_ptr<AbstractValue> operator()();
    virtual void setParam(size_t num, AbstractValue* value);
};

template <typename T>
class AddOperator: public AbstractMethod
{
    T* left;
    T* right;
    
public:
    virtual boost::shared_ptr<AbstractValue> operator()();
    virtual void setParam(size_t num, AbstractValue* value);
};


template <typename T>
class SubOperator: public AbstractMethod
{
    T* left;
    T* right;
    
public:
    virtual boost::shared_ptr<AbstractValue> operator()();
    virtual void setParam(size_t num, AbstractValue* value);
};

template <typename T>
class MulOperator: public AbstractMethod
{
    T* left;
    T* right;
    
public:
    virtual boost::shared_ptr<AbstractValue> operator()();
    virtual void setParam(size_t num, AbstractValue* value);
};


template <typename T>
class DivOperator: public AbstractMethod
{
    T* left;
    T* right;
    
public:
    virtual boost::shared_ptr<AbstractValue> operator()();
    virtual void setParam(size_t num, AbstractValue* value);
};

template <typename T>
boost::shared_ptr<AbstractValue> AssigmnentOperator<T>::operator()()
{    
    if ( !left | !right )
        throw "Agument not set";
    
    left->setValue(right->value());
    boost::shared_ptr<AbstractValue> result = left->clone();    
    
    return result;
}

template <typename T>
void AssigmnentOperator<T>::setParam(size_t num, AbstractValue* value)
{ 
    switch ( num ){
        case 1:
            left = dynamic_cast<T*>(value);
            break;
        case 2:
            right = dynamic_cast<T*>(value);
            break;
        default:
            throw "Out of agument range";
    }
}

template <typename T>
boost::shared_ptr<AbstractValue> UnaryMinusOperator<T>::operator ()()
{
    boost::shared_ptr<AbstractValue> result = val->clone();
    
    dynamic_cast<T*>(result.get())->setValue(val->value() * -1);
    
    return result;
}

template <typename T>
void UnaryMinusOperator<T>::setParam(size_t num, AbstractValue* value)
{
    if ( num == 1 ) val = dynamic_cast<T*>(value);
    else
        throw "Out of agument range";
}

template <typename T>
boost::shared_ptr<AbstractValue> AddOperator<T>::operator ()()
{
    T* result = new T();
    
    result->setValue(left->value() + right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

template <typename T>
void AddOperator<T>::setParam(size_t num, AbstractValue* value)
{
    switch ( num ){
        case 1:
            left = dynamic_cast<T*>(value);
            break;
        case 2:
            right = dynamic_cast<T*>(value);
            break;
        default:
            throw "Out of agument range";
    }
}

template <typename T>
boost::shared_ptr<AbstractValue> SubOperator<T>::operator ()()
{
    T* result = new T();
    
    result->setValue(left->value() - right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

template <typename T>
void SubOperator<T>::setParam(size_t num, AbstractValue* value)
{   
    switch ( num ){
        case 1:
            left = dynamic_cast<T*>(value);
            break;
        case 2:
            right = dynamic_cast<T*>(value);
            break;
        default:
            throw "Out of agument range";
    }
}

template <typename T>
boost::shared_ptr<AbstractValue> MulOperator<T>::operator ()()
{
    T* result = new T();
    
    result->setValue(left->value() * right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

template <typename T>
void MulOperator<T>::setParam(size_t num, AbstractValue* value)
{
    switch ( num ){
        case 1:
            left = dynamic_cast<T*>(value);
            break;
        case 2:
            right = dynamic_cast<T*>(value);
            break;
        default:
            throw "Out of agument range";
    }
}

template <typename T>
boost::shared_ptr<AbstractValue> DivOperator<T>::operator ()()
{
    T* result = new T();
    
    if ( right->value() == 0 )
        throw "Div by zero";
    
    result->setValue(left->value() / right->value());
    boost::shared_ptr<AbstractValue> ptr(result);
    
    return ptr;
}

template <typename T>
void DivOperator<T>::setParam(size_t num, AbstractValue* value)
{   
    switch ( num ){
        case 1:
            left = dynamic_cast<T*>(value);
            break;
        case 2:
            right = dynamic_cast<T*>(value);
            break;
        default:
            throw "Out of agument range";
    }
}

#endif	/* OPERATORS_HPP */

