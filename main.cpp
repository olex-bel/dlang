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
#include <boost/shared_ptr.hpp>

int yylval;
LexemTable* globalLexTable;
TypeTable* globalTypeTable;
ValueTable* globalValueTable;
int curr_tok;

void def_var();
void print_var();
boost::shared_ptr<AbstractValue> expr(bool get);
boost::shared_ptr<AbstractValue> term(bool get);
boost::shared_ptr<AbstractValue> prim(bool get);

int main(int argc, char** argv) {
    
    globalLexTable = new LexemTable();
    globalTypeTable = new TypeTable();
    globalValueTable = new ValueTable();
    
    try{
        while ( (curr_tok = yylex()) != 0 ){
            switch ( curr_tok ){
                case TYPE:
                    def_var();
                    break;
                case ID:
                    expr(false);
                    break;
                case PRINT:                
                    print_var();
                    break;
            }
                    
            if ( curr_tok != SEMICOLON ){
                curr_tok = yylex();
                if ( curr_tok != SEMICOLON ){
                        std::cout << curr_tok << std::endl;
                        throw "; expected";
                }
            }      
        }
    }catch(const char* s){
        std::cout << s << std::endl;
    }
        
    delete globalLexTable;
    delete globalTypeTable;
    
    return 0;
}

void print_var()
{
    curr_tok = yylex();
    if ( curr_tok != ID ) throw "Must be identifier";
    
    AbstractValue *val = globalValueTable->value((*globalLexTable)[yylval].text);
    if ( val )
        std::cout << val->toString() << std::endl;
}

void def_var()
{
    AbstractType* type = globalTypeTable->prototype(yytext);
    
    if ( !type )
        throw "Unknow type";
    
    curr_tok = yylex();
    if ( curr_tok != ID ) throw "Must be identifier";
    
    if ( !globalValueTable->add((*globalLexTable)[yylval].text, type) )
        throw "Redefinition of an identifier";
   
}

boost::shared_ptr<AbstractValue> expr(bool get)
{
    boost::shared_ptr<AbstractValue> result;
    
    result = term(get);
    
    for (;;){
        switch ( curr_tok ){
            case PLUS:
            {
                AbstractMethod* method = result->getMethod("operator+");
                boost::shared_ptr<AbstractValue> right = term(true);
                method->setParam(1, result.get());
                method->setParam(2, right.get());
                result = (*method)();
            }
                break;
            case MINUS:
            {
                AbstractMethod* method = result->getMethod("operator-");
                boost::shared_ptr<AbstractValue> right = term(true);
                method->setParam(1, result.get());
                method->setParam(2, right.get());
                result = (*method)();
            }
                break;
            default:
                return result;
        }
    }
}

boost::shared_ptr<AbstractValue> term(bool get)
{
    boost::shared_ptr<AbstractValue> result;
    
    result = prim(get);
    for(;;){
        switch ( curr_tok ){
            case MUL:
            {
                AbstractMethod* method = result->getMethod("operator*");
                boost::shared_ptr<AbstractValue> right = prim(true);
                method->setParam(1, result.get());
                method->setParam(2, right.get());
                result = (*method)();
            }
                break;
            case DIV:
            {
                AbstractMethod* method = result->getMethod("operator/");
                boost::shared_ptr<AbstractValue> right = prim(true);
                method->setParam(1, result.get());
                method->setParam(2, right.get());
                result = (*method)();
            }
                break;
            default:
                return result;
        }
                
    }
}

boost::shared_ptr<AbstractValue> prim(bool get)
{    
    boost::shared_ptr<AbstractValue> result;
    
    if ( get ) curr_tok = yylex();
    
    switch ( curr_tok ){
        case INT:
        {
            int32_t num;
            
            if ( !str2int(num, (*globalLexTable)[yylval].text) )
                throw "Error int convertion";
            
            AbstractType* type = globalTypeTable->prototype("int");
            result = boost::shared_ptr<AbstractValue>(type->create());
            ((Int32Value*)result.get())->setValue(num);
            curr_tok = yylex();
        }
            break;
        case STRING:
        {
            AbstractType* type = globalTypeTable->prototype("string");
            result = boost::shared_ptr<AbstractValue>(type->create());
            ((StringValue*)result.get())->setValue((*globalLexTable)[yylval].text);
        }
            break;
        case ID:
        {
            std::string id = (*globalLexTable)[yylval].text;
            if ( !globalValueTable->exists(id) )
                throw "Undefined identifier";
            
            AbstractValue* value = globalValueTable->value(id);
            
            if (( curr_tok = yylex()) == ASSIGNMENT ) {
                boost::shared_ptr<AbstractValue> val = expr(true);
                AbstractMethod* method = value->getMethod("operator=");
                method->setParam(1, value);
                method->setParam(2, val.get());
                result = (*method)();
            } else
                result = value->clone();
        }
            break;
        case MINUS:
        {
            result = prim(true);
            AbstractMethod* method = result.get()->getMethod("operator-u");
            method->setParam(1, result.get());
            result = (*method)();
        }
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
