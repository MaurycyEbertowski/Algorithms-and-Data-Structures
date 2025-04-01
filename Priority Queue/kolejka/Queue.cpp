#include "global.h"
#include "PQueue.h"
#include <stdio.h>
#include <stdlib.h>

void printFunc( const void* pInfo );
int compareFunc( const void* pFirst, const void* pSecond );
void freeFunc( const void* pInfo );
//sprawdzic kazda instrukcje, calloc, penqueue, 
int main()
{
  PQueue* queue = PQCreate( 20 );
  if( queue == NULL ) {
    printf( "blad przy tworzeniu kolejki\n" );
    return -2;
  }

  //dodawanie 6 elementów do kolejki
  for(int i = 0; i < 6; i++ ) {
    PQINFO* info = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
    if( info == NULL ) {
      printf( "blad przy tworzeniu elementu kolejki" );
      return -3;
    }
    info->nKey = i + 1;
    info->pTab = (int*)calloc( 2, sizeof( int ) );
    if( info->pTab == NULL ) {
      printf( "blad przy tworzeniu tablicy dwuelementowej\n" );
      return -4;
    }
    *(info->pTab) = i * 10;
    PQEnqueue( queue, i + 1, info );
  }
  printf( "Kolejka po dodaniu 6 elementow:\n" );
  printf( "[indeks] / (priorytet) / dane\n" );
  PQPrint( queue, 0, printFunc );

  //usuniecie elementu o najwyższym priorytecie
  PQINFO* temp = PQDequeue( queue );
  if( temp == NULL )
    printf( "blad przy usuwaniu elementu\n" );
  else {
    freeFunc( temp );//zapamietac dequeue i sparwdzic - komunikat, else wypisac klucz i zwolnic freefunc
    printf( "\nKolejka po usunieciu elementu o najwyzszym priorytecie:\n" );
    PQPrint( queue, 0, printFunc );
  }
  

  //dodanie kolejnych 2 elementów
  PQINFO* info1 = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
  if( info1 == NULL ) {
    printf( "blad przy tworzeniu info1\n" );
    return -5;
  }
  info1->nKey = 7;
  info1->pTab = (int*)calloc( 2, sizeof( int ) );
  if( info1->pTab == NULL ) {
    printf( "blad przy tworzeniu tablicy dwuelementowej w info1\n" );
    return -6;
  }
  *(info1->pTab) = 70;
  if( !PQEnqueue( queue, 7, info1 ) )
    printf( "blad przy dodawaniu do kolejki\n" );

  PQINFO* info2 = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
  if( info2 == NULL ) {
    printf( "blad przy tworzeniu info2\n" );
    return -7;
  }
  info2->nKey = 8;
  info2->pTab = (int*)calloc( 2, sizeof( int ) );
  if( info2->pTab == NULL ) {
    printf( "blad przy tworzeniu tablicy dwuelementowej w info2\n" );
    return -8;
  }
  *(info2->pTab) = 80;
  if( !PQEnqueue( queue, 8, info2 ) )
    printf( "blad przy dodawaniu do kolejki\n" );
  
  printf( "\nKolejka po dodaniu kolejnych 2 elementow:\n" );
  PQPrint( queue, 0, printFunc );

  //wyszukanie elementu o priorytecie 4 i zmienienie go na 104
   
  PQINFO* searchInfo = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
  if( searchInfo == NULL ) {
    printf( "blad przy tworzeniu searchinfo\n" );
    return -10;
  }
  searchInfo->nKey = 4;
  searchInfo->pTab = NULL;
  int oldPrior = PQSetPrior( queue, 104, searchInfo, compareFunc );
  if( oldPrior == PRIOR_ERROR ) {
    printf( "blad przy zmianie priorytetu" );
    //return -11;
  }
  //PQSetPrior( queue, 104, searchInfo, compareFunc );//zapamietac, sprawdzic czy prior error jak tak to continur
  else {
    printf( "\nKolejka po wyszukaniu elementu i zmianie priorytetu:\n" );
    PQPrint( queue, 0, printFunc );
  }
  
  //zmniejszenie priorytetu jakiegos elementu
  PQINFO* searchInfo2 = (PQINFO*)calloc( 1, sizeof( PQINFO ) ); //komunikat i wyjsce
  if( searchInfo2 == NULL ) {
    printf( "blad przy tworzeniu searchInfo2\n" );
    return -12;
  }
  searchInfo2->nKey = 5;
  searchInfo2->pTab = NULL;
  oldPrior = PQSetPrior( queue, 4, searchInfo2, compareFunc );
  if( oldPrior == PRIOR_ERROR ) {
    printf( "blad przy zmianie priorytetu\n" );
    //return -13;
  }
  printf( "\nKolejka po zmniejszeniu priorytetu piatego elementu na 4:\n" );
  PQPrint( queue, 0, printFunc );
  
  //dodanie dwoch elementow o tych samych priorytetach
  PQINFO* prior1 = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
  if( prior1 == NULL ) {
    printf( "blad przy tworzeniu elementu kolejki\n" );
    return -14;
  }
  prior1->nKey = 50;
  prior1->pTab = (int*)calloc( 2, sizeof( int ) );
  if( prior1->pTab == NULL ) {
    printf( "blad przy tworzeniu tablicy dwuelementowej\n" );
    return -15;
  }
  *(prior1->pTab) = 150;
  if( !PQEnqueue( queue, 110, prior1 ) )
    printf( "blad przy dodawaniu elementu do kolejki\n" );

  PQINFO* prior2 = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
  if( prior2 == NULL ) {
    printf( "blad przy tworzeniu elementu kolejki\n" );
    return -16;
  }
  prior2->nKey = 51;
  prior2->pTab = (int*)calloc( 2, sizeof( int ) );
  if( prior2->pTab == NULL ) {
    printf( "blad przy tworzeniu tablicy dwuelementowej\n" );
    return -17;
  }
  *(prior2->pTab) = 250;
  if( !PQEnqueue( queue, 110, prior2 ) )
    printf( "blad przy dodawaniu elementu do kolejki\n" );

  printf( "\nKolejka po dodaniu 2 elementow z tym samym priorytetetm\n" );
  PQPrint( queue, 0, printFunc );


  temp = PQDequeue( queue );
  if( temp == NULL )
    printf( "blad przy usuwaniu elementu\n" );
  else {
    freeFunc( temp );//zapamietac dequeue i sparwdzic - komunikat, else wypisac klucz i zwolnic freefunc
    printf( "\nKolejka po usunieciu jednego elementu z najwyzszym priorytetem:\n" );
    PQPrint( queue, 0, printFunc );
  }

  //temp = PQDequeue( queue );
  //freeFunc( PQDequeue( queue ) );
  //printf( "\nKolejka po usunieciu jedengo elementu z maksymalnym priorytetem\n" );
  //PQPrint( queue, 0, printFunc );

  temp = PQDequeue( queue );
  if( temp == NULL )
    printf( "blad przy usuwaniu elementu\n" );
  else {
    freeFunc( temp );//zapamietac dequeue i sparwdzic - komunikat, else wypisac klucz i zwolnic freefunc
    printf( "\nKolejka po usunieciu drugiego elementu z najwyzszym priorytetem:\n" );
    PQPrint( queue, 0, printFunc );
  }

  //freeFunc( PQDequeue( queue ) );
  //printf( "\nKolejka po usunieciu drugiego elementu z maksymalnym priorytetem\n" );
  //PQPrint( queue, 0, printFunc );

  //zwalnianie pamieci
  PQClear( queue, freeFunc );
  PQRelease( &queue, freeFunc );

  return 0;
}


void printFunc( const void* pInfo )
{
  printf( "nKey: %d, pTab[0]: %d\n", ((PQINFO*)pInfo)->nKey, ((PQINFO*)pInfo)->pTab[0] );
}

int compareFunc( const void* pFirst, const void* pSecond )
{
  if( ((PQINFO*)pFirst)->nKey < ((PQINFO*)pSecond)->nKey ) return -1;
  if( ((PQINFO*)pFirst)->nKey > ((PQINFO*)pSecond)->nKey ) return 1;
  return 0;
}

void freeFunc( const void* pInfo )
{
  if( pInfo )
    free( ((PQINFO*)pInfo)->pTab );
  free( (PQINFO*)pInfo );
}
