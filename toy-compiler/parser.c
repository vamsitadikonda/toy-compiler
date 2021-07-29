#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"parserDef.h"
#include"lexerDef.h"

   char *NonTer[50] = {"<program>","<mainFunction>","<otherFunctions>","<function>","<input_par>","<output_par>","<parameter_list>","<dataType>","<primitiveDatatype>",
   "<constructedDatatype>","<remaining_list>","<stmts>","<typeDefinitions>","<typeDefinition>","<fieldDefinitions>","<fieldDefinition>","<moreFields>","<declarations>","<declaration>",
   "<global_or_not>","<otherStmts>","<stmt>","<assignmentStmt>","<singleOrRecId>","<new_24>","<funCallStmt>","<outputParameters>","<inputParameters>",
"<iterativeStmt>","<conditionalStmt>","<elsePart>","<ioStmt>","<allVar>","<arithmeticExpression>","<expPrime>","<term>","<termPrime>","<factor>","<highPrecedenceOperators>",
"<lowPrecedenceOperators>","<all>","<temp>","<booleanExpression>","<var>","<logicalOp>","<relationalOp>","<returnStmt>","<optionalReturn>","<idList>","<more_ids>"} ;

   char *Terminals[57] ={"TK_CL","TK_AND","TK_OR","TK_NE","TK_RECORDID","TK_PLUS","TK_GE","TK_GT","TK_COLON","TK_MINUS","TK_MUL","TK_EQ","TK_FUNID","TK_SQL","TK_SQR",
"TK_COMMA","TK_SEM","TK_LE","TK_ASSIGNOP","TK_LT","TK_OP","TK_NOT","TK_DIV","TK_DOT","TK_NL","TK_COMMENT","TK_SPACE","TK_RNUM","TK_NUM",
"TK_FIELDID","TK_ID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_INT","TK_REAL","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER",
"TK_LIST","TK_INPUT","TK_OUTPUT","TK_ENDWHILE","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_CALL","TK_RECORD","TK_ENDRECORD","TK_ELSE","$","EPSILON"} ;


void push(struct stack *s,char *temp,struct ParseTree* p) {
//s->stArray[++s->top] = (char *) malloc(sizeof(char)) ;
//s->trArray[s->top] = (struct ParseTree*) malloc(sizeof(struct ParseTree));
strcpy(s->stArray[++s->top], temp) ;
s->trArray[s->top]=p;
}

struct ParseTree* pop(struct stack *s) {
return s->trArray[s->top--] ;
}

char *getTopOfStack(struct stack *s) {
return s->stArray[s->top] ;
}


