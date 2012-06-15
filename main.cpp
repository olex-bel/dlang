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


int yylval;
LexemTable* globalLexTable;

int main(int argc, char** argv) {

    int lex;
    
    globalLexTable = new LexemTable();
    
    while ( (lex = yylex()) != 0 ){
        std::cout << lex << std::endl;
    }
    
    delete globalLexTable;
    
    return 0;
}

