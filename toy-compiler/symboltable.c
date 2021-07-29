#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parserDef.h"
#include"lexerDef.h"
#include"astreeDef.h"
#include"symboltableDef.h"

// Accessory Functions for Searching

char* search(struct outerHT* OST, char* id, char* func)
{
  int i=0;
 for(i=0;i< (OST->funcno);i++)
 {
   if(strcmp(OST->outerarr[i]->funcID, func)==0)
   {
    int j=0;
    for(j=0;j<(OST->outerarr[i]->stcount);j++)
    {   
     if(strcmp(OST->outerarr[i]->arr[j]->id,id)==0)
       return OST->outerarr[i]->arr[j]->type;
    }
   }
  
 }
 return NULL;
}



char* searchRecord( struct RecordList* RL,char* field ,char * recordtype);
{
 int i=0;
  for(i=0;i<(RL->recordno);i++)
  {
    if(strcmp(RL->arr[i]->recordid,recordtype)==0)
    {
	int j=0;
        for(j=0;j<(RL->arr[i]->fieldno);j++)
        {
          if(strcmp(RL->arr[i]->fieldarr[j]->fieldid,field)==0)
            return RL->arr[i]->fieldarr[j]->datatype;
        }
    }
  } 
 return NULL;
}

void populateRecord(struct AsTree *tree, struct RecordTypes* RL)
{
 if(tree==NULL )
   return;
//printf("\n populateRecord:: lexeme: %s  record: %s\n",tree->lexeme,RL->recordid);

 if(strcmp(tree->TokenName,"<fieldDefinition>")==0)
 {
   RL->fieldarr[RL->fieldno] = (struct fields* ) malloc(sizeof(struct fields));
   strcpy(RL->fieldarr[RL->fieldno]->datatype, tree->ptr[0]->lexeme);
   strcpy(RL->fieldarr[RL->fieldno]->fieldid, tree->ptr[1]->lexeme);
  // printf("adding %s %s \n",RL->fieldarr[RL->fieldno]->datatype,RL->fieldarr[RL->fieldno]->fieldid);  
  (RL->fieldno)++;   
 }
 else if(strcmp(tree->TokenName,"<fieldDefinitions>")==0)
 {
  int i=0;
  for(i=0;i<3;i++)
   if(tree->ptr[i]!=NULL)
     populateRecord(tree->ptr[i],RL);
 }
 else if(strcmp(tree->TokenName,"<moreFields>")==0)
 {
  if(tree->ptr[0]!=NULL)
   populateRecord(tree->ptr[0],RL);
  if(tree->ptr[1]!=NULL)
   populateRecord(tree->ptr[1],RL);
 }
}


void populateRecordList(struct AsTree *tree, struct RecordList* RL) 
{
 if(tree==NULL)
   return;
// printf("populateRecordList:: lexeme: %s recordno: %d \n",tree->lexeme,RL->recordno);
 if(strcmp(tree->TokenName,"<typeDefinition>")==0)
 {
   printf("%s  %s \n",tree->ptr[0]->lexeme,tree->ptr[1]->lexeme);
   RL->arr[RL->recordno] = (struct RecordTypes *) malloc(sizeof(struct RecordTypes));
   RL->arr[RL->recordno]->fieldno=0;
   strcpy(RL->arr[RL->recordno]->recordid, tree->ptr[0]->lexeme);
   //printf("**%s  %s %s \n",tree->ptr[0]->lexeme,tree->ptr[1]->lexeme,RL->arr[RL->recordno]->recordid);
   populateRecord(tree->ptr[1],RL->arr[RL->recordno]);
   (RL->recordno)++;
 }
 else if(strcmp(tree->TokenName,"<typeDefinitions>")==0)
 {
  if(tree->ptr[0]!=NULL)
  {  
  // printf("\n 1 \n"); 
   populateRecordList(tree->ptr[0],RL);
  } 
  if(tree->ptr[1]!=NULL)
  {
  //  printf("\n 2 \n");
   populateRecordList(tree->ptr[1],RL);   
  }
 }
}


void printRecordList(struct RecordList* RL )
{
 int i=0;
  for(i=0;i<(RL->recordno);i++)
  {
    int j=0;
    printf("   In Record: %s  \n",RL->arr[i]->recordid);
    for(j=0;j<(RL->arr[i]->fieldno);j++)
    {
     printf("%s %s; \n",RL->arr[i]->fieldarr[j]->datatype,RL->arr[i]->fieldarr[j]->fieldid);
    }
  } 
}



/*
Didnt take care of Record inside stuff (definition part not taken care ) but while declaring it will accept.
didnt take care of global !!!!!!!!!
******************* take care of offset
*/

