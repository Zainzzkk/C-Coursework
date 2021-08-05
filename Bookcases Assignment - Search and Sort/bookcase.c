#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "neillsimplescreen.h"

#define MAXHEIGHT 9
#define MAXWIDTH 9
#define EMPTY '.'
#define BLACK 'K'
#define RED 'R'
#define GREEN 'G'
#define YELLOW 'Y'
#define BLUE 'B'
#define MAGENTA 'M'
#define CYAN 'C'
#define WHITE 'W'
#define ISNOTEMPTY -5
#define ISEMPTY -6
/*most my computer will allow to allocate*/
#define FULLSIZE 20000000
/*calculated before overflowing on 5 5 7*/
#define MAXTIMES 1199999
/*ensures don't overflow*/
#define SIZE 150
/*for longer file names*/
#define LEN 30
/*as 8 colours*/
#define NUMCOLOUR 8
/*size of parent/iteration array*/
#define TRACKER 2
#define CHILD 0
#define PARENT 1
#define BLA 0
#define RE 1
#define GRE 2
#define YEL 3
#define BLU 4
#define MAG 5
#define CYA 6
#define WHI 7
#define PRNT 0
#define FIRST 0

enum bool {false, true};
typedef enum bool bool;

/*parent to link back and check which move from parent link back to*/
struct bookshelf {
   char shelf[MAXHEIGHT][MAXWIDTH];
   int height;
   int width;
   int parent;
   };
typedef struct bookshelf bookshelf;
/*functions in order of which made first*/
void test(void);
/*checks if the shelf is totally empty*/
bool shelfempty(bookshelf bs, int y);
/*checks if there is an empty slot on a shelf*/
bool emptyslots(bookshelf bs, int y);
/*return position for right most empty space*/
int mostright(bookshelf bs, int y);
/*return position for right most book*/
int mostrightbook(bookshelf bs, int y);
/*checks for happy bookshelf*/
bool samecheck(bookshelf bs);
/*makes sure 1 colour only on 1 row*/
bool samecheckrow(bookshelf bs);
/*makes sure valid bookshelf conditions are met*/
bool shelfconditions(bookshelf bs, int colours[NUMCOLOUR]);
/*makes sure not more colours than rows*/
bool howmanycolours(bookshelf bs, int colours[NUMCOLOUR]);
/*makes sure only valid colours*/
bool colourcheck(bookshelf bs);
/*checks for invalid colours*/
bool colourvalid(char c);
/*generates all child for single parent and fills array, my bad sense of humour
was too tempting sorry!*/
bool ILikeToMoveItMoveIt(bookshelf bs, bookshelf gens[FULLSIZE],
                         int tracker[TRACKER]);
/*makes sure array inbounds*/
bool inbounds(bookshelf bs, int y, int n);
/*moves books around*/
void changepositions(bookshelf bs, bookshelf gens[FULLSIZE],
                     int y, int newy, int tracker[TRACKER]);
/*ensure no overflow*/
void inmemory(int n);
/*finds parent boards steps needed*/
int parentboardcheck(bookshelf gens[FULLSIZE], bookshelf parents[SIZE],
                     int n);
/*prints parent boards for verbose*/
void printparents(bookshelf parents[SIZE], int n);
/*scans in file and makes sure valid*/
bool scanfile(bookshelf bs, bookshelf cases[FULLSIZE],
              char filename[LEN], int* n);
/*reads actual bookshelf*/
void readshelf(bookshelf* bs, FILE* fp, int* i);
/*checks that follows rules*/
bool validitycheck(bookshelf bs, int i);
/*checks that board is valid*/
void validboard(bookshelf bs, bookshelf cases[FULLSIZE],
                char filename[LEN], int c[NUMCOLOUR]);
/*converts to all uppercase*/
void makeupper(bookshelf* bs);
/*ensures that top line dimensions == actual shelf*/
bool checkheightwidth(bookshelf bs, int height, int width);
/*checks that there is no book after empty*/
bool rightconfig(bookshelf bs);
/*prints boards for verbose*/
void verbose(bookshelf parents[SIZE], int solutions);
/*checks for full empty board*/
bool emptyboard(bookshelf cases);

