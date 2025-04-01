#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define _DEBUG_

LISTINFO* create();
void printList( ListItem* pList );

int main()
{
	ListItem* pList = CreateList();//glowa listy, sprawdzic
	if( pList == NULL ) {
		perror( "blad przy kreowaniu listy\n" );
		return 10;
	}
	
	srand( (unsigned)time( 0 ) );
	for( int i = 0; i < 20; i++ ) {
		LISTINFO* pInfo = create();//sprawdzic
		if( pInfo == NULL ) {
			perror( "tworzenie elementu nie powiodlo sie\n" );
			return 11;
		}
		
		pInfo->nKey = rand() % 50;
		pInfo->ptab[0] = i + 1;

		if( i == 8 )
			pInfo->nKey = 2000;
			
		if( !Insert( pList, pInfo ) ) {
			perror( "blad przy dodawaniu elementu do listy\n" );
			freeInf( pInfo );
			return 12;
		}
	}
#ifdef _DEBUG_
	printf( "Pierwotna lista: \n\n" );
	printList( pList );
#endif

#ifdef _DEBUG_
	printf( "\nPosortowana lista: \n\n" );
	SortList( pList, comp );
	printList( pList );
#endif
	//szukanie klucza 2000
	LISTINFO* pFindKey = create();//sprawdzic
	if( pFindKey == NULL ) {
		printf( "blad przy tworzeniu pFindKey\n" );
		return 13;
	}
	pFindKey->nKey = 2000;
	ListItem* pPrev;
	ListItem* pFoundItem = Find( pList, pFindKey, &pPrev, comp );//zwraca wskaznik na element z kluczem 2000, pprev wskazuje na wczesniejszy element, potrzebne do wstawienia klucza 3000 &Prev
	if( pFoundItem == NULL ) {
		printf( "blad przy szukaniu elementu 2000\n" );
	}
	printf( "\n\nZnaleziony element: nr: %d, key: %d\n\n", pFoundItem->pInfo->ptab[0], pFoundItem->pInfo->nKey );
	
	
	//wstawienie 3000
	LISTINFO* pTemp = create();//
	if( pTemp == NULL ) {
		printf( "blad przy tworzeniu pTemp\n" );
		return 14;
	}
	pTemp->nKey = 3000;
	if( !Insert( pPrev, pTemp ) ) {//wstawia za pprev, pprev wskazywal na element przed 2000, teraz na element przed 3000
		perror( "Insert error  1 - main\n" );
		return 15;
	}

#ifdef _DEBUG_
	printf( "\nwstawiamy element z kluczem 3000: \n\n" );
	printList( pList );
#endif
	//usuniecie klucza 2000
	LISTINFO* temp = Remove( pPrev->pNext );//usuwa element nastepny po nastepnym po pprev czyli 2000
	if( temp == NULL ) {
		printf( "blad przy usuwaniu klucza 2000\n" );
		return 25;
	}
	free( temp );//wlasna funkcja

#ifdef _DEBUG_
	printf( "\nusuwamy element z kluczem 2000\n\n" );
	printList( pList );
#endif

	ClearList( pList, freeInf );//"usuniecie" listy
	
	//wstawienie elementow
	LISTINFO* pInf = create();
	if( pInf == NULL ) {
		printf( "blad przy tworzeniu pInf\n" );
		return 16;
	}
	pInf->nKey = 1;
	pInf->ptab[0] = 1;
	if( !Insert( pList, pInf ) ) {
		perror( "insert error 2 - main\n" );
		return 17;
	}

	LISTINFO* pInf_2 = create();
	if( pInf_2 == NULL ) {
		printf( "blad przy tworzeniu pInf_2\n" );
		return 18;
	}
	pInf_2->nKey = 2;
	pInf_2->ptab[0] = 2;
	if( !Insert( pList, pInf_2 ) ) {
		perror( "insert error 3 - main" );
		return 19;
	}

#ifdef _DEBUG_
	printf( "\nnowe elementy: \n\n" );
	printList( pList );
#endif

	RemoveList( &pList, freeInf );

	return 0;
}

void freeInf( const void* itemInf ) {//const void* - dowolny wskaznik, nie zmienia danych
	free( ((LISTINFO*)itemInf)->ptab );//rzutowanie na listinfo*, zwalnia pamiec zaalokowana dla ptab
	free( (LISTINFO*)itemInf );//zwalnia pamiec zaalokowana dla calej struktury
}

int comp( const void* p, const void* q ) {
	if( ((LISTINFO*)p)->nKey < ((LISTINFO*)q)->nKey ) return -1;
	if( ((LISTINFO*)p)->nKey == ((LISTINFO*)q)->nKey ) return 0;
	return 1;
}

void printList(ListItem* pList) {
	if( pList == NULL ) {
		printf( "lista pusta" );
		return;
	}
	ListItem* k = pList;
	while( !IsEmpty( k ) ) {
		k = k->pNext;
		printf( "nr: %d, key: %d\n", k->pInfo->ptab[0], k->pInfo->nKey );
	}
}

LISTINFO* create() {
	LISTINFO* p = (LISTINFO*)calloc( 1, sizeof( LISTINFO ) );
	if( !p ) {
		//printf( "create error - if 1\n" );
		return NULL;
	}
	p->ptab = (int*)calloc( 2, sizeof( int ) );
	if( !(p->ptab) ) {
		//printf( "create error - if 2\n" );
		return NULL;
	}
	return p;
}