/*
  BATCH NO :22 
  VAMSI TADIKONDA (2013A7PS039P)
  ISHAN CHUTANI (2013A7PS112P)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"lexerDef.h"
#include"parserDef.h"
#include"lexer.h"
#include"parser.h"
#include"astreeDef.h"
#include"astree.h" 
#include"symboltableDef.h"
#include"symboltable.h"

  
main(int argc, char* argv[]) {
  int start=0 ; int stop=0 ; int line =1 ;
  FILE *fp;
  fp = fopen(argv[1],"r");
   if(fp==NULL)
   {
     printf("Error in Opening Testfile. \n Press Enter Continue:\n");
     char day ;
     while(day!='\n')
      day= getchar();
      exit(0);
   }
  else 	
   {
     buffer B;
     B.size=0;
     HTABLE t;
     int y=0;
     for(y=0;y<30;y++) {
	t.ent[y] = (ENTRY *) malloc(sizeof(ENTRY)) ;
	}
     populateTable(&t);
     getStream(fp,&B,100000);
     
      TOKEN ERROR;
      ERROR.tkno=-100;
        int errorfound=0;  
	TOKEN* temp1 = NULL;
       while ( stop < B.size  ) {
        temp1=(TOKEN*)getNextToken(&t, &B,&start,&stop,&line,&ERROR);
	  
         if(temp1==&ERROR)
           { errorfound=1;  start=stop ;}
	 else if(temp1==NULL && B.buff[start]==EOF)
            {
                break;        
            }

         else  start=stop ;
        }
        if(errorfound==1)
	 {printf("\n \n Resolve the Lexical Errors!! \n \n");}
        else
	{
           	struct table why;
          	 int g1=0,h1=0;
       		 for(g1=0;g1<50;g1++)
        	{
            		for(h1=0;h1<57;h1++)
            		{why.ParseTable[g1][h1] = 100;}
        	}
         	createParseTable(&why);
         	struct grammar G;
         	loadGrammar(&G,"grammar.txt") ;        
         	
         	
              		struct ParseTree* roottree = parseInputSourceCode(STARTNODE,&why,&G);
              		FILE *outfile = fopen(argv[2],"w");
//			printtree(roottree);
                   	printParseTree(roottree,outfile);        	

//*****************DO NOT CHANGE **********************************************************************************************************

		
			struct AsTree* aroot = (struct AsTree*) malloc(sizeof(struct AsTree));
					
			strcpy(aroot->TokenName , "ROOT");
			strcpy(aroot->lexeme , "$");
			aroot->childno=-1;
			aroot->parentPTR=aroot;
  			aroot->isLeaf=0;
			 int treevar=0;
     			for(treevar=0;treevar<20;treevar++)
       				 aroot->ptr[treevar]= NULL;


			astreecreation(roottree,aroot);


                        printf("\n\n\n\n**********\n\n\n");			
			printastree(aroot);
			
				
//*****************************************************************************************     


struct outerHT *OST = (struct outerHT *) malloc(sizeof(struct outerHT)) ;
int i,j ;

for(i=0;i<100;i++) {
    OST->outerarr[i] = (struct funcHT *) malloc(sizeof(struct funcHT)) ;
        for(j=0;j<50;j++) {
            OST->outerarr[i]->arr[j] = NULL ;  
        }
    
}

struct RecordList* RL = (struct RecordList*) malloc(sizeof(struct RecordList));
RL->recordno=0;

OST->funcno=1;
strcpy(OST->outerarr[0]->funcID , "global");
OST->outerarr[0]->stcount=0;
printf("\n\n\n\n?????????????????????????\n\n\n");
populateST(aroot->ptr[0],OST,RL) ;
printf("\n\n\n$$$$$$$$$  SYMBOL TABLE  $$$$$$$$$$\n\n\n");
printSymbolTable(OST);
printf("\n\n\n$$$$$$$$$  RECORD LIST  $$$$$$$$$$\n\n\n");
printRecordList(RL);





//*********************************************************************************************       
        }
   
   }
}
