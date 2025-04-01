#include "sort.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void quick( int* tab, int l, int p );
void update( int* ptab, int l, int p );

void SelectionSort( int* pTab, int nSize ) {
  for( int i = 0; i < nSize; i++ ) {
    int min = pTab[i];
    int x = i;
    for( int j = i + 1; j < nSize; j++ ) {
      if( pTab[j] < min ) {
        min = pTab[j];
        x = j;
      }
    }
    pTab[x] = pTab[i];
    pTab[i] = min;
  }
}

void InsertionSort( int* pTab, int nSize ) {
  int i, key, j;
  for( i = 1; i < nSize; i++ )
  {
    key = pTab[i];
    j = i - 1;
    while( j >= 0 && pTab[j] > key )
    {
      pTab[j + 1] = pTab[j--];
    }
    pTab[j + 1] = key;
  }
}
void BubbleSort( int* pTab, int nSize ) {

  for( int i = 0; i < nSize - 1; i++ )
    for( int j = 0; j < nSize - i - 1; j++ )
      if( pTab[j] > pTab[j + 1] ) {
        int temp = pTab[j];
        pTab[j] = pTab[j + 1];
        pTab[j + 1] = temp;
      }
}
void MixedSort( int* pTab, int n ) {
  int k = n;
  int l = 1;
  int p = n - 1;
  do {
    for( int j = p; j >= l; j-- ) {
      if( pTab[j - 1] > pTab[j] ) {
        int temp = pTab[j - 1];
        pTab[j - 1] = pTab[j];
        pTab[j] = temp;
        k = j;
      }
    }
    l = k + 1;
    for( int j = l; j <= p; j++ ) {
      if( pTab[j - 1] > pTab[j] ) {
        int temp = pTab[j - 1];
        pTab[j - 1] = pTab[j];
        pTab[j] = temp;
        k = j;
      }
    }
    p = k - 1;
  } while( l <= p );
}
void HalfInsertSort( int* pTab, int n ) {
  for( int i = 1; i < n - 1; i++ ) {
    int temp = pTab[i];
    int p = i - 1;
    int j = 0;
    while( j <= p ) {
      int m = (j + p) / 2;
      if( temp < pTab[m] )
        p = m - 1;
      else j = m + 1;
    }

    for( int k = i - 1; k >= j; k-- )
      pTab[k + 1] = pTab[k];
    pTab[j] = temp;
  }
}
void HeapSort(int* tab, int n) {
  int p = n - 1;
  for( int i = n / 2; i >= 0; i-- ) update( tab, i, p );
  for( ; p > 0; p-- ) {  //!!!! for
    int temp = tab[0];
    tab[0] = tab[p];
    tab[p] = temp;
    update( tab, 0, p - 1 );
  }
}
void update( int* tab, int l, int p ) {
  if( l >= p ) return;
  int i = l;
  int j = 2 * i + 1;
  int temp = tab[i];
  while( j <= p ) {
    if( j < p && tab[j] < tab[j + 1] ) j++;
    if( temp >= tab[j] ) break;
    tab[i] = tab[j];
    i = j;
    j = 2 * i + 1;
  }
  tab[i] = temp;
}
void quick( int* tab, int l, int p ) {
  int j = p;
  int i = l;
  int temp = tab[(l + p) / 2];

  do {
    while( tab[i] < temp ) i++;
    while( temp < tab[j] ) j--;
    if( i <= j ) {
      int w = tab[i];
      tab[i] = tab[j];
      tab[j] = w;
      i++;
      j--;
    }
  } while( i <= j );

  if( j > l ) quick( tab, l, j );
  if( i < p ) quick( tab, i, p );
}

void QuickSort( int* tab, int n ) {
  quick( tab, 0, n - 1 );
}
