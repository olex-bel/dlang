%option yylineno

%{
#include "struct_def.h"
#include "lex_table.h"
#include "type_table.h"
%}

INT     [0-9]+
ID	[a-zA-Z_][a-zA-Z0-9]*
WS	[ \r\n\t]+

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