void createParseTable(struct table *why)
{
  why->ParseTable[(int)program][(int)TK_FUNID] = 0;
why->ParseTable[(int)program][(int)TK_MAIN] = 0;
why->ParseTable[(int)mainFunction][(int)TK_MAIN] = 1;
why->ParseTable[(int)otherFunctions][(int)TK_FUNID] = 2;
why->ParseTable[(int)otherFunctions][(int)TK_MAIN] = 3;
why->ParseTable[(int)function][(int)TK_FUNID] = 4;
why->ParseTable[(int)input_par][(int)TK_INPUT] = 5;
why->ParseTable[(int)output_par][(int)TK_OUTPUT] = 6;
why->ParseTable[(int)output_par][(int)TK_SEM] = 7;
why->ParseTable[(int)parameter_list][(int)TK_INT] = 8;
why->ParseTable[(int)parameter_list][(int)TK_REAL] = 8;
why->ParseTable[(int)parameter_list][(int)TK_RECORD] = 8;
why->ParseTable[(int)dataType][(int)TK_INT] = 9;
why->ParseTable[(int)dataType][(int)TK_REAL] = 9;
why->ParseTable[(int)dataType][(int)TK_RECORD] = 10;
why->ParseTable[(int)primitiveDatatype][(int)TK_INT] = 11;
why->ParseTable[(int)primitiveDatatype][(int)TK_REAL] = 12;
why->ParseTable[(int)constructedDatatype][(int)TK_RECORD] = 13;
why->ParseTable[(int)remaining_list][(int)TK_COMMA] = 14;
why->ParseTable[(int)remaining_list][(int)TK_SQR] = 15;
why->ParseTable[(int)stmts][(int)TK_CALL] = 16;
why->ParseTable[(int)stmts][(int)TK_ID] = 16;
why->ParseTable[(int)stmts][(int)TK_IF] = 16;
why->ParseTable[(int)stmts][(int)TK_READ] = 16;
why->ParseTable[(int)stmts][(int)TK_RECORD] = 16;
why->ParseTable[(int)stmts][(int)TK_RECORDID] = 16;
why->ParseTable[(int)stmts][(int)TK_RETURN] = 16;
why->ParseTable[(int)stmts][(int)TK_SQL] = 16;
why->ParseTable[(int)stmts][(int)TK_TYPE] = 16;
why->ParseTable[(int)stmts][(int)TK_WHILE] = 16;
why->ParseTable[(int)stmts][(int)TK_WRITE] = 16;
why->ParseTable[(int)typeDefinitions][(int)TK_CALL] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_ID] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_IF] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_READ] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_RECORD] = 17;
why->ParseTable[(int)typeDefinitions][(int)TK_RECORDID] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_RETURN] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_SQL] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_TYPE] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_WHILE] = 18;
why->ParseTable[(int)typeDefinitions][(int)TK_WRITE] = 18;
why->ParseTable[(int)typeDefinition][(int)TK_RECORD] = 19;
why->ParseTable[(int)fieldDefinitions][(int)TK_TYPE] = 20;
why->ParseTable[(int)fieldDefinition][(int)TK_TYPE] = 21;
why->ParseTable[(int)moreFields][(int)TK_ENDRECORD] = 23;
why->ParseTable[(int)moreFields][(int)TK_TYPE] = 22;
why->ParseTable[(int)declarations][(int)TK_CALL] = 25;
why->ParseTable[(int)declarations][(int)TK_ID] = 25;
why->ParseTable[(int)declarations][(int)TK_IF] = 25;
why->ParseTable[(int)declarations][(int)TK_READ] = 25;
why->ParseTable[(int)declarations][(int)TK_RECORDID] = 25;
why->ParseTable[(int)declarations][(int)TK_RETURN] = 25;
why->ParseTable[(int)declarations][(int)TK_SQL] = 25;
why->ParseTable[(int)declarations][(int)TK_TYPE] = 24;
why->ParseTable[(int)declarations][(int)TK_WHILE] = 25;
why->ParseTable[(int)declarations][(int)TK_WRITE] = 25;
why->ParseTable[(int)declaration][(int)TK_TYPE] = 26;
why->ParseTable[(int)global_or_not][(int)TK_COLON] = 27;
why->ParseTable[(int)global_or_not][(int)TK_SEM] = 28;
why->ParseTable[(int)otherStmts][(int)TK_CALL] = 29;
why->ParseTable[(int)otherStmts][(int)TK_ELSE] = 30;
why->ParseTable[(int)otherStmts][(int)TK_ENDIF] = 30;
why->ParseTable[(int)otherStmts][(int)TK_ENDWHILE] = 30;
why->ParseTable[(int)otherStmts][(int)TK_ID] = 29;
why->ParseTable[(int)otherStmts][(int)TK_IF] = 29;
why->ParseTable[(int)otherStmts][(int)TK_READ] = 29;
why->ParseTable[(int)otherStmts][(int)TK_RECORDID] = 29;
why->ParseTable[(int)otherStmts][(int)TK_RETURN] = 30;
why->ParseTable[(int)otherStmts][(int)TK_SQL] = 29;
why->ParseTable[(int)otherStmts][(int)TK_WHILE] = 29;
why->ParseTable[(int)otherStmts][(int)TK_WRITE] = 29;
why->ParseTable[(int)stmt][(int)TK_CALL] = 35;
why->ParseTable[(int)stmt][(int)TK_ID] = 31;
why->ParseTable[(int)stmt][(int)TK_IF] = 33;
why->ParseTable[(int)stmt][(int)TK_READ] = 34;
why->ParseTable[(int)stmt][(int)TK_RECORDID] = 31;
why->ParseTable[(int)stmt][(int)TK_SQL] = 35;
why->ParseTable[(int)stmt][(int)TK_WHILE] = 32;
why->ParseTable[(int)stmt][(int)TK_WRITE] = 34;
why->ParseTable[(int)assignmentStmt][(int)TK_ID] = 36;
why->ParseTable[(int)singleOrRecId][(int)TK_ID] = 37;
why->ParseTable[(int)funCallStmt][(int)TK_CALL] = 40;
why->ParseTable[(int)funCallStmt][(int)TK_SQL] = 40;
why->ParseTable[(int)outputParameters][(int)TK_CALL] = 42;
why->ParseTable[(int)outputParameters][(int)TK_SQL] = 41;
why->ParseTable[(int)inputParameters][(int)TK_SQL] = 43;
why->ParseTable[(int)iterativeStmt][(int)TK_WHILE] = 44;
why->ParseTable[(int)conditionalStmt][(int)TK_IF] = 45;
why->ParseTable[(int)elsePart][(int)TK_ELSE] = 46;
why->ParseTable[(int)elsePart][(int)TK_ENDIF] = 47;
why->ParseTable[(int)ioStmt][(int)TK_READ] = 48;
why->ParseTable[(int)ioStmt][(int)TK_WRITE] = 49;
why->ParseTable[(int)arithmeticExpression][(int)TK_ID] = 51;
why->ParseTable[(int)arithmeticExpression][(int)TK_NUM] = 51;
why->ParseTable[(int)arithmeticExpression][(int)TK_OP] = 51;
why->ParseTable[(int)arithmeticExpression][(int)TK_RECORDID] = 51;
why->ParseTable[(int)arithmeticExpression][(int)TK_RNUM] = 51;
why->ParseTable[(int)expPrime][(int)TK_CL] = 53;
why->ParseTable[(int)expPrime][(int)TK_MINUS] = 52;
why->ParseTable[(int)expPrime][(int)TK_PLUS] = 52;
why->ParseTable[(int)expPrime][(int)TK_SEM] = 53;
why->ParseTable[(int)term][(int)TK_ID] = 54;
why->ParseTable[(int)term][(int)TK_NUM] = 54;
why->ParseTable[(int)term][(int)TK_OP] = 54;
why->ParseTable[(int)term][(int)TK_RECORDID] = 54;
why->ParseTable[(int)term][(int)TK_RNUM] = 54;
why->ParseTable[(int)termPrime][(int)TK_CL] = 56;
why->ParseTable[(int)termPrime][(int)TK_DIV] = 55;
why->ParseTable[(int)termPrime][(int)TK_MINUS] = 56;
why->ParseTable[(int)termPrime][(int)TK_MUL] = 55;
why->ParseTable[(int)termPrime][(int)TK_PLUS] = 56;
why->ParseTable[(int)termPrime][(int)TK_SEM] = 56;
why->ParseTable[(int)factor][(int)TK_ID] = 58;
why->ParseTable[(int)factor][(int)TK_NUM] = 58;
why->ParseTable[(int)factor][(int)TK_OP] = 57;
why->ParseTable[(int)factor][(int)TK_RECORDID] = 58;
why->ParseTable[(int)factor][(int)TK_RNUM] = 58;
why->ParseTable[(int)all][(int)TK_ID] = 65;
why->ParseTable[(int)all][(int)TK_NUM] = 63;
why->ParseTable[(int)all][(int)TK_RNUM] = 64;
why->ParseTable[(int)temp][(int)TK_AND] = 66;
why->ParseTable[(int)temp][(int)TK_CL] = 67;
why->ParseTable[(int)temp][(int)TK_DIV] = 67;
why->ParseTable[(int)temp][(int)TK_MINUS] = 67;
why->ParseTable[(int)temp][(int)TK_MUL] = 67;
why->ParseTable[(int)temp][(int)TK_PLUS] = 67;
why->ParseTable[(int)temp][(int)TK_SEM] = 67;
why->ParseTable[(int)temp][(int)TK_DOT] = 66;
why->ParseTable[(int)temp][(int)EPSILON] = 68;
why->ParseTable[(int)booleanExpression][(int)TK_ID] = 69;
why->ParseTable[(int)booleanExpression][(int)TK_NOT] = 70;
why->ParseTable[(int)booleanExpression][(int)TK_NUM] = 69;
why->ParseTable[(int)booleanExpression][(int)TK_OP] = 68;
why->ParseTable[(int)booleanExpression][(int)TK_RNUM] = 69;
why->ParseTable[(int)var][(int)TK_ID] = 71;
why->ParseTable[(int)var][(int)TK_NUM] = 72;
why->ParseTable[(int)var][(int)TK_RNUM] = 73;
why->ParseTable[(int)logicalOp][(int)TK_AND] = 74;
why->ParseTable[(int)logicalOp][(int)TK_OR] = 75;
why->ParseTable[(int)relationalOp][(int)TK_EQ] = 78;
why->ParseTable[(int)relationalOp][(int)TK_GE] = 80;
why->ParseTable[(int)relationalOp][(int)TK_GT] = 79;
why->ParseTable[(int)relationalOp][(int)TK_LE] = 77;
why->ParseTable[(int)relationalOp][(int)TK_LT] = 76;
why->ParseTable[(int)relationalOp][(int)TK_NE] = 81;
why->ParseTable[(int)returnStmt][(int)TK_RETURN] = 82;
why->ParseTable[(int)optionalReturn][(int)TK_SEM] = 84;
why->ParseTable[(int)optionalReturn][(int)TK_SQL] = 83;
why->ParseTable[(int)idList][(int)TK_ID] = 85;
why->ParseTable[(int)more_ids][(int)TK_COMMA] = 86;
why->ParseTable[(int)more_ids][(int)TK_SQR] = 87;
why->ParseTable[(int)allVar][(int)TK_ID] = 50;
why->ParseTable[(int)allVar][(int)TK_NUM] = 50;
why->ParseTable[(int)allVar][(int)TK_RNUM] = 50;
why->ParseTable[(int)new_24][(int)TK_ASSIGNOP] = 39;
why->ParseTable[(int)new_24][(int)TK_CL] = 39;
why->ParseTable[(int)new_24][(int)TK_DOT] = 38;
why->ParseTable[(int)lowPrecedenceOperators][(int)TK_MINUS] = 62;
why->ParseTable[(int)lowPrecedenceOperators][(int)TK_PLUS] = 61;
why->ParseTable[(int)highPrecedenceOperators][(int)TK_DIV] = 60;
why->ParseTable[(int)highPrecedenceOperators][(int)TK_MUL] = 59;
}


