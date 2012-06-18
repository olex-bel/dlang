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

void typeDef();
void assigmnent(std::string id);
void identifier();
void assign(std::string id1, std::string id2);

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
