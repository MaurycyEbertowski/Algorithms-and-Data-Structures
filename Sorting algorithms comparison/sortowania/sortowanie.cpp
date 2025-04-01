#include "sort.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLINE 10
#define MAXTAB 25000
#define _DEBUG_

int createTab( int** pTab, int nSize );
void copyTab( int* pDest, int* pSource, int nSize );
void initTab( int* pTab, int nSize );
void printTab( int* pTab, int nSize );

typedef void (*sortFunc)(int*, int);

int main( int argc, char* argv[] ) {
  if( argc != 2 ) {
    printf( "Usage %s <tab_size>\n", argv[0] );
    return -1;
  }

  int nSize = atoi( argv[1] );
  sortFunc SortTab[] = { BubbleSort, InsertionSort, SelectionSort, MixedSort, HalfInsertSort, HeapSort, QuickSort };
  const char* names[] = {"BubbleSort", "InsertionSort", "SelectionSort", "MixedSort", "HalfInsertionSort", "HeapSort", "QuickSort"};

  int* pTab = NULL;
  if( !createTab( &pTab, nSize )) {
    perror( "createTab error" );
    return -2;
  }

  initTab( pTab, nSize );

  int* sortTab = NULL;
  if( !createTab( &sortTab, nSize )) {
    perror( "createTab error" );
    return -3;
  }

  printf( "Sorting times in seconds for 25000 elements:\n(wait for it)\n" );

  int licznik = sizeof( SortTab ) / sizeof( sortFunc );

  for( int i = 0; i < licznik; i++ ) {
    copyTab( sortTab, pTab, nSize );
    clock_t start = clock();
    SortTab[i]( sortTab, nSize );
    printf( "\n %s: \n %f\n", names[i], (double)(clock() - start) / CLOCKS_PER_SEC);

  }

  free( sortTab );
  free( pTab );

  return 0;
}

int createTab( int** pTab, int nSize ) {
  *pTab = (int*)malloc( nSize * sizeof( int ) );
  if( !*pTab )
    return 0;
  memset( *pTab, 0, nSize * sizeof( int ) );
  return 1;
}
void copyTab( int* pDest, int* pSource, int nSize ) {
  memcpy( pDest, pSource, nSize * sizeof( int ) );
}
void initTab( int* pTab, int nSize ) {
  srand( (unsigned)time( NULL ) );
  for( int i = 0; i < nSize; i++ ) {
    pTab[i] = rand() % 100;
  }
}
void printTab( int* pTab, int nSize ) {
  for( int i = 0; i < nSize; i++ ) {
    printf( "%d ", pTab[i] );
    if( (i + 1) % MAXLINE == 0 ) {
      printf( "\n" );
    }
  }
}