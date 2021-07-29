#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

struct small {
char str[30] ;
struct small *next;
};


struct first {
char *str ;
struct first *next ;
};

struct follow {
char *str ;
struct follow *next ;
};


struct followset {
struct follow *arr[88] ;
};

struct firstset {
struct first *arr[88] ;
};

struct node {
char str[30] ; // name of the non-terminal
//char *follow[10] ;
struct small *ptr ;
};


struct grammar {
struct node GrammarArray[88] ;
};


struct table {
int ParseTable[50][57];
};

enum NonTerminals {program,mainFunction,otherFunctions,function,input_par,output_par,parameter_list,dataType,primitiveDatatype,
constructedDatatype,remaining_list,stmts,typeDefinitions,typeDefinition,fieldDefinitions,fieldDefinition,moreFields,declarations,declaration,
global_or_not,otherStmts,stmt,assignmentStmt,singleOrRecId,new_24,funCallStmt,outputParameters,inputParameters,
iterativeStmt,conditionalStmt,elsePart,ioStmt,allVar,arithmeticExpression,expPrime,term,termPrime,factor,highPrecedenceOperators,
lowPrecedenceOperators,all,temp=41,booleanExpression,var,logicalOp,relationalOp,returnStmt,optionalReturn,idList,more_ids} ;

enum Terminals {TK_CL,TK_AND,TK_OR,TK_NE,TK_RECORDID,TK_PLUS,TK_GE,TK_GT,TK_COLON,TK_MINUS,TK_MUL,TK_EQ,TK_FUNID,TK_SQL,TK_SQR,
TK_COMMA,TK_SEM,TK_LE,TK_ASSIGNOP,TK_LT,TK_OP,TK_NOT,TK_DIV,TK_DOT,TK_NL,TK_COMMENT,TK_SPACE,TK_RNUM,TK_NUM,
TK_FIELDID,TK_ID,TK_WITH,TK_PARAMETERS,TK_END,TK_WHILE,TK_INT,TK_REAL,TK_TYPE,TK_MAIN,TK_GLOBAL,TK_PARAMETER,
TK_LIST,TK_INPUT,TK_OUTPUT,TK_ENDWHILE,TK_IF,TK_THEN,TK_ENDIF,TK_READ,TK_WRITE,TK_RETURN,TK_CALL,TK_RECORD,TK_ENDRECORD,TK_ELSE,DOLLAR,EPSILON} ;

struct stack {
int top ;
char* stArray[100] ;
struct ParseTree* trArray[100];
};

struct ParseTree {
int isLeaf ;
char lexeme[30] ;
int lineNumber ;
int ruleno;
char TokenName[30] ;
struct ParseTree *ptr[20] ;
struct ParseTree *parentPTR ;
} ;


#endif // PARSERDEF_H_INCLUDED
