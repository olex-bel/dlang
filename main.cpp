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
#include "struct_def.h"
#include "strutil.h"

int yylval;
LexemTable* globalLexTable;
TypeTable* globalTypeTable;

void typeDef();
void assigmnent(std::string id);
void identifier();

int main(int argc, char** argv) {

    int lex;
    
    globalLexTable = new LexemTable();
    globalTypeTable = new TypeTable();
    
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
    ValueInfo::ValueType type = static_cast<ValueInfo::ValueType>(yylval);
    int lex = yylex();
    if ( lex != ID ) throw "Must be identifier";
    if ( !globalTypeTable->add((*globalLexTable)[yylval].text, type) )
        throw "Redefinition of an identifier";
    lex = yylex();
    if ( lex != SEMICOLON ) throw "; expected";
}

void identifier()
{
    std::string id = (*globalLexTable)[yylval].text;
    
    if ( !globalTypeTable->exists(id) ) throw "Undefined identifier";
            
    switch ( yylex() ){
        case ASSIGNMENT:
            assigmnent(id);
            break;
        case SEMICOLON:{
            ValueInfo vinf = globalTypeTable->value(id);
            std::cout << vinf.value->toString() << std::endl;
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
            
            ValueInfo vinf = globalTypeTable->value(id);
            Int32Value* val = dynamic_cast<Int32Value*>(vinf.value);
            val->setValue(num);
        }       
        break;
        case STRING:{
            ValueInfo vinf = globalTypeTable->value(id);
            StringValue* val = dynamic_cast<StringValue*>(vinf.value);
            val->setValue((*globalLexTable)[yylval].text);
        }
        break;
        case ID:{
            
        }
        break;
        default:
            throw "Invalid rvalue";
    }
    
    if ( yylex() != SEMICOLON ) throw "; expected";
}

void assign(std::string id1, std::string id2)
{
    if ( !globalTypeTable->exists(id1) || !globalTypeTable->exists(id2) )
        throw "Undefined identifier";
    
    ValueInfo vinf_left = globalTypeTable->value(id1);
    ValueInfo vinf_right = globalTypeTable->value(id2);
    
    if ( vinf_left.type != vinf_right.type )
        throw "Variable must be the same type";
            
            
}
