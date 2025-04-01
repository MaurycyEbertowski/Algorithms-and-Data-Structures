#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "ship.h"

#define N 10
#define M 10
#define MINDEPTH 5

#define _DEBUG_

int** CreateTab( int nRow, int nCol );
void PrintTab( int** pTab, int nRow, int nCol );
void DeleteTab( int*** pTab );

int main( int argc, char** argv )
{
  if( argc != 2 )
  {
    printf( "Problem with input file: %s <input_file>\n", argv[1] );
    return 1;
  }

  int** pTab = CreateTab( N, M );
  int** pRoot = CreateTab( N, M );
  if( !pTab || !pRoot ) {
    perror( "CreateTab error - main\n" );
    return -1;
  }

  if( !setTab( argv[1], pTab, N, M ) )
  {
    printf( "setTab %s error - main\n", argv[1] );
    return -3;
  }
 
  printf( "Minimalna glebokosc = %d\nMapa:\n", MINDEPTH );
  PrintTab( pTab, N, M );
  printf( "\n" );

  if( !Root( pTab, N, M, MINDEPTH, 0, 0, pRoot, N - 1, M - 1 ) )
  {
    printf( " Nie ma mozliwosci doplynac do portu!!\n\n" );
  }
  else
  {
    printf( "Trasa do portu:\n" );
    PrintTab( pRoot, N, M );
  }

  DeleteTab( &pTab );
  DeleteTab( &pRoot );

  return 0;
}

int** CreateTab( int nRow, int nCol )
{
  int** temp = (int**)malloc( nRow * sizeof( int* ) );
  if( !temp )
    return 0;
  memset( temp, 0, nRow * sizeof( int* ) );

  *temp = (int*)malloc( nRow * nCol * sizeof( int* ) );
  if( !*temp )
    return 0;
  memset( *temp, 0, nRow * nCol * sizeof( int ) );

  int** temp1 = temp + 1;
  int* temp_col = *temp + nCol;

  for( int i = 1; i < nRow; i++, temp1++, temp_col += nCol ) {
    *temp1 = temp_col;
    
  }
  return temp;
}

void PrintTab( int** pTab, int nRow, int nCol )
{
  for( int i = 0; i < nRow; i++ )
  {
    int* temp = *pTab++;
    for( int j = 0; j < nCol; j++, temp++ )
    {
      printf( "%d   ", *temp );
    }
    printf( "\n" );
  }
}

void DeleteTab( int*** pTab )
{
  free( **pTab );
  free( *pTab );
  *pTab = NULL;
}