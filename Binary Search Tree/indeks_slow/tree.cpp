#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

TreeItem* createTreeItem( char* word, int lineNumber ) {//utworzenie elementu dla nowego slowa
  TreeItem* item = (TreeItem*)calloc( 1, sizeof( TreeItem ) );
  if( item == NULL ) {
    printf( "blad przy tworzeniu elementu drzewa\n" );
    return NULL;
  }

  item->pWord = (char*)calloc( (strlen( word ) + 1), sizeof( char ) ); //+1 bo strlen nie liczy '\0'
  if( item->pWord == NULL ) {
    printf( "blad przy tworzeniu elementu drzewa\n" );
    free( item );
    return NULL;
  }
  strcpy( item->pWord, word );
  //item->pWord = word; tracenie pamieci
  item->counter = 1;

  item->lineNumbersList = createListHead( lineNumber );//nowe slowo wiec trzeba zrobic nowa liste
  if( item->lineNumbersList.pFirst == NULL ) {
    printf( "blad przy tworzeniu listy\n" );
    free( item->pWord );
    free( item );
    return NULL;
  }

  return item;
}

ListHead createListHead( int lineNumber ) {

  ListHead head;
  head.pFirst = head.pLast = NULL;
  ListItem* item = (ListItem*)calloc( 1, sizeof( ListItem ) );
  if( item == NULL ) {
    printf( "blad przy tworzeniu listy\n" );
    return head;
  }
  item->lineNumber = lineNumber;
  
  head.pFirst = head.pLast = item;//polaczyc

  return head;
}

int isIdentifier( char c ) {
  return isFirst( c ) || (c >= '0' && c <= '9');
 // return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_');
}

int isFirst( char c ) {
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

void insertWord( TreeItem** root, char* word, int lineNumber ) {//dwie gwiazdki bo zmieniamy *root
  if( *root == NULL ) {
    *root = createTreeItem( word, lineNumber );//jezeli nowe slowo to tworzymy nowy wezel drzewa
    return;
  }

  int compare = StrCmp( (*root)->pWord, word );//0 gdy sa rowne
  if( compare == 0 ) {
    (*root)->counter++;//jesli slowo juz istnieje to zwiekszamy counter
    addLineNumber( (*root)->lineNumbersList, lineNumber );
  }
  else if( compare > 0 )//word<pWord idziemy w lewo
    insertWord( &((*root)->left), word, lineNumber );

  else//word>pWord idziemy w prawo
    insertWord( &((*root)->right), word, lineNumber );
}

void addLineNumber( ListHead head, int lineNumber ) {
  if( head.pLast->lineNumber == lineNumber )
    return;
  ListItem* item = (ListItem*)calloc( 1, sizeof( ListItem ) );//nowy element listy
  if( item == NULL ) {
    printf( "blad przy tworzeniu elementu listy\n" );
    return;
  }

  item->lineNumber = lineNumber;

  head.pLast->next = item;//doczepiamy do ostatniego elementu
  head.pLast = item;//zapisujemy node jako ostatni element listy
}


int StrCmp( char* str1, char* str2 ) {
  char* copyStr1 = (char*)calloc( (strlen( str1 ) + 1), sizeof( char ) );//+1 bo \0 nie jest wliczane
  char* copyStr2 = (char*)calloc( (strlen( str2 ) + 1), sizeof( char ) );

  if( copyStr1 == NULL || copyStr2 == NULL ) {
    printf( "blad przy kopiowaniu wyrazow\n" );
    return 0;
  }

  strcpy( copyStr1, str1 ); //kopiuje str1 do copyStr1
  strcpy( copyStr2, str2 );

  _strlwr( copyStr1 );
  _strlwr( copyStr2 );

  int result = strcmp( copyStr1, copyStr2 );//0 gdy sa rowne, <0 gdy str1 < str2, >0 na odwrot

  free( copyStr1 );
  free( copyStr2 );

  return result;
}

void freeTree( TreeItem* root ) {
  if( root == NULL )
    return;

  freeTree( root->left );
  freeTree( root->right );
  freeList( root->lineNumbersList.pFirst );
  free( root->pWord );
  free( root );
}

void freeList( ListItem* item ) {
  ListItem* current = item;
  while( current != NULL ) {
    ListItem* next = current->next;
    free( current );
    current = next;
  }
}

void printTreeInOrder( TreeItem* root, FILE* file ) { //do tree.cpp
  if( root == NULL )
    return;

  printTreeInOrder( root->left, file );

  fprintf( file, "\"%s\" wystepuje %d razy, w liniach: ", root->pWord, root->counter );

  ListItem* current = root->lineNumbersList.pFirst;
  while( current != NULL ) {
    fprintf( file, "%d ", current->lineNumber );
    current = current->next;
  }
  fprintf( file, "\n\n" );

  printTreeInOrder( root->right, file );
}

void read( FILE* file, TreeItem** root ) {
  int lineNumber = 1;
  char c;

  while( (c = fgetc( file )) != EOF ) {//eof - koniec pliku
    
    if( isFirst( c ) ) {
      int index = 0;
      int maxSize = 10;
      char* word = (char*)calloc( maxSize, sizeof( char ) );
      if( word == NULL ) {
        printf( "blad przy alokacji pamieci na slowo\n" );
        return;
      }
      word[index++] = c;
      while( ((c = fgetc( file )) != EOF) && isIdentifier( c ) ) {//musi byc fgetc zeby przechodzic do kolejnego znaku
        word[index++] = c;
        if( index == maxSize ) {
          maxSize += 10;
          char* word2 = (char*)realloc( word, maxSize * sizeof( char ) );//przenosi wartosc word na nowy adres
          if( word2 == NULL ) {
            printf( "blad przy realokacji pamieci\n" );
            return;
          }
          word = word2;
        }
      }
      word[index] = '\0';
      int length = (int)strlen( word );
      if( length > 0 )
        insertWord( root, word, lineNumber );
      free( word );
      //free word
    }
    if( c == '\n' )
      lineNumber++;
  }
}


/*void freeList(ListHead head) {//listitem, head.pfirst

  ListItem* current = head.pFirst;//w parametrze
  while( current != NULL ) {
    ListItem* next = current->next;
    free( current );
    current = next;
  }
  //free( &head );//usuniecie glowy
}*/