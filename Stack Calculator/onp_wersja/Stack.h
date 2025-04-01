#ifndef  _STACK_H
#define _STACK_H

//definicja typu elementu stosu StackItem: key pNext
typedef struct tagStackItem
{
  char key;
  tagStackItem* pNext;
} StackItem;
StackItem* createStack();
// naglowki publicznych funkcji modulu Stosu
void push( StackItem** pStack, char c );    // wloz na stos
char pop( StackItem** pStack );            // zdejmij i zwroc wartosc szczytowa stosu
char top( StackItem* pStack );            // zwraca wartosc szczytowa
void del( StackItem** pStack );          // usuniecie szczytu ze stosu
int  isEmpty( StackItem* pStack );      // zwraca 1 gdy stos pusty, 0 w przeciwnym przypadku


#endif

