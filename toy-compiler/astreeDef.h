#include <stdio.h>
#include <stdlib.h>


struct AsTree {
int isLeaf ;
char lexeme[30] ;
int lineNumber ;
char TokenName[30] ;
int childno;
struct AsTree *ptr[20] ;
struct AsTree *parentPTR ;

};


