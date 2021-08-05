#include "interpreter.h"

int main(void)
{
   test();

   return 0;
}

void test(void)
{
   Instructions test;
   int testnum[2];
   int n;
   char vartest[2];
   char varfrom[2];
   char varto[2];
   double varnumtest[2];
   double from[2];
   double to[2];
   stack* stest;
   Coordinates ctest;
   SDL_Simplewin sw;

   /*test void difference(Coordinates* c, double angle, int a)*/
   ctest.angle = 360; /*360 is 0*/
   /*test left*/
   difference(&ctest, 45, 0);
   assert(ctest.angle < 315.0001);
   assert(ctest.angle > 314.9999);
   ctest.angle = 360; /*360 is 0*/
   difference(&ctest, 360, 0);
   assert(ctest.angle < 360.0001);
   assert(ctest.angle > 359.9999);
   difference(&ctest, 90, 0);
   assert(ctest.angle < 270.0001);
   assert(ctest.angle > 269.9999);
   difference(&ctest, 180, 0);
   assert(ctest.angle < 90.0001);
   assert(ctest.angle > 89.9999);
   difference(&ctest, 360, 1);
   assert(ctest.angle < 90.0001);
   assert(ctest.angle > 89.9999);
   difference(&ctest, 180, 1);
   assert(ctest.angle < 270.0001);
   assert(ctest.angle > 269.9999);
   difference(&ctest, 91, 1);
   assert(ctest.angle < 1.0001);
   assert(ctest.angle > 0.9999);
   /*passed tests*/
   /*test void xypositions(Coordinates* c, double distance)*/
   ctest.x1 = 0;
   ctest.y1 = 0;
   ctest.angle = 90;
   xypositions(&ctest, 30);
   assert(ctest.y2 < 30.000001);
   assert(ctest.y2 > 29.999999);
   assert(ctest.x2 < 0.000001);
   assert(ctest.x2 > -0.000001);
   ctest.x1 = 0;
   ctest.y1 = 0;
   ctest.angle = 180;
   xypositions(&ctest, 30);
   assert(ctest.x2 > -30.000001);
   assert(ctest.x2 < -29.999999);
   assert(ctest.y2 < 0.000001);
   assert(ctest.y2 > -0.000001);
   ctest.x1 = 0;
   ctest.y1 = 0;
   ctest.angle = 270;
   xypositions(&ctest, 30);
   assert(ctest.x2 > -0.00001);
   assert(ctest.x2 < 0.000001);
   assert(ctest.y2 > -30.000001);
   assert(ctest.y2 < -29.999999);
   ctest.x1 = 0;
   ctest.y1 = 0;
   ctest.angle = 360;
   xypositions(&ctest, 30);
   assert(ctest.y2 > -0.00001);
   assert(ctest.y2 < 0.000001);
   assert(ctest.x2 < 30.000001);
   assert(ctest.x2 > 29.999999);
   ctest.x1 = 0;
   ctest.y1 = 0;
   ctest.angle = 45;
   xypositions(&ctest, 30);
   assert(ctest.y2 > 21.2132029999);
   assert(ctest.y2 < 21.213204);
   assert(ctest.x2 > 21.2132029999);
   assert(ctest.x2 < 21.213204);
   ctest.x1 = ctest.x2;
   ctest.y1 = ctest.y2;
   ctest.angle = 90;
   xypositions(&ctest, 30);
   ctest.x1 = ctest.x2;
   ctest.y1 = ctest.y2;
   ctest.angle = 135;
   xypositions(&ctest, 30);
   ctest.x1 = ctest.x2;
   ctest.y1 = ctest.y2;
   ctest.angle = 180;
   xypositions(&ctest, 30);
   ctest.x1 = ctest.x2;
   ctest.y1 = ctest.y2;
   ctest.angle = 225;
   xypositions(&ctest, 30);
   ctest.x1 = ctest.x2;
   ctest.y1 = ctest.y2;
   ctest.angle = 270;
   xypositions(&ctest, 30);
   ctest.x1 = ctest.x2;
   ctest.y1 = ctest.y2;
   ctest.angle = 315;
   xypositions(&ctest, 30);
   ctest.x1 = ctest.x2;
   ctest.y1 = ctest.y2;
   ctest.angle = 360;
   xypositions(&ctest, 30);
   assert(ctest.y2 > -0.00001);
   assert(ctest.y2 < 0.000001);
   assert(ctest.x2 > -0.00001);
   assert(ctest.x2 < 0.000001);
   /*passes test*/

   /*charvarvalue testing*/
   /*setvar values set to 5001 so empty*/
   for (n = 0; n < 26; n++){
      test.setvar[n] = 5001;
      }
   assert(charvarvalue(&test, "A", varnumtest)==false);
   assert(charvarvalue(&test, "B", varnumtest)==false);
   assert(charvarvalue(&test, "C", varnumtest)==false);
   assert(charvarvalue(&test, "D", varnumtest)==false);
   assert(charvarvalue(&test, "E", varnumtest)==false);
   assert(charvarvalue(&test, "F", varnumtest)==false);
   assert(charvarvalue(&test, "G", varnumtest)==false);
   assert(charvarvalue(&test, "H", varnumtest)==false);
   assert(charvarvalue(&test, "I", varnumtest)==false);
   assert(charvarvalue(&test, "J", varnumtest)==false);
   assert(charvarvalue(&test, "K", varnumtest)==false);
   assert(charvarvalue(&test, "L", varnumtest)==false);
   assert(charvarvalue(&test, "M", varnumtest)==false);
   assert(charvarvalue(&test, "N", varnumtest)==false);
   assert(charvarvalue(&test, "O", varnumtest)==false);
   assert(charvarvalue(&test, "P", varnumtest)==false);
   assert(charvarvalue(&test, "Q", varnumtest)==false);
   assert(charvarvalue(&test, "R", varnumtest)==false);
   assert(charvarvalue(&test, "S", varnumtest)==false);
   assert(charvarvalue(&test, "T", varnumtest)==false);
   assert(charvarvalue(&test, "U", varnumtest)==false);
   assert(charvarvalue(&test, "V", varnumtest)==false);
   assert(charvarvalue(&test, "W", varnumtest)==false);
   assert(charvarvalue(&test, "X", varnumtest)==false);
   assert(charvarvalue(&test, "Y", varnumtest)==false);
   assert(charvarvalue(&test, "Z", varnumtest)==false);
   /*NOW SET*/
   for (n = 0; n < 26; n++){
      test.setvar[n] = n * 2;
      }
   assert(charvarvalue(&test, "A", varnumtest)==true);
   assert(varnumtest[0] < 0.01);
   assert(varnumtest[0] > -0.01);
   assert(charvarvalue(&test, "B", varnumtest)==true);
   assert(varnumtest[0] < 2.001);
   assert(varnumtest[0] > 1.999);
   assert(charvarvalue(&test, "C", varnumtest)==true);
   assert(varnumtest[0] < 4.001);
   assert(varnumtest[0] > 3.999);
   assert(charvarvalue(&test, "D", varnumtest)==true);
   assert(varnumtest[0] < 6.001);
   assert(varnumtest[0] > 5.999);
   assert(charvarvalue(&test, "E", varnumtest)==true);
   assert(varnumtest[0] < 8.001);
   assert(varnumtest[0] > 7.999);
   assert(charvarvalue(&test, "F", varnumtest)==true);
   assert(varnumtest[0] < 10.001);
   assert(varnumtest[0] > 9.999);
   assert(charvarvalue(&test, "G", varnumtest)==true);
   assert(varnumtest[0] < 12.001);
   assert(varnumtest[0] > 11.999);
   assert(charvarvalue(&test, "H", varnumtest)==true);
   assert(varnumtest[0] < 14.001);
   assert(varnumtest[0] > 13.999);
   assert(charvarvalue(&test, "I", varnumtest)==true);
   assert(varnumtest[0] < 16.001);
   assert(varnumtest[0] > 15.999);
   assert(charvarvalue(&test, "J", varnumtest)==true);
   assert(varnumtest[0] < 18.001);
   assert(varnumtest[0] > 17.999);
   assert(charvarvalue(&test, "K", varnumtest)==true);
   assert(varnumtest[0] < 20.001);
   assert(varnumtest[0] > 19.999);
   assert(charvarvalue(&test, "L", varnumtest)==true);
   assert(varnumtest[0] < 22.001);
   assert(varnumtest[0] > 21.999);
   assert(charvarvalue(&test, "M", varnumtest)==true);
   assert(varnumtest[0] < 24.001);
   assert(varnumtest[0] > 23.999);
   assert(charvarvalue(&test, "N", varnumtest)==true);
   assert(varnumtest[0] < 26.001);
   assert(varnumtest[0] > 25.999);
   assert(charvarvalue(&test, "O", varnumtest)==true);
   assert(varnumtest[0] < 28.001);
   assert(varnumtest[0] > 27.999);
   assert(charvarvalue(&test, "P", varnumtest)==true);
   assert(varnumtest[0] < 30.001);
   assert(varnumtest[0] > 29.999);
   assert(charvarvalue(&test, "Q", varnumtest)==true);
   assert(varnumtest[0] < 32.001);
   assert(varnumtest[0] > 31.999);
   assert(charvarvalue(&test, "R", varnumtest)==true);
   assert(varnumtest[0] < 34.001);
   assert(varnumtest[0] > 33.999);
   assert(charvarvalue(&test, "S", varnumtest)==true);
   assert(varnumtest[0] < 36.001);
   assert(varnumtest[0] > 35.999);
   assert(charvarvalue(&test, "T", varnumtest)==true);
   assert(varnumtest[0] < 38.001);
   assert(varnumtest[0] > 37.999);
   assert(charvarvalue(&test, "U", varnumtest)==true);
   assert(varnumtest[0] < 40.001);
   assert(varnumtest[0] > 39.999);
   assert(charvarvalue(&test, "V", varnumtest)==true);
   assert(varnumtest[0] < 42.001);
   assert(varnumtest[0] > 41.999);
   assert(charvarvalue(&test, "W", varnumtest)==true);
   assert(varnumtest[0] < 44.001);
   assert(varnumtest[0] > 43.999);
   assert(charvarvalue(&test, "X", varnumtest)==true);
   assert(varnumtest[0] < 46.001);
   assert(varnumtest[0] > 45.999);
   assert(charvarvalue(&test, "Y", varnumtest)==true);
   assert(varnumtest[0] < 48.001);
   assert(varnumtest[0] > 47.999);
   assert(charvarvalue(&test, "Z", varnumtest)==true);
   assert(varnumtest[0] < 50.001);
   assert(varnumtest[0] > 49.999);
   /*all passed with numbers correct*/
   /*make sure all characters fail instrctlst*/
   for (n = 0; n < 26; n++){
      test.setvar[n] = 5001;
      }
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "A");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "A");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "A");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "B");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "B");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "B");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "C");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "C");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "C");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "D");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "D");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "D");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "E");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "E");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "E");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "F");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "F");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "F");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "G");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "G");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "G");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "H");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "H");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "H");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "I");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "I");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "I");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "J");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "J");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "J");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "K");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "K");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "K");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "L");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "L");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "L");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "M");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "M");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "M");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "N");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "N");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "N");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "O");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "O");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "O");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "P");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "P");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "P");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "Q");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "Q");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "Q");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "R");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "R");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "R");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "S");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "S");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "S");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "T");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "T");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "T");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "U");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "U");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "U");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "V");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "V");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "V");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "W");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "W");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "W");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "X");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "X");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "X");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "Y");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "Y");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "Y");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "Z");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "Z");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "Z");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == false);

   for (n = 0; n < 26; n++){
      test.setvar[n] = 5;
      }

   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "A");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "A");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "A");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "B");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "B");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "B");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "C");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "C");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "C");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "D");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "D");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "D");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "E");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "E");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "E");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "F");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "F");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "F");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "G");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "G");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "G");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "H");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "H");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "H");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "I");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "I");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "I");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "J");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "J");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "J");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "K");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "K");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "K");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "L");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "L");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "L");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "M");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "M");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "M");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "N");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "N");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "N");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "O");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "O");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "O");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "P");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "P");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "P");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "Q");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "Q");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "Q");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "R");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "R");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "R");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "S");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "S");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "S");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "T");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "T");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "T");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "U");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "U");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "U");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "V");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "V");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "V");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "W");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "W");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "W");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "X");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "X");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "X");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "Y");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "Y");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "Y");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   test.cw = 0;
   test.maxwds = 6;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "Z");
   strcpy(test.instructs[2], "RT");
   strcpy(test.instructs[3], "Z");
   strcpy(test.instructs[4], "LT");
   strcpy(test.instructs[5], "Z");
   strcpy(test.instructs[6], "}");
   assert(instrctlst(&test, &ctest, &sw) == true);
   /*passes tests*/

   /*test bool doloop(Instructions* i, int* varnum, char* varchar, double* varnumnum)
   now*/
   for (n = 0; n < 26; n++){
      test.setvar[n] = 5001;
      }
   varnumtest[0] = 0;
   assert(doloop(&test, testnum, "A", varnumtest)==false);
   assert(doloop(&test, testnum, "B", varnumtest)==false);
   assert(doloop(&test, testnum, "C", varnumtest)==false);
   assert(doloop(&test, testnum, "D", varnumtest)==false);
   assert(doloop(&test, testnum, "E", varnumtest)==false);
   assert(doloop(&test, testnum, "F", varnumtest)==false);
   assert(doloop(&test, testnum, "G", varnumtest)==false);
   assert(doloop(&test, testnum, "H", varnumtest)==false);
   assert(doloop(&test, testnum, "I", varnumtest)==false);
   assert(doloop(&test, testnum, "J", varnumtest)==false);
   assert(doloop(&test, testnum, "K", varnumtest)==false);
   assert(doloop(&test, testnum, "L", varnumtest)==false);
   assert(doloop(&test, testnum, "M", varnumtest)==false);
   assert(doloop(&test, testnum, "N", varnumtest)==false);
   assert(doloop(&test, testnum, "O", varnumtest)==false);
   assert(doloop(&test, testnum, "P", varnumtest)==false);
   assert(doloop(&test, testnum, "Q", varnumtest)==false);
   assert(doloop(&test, testnum, "R", varnumtest)==false);
   assert(doloop(&test, testnum, "S", varnumtest)==false);
   assert(doloop(&test, testnum, "T", varnumtest)==false);
   assert(doloop(&test, testnum, "U", varnumtest)==false);
   assert(doloop(&test, testnum, "V", varnumtest)==false);
   assert(doloop(&test, testnum, "W", varnumtest)==false);
   assert(doloop(&test, testnum, "X", varnumtest)==false);
   assert(doloop(&test, testnum, "Y", varnumtest)==false);
   assert(doloop(&test, testnum, "Z", varnumtest)==false);
   /*NOW SET*/
   for (n = 0; n < 26; n++){
      test.setvar[n] = n * 2;
      }
   assert(doloop(&test, testnum, "A", varnumtest)==true);
   assert(testnum[0]==0);
   assert(doloop(&test, testnum, "B", varnumtest)==true);
   assert(testnum[0]==2);
   assert(doloop(&test, testnum, "C", varnumtest)==true);
   assert(testnum[0]==4);
   assert(doloop(&test, testnum, "D", varnumtest)==true);
   assert(testnum[0]==6);
   assert(doloop(&test, testnum, "E", varnumtest)==true);
   assert(testnum[0]==8);
   assert(doloop(&test, testnum, "F", varnumtest)==true);
   assert(testnum[0]==10);
   assert(doloop(&test, testnum, "G", varnumtest)==true);
   assert(testnum[0]==12);
   assert(doloop(&test, testnum, "H", varnumtest)==true);
   assert(testnum[0]==14);
   assert(doloop(&test, testnum, "I", varnumtest)==true);
   assert(testnum[0]==16);
   assert(doloop(&test, testnum, "J", varnumtest)==true);
   assert(testnum[0]==18);
   assert(doloop(&test, testnum, "K", varnumtest)==true);
   assert(testnum[0]==20);
   assert(doloop(&test, testnum, "L", varnumtest)==true);
   assert(testnum[0]==22);
   assert(doloop(&test, testnum, "M", varnumtest)==true);
   assert(testnum[0]==24);
   assert(doloop(&test, testnum, "N", varnumtest)==true);
   assert(testnum[0]==26);
   assert(doloop(&test, testnum, "O", varnumtest)==true);
   assert(testnum[0]==28);
   assert(doloop(&test, testnum, "P", varnumtest)==true);
   assert(testnum[0]==30);
   assert(doloop(&test, testnum, "Q", varnumtest)==true);
   assert(testnum[0]==32);
   assert(doloop(&test, testnum, "R", varnumtest)==true);
   assert(testnum[0]==34);
   assert(doloop(&test, testnum, "S", varnumtest)==true);
   assert(testnum[0]==36);
   assert(doloop(&test, testnum, "T", varnumtest)==true);
   assert(testnum[0]==38);
   assert(doloop(&test, testnum, "U", varnumtest)==true);
   assert(testnum[0]==40);
   assert(doloop(&test, testnum, "V", varnumtest)==true);
   assert(testnum[0]==42);
   assert(doloop(&test, testnum, "W", varnumtest)==true);
   assert(testnum[0]==44);
   assert(doloop(&test, testnum, "X", varnumtest)==true);
   assert(testnum[0]==46);
   assert(doloop(&test, testnum, "Y", varnumtest)==true);
   assert(testnum[0]==48);
   assert(doloop(&test, testnum, "Z", varnumtest)==true);
   assert(testnum[0]==50);
   varnumtest[0] = 0;
   assert(doloop(&test, testnum, "\0", varnumtest)==true);
   assert(testnum[0]==0);
   varnumtest[0] = 500;
   assert(doloop(&test, testnum, "\0", varnumtest)==true);
   assert(testnum[0]==500);
   varnumtest[0] = -55;
   assert(doloop(&test, testnum, "\0", varnumtest)==true);
   assert(testnum[0]==-55);
   varnumtest[0] = 10000000;
   assert(doloop(&test, testnum, "\0", varnumtest)==true);
   assert(testnum[0]==10000000);
   varnumtest[0] = 566.45645;
   assert(doloop(&test, testnum, "\0", varnumtest)==true);
   assert(testnum[0]==566);

   test.cw = 0;
   strcpy(vartest, "A");
   test.setvar[0] = 5001;
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, 0, vartest)==false);
   test.cw = 0;
   strcpy(vartest, "A");
   varnumtest[0] = 0;
   test.setvar[0] = 2;
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], "TO");
   assert(varnumone(&test, varnumtest, vartest)==true);
   assert(varnumtest[0] > 1.9999);
   assert(varnumtest[0] < 2.000001);
   test.cw = 0;
   strcpy(vartest, "A");
   varnumtest[0] = 0;
   test.setvar[0] = 5001;
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, 0, vartest)==false);
   test.cw = 0;
   strcpy(vartest, "A");
   varnumtest[0] = 0;
   test.setvar[0] = 2;
   strcpy(test.instructs[0], vartest);
   strcpy(test.instructs[1], "{");
   assert(varnumtwo(&test, varnumtest, vartest)==true);
   assert(varnumtest[0] > 1.9999);
   assert(varnumtest[0] < 2.000001);

   for (n = 0; n < 26; n++){
      test.setvar[n] = 5001;
      }
   strcpy(vartest, "A");
   strcpy(varfrom, "B");
   strcpy(varto, "C");
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to) == false);
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
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to) == false);
   test.cw = 7;
   test.setvar[1] = 5;
   test.setvar[2] = 5001;
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to) == false);
   test.cw = 7;
   test.setvar[1] = 5;
   test.setvar[2] = 8;
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to) == true);
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
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to) == true);
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
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to) == true);
   /*tests passed - can mix numbers and letters*/

   for (n = 0; n < 26; n++){
      test.setvar[n] = 5001;
      }
   test.cw = 1;
   strcpy(test.instructs[0], "DO");
   strcpy(test.instructs[1], "A");
   strcpy(test.instructs[2], "FROM");
   strcpy(test.instructs[3], "5");
   strcpy(test.instructs[4], "TO");
   strcpy(test.instructs[5], "10");
   strcpy(test.instructs[6], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);
   test.cw = 1;
   strcpy(test.instructs[0], "DO");
   strcpy(test.instructs[1], "A");
   strcpy(test.instructs[2], "FROM");
   strcpy(test.instructs[3], "G");
   strcpy(test.instructs[4], "TO");
   strcpy(test.instructs[5], "10");
   strcpy(test.instructs[6], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==false);
   for (n = 0; n < 26; n++){
      test.setvar[n] = 5;
      }
   test.cw = 1;
   strcpy(test.instructs[0], "DO");
   strcpy(test.instructs[1], "A");
   strcpy(test.instructs[2], "FROM");
   strcpy(test.instructs[3], "G");
   strcpy(test.instructs[4], "TO");
   strcpy(test.instructs[5], "10");
   strcpy(test.instructs[6], "{");
   assert(doinst(&test, vartest, varfrom, varto, from, to)==true);

   for (n = 0; n < 26; n++){
      test.setvar[n] = 5001;
      }
   test.cw = 0;
   from[0] = 1;
   to[0] = 2;
   strcpy(varto, "\0");
   strcpy(varfrom, "\0");
   strcpy(vartest, "B");
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "30");
   strcpy(test.instructs[2], "FD");
   strcpy(test.instructs[3], "A");
   strcpy(test.instructs[4], "}");
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to)==false);
   for (n = 0; n < 26; n++){
      test.setvar[n] = 1;
      }
   test.cw = 0;
   from[0] = 1;
   to[0] = 2;
   strcpy(test.instructs[0], "FD");
   strcpy(test.instructs[1], "30");
   strcpy(test.instructs[2], "FD");
   strcpy(test.instructs[3], "A");
   strcpy(test.instructs[4], "}");
   assert(dofromto(&test, &ctest, &sw, vartest, varfrom, varto, from, to)==true);



  /*test void changevaluevar(Instructions* i, char* varchar, double loopnum)*/
  test.setvar[0] = 0;
  changevaluevar(&test, "A", 2);
  assert(test.setvar[0] > 0);
  assert(test.setvar[0] > 1.9999);
  assert(test.setvar[0] < 2.00001);
  test.setvar[25] = 33;
  changevaluevar(&test, "Z", 66);
  assert(test.setvar[25] > 65.999);
  assert(test.setvar[25] < 66.00001);
  /*passed*/
  test.setvar[0] = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "-");
  assert(stackplus(&test, stest)==false);
  stack_free(stest);
  test.setvar[0] = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "*");
  assert(stackdivide(&test, stest)==false);
  stack_free(stest);
  test.setvar[0] = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "*");
  assert(stackminus(&test, stest)==false);
  stack_free(stest);
  test.setvar[0] = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "/");
  assert(stackmult(&test, stest)==false);
  stack_free(stest);
  /*test void resetvaluevar(Instructions* i, char* varchar)*/
  resetvaluevar(&test, "A");
  assert(test.setvar[0] > 5000);
  resetvaluevar(&test, "Z");
  assert(test.setvar[25] > 5000);
  /*passed test*/
  /*test bool polish(Instructions* i, stack* s, char* var)*/
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "A")==true);
  assert(test.setvar[0] > 24.9999);
  assert(test.setvar[0] < 25.00001);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "+");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "A")==true);
  assert(test.setvar[0] > 9.9999);
  assert(test.setvar[0] < 10.00001);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "-");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "A")==true);
  assert(test.setvar[0] > -0.0001);
  assert(test.setvar[0] < 0.00001);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "/");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "A")==true);
  assert(test.setvar[0] > 0.9999);
  assert(test.setvar[0] < 1.0001);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "4.5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==true);
  assert(test.setvar[25] > 22.4999);
  assert(test.setvar[25] < 22.50001);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "4.5");
  strcpy(test.instructs[1], "-5");
  strcpy(test.instructs[2], "+");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==true);
  assert(test.setvar[25] > -0.500001);
  assert(test.setvar[25] < -0.499999);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "25");
  strcpy(test.instructs[2], "-");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==true);
  assert(test.setvar[25] > -20.0001);
  assert(test.setvar[25] < -19.9999);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "1");
  strcpy(test.instructs[1], "4");
  strcpy(test.instructs[2], "/");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==true);
  assert(test.setvar[25] > 0.249999);
  assert(test.setvar[25] < 0.250001);
  test.cw = 0;
  stest = stack_init();
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
  assert(polish(&test, stest, "Z")==true);
  assert(test.setvar[25] > 5.99999);
  assert(test.setvar[25] < 6.0001);
  test.cw = 0;
  stest = stack_init();
  test.setvar[0] = 5;
  strcpy(test.instructs[0], "A");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "A")==true);
  assert(test.setvar[0] > 24.9999);
  assert(test.setvar[0] < 25.00001);
  test.cw = 0;
  stest = stack_init();
  test.setvar[0] = 5;
  strcpy(test.instructs[0], "A");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==true);
  assert(test.setvar[25] > 24.9999);
  assert(test.setvar[25] < 25.00001);
  /*try to break*/
  test.cw = 0;
  test.setvar[1] = 5001;
  stest = stack_init();
  strcpy(test.instructs[0], "B");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==false);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "}");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==false);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==false);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "AA");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==false);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "\0");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==false);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "\0");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==false);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], " ");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], ";");
  assert(polish(&test, stest, "Z")==false);
  test.cw = 0;
  stest = stack_init();
  strcpy(test.instructs[0], "5");
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "*");
  strcpy(test.instructs[3], "}");
  assert(polish(&test, stest, "Z")==false);
  /*passed all tests*/
  /*test bool set(Instructions* i, char* var, double* setvalue)*/
  test.cw = 0;
  strcpy(vartest, "C");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "*");
  strcpy(test.instructs[5], ";");
  assert(set(&test, vartest, varnumtest)==true);
  assert(varnumtest[0] > 24.9999);
  assert(varnumtest[0] < 25.00001);
  /*should fail as setvarnotset*/
  test.cw = 0;
  test.setvar[0] = 5001;
  strcpy(vartest, "C");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "A");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "*");
  strcpy(test.instructs[5], ";");
  assert(set(&test, vartest, varnumtest)==false);
  test.cw = 0;
  test.setvar[0] = 1;
  strcpy(vartest, "C");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "A");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "*");
  strcpy(test.instructs[5], ";");
  assert(set(&test, vartest, varnumtest)==true);
  assert(varnumtest[0] > 4.9999);
  assert(varnumtest[0] < 5.00001);
  /*try to break*/
  test.cw = 0;
  test.setvar[0] = 1;
  strcpy(vartest, "a");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "A");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "*");
  strcpy(test.instructs[5], ";");
  assert(set(&test, vartest, varnumtest)==false);
  test.cw = 0;
  strcpy(vartest, "A");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "*");
  strcpy(test.instructs[5], "}");
  assert(set(&test, vartest, varnumtest)==false);
  test.cw = 0;
  strcpy(vartest, "A");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "}");
  assert(set(&test, vartest, varnumtest)==false);
  test.cw = 0;
  strcpy(vartest, "A");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "}");
  assert(set(&test, vartest, varnumtest)==false);
  test.cw = 0;
  strcpy(vartest, "A");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":");
  strcpy(test.instructs[2], "=");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "*");
  strcpy(test.instructs[6], "}");
  assert(set(&test, vartest, varnumtest)==false);
  /*passed all tests*/

  test.cw = 0;
  test.maxwds = 9;
  strcpy(test.instructs[0], "SET");
  strcpy(test.instructs[1], "A");
  strcpy(test.instructs[2], ":=");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "5");
  strcpy(test.instructs[6], "*");
  strcpy(test.instructs[7], "*");
  strcpy(test.instructs[8], ";");
  strcpy(test.instructs[9], "}");
  assert(instrctlst(&test, &ctest, &sw)==true);
  assert(test.setvar[0] > 124.9999);
  assert(test.setvar[0] < 125.0001);
  test.cw = 0;
  test.maxwds = 8;
  strcpy(test.instructs[0], "SET");
  strcpy(test.instructs[1], "A");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "*");
  strcpy(test.instructs[6], "*");
  strcpy(test.instructs[7], ";");
  strcpy(test.instructs[8], "}");
  assert(instrctlst(&test, &ctest, &sw)==false);
  test.cw = 0;
  strcpy(vartest, "A");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "*");
  strcpy(test.instructs[6], "*");
  strcpy(test.instructs[7], ";");
  assert(set(&test, vartest, varnumtest)==true);
  assert(varnumtest[0] > 124.9999);
  assert(varnumtest[0] < 125.0001);
  test.cw = 0;
  strcpy(vartest, "a");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "*");
  strcpy(test.instructs[6], "*");
  strcpy(test.instructs[7], ";");
  assert(set(&test, vartest, varnumtest)==false);
  test.cw = 0;
  strcpy(vartest, " ");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], ":=");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "5");
  strcpy(test.instructs[5], "*");
  strcpy(test.instructs[6], "*");
  strcpy(test.instructs[7], ";");
  assert(set(&test, vartest, varnumtest)==false);
  test.cw = 0;
  strcpy(vartest, "Z");
  strcpy(test.instructs[0], vartest);
  strcpy(test.instructs[1], "5");
  strcpy(test.instructs[2], "5");
  strcpy(test.instructs[3], "5");
  strcpy(test.instructs[4], "*");
  strcpy(test.instructs[5], "*");
  strcpy(test.instructs[6], ";");
  assert(set(&test, vartest, varnumtest)==false);

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

  assert(mainstart(&test, &ctest, &sw)==true);
  /*testing scanfile*/
  assert(scanfile(&test, "TTLfiles/simp.ttl")==true);
  assert(mainstart(&test, &ctest, &sw)==true);
  assert(scanfile(&test, "TTLfiles/spiral2_c.ttl")==true);
  assert(mainstart(&test, &ctest, &sw)==true);
  /*file doesn't exist*/
  assert(scanfile(&test, "TTLfiles/simp12.ttl")==false);
  /*made an incorrect file*/
  assert(scanfile(&test, "TTLfiles/simpbroke_c.ttl")==true);
  assert(mainstart(&test, &ctest, &sw)==false);
  /*mistake in file check if works*/
  assert(scanfile(&test, "TTLfiles/spiral2broken_c.ttl")==true);
  assert(mainstart(&test, &ctest, &sw)==false);
  assert(scanfile(&test, "TTLfiles/passing.ttl")==true);
  assert(mainstart(&test, &ctest, &sw)==true);
  /*passing parse but will not pass interpreter*/
  assert(scanfile(&test, "TTLfiles/passingparse.ttl")==true);
  assert(mainstart(&test, &ctest, &sw)==false);
  /*testing complete*/

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
   c->x1 = 512;
   c->y1 = 384;
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
   /*temporary var*/
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
   /*ptr will be \0 if is a number*/
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
      SDL_Delay(DELAYTIME);
      Neill_SDL_SetDrawColour(sw, WHITE, WHITE, WHITE);
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
