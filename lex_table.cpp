/*
 * lex_table.cpp
 *
 *  Created on: 08.06.2012
 *      Author: BelyaevAN
 */

#include "lex_table.h"

LexemTable::LexemTable()
{
	table.reserve(LEX_NUM);
}

Lexeme LexemTable::operator [](size_t indx) const
{
	return table[indx];
}

int LexemTable::addNumber(int lineno, char* text)
{
	return add(lineno, text, Lexeme::NUMBER);
}

int LexemTable::addId(int lineno, char* text)
{
	return add(lineno, text, Lexeme::ID);
}

int LexemTable::addString(int lineno, char* text)
{
    std::string str = text;
    
    return add(lineno, str.substr(1, str.size() - 2), Lexeme::STRING);
}

int LexemTable::add(int lineno, const std::string&  text, Lexeme::LexType type)
{
	Lexeme lex;

	lex.text = text;
	lex.type = type;
	lex.lineno = lineno;

	table.push_back(lex);

	return table.size() - 1;
}

