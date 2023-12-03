#define _CRT_SECURE_NO_WARNINGS

#include "hash.h"
#include "stringList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void cycleSingleRand(struct hashTable *);
void cycleMultiRand(struct hashTable *);
void cycleToVal(char *, struct hashTable *);
int argsContain(char *, char **, int);
struct hashTable *loadEntries(char *);

int main(int argc, char **argv) {

  /* getenv("USERPROFILE") gets your local directory. If you want to change
   * the route from there, edit the second option in strcat
   */
  char *imagePath = malloc(sizeof(char)*300);
  strcat(imagePath, getenv("USERPROFILE"));
  strcat(imagePath, "\\AppData\\Local\\Packages\\Microsoft.WindowsTerminal_"
                    "8wekyb3d8bbwe\\LocalState\\images.txt");

  srand(time(NULL));

  if (argc == 2 && argsContain("--version", argv, argc)) {
     printf("Cycle Background\nVersion 1.0\nWritten by qeftser\n");
     exit(EXIT_SUCCESS);
  }
  else if (argc == 3 && argsContain("--help", argv, argc) && argsContain("--route", argv, argc)) {
      printf("The route to the image file is compiled into the program. To change it\n");
      printf("get the files off of github at https://github.com/qeftser/cycle-background.\n");
      printf("Go to the file cycle.c and change the variable imagePath in main to the path\n");
      printf("you want. Then recompile with cycle.c, hash.c, and stringList.c\n");
      exit(EXIT_SUCCESS);
  }
  else if (argc == 3 && argsContain("--help", argv, argc) && argsContain("--broken", argv, argc)) {
     printf("There are a couple of options here. I use the program pretty often so there is\n");
     printf("a chance I fixed the change in the latest version. Get it off of github at:\n");
     printf("    https://github.com/qeftser/cycle-background\n");
     printf("There is also a chance that the compiled instructions don't work with your\n");
     printf("computer architecture. Try compiling the program on your machine.\n");
     printf("If neither of those options work, open an issue on github and I will\n");
     printf("hopefully take a look at it :)\n");
     exit(EXIT_FAILURE);
  }
  else if (argc == 3 && argsContain("--help", argv, argc) && argsContain("--daily", argv, argc)) {
     printf("You can use task manager in windows to have this command run every day. Search\n");
     printf("task manager on your machine and add a new task that runs this program each\n");
     printf("day. There is plenty of information on using task manager avaliable online if\n");
     printf("you get stuck. I just wanted to throw the option out here for anyone who might\n");
     printf("be unaware :)\n");
     exit(EXIT_SUCCESS);
  }
  else if (argc == 4 && argsContain("--help", argv, argc) && argsContain("--format", argv, argc) && argsContain("--template", argv, argc)) {
     printf("Generating template in %s\n", imagePath);
     FILE *flptr = fopen(imagePath, "w");
     char *template = "-[name] [image path]\n"
                      "example-name-1 \"path/to/image/in/quotes\"\n"
                      "example-name-2,\"path/to/image/2/in/quotes\"\n"
                      "example-name-3, , , \"this/would/still/parse\"\n"
                      "this-line-would-be-skipped\n"
                      "example-name-4, \"this/line/would/still/be/processed\"\n";
     while (*template++ != '\0')
        putc(*template,flptr);
     fclose(flptr);
     exit(EXIT_SUCCESS);
  }
  else if (argc == 3 && argsContain("--help", argv, argc) && argsContain("--format", argv, argc)) {
     printf("Your image options file is what is pulled from when selecting an\n");
     printf("image to set the background to. If your program is crashing with\n");
     printf("an error about not being able to find a file, your image file is\n");
     printf("likely in the wrong spot.\n");
     printf("The current route to the image file is:\n");
     printf("    %s\n", imagePath);
     printf("Check if your image file is placed there and matches the file name.\n\n");
     printf("If the command fails to run for a different reason, it could be that\n");
     printf("your image file is not formatted properly.\n");
     printf("The correct format for each line of the image file is:\n");
     printf("[name] [,| ] \"[image path]\"\n");
     printf("Each line should contain a name, which can be used to set the background\n");
     printf("image with the command cycle [name], followed by any number of spaces or\n");
     printf("commas, and a filepath to the image to be associated with the name.\n");
     printf("NOTE: The image path should be in quotes or it will not be read properly.\n");
     printf("Check if your image file is correctly formatted. If this explanation\n");
     printf("does not make sense, run:\n  cycle --help --format --template\n");
     printf("to generate an example template to fill in.\n");
     printf("If you have done all of this and your images are still not loading, run:\n");
     printf("  cycle --help --broken for info on troubleshooting\n");
     exit(EXIT_SUCCESS);
  }
  else if (argc == 2 && argsContain("--help", argv, argc)) {
      printf("Cycle Background is a simple command for changing the background\n");
      printf("image on the windows terminal. It does not work for any other\n");
      printf("environment (linux, mac) so don't try to use it there.\n");
      printf("Options:\n");
      printf("[null]                     | default option, sets all active\n");
      printf("                           | background images to the same random\n");
      printf("                           | image\n\n");
      printf("-r                         | sets all active backgrounds to\n");
      printf("                           | different random images\n\n");
      printf("[name]                     | sets all active backgrounds to the\n");
      printf("                           | background with the given name\n\n");
      printf("--names or -n              | lists all image names for reference\n\n");
      printf("--version                  | displays the current version\n\n");
      printf("--help                     | displays this text\n\n");
      printf("--help --format            | displays information about how to format\n");
      printf("                           | your image options file so that it can\n");
      printf("                           | be read by the loader\n\n");
      printf("--help --format --template | generates a example template\n");
      printf("                           | showing the correct format for\n");
      printf("                           | the image options file\n\n");
      printf("--help --route             | instructions on how to change the\n");
      printf("                           | directory the program looks in for your\n");
      printf("                           | image options file\n\n");
      printf("--help --broken            | instructions on what to do if the\n");
      printf("                           | program does not work or has stopped\n");
      printf("                           | working\n\n");
      printf("--help --daily             | instructions on how you can get this\n");
      printf("                           | command to run daily on your computer\n\n");
      printf("NOTE: there is a heirarchy of options. --version has highest precidence,\n");
      printf("      followed by all of the --help options. -r has priority over --names\n");
      printf("      and --names has priority over passing a name.");
      exit(EXIT_SUCCESS);
  }


  struct hashTable *images = loadEntries(imagePath);


  if (argc == 1)
    cycleSingleRand(images);
  else if (argc == 2 && argsContain("-r", argv, argc))
    cycleMultiRand(images);
  else if (argc == 2 && (argsContain("-n", argv, argc) || argsContain("--names", argv, argc))) {
     printKeysHT(images);
     exit(EXIT_SUCCESS);
  }
  else if (argc == 2) {
    char *val = getHT(*(argv + 1), images);
    if (*val == '\0') {
      printf("Given name was not one of:\n");
      printKeysHT(images);
      exit(EXIT_FAILURE);
    }
    cycleToVal(getHT(*(argv + 1), images), images);
  } 
  else if (argc > 2 && argsContain("-r", argv, argc))
    cycleMultiRand(images);
  else
    printf("Usage: cycle [-r | <image-name>]\nCycle --help for more information\n");
  return 0;
}

