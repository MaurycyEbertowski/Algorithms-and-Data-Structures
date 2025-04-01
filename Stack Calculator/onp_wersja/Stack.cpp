#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "Stack.h"
using namespace std;

StackItem* createStack() {
  return NULL;
}

void push( StackItem** pStack, char c )
{
  StackItem* p = (StackItem*)malloc( sizeof( StackItem ) );  
  if (!p) { //sprawdzic czy sie powiodlo
    perror( "push error: Allocation error StackItem*" );
    return;
  }
  memset( p, 0, sizeof( StackItem ) );    //wyzerowanie kazdego bajtu pamieci
  p->key = c;    //wstawienie informacji i dowiazanie
  p->pNext = *pStack;
  *pStack = p;

}
char pop( StackItem** pStack )
{
  if (!isEmpty( *pStack ))
  {
    char c = top( *pStack );
    del( pStack );
    return c;
  }
  perror( "pop error: Stack underflow1!\n" );
  return 0;
}
char top( StackItem* pStack )
{
  if (!isEmpty( pStack ))
    return pStack->key;//z pierwszego elementu ktory jest wskazywany przez pStack zwraca key
   //perror( "top error: stack underflow\n" ); //wyrzuca ten error
  return 0;
}
void del( StackItem** pStack )
{
  if (!isEmpty( *pStack ))
  {//zwolnienie pamieci na pierwszy element stosu
    StackItem* p = *pStack;
    *pStack = (*pStack)->pNext;
    free( p );

    return;
  }
  perror( " del error: Stack underflow!\n" );
}
int  isEmpty( StackItem* pStack )//zwraca true jesli stos pusty, else false
{
  return !pStack;
}
