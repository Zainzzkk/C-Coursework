typedef struct array {
   void* data;
   void* key;
   } array;

typedef struct assoc {
   array* hashtable;
   unsigned int size;
   unsigned int type;
   unsigned int count;
   } assoc;

#define SIZE 17
#define SCALEFACTOR 2
#define STR 0
#define CAPACITYLIMIT 0.6
#define NUMITEMS 2
#define EMPTY 0
#define HASHVALUE 5381
#define HASHNUM 33
#define PRIME 7
#define NOTPRIME 0

typedef enum bool {false, true} bool;
typedef unsigned int datatype;


/*for testing only*/

typedef struct tester {
   int a;
   int b;
   int c;
   } tester;