int main(int argc, char* argv[])
{
   bookshelf bs = {0};
   static bookshelf cases[FULLSIZE];
   bookshelf parents[SIZE];
   int i, solutions;
   int colours[NUMCOLOUR] = {0};
   int tracker[TRACKER] = {0};

   test();
   /*makes sure bookcase is valid*/
   validboard(bs, cases, argv[1],colours);
   /*if iniital board is happy then ends program*/
   if ((samecheck(cases[PRNT]) == true)||(emptyboard(cases[PRNT]) == true)){
      solutions = parentboardcheck(cases, parents, PRNT);
      if ((argc == 3) && (strcmp(argv[2],"verbose")==0)){
         verbose(parents, solutions);
         exit(EXIT_SUCCESS);
         }
      printf("%d\n", solutions + 1);
      exit(EXIT_SUCCESS);
      }

   for (i = 0; i < MAXTIMES; i++){
      memcpy(&bs,&cases[i], sizeof(bookshelf));
      if (ILikeToMoveItMoveIt(bs, cases, tracker) == true){
         solutions = parentboardcheck(cases, parents, tracker[CHILD]);
         if ((argc == 3) && (strcmp(argv[2],"verbose")==0)){
            verbose(parents, solutions);
            exit(EXIT_SUCCESS);
            }
         printf("%d\n", solutions);
         exit(EXIT_SUCCESS);
         }
      tracker[PARENT] += 1;
      }
      /*if no solution found then will exit program*/
      printf("No Solution?\n");

   return 0;
}

void validboard(bookshelf bs, bookshelf cases[FULLSIZE],
                char filename[LEN], int c[NUMCOLOUR])
{
   int initmoves;

   if ((scanfile(bs, cases, filename, &initmoves)==false)||
       (shelfconditions(cases[PRNT], c)==false)){
      fprintf(stderr,"Not valid board\n");
      exit(EXIT_FAILURE);
      }
}
/*made in previous lab session and adapted for this assignment*/
bool scanfile(bookshelf bs, bookshelf cases[FULLSIZE], char filename[LEN], int* n)
{
   FILE* fp;
   char temp[LEN];
   int i;

   if ((fp = fopen(filename, "r")) == NULL) {
      fprintf(stderr, "Cannot open file\n");
      exit(EXIT_FAILURE);
      }
   /*reads first line and stores values*/
   if (fgets(temp, LEN, fp) != NULL) {
      sscanf(temp, "%d %d %d", &bs.height, &bs.width, n);
      }
   /*read board from line 1 (under numbers)*/
   readshelf(&bs, fp, &i);
   fclose(fp);
   /*makes sure uppercase*/
   makeupper(&bs);
   /*makes sure height and width match up*/
   if (validitycheck(bs, i)== false){
      return false;
      }
   bs.parent = 0;
   /*copies scanned bookshelf to parent first cell in array*/
   memcpy(&cases[PRNT], &bs, sizeof(bookshelf));

   return true;
}

void readshelf(bookshelf* bs, FILE* fp, int* i)
{
   int n;
   char temp[LEN];
   bool read = false;

   n = 0;
   do {
      if (fgets(temp, LEN, fp) != NULL){
         sscanf(temp, "%s", bs->shelf[n]);
         n++;
         }
      else {
         read = true;
         }
      } while (read == false);
      *i = n;
}

void makeupper(bookshelf* bs)
{
   int i, j;

   for (j = 0; j < bs->height; j++){
      for (i = 0; i < bs->width; i++){
         bs->shelf[j][i] = toupper(bs->shelf[j][i]);
         }
      }
}

bool validitycheck(bookshelf bs, int i)
{
   int j;

   if (i == 0){
      return false;
      }
   for (j = 0; j < i; j++){
   if (checkheightwidth(bs, i, strlen(bs.shelf[j])) == false){
         return false;
         }
      }
   if (colourcheck(bs) == false){
      return false;
      }

   return true;
}

