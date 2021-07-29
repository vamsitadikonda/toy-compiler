
void populateRecord(struct AsTree *tree, struct RecordTypes RL);

void populateRecordList(struct AsTree *tree, struct RecordList* RL);

void printRecordList(struct RecordList* RL ); 

void populateFuncHT(struct AsTree *tree,struct funcHT *ht, struct outerHT* OST, struct RecordList* RL);

void populateST(struct AsTree* tree,struct outerHT* OST, struct RecordList* RL); 

void printSymbolTable(struct outerHT* OST);
