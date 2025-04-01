#ifndef _UTIL_H
#define _UTIL_H

int prior( char c );
char getOper();
double getNum();
void skipSpace();
int isOper( char c );
double Eval( char oper, double arg1, double arg2 );
int isDigit( char c );

#endif