struct hashTable *loadEntries(char *path) {
  FILE *entries = fopen(path, "r");
  struct hashTable *out = makeHashTable(23);
  struct stringList *buffer = makeStringList(4);
  char c, *kc, *lastKc = "\0";
  int key = 0;
  while ((c = getc(entries)) != EOF) {
    if (key == 0) {
      if (c == ' ' || c == ',') {
        key = 1;
        kc = f_toStringSL(buffer);
        continue;
      }
      else if (c == '\n' || c == '\r') {
         f_toStringSL(buffer);
         continue;
      }
      else
        pshSL(c, buffer);
    } else if (key == 1) {
      if (c != ' ' && c != ',') {
        key = 2;
      } 
      else if (c == '\n' || c == '\r') {
         key = 0;
         f_toStringSL(buffer);
         continue;
      } 
      else continue;
    }
    if (key == 2) {
      if (c == '\n' || c == '\r') {
         if (kc == lastKc || buffer->tail - buffer->head == 0) {
            key = 0;
            f_toStringSL(buffer);
            continue;
         }
         addHT(kc, f_toStringSL(buffer), out);
         lastKc = kc;
         key = 0;
      } else
        pshSL(c, buffer);
    }
  }
  if (kc != NULL && buffer->head - buffer->tail > 2)
    addHT(kc, f_toStringSL(buffer), out);
  free(buffer);
  fclose(entries);
  return out;
}

