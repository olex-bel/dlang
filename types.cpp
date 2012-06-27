#include "types.h"
#include <stdint.h>
#include "number_value.hpp"

AbstractValue* Int32Type::create()
{
    NumberValue<int32_t, VINT32>* val = new NumberValue<int32_t, VINT32>();
    
    return val;
}

AbstractValue* DoubleType::create()
{
    NumberValue<double, VDOUBLE>* val = new NumberValue<double, VDOUBLE>();
    
    return val;
}

AbstractValue* StringType::create()
{
    StringValue* val = new StringValue();
    
    return val;
}
