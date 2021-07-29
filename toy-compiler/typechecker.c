#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parserDef.h"
#include"lexerDef.h"
#include"astreeDef.h"
#include"symboltableDef.h"


char* checktype(struct AsTree* tree, struct outerHT* OST, struct RecordList* RL , char* func)
{
 if(tree==NULL)
 return NULL;
char res[30];
 if(strcmp(tree->ptr[0]->TokenName,"TK_ID")==0 )
 {
  res= search(OST,tree->ptr[0]->lexeme, func);
  if(res==NULL)
   printf("\n ERROR :: Variable Not Declared \n");
  else if(strcmp(res,"int")==0||strcmp(res,"real")==0)
   return res;
  else if(tree->ptr[1]!=NULL) 
  {
   res=searchRecord(RL,tree->ptr[1]->lexeme,res);
   if(res==NULL)y
    printf("\n ERROR :: No such Field in Record Declared \n"); 
   return res;
  }
  else printf("\n ERROR :: Cannot Assign Values to Record Type \n");
 }
 printf("TK_ID TERM NOT PRESENT(BECAME NULL) \n");
}



// check for assignmentstmt arithmeticExprn

typecheck(struct AsTree* tree, struct outerHT* OST, struct RecordList* RL ,char* func)
{
 if(tree==NULL)
   return;
 if(strcmp(tree->TokenName,"<assignmentStmt>")==0)
 {
   char lhs[30];
   lhs = checktype(tree->ptr[1],OST,RL,func);
   strcpy(lhs,tree->ptr[1])  
   
 }
 
}

