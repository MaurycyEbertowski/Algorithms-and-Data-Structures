#ifndef _DSTACK_H
#define _DSTACK_H

//definicja typu elementu stosu StackItem: key pNext
typedef struct tagDStackItem{
  double key;
  tagDStackItem* pNext;
} DStackItem;

DStackItem* createDStack();
void dpush( DStackItem** pDHead, double n );   // wloz na stos
double dpop( DStackItem** pDHead );            // zdejmij i zwroc wartosc szczytowa stosu
double dtop( DStackItem* pDHead );            // zwraca wartosc szczytowa
void ddel( DStackItem** pDHead );            // usuniecie szczytu ze stosu
int  disEmpty( DStackItem* pDHead );        // zwracaa 1 gdy stos pusty, 0 w przeciwnym przypadku

#endif
