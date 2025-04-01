#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

ListItem* CreateList() {
	return ( ListItem* )calloc( 1, sizeof( ListItem ) );
}

int Insert( ListItem* pAfter, LISTINFO* pInfo ) {//wstawia na poczatek listy, za empty, empty wskazuje teraz na nowo utworzony element zawierajacy pinfo
	if( pAfter ) {
		ListItem* p = (ListItem*)calloc( 1, sizeof( ListItem ) );
		if( !p ) {
			//perror( "Insert error\n" );
			return 0;
		}
		p->pInfo = pInfo;
		p->pNext = pAfter->pNext;
		pAfter->pNext = p;
		return 1;
	}
	return 0;
}

int IsEmpty( ListItem* pList ) {
	return !pList || !(pList->pNext);
}

LISTINFO* Remove( ListItem* pAfter ) {//usuwa z listy nastepny element po pafter, zwraca listinfo tego elementu,dla pList usunie pierwsze element po glowie, LIFO
	if( IsEmpty( pAfter ) ) {
		//perror( "Remove error - IsEmpty\n" );
		return NULL;
	}
	ListItem* k = pAfter->pNext;
	LISTINFO* r = k->pInfo;
	pAfter->pNext = k->pNext;//teraz wskazuje na kolejny element listy, po tym usunietym
	free( k );
	return r;
}

LISTINFO* Front( ListItem* pList ) {//zwraca wskaznik na listinfo pierwszego elementu w kolejce, po empty
	return( IsEmpty( pList )) ? NULL : pList->pNext->pInfo;
}

void ClearList( ListItem* pList, void( __cdecl* freeMem )(const void*) ) {//ususwa elementy listitem i listinfo, empty zostaje
	if( pList && freeMem ) {
		while( !IsEmpty( pList ) )
			freeMem( Remove( pList ) );
	}
	else
		perror( "\nbledny adres funkcji lub brak listy\n" );
}

void RemoveList( ListItem** pList, void( __cdecl* freeMem )(const void*) ) { //usuwa razem z empty, wskaznik na glowe == null
	if( !pList || !*pList ) {
		printf( "brak listy\n" );
		return;
	}
		ClearList( *pList, freeMem );
		free( *pList );//usuniecie glowy
		*pList = NULL;
}

void SortList( ListItem* pList, int( __cdecl* compare )(const void*, const void*) ) {//selection sort

	if( !compare ) {
		perror( "SortList error - brak funkcji\n" );
		return;
	}

	ListItem* pFirst = pList;//dziala bez pFirst

	while( !IsEmpty( pFirst ) ) {
		ListItem* pMin = pFirst;
		ListItem* pCurr = pMin->pNext;//pmin, pcurr wskazuja wczesniejsze elementy od min, curr

		while( !IsEmpty( pCurr ) ) {
			if( compare( (pCurr->pNext->pInfo), (pMin->pNext->pInfo) ) == -1 )
				pMin = pCurr;//szukamy najmniejszego klucza
			pCurr = pCurr->pNext;
		}

		if( pMin != pFirst ) {
			pCurr = pMin->pNext->pNext;//pcurr wskazuje na nastepny element po najmniejszym
			pMin->pNext->pNext = pFirst->pNext;//najmniejszy element wskazuje teraz na drugi element
			pFirst->pNext = pMin->pNext;//poprzedni najmniejszy element wskazuje na kolejny najmniejszy, ten ktory teraz znalezlismy
			pMin->pNext = pCurr;//element ktory wskazywal na najmniejszy wskazuje na nastepny, za nim
		}
		pFirst = pFirst->pNext;
	}
}

ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl* compareee )(const void*, const void*) ) {//dwie gwiazdki bo zmieniamy pprev a nie lokalna kopie, szuka elementu o danym pinfo
	if( !compareee ) {
		printf( "brak funkcji find\n" );
		return *pPrev = NULL;
	}
	*pPrev = pList;
	while( !IsEmpty( *pPrev ) ) {
		if( compareee( (*pPrev)->pNext->pInfo, pInfo ) == 0 )
			return (*pPrev)->pNext;//zwraca wskaznik na szukany element, pprev wskazuje na element wczesniejszy, potrzebne do wstawienia elementu z kluczem 3000
		*pPrev = (*pPrev)->pNext;
	}
	return *pPrev = NULL;
}
	/*ListItem* p = pList;
	while( !IsEmpty( p ) ) {
		if( compareee( (const void*)(p->pNext->pInfo), pInfo ) == 0 ) {//porownoje klucze
			*pPrev = p;//*pPrev
			return p->pNext;//zwraca wskaznik na znaleziony element, pprev wskazuje na element jeden przed tym
		}
		p = p->pNext;
	}
	return *pPrev = NULL;
}*/ //bez p