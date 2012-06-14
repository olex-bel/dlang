/*
 * lex_table.h
 *
 *  Created on: 08.06.2012
 *      Author: BelyaevAN
 */

#ifndef LEX_TABLE_H_
#define LEX_TABLE_H_

#include <string>
#include <vector>

struct Lexeme{
	enum LexType {NUMBER, ID};

	int lineno;
	LexType type;
	std::string text;
};

class LexemTable{

	enum { LEX_NUM = 200 };

	std::vector<Lexeme> table;
	int add(int lineno, char* text, Lexeme::LexType type);

public:
	LexemTable();
	int addNumber(int lineno, char* text);
	int addId(int lineno, char* text);
	Lexeme operator[](size_t indx) const;
};

extern LexemTable* globalLexTable;

#endif /* LEX_TABLE_H_ */
