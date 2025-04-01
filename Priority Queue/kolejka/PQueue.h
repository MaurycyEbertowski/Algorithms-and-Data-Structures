#pragma once
#include "global.h"

#define PRIOR_ERROR INT_MIN //–2147483648
#define POS_ERROR -1

typedef struct
{
  PQINFO* pInfo;       // Ptr to user info  
  int nPrior;      // prior value (int) for the user info  
} PQItem;         // type of the queue item

typedef struct
{
  PQItem* pPQueue;     // kolejka realizowana w postaci stogu  (dynamiczna tablica)
  int nPQSize;      // rozmiar calkowity kolejki priorytetowej
  int nPQCurrSize;  // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce) 
} PQueue;

PQueue* PQCreate( int nSize );//kreuje kolejke i zwraca wskaznik do niej lub null

int PQisEmpty( PQueue* q );//0-niepusta, 1-pusta

int PQSize( PQueue* q );//ilosc elementow w kolejce

int PQMaxPrior( PQueue* q );//najwiekszy priorytet w kolejce

int PQEnqueue( PQueue* q, int nPrior, PQINFO* pInfo );//wstawia informacje o danym priorytecie, zwraca 0 gdy niepowodzenie lub 1 gdy powowdzenie

PQINFO* PQDequeue( PQueue* q );//informacje o najwiekszym priorytecie

void PQClear( PQueue* q, void( _cdecl* FreeInfo )(const void*) );//czysci cala kolejke zwlaniajac pamiec

void PQRelease( PQueue** q, void( _cdecl* FreeInfo )(const void*) );//usuwa kolejke

void PQPrint( PQueue* q, int nPos, void( _cdecl* PrintInfo )(const void*) );//drukuje w kolejnosci preorder od danej pozycji

int PQSetPrior( PQueue* q, int nPrior, PQINFO* pInfo, int( _cdecl* compare )(const void*, const void*) );//ustawia nowy priorytet dla danej informacji

int PQsetPrior( PQueue* q, int nPrior, int nIndex );

int PQGetPrior( PQueue* q, PQINFO* pInfo, int( _cdecl* compare )(const void*, const void*) );//zwraca priorytet informacji

int PQgetPrior( PQueue* q, int nIndex );

int PQFind( PQueue* q, PQINFO* pInfo, int( _cdecl* compareFunc )(const void*, const void*) );//zwraca indeks szukanej informacji
