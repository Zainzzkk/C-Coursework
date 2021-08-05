#include "parser.h"

int main(void)
{

   test();

   return 0;
}

void zeroit(Instructions* i)
{
   int m, n;

   for (n = 0; n < INSTCTSIZE; n++){
      for (m = 0; m < MAXCHARS; m++){
         i->instructs[n][m] = '\0';
         }
      }

   for (n = 0; n < ALPHACHAR; n++){
      i->setvar[n] = EMPTY;
      }
}


bool scanfile(Instructions* i, char filename[LEN])
{
   int n;
   FILE *fp;
   bool read = false;

   if ((fp = fopen(filename, "r")) == NULL) {
      fprintf(stderr, "Cannot open file\n");
      return false;
      }

   n = 0;
   do {
      if (fscanf(fp, "%s", i->instructs[n]) == 1){
         n++;
         }
      else {
         read = true;
         }
      } while (read == false);

      i->maxwds = n - 1;
      i->cw = 0;

   return true;
}

bool mainstart(Instructions* i)
{
   if ((i == NULL)||(strcmp(i->instructs[i->cw], "\0") == 0)){
      fprintf(stderr, "File is empty\n");
      return false;
      }
   if (strcmp(i->instructs[i->cw], "{") != 0){
      fprintf(stderr, "Opening { not detected!\n");
      return false;
      }
   i->cw++;

   return endbrace(i);
}

bool endbrace(Instructions* i)
{
   if (i == NULL){
      fprintf(stderr, "File is empty\n");
      return false;
      }
   if (strcmp(i->instructs[i->maxwds], "}") != 0){
      fprintf(stderr, "Closing } not detected!\n");
      return false;
      }
   return instrctlst(i);
}

bool instrctlst(Instructions* i)
{
   double varnum, varnum1, varnum2;
   char var, varnumchar, varchar1, varchar2;

   if (i->cw == i->maxwds){
      return true;
      }
   if (instrctlstrules(i) == false) {
      return false;
      }

   if ((strcmp(i->instructs[i->cw], "FD") == 0) ||
       (strcmp(i->instructs[i->cw], "RT") == 0) ||
       (strcmp(i->instructs[i->cw], "LT") == 0)){
      i->cw++;
      if (varnumvalue(i, &varnumchar, &varnum) == true){
         if (varnumchar == '\0'){
            i->cw++;
            return instrctlst(i);
            }
         else if (charlimit(i, &varnumchar) == true){
            i->cw++;
            return instrctlst(i);
            }
         }
      return false;
      }

   else if (strcmp(i->instructs[i->cw], "DO") == 0){
      i->cw++;
      if (doinst(i, &var, &varchar1, &varchar2, &varnum1,
                 &varnum2)==true){
         if (dofromto(i, &var, &varchar1, &varchar2, &varnum1,
                    &varnum2)==false){
               return false;
               }
         i->cw++;
         return instrctlst(i);
         }
      return false;
      }
   else if (strcmp(i->instructs[i->cw], "SET") == 0){
      i->cw++;
      if (set(i, &var) == true){
         i->cw++;
         return instrctlst(i);
         }
      return false;
      }
   return true;
}

bool instrctlstrules(Instructions* i)
{
   if (strcmp(i->instructs[i->cw], "FD") == 0){
      return true;
      }
   if (strcmp(i->instructs[i->cw], "RT") == 0){
      return true;
      }
   if (strcmp(i->instructs[i->cw], "LT") == 0){
      return true;
      }
   if (strcmp(i->instructs[i->cw], "DO") == 0){
      return true;
      }
   if (strcmp(i->instructs[i->cw], "SET") == 0){
      return true;
      }
   if (strcmp(i->instructs[i->cw], "}") == 0){
      return true;
      }

   return false;
}

bool charlimit(Instructions* i, char* var)
{
   char c[CHARSIZE];
   char v;
   if (strlen(i->instructs[i->cw]) != 1){
      return false;
      }

   strcpy(c, i->instructs[i->cw]);
   v = c[CHAR];

   if ((v >= 'A') && (v <= 'Z')){
      *var = v;
      return true;
      }

   return false;
}

