#include "parser.h"

int main(int argc, char* argv[])
{
   Instructions i;

   zeroit(&i);
   assert(argc==2);

   if (scanfile(&i, argv[1])==false){
      return 1;
      }

   if (mainstart(&i) == false){
      printf("Failed\n");
      return 1;
      }
   printf("Passed\n");
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
