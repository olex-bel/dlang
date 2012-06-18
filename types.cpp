#include "types.h"

AbstractValue* Int32Type::create()
{
    Int32Value* val = new Int32Value();
    
    return val;
}

AbstractValue* StringType::create()
{
    StringValue* val = new StringValue();
    
    return val;
}
