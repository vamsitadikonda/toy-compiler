
#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include"lexerDef.h"

int hashfunction(char* str);
int equals(char* s1, char*s2);
FILE* getStream(FILE *fp, buffer *B, buffersize k);
void addEntry(HTABLE* t, char* token, char* inputstring,int tkno);
void populateTable(HTABLE* t);
TOKEN* tokenInit(char* token , char* inputstring ,int line, int tkno);
TOKEN* searchToken(HTABLE *t, char *s,char * probableToken,int line, int tkno);
TOKEN *getNextToken(HTABLE* t, buffer *B,int *start, int *stop,int *line,TOKEN* ERROR);
void printall();
void lex_Error(buffer *B,int start, int i,int type,int line);
void commentfreecode(buffer* B);

#endif // LEXER_H_INCLUDED