bool checkheightwidth(bookshelf bs, int height, int width)
{
   if (bs.height != height){
      return false;
   }
   if (bs.width != width){
      return false;
   }
   /*makes sure not over limit of 9x9 or 0*/
   if (bs.height > MAXHEIGHT || height > MAXHEIGHT ||
       bs.height == 0 || height == 0){
      return false;
      }
   /*-1 as extra 1 added to max width*/
   if (bs.width > MAXWIDTH  || width > MAXWIDTH ||
       bs.width == 0 || width == 0){
      return false;
      }
   if (rightconfig(bs) == false){
      return false;
   }
   return true;
}

bool rightconfig(bookshelf bs)
{
   int i, j;

   for(j = 0; j < bs.height; j++){
      for (i = 0; i < bs.width - 1 ; i++){
         if (bs.shelf[j][i] == EMPTY){
            if(bs.shelf[j][i+1] != EMPTY){
               return false;
               }
            }
         }
      }
   return true;
}

bool colourcheck(bookshelf bs)
{
   int i, j;
   /*makes sure only these are on shelf*/
   for (j = 0; j < bs.height; j++){
      for (i = 0; i < bs.width; i++){
         if (!colourvalid(bs.shelf[j][i])){
            return false;
            }
         }
      }
      return true;
}

bool colourvalid(char c)
{
   if (c == BLACK || c == RED || c == GREEN || c == YELLOW ||
       c == BLUE || c == MAGENTA || c == CYAN || c == WHITE
       || c == EMPTY){
      return true;
      }
   return false;
}

bool shelfconditions(bookshelf bs, int colours[NUMCOLOUR])
{
   int i, j;
   /*adds counter for each colour in array*/
   for (j = 0; j < bs.height; j++){
      for (i = 0; i < bs.width; i++){
         if (bs.shelf[j][i] == BLACK){
            colours[BLA] += 1;
            }
         if (bs.shelf[j][i] == RED){
            colours[RE] += 1;
            }
         if (bs.shelf[j][i] == GREEN){
            colours[GRE] += 1;
            }
         if (bs.shelf[j][i] == YELLOW){
            colours[YEL] += 1;
            }
         if (bs.shelf[j][i] == BLUE){
            colours[BLU] += 1;
            }
         if (bs.shelf[j][i] == MAGENTA){
            colours[MAG] += 1;
            }
         if (bs.shelf[j][i] == CYAN){
            colours[CYA] += 1;
            }
         if (bs.shelf[j][i] == WHITE){
            colours[WHI] += 1;
            }
         }
      }

   if (howmanycolours(bs, colours) == false){
      return false;
      }

   return true;
}

bool howmanycolours(bookshelf bs, int colours[NUMCOLOUR])
{
   int i, counter = 0;

   for (i = 0; i < NUMCOLOUR; i++){
      /*checks not more of 1 colour than row width*/
      if (colours[i] > bs.width){
         return false;
         }
      if (colours[i] > 0){
         counter += 1;
         }
      }
   /*checks that not more colours than number of shelves*/
   if (counter > bs.height){
      return false;
      }

   return true;
}

bool emptyboard(bookshelf cases)
{
   int i, j;
   /* if empty board*/
   for (j = 0; j < cases.height; j++){
      for(i = 0; i < cases.width; i++){
         if (cases.shelf[j][i] != EMPTY){
            return false;
            }
         }
      }
   return true;
}

bool shelfempty(bookshelf bs, int y)
{
   int i;
   /*will return false if finds book*/
   for (i = 0; i < bs.width; i++){
      if (bs.shelf[y][i] != EMPTY){
         return false;
         }
   }
   return true;
}

bool emptyslots(bookshelf bs, int y)
{
   int i;
   /*tells you if space on shelf to add book*/
   for (i = 0; i < bs.width; i++){
      if (bs.shelf[y][i] == EMPTY){
         return true;
         }
      }
   return false;
}

int mostright(bookshelf bs, int y)
{
   int i;
   /*if first position empty then returns 0*/
   if (bs.shelf[y][FIRST] == EMPTY){
      i = 0;
      return i;
      }
   /*return the first non empty cell*/
   for (i = bs.width - 1; i >= 1; i--){
      if (bs.shelf[y][i-1] != EMPTY){
         return i;
         }
      }
   return ISNOTEMPTY;
}

