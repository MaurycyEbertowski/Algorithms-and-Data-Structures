#pragma once

typedef struct {
	int nKey;
	int* ptab; //tab 2 elem
} ListInfo;

#define LISTINFO ListInfo

void freeInf( const void* );
int comp( const void*, const void* );
