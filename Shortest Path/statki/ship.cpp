#include "ship.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { UP, DOWN, RIGHT, LEFT } Direction;

int Move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot )
{
  switch( move )
  {
  case UP: *px = x - 1; *py = y; break;
  case DOWN: *px = x + 1; *py = y; break;
  case RIGHT: *px = x; *py = y + 1; break;
  case LEFT: *px = x; *py = y - 1; break;
  }

  if( *px >= 0 && *px < nRow && *py >= 0 && *py < nCol )
    if( pTab[*px][*py] > nDepth && !pRoot[*px][*py] )
      return 1;
  return 0;
}

int Root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
{
  static int counter = 1;
  pRoot[x][y] = counter++;

  if( x == x_dest && y == y_dest )
    return 1;

  int px = 0;
  int py = 0;

  for( int i = UP; i <= LEFT; i++ )
  {
    if( Move( pTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) )
      if( Root( pTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) )
        return 1;
  }

  counter--;
  return 0;
}

void ClearRoot( int** pRoot, int nRow, int nCol )
{
  memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
  FILE* fin = fopen( sFile, "r" );
  if( !fin )
  {
    //perror( "setTab error opening file\n" );
    return 0;
  }

  for( int i = 0; i < nRow; i++, pTab++ )
  {
    int* pTemp = *pTab;
    for( int j = 0; j < nCol; j++, pTemp++ )
      fscanf_s( fin, "%d", pTemp );
  }

  fclose( fin );
  return 1;
}