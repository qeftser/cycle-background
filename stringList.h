

#ifndef STRINGS

#define STRINGS

struct stringList { int head; int tail; int size; char *string; };
struct stringList *makeStringList(int);
struct stringList *adjustStringList(struct stringList *);
struct stringList *shiftStringList(struct stringList *);
void pshSL(char, struct stringList *);
char popSL(struct stringList *);
void addSL(char, struct stringList *);
char remSL(struct stringList *);
char fstSL(struct stringList *);
char lstSL(struct stringList *);
void printSL(struct stringList *);
char *f_toStringSL(struct stringList *);
char *r_toStringSL(struct stringList *);
char *fileToString(char *);
int eqlSL(char *, struct stringList *);

#endif