void cycleSingleRand(struct hashTable *ht) {
  char *image = randElementHT(ht);
  char *path = malloc(sizeof(char)*300);
  strcpy(path,getenv("USERPROFILE"));
  strcat(path, "\\AppData\\Local\\Packages\\Microsoft.WindowsTerminal_"
               "8wekyb3d8bbwe\\LocalState\\settings.json");
  char *old = fileToString(path);
  struct stringList *buffer = makeStringList(20);
  for (int i = 0; i < 19; i++)
    pshSL('-', buffer);
  FILE *new = fopen(path, "w");
  int warn = 0, v = 0, i;
  while (*old != '\0') {
    remSL(buffer);
    pshSL(*old, buffer);
    if (eqlSL("\"backgroundImage\": ", buffer)) {
      i = 0;
      putc(' ', new);
      while (*(image + i) != '\0') {
        putc(*(image + i++), new);
      }
      while (*(++old) != ',');
      putc(*old, new);
    } else
      putc(*old, new);
    old++;
  }
  /* This for some reason crashes the program.
   * Maybe a future me who knows more will understand.
   * free(old); */
  free(path);
  fclose(new);
}

void cycleMultiRand(struct hashTable *ht) {
  char *image = randElementHT(ht);
  char *path = malloc(sizeof(char)*300);
  strcpy(path,getenv("USERPROFILE"));
  strcat(path, "\\AppData\\Local\\Packages\\Microsoft.WindowsTerminal_"
               "8wekyb3d8bbwe\\LocalState\\settings.json");
  char *old = fileToString(path);
  struct stringList *buffer = makeStringList(20);
  for (int i = 0; i < 19; i++)
    pshSL('-', buffer);
  FILE *new = fopen(path, "w");
  int warn = 0, v = 0, i;
  while (*old != '\0') {
    remSL(buffer);
    pshSL(*old, buffer);
    if (eqlSL("\"backgroundImage\": ", buffer)) {
      i = 0;
      putc(' ', new);
      while (*(image + i) != '\0') {
        putc(*(image + i++), new);
      }
      while (*(++old) != ',');
      putc(*old, new);
      image = randElementHT(ht);
    } else
      putc(*old, new);
    old++;
  }
  /* This for some reason crashes the program.
   * Maybe a future me who knows more will understand.
   * free(old); */
  free(path);
  fclose(new);
}

void cycleToVal(char *image, struct hashTable *ht) {
  struct stringList *buffer = makeStringList(20);
  char *path = malloc(sizeof(char)*200);
  strcpy(path,getenv("USERPROFILE"));
  strcat(path, "\\AppData\\Local\\Packages\\Microsoft.WindowsTerminal_"
               "8wekyb3d8bbwe\\LocalState\\settings.json");
  char *old = fileToString(path);
  for (int i = 0; i < 19; i++)
    pshSL('-', buffer);
  FILE *new = fopen(path, "w");
  int warn = 0, v = 0, i;
  while (*old != '\0') {
    remSL(buffer);
    pshSL(*old, buffer);
    if (eqlSL("\"backgroundImage\": ", buffer)) {
      i = 0;
      putc(' ', new);
      while (*(image + i) != '\0') {
        putc(*(image + i++), new);
      }
      while (*(++old) != ',');
      putc(*old, new);
    } else
      putc(*old, new);
    old++;
  }
  /* This for some reason crashes the program.
   * Maybe a future me who knows more will understand.
   * free(old); */
  free(path);
  fclose(new);
}

int argsContain(char *element, char **argv, int argc) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(element, *(argv + i)) == 0) {
      return i;
    }
  }
  return 0;
}