int mostrightbook(bookshelf bs, int y)
{
   int i;
      /*if most right cell is book then return*/
   if (bs.shelf[y][bs.width-1] != EMPTY){
      return bs.width - 1;
      }
   for (i = bs.width - 1; i >= 1; i--){
      if (bs.shelf[y][i-1] != EMPTY){
         return i - 1;
         }
      }
   return ISEMPTY;
}
/*will generate all children for any generation in 1 run
and populate array of structs*/
bool ILikeToMoveItMoveIt(bookshelf bs, bookshelf gens[FULLSIZE],
                         int tracker[TRACKER])
{
   int i, j;
   /*goes through each row*/
   for (j = 0; j < bs.height; j++){
      /*looks at all possibilities to move up and down if inbound*/
      for (i = j - (bs.height - 1); i < (j + bs.height); i++){
         if (inbounds(bs, j, i) == true){
            changepositions(bs, gens, j, i, tracker);
            if(samecheck(gens[tracker[CHILD]]) == true){
               return true;
               }
            }
         }
      }
   return false;
}

bool inbounds(bookshelf bs, int y, int n)
{
   /*won't move onto same row and if empty and only if space on shelf*/
   if ((n >= 0) && (n < bs.height) && (shelfempty(bs, y) == false)
        && (emptyslots(bs,n) == true) && (n != y)){
      return true;
      }

   return false;
}

void changepositions(bookshelf bs, bookshelf gens[FULLSIZE],
                     int y, int newy, int tracker[TRACKER])
{
   bookshelf tmp;
   int oldx, newx;

   oldx = (mostrightbook(bs,y));
   newx = (mostright(bs,newy));
   if (bs.shelf[y][oldx] != EMPTY){
      tracker[CHILD] +=1;
      inmemory(tracker[CHILD]);
      memcpy(&tmp, &bs, sizeof(bookshelf));
      /*will allow to track back*/
      tmp.parent = tracker[PARENT];
      tmp.shelf[newy][newx] =  bs.shelf[y][oldx];
      tmp.shelf[y][oldx] = EMPTY;
      /*copies it to position on array - will be in order*/
      memcpy(&gens[tracker[CHILD]], &tmp, sizeof(bookshelf));
      }
}

void inmemory(int n)
{
   if (n >= FULLSIZE){
      printf("No solution?\n");
      exit(EXIT_FAILURE);
      }
}

bool samecheck(bookshelf bs)
{
   int i, j;
   /*checks if all colours on row same (up till empty)*/
   for(j = 0; j < bs.height; j++){
      for(i = 0; i < bs.width - 1; i++){
         if((bs.shelf[j][i] != bs.shelf[j][i+1])
             && (bs.shelf[j][i+1] != EMPTY)){
            return false;
            }
         }
      }

   if (samecheckrow(bs) == false){
      return false;
      }

   return true;
}

bool samecheckrow(bookshelf bs)
{
   int i, j;
   /*checks same colour not repeated on multiple rows*/
   for (j = 0; j < bs.height - 1; j++){
      for (i = j + 1; i < bs.height; i++){
         if (shelfempty(bs, j) == true){
            j++;
            }
         if (bs.shelf[j][FIRST] == bs.shelf[i][FIRST]){
            return false;
            }
         }
      }

   return true;
}

int parentboardcheck(bookshelf gens[FULLSIZE], bookshelf parents[SIZE], int n)
{
   int i;
   /*n is parent value of happy bookshelf*/
   i = 0;
   while (n != 0){
      /*copies happy cell to parent array and then copies
      parent of parent etc*/
      memcpy(&parents[i], &gens[n], sizeof(bookshelf));
      /*sets n to parent of parent*/
      n = gens[n].parent;
      i++;
      }
   /*copies the starting board*/
   memcpy(&parents[i], &gens[PRNT], sizeof(bookshelf));
   /*i is number of moves*/
   return i;
}

