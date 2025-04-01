#include "Util.h"
#include <stdio.h>
#include <math.h>

#define MIN_DBL 1e-200

int prior( char c )
{
  switch (c)
  {
  case '+':
  case '-': return 1;
  case '*':
  case '/': return 2;
  case '^': return 3;
  }
  return 0;
}

char getOper() {
  skipSpace();
  return getchar();
}

double getNum() {
  char c;
  double res = 0;
  skipSpace();
  while (isDigit( c = getchar() )) {
    res = res * 10 + (c - '0');
  }

  if (c == '.') {
    double x = 0.1;
    while (isDigit( c = getchar() )) {
      res += x * (c - '0');
      x *= 0.1;
    }
  }
  ungetc( c, stdin );
  return res;
}

int isOper( char c ) {
  switch (c) {
  case '+':
  case '-':
  case '*':
  case '/':
  case '^': return 1;
  default: return 0;
  }
}
void skipSpace() {
  char c;
  while ((c = getchar()) == ' '|| c == '\t');
  ungetc( c, stdin );
}
double Eval( char oper, double arg1, double arg2 ) {
  switch (oper)
  {
  case '+': return arg1 + arg2;
  case '-': return arg1 - arg2;
  case '*': return arg1 * arg2;
  case '/': if( arg2 < MIN_DBL ) {
    perror( "dzielenie przez 0\n" );
    return 0;
  }
            return arg1 / arg2;
  case '^':return pow( arg1, arg2 );//tylko gdy arg2 jest double
  default: return 0;
  }
}
int isDigit( char c ) {
  return (c >= '0' && c <= '9');
}