void loadGrammar(struct grammar *G, char *filename){
	FILE *fp = fopen(filename,"r");
	if(fp == NULL){
		printf("NO GRAMMAR FILE !!");
		return;
	}
	char deep[30];
	int lineNo=0;
	int  flag= 1;
	while(1){
		fscanf(fp,"%s",deep);

		if(feof(fp)){
			break;
		}

		if(flag){
			strcpy(G->GrammarArray[lineNo].str,deep) ; // add first and follow too.
            		G->GrammarArray[lineNo].ptr = NULL;
			flag = 0;
		}
               else{
			if(strcmp(deep,";")==0){
				flag = 1;
				lineNo++;
				continue;
			}else{
				struct small *f=(struct small *) malloc(sizeof(struct small)) ;
               			 strcpy(f->str,deep) ;
       			         f->next=NULL ;
                		struct node *d = &G->GrammarArray[lineNo] ;
                		if(d->ptr==NULL) { // add to first node if empty.
                    			d->ptr = f ;
                    			}
              	    	        else {
                    			struct small *ptr1 = d->ptr ;
                    			while(ptr1->next != NULL) { // otherwise add in last.
                       		 		ptr1 = ptr1->next ;
                    			}
                   	 		ptr1->next=f ;
                		      }

			      }
		     }
	}
}

