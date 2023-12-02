#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct stringList { int head; int tail; int size; char *string; };

/* This is an arrayList that kind of just functions like a stack and a queue
 * at the same time. It will work for what I want to do and it only really
 * accepts characters.
 * Becuase of this, the add method is o(n) while all the others are o(1). So
 * I will just have to aviod access patterns that make heavy use of add. */

struct stringList *makeStringList(int size) {
   struct stringList *newSL = malloc(sizeof(struct stringList));
   if (newSL == NULL) {
      fprintf(stderr, "ERROR: Cannot allocate memory in makeStringList\n");
      exit(EXIT_FAILURE);
   }
   newSL->head = newSL->tail = 0;
   newSL->size = size;
   newSL->string = malloc(sizeof(char)*size);
   if (newSL->string == NULL) {
      fprintf(stderr, "ERROR: Cannot allocate memory in makeStringList\n");
      exit(EXIT_FAILURE);
   }
   return newSL;
}

struct stringList *adjustStringList(struct stringList *sl) {
   if (sl->tail == sl->size) {
      if (sl->head != 0) {
         int n = sl->tail - sl->head;
         for (int i = 0; i < n; i++)
            *(sl->string+i) = *(sl->string+(i+sl->head));
         sl->tail -= sl->head;
         sl->head = 0;
      }
      else {
         sl->string = realloc(sl->string, sl->size*2);
         if (sl->string == NULL) {
            fprintf(stderr, "ERROR: Cannot allocate memory in maybeResizeStringList\n");
            exit(EXIT_FAILURE);
         }
         sl->size *= 2;
      }
   }
   return sl;
}

struct stringList *shiftStringList(struct stringList *sl) {
   int n = sl->tail - sl->head;
   for (int i = n; i > sl->head; i--) 
      *(sl->string+i) = *(sl->string+(i - 1));
   sl->tail++;
   sl->head++;
   return sl;
}
      
void pshSL(char element, struct stringList *sl) {
   sl = adjustStringList(sl);
   *(sl->string+(sl->tail++)) = element;
}

char popSL(struct stringList *sl) {
   if (sl->tail == sl->head)
      return '\0';
   return *(sl->string+(--(sl->tail)));
}

void addSL(char element, struct stringList *sl) {
   if (sl->head != 0) {
      *(sl->string+(--(sl->head))) = element;
   }
   else if (sl->tail != sl->size) {
      sl = shiftStringList(sl);
      *sl->string = element;
      sl->head--;
   }
   else {
      sl = shiftStringList(adjustStringList(sl));
      *sl->string = element;
      sl->head--;
   }
}

char remSL(struct stringList *sl) {
   if (sl->head == sl->tail) 
      return '\0';
   return *(sl->string+(sl->head++));
}

char fstSL(struct stringList *sl) {
    if (sl->head == sl->tail)
       return '\0';
    return *(sl->string+sl->head);
}

char lstSL(struct stringList *sl) {
   if (sl->tail == sl->head) 
      return '\0';
   return *(sl->string+(sl->tail-1));
}

void printSL(struct stringList *sl) {
   int n = sl->tail - sl->head;
   for (int i = 0; i < n; i++) {
      printf("%c", *(sl->string+(i + sl->head)));
   }
   printf("\n");
}

char *f_toStringSL(struct stringList *sl) {
   int i, n = sl->tail - sl->head;
   char *ret = malloc(sizeof(char)*(n + 1));
   for (i = 0; i < n; i++) {
      char j = remSL(sl);
      *(ret + i) = j;
   }
   *(ret + i) = '\0';
   free(sl);
   return ret;
}
   
char *r_toStringSL(struct stringList *sl) {
   int i, n = sl->tail - sl->head;
   char *ret = malloc(sizeof(char)*(n + 1));
   for (i = 0; i < n; i++) {
      char j = popSL(sl);
      *(ret + i) = j;
   }
   *(ret + i) = '\0';
   free(sl);
   return ret;
}

