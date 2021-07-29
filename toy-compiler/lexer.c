
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"lexerDef.h"

TOKEN* STARTNODE=NULL ;
TOKEN* LASTNODE= NULL;

int hashfunction(char* str)
{
    int i=0, val=0;
    while(str[i]!='\0')
    {
     val = val+ str[i];
      i++;
    }
    return val%30 ;
}

int equals(char* s1, char*s2)
{
    int i=0;
    while((s1[i]==s2[i]) &&s1[i]!= '\0'&&s2[i]!='\0')
    {
        i++;
    }
    if(s1[i]=='\0' && s2[i]=='\0')
        return 1;
    else return 0;
}

void getStream(FILE *fp, buffer *B, buffersize k)
{

   int nbytes = fread(B->buff, 1, 10000, fp);
   B->size = nbytes;
  /*char c =(char) getc(fp);
  while(c!=EOF || ((B->size)==k))
  {
      B->buff[B->size]= c;
      B->size++;
      c = getc(fp);
  }
  if(c==EOF)
  {
      B->buff[B->size]= c;
      B->size++;
  }
*/
  
}


void addEntry(HTABLE* t, char* token, char* inputstring,int tkno)
{
    int i=0, j=0;
  ENTRY* temp = (ENTRY*) malloc(sizeof(ENTRY));
  while(token[i]!='\0')
        {
            temp->token[i] = token[i];
            i++;
        }
        temp->token[i]= '\0';
        // adding the input string.
        while(inputstring[j]!='\0')
        {
            temp->inputstring[j] = inputstring[j];
            j++;
        }
        temp->inputstring[j]= '\0';

  temp-> value = hashfunction(inputstring);
  temp->tkno = tkno;
  temp->next =NULL;
  ENTRY* key = t->ent[temp->value];
  if(key==NULL)
        {
            t->ent[temp->value] = temp;
        }
  else{
    while(key->next!=NULL)
    {
      key = key -> next;
    }
    key->next = temp;
  }
}


void populateTable(HTABLE* t)
{
  addEntry(t,"TK_WITH","with",31);
  addEntry(t,"TK_PARAMETERS","parameters",32);
  addEntry(t,"TK_END","end",33);
  addEntry(t,"TK_WHILE","while",34);
  addEntry(t,"TK_INT","int",35);
  addEntry(t,"TK_REAL","real",36);
  addEntry(t,"TK_TYPE","type",37);
  addEntry(t,"TK_MAIN","_main",38);
  addEntry(t,"TK_GLOBAL","global",39);
  addEntry(t,"TK_PARAMETER","parameter",40);
  addEntry(t,"TK_LIST","list",41);
  addEntry(t,"TK_INPUT","input",42);
  addEntry(t,"TK_OUTPUT","output",43);
  addEntry(t,"TK_ENDWHILE","endwhile",44);
  addEntry(t,"TK_IF","if",45);
  addEntry(t,"TK_THEN","then",46);
  addEntry(t,"TK_ENDIF","endif",47);
  addEntry(t,"TK_READ","read",48);
  addEntry(t,"TK_WRITE","write",49);
  addEntry(t,"TK_RETURN","return",50);
  addEntry(t,"TK_CALL","call",51);
  addEntry(t,"TK_RECORD","record",52);
  addEntry(t,"TK_ENDRECORD","endrecord",53);
  addEntry(t,"TK_ELSE","else",54);
  return;
}

// returns the token if not newline, whitespace or comment.
// returns NULL if white space or newline or comment.

