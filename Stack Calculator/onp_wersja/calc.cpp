#include <iostream>
#include <stdio.h>
#include "Stack.h"
#include "Util.h"
#include "DStack.h"
#include <math.h>

using namespace std;

double ONP();

int main()
{
  printf( "Wpisz dzialanie: " );
  printf( "wartosc dzialania = %lf\n", ONP() );

  return 0;
}

double ONP() {

  DStackItem* pDStack = createDStack();//liczby
  StackItem* pCStack = createStack();//operatory
  char c;


  dpush( &pDStack, getNum() );

  while (isOper( c = getOper() ))
  {

    while( prior( c ) <= prior( top( pCStack ) )) {
      double x = dpop( &pDStack );//zdejmujemy szczytowy element stosu aby w kolejnej linii wykonac dzialanie
      dpush( &pDStack, Eval( pop( &pCStack ), dpop( &pDStack ), x ) );//wykonanie dzialania i wrzucenie wyniku na stos
    }
    push( &pCStack, c );
    dpush( &pDStack, getNum() );
  }

  while (!isEmpty( pCStack )) {//jesli dzialania sa w kolejnosci waznosci
    double x = dpop( &pDStack );
    dpush( &pDStack, Eval( pop( &pCStack ), dpop( &pDStack ), x ) );//wykonanie dzialania
  }
  return dpop( &pDStack );//zwraca szczytowy element czyli wynik
}

