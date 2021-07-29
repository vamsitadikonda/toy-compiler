

struct STnode {
char type[10] ;
char id[20] ;
int offset ;
struct STnode *ptr ;
};


struct funcHT {
char funcID[20] ;
int stcount;
struct STnode *arr[50] ;
};

struct outerHT {
int funcno;
struct funcHT *outerarr[100] ;
};


struct fields
{
 char datatype[30];
 char fieldid[30];
};


struct RecordTypes
{
 char recordid[30];
 int fieldno;
 struct fields* fieldarr[50]; 
};

struct RecordList
{
 int recordno;
 struct RecordTypes* arr[20]; 
};

