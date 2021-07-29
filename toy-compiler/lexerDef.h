#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED


typedef struct BUFFER buffer;
struct BUFFER
{
  char buff[10000];
  int size;
};

typedef int buffersize;

typedef struct token TOKEN;
struct token
{
  int tkno;
  char token[20];
  char string[20];
  int line;
  TOKEN *next ;
};

typedef struct tableentry ENTRY;
struct tableentry
{
   int tkno;
   char token[20];
   char inputstring[20];
    int value;
    ENTRY* next;
};

typedef struct htable HTABLE;
struct htable
{
    ENTRY* ent[30];
};
extern TOKEN* STARTNODE ;
extern TOKEN* LASTNODE ;


#endif // LEXERDEF_H_INCLUDED
