#include <iostream>
#include <memory.h>
#include <stdio.h>
#include "DStack.h"
using namespace std;

DStackItem* createDStack() {
  return NULL;
}

void dpush( DStackItem** pDHead, double n )
{
  DStackItem* p = (DStackItem*)malloc( sizeof( DStackItem ) );
  if (!p) //sprawdzic czy sie powiodlo
  {
    perror("dpush error: DStack overflow!\n");
    return;
  }
  memset( p, 0, sizeof( DStackItem ) );    //wyzerowanie kazdego bajtu pamieci
  p->key = n;    //wstawienie informacji i dowiazanie
  p->pNext = *pDHead;
  *pDHead = p;
}

double dpop( DStackItem** pDHead )
{
  if (!disEmpty( *pDHead )) {
    double n = dtop( *pDHead );
    ddel( pDHead );
    return n;
  }

  perror("dpop error: DStack underflow!\n");
  return 0;
}

double dtop( DStackItem* pDHead )
{
  if (!disEmpty( pDHead ))
    return pDHead->key;
  perror( "dtop error: stck underflow\n" );
  return 0;
}

void ddel( DStackItem** pDHead )
{
  if (disEmpty( *pDHead )) {
    perror("ddel error: DStack underflow!\n");
    return;
  }
  DStackItem* p = *pDHead;   //nowy wskaznik pod ktorego podstawie wczyt mojego stosu
  *pDHead = p->pNext;   //przewiaze na kolejny element listy nawet jak nic nie ma to bedzue NULL
  free( p );
}

int  disEmpty( DStackItem* pDHead )
{
  return !pDHead;
}