void printGrammar(struct grammar* G)
{
    int i=0;
    struct node temp ;
    struct small* key;
    for(i=0;i<88;i++)
    {
      temp= G->GrammarArray[i];
      printf("\n %d. %s ->",i,temp.str);
      key = temp.ptr;
      if(key==NULL)
        printf("\n");
      else{
        while(key!=NULL)
        {
            printf("%s",key->str);
            key = key->next;
        }
      }     
    }
}



int isLeaf(char* str)
{
    if(str[0]=='<')
        return 0;
    else if(str[0]=='T')
        return 1;
    else if(str[0]=='E')
        return 1;
    else return 2;
}



// Need to write proper error statements
// add Tree Part.
struct ParseTree *parseInputSourceCode(TOKEN *testcaseFile, struct table *T, struct grammar *G) {

// make a new stack and return the parse tree.
    TOKEN *temp = testcaseFile ;

    struct stack s ;
    s.top=-1 ;
    int p;
    for(p=0;p<100;p++) {
    s.stArray[p] = (char *) malloc(sizeof(char)) ;
    s.trArray[p] = (struct ParseTree*) malloc(sizeof(struct ParseTree));
    }
    struct ParseTree *dollar = (struct ParseTree *) malloc(sizeof(struct ParseTree)) ;
     dollar->isLeaf = 0;
     strcpy(dollar->lexeme ,"$") ;
     dollar->lineNumber=-1;
     dollar->parentPTR = dollar;
     dollar->ruleno=0;
     strcpy(dollar->TokenName,"ROOT");
     int treevar=0;
     for(treevar=0;treevar<20;treevar++)
        dollar->ptr[treevar]= NULL;

