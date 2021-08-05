#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <SDL.h>
#include "bool.h"
#include "neillsdl2.h"
#include "stack.h"

#define CHARSIZE 2
#define CHAR 0
#define INSTCTSIZE 1000
#define MAXCHARS 10
#define ALPHACHAR 26
#define LEN 30
#define EMPTY 5001
#define NOTEMPTY 5000
#define RIGHT 1
#define LEFT 0
#define FULLANGLE 360
#define STARTANGLE 1
#define RGB 3
#define RED 0
#define GREEN 1
#define BLUE 2
#define NAME 1
#define NOTNAME 0
#define WHITE 255
#define NODELAY 0

typedef struct Instructions {
   char instructs[INSTCTSIZE][MAXCHARS];
   double setvar[ALPHACHAR];
   int RGBcol[RGB];
   int nme;
   int cw;
   int maxwds;
   } Instructions;

typedef struct Coordinates {
   double angle;
   double x1;
   double x2;
   double y1;
   double y2;
   }Coordinates;

#define DELAYTIME 10

/*scans in file*/
bool scanfile(Instructions* i, char filename[LEN]);
/*sets variables value to empty and \0 all cells*/
void zeroit(Instructions* i, Coordinates* c);
/*checks opens with {*/
bool mainstart(Instructions* i, Coordinates* c, SDL_Simplewin *sw);
/*checks closes with a }*/
bool endbrace(Instructions* i, Coordinates* c, SDL_Simplewin *sw);
/*recursive instruction list*/
bool instrctlst(Instructions* i, Coordinates* c, SDL_Simplewin *sw);
/*checks only instructions or } enter function*/
bool instrctlstrules(Instructions* i);
/*checks VAR is from A-Z*/
bool charlimit(Instructions* i, char* var);
/*gets value of angle or distance (if var \0 then number)*/
bool varnumvalue(Instructions* i, char* var, double* varnum);
/*gives back value if VAR is set*/
bool charvarvalue(Instructions* i, char* var, double* varnum);
/*checks first part of do loop */
bool doinst(Instructions* i, char* var, char* var1, char* var2,
            double* varnum1, double* varnum2);
/*checks that is legal up to TO*/
bool varnumone(Instructions* i, double* varnum, char* varchar);
/*checks legal up to opening bracket*/
bool varnumtwo(Instructions* i, double* varnum, char* varchar);
/*gets value from and to for the do loop*/
bool doloop(Instructions* i, int* varnum, char* varchar, double* varnumnum);
/*executes the loop*/
bool dofromto(Instructions* i, Coordinates* c, SDL_Simplewin *sw, char* var, char* varchar1,
              char* varchar2, double* varnum1, double* varnum2);
/*changes the value of VAR as loop progresses*/
void changevaluevar(Instructions* i, char* varchar, double loopnum);
/*resets set value once set time over*/
void resetvaluevar(Instructions* i, char* varchar);
/*checks legality of set instruction*/
bool set(Instructions* i, char* var, double* setvalue);
/*recursive function for polish notation*/
bool polish(Instructions* i, stack* s, char* var);
/*checks if character is between A-Z without using array*/
bool charalonelimit(char* var);
/*sets value to var and checks nothing left on stack*/
bool endstack(Instructions* i, stack* s, char* var);
/*add function for stack*/
bool stackplus(Instructions* i, stack* s);
/* - function for stack*/
bool stackminus(Instructions* i, stack* s);
/* * for stack*/
bool stackmult(Instructions* i, stack* s);
/* / for stack*/
bool stackdivide(Instructions* i, stack* s);
/*if using VAR makes sure is set in stack*/
bool stackpushchar(Instructions* i, stack* s, char* varnumchar);
/*draws to screen if FD or calculates angle*/
void coordinateinst(Instructions* i, Coordinates* c, double varnum, SDL_Simplewin *sw);
/*calculates xy coordinates*/
void xypositions(Coordinates* c, double distance);
/*calculates new angle*/
void difference(Coordinates* c, double angle, int a);
/*prints off intro screen*/
void startscreen(void);
/*enter choice after start screen and colour*/
bool scannumber(int* scanner, char file[LEN]);
/*enter in instructions for draw if no file*/
bool enterinstrcts(Instructions* i);
/*review and change certain lines of instructs - recursive*/
bool reviewinstructs(Instructions* i);
/*changes the actual instructions*/
bool linenumber(Instructions* i);
/*select colour for lines*/
void colourselect(Instructions* i, Coordinates* c);
/*enters name if choose option 3*/
bool nameentry(Instructions* i, Coordinates* c);
/*opens alphabet ttl files*/
bool scanfilename(Instructions* i, char letter, int length);
/*conditions based on scanned in number*/
bool scancond(Instructions* i, Coordinates* c, char* file, int scanner);
void test(void);
