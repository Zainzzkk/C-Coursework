#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "bool.h"


#define CHARSIZE 2
#define CHAR 0
#define INSTCTSIZE 1000
#define MAXCHARS 10
#define ALPHACHAR 26
#define LEN 30
#define EMPTY 5001
#define NOTEMPTY 5000

typedef struct Instructions {
   char instructs[INSTCTSIZE][MAXCHARS];
   double setvar[ALPHACHAR];
   unsigned int cw;
   unsigned int maxwds;
   } Instructions;

void test(void);
bool scanfile(Instructions* i, char filename[LEN]);
void zeroit(Instructions* i);
bool mainstart(Instructions* i);
bool endbrace(Instructions* i);
bool instrctlst(Instructions* i);
bool instrctlstrules(Instructions* i);
bool charlimit(Instructions* i, char* var);
bool varnumvalue(Instructions* i, char* var, double* varnum);
bool doinst(Instructions* i, char* var, char* var1, char* var2,
            double* varnum1, double* varnum2);
bool varnumone(Instructions* i, double* varnum, char* varchar);
bool varnumtwo(Instructions* i, double* varnum, char* varchar);
bool doloop(int* varnum, char* varchar, double* varnumnum);
bool dofromto(Instructions* i, char* var, char* varchar1,
              char* varchar2, double* varnum1, double* varnum2);
void changevaluevar(Instructions* i, char* varchar, double loopnum);
void resetvaluevar(Instructions* i, char* varchar);
bool set(Instructions* i, char* var);
bool polish(Instructions* i, char* var);
bool charalonelimit(char* var);
bool endstack(Instructions* i);
bool stackplus(Instructions* i);
bool stackminus(Instructions* i);
bool stackmult(Instructions* i);
bool stackdivide(Instructions* i);
