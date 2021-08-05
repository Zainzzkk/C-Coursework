#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "neillsimplescreen.h"

#define HEIGHT 30
#define WIDTH 80
/*for checking neighbours of cells for fire*/
#define NEIGHBOURS 1
/*value of G for working out probability*/
#define G 250
/*value of L is 10*G for working out probability*/
#define L (G * 10)
/*number of generations/iterations code works for*/
#define GENERATIONS 1000
#define TREE '@'
#define EMPTY ' '
#define FIRE '*'
/*time for neillbusywait*/
#define WAITTIME 0.05
/*Please see comment in function*/
#define NUMBEROFTREESBASEDONPROB 2300
/*Please see comment in function*/
#define NUMBEROFFIRESBASEDONPROB 700

enum bool {false, true};
typedef enum bool bool;

/* for test function to check in input is same as expected output*/
bool testcompareinout(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH],
                      int y, int x);
/* for test function to check if tree turning to fire*/
bool testtree2fire(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH],
                   int y, int x);
/* for test function to check if fire turning to empty*/
bool testfire2empty(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH],
                    int y, int x);
/*tests probability working for trees - rough*/
bool testtreegeneration(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH]);
/*tests probability for fires - rough*/
bool testfiregeneration(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH]);
/*creates the initial empty forest*/
void forestinit(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH]);
/*function to copy output to input to make it easier to understand*/
void outputtoinput(char outforest[HEIGHT][WIDTH], char inforest[HEIGHT][WIDTH]);
/*Generates chance of G*/
int probofg(void);
/*Generates chance of L*/
int probofl(void);
/*populate forest with trees*/
void populatetrees(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH]);
/*takes the chances of L and starts a fire in a random spot if tree present*/
void lightning(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH]);
/*puts out fire in 1 generation*/
void fireburnspread(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH]);
/*checks neighbouring cells if trees and sets them on fire*/
void next2trees(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH],
                int y, int x);
/*prints out each iteration*/
void printforest(char forest[HEIGHT][WIDTH]);
void test(void);

int main(void)
{
   char forestin[HEIGHT][WIDTH];
   char forestout[HEIGHT][WIDTH];
   int i;
   /*seed for random number*/
   srand(time(NULL));
   /*remove for loop after testing complete, tests over 1000 times*/
   /*for (i = 0; i < GENERATIONS; i++){*/
      test();
      /*}*/
   /*creates and prints empty forest*/
   forestinit(forestin, forestout);
   printforest(forestout);
   outputtoinput(forestout,forestin);
   neillclrscrn();

   for (i = 0; i < GENERATIONS; i++){
      fireburnspread(forestin, forestout);
      outputtoinput(forestout,forestin);
      lightning(forestin, forestout);
      outputtoinput(forestout,forestin);
      populatetrees(forestin, forestout);
      outputtoinput(forestout,forestin);
      neillcursorhome();
      printforest(forestin);
      neillbusywait(WAITTIME);
      }
   neillreset();

   /*printf("\n");*/ /*remove after debugging*/
   return 0;
}

