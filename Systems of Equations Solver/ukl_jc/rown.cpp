#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void ReadData( FILE* fin, double** pMat, double* b, int nDim );
int CreateVector( double** pB, int nDim );
void DeleteVector( double** pVec );
void PrintVector( double* pVec, int nSize );

#define ZERO 1e-300

int main( int argc, char* argv[] )
{
  if( argc != 2 )
  {
    printf( "Usage: %s <data file>", argv[0] );
    return 1;
  }

  FILE* fin = NULL;

  if( !(fin = fopen( argv[1], "r" )) )
  {
    printf( "Error opening input file - %s\n", argv[1]);
    return -1;
  }

  int nDim = 0;
  fscanf( fin, "%d\n", &nDim );
  if( nDim < 1 ) {
    printf( "\nrozmiar macierzy = 0\n" );
    return 20;
  }
#ifdef _DEBUG_
  printf( "Rozmiar macierzy: %d\n", nDim );
#endif

  double** pMatrix = NULL;

  if( !CreateMatrix( &pMatrix, nDim ) )
  {
    printf( "error creating matrix, main\n" );
    return 3;
  }

  double* pB = NULL;
  if( !CreateVector( &pB, nDim ) )
  {
    printf( "error creating vector, main\n" );
    return 5;
  }

  ReadData( fin, pMatrix, pB, nDim );
#ifdef _DEBUG_
  printf( "\nMacierz wejsciowa:\n" );
  PrintMatrix( pMatrix, nDim );
  printf( "\nWektor niewiadomych:\n" );
  PrintVector( pB, nDim );
#endif
 
  double det = Det( pMatrix, nDim );
#ifdef _DEBUG_
  printf( "\nWyznacznik: %lf\n", det );
#endif
  if( fabs(det) < ZERO ) {
    printf( "Det = 0\n" );
    return 10;
  }

  double** pInv = NULL;

  if( !CreateMatrix( &pInv, nDim ) )
  {
    perror( "error creating pInv, main\n" );
    return 4;
  }

  InverseMatrix( pInv, pMatrix, nDim, det );
#ifdef _DEBUG_
  printf( "\nMacierz odwrotna:\n" );
  PrintMatrix( pInv, nDim );
#endif
  double* res = NULL;
  if( !CreateVector( &res, nDim ) )
  {
    perror( "error creating res vector, main\n" );
    return 7;
  }
  LayoutEqu( pInv, pB, res, nDim );

  printf( "\nWynik ukladu rownan to : \n" );
  PrintVector( res, nDim );

  DeleteVector( &pB );
  DeleteVector( &res );
  DeleteMatrix( &pMatrix, nDim );
  DeleteMatrix( &pInv, nDim );

  return 0;
}

void ReadData( FILE* fin, double** pMat, double* b, int nDim )
{
  for( int i = 0; i < nDim; i++, pMat++ )
  {
    double* temp = *pMat;
    for( int j = 0; j < nDim; j++ )
      fscanf( fin, "%lf", temp++ );
    fscanf( fin, "%lf\n", b++ );
  }
  fclose( fin );
}

int CreateVector( double** pB, int nDim )
{
  *pB = (double*)malloc( nDim * sizeof( double ) );
  if( !*pB )
    return 0;
  memset( *pB, 0, (nDim * sizeof( double )) );
  return 1;

}

void DeleteVector( double** pVec )
{
  free( *pVec );
  *pVec = NULL;
}
void PrintVector( double* pVec, int nSize )
{
  for( int i = 0; i < nSize; i++ )
    printf( "%lf \n", *pVec++ );
}