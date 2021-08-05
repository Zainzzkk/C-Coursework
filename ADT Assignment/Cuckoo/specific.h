#include <math.h>

typedef struct array {
   void* data;
   void* key;
   } array;

typedef struct assoc {
   array* hashtable1;
   array* hashtable2;
   unsigned int size;
   unsigned int type;
   unsigned int count;
   unsigned int loopcounter;
   } assoc;

#define SIZE 17
#define SCALEFACTOR 2
#define STR 0
#define CAPACITYLIMIT 0.3
#define NUMITEMS 2
#define EMPTY 0
#define HASHVALUE 5381
#define HASHVALUE2 5591
#define SHIFT 5
#define HASHNUM 33
#define PRIME 7
#define TABLEONE 1
#define TABLETWO 2


typedef enum bool {false, true} bool;