bool varnumvalue(Instructions* i, char* var, double* varnum)
{
   char *ptr;
   double tempnum;

   if (strcmp(i->instructs[i->cw],"\0")==0){
      return false;
      }

   tempnum = strtod(i->instructs[i->cw], &ptr);

   if (*ptr == '\0'){
      *varnum = tempnum;
      *var = '\0';
      return true;
      }
   else {
      if (charlimit(i, var) == true){
         return true;
         }
      }
   return false;
}

bool doinst(Instructions* i, char* var, char* var1, char* var2,
            double* varnum1, double* varnum2)
{
   /*use var to remember char*/
   if (charlimit(i, var) == false){
      return false;
      }
   i->cw++;

   if (strcmp(i->instructs[i->cw], "FROM")!= 0){
      return false;
      }
   i->cw++;

   if (varnumone(i, varnum1, var1) == false){
      return false;
      }
   if (varnumtwo(i, varnum2, var2) == false){
      return false;
      }

   return true;
}

bool varnumone(Instructions* i, double* varnum, char* varchar)
{
   if (varnumvalue(i, varchar, varnum) == false){
      return false;
      }
   i->cw++;

   if (strcmp(i->instructs[i->cw], "TO") == 0){
      i->cw++;
      return true;
      }

   return false;
}

bool varnumtwo(Instructions* i, double* varnum, char* varchar)
{
   if (varnumvalue(i, varchar, varnum) == false){
      return false;
      }
   i->cw++;

   if (strcmp(i->instructs[i->cw], "{") == 0){
      i->cw++;
      return true;
      }

   return false;
}

bool dofromto(Instructions* i, char* var, char* varchar1,
              char* varchar2, double* varnum1, double* varnum2)
{
   int from, to;

   if (doloop(&from, varchar1, varnum1)==false){
      return false;
      }
   if (doloop(&to, varchar2, varnum2)==false){
      return false;
      }

   if (instrctlst(i)==false){
      return false;
      }

   if (strcmp(i->instructs[i->cw], "}") != 0){
      return false;
      }
   resetvaluevar(i, var);
   return true;
}

bool doloop(int* varnum, char* varchar, double* varnumnum)
{
   char var[CHARSIZE];

   if (strcmp(varchar, "\0") == 0){
      *varnum = *varnumnum;
      return true;
      }
   else {
      if (charalonelimit(varchar)==false){
         return false;
         }
      strcpy(var, varchar);
      *varnum = var[CHAR];
      return true;
   }

   return false;
}

bool charalonelimit(char* var)
{
   if (strlen(var) != 1){
      return false;
      }
   if ((var[CHAR] >= 'A') && (var[CHAR] <= 'Z')){
      return true;
      }
   return false;
}

void changevaluevar(Instructions* i, char* varchar, double loopnum)
{
   int n;

   n = varchar[0] - 'A';
   i->setvar[n] = loopnum;

}

void resetvaluevar(Instructions* i, char* varchar)
{
   int n;

   n = varchar[CHAR] - 'A';
   i->setvar[n] = EMPTY;
}

bool set(Instructions* i, char* var)
{

   if (charlimit(i, var) == false){
      return false;
      }
   i->cw++;

   if (strcmp(i->instructs[i->cw],":=") != 0){
      return false;
      }
   i->cw++;

   if (polish(i, var) == true){
      return true;
      }
   return false;

}

bool polish(Instructions* i, char* var)
{
   char varnumchar[CHARSIZE];
   double varnum;

   if (endstack(i) == true){
      return true;
      }

   if (stackplus(i) == true){
      return polish(i, var);
      }
   else if (stackminus(i) == true){
      return polish(i, var);
      }
   else if (stackdivide(i) == true){
      return polish(i, var);
      }
   else if (stackmult(i) == true){
      return polish(i, var);
      }
   else if (varnumvalue(i, varnumchar, &varnum) == true){
      if (strcmp(varnumchar, "\0") == 0){
         i->cw++;
         return polish(i, var);
         }
      else {
         if (charlimit(i, varnumchar) == true){
            i->cw++;
            return polish(i, var);
            }
         }
      }
   return false;
}

bool endstack(Instructions* i)
{

   if (strcmp(i->instructs[i->cw],";") == 0){
      return true;
      }
   return false;
}

bool stackplus(Instructions* i)
{
   if (strcmp(i->instructs[i->cw], "+") == 0){
      i->cw++;
      return true;
      }
   return false;
}

bool stackminus(Instructions* i)
{
   if (strcmp(i->instructs[i->cw], "-") == 0){
      i->cw++;
      return true;
      }
   return false;
}

