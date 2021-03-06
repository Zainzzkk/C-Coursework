#pragma once

#define FORMATSTR "%f"
#define ELEMSIZE 20

#define STACKTYPE "Realloc"

#define FIXEDSIZE 16
#define SCALEFACTOR 2

struct stack {
   /* Underlying array */
   stacktype* a;
   int size;
   int capacity;
};
