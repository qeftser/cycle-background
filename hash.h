

#ifndef  HASH

#define  HASH

struct hashEntry { char *key; char *element; struct hashEntry *next; };
struct hashTable { int size; int capacity; struct hashEntry **elements; };
struct hashTable *makeHashTable(int);
struct hashEntry *makeHashEntry(char *, char *);
int hashStr(char *);
void addHT(char *, char *, struct hashTable *);
char *getHT(char *, struct hashTable *);
void remHT(char *, struct hashTable *);
void printHT(struct hashTable *);
void printKeysHT(struct hashTable *);
char *randElementHT(struct hashTable *);

#endif
