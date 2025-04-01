#include "PQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void UpdateDown( PQItem* pPQueue, int l, int p );
void UpdateUp( PQItem* pPQueue, int l, int p );

PQueue* PQCreate( int nSize )
{
	if( nSize <= 0 )
		return NULL;
	PQueue* q = (PQueue*)calloc( 1, sizeof( PQueue ) );
	if( !q )
		return NULL;
	q->pPQueue = (PQItem*)calloc( nSize, sizeof( PQItem ) );
	if( !q->pPQueue ) {
		free( q );
		return NULL;
	}
	q->nPQSize = nSize;
	return q;
}

int PQisEmpty( PQueue* q )
{
	return !q;
}

int PQSize( PQueue* q )//ilosc elementow w kolejce
{
	return (q == NULL) ? POS_ERROR : q->nPQCurrSize;
}

int PQMaxPrior( PQueue* q )//zwraca priorytet pierwszego elementu w kolejce, czyli o najwyzszym priorytecie
{//wyrazenie pytajnikowe
	/*if( !q )//not is empty
		return PRIOR_ERROR;
	return PQgetPrior( q, 0 );*/
	return PQisEmpty( q ) ? PRIOR_ERROR : PQgetPrior( q, 0 ); //q->pPQueue[0].nPrior
}

int PQEnqueue( PQueue* q, int nPrior, PQINFO* pInfo )//wstawia nowy element na koniec, a potem przesuwa go na swoje miejsce
{
	if( !q )
		return 0;
	if( PQSize( q ) == q->nPQSize )
		return 0;
	int nSize = PQSize( q );//aktualny rozmiar kolejki
	q->pPQueue[nSize].pInfo = pInfo;//przypisjue wskaźnik do informacji do odpowiedniego pola w kolejce
	q->pPQueue[nSize].nPrior = nPrior;//przypisuje priorytet do odpowiedniego pola w kolejce
	
	if( nSize > 0 )
		UpdateUp( q->pPQueue, 0, nSize );//aktualizuje kolejność elementów w kolejce, ustawiajac nowo dodany element na swoje miejsce
	q->nPQCurrSize++;//zwieksz rozmiar kolejki
	return 1;
}

PQINFO* PQDequeue( PQueue* q )//zdejmuje element o najwyzszym priorytecie, wstawia na jego miejsce ostatni element, ktory nastepnie jest przesuwany na swoje miejsce
{
	if( PQisEmpty( q ) )
		return NULL;
	PQINFO* pInfo = q->pPQueue[0].pInfo;//pobiera wskaźnik do informacji o elemencie o najwyższym priorytecie
	
	int nSize = --q->nPQCurrSize;//zmniejszamy rozmiar o jeden bo ususwamy element
	if( nSize > 0 )
		q->pPQueue[0] = q->pPQueue[nSize];//ostatni element drzewa wstawiamy na pierwsze miejsce
	memset( q->pPQueue + nSize, 0, sizeof( PQItem ) );//zerujemy ostatni element
	if( nSize > 1 )
		UpdateDown( q->pPQueue, 0, nSize - 1 );//aktualizuje drzewo, od góry, nsize-1 bo indeks od 0
	return pInfo;//zwraca info elementu o najwyzszym priorytecie
}

void PQClear( PQueue* q, void( _cdecl* freeFunc )(const void*) )//czysci kolejke, zwalnia pamiec
{//while dopoki nie pusta - dequeue
	if( !q || !freeFunc ) { //komunikat - dwa bledy
		printf( "brak kolejki lub funkcji\n" );
		return;
	}
	while( PQisEmpty( q ) )
		freeFunc( PQDequeue( q ) );
	/*for( int i = 0; i < q->nPQCurrSize; i++ ) {
		PQINFO* pInfo = q->pPQueue[i].pInfo;
		if( pInfo ) {
			freeFunc( pInfo ); //zwalnia PQINFO i-tego elementu kolejki
		}
		q->pPQueue[i].pInfo = NULL;//
	}
	q->nPQCurrSize = 0;*/
}//elementy w kolejce maja swoj priorytet ale ich wskazniki na PQINFO sa wynullowane

void PQRelease( PQueue** q, void( _cdecl* freeFunc )(const void*) )//usuwa kolejke
{
	if( !q || !*q ) { //komuniiakat
		printf( "brak kolejki\n" );
		return;
	}
	PQClear( *q, freeFunc );//czysci kolejk
	free( (*q)->pPQueue );//zwalnia pamiec zaalokowana dla tablicy elememtow kolejki
	free( *q );//zwalnia pamiec zalokowana dla struktury kolejki
	*q = NULL;
}

