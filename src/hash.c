#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* It's a string hash table :) */
struct hashEntry { char *key; char *element; struct hashEntry *next; };
struct hashTable { int size; int capacity; struct hashEntry **elements; };

/* try and make the size a prime number for better performance */
struct hashTable *makeHashTable(int size) {
   struct hashTable *newHT = malloc(sizeof(struct hashTable));
   if (NULL == newHT) {
      fprintf(stderr, "ERROR: Unable to allocate memory in makeHashTable\n");
      exit(EXIT_FAILURE);
   }
   newHT->size = size;
   newHT->capacity = 0;
   newHT->elements = malloc(sizeof(struct hashEntry)*size);
   if (NULL == newHT->elements) {
      fprintf(stderr, "ERROR: Unable to allocate memory in makeHashTable\n");
      exit(EXIT_FAILURE);
   }
   for (int i = 0; i < size; i++)
      newHT->elements[i] = NULL;
   return newHT;
}

struct hashEntry *makeHashEntry(char *key, char *element) {
   struct hashEntry *newHE = malloc(sizeof(struct hashEntry));
   if (NULL == newHE) {
      fprintf(stderr, "ERROR: Unable to allocate memory in makeHashEntry\n");
      exit(EXIT_FAILURE);
   }
   newHE->next = NULL;
   newHE->key = key;
   newHE->element = element;
   return newHE;
}

int hashStr(char *key) {
   int idx = 9196283, i=0;
   while (*(key+i) != '\0') {
      idx ^= *(key+i) * 14660237;
      i++;
   }
   return idx;
}

void addHT(char * key, char * element, struct hashTable *ht) {
   int idx = hashStr(key) % ht->size;
   if (ht->elements[idx] == NULL) {
      struct hashEntry *he = makeHashEntry(key, element);
      ht->elements[idx] = he;
      ht->capacity++;
   }
   else {
      struct hashEntry *curr = ht->elements[idx];
      if (curr->next == NULL && strcmp(curr->key, key)==0) {
         curr->element = element;
         return;
      }
      while (curr->next != NULL) {
         if (strcmp(curr->key,key)==0) {
            curr->element = element;
            return;
         }
         curr = curr->next;
      }
      struct hashEntry *he = makeHashEntry(key, element);
      curr->next = he;
      ht->capacity++;
   }
}

char * getHT(char * key, struct hashTable *ht) {
   int idx = hashStr(key) % ht->size;
   struct hashEntry *curr = ht->elements[idx];
   while (curr != NULL) {
      if (strcmp(curr->key,key)==0)
         return curr->element;
      curr = curr->next;
   }
   return "\0";
}

void remHT(char * key, struct hashTable *ht) {
   int idx = hashStr(key) % ht->size;
   struct hashEntry *curr = ht->elements[idx], *prev = NULL;
   while (curr != NULL) {
      if (strcmp(curr->key,key)==0) {
         if (prev == NULL) {
            ht->elements[idx] = curr->next;
            free(curr);
            ht->capacity--;
            return;
         }
         else {
            prev->next = curr->next;
            free(curr);
            ht->capacity--;
            return;
         }
      }
      prev = curr;
      curr = curr->next;
   }
}

char *randElementHT(struct hashTable *ht) {
   struct hashEntry *val;
   while((val = *(ht->elements+(rand()%(ht->size)))) == NULL);
   struct hashEntry *iter = val;
   int len = 0;
   while (iter != NULL) {
      iter = iter->next;
      len++;
   }
   int pos = rand()%len;
   while (pos--) {
      val = val->next;
   }
   return val->element; 
}

void printHT(struct hashTable *ht) {
   struct hashEntry *curr;
   printf("+\n");
   for (int i = 0; i < ht->size; i++) {
      printf(": ");
      curr = ht->elements[i];
      while(curr != NULL) {
         printf("[%s, %s] ", curr->key, curr->element);
         curr = curr->next;
      }
      printf(" |\n");
   }
   printf("+\n");
}

void printKeysHT(struct hashTable *ht) {
   struct hashEntry *curr;
   for (int i = 0; i < ht->size; i++) {
      curr = ht->elements[i];
      while(curr != NULL) {
         printf("%s\n", curr->key);
         curr = curr->next;
      }
   }
}
         

