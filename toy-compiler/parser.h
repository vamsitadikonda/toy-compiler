#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include"parserDef.h"
#include"lexerDef.h"
void push(struct stack *s,char *temp,struct ParseTree* p);
struct ParseTree* pop(struct stack *s);
char *getTopOfStack(struct stack *s);
void createParseTable(struct table *why);
void loadGrammar(struct grammar *G, char *filename);
void printGrammar(struct grammar* G);
int isLeaf(char* str);
struct ParseTree *parseInputSourceCode(TOKEN *testcaseFile, struct table *T, struct grammar *G);
void   printParseTree(struct ParseTree* p,FILE*fp);

#endif // PARSER_H_INCLUDED