void PQPrint( PQueue* q, int index, void( _cdecl* printFunc )(const void*) )//drukuje w kolejnosci preorder
{
	if( !q || index < 0 || printFunc == NULL ) { //komunikat opisac 3 bledy
		printf( "\nbrak kolejki, za maly indeks lub brak funkcji\n" );
		return;
	}
	if( index >= q->nPQCurrSize )
		return;

	printf( "[%d] ", index ); //drukujr pozycjr w kolejce w kwadratowych nawiasach
	printf( "(%d) ", q->pPQueue[index].nPrior ); //drukujr priorytet w okrąglych nawiasach
	printFunc( q->pPQueue[index].pInfo );//drukuje przechowywane informacje, nkey i ptab[0]

	//int left = 2 * index + 1;//lewe dziecko
	//int right = 2 * index + 2;//prawe dziecko

	PQPrint( q, 2 * index + 1, printFunc );
	PQPrint( q, 2 * index + 2, printFunc ); 
}

int PQSetPrior( PQueue* q, int nPrior, PQINFO* pInfo, int( _cdecl* compareFunc )(const void*, const void*) )
{
	return PQsetPrior( q, nPrior, PQFind( q, pInfo, compareFunc ) );//ustawia priorytet elementu o kluczu danym w pInfo na nprior, zwraca poprzedni priorytet
}

int PQsetPrior( PQueue* q, int nPrior, int nIndex )//ustawia priorytet nindex-elementu na nprior
{//sprawdzic czy kolejka pusta
	if( !q || nIndex < 0 || nIndex >= q->nPQCurrSize ) {
		printf( "brak kolejki lub niepoprawny indeks\n" );
		return PRIOR_ERROR;
	}

	//int oldPrior = q->pPQueue[nIndex].nPrior; //aktualny priorytet, getprior
		int oldPrior = PQgetPrior( q, nIndex );
		if( oldPrior == POS_ERROR )//czy oldprior poserror, jesli tak zracamy prior error
			return PRIOR_ERROR;
	q->pPQueue[nIndex].nPrior = nPrior;//nowy priorytet
	if( oldPrior > nPrior )
		UpdateDown( q->pPQueue, nIndex, PQSize( q ) - 1 );
	if( oldPrior < nPrior )
		UpdateUp( q->pPQueue, 0, nIndex );
	//updaty
	return oldPrior;
}

int PQGetPrior( PQueue* q, PQINFO* pInfo, int( _cdecl* compareFunc )(const void*, const void*) )//zwraca priorytet szukanego elementu
{
	return PQgetPrior( q, PQFind( q, pInfo, compareFunc ) );
}

int PQgetPrior( PQueue* q, int nIndex )//zwraca priorytet n-tego elementu kolejki
{
	if( !q )
		return PRIOR_ERROR;
	if( nIndex >= q->nPQSize || nIndex < 0 )
		return POS_ERROR;
	return q->pPQueue[nIndex].nPrior;
}

int PQFind( PQueue* q, PQINFO* pInfo, int( _cdecl* compareFunc )(const void*, const void*) )//zwraca numer w kolejce elementu o danym kluczu
{
	if( !q )
		return PRIOR_ERROR;
	if( !compareFunc )
		return POS_ERROR;
	for( int i = 0; i < PQSize( q ); i++ ) {
		if( compareFunc( pInfo, q->pPQueue[i].pInfo ) == 0 )
			return i;//znaleziono informacje, zwraca indeks
	}
	return POS_ERROR;
}

void UpdateDown( PQItem* pItem, int l, int p )
{
	if( l >= p )
		return;
	int i = l;
	int j = 2 * i + 1;//wzor na indeks lewego dziecka
	PQItem pTemp = pItem[i];
	while( j <= p )
	{
		if( j < p && pItem[j].nPrior < pItem[j + 1].nPrior )//>
			j++;//jezeli prawe ziecko jest wieksze to wskazujemy na prawe
		if( pTemp.nPrior >= pItem[j].nPrior )//<
			break;
		pItem[i] = pItem[j];
		i = j;
		j = 2 * i + 1;
	}
	pItem[i] = pTemp;
}

void UpdateUp( PQItem* pItem, int l, int p )
{
	if( l >= p )
		return;
	int i = p;
	int j = (i - 1) / 2;//indeks rodzica
	PQItem pTemp = pItem[i];
	while( j >= l && pItem[j].nPrior < pTemp.nPrior )//priorytet rodzica jest mniejszy,
	{
		pItem[i] = pItem[j];//wstawiamy rodzica w miejsce dziecka
		i = j;
		j = (i + 1) / 2 - 1;//wzor na indeks rodzica, dla i = 0, j = -1, liczy tak samo jak ten wyzej za wyjatkiem i=0

	}
	pItem[i] = pTemp;
}