void test(void)
{
   int i;
   char foresttesta[HEIGHT][WIDTH];
   char foresttestb[HEIGHT][WIDTH];
   /*test probability functions -  don't go above L or G or HEIGHT or WIDTH*/
   for (i = 0; i < 100; i++){
      assert(probofg()!=(G + 5));
      assert(probofl()!=(L + 5));
      }
   /*test that board is wiped*/
   forestinit(foresttesta,foresttestb);
   assert(testcompareinout(foresttesta,foresttestb,0,0)==(true));
   assert(testcompareinout(foresttesta,foresttestb,2,5)==(true));
   /*sets some parts of the forest*/
   foresttesta[0][0] = TREE;
   foresttesta[0][1] = FIRE;
   foresttesta[0][2] = TREE;
   foresttesta[0][3] = TREE;
   foresttesta[0][4] = EMPTY;
   foresttesta[0][5] = TREE;
   foresttesta[0][6] = EMPTY;
   foresttesta[1][1] = TREE;
   foresttesta[1][0] = TREE;
   foresttesta[1][2] = TREE;
   /*tests copy function is working*/
   outputtoinput(foresttesta, foresttestb);
   assert(testcompareinout(foresttesta,foresttestb,0,0)==(true));
   assert(testcompareinout(foresttesta,foresttestb,3,5)==(true));
   assert(testcompareinout(foresttesta,foresttestb,0,3)==(true));
   /*first iteration to test burn and spread*/
   fireburnspread(foresttesta, foresttestb);
   /*this will test both functions, fireburnspread and next2trees*/
   /*should be false as burning and checks if changing from tree to fire*/
   assert(testcompareinout(foresttesta,foresttestb,0,0)==(false));
   assert(testtree2fire(foresttesta,foresttestb,0,0)==(true));
   /*should be false as from fire to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,1)==(false));
   assert(testfire2empty(foresttesta,foresttestb,0,1)==(true));
   /*false as should be tree to fire*/
   assert(testcompareinout(foresttesta,foresttestb,0,2)==(false));
   assert(testtree2fire(foresttesta,foresttestb,0,2)==(true));
   /*true as tree hasn't burned yet*/
   assert(testcompareinout(foresttesta,foresttestb,0,3)==(true));
   assert(testtree2fire(foresttesta,foresttestb,0,3)==(false));
   assert(testcompareinout(foresttesta,foresttestb,0,4)==(true));
   /*should be false as burning*/
   assert(testcompareinout(foresttesta,foresttestb,1,0)==(false));
   assert(testtree2fire(foresttesta,foresttestb,1,0)==(true));
   assert(testfire2empty(foresttesta,foresttestb,1,0)==(false));
   /*should be false as burning*/
   assert(testcompareinout(foresttesta,foresttestb,1,1)==(false));
   assert(testtree2fire(foresttesta,foresttestb,1,1)==(true));
   /*should be false as burning*/
   assert(testcompareinout(foresttesta,foresttestb,1,2)==(false));
   assert(testtree2fire(foresttesta,foresttestb,1,2)==(true));
   /*check second iteration of burn and spread*/
   outputtoinput(foresttestb, foresttesta);
   fireburnspread(foresttesta, foresttestb);
   /*should be false as from fire to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,0)==(false));
   assert(testfire2empty(foresttesta,foresttestb,0,0)==(true));
   /*true as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,1)==(true));
   /*false as fire to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,2)==(false));
   assert(testfire2empty(foresttesta,foresttestb,0,2)==(true));
   /*false as on fire*/
   assert(testcompareinout(foresttesta,foresttestb,0,3)==(false));
   assert(testfire2empty(foresttesta,foresttestb,0,3)==(false));
   /*true as empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,4)==(true));
   /*should be false as changed to empty*/
   assert(testcompareinout(foresttesta,foresttestb,1,0)==(false));
   assert(testfire2empty(foresttesta,foresttestb,1,0)==(true));
   /*should be false as changed to empty*/
   assert(testcompareinout(foresttesta,foresttestb,1,1)==(false));
   assert(testfire2empty(foresttesta,foresttestb,1,1)==(true));
   /*should be false as changed to empty*/
   assert(testcompareinout(foresttesta,foresttestb,1,2)==(false));
   assert(testfire2empty(foresttesta,foresttestb,1,2)==(true));
   /*check second iteration of burn and spread*/
   outputtoinput(foresttestb, foresttesta);
   fireburnspread(foresttesta, foresttestb);
   /*true as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,0)==(true));
   /*true as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,1)==(true));
   /*true as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,2)==(true));
   /*false as fire to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,3)==(false));
   assert(testfire2empty(foresttesta,foresttestb,0,3)==(true));
   /*empty as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,4)==(true));
   /*true as tree as fire won't spread from empty*/
   assert(testcompareinout(foresttesta,foresttestb,0,5)==(true));
   /*true as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,1,0)==(true));
   /*true as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,1,1)==(true));
   /*true as empty to empty*/
   assert(testcompareinout(foresttesta,foresttestb,1,2)==(true));
   /*checks probabilities of trees populating*/
   assert(testtreegeneration(foresttesta, foresttestb)==(true));
   /*checks probability of fires if all board is tree*/
   assert(testfiregeneration(foresttesta, foresttestb)==(true));
}

bool testcompareinout(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH],
                      int y, int x)
{
   char a, b;
   /*dereferences what is pointed to*/
   a = compare1[y][x];
   b = compare2[y][x];
   /*checks if both same*/
   if (a == b){
      return true;
   }
   else {
      return false;
      }
}

bool testtree2fire(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH],
                   int y, int x)
{
   char a, b;

   a = compare1[y][x];
   b = compare2[y][x];
   /*checking if tree is turning into a fire*/
   if (a == TREE && b == FIRE){
      return true;
      }
   else {
      return false;
      }
}

bool testfire2empty(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH],
                    int y, int x)
{
   char a, b;

   a = compare1[y][x];
   b = compare2[y][x];

   if (a == FIRE && b == EMPTY){
      return true;
      }
   else {
      return false;
      }
}

bool testtreegeneration(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH])
{
   int i, y, x, counter = 0;
   /*fill board with trees to check probability and counts how many*/
   for (i = 0; i < GENERATIONS; i++)
   {
      populatetrees(compare1, compare2);
      }
   for(y = 0; y < HEIGHT; ++y){
      for(x = 0; x < WIDTH; ++x){
         if (compare2[y][x] == TREE){
            counter = counter + 1;
            }
         }
      }
   /*2300 as prob of no tree is (249/250)^1000(gen) (100%-approx 1%) so 98%
   of cells will have trees and rounded down to nearest 100*/
   if (counter >= NUMBEROFTREESBASEDONPROB){ /*change if G  changed*/
      return true;
      }
   else {
      return false;
      }
}