void verbose(bookshelf parents[SIZE], int solutions)
{
   printf("%d\n", solutions + 1);
   printf("\n");
   printparents(parents, solutions);
}
/*no way to shorten print function*/
void printparents(bookshelf parents[SIZE], int n)
{
   int i, j, k;

   for (k = n; k >= 0; k--){
      for (j = 0; j < parents->height; j++){
         for(i = 0; i < parents->width; i++){
            if (parents[k].shelf[j][i] == BLACK){
               neillbgcol(white);
               neillfgcol(black);
               }
            if (parents[k].shelf[j][i] == RED){
               neillreset();
               neillfgcol(red);
               }
            if (parents[k].shelf[j][i] == GREEN){
               neillreset();
               neillfgcol(green);
               }
            if (parents[k].shelf[j][i] == YELLOW){
               neillreset();
               neillfgcol(yellow);
               }
            if (parents[k].shelf[j][i] == BLUE){
               neillreset();
               neillfgcol(blue);
               }
            if (parents[k].shelf[j][i] == MAGENTA){
               neillreset();
               neillfgcol(yellow);
               }
            if (parents[k].shelf[j][i] == CYAN){
               neillreset();
               neillfgcol(cyan);
               }
            if (parents[k].shelf[j][i] == WHITE){
               neillreset();
               neillfgcol(white);
               }
            printf("%c ", parents[k].shelf[j][i]);
            neillreset();
            }
         printf("\n");
         }
      printf("\n");
      }
}

