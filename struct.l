%option yylineno

%{
#include "struct_def.h"
#include "lex_table.h"
%}

ID	[a-zA-Z_][a-zA-Z0-9]*
WS	[ \r\n\t]+

%%

{WS}		{ /* White space, nothing to do */ }
"class"         {   return CLASS; }
"int"           {   return INT; }
"string"        {   return STRING; }
{ID}		{
			yylval = globalLexTable->addId(yylineno, yytext); 
			return ID; 
		}
"{"             {   return LEFT_CBRACE; }
"}"             {   return RIGHT_CBRACE; }
";"             {   return SEMICOLON; }
"//".*		{ /* One line comment, nothing to do */ }

%%

int yywrap(){
	return 1;
}
