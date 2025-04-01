#pragma once

#include "global.h"

typedef struct tagListItem {
	LISTINFO* pInfo;
	tagListItem* pNext;
} ListItem;

ListItem* CreateList();
ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl* cmpItems )(const void*, const void*) );

LISTINFO* Remove( ListItem* pAfter );
LISTINFO* Front( ListItem* pList );

int Insert( ListItem* pAfter, LISTINFO* pInfo );
int IsEmpty( ListItem* pList );
void ClearList( ListItem* pList, void( __cdecl* freeMem )(const void*) );
void RemoveList( ListItem** pList, void( __cdecl* freeMem )(const void*) );
void SortList( ListItem* pList, int( __cdecl* cmpItems )(const void*, const void*) );
