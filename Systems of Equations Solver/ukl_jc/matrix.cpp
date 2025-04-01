#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void ComplMatrix( double** pTabD, double** pTab, int nDim );
void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );

int CreateMatrix( double*** pTab, int nDim )
{
  double** row = *pTab = (double**)malloc( nDim * sizeof( double* ) );
  if( !row ) {
    //perror( "CreateMatrix error\n" );
    return 0;
  }
  memset( row, 0, nDim * sizeof( double* ) );
  for( int i = 0; i < nDim; i++, row++ )
  {
    *row = (double*)malloc( nDim * sizeof( double ) );
    if( !*row ) {
      //perror( "CreateMatrix for loop error\n" );
      return 0;
    }
    memset( *row, 0, nDim * sizeof( double ) );
  }
  return 1;

}

void PrintMatrix( double** pTab, int nDim )
{
  for( int i = 0; i < nDim; i++ )
  {
    double* temp = *pTab++;
    for( int j = 0; j < nDim; j++ )
      printf( "%lf ", *temp++ );
    printf( "\n" );
  }
}


void TransMatrix( double** pTab, int nDim )
{

  double** p = pTab;
  for( int i = 0; i < nDim - 1; i++, p++ )
  {
    double* temp = *p + i + 1;
    for( int j = i + 1; j < nDim; j++, temp++ )
    {
      double temp2 = *temp;
      *temp = pTab[j][i];
      pTab[j][i] = temp2;
    }
  }
}
void DeleteMatrix( double*** pTab, int nDim )
{
  double** temp = *pTab;
  for( int i = 0; i < nDim; i++, temp++ )
    free( *temp );
  free( *pTab );
  *pTab = NULL;
}

void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )
{
  for( int i = 0; i < nDim; i++, pTabI++ )
  {
    if( i == nRow )
      continue;
    double* tempI = *pTabI;
    double* tempO = *pTabO++;
    for( int j = 0; j < nDim; j++, tempI++ )
    {
      if( j == nCol )
        continue;
      *tempO++ = *tempI;
    }
  }
}


double Det( double** pTab, int nDim )
{
  if( nDim == 1 )
    return **pTab;
  if( nDim == 2 )
    return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];

  double** temp = NULL;
  if( !CreateMatrix( &temp, nDim - 1 ) )
  {
    perror( "Det error\n" );
    return 0;
  }
  double* p = *pTab;
  double det = 0;
  int sgn = 1;
  for( int i = 0; i < nDim; i++, p++ )
  {
    Complement( temp, pTab, 0, i, nDim );
    det += sgn * *p * Det( temp, nDim - 1 );
    sgn = -sgn;
  }
  DeleteMatrix( &temp, nDim - 1 );
  return det;
}

void ComplMatrix( double** pTabD, double** pTab, int nDim )
{
  double** temp = NULL;
  if( !CreateMatrix( &temp, nDim - 1 ) )
  {
    perror( "ComplMtarix error\n" );
    return;
  }
  for( int i = 0; i < nDim; i++ )
  {
    double* temp2 = *pTabD++;
    int sgn = (i % 2) ? -1 : 1;
    for( int j = 0; j < nDim; j++, temp2++ )
    {
      Complement( temp, pTab, i, j, nDim );
      *temp2 = sgn * Det( temp, nDim - 1 );
      sgn = -sgn;
    }
  }
  DeleteMatrix( &temp, nDim - 1 );
}


void InverseMatrix( double** pInv, double** pTab, int nDim, double Det )
{
  ComplMatrix( pInv, pTab, nDim );
  TransMatrix( pInv, nDim );
  for( int i = 0; i < nDim; i++, pInv++ )
  {
    double* p = *pInv;
    for( int j = 0; j < nDim; j++, p++ )
      *p /= Det;
  }
}

void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim )
{
  for( int i = 0; i < nDim; i++, pRes++ )
  {
    double* tempB = pB;
    double* temp = *pInv++;
    for( int j = 0; j < nDim; j++, temp++, tempB++ )
    {
      *pRes += *temp * *tempB;
    }
  }
}