void populateFuncHT(struct AsTree *tree,struct funcHT *ht, struct outerHT* OST, struct RecordList* RL)
{
  if(tree==NULL)
	return;
//  printf("populateFunctHt :: lexeme : %s funcHT: %s \n",tree->lexeme, ht->funcID);
  if(strcmp(tree->TokenName,"<stmts>")==0)
  { 
    populateFuncHT(tree->ptr[0],ht,OST,RL);
    populateFuncHT(tree->ptr[1],ht,OST,RL);
  }
  else if(strcmp(tree->TokenName,"<typeDefinitions>")==0)
  {
//   printf("\n\n\nThere are Record Types !!!\n\n\n") ;
   populateRecordList(tree,RL);
  }
  else if(strcmp(tree->TokenName,"<declarations>")==0)
  {
      populateFuncHT(tree->ptr[0],ht,OST,RL);
      populateFuncHT(tree->ptr[1],ht,OST,RL); 
  }
  else if(strcmp(tree->TokenName,"<declaration>")==0)
  {
     if(tree->ptr[2]==NULL)
     {
//	printf("adding %s %s \n",tree->ptr[0]->lexeme,tree->ptr[1]->lexeme);
     	ht->arr[ht->stcount]= (struct STnode*) malloc(sizeof(struct STnode));
     	strcpy(ht->arr[ht->stcount]->type, tree->ptr[0]->lexeme);
     	strcpy(ht->arr[ht->stcount]->id, tree->ptr[1]->lexeme);
     	ht->arr[ht->stcount]->offset = 2*(ht->stcount);
     	ht->arr[ht->stcount]->ptr = NULL;
     	(ht->stcount)++;
     }
     else
     {
//       printf("adding %s %s %s \n",tree->ptr[0]->lexeme,tree->ptr[1]->lexeme,tree->ptr[2]->lexeme);
     	OST->outerarr[0]->arr[OST->outerarr[0]->stcount]= (struct STnode*) malloc(sizeof(struct STnode));
     	strcpy(OST->outerarr[0]->arr[OST->outerarr[0]->stcount]->type, tree->ptr[0]->lexeme);
     	strcpy(OST->outerarr[0]->arr[OST->outerarr[0]->stcount]->id, tree->ptr[1]->lexeme);
     	OST->outerarr[0]->arr[OST->outerarr[0]->stcount]->offset = 0;
     	OST->outerarr[0]->arr[OST->outerarr[0]->stcount]->ptr = NULL;
     	(OST->outerarr[0]->stcount)++;
     }
  }
}



void populateST(struct AsTree* tree,struct outerHT* OST, struct RecordList* RL) 
{
  if(tree==NULL)
      return;
//  printf("**populateST :: lexeme : %s \n",tree->lexeme);

  if(strcmp(tree->TokenName,"<program>")==0)
  {
    if(tree->ptr[0]!=NULL)
    {
     populateST(tree->ptr[0],OST,RL) ; 
    }
    if(tree->ptr[1]!=NULL)
    {
	OST->outerarr[(OST->funcno)] = (struct funcHT *) malloc(sizeof(struct funcHT ));
	strcpy( OST->outerarr[(OST->funcno)]->funcID,"_main");
        OST->outerarr[(OST->funcno)]->stcount=0;
	int op=0;
        for(op=0;op<50;op++)
	    OST->outerarr[OST->funcno]->arr[op]=(struct STnode *) malloc(sizeof(struct STnode));		
	(OST->funcno)++;     
        populateFuncHT(tree->ptr[1],OST->outerarr[(OST->funcno)-1],OST,RL);
    }	    
  }
  else if(strcmp(tree->TokenName,"<otherFunctions>")==0)
  {
    if(tree->ptr[0]!=NULL)
    {
      populateST(tree->ptr[0],OST,RL) ; 
    }
    if(tree->ptr[1]!=NULL)
    {
      populateST(tree->ptr[1],OST,RL) ;     
    } 
  }
  else if(strcmp(tree->TokenName,"<function>")==0)
  {
    OST->outerarr[(OST->funcno)] = (struct funcHT *) malloc(sizeof(struct funcHT ));
	strcpy( OST->outerarr[(OST->funcno)]->funcID,tree->ptr[0]->lexeme);
	OST->outerarr[(OST->funcno)]->stcount=0;
	int op=0;
        for(op=0;op<50;op++)
	    OST->outerarr[OST->funcno]->arr[op]=(struct STnode *) malloc(sizeof(struct STnode));		
	(OST->funcno)++;     
	 return populateFuncHT(tree->ptr[3],OST->outerarr[(OST->funcno)-1],OST,RL);
  }
}



void printSymbolTable(struct outerHT* OST)
{
 int i=0;
 for(i=0;i< (OST->funcno);i++)
 {
  int j= OST->outerarr[i]->stcount;
  for(j=0;j<(OST->outerarr[i]->stcount);j++)
  {
    printf("type : %s  variable: %s  scope: %s offset:%d \n",OST->outerarr[i]->arr[j]->type,OST->outerarr[i]->arr[j]->id,OST->outerarr[i]->funcID,OST->outerarr[i]->arr[j]->offset );
  }
 
 }

}


