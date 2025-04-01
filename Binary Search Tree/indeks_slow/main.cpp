#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

//#define _CRT_SECURE_NO_WARNINGS

int main( int argc, char* argv[] ) {

  if( argc != 2 ) {
    printf( "Usage: %s <data file>", argv[0] );
    return 1;
  }

  FILE* file = fopen( argv[1], "r");
  if( file == NULL ) {
    printf( "Nie mozna otworzyc pliku wejsciowego %s\n", argv[1] );
    return 1;
  }

  TreeItem* root = NULL;

  read( file, &root );

  fclose( file );

  FILE* indexFile = fopen( "indeks.txt", "w+");//w+ - mozna czytac i modyfikowac plik, jezeli taki plik juz istnieje to jego zawartosc jest kasowana
  if( indexFile == NULL ) {
    printf( "Nie mozna otworzyc pliku indeks.txt.\n" );
    return 1;
  }
  
  
  printTreeInOrder( root, indexFile );
  
  fseek(indexFile, 0, SEEK_SET);//przesuwamy na poczatek pliku, 0 - ilosc bajtow, SEEK_SET-wzgledem poczatku pliku
  char c;
  while( (c = fgetc( indexFile )) != EOF ) {
    printf( "%c", c );
  }

  fclose( indexFile );
  
  freeTree( root );

  return 0;
}













/*int lineNumber = 1;
char c;

while( (c = fgetc( file )) != EOF ) {//eof - koniec pliku
  int index = 0;
  int maxSize = 10;
  char* word = (char*)calloc( maxSize, sizeof( char ) );

  if( word == NULL ) {
    printf( "blad przy alokacji pamieci na slowo\n" );
    return 10;
  }

  if( isFirst( c ) ) {
    word[index++] = c;

    while( ((c = fgetc( file )) != EOF) && isIdentifier( c ) ) {//musi byc fgetc zeby przechodzic do kolejnego znaku
      word[index++] = c;
      if( index == maxSize ) {
        maxSize += 10;
        char* word2 = (char*)realloc( word, maxSize * sizeof( char ) );//przenosi wartosc word na nowy adres
        if( word2 == NULL ) {
          printf( "blad przy realokacji pamieci\n" );
          return 15;
        }
        word = word2;
      }
    }
    word[index] = '\0';
    int length = strlen( word );
    if( length > 0 )
      insertWord( &root, word, lineNumber );
  }
  if( c == '\n' )
    lineNumber++;
}*/



/*while( fscanf(file, "%s", word) == 1 ) {//%s - do spacji lub nowej linii, zapisuje w word

  int length = strlen( word );

  //while( length > 0 && !isalnum( word[length - 1] ) ) {//isalnum-znaki alfanumeryczne
   /// word[length - 1] = '\0';//zamiana znakow niealfanumerycznych na '\0'
    //length--;
  //}

  if( length > 0 ) {
    insertWord( &root, word, lineNumber );
  }

  long currentPos = ftell( file );//bierzaca pozycja w pliku
  fseek( file, 1, SEEK_CUR );//przesuwamy wskaznik o jeden bajt - wzgledem aktualnej pozycji (SEEK_CUR
  if( fgetc( file ) == '\n' )//odczytuje znak
    lineNumber++;
  fseek( file, -1, SEEK_CUR );//cofamy do poprzedniej pozycji
}*/