bool testfiregeneration(char compare1[HEIGHT][WIDTH], char compare2[HEIGHT][WIDTH])
{
   int i, y, x, counter = 0;
   /*fills board with trees*/
   for (y = 0; y < HEIGHT; ++y){
      for (x = 0; x < WIDTH; ++x){
         compare1[y][x] = TREE;
         }
      }
   for (i = 0; i < GENERATIONS; i++){
      lightning(compare1, compare2); /*change if G or L changed*/
      }
   for (y = 0; y < HEIGHT; ++y){
      for (x = 0; x < WIDTH; ++x){
         if (compare2[y][x] == FIRE){
            counter = counter + 1;
            }
         }
      }
   /*2300 as prob of no tree is (2499/2500)^1000(gen) (100%-approx 67%) so 32%
      of cells will have trees and rounded down to nearest 100*/
   if (counter >= NUMBEROFFIRESBASEDONPROB){
      return true;
      }
   else {
      return false;
      }
}


void outputtoinput(char outforest[HEIGHT][WIDTH], char inforest[HEIGHT][WIDTH])
{
   int y, x;

   for (y = 0; y < HEIGHT; ++y){
      for (x = 0; x < WIDTH; ++x){
         inforest[y][x] = outforest[y][x];
         }
      }
}

void printforest(char forest[HEIGHT][WIDTH])
{
   int y, x;
   /*will print out forest for each iteration in main*/
   for (y = 0; y < HEIGHT; ++y){
      /*printf("%02d ", y + 1);*/ /*remove after debug*/
      for (x = 0; x < WIDTH; ++x){
         if (forest[y][x] == TREE){
            neillfgcol(green);
            }
         else if (forest[y][x] == FIRE){
            neillfgcol(red);
            }
         printf("%c", forest[y][x]);
         neillfgcol(white);
         }
      printf("\n");
      }
   /*printf("end\n"); *//*remove after debug*/
}

int probofg(void)
{
   return rand() % G; /*random number between 0 - G-1*/
}

int probofl(void)
{
   return rand() % L; /*returns number between 0 and L-1*/
}

void forestinit(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH])
{
   int y, x;

   for (y = 0; y < HEIGHT; ++y){
      for (x = 0; x < WIDTH; ++x){
         inforest[y][x] = EMPTY;
         outforest[y][x] = EMPTY; /*fills empty forest with spaces*/
         }
      }
}

void populatetrees(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH] )
{
   int y, x;

   for (y = 0; y < HEIGHT; ++y){
      for (x = 0; x < WIDTH; ++x){
         /*if the cell is empty and also if it is 1 in G chance*/
         if ((probofg() == 0) && (inforest[y][x] == EMPTY)){
            outforest[y][x] = TREE;
            }
         }
      }
}

void lightning(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH])
{
   int y, x;

   for (y = 0; y < HEIGHT; ++y){
      for (x = 0; x < WIDTH; ++x){
         /*if 1 in L chance + if cell has tree in it then fire*/
         if ((probofl() == 0) && (inforest[y][x] == TREE)){
            outforest[y][x] = FIRE;
            }
         }
      }
}

void fireburnspread(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH])
{
   int y, x;
   /*extinguishes fire after 1 generation in main*/
   for (y = 0; y < HEIGHT; ++y){
      for (x = 0; x < WIDTH; ++x){
         if (inforest[y][x] == FIRE){
            outforest[y][x] = EMPTY;
            next2trees(inforest, outforest, y, x);
            }
         }
      }
}

void next2trees(char inforest[HEIGHT][WIDTH], char outforest[HEIGHT][WIDTH],
                int y, int x)
{
   int rowsleft2check, colsleft2check;
   /*checks the neighbouring y cells*/
   for (rowsleft2check = (y + NEIGHBOURS); rowsleft2check >= (y - NEIGHBOURS);
        --rowsleft2check){
      /*checks the neighbouring x cells*/
      for (colsleft2check = (x + NEIGHBOURS); colsleft2check >= (x - NEIGHBOURS);
           --colsleft2check){
         /*keeps inbound of array*/
         if ((rowsleft2check >= 0 && rowsleft2check < HEIGHT) &&
             (colsleft2check >= 0 && colsleft2check < WIDTH)){
            if (inforest[rowsleft2check][colsleft2check] == TREE){
               outforest[rowsleft2check][colsleft2check] = FIRE;
               }
            }
         }
      colsleft2check = x + NEIGHBOURS;  /*reset width to original*/
      }
}