    struct ParseTree *program = (struct ParseTree*) malloc(sizeof(struct ParseTree));
    program->isLeaf=isLeaf("<program>");
    strcpy(program->lexeme ,"<program>");
    program->lineNumber=-1;
    program->parentPTR=dollar;
    strcpy(program->TokenName ,"<program>");
    treevar=0;
     for(treevar=0;treevar<20;treevar++)
        program->ptr[treevar]= NULL;
    dollar->ptr[0] = program;
    treevar=0;
     for(treevar=1;treevar<20;treevar++)
        program->ptr[treevar]= NULL;
      char *str1 = (char*)malloc(sizeof(char));
    push(&s,"$",dollar);
    push(&s,"<program>",program);
    while(1)
    {
         str1= getTopOfStack(&s) ;
        //printf("\n Top: %s  \n",str1);
        if(strcmp(str1,"$")==0) {

           if(temp==NULL) {
            printf("SUCCESSFULLY PARSED!! \n") ;
           }

           else {
            printf("ERROR_6: Parser Stack Empty But not the Input File") ;
           }
            break ;
        }

        if(str1[0]=='T'||str1[0]=='E') {
             if(strcmp(str1,temp->token)==0)
              {
                struct ParseTree* leaf =pop(&s);
                strcpy(leaf->lexeme ,temp->string);
                if(str1[0]=='T')
                    strcpy(leaf->TokenName,temp->token);
                else
                    strcpy(leaf->TokenName,"EPSILON");
                leaf->lineNumber = temp->line;
                leaf->ruleno=999;
                int leafvar=0;
                for(leafvar=0; leafvar<20;leafvar++)
                leaf->ptr[leafvar]=NULL;
                temp = temp->next;
              }
              else if(strcmp(str1,"EPSILON")==0)
              {
                pop(&s);
              }
             else
               {
                   printf("ERROR_5:The token %s for lexeme %s does not match at line %d. The expected token here is %s",temp->token,temp->string,temp->line,str1);
                   break;
               }
           }

        else if (str1[0]=='<'){
              int i=0,j=0;
              for(i=0;i<50;i++)
              {
                  if(strcmp(NonTer[i],str1)==0)
                     break;
              }
              for(j=0;j<57;j++)
              {
                  if(strcmp(Terminals[j],temp->token)==0)
                     break;
              } // we have got the coordinates of table entry to look for
              int Ruleno =  T->ParseTable[i][j];
               // printf("i:%d j:%d ruleno:%d \n",i,j,Ruleno);
                if(Ruleno==100) // assuming no rule if 100.
                 {
                     printf("ERROR_7: Error in Parsing could not find rule with given Non Terminal");
                    break;
                 }
                 else{
                    char  RHS[10][30];
                    int po=0;
                    //for(po=0;po<10;po++)
                      //  RHS[po]=(char*) malloc(sizeof(char));
                        struct node key = G->GrammarArray[Ruleno];
                        struct small* om = key.ptr;
                        po=0;
                      //  printf(" adding:");
                        while(om!=NULL)
                        {
                        // printf("%s",om->str);
                         strcpy(RHS[po],om->str);
                         om = om->next;
                         po++;
                        }

                    struct ParseTree* parent = pop(&s);
                    int y=po-1;
                    for(y=po-1;y>=0;y--)
                    {
                     //printf("v: %d %s \n",y,RHS[y]);
                     struct ParseTree* sai= (struct ParseTree*) malloc(sizeof(struct ParseTree));
                     parent->ptr[y]=sai;
                     sai->isLeaf = isLeaf(RHS[y]);
                     strcpy(sai->lexeme,RHS[y]);
                     strcpy(sai->TokenName,RHS[y]);
                     sai->parentPTR = parent;
                     parent->ruleno = Ruleno+1;
		     sai->lineNumber=-1;
                     int jai =0;
                     for(jai=0;jai<20;jai++)
                        sai->ptr[jai]=NULL;
                     push(&s,RHS[y],sai);
                    }
                    //temp= temp->next;
                 }

           }

        else {printf("ERROR_8: Error Caused by Lexer"); return dollar;}
    }