void test(void)
{
   /*all functions tested at least twice unless function cannot be tested*/
   bookshelf b;
   int i;
   bookshelf testcases[1000];
   bookshelf testparents[100];
   int cols[NUMCOLOUR] = {0};
   int tracker[TRACKER] = {0};
   /* height 3 width 3*/
   b.height = 3;
   b.width = 3;
   b.parent = 0;

   b.shelf[0][0] = EMPTY;
   b.shelf[0][1] = EMPTY;
   b.shelf[0][2] = EMPTY;
   b.shelf[1][0] = EMPTY;
   b.shelf[1][1] = EMPTY;
   b.shelf[1][2] = EMPTY;
   b.shelf[2][0] = EMPTY;
   b.shelf[2][1] = EMPTY;
   b.shelf[2][2] = EMPTY;
   assert(shelfconditions(b,cols)==(true));
   assert(emptyboard(b)==(true));
   cols[0] = 0;
   cols[1] = 0;
   cols[2] = 0;
   cols[3] = 0;
   cols[4] = 0;
   cols[5] = 0;
   cols[6] = 0;
   cols[7] = 0;
   b.shelf[0][0] = BLACK;
   b.shelf[0][1] = BLACK;
   b.shelf[0][2] = BLACK;
   b.shelf[1][0] = RED;
   b.shelf[1][1] = RED;
   b.shelf[1][2] = BLACK;
   b.shelf[2][0] = EMPTY;
   b.shelf[2][1] = EMPTY;
   b.shelf[2][2] = EMPTY;
   assert(shelfconditions(b,cols)==(false));
   assert(howmanycolours(b,cols)==(false));
   b.shelf[1][2] = YELLOW;
   b.shelf[2][1] = BLUE;
   assert(shelfconditions(b,cols)==(false));
   assert(howmanycolours(b,cols)==(false));
   /*RESET counter*/
   cols[0] = 0;
   cols[1] = 0;
   cols[2] = 0;
   cols[3] = 0;
   cols[4] = 0;
   cols[5] = 0;
   cols[6] = 0;
   cols[7] = 0;
   b.height = 3;
   b.width = 3;
   b.parent = 0;
   b.shelf[0][0] = BLACK;
   b.shelf[0][1] = BLACK;
   b.shelf[0][2] = EMPTY;
   b.shelf[1][0] = RED;
   b.shelf[1][1] = RED;
   b.shelf[1][2] = BLACK;
   b.shelf[2][0] = EMPTY;
   b.shelf[2][1] = EMPTY;
   b.shelf[2][2] = EMPTY;
   assert(shelfconditions(b, cols)==(true));
   assert(howmanycolours(b,cols)==(true));
   /*makes sure returns true when whole row empty*/
   assert(shelfempty(b,0)==(false));
   assert(shelfempty(b,1)==(false));
   assert(shelfempty(b,2)==(true));
   assert(shelfempty(b,0)!=(true));
   /*checks that true if any empty slots on 1 and 2*/
   assert(emptyslots(b, 0)==(true));
   assert(emptyslots(b, 1)==(false));
   assert(emptyslots(b, 2)==(true));
   assert(emptyslots(b, 0)!=(false));
   /*checks correct int returned for right most*/
   assert(mostright(b, 0)==(2));
   assert(mostright(b, 1)==(b.width-1));
   assert(mostright(b, 2)==(0));

   assert(mostrightbook(b,0)==(1));
   assert(mostrightbook(b,1)==(2));
   assert(mostrightbook(b,2)==(ISEMPTY));
   /*check if same*/
   assert(samecheck(b)==(false));
   assert(samecheckrow(b)==(true));

   b.shelf[0][2] = BLACK;
   b.shelf[1][2] = EMPTY;
   assert(emptyslots(b, 0)==(false));
   assert(emptyslots(b, 1)==(true));
   assert(emptyslots(b, 2)==(true));
   assert(mostright(b, 0)==(b.width-1));
   assert(mostright(b, 1)==(2));
   assert(mostright(b, 2)==(0));
   assert(samecheckrow(b)==(true));
   assert(samecheck(b)==(true));

   b.shelf[2][0] = RED;
   assert(shelfempty(b,2)==(false));
   assert(emptyslots(b, 0)==(false));
   assert(emptyslots(b, 1)==(true));
   assert(emptyslots(b, 2)==(true));
   assert(mostright(b, 0)==(b.width-1));
   assert(mostright(b, 1)==(2));
   assert(mostright(b, 2)==(1));
   assert(samecheckrow(b)==(false));
   assert(samecheck(b)==(false));

   cols[0] = 0;
   cols[1] = 0;
   cols[2] = 0;
   cols[3] = 0;
   cols[4] = 0;
   cols[5] = 0;
   cols[6] = 0;
   cols[7] = 0;

   b.parent = 0;
   b.height = 3;
   b.width = 3;
   b.shelf[0][0] = YELLOW;
   b.shelf[0][1] = EMPTY;
   b.shelf[0][2] = EMPTY;
   b.shelf[1][0] = BLUE;
   b.shelf[1][1] = BLUE;
   b.shelf[1][2] = YELLOW;
   b.shelf[2][0] = YELLOW;
   b.shelf[2][1] = BLUE;
   b.shelf[2][2] = EMPTY;
   assert(shelfconditions(b,cols)==(true));
   memcpy(&testcases[0], &b, sizeof(bookshelf));
   /*runs move function till found*/
   for (i = 0; i < 15; i++){
      memcpy(&b,&testcases[i], sizeof(bookshelf));
      if(ILikeToMoveItMoveIt(b, testcases, tracker)==true){
         parentboardcheck(testcases, testparents, tracker[0]);
      }
      }
   memcpy(&b, &testcases[1], sizeof(bookshelf));
   /*YELLOW HAS BEEN moved first so 0 0 empty*/
   assert(b.shelf[0][0]==(EMPTY));
   assert(b.shelf[0][1]==(EMPTY));
   assert(b.shelf[0][2]==(EMPTY));
   assert(b.shelf[1][0]==(BLUE));
   assert(b.shelf[1][1]==(BLUE));
   assert(b.shelf[1][2]==(YELLOW));
   assert(b.shelf[2][0]==(YELLOW));
   assert(b.shelf[2][1]==(BLUE));
   /*YELLOW moved to here*/
   assert(b.shelf[2][2]==(YELLOW));

   memcpy(&b, &testcases[2], sizeof(bookshelf));
   /*yellow should be replaced*/
   assert(b.shelf[0][0]==(YELLOW));
   /*moved from 1 2 to here first*/
   assert(b.shelf[0][1]==(YELLOW));
   assert(b.shelf[0][2]==(EMPTY));
   assert(b.shelf[1][0]==(BLUE));
   assert(b.shelf[1][1]==(BLUE));
   /*EMPTY as moved*/
   assert(b.shelf[1][2]==(EMPTY));
   assert(b.shelf[2][0]==(YELLOW));
   assert(b.shelf[2][1]==(BLUE));
   /*should be empty as yellow moved back*/
   assert(b.shelf[2][2]==(EMPTY));

   memcpy(&b, &testcases[3], sizeof(bookshelf));
   assert(b.shelf[0][0]==(YELLOW));
   assert(b.shelf[0][1]==(EMPTY));
   assert(b.shelf[0][2]==(EMPTY));
   assert(b.shelf[1][0]==(BLUE));
   assert(b.shelf[1][1]==(BLUE));
   assert(b.shelf[1][2]==(EMPTY));
   assert(b.shelf[2][0]==(YELLOW));
   assert(b.shelf[2][1]==(BLUE));
   assert(b.shelf[2][2]==(YELLOW));
   assert(samecheck(testcases[3])==(false));
   assert(samecheckrow(testcases[3])==(false));

   memcpy(&b, &testcases[12], sizeof(bookshelf));
   assert(b.shelf[0][0]==(YELLOW));
   assert(b.shelf[0][1]==(YELLOW));
   assert(b.shelf[0][2]==(EMPTY));
   assert(b.shelf[1][0]==(BLUE));
   assert(b.shelf[1][1]==(BLUE));
   assert(b.shelf[1][2]==(BLUE));
   assert(b.shelf[2][0]==(YELLOW));
   assert(b.shelf[2][1]==(EMPTY));
   assert(b.shelf[2][2]==(EMPTY));
   assert(samecheck(testcases[12])==(false));
   assert(samecheckrow(testcases[12])==(false));
   /*worked out on pen and paper for where to find solved board*/
   memcpy(&b, &testcases[52], sizeof(bookshelf));
   assert(b.shelf[0][0]==(YELLOW));
   assert(b.shelf[0][1]==(YELLOW));
   assert(b.shelf[0][2]==(YELLOW));
   assert(b.shelf[1][0]==(BLUE));
   assert(b.shelf[1][1]==(BLUE));
   assert(b.shelf[1][2]==(BLUE));
   assert(b.shelf[2][0]==(EMPTY));
   assert(b.shelf[2][1]==(EMPTY));
   assert(b.shelf[2][2]==(EMPTY));
   assert(samecheck(testcases[52])==(true));
   assert(samecheckrow(testcases[52])==(true));
   memcpy(&b, &testparents[0], sizeof(bookshelf));
   assert(b.shelf[0][0]==(YELLOW));
   assert(b.shelf[0][1]==(YELLOW));
   assert(b.shelf[0][2]==(YELLOW));
   assert(b.shelf[1][0]==(BLUE));
   assert(b.shelf[1][1]==(BLUE));
   assert(b.shelf[1][2]==(BLUE));
   assert(b.shelf[2][0]==(EMPTY));
   assert(b.shelf[2][1]==(EMPTY));
   assert(b.shelf[2][2]==(EMPTY));
   /*correct number of moves*/
   b.height = 2;
   b.width = 1;
   b.parent = 0;
   b.shelf[0][0] = EMPTY;
   /*makes sure make uppercase works*/
   b.shelf[0][0] = 'b';
   b.shelf[1][0] = '.';
   makeupper(&b);
   assert(b.shelf[0][0]==(BLUE));
   assert(b.shelf[1][0]==(EMPTY));
   /*CHECK COMPLETED BOARD 4X4 WITH 1 STRAY COLOUR*/
   b.height = 3;
   b.width = 3;
   b.shelf[0][0]=EMPTY;
   b.shelf[0][1]=EMPTY;
   b.shelf[0][2]=EMPTY;
   b.shelf[1][0]=EMPTY;
   b.shelf[1][1]=EMPTY;
   b.shelf[1][2]=EMPTY;
   b.shelf[2][0]=EMPTY;
   b.shelf[2][1]=EMPTY;
   b.shelf[2][2]=EMPTY;
   assert(emptyboard(b)==(true));
   /*check still works on empty board*/
   assert(rightconfig(b)==(true));
   b.shelf[0][0]=RED;
   b.shelf[0][1]=RED;
   b.shelf[0][2]=EMPTY;
   b.shelf[1][0]=YELLOW;
   b.shelf[1][1]=YELLOW;
   b.shelf[1][2]=YELLOW;
   b.shelf[2][0]=RED;
   b.shelf[2][1]=EMPTY;
   b.shelf[2][2]=EMPTY;
   assert(emptyboard(b)==(false));
   assert(colourcheck(b)==(true));
   assert(samecheck(b)==(false));
   assert(samecheckrow(b)==(false));
   assert(rightconfig(b)==(true));
   /*check false colour flags up*/
   b.shelf[0][0]=RED;
   b.shelf[0][1]=RED;
   b.shelf[0][2]=EMPTY;
   b.shelf[1][0]=EMPTY;
   b.shelf[1][1]=EMPTY;
   b.shelf[1][2]=EMPTY;
   b.shelf[2][0]=EMPTY;
   b.shelf[2][1]=EMPTY;
   b.shelf[2][2]='O';
   assert(colourcheck(b)==(false));
   assert(rightconfig(b)==(false));
   /*checks that it returns false with mismatch*/
   b.height = 3;
   b.width = 3;
   b.shelf[0][0]=RED;
   b.shelf[0][1]=RED;
   b.shelf[0][2]=EMPTY;
   b.shelf[1][0]=EMPTY;
   b.shelf[1][1]=EMPTY;
   b.shelf[1][2]=EMPTY;
   b.shelf[2][0]=EMPTY;
   b.shelf[2][1]=EMPTY;
   b.shelf[2][2]=EMPTY;
   assert(checkheightwidth(b, 3, 4)==(false));
   assert(validitycheck(b,3)==(true));
   assert(validitycheck(b,4)==(false));
   b.height = 3;
   b.width = 3;
   assert(checkheightwidth(b, 3, 3)==(true));
   assert(validitycheck(b,3)==(true));
   b.height = 4;
   b.width = 4;
   assert(checkheightwidth(b, 3, 3)==(false));
   assert(validitycheck(b,3)==(false));
   /*tests incorrect config*/
   b.shelf[0][0]=EMPTY;
   b.shelf[0][1]=BLACK;
   b.shelf[0][2]=EMPTY;
   b.shelf[1][0]=EMPTY;
   b.shelf[1][1]=EMPTY;
   b.shelf[1][2]=EMPTY;
   b.shelf[2][0]=EMPTY;
   b.shelf[2][1]=EMPTY;
   b.shelf[2][2]=EMPTY;
   assert(rightconfig(b)==(false));
   /*inbounds test*/
   b.height = 3;
   b.width = 3;
   b.shelf[0][0]=YELLOW;
   b.shelf[0][1]=BLACK;
   b.shelf[0][2]=EMPTY;
   b.shelf[1][0]=YELLOW;
   b.shelf[1][1]=EMPTY;
   b.shelf[1][2]=EMPTY;
   b.shelf[2][0]=YELLOW;
   b.shelf[2][1]=EMPTY;
   b.shelf[2][2]=EMPTY;
   assert(inbounds(b, 2, -1)==(false));
   assert(inbounds(b, 2, 2)==(false));
   assert(inbounds(b, 2, 3)==(false));
   assert(inbounds(b, 0, 2)==(true));
   assert(inbounds(b, 0, 0)==(false));
   assert(inbounds(b, 0, -1)==(false));
   assert(inbounds(b, 0, 1)==(true));
   assert(inbounds(b, 1, 1)==(false));
   assert(inbounds(b, 1, 0)==(true));
   assert(inbounds(b, 1, 2)==(true));
   /*check when shelf empty and full*/
   b.shelf[0][0]=YELLOW;
   b.shelf[0][1]=BLACK;
   b.shelf[0][2]=BLACK;
   b.shelf[1][0]=YELLOW;
   b.shelf[1][1]=EMPTY;
   b.shelf[1][2]=EMPTY;
   b.shelf[2][0]=EMPTY;
   b.shelf[2][1]=EMPTY;
   b.shelf[2][2]=EMPTY;
   assert(inbounds(b, 2, 0)==(false));
   assert(inbounds(b, 2, 2)==(false));
   assert(inbounds(b, 2, 3)==(false));
   assert(inbounds(b, 0, 2)==(true));
   assert(inbounds(b, 0, 0)==(false));
   assert(inbounds(b, 0, -1)==(false));
   assert(inbounds(b, 0, 1)==(true));
   assert(inbounds(b, 1, 1)==(false));
   assert(inbounds(b, 1, 0)==(false));
   assert(inbounds(b, 1, 2)==(true));

}
