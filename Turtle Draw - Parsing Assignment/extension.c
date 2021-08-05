#include "extension.h"

int main(void)
{
   Instructions i;
   Coordinates c;
   int scanner;
   char file[LEN];

   SDL_Simplewin sw;

   startscreen();
   colourselect(&i, &c);

   if (scannumber(&scanner, file) == false){
      printf("incorrect option entered\n");
      return 1;
      }
   if (scancond(&i, &c, file, scanner) == false){
      return 1;
      }

   Neill_SDL_Init(&sw);

   if (mainstart(&i, &c, &sw) == false){
      printf("Failed\n");
      return 1;
      }

   do {
      Neill_SDL_Events(&sw);
      } while (!sw.finished);
   SDL_Quit();
   atexit(SDL_Quit);

   return 0;
}

void startscreen(void)
{
   printf("Welcome to Turtle Drawing\n");
   printf("Please select colour first\n");
}

bool scannumber(int* scanner, char file[LEN])
{
   printf("Please type 1 to write in instructions\n");
   printf("Please type 2 to type in filename\n");
   printf("Please type 3 to print your name in SDL\n");
   printf("Please enter your choice: ");
   if (scanf("%d", scanner) != 1){
      return false;
      }
   if (*scanner == 1){
      return true;
      }
   if (*scanner == 2){
      printf("Please enter file name: ");
      if (scanf("%s", file) != 1){
         printf("Please enter again");
         }
      printf("Filename entered succesfully\n");
      return true;
      }
   if (*scanner == 3){
      return true;
      }
   return false;
}

bool scancond(Instructions* i, Coordinates* c, char* file, int scanner)
{
   if (scanner == 1){
      /*if wrong instructions*/
      if (enterinstrcts(i) == true){
         return true;
         }
      i->nme = NOTNAME;
      }
   else if (scanner == 2) {
      if (scanfile(i, file) == true){
         return true;
         }
      i->nme = NOTNAME;
      }
   else if (scanner == 3) {
      if (nameentry(i, c) == true){
         i->nme = NAME;
         return true;
            }
      }
   return false;
}

bool nameentry(Instructions* i, Coordinates* c)
{
   int j;
   char name[LEN] = "\0";
   int n;

   printf("Please enter your name: ");

   if (scanf("%s", name) != 1){
      return false;
      }
   n = strlen(name);
   strcpy(i->instructs[0], "{");
   for (j = 0; j < n; j++){
      /*tolower as filenames are lowercase*/
      if (scanfilename(i, tolower(name[j]), n) == false){
         return false;
         }
      }
   /*starting angle for letters*/
   c->angle = 270;
   c->x1 = 100;
   c->y1 = 400;
   return true;

}

bool enterinstrcts(Instructions* i)
{
   int n = 0;
   printf("Please enter instructions with enter after each line and END when finished\n");
   do {
      if (scanf("%s", i->instructs[n]) != 1){
         return false;
      }
      n++;
   } while (strcmp(i->instructs[n-1], "END") != 0);
   /*as do not want the END to be read*/
   i->maxwds = n - 2;
   strcpy(i->instructs[n], "\0");
   i->cw = 0;
   if(reviewinstructs(i) == false){
      return false;
      }
   printf("Instructions entered successfully\n");
   return true;
}

bool reviewinstructs(Instructions* i)
{
   int d, n, choice;

   printf("Would you like to review your instructions?\n");
   printf("1 for yes, 2 for no: ");
   if (scanf("%d", &d) != 1){
      return false;
      }
   if (d == 1){
      /*prints off instructions with line number*/
      for (n = 0; n <= i->maxwds; n++){
         printf("%02d %s\n",n, i->instructs[n]);
         }
      printf("Would you like to change any instructions?\n");
      printf("1 for yes, 2 for no\n");
      if (scanf("%d", &choice) != 1){
         return false;
         }
      if (choice == 1){
         if (linenumber(i) == true){
            /*recursive until no more to change*/
            return reviewinstructs(i);
            }
         }
      if (choice == 2){
         return true;
         }
      }
   if (d == 2){
      return true;
   }
   return false;
}

bool linenumber(Instructions* i)
{
   int d, choice;
   char temp[LEN];

   printf("please enter line number\n");
   if (scanf("%d", &d) != 1){
      return false;
      }
   if ((d >= 0) && (d <= i->maxwds)){
      printf("Please enter the instruction\n");
      if (scanf("%s", temp) != 1){
         return false;
         }
      printf("Please confirm with 1 for yes or 2 for no\n");
      printf("%s will be replaced by %s\n", i->instructs[d], temp);
      printf("Choice: ");
      if (scanf("%d", &choice) != 1){
         return false;
         }
      if (choice == 1){
         strcpy(i->instructs[d], temp);
         return true;
         }
      if (choice == 2){
         return linenumber(i);
         }
      }
   return false;
}