   return dollar;
}

//void printParseTree(struct parseTree  PT) {

void printtree(struct ParseTree* p)
{
    if(p==NULL)
       {
         printf("NULL");
         return;
       }
/*       if(p->isLeaf==0)
     printf("lexeme: %s token: %s line no:---- value :--- parent: %s isLeaf: %d ruleno: %d \n",p->lexeme,"----",p->parentPTR->lexeme,p->isLeaf,p->ruleno);
        else if ((strcmp(p->lexeme,"TK_NUM")==0) || (strcmp(p->lexeme,"TK_NUM") ==0))
     printf("lexeme: %s token: %s line no: %d value :%s parent: %s isLeaf: %d ruleno: %d \n",p->lexeme,p->TokenName,p->lineNumber,p->lexeme,p->parentPTR->lexeme,p->isLeaf,p->ruleno);
        else
     printf("lexeme: %s token: %s line no: %d value :--- parent: %s isLeaf: %d ruleno: %d \n",p->lexeme,p->TokenName,p->lineNumber,p->parentPTR->lexeme,p->isLeaf,p->ruleno);
 */    

printf("lexeme: %s token: %s line no: %d parent: %s isLeaf: %d ruleno: %d \n",p->lexeme,p->TokenName,p->lineNumber,p->parentPTR->lexeme,p->isLeaf,p->ruleno);

	int i=0;
     while(p->ptr[i]!=NULL)
       {
         printtree(p->ptr[i]);
         i++;
       }
     return;
}

void  printParseTree(struct ParseTree* p,FILE* fp)
{
    if(p==NULL)
       {
         printf("NULL");
         return;
       }
       char yesno[5];
       if(p->isLeaf)
         strcpy(yesno,"yes");
        else strcpy(yesno,"no");
       if(p->isLeaf==0)
     fprintf(fp,"lexemeCurrentNode:--- line no:--- token:---  value :--- parent: %s isLeaf: %s NodeSymbol: %s\n",p->parentPTR->lexeme,yesno,p->lexeme);
        else if ((strcmp(p->TokenName,"TK_NUM")==0) || (strcmp(p->TokenName,"TK_RNUM") ==0))
     fprintf(fp,"lexemeCurrentNode:%s line no:%d token:%s  value :%s parent: %s isLeaf: %s NodeSymbol: %s\n",p->lexeme,p->lineNumber,p->TokenName,p->lexeme,p->parentPTR->lexeme,yesno,p->lexeme);
        else if((strcmp(p->TokenName,"EPSILON")==0))
     fprintf(fp,"lexemeCurrentNode:%s line no:--- token:%s  value :--- parent: %s isLeaf: %s NodeSymbol: %s\n",p->lexeme,p->TokenName,p->parentPTR->lexeme,yesno,p->lexeme);
	else
     fprintf(fp,"lexemeCurrentNode:%s line no:%d token:%s  value :--- parent: %s isLeaf: %s NodeSymbol: %s\n",p->lexeme,p->lineNumber,p->TokenName,p->parentPTR->lexeme,yesno,p->lexeme);
     int i=0;
     while(p->ptr[i]!=NULL)
       {
          printParseTree(p->ptr[i],fp);
         i++;
       }
     return;
}



