%option yylineno

%{
#include "struct_def.h"
#include "lex_table.h"
#include "type_table.h"
%}

DIGIT   [0-9]
INT     [0-9]+
ID	[a-zA-Z_][a-zA-Z0-9]*
WS	[ \r\n\t]+
EXP     [Ee][\+\-]?{DIGIT}+
DOUBLE  {DIGIT}+(("."{DIGIT}+({EXP})?)|{EXP})

%%

{WS}		{ /* White space, nothing to do */ }
"class"         {   return CLASS; }
"int"           {   
                    yylval = VINT32;
                    return TYPE; 
                }
"string"        {   
                    yylval = VSTRING;
                    return TYPE; 
                }
"float"        {
                    yylval = VDOUBLE;
                    return TYPE; 
                }
{DOUBLE}        {
                    yylval = globalLexTable->addNumber(yylineno, yytext); 
                    return DOUBLE;
                }
{ID}		{
                    yylval = globalLexTable->addId(yylineno, yytext); 
                    return ID; 
		}
{INT}           {   
                    yylval = globalLexTable->addNumber(yylineno, yytext); 
                    return INT;
                }
"!"             {   return PRINT;   }
"{"             {   return LEFT_CBRACE; }
"}"             {   return RIGHT_CBRACE; }
";"             {   return SEMICOLON; }
"="             {   return ASSIGNMENT; }
"-"             {   return MINUS; }
"+"             {   return PLUS; }
"*"             {   return MUL; }
"/"             {   return DIV; }
"("             {   return LP; }
")"             {   return RP; }
"'".*"'"        {   
                        yylval = globalLexTable->addString(yylineno, yytext); 
                        return STRING; 
                }
"//".*		{ /* One line comment, nothing to do */ }

%%

int yywrap(){
	return 1;
}