TOKEN* tokenInit(char* token , char* inputstring ,int line, int tkno)
{
   int i=0, j=0;
   if(inputstring[0] ==' ' ||inputstring[0] =='%'||inputstring[0] =='\n'||inputstring[0] =='\r' || inputstring[0] =='\t')
   {
     return NULL;
   }
   else
   {
        TOKEN* temp = (TOKEN*) malloc(sizeof(TOKEN));
        temp->line =line;
        temp ->tkno =tkno;
        while(token[i]!='\0')
        {
            temp->token[i] = token[i];
            i++;
        }
        temp->token[i]= '\0';
        // adding the input string.
        while(inputstring[j]!='\0')
        {
            temp->string[j] = inputstring[j];
            j++;
        }
        temp->string[j]= '\0';

        // adding to the last of the linked list
        // if list empty
        if(STARTNODE==NULL)
           {
             STARTNODE = temp;
             LASTNODE = temp;
             LASTNODE->next=NULL;
             return temp;
           }
        else
        {
         LASTNODE->next=temp;
         LASTNODE= LASTNODE->next;
         LASTNODE ->next = NULL;
         return temp;
        }
   }
}



/* This function takes care of printing the Error present based on the type.
*/

int lex_Error(buffer *B,int start, int i,int type,int line)
{
    char s[21] = {'\0'};   
	int j;
     for(j=start;j<=i;j++)
       {
         s[j-start]=B->buff[j];
       }
    s[j]='\0';
    switch(type)
    {
        case 1 : printf("\n ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters",line);
                 break;
        case 2 : printf("\n ERROR_2: Unknown Symbol '%s' at line %d ",s,line);
                 break;
        case 3 : printf("\n ERROR_3:  Unknown pattern '%s' at line %d ",s, line);
                 break;

    }
    int temp=i;
    while(temp<=(B->size-1)){
    char look = B->buff[temp];
    if(look==' '||look=='\n'||look=='\r'||look=='\t')
     break;
    else
     temp++; 
    } 
    printf("\n start:%d stop:%d temp:%d \n",start,i,temp);
    return temp;
}


/*
  searches for the input string in the table:
  if present then creates token and return the address of token.
  otherwise, it creates entry into the table and then creates token and return the address of token.
*/
TOKEN* searchToken(HTABLE *t, char *s,char * probableToken,int line, int tkno)
{
  int val= hashfunction(s);
   ENTRY* temp = t->ent[val];

   while(temp!=NULL)
   {
     if(equals(temp->inputstring ,s ))
        return tokenInit(temp->token,s,line,temp->tkno);
     else
        temp = temp->next;
   }
   if(temp==NULL)
   {
    addEntry(t,probableToken,s,tkno);
   return tokenInit(probableToken,s,line,tkno);
   }
   return NULL;
}


