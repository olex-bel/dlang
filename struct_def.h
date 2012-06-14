/* 
 * File:   struct_def.h
 * Author: konung
 *
 * Created on 13 Июнь 2012 г., 23:08
 */

#ifndef STRUCT_DEF_H
#define	STRUCT_DEF_H

enum {
    ID = 1,
    TYPE,
    CLASS,
    LEFT_CBRACE,
    RIGHT_CBRACE,
    SEMICOLON
};

extern int yylval;

#endif	/* STRUCT_DEF_H */