void colourselect(Instructions* i, Coordinates* c)
{
   int choice;
   SDL_Simplewin sw;

   Neill_SDL_Init(&sw);

   zeroit(i, c);

   printf("Please select colour values for Red Blue and Green\n");
   printf("Red: ");
   if (scanf("%d", &i->RGBcol[RED]) != 1){
      i->RGBcol[RED]=WHITE;
      i->RGBcol[GREEN]=WHITE;
      i->RGBcol[BLUE]=WHITE;
      zeroit(i, c);
      return;
      }
   printf("Green: ");
   if (scanf("%d", &i->RGBcol[GREEN]) != 1){
      i->RGBcol[GREEN]=WHITE;
      i->RGBcol[BLUE]=WHITE;
      zeroit(i, c);
      return;
      }
   printf("Blue: ");
   if (scanf("%d", &i->RGBcol[BLUE]) != 1){
      i->RGBcol[BLUE]=WHITE;
      zeroit(i, c);
      return;
      }
   i->cw = 0;
   i->maxwds = 3;
   strcpy(i->instructs[0], "FD");
   strcpy(i->instructs[1], "100");
   strcpy(i->instructs[2], "}");
   instrctlst(i, c, &sw);
   Neill_SDL_Events(&sw);

   printf("Please check the line colour - Are you happy with your choice? 1 for yes, 2 for no: ");
   if (scanf("%d", &choice) != 1){
      zeroit(i, c);
      SDL_Quit();
      return;
      }
   if (choice == 2){
      SDL_Quit();
      colourselect(i, c);
      }
   zeroit(i, c);
   SDL_Quit();
   return;
}

void zeroit(Instructions* i, Coordinates* c)
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

      c->angle = 90;
      c->x1 = 500;
      c->y1 = 400;
}
/*modified to one made in lab session*/
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
      /*reads 1 at a time*/
      if (fscanf(fp, "%s", i->instructs[n]) == 1){
         n++;
         }
      else {
         read = true;
         }
      } while (read == false);
      /*since array starts at 0*/
      i->maxwds = n - 1;
      i->cw = 0;

   if (reviewinstructs(i) == false){
      return false;
      }

   return true;
}

bool scanfilename(Instructions* i, char letter, int length)
{
   static int n = 1;
   static int count = 1;
   FILE *fp;
   bool read = false;
   char filename[LEN] = "\0";
   /*all files have letter at beginning*/
   filename[CHAR] = letter;
   /*adds extension onto end*/
   strncat(filename, ".ttl", 5);

   if ((fp = fopen(filename, "r")) == NULL) {
      fprintf(stderr, "Cannot open file\n");
      return false;
      }

   do {
      /*reads 1 at a time*/
      if (fscanf(fp, "%s", i->instructs[n]) == 1){
         n++;
         }
      else {
         read = true;
         }
      } while (read == false);

   if (count == length){
      /*once reached last letter of name then add }*/
      strcpy(i->instructs[n], "}");
      i->cw = 0;
      i->maxwds = n;
      return true;
      }
   count++;
   return true;
}

bool mainstart(Instructions* i, Coordinates* c, SDL_Simplewin *sw)
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

   return endbrace(i, c, sw);
}

bool endbrace(Instructions* i, Coordinates* c, SDL_Simplewin *sw)
{
   if (i == NULL){
      fprintf(stderr, "File is empty\n");
      return false;
      }
   /*checks last word is a }*/
   if (strcmp(i->instructs[i->maxwds], "}") != 0){
      fprintf(stderr, "Closing } not detected!\n");
      return false;
      }
   return instrctlst(i,c, sw);
}

