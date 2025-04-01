#ifndef _SHIP_
#define _SHIP_


int Move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot );
int Root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest );
void ClearRoot( int** pRoot, int nRow, int nCol );

int setTab( char* sFile, int** pTab, int nRow, int nCol );

#endif