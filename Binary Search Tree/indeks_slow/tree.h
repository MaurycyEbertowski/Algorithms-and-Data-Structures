#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct ListItem {//lista do przechowywania numerów linii - fifo
  int lineNumber;
  ListItem* next;
} ListItem;

typedef struct ListHead {//glowa listy
  ListItem* pFirst;
  ListItem* pLast;
} ListHead;

typedef struct TreeItem {//element drzewa
  char* pWord;//slowo
  int counter;//ilosc wystapien
  ListHead lineNumbersList;//lista z liniami wystapien, //bez gwiazdki
  TreeItem* left;//dziecko
  TreeItem* right;
} TreeItem;


TreeItem* createTreeItem( char* word, int lineNumber );
ListHead createListHead( int lineNumber );//utworzenie listy z numerami lin

void insertWord( TreeItem** root, char* word, int lineNumber );
void addLineNumber( ListHead head, int lineNumber );//dodanie numeru linii do listy
void freeList( ListItem* head );
void freeTree( TreeItem* root );

int isFirst( char c );
int isIdentifier( char c );
int StrCmp( char* str1, char* str2 );

void printTreeInOrder( TreeItem* root, FILE* file );
void read( FILE* file, TreeItem** root );
