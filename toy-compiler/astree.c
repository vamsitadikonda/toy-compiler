#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"parserDef.h"
#include"lexerDef.h"
#include"astreeDef.h"


void astreecreation(struct ParseTree* p, struct AsTree *a)
{



 if(p==NULL)
  {return;}
// printf(" ParseTree: %s AsTree: %s parent: %s \n",p->TokenName, a->TokenName,a->parentPTR->TokenName);
// TAKE CARE OF ARTHEMETIC AND A->B->C === A->C
int i=0;
for(i=0;i<20;i++)
{
        if(p->ptr[i]==NULL)
              break;	
	if((strcmp(p->ptr[i]->TokenName,"TK_FUNID")==0)||(strcmp(p->ptr[i]->TokenName,"TK_ID")==0)||(strcmp(p->ptr[i]->TokenName,"TK_RECORDID")==0)||(strcmp(p->ptr[i]->TokenName,"TK_FIELDID")==0)||(strcmp(p->ptr[i]->TokenName,"TK_INT")==0)||(strcmp(p->ptr[i]->TokenName,"TK_REAL")==0)||(strcmp(p->ptr[i]->TokenName,"TK_GLOBAL")==0)|| (strcmp(p->ptr[i]->TokenName,"TK_READ")==0)|| (strcmp(p->ptr[i]->TokenName,"TK_WRITE")==0)|| (strcmp(p->ptr[i]->TokenName,"TK_MUL")==0)|| (strcmp(p->ptr[i]->TokenName,"TK_DIV")==0)|| (strcmp(p->ptr[i]->TokenName,"TK_PLUS")==0) ||(strcmp(p->ptr[i]->TokenName,"TK_MINUS")==0) || (strcmp(p->ptr[i]->TokenName,"TK_NUM")==0) || (strcmp(p->ptr[i]->TokenName,"TK_RNUM")==0) ||(strcmp(p->ptr[i]->TokenName,"TK_NOT")==0) || (strcmp(p->ptr[i]->TokenName,"TK_LE")==0) ||(strcmp(p->ptr[i]->TokenName,"TK_LT")==0)||(strcmp(p->ptr[i]->TokenName,"TK_GT")==0)||(strcmp(p->ptr[i]->TokenName,"TK_GE")==0)||(strcmp(p->ptr[i]->TokenName,"TK_EQ")==0)||(strcmp(p->ptr[i]->TokenName,"TK_NE")==0)||(strcmp(p->ptr[i]->TokenName,"TK_RETURN")==0) )
	{
  		a->ptr[++(a->childno)]= (struct AsTree*) malloc(sizeof(struct AsTree));
		 int treevar=0;
     		for(treevar=0;treevar<20;treevar++)
        		a->ptr[a->childno]->ptr[treevar]= NULL;
		strcpy(a->ptr[a->childno]->TokenName ,p->ptr[i]->TokenName) ;
		
		strcpy(a->ptr[a->childno]->lexeme, p->ptr[i]->lexeme);
		a->ptr[a->childno]->isLeaf = p->ptr[i]->isLeaf;
  		a->ptr[a->childno]->childno = -1;
  		a->ptr[a->childno]->parentPTR = a;
  		 astreecreation(p->ptr[i],(a->ptr[a->childno])); 
//		 ("**ParseTree: %s AsTree: %s childno: %d\n",p->TokenName, a->TokenName, a->childno);
	}
 
	else if (p->ptr[i]-> TokenName[0]=='<')
	{
           a->ptr[++(a->childno)]= (struct AsTree*) malloc(sizeof(struct AsTree));
 		int treevar=0;
     		for(treevar=0;treevar<20;treevar++)
        		a->ptr[a->childno]->ptr[treevar]= NULL;
		strcpy(a->ptr[a->childno]->TokenName, p->ptr[i]->TokenName );
		
		strcpy(a->ptr[a->childno]->lexeme , p->ptr[i]->lexeme);
		a->ptr[a->childno]->isLeaf = p->ptr[i]->isLeaf;
  		a->ptr[a->childno]->childno = -1;
  		a->ptr[a->childno]->parentPTR = a;
  		astreecreation(p->ptr[i],(a->ptr[a->childno])); 
//		 printf("**ParseTree: %s AsTree: %s childno:%d \n",p->TokenName, a->TokenName,a->childno);	
	}
	else if (p->ptr[i]-> TokenName[0]=='E')
 	{
        		int pari=0;
                for(pari=0;pari<=(a->parentPTR->childno);pari++)
		{
  		   if((a->parentPTR->ptr[pari]!=NULL)&&strcmp(a->parentPTR->ptr[pari]->TokenName,a->TokenName)==0)
 			break;
		}
		struct AsTree * rr = a;
		int y=pari;		
		for(y=pari;y<(a->parentPTR->childno);y++)
	        	a->parentPTR->ptr[y] = a->parentPTR->ptr[y+1] ;
 		a->parentPTR->ptr[y] = NULL;
//		(a->parentPTR->childno)--;
		
	} 
	
}// end of "for" loop

	if(a->childno==0)
	{
//		printf("Trying to Remove Node %s \n",a->TokenName);		
		int pari=0;
                for(pari=0;pari<=(a->parentPTR->childno);pari++)
		{
  		   if((a->parentPTR->ptr[pari]!=NULL)&&strcmp(a->parentPTR->ptr[pari]->TokenName,a->TokenName)==0)
 			break;
		}
		struct AsTree * rr = a;
         	a->ptr[0]->parentPTR= a->parentPTR;
		a->parentPTR->ptr[pari] = a->ptr[0];
               
	}
}


void printastree(struct AsTree* p)
{
    if(p==NULL)
       {
        // printf("NULL \n");
         return;
       }  

printf("lexeme: %s token: %s  parent: %s  childno: %d \n",p->lexeme,p->TokenName,p->parentPTR->lexeme,p->childno);

	int i=0;
         int max = p->childno;  
     for(i=0;i<=max;i++)
       {
         printastree(p->ptr[i]);
         
       }
     return;
}


