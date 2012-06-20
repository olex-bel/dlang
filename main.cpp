/* 
 * File:   main.cpp
 * Author: konung
 *
 * Created on 13 Июнь 2012 г., 22:47
 */

#include <cstdlib>
#include <iostream>
#include "lex_table.h"
#include "lexer.h"
#include "type_table.h"
#include "ValueTable.h"
#include "struct_def.h"
#include "strutil.h"

int yylval;
LexemTable* globalLexTable;
TypeTable* globalTypeTable;
ValueTable* globalValueTable;
int curr_tok;

void typeDef();
void assigmnent(std::string id);
void identifier();
void assign(std::string id1, std::string id2);

AbstractValue* expr(bool get);
AbstractValue* term(bool get);
AbstractValue* prim(bool get);

int main(int argc, char** argv) {

    int lex;
    
    globalLexTable = new LexemTable();
    globalTypeTable = new TypeTable();
    globalValueTable = new ValueTable();
    
    try{
        while ( (lex = yylex()) != 0 ){
                if ( lex == TYPE ) typeDef();
                if ( lex == ID ) identifier();
        }
    }catch(const char* s){
        std::cout << s << std::endl;
    }
        
    delete globalLexTable;
    delete globalTypeTable;
    
    return 0;
}

void typeDef()
{
    AbstractType* type = globalTypeTable->prototype(yytext);
    
    if ( !type )
        throw "Unknow type";
    
    int lex = yylex();
    if ( lex != ID ) throw "Must be identifier";
    
    if ( !globalValueTable->add((*globalLexTable)[yylval].text, type) )
        throw "Redefinition of an identifier";
    
    lex = yylex();
    if ( lex != SEMICOLON ) throw "; expected";
}

void identifier()
{
    std::string id = (*globalLexTable)[yylval].text;
    
    if ( !globalValueTable->exists(id) ) throw "Undefined identifier";
            
    switch ( yylex() ){
        case ASSIGNMENT:
            assigmnent(id);
            break;
        case SEMICOLON:{
            AbstractValue* vinf = globalValueTable->value(id);
            std::cout << vinf->toString() << std::endl;
        }
            break;
        
        default:
            throw "Unknow operation";
    }
}

void assigmnent(std::string id)
{
    switch ( yylex() ){
        case INT:{
            int32_t num;
            
            if ( !str2int(num, (*globalLexTable)[yylval].text) )
                throw "Error int convertion";
            
            AbstractValue* vinf = globalValueTable->value(id);
            Int32Value* val = dynamic_cast<Int32Value*>(vinf);
            val->setValue(num);
        }       
        break;
        case STRING:{
            AbstractValue* vinf = globalValueTable->value(id);
            StringValue* val = dynamic_cast<StringValue*>(vinf);
            val->setValue((*globalLexTable)[yylval].text);
        }
        break;
        case ID:{
            assign(id, (*globalLexTable)[yylval].text);
        }
        break;
        default:
            throw "Invalid rvalue";
    }
    
    if ( yylex() != SEMICOLON ) throw "; expected";
}

void assign(std::string id1, std::string id2)
{
    if ( !globalValueTable->exists(id1) || !globalValueTable->exists(id2) )
        throw "Undefined identifier";
    
    AbstractValue* vinf_left = globalValueTable->value(id1);
    AbstractValue* vinf_right = globalValueTable->value(id2);
    
    vinf_left->copyData(vinf_right);
}

AbstractValue* expr(bool get)
{
    AbstractValue *result;
    
    result = term(get);
    
    for (;;){
        switch ( curr_tok ){
            case PLUS:
                break;
            case MINUS:
                break;
            default:
                return result;
        }
    }
}

AbstractValue* term(bool get)
{
    AbstractValue *result;
    
    result = prim(get);
    for(;;){
        switch ( curr_tok ){
            case MUL:
                break;
            case DIV:
                break;
            default:
                return result;
        }
                
    }
}

AbstractValue* prim(bool get)
{    
    AbstractValue *result;
    
    if ( get ) curr_tok = yylex();
    
    switch ( curr_tok ){
        case INT:
        {
            int32_t num;
            
            if ( !str2int(num, (*globalLexTable)[yylval].text) )
                throw "Error int convertion";
            
            AbstractType* type = globalTypeTable->prototype("int");
            result = type->create();
            ((Int32Value*)result)->setValue(num);
        }
            break;
        case STRING:
        {
            AbstractType* type = globalTypeTable->prototype("string");
            result = type->create();
            ((StringValue*)result)->setValue((*globalLexTable)[yylval].text);
        }
            break;
        case ID:
        {
            std::string id = (*globalLexTable)[yylval].text;
            if ( !globalValueTable->exists(id) )
                throw "Undefined identifier";
            
            result =  globalValueTable->value(id);
            if (( curr_tok = yylex()) == ASSIGNMENT ) {
                AbstractValue *val = expr(true);
                AbstractMethod* method = result->getMethod("operator=");
                method->setParam(1, result);
                method->setParam(2, val);
                (*method)();
                delete val;
            }
        }
            break;
        case MINUS:
            result = prim(true);
            // call method unary-
            break;
        case LP:
            result = expr(true);
            if ( curr_tok != RP ) throw "Expected ')'";
            curr_tok = yylex();
            break;
        default:
            throw "Primary expected";
    }
    
    return result;
}