bool instrctlst(Instructions* i, Coordinates* c, SDL_Simplewin *sw)
{
   double varnum, varnum1, varnum2, setvalue;
   char var, varnumchar, varchar1, varchar2;
   /*no need to check if } as already done*/
   if (i->cw == i->maxwds){
      return true;
      }
   if (instrctlstrules(i) == false) {
      return false;
      }
   /*if any of the FD RT or LT then will work out xy*/
   if ((strcmp(i->instructs[i->cw], "FD") == 0) ||
       (strcmp(i->instructs[i->cw], "RT") == 0) ||
       (strcmp(i->instructs[i->cw], "LT") == 0)){
      i->cw++;
      if (varnumvalue(i, &varnumchar, &varnum) == true){
         /*\0 if number*/
         if (varnumchar == '\0'){
            coordinateinst(i, c, varnum, sw);
            /*makes 1 = 2 so that can draw shapes*/
            c->x1 = c->x2;
            c->y1 = c->y2;
            i->cw++;
            return instrctlst(i,c, sw);
            }
         /*will get value from char or false if not set*/
         else if (charvarvalue(i, &varnumchar, &varnum) == true){
            coordinateinst(i, c, varnum, sw);
            c->x1 = c->x2;
            c->y1 = c->y2;
            i->cw++;
            return instrctlst(i,c, sw);
            }
         }
      return false;
      }
      /*instructions for do loop*/
   else if (strcmp(i->instructs[i->cw], "DO") == 0){
      i->cw++;
      if (doinst(i, &var, &varchar1, &varchar2, &varnum1,
                 &varnum2)==true){
         if (dofromto(i,c, sw, &var, &varchar1, &varchar2, &varnum1,
                    &varnum2)==false)
            {
               return false;
            }
         i->cw++;
         return instrctlst(i,c, sw);
         }
      return false;
      }
   /*instructions for set loop*/
   else if (strcmp(i->instructs[i->cw], "SET") == 0){
      i->cw++;
      if (set(i, &var, &setvalue) == true){
         i->cw++;
         return instrctlst(i,c, sw);
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
   /*return if more than 1 character*/
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
   /*Will be \0 if not char*/
   if (strcmp(i->instructs[i->cw],"\0")==0){
      return false;
      }
   /*gets the value of the number in double*/
   tempnum = strtod(i->instructs[i->cw], &ptr);

   if (*ptr == '\0'){
      *varnum = tempnum;
      *var = '\0';
      return true;
      }
   else {
      if (charlimit(i, var) == true){
         if (charvarvalue(i, var, varnum)== true){
            return true;
            }
         }
      }
   return false;
}

bool charvarvalue(Instructions* i, char* var, double* varnum)
{
   int n;
   n = var[CHAR] - 'A';
   /*checks set has been used or var has number with it*/
   if (i->setvar[n] < EMPTY){
      *varnum = i->setvar[n];
      return true;
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

bool dofromto(Instructions* i, Coordinates* c, SDL_Simplewin *sw, char* var, char* varchar1,
              char* varchar2, double* varnum1, double* varnum2)
{
   int j, from, to, tempcw;

   if (doloop(i, &from, varchar1, varnum1)==false){
      return false;
      }
   if (doloop(i, &to, varchar2, varnum2)==false){
      return false;
      }
   /*remember which cw loop starts on*/
   tempcw = i->cw;
   for (j = from; j <= to; j++){
      /*reset to start of loop*/
      i->cw = tempcw;
      /*change value stored in VAR as loop goes up*/
      changevaluevar(i, var, j);
      /*goes through the do loop instructions*/
      if (instrctlst(i,c,sw)==false){
         return false;
         }
      }
   if (strcmp(i->instructs[i->cw], "}") != 0){
      return false;
      }
   /*since do loop over, set var value to be empty*/
   resetvaluevar(i, var);
   return true;
}

bool doloop(Instructions* i, int* varnum, char* varchar, double* varnumnum)
{
   int n;
   /*\0 if number and not char*/
   if (strcmp(varchar, "\0") == 0){
      *varnum = *varnumnum;
      return true;
      }
   else {
      if (charalonelimit(varchar)==false){
         return false;
         }
      /*find appropriate cell in array*/
      n = varchar[CHAR] - 'A';
      if (i->setvar[n] > NOTEMPTY){
         return false;
         }
      *varnum = i->setvar[n];
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

   n = varchar[CHAR] - 'A';
   i->setvar[n] = loopnum;

}

void resetvaluevar(Instructions* i, char* varchar)
{
   int n;

   n = varchar[CHAR] - 'A';
   i->setvar[n] = EMPTY;
}

bool set(Instructions* i, char* var, double* setvalue)
{
   stack* s;
   int n;
   s = stack_init();
   /*check first character is char*/
   if (charlimit(i, var) == false){
      stack_free(s);
      return false;
      }
   i->cw++;

   if (strcmp(i->instructs[i->cw],":=") != 0){
      stack_free(s);
      return false;
      }
   i->cw++;

   if (polish(i, s, var) == true){
      /*get the value stored for that character*/
      n = var[CHAR] - 'A';
      *setvalue = i->setvar[n];
      return true;
      }
   return false;

}

bool polish(Instructions* i, stack* s, char* var)
{
   char varnumchar[CHARSIZE];
   double varnum;
   /*check stack is empty at end*/
   if (endstack(i, s, var) == true){
      return true;
      }

   if (stackplus(i, s) == true){
      return polish(i, s, var);
      }
   else if (stackminus(i, s) == true){
      return polish(i, s, var);
      }
   else if (stackdivide(i, s) == true){
      return polish(i, s, var);
      }
   else if (stackmult(i, s) == true){
      return polish(i, s, var);
      }
   else if (varnumvalue(i, varnumchar, &varnum) == true){
      if (strcmp(varnumchar, "\0") == 0){
         stack_push(s, varnum);
         i->cw++;
         return polish(i, s, var);
         }
      else {
         if (stackpushchar(i, s, varnumchar)==true){
            return polish(i, s, var);
            }
         }
      }
   stack_free(s);
   return false;
}

bool endstack(Instructions* i, stack* s, char* var)
{
   double d;
   int n;

   if (strcmp(i->instructs[i->cw],";") == 0){
      assert(stack_pop(s, &d));
      n = var[CHAR] - 'A';
      i->setvar[n] = d;
      if(stack_peek(s, &d) == true){
         fprintf(stderr, "Stack still had items on it ?\n");
         return false;
         }
      stack_free(s);
      return true;
      }
   return false;
}

bool stackplus(Instructions* i, stack* s)
{
   double d, g1, g2;

   if (strcmp(i->instructs[i->cw], "+") == 0){
      assert(stack_pop(s, &g2));
      assert(stack_pop(s, &g1));
      d = g1 + g2;
      stack_push(s, d);
      i->cw++;
      return true;
      }
   return false;
}

bool stackminus(Instructions* i, stack* s)
{
   double d, g1, g2;

   if (strcmp(i->instructs[i->cw], "-") == 0){
      assert(stack_pop(s, &g2));
      assert(stack_pop(s, &g1));
      d = g1 - g2;
      stack_push(s, d);
      i->cw++;
      return true;
      }
   return false;
}

bool stackmult(Instructions* i, stack* s)
{
   double d, g1, g2;

   if (strcmp(i->instructs[i->cw], "*") == 0){
      assert(stack_pop(s, &g2));
      assert(stack_pop(s, &g1));
      d = g1 * g2;
      stack_push(s, d);
      i->cw++;
      return true;
      }

   return false;
}

bool stackdivide(Instructions* i, stack* s)
{
   double d, g1, g2;

   if (strcmp(i->instructs[i->cw], "/") == 0){
      assert(stack_pop(s, &g2));
      assert(stack_pop(s, &g1));
      d = g1 / g2;
      stack_push(s, d);
      i->cw++;
      return true;
      }

   return false;
}

bool stackpushchar(Instructions* i, stack* s, char* varnumchar)
{
   int n;

   n = varnumchar[CHAR] - 'A';
   if (i->setvar[n] > NOTEMPTY){
      return false;
      }
   stack_push(s, i->setvar[n]);
   i->cw++;
   return true;
}

void coordinateinst(Instructions* i, Coordinates* c, double varnum, SDL_Simplewin *sw)
{
   if (strcmp(i->instructs[i->cw-1], "FD")==0){
      xypositions(c,varnum);
      if (i->nme == 1){
         SDL_Delay(NODELAY);
         }
      else {
         SDL_Delay(DELAYTIME);
      }
      Neill_SDL_SetDrawColour(sw, i->RGBcol[RED], i->RGBcol[GREEN], i->RGBcol[BLUE]);
      SDL_RenderDrawLine(sw->renderer, c->x1, c->y1, c->x2, c->y2);
      Neill_SDL_UpdateScreen(sw);
      }
   if (strcmp(i->instructs[i->cw-1], "RT")==0){
      difference(c,varnum, RIGHT);
      }
   if (strcmp(i->instructs[i->cw-1], "LT")==0){
      difference(c,varnum, LEFT);
      }
}

void xypositions(Coordinates* c, double distance)
{
   double radiam;

   radiam = c->angle * (M_PI / 180);

   c->x2 = c->x1 + (distance * cos(radiam));
   c->y2 = c->y1 + (distance * sin(radiam));

}
/*for orientation add and subtract from constant angle value*/
void difference(Coordinates* c, double angle, int a)
{
   if (a == LEFT){
      c->angle = c->angle - angle;
      }
   if (a == RIGHT){
      c->angle = c->angle + angle;
      }
   /*wrap around*/
   if (c->angle > FULLANGLE){
      c->angle = c->angle - FULLANGLE;
      }

   if (c->angle < STARTANGLE){
      c->angle = FULLANGLE + c->angle;
      }
}