bool stackmult(Instructions* i)
{

   if (strcmp(i->instructs[i->cw], "*") == 0){
      i->cw++;
      return true;
      }

   return false;
}

bool stackdivide(Instructions* i)
{

   if (strcmp(i->instructs[i->cw], "/") == 0){
      i->cw++;
      return true;
      }

   return false;
}

void test(void)
{
   Instructions test;
   int n, m;
   int testnum[2];
   char c;
   char vartest[2] = "A";
   char varfrom[2] = "A";
   char varto[2] = "A";
   double varnumtest[2];
   double from[2];
   double to[2];

   for (n = 0; n < 50; n++){
      for (m = 0; m < 10; m++){
         test.instructs[n][m] = '\0';
         }
      }

   for (n = 0; n < 26; n++){
      test.setvar[n] = 5001;
      }
   test.cw = 0;
   test.maxwds = 1;
   /*ensure null fails immediately*/
   assert(mainstart(&test)==false);
   /*ensure that no chars can pass the first check*/
   for (c = 'A'; c <= 'z'; c++){
      test.instructs[0][0] = c;
      assert(mainstart(&test)==false);
      }
   for (n = 0; n < 500; n++){
      test.instructs[0][0] = n;
      assert(mainstart(&test)==false);
      }
   /*and no <INSTRCTLST> commands can be used*/
   strcpy(test.instructs[0], "FD");
   assert(mainstart(&test)==false);
   strcpy(test.instructs[0], "RT");
   assert(mainstart(&test)==false);
   strcpy(test.instructs[0], "LT");
   assert(mainstart(&test)==false);
   strcpy(test.instructs[0], "DO");
   assert(mainstart(&test)==false);
   strcpy(test.instructs[0], "SET");
   assert(mainstart(&test)==false);
   /*simple program should pass*/
   test.cw = 0;
   test.maxwds = 3;
   strcpy(test.instructs[0], "{");
   strcpy(test.instructs[1], "FD");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], "}");
   assert(mainstart(&test)==true);
   assert(endbrace(&test)==true);
   /*break simple program*/
   for (c = 48; c <= 'z'; c++){
      test.cw = 0;
      test.instructs[0][0] = c;
      strcpy(test.instructs[1], "FD");
      strcpy(test.instructs[2], "5");
      strcpy(test.instructs[3], "}");
      assert(mainstart(&test)==false);
      }
   /*break closing brackets*/
   for (c = 48; c <= 'z'; c++){
      test.cw = 0;
      strcpy(test.instructs[0], "{");
      strcpy(test.instructs[1], "FD");
      strcpy(test.instructs[2], "5");
      test.instructs[3][0] = c;
      test.instructs[3][1] = '\0';
      assert(mainstart(&test)==false);
      assert(endbrace(&test)==false);
      }
   test.cw = 1;
   test.maxwds = 3;
   assert(instrctlst(&test)==true);
   /*no } will not trigger as already testing before
   coming to this function*/
   test.cw = 1;
   strcpy(test.instructs[1], "FD");
   assert(instrctlstrules(&test)==true);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==true);
   /*break FD*/
   test.cw = 1;
   strcpy(test.instructs[1], "FDd");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "FD1");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "Fd");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "fd");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "fD");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "FfD");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);

   test.cw = 1;
   strcpy(test.instructs[1], "RT");
   assert(instrctlstrules(&test)==true);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==true);
   /*break RT*/
   test.cw = 1;
   strcpy(test.instructs[1], "RTt");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "RT1");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "Rt");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "rt");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "rT");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "RrT");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);

   test.cw = 1;
   strcpy(test.instructs[1], "LT");
   assert(instrctlstrules(&test)==true);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==true);
   /*break LT*/
   test.cw = 1;
   strcpy(test.instructs[1], "LTt");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "LT1");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "Lt");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "lt");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "lT");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);
   test.cw = 1;
   strcpy(test.instructs[1], "LlT");
   assert(instrctlstrules(&test)==false);
   strcpy(test.instructs[2], "5");
   assert(instrctlst(&test)==false);

   /*test charlimit function*/
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   assert(charlimit(&test, vartest)==true);
   assert(strcmp(vartest, "A")==0);

   test.cw = 0;
   strcpy(test.instructs[0], "Q");
   assert(charlimit(&test, vartest)==true);
   assert(strcmp(vartest, "Q")==0);

   test.cw = 0;
   strcpy(test.instructs[0], "H");
   assert(charlimit(&test, vartest)==true);
   assert(strcmp(vartest, "H")==0);

   test.cw = 0;
   strcpy(test.instructs[0], "X");
   assert(charlimit(&test, vartest)==true);
   assert(strcmp(vartest, "X")==0);

   test.cw = 0;
   strcpy(test.instructs[0], "Z");
   assert(charlimit(&test, vartest)==true);
   assert(strcmp(vartest, "Z")==0);
   /*now to try to break the function*/
   test.cw = 0;
   strcpy(test.instructs[0], "a");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "z");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "g");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "AB");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "AA");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "ZZ");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "ZF");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "ZT");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "II");
   assert(charlimit(&test, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "1");
   assert(charlimit(&test, vartest)==false);
   strcpy(test.instructs[0], "4564654654");
   assert(charlimit(&test, vartest)==false);
   strcpy(test.instructs[0], "45646546540000000000000000000");
   assert(charlimit(&test, vartest)==false);
   strcpy(test.instructs[0], "{");
   assert(charlimit(&test, vartest)==false);
   strcpy(test.instructs[0], "}");
   assert(charlimit(&test, vartest)==false);
   strcpy(test.instructs[0], "0");
   assert(charlimit(&test, vartest)==false);
   strcpy(test.instructs[0], "\0");
   assert(charlimit(&test, vartest)==false);
   /*all pass the test including NULL character*/
   /*varnumvalue testing*/
   test.cw = 0;
   strcpy(test.instructs[0], "1");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "\0")==0);
   /*since cannot compare floats/doubles*/
   assert(varnumtest[0] < 1.01);
   assert(varnumtest[0] > 0.99);
   test.cw = 0;
   strcpy(test.instructs[0], "50.5");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "\0")==0);
   /*since cannot compare floats/doubles*/
   assert(varnumtest[0] < 50.501);
   assert(varnumtest[0] > 50.499);
   test.cw = 0;
   strcpy(test.instructs[0], "100000.54654");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "\0")==0);
   /*since cannot compare floats/doubles*/
   assert(varnumtest[0] < 100000.546541);
   assert(varnumtest[0] > 100000.5465399);
   test.cw = 0;
   strcpy(test.instructs[0], "-45");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "\0")==0);
   /*since cannot compare floats/doubles*/
   assert(varnumtest[0] > -45.01);
   assert(varnumtest[0] < -44.99);
   test.cw = 0;
   strcpy(test.instructs[0], "0");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "\0")==0);
   /*since cannot compare floats/doubles*/
   assert(varnumtest[0] > -0.001);
   assert(varnumtest[0] < 0.0001);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "A")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "Z");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "Z")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "Q");
   assert(varnumvalue(&test, vartest, varnumtest)==true);
   assert(strcmp(vartest, "Q")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "Aa");
   assert(varnumvalue(&test, vartest, varnumtest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "Za");
   assert(varnumvalue(&test, vartest, varnumtest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "a");
   assert(varnumvalue(&test, vartest, varnumtest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "a");
   assert(varnumvalue(&test, vartest, varnumtest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "{");
   assert(varnumvalue(&test, vartest, varnumtest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "}");
   assert(varnumvalue(&test, vartest, varnumtest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "\0");
   assert(varnumvalue(&test, vartest, varnumtest)==false);
   /*passed all tests*/

   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "1");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "5");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "1");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "5");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);
   assert(strcmp(vartest, "A")==0);
   assert(strcmp(varfrom, "\0")==0);
   assert(strcmp(varto, "\0")==0);
   assert(from[0] < 1.0001);
   assert(from[0] > 0.999);
   assert(to[0] < 5.001);
   assert(to[0] > 4.999);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "45.55");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "46.55");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);
   assert(strcmp(vartest, "A")==0);
   assert(strcmp(varfrom, "\0")==0);
   assert(strcmp(varto, "\0")==0);
   assert(from[0] < 45.55001);
   assert(from[0] > 45.54999);
   assert(to[0] < 46.55001);
   assert(to[0] > 46.54999);
   test.cw = 0;
   strcpy(test.instructs[0], "Aa");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "45.55");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "46.55");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "B");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "F");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);
   assert(strcmp(vartest, "A")==0);
   assert(strcmp(varfrom, "B")==0);
   assert(strcmp(varto, "F")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);
   assert(strcmp(vartest, "A")==0);
   assert(strcmp(varfrom, "A")==0);
   assert(strcmp(varto, "Z")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "B");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "46.55");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);
   assert(strcmp(vartest, "A")==0);
   assert(strcmp(varfrom, "B")==0);
   assert(strcmp(varto, "\0")==0);
   assert(to[0] < 46.55001);
   assert(to[0] > 46.54999);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "1");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);
   assert(strcmp(vartest, "A")==0);
   assert(strcmp(varfrom, "\0")==0);
   assert(strcmp(varto, "Z")==0);
   assert(from[0] < 1.0001);
   assert(from[0] > 0.999);
   /*try to break*/
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "Aa");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "{");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "}");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "}");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "}");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "\0");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "\0");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "13");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "a");
   strcpy(test.instructs[1], "FrOM");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "TO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "a");
   strcpy(test.instructs[1], "FROM");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "tO");
   strcpy(test.instructs[4], "Z");
   strcpy(test.instructs[5], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   /*passed all tests*/
   test.cw = 0;
   strcpy(test.instructs[0], "13");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 13.0001);
   assert(varnumtest[0] > 12.999);
   test.cw = 0;
   strcpy(test.instructs[0], "999.99");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 999.990001);
   assert(varnumtest[0] > 999.98999);
   test.cw = 0;
   strcpy(test.instructs[0], "0");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 0.0001);
   assert(varnumtest[0] > -0.0001);
   test.cw = 0;
   strcpy(test.instructs[0], "999.99");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 999.990001);
   assert(varnumtest[0] > 999.98999);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "A")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "Q");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "Q")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "Z");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "Z")==0);
   /*try to break*/
   test.cw = 0;
   strcpy(test.instructs[0], "Aa");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "K*");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "}");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "{");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "*");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "\0");
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "\0");
   assert(varnumone(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "\0");
   strcpy(test.instructs[1], "\0");
   assert(varnumone(&test, varnumtest, vartest)==false);
   /*passed test*/
   /*test varnumtwo*/
   test.cw = 0;
   strcpy(test.instructs[0], "13");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 13.0001);
   assert(varnumtest[0] > 12.999);
   test.cw = 0;
   strcpy(test.instructs[0], "999.99");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 999.990001);
   assert(varnumtest[0] > 999.98999);
   test.cw = 0;
   strcpy(test.instructs[0], "0");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 0.0001);
   assert(varnumtest[0] > -0.0001);
   test.cw = 0;
   strcpy(test.instructs[0], "999.99");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "\0")==0);
   assert(varnumtest[0] < 999.990001);
   assert(varnumtest[0] > 999.98999);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "A")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "Q");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "Q")==0);
   test.cw = 0;
   strcpy(test.instructs[0], "Z");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(strcmp(vartest, "Z")==0);
   /*try to break*/
   test.cw = 0;
   strcpy(test.instructs[0], "Aa");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   test.cw = 0;
   strcpy(test.instructs[0], "K*");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "}");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "{");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "*");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "\0");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "\0");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "\0");
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   strcpy(test.instructs[0], "B");
   strcpy(test.instructs[1], "{{");
   assert(varnumtwo(&test, varnumtest, vartest)==false);
   /*passed all tests*/
   /*test bool doloop(Instructions* i, int* varnum, char* varchar, double* varnumnum)
   now*/
   assert(doloop(testnum, "A", varnumtest)==true);
   assert(doloop(testnum, "B", varnumtest)==true);
   assert(doloop(testnum, "C", varnumtest)==true);
   assert(doloop(testnum, "D", varnumtest)==true);
   assert(doloop(testnum, "E", varnumtest)==true);
   assert(doloop(testnum, "F", varnumtest)==true);
   assert(doloop(testnum, "G", varnumtest)==true);
   assert(doloop(testnum, "H", varnumtest)==true);
   assert(doloop (testnum, "I", varnumtest)==true);
   assert(doloop( testnum, "J", varnumtest)==true);
   assert(doloop( testnum, "K", varnumtest)==true);
   assert(doloop( testnum, "L", varnumtest)==true);
   assert(doloop( testnum, "M", varnumtest)==true);
   assert(doloop( testnum, "N", varnumtest)==true);
   assert(doloop( testnum, "O", varnumtest)==true);
   assert(doloop( testnum, "P", varnumtest)==true);
   assert(doloop( testnum, "Q", varnumtest)==true);
   assert(doloop( testnum, "R", varnumtest)==true);
   assert(doloop( testnum, "S", varnumtest)==true);
   assert(doloop( testnum, "T", varnumtest)==true);
   assert(doloop( testnum, "U", varnumtest)==true);
   assert(doloop( testnum, "V", varnumtest)==true);
   assert(doloop( testnum, "W", varnumtest)==true);
   assert(doloop( testnum, "X", varnumtest)==true);
   assert(doloop( testnum, "Y", varnumtest)==true);
   assert(doloop( testnum, "Z", varnumtest)==true);
   varnumtest[0] = 0;
   assert(doloop( testnum, "\0", varnumtest)==true);
   assert(testnum[0]==0);
   varnumtest[0] = 500;
   assert(doloop( testnum, "\0", varnumtest)==true);
   assert(testnum[0]==500);
   varnumtest[0] = -55;
   assert(doloop( testnum, "\0", varnumtest)==true);
   assert(testnum[0]==-55);
   varnumtest[0] = 10000000;
   assert(doloop( testnum, "\0", varnumtest)==true);
   assert(testnum[0]==10000000);
   varnumtest[0] = 566.45645;
   assert(doloop( testnum, "\0", varnumtest)==true);
   assert(testnum[0]==566);
   /*try to break*/
   assert(doloop( testnum, "{", varnumtest)==false);
   assert(doloop( testnum, "*", varnumtest)==false);
   assert(doloop( testnum, "Zz", varnumtest)==false);
   assert(doloop( testnum, "A/", varnumtest)==false);
   assert(doloop( testnum, "a", varnumtest)==false);
   assert(doloop( testnum, "z", varnumtest)==false);
   assert(doloop( testnum, " ", varnumtest)==false);
   /*test passed*/
   /*TEST bool dofromto(Instructions* i, char* var, char* varchar1,
              char* varchar2, double* varnum1, double* varnum2)*/
              /*try to break from beginning*/
    strcpy(vartest, "A");
    strcpy(varfrom, "B");
    strcpy(varto, "C");
    assert(dofromto(&test, vartest, varfrom, varto, from, to) == false);
    strcpy(test.instructs[0], "DO");
    strcpy(test.instructs[1], "A");
    strcpy(test.instructs[2], "FROM");
    strcpy(test.instructs[3], "B");
    strcpy(test.instructs[4], "TO");
    strcpy(test.instructs[5], "C");
    strcpy(test.instructs[6], "{");
    strcpy(test.instructs[7], "FD");
    strcpy(test.instructs[8], "10");
    strcpy(test.instructs[9], "}");
    test.cw = 7;
    assert(dofromto(&test, vartest, varfrom, varto, from, to) == true);
    test.cw = 7;
    assert(dofromto(&test, vartest, varfrom, varto, from, to) == true);
    test.cw = 7;
    assert(dofromto(&test, vartest, varfrom, varto, from, to) == true);
    strcpy(vartest, "A");
    strcpy(varfrom, "\0");
    strcpy(varto, "\0");
    from[0] = 1;
    to[0] = 3;
    strcpy(test.instructs[0], "DO");
    strcpy(test.instructs[1], "A");
    strcpy(test.instructs[2], "FROM");
    strcpy(test.instructs[3], "1");
    strcpy(test.instructs[4], "TO");
    strcpy(test.instructs[5], "3");
    strcpy(test.instructs[6], "{");
    strcpy(test.instructs[7], "FD");
    strcpy(test.instructs[8], "10");
    strcpy(test.instructs[9], "}");
    test.cw = 7;
    assert(dofromto(&test, vartest, varfrom, varto, from, to) == true);
    strcpy(vartest, "A");
    strcpy(varfrom, "B");
    strcpy(varto, "\0");
    to[0] = 55;
    test.setvar[1] = 5;
    strcpy(test.instructs[0], "DO");
    strcpy(test.instructs[1], "A");
    strcpy(test.instructs[2], "FROM");
    strcpy(test.instructs[3], "B");
    strcpy(test.instructs[4], "TO");
    strcpy(test.instructs[5], "5");
    strcpy(test.instructs[6], "{");
    strcpy(test.instructs[7], "FD");
    strcpy(test.instructs[8], "10");
    strcpy(test.instructs[9], "}");
    test.cw = 7;
    assert(dofromto(&test, vartest, varfrom, varto, from, to) == true);
    /*tests passed - can mix numbers and letters*/

    assert(charalonelimit("A")==true);
    assert(charalonelimit("B")==true);
    assert(charalonelimit("C")==true);
    assert(charalonelimit("D")==true);
    assert(charalonelimit("E")==true);
    assert(charalonelimit("F")==true);
    assert(charalonelimit("G")==true);
    assert(charalonelimit("H")==true);
    assert(charalonelimit("I")==true);
    assert(charalonelimit("J")==true);
    assert(charalonelimit("K")==true);
    assert(charalonelimit("L")==true);
    assert(charalonelimit("M")==true);
    assert(charalonelimit("N")==true);
    assert(charalonelimit("O")==true);
    assert(charalonelimit("P")==true);
    assert(charalonelimit("Q")==true);
    assert(charalonelimit("R")==true);
    assert(charalonelimit("S")==true);
    assert(charalonelimit("T")==true);
    assert(charalonelimit("U")==true);
    assert(charalonelimit("V")==true);
    assert(charalonelimit("W")==true);
    assert(charalonelimit("X")==true);
    assert(charalonelimit("Y")==true);
    assert(charalonelimit("Z")==true);

    assert(charalonelimit("")==false);
    assert(charalonelimit(" ")==false);
    assert(charalonelimit("\0")==false);
    assert(charalonelimit("1")==false);
    assert(charalonelimit("{")==false);
    assert(charalonelimit("AA")==false);
    assert(charalonelimit("a")==false);
    assert(charalonelimit("z")==false);
    assert(charalonelimit("aa")==false);
    assert(charalonelimit("123")==false);
    assert(charalonelimit("A1")==false);
    assert(charalonelimit("Aa")==false);

   test.setvar[0] = 0;
   strcpy(test.instructs[0], "-");
   assert(stackplus(&test)==false);

   test.setvar[0] = 0;

   strcpy(test.instructs[0], "*");
   assert(stackdivide(&test)==false);

   test.setvar[0] = 0;

   strcpy(test.instructs[0], "*");
   assert(stackminus(&test)==false);

   test.setvar[0] = 0;
   strcpy(test.instructs[0], "/");
   assert(stackmult(&test)==false);
   /*test void resetvaluevar(Instructions* i, char* varchar)*/
   resetvaluevar(&test, "A");
   assert(test.setvar[0] > 5000);
   resetvaluevar(&test, "Z");
   assert(test.setvar[25] > 5000);
   /*passed test*/
   /*test bool polish(Instructions* i, stack* s, char* var)*/
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "+");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "-");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "/");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "4.5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "4.5");
   strcpy(test.instructs[1], "-5");
   strcpy(test.instructs[2], "+");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "25");
   strcpy(test.instructs[2], "-");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "1");
   strcpy(test.instructs[1], "4");
   strcpy(test.instructs[2], "/");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "8");
   strcpy(test.instructs[1], "2");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], "*");
   strcpy(test.instructs[4], "+");
   strcpy(test.instructs[5], "1");
   strcpy(test.instructs[6], "3");
   strcpy(test.instructs[7], "2");
   strcpy(test.instructs[8], "*");
   strcpy(test.instructs[9], "+");
   strcpy(test.instructs[10], "4");
   strcpy(test.instructs[11], "-");
   strcpy(test.instructs[12], "/");
   strcpy(test.instructs[13], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "*");
   strcpy(test.instructs[1], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "*");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "A")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "A");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "B");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "}");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==false);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==true);
   test.cw = 0;
   strcpy(test.instructs[0], "AA");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==false);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "\0");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==false);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "\0");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==false);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], " ");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], ";");
   assert(polish(&test, "Z")==false);
   test.cw = 0;
   strcpy(test.instructs[0], "5");
   strcpy(test.instructs[1], "5");
   strcpy(test.instructs[2], "*");
   strcpy(test.instructs[3], "}");
   assert(polish(&test, "Z")==false);
   /*passed all tests*/
   /*test bool set(Instructions* i, char* var, double* setvalue)*/
   test.cw = 0;
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":=");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "*");
   strcpy(test.instructs[5], ";");
   assert(set(&test, vartest)==true);
   /*should fail as setvarnotset*/
   test.cw = 0;
   strcpy(vartest, "C");
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":=");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "*");
   strcpy(test.instructs[5], ";");
   assert(set(&test, vartest )==true);
   test.cw = 0;
   strcpy(vartest, "C");
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":=");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "*");
   strcpy(test.instructs[5], ";");
   assert(set(&test, vartest)==true);
   /*try to break*/
   test.cw = 0;
   strcpy(vartest, "a");
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":=");
   strcpy(test.instructs[2], "A");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "*");
   strcpy(test.instructs[5], ";");
   assert(set(&test, vartest)==false);
   test.cw = 0;
   strcpy(vartest, "A");
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":=");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "*");
   strcpy(test.instructs[5], "}");
   assert(set(&test, vartest)==false);
   test.cw = 0;
   strcpy(vartest, "A");
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":=");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "5");
   strcpy(test.instructs[5], "}");
   assert(set(&test, vartest)==false);
   test.cw = 0;
   strcpy(vartest, "A");
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":");
   strcpy(test.instructs[2], "5");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "5");
   strcpy(test.instructs[5], "}");
   assert(set(&test, vartest)==false);
   test.cw = 0;
   strcpy(vartest, "A");
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], ":");
   strcpy(test.instructs[2], "=");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "5");
   strcpy(test.instructs[5], "*");
   strcpy(test.instructs[6], "}");
   assert(set(&test, vartest)==false);
   /*passed all tests*/

   changevaluevar(&test, "A", 5);
   assert(test.setvar[0] > 4.99999);
   assert(test.setvar[0] < 5.00001);
   changevaluevar(&test, "A", 3);
   assert(test.setvar[0] > 2.99999);
   assert(test.setvar[0] < 3.00001);
   changevaluevar(&test, "Z", 111.11);
   assert(test.setvar[25] > 111.1099999);
   assert(test.setvar[25] < 111.1100001);

   resetvaluevar(&test, "A");
   resetvaluevar(&test, "Z");

   assert(test.setvar[0] > 5000);
   assert(test.setvar[25] > 5000);

   test.cw = 0;
   test.maxwds = 25;

   strcpy(test.instructs[0], "{");
   strcpy(test.instructs[1], "FD");
   strcpy(test.instructs[2], "25");
   strcpy(test.instructs[3], "DO");
   strcpy(test.instructs[4], "A");
   strcpy(test.instructs[5], "FROM");
   strcpy(test.instructs[6], "1");
   strcpy(test.instructs[7], "TO");
   strcpy(test.instructs[8], "3");
   strcpy(test.instructs[9], "{");
   strcpy(test.instructs[10], "FD");
   strcpy(test.instructs[11], "20");
   strcpy(test.instructs[12], "RT");
   strcpy(test.instructs[13], "20");
   strcpy(test.instructs[14], "DO");
   strcpy(test.instructs[15], "B");
   strcpy(test.instructs[16], "FROM");
   strcpy(test.instructs[17], "1");
   strcpy(test.instructs[18], "TO");
   strcpy(test.instructs[19], "5");
   strcpy(test.instructs[20], "{");
   strcpy(test.instructs[21], "FD");
   strcpy(test.instructs[22], "5");
   strcpy(test.instructs[23], "}");
   strcpy(test.instructs[24], "}");
   strcpy(test.instructs[25], "}");

   assert(mainstart(&test)==true);
   /*testing scanfile*/
   assert(scanfile(&test, "TTLfiles/simp.ttl")==true);
   assert(mainstart(&test)==true);
   assert(scanfile(&test, "TTLfiles/spiral2_c.ttl")==true);
   assert(mainstart(&test)==true);
   /*file doesn't exist*/
   assert(scanfile(&test, "TTLfiles/simp12.ttl")==false);
   /*made an incorrect file*/
   assert(scanfile(&test, "TTLfiles/simpbroke_c.ttl")==true);
   assert(mainstart(&test)==false);
   /*mistake in file check if works*/
   assert(scanfile(&test, "TTLfiles/spiral2broken_c.ttl")==true);
   assert(mainstart(&test)==true);
   assert(scanfile(&test, "TTLfiles/passing.ttl")==true);
   assert(mainstart(&test)==true);
   /*passing parse but will not pass interpreter*/
   assert(scanfile(&test, "TTLfiles/passingparse.ttl")==true);
   assert(mainstart(&test)==true);

   /*testing complete*/
}