// thought of putting a recursive getStream() for very k chars input till we get EOF
// we are just using i++ but if we are at the last of the buffer then our code not valid.
// left the a-z and b-e part of the DFA.**************
// returns null for whitespace, newline,comment.
// NOT Dealt with EOF.
TOKEN *getNextToken(HTABLE* t, buffer *B,int *start, int *stop,int *line, TOKEN* ERROR)
{
  char c;
  c = B->buff[*start] ;
  int i =*start;
  char s[21];
  char ff[2];
  switch(c)   {

  case ')' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_CL",")",*line,0) ; // write tokenInit function that initializes a token and returns a pointer to the token
            break ;

  case '&' :

            if ((c=B->buff[++i]) == '&') {
                if ((c=B->buff[++i]) == '&') { // i is the string seen uptil now

                    *stop = ++i ; // stop is the string next to be seen
                    return tokenInit("TK_AND","&&&",*line,1) ;
                }
                else  {
                   *stop = lex_Error(B,*start, i,3,*line ) ;
                    return ERROR ;
                }
            }
            else  {
                *stop = lex_Error(B,*start, i,3,*line ) ; 
                return ERROR ;
            }
            break ;

  case '@' :
            if ((c=B->buff[++i]) == '@') {
                if ((c=B->buff[++i]) == '@') { // i is the string seen uptil now

                    *stop = ++i ; // stop is the string next to be seen
                    return tokenInit("TK_OR","@@@",*line,2) ;
                    }
                else  {
                    *stop = lex_Error(B,*start, i,3,*line ) ;
                    return ERROR ;
                }
            }
            else  {
                *stop = lex_Error(B,*start, i,3,*line ) ; 
                return ERROR ;
            }
            break ;

  case '!' :

            if ((c=B->buff[++i]) == '=') { // i is the string seen uptil now

                *stop = ++i ; // stop is the string next to be seen
                return tokenInit("TK_NE","!=",*line,3) ;
            }
            else  {
                *stop = lex_Error(B,*start, i,3,*line ) ;
                return ERROR ;
            }
            break ;

  case '#' :
             s[0]='#' ;
            c=s[1]=B->buff[++i]  ;
            if(c>='a'&&c<='z') {
                while (c>='a'&&c<='z') {

                    i++ ;
                    if(i-*start+1 > 20) {
                    *stop = lex_Error(B,*start, i,1,*line ) ;
                        return ERROR ;
                    }
                    c=s[i-(*start)]=B->buff[i]  ;
                }
                s[i-*start]='\0' ;
                i-- ; // backtracking
                *stop=++i ;

                return tokenInit("TK_RECORDID",s,*line,4) ;
            }
            else  {
               *stop = lex_Error(B,*start, i,3,*line ) ;
                return ERROR ;
            }
            break ;

 case '+' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_PLUS","+",*line,5) ; // write tokenInit function that initializes a token and returns a pointer to the token
            break ;

 case '>' :

            if ((c=B->buff[++i]) == '=') { // i is the string seen uptil now

            *stop = ++i ; // stop is the string next to be seen
            return tokenInit("TK_GE",">=",*line,6) ;
            }
            else  {
            i--; // backtracking
            *stop = ++i ; // stop is the string next to be seen
            return tokenInit("TK_GT",">",*line,7) ;
            }
            break;

 case ':' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_COLON",":",*line,8) ; 
            break ;

 case '-' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_MINUS","-",*line,9) ; // write tokenInit function that initializes a token and returns a pointer to the token
            break ;

 case '*' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_MUL","*",*line,10) ; // write tokenInit function that initializes a token and returns a pointer to the token
            break ;

 case '=' :

            if ((c=B->buff[++i]) == '=') { // i is the string seen uptil now

            *stop = ++i ; // stop is the string next to be seen
            return tokenInit("TK_EQ","==",*line,11) ;
            }
            else  {
                *stop = lex_Error(B,*start, i,3,*line ) ;
                return ERROR ;
            }
            break ;


  case '_':
             s[0]='_' ;
            c=s[1]=B->buff[++i]  ;
            if((c>='a'&&c<='z')|| (c>='A'&& c<='Z')) {
                while ((c>='a'&&c<='z')|| (c>='A'&& c<='Z')) {

                    i++ ;
                    if(i-*start+1 > 20) {
                    *stop = lex_Error(B,*start, i,1 ,*line) ;
                        return ERROR ;
                    }
                    c=s[i-(*start)]=B->buff[i]  ;
                }
                if(c<='9'&& c>='0')
                {
                  while (c>='0'&&c<='9') {

                    i++ ;
                    if(i-*start+1 > 20) {
                    *stop = lex_Error(B,*start, i,1,*line ) ;
                        return ERROR ;
                    }
                    c=s[i-(*start)]=B->buff[i]  ;
                  }
                }
                s[i-*start]='\0' ;
                i-- ; // backtracking
                *stop=++i ;
// *TEMPORARY ****************************************************************************************************************************
                return searchToken(t,s,"TK_FUNID",*line,12) ;  // we need to write a search_token function that will search the hashtable and if no token present matching then return the most possible token from input arg.
            }
            else  {
                *stop = lex_Error(B,*start, i,3,*line ) ;
                return ERROR ;
            }
            break ;

 case '[' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_SQL","[",*line,13) ;
            break ;

 case ']' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_SQR","]",*line,14) ;
            break ;

 case ',' : // Not included in the main grammar but present in the errata.
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_COMMA",",",*line,15) ;
            break ;

 case ';' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_SEM",";",*line,16) ; // write tokenInit function that initializes a token and returns a pointer to the token
            break ;

 case '<' :

            if ((c=B->buff[++i]) == '=') { // i is the string seen uptil now

            *stop = ++i ; // stop is the string next to be seen
            return tokenInit("TK_LE","<=",*line,17) ;
            }
            else if(c == '-'){
              if ((c=B->buff[++i]) == '-'){
                if ((c=B->buff[++i]) == '-'){
                    *stop = ++i ; // stop is one more than what we have read in the input buffer.
                    return tokenInit("TK_ASSIGNOP","<---",*line,18);
                }
                else {
                   *stop = lex_Error(B,*start, i,3,*line ) ;
                return ERROR ;
                }
              }
              else{
                *stop = lex_Error(B,*start, i,3 ,*line) ;
                return ERROR ;
              }
            }
            else  {
            i--; // backtracking
            *stop = ++i ; // stop is the string next to be seen
            return tokenInit("TK_LT","<",*line,19) ;
            }
            break;

 case '(' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_OP","(",*line,20) ;
            break ;


 case '~' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_NOT","~",*line,21) ;
            break ;


 case '/' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_DIV","/",*line,22) ;
            break ;

 case '.' :
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_DOT",".",*line,23) ;
            break ;
//******** Special cases: we should not add comments, newline and white spaces in the tokenInit section. ***************************
 case '\n' :
            *line = *line+1;
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_NL","\n",*line-1,24) ;
            break ;

  case '%' : while( c != '\n')   // read the comment till we get a new line.then increment line.
             {
                 c=B->buff[++i];
             }
             *line= *line+1;
             *stop = ++i ; // stop is the string next to be seen
             return tokenInit("TK_COMMENT","%",*line-1,25) ;
            break;

 case ' ' :
            ff[0]=' ';
            ff[1]='\0'; 
	    *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_SPACE",ff,*line,26) ;
            break ;
 case '\r' :
            ff[0]='\r';
            ff[1]='\0';
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_SPACE",ff,*line,26) ;
            break ;
 case '\t' :
            ff[0]='\t';
            ff[1]='\0'; 
            *stop = ++i ; // stop is one more than what we have read in the input buffer.
            return tokenInit("TK_SPACE",ff,*line,26) ;
            break ;

 // ********************************************************************************

default :  //do we need to store only 20 chars for numbers also.
         if( c<='9'&& c>='0' ){
            char s[21]; s[0]=c ;
            c=s[1]=B->buff[++i]  ;
                while (c>='0'&&c<='9') {
                    i++ ;
                    if(i-*start+1 > 20) {
                   *stop = lex_Error(B,*start, i,1 ,*line) ;
                        return ERROR ;
                    }
                    c=s[i-(*start)]=B->buff[i]  ;
                }
                if(c=='.')
                {
                 i++ ;
                    if(i-*start+1 > 20) {
                    *stop = lex_Error(B,*start, i,1,*line ) ;
                        return ERROR ;
                    }
                    c=s[i-(*start)]=B->buff[i]  ;
                    if(c>='0'&&c<='9'){
                        while (c>='0'&&c<='9') {
                         i++ ;
                         if(i-*start+1 > 20) {
                            *stop = lex_Error(B,*start, i,1 ,*line) ;
                            return ERROR ;
                          }
                         c=s[i-(*start)]=B->buff[i]  ;
                        }

                         s[i-*start]='\0' ;
                        i-- ; // backtracking
                        *stop=++i ;

                        return tokenInit("TK_RNUM",s,*line,27);

                    }
                    else {
                      *stop = lex_Error(B,*start, i,3 ,*line) ;
                            return ERROR ;
                    }

                }
                else {
                    s[i-*start]='\0' ;
                    i-- ; // backtracking
                    *stop=++i ;
                    return tokenInit("TK_NUM",s,*line,28) ;
                }

            break ;
            }
            // if part of b-d
            else if(c<='d'&& c>='b')
            {
                s[0]=c ;
                c=s[1]=B->buff[++i]  ;
                if(c>='a'&&c<='z') {
                    while (c>='a'&&c<='z') {

                        i++ ;
                        if(i-*start+1 > 20) {
                            *stop = lex_Error(B,*start, i,1 ,*line) ;
                            return ERROR ;
                        }
                        c=s[i-(*start)]=B->buff[i]  ;
                    }
                    s[i-*start]='\0' ;
                    i-- ; // backtracking
                    *stop=++i ;
                    return searchToken(t,s,"TK_FIELDID",*line,29);
                }
                else if(c<='7' && c>='2')
                {
                 c=s[2]=B->buff[++i]  ;
                  if(c>='b'&&c<='d') {
                    while (c>='b'&&c<='d') {

                        i++ ;
                        if(i-*start+1 > 20) {
                            *stop = lex_Error(B,*start, i,1 ,*line) ;
                            return ERROR ;
                        }
                        c=s[i-(*start)]=B->buff[i] ;
                        }
                    if(c>='2'&&c<='7')
                        {
                            while (c>='2'&&c<='7') {

                                i++ ;
                                if(i-*start+1 > 20) {
                                    *stop = lex_Error(B,*start, i,1 ,*line) ;
                                    return ERROR ;
                                }
                                c=s[i-(*start)]=B->buff[i]  ;
                            }
                            s[i-*start]='\0' ;
                            i-- ; // backtracking
                            *stop=++i ;
                            return searchToken(t,s,"TK_ID",*line,30);

                        }
                    s[i-*start]='\0' ;
                    i-- ; // backtracking
                    *stop=++i ;
                    return searchToken(t,s,"TK_ID",*line,30);

                }
                else if(c>='2'&&c<='7')
                {
                            while (c>='2'&&c<='7') {

                                i++ ;
                                if(i-*start+1 > 20) {
                                    *stop = lex_Error(B,*start, i,1 ,*line) ;
                                    return ERROR ;
                                }
                                c=s[i-(*start)]=B->buff[i]  ;
                            }
                            s[i-*start]='\0' ;
                            i-- ; // backtracking
                            *stop=++i ;
                            return searchToken(t,s,"TK_ID",*line,30);
                }
                else{
                            s[i-*start]='\0' ;
                            i-- ; // backtracking
                            *stop=++i ;
                            return searchToken(t,s,"TK_ID",*line,30);
                }
            }
                            s[i-*start]='\0' ;
                            i-- ; // backtracking
                            *stop=++i ;
                            return searchToken(t,s,"TK_FIELDID",*line,29);
        }
        // a/e-z part of DFA
        else if((c=='a')|| (c<='z'&&c>='e'))
        {
                s[0]=c ;
                c=s[1]=B->buff[++i]  ;
                if(c>='a'&&c<='z') {
                    while (c>='a'&&c<='z') {

                        i++ ;
                        if(i-*start+1 > 20) {
                           *stop = lex_Error(B,*start, i,1 ,*line) ;
                            return ERROR ;
                        }
                        c=s[i-(*start)]=B->buff[i]  ;
                    }
                    s[i-*start]='\0' ;
                    i-- ; // backtracking
                    (*stop)=++i ;
                    return searchToken(t,s,"TK_FIELDID",*line,29);
                }
                else{
                    s[i-*start]='\0' ;
                    i-- ; // backtracking
                    *stop=++i ;
                    return searchToken(t,s,"TK_FIELDID",*line,29);
                }
        }

        else if(c==EOF)
                    return NULL;
        else {
               if(c=='\0')
                printf("EOF");
              *stop = lex_Error(B,*start, i, 2,*line ) ;
              *stop =++i;
	      return ERROR ;
            }

  }
  return NULL;
}

void printall()
{
  TOKEN* temp = STARTNODE;
  if(STARTNODE==NULL)
   { printf("List Empty !!!!");}
  while(temp != NULL)
  {
     printf(" %s %s at line %d \n", temp->token,temp->string, temp->line);
     temp = temp->next;
  }
}


void commentfreecode(buffer* B)
{
    int i=0;
    while(i!=B->size && B->buff[i]!=EOF )
    {
        if(B->buff[i]=='%')
        {
            while(B->buff[i]!='\n')
                i++;
        }
        printf("%c",B->buff[i]);
        i++;
    }
}





