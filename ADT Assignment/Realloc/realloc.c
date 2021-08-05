#include "specific.h"
#include "../general.h"
#include "../assoc.h"
/*adapted from Neill's lecture*/
datatype _hash(assoc* a, int size, char* key);
datatype _hash2(assoc* a, char* key);
/*returns the key or data*/
void* _typetoreturn(assoc* a, void* key, int index);
/*checks has not been seen before*/
bool _samecheck(assoc* a, void* key);
bool _typesamecheck(assoc* a, void* key, int index);
/*checks if prime number or not*/
bool _isprime(datatype a);
/*returns next prime number*/
datatype _nextprime(datatype a);
/*resizes the array*/
assoc* _resize(assoc* a);
/*rehashes whatever is in the array*/
void _rehash(assoc* a, assoc* new);
void test(void);
/*
   Initialise the Associative array
   keysize : number of bytes (or 0 => string)
   This is important when comparing keys since
   we'll need to use either memcmp() or strcmp()
*/
assoc* assoc_init(int keysize)
{
   assoc *new;
   static int i;
   /*runs test only once*/
   if (i == 0){
      i = 1;
      test();
      }

   new = (assoc*)ncalloc(1, sizeof(assoc));
   new->hashtable = (array*)ncalloc(SIZE*2, sizeof(array*));
   new->size = SIZE;
   new->count = EMPTY;
   if (keysize == STR){
      new->type = STR;
      }
   else {
      new->type = keysize;
      }
   return new;
}
/*
   Insert key/data pair
   - may cause resize, therefore 'a' might
   be changed due to a realloc() etc.
*/
void assoc_insert(assoc** a, void* key, void* data)
{
   datatype hashindex, newindex, i, hash2;
   char *keyconvert = (char *)key;
   assoc* new;
   /*returns if key is null*/
   if (key == NULL){
      return;
      }
   if ((*a)==NULL){
      on_error("Assoc is NULL");
      }
   hashindex = _hash((*a), (*a)->size, keyconvert);
   hash2 = _hash2((*a), keyconvert);
   /*resizes when 60% full*/
   if ((*a)->count > ((*a)->size * CAPACITYLIMIT)){
      new = _resize((*a));
      (*a) = new;
      }
   /*checks not already in table*/
   if (_samecheck((*a), key) == true){
      return;
      }
   for (i = 0; i < (*a)->size; i += hash2){
      newindex = (hashindex + i) % (*a)->size;
      /*if empty*/
      if ((*a)->hashtable[newindex].key == EMPTY){
         (*a)->hashtable[newindex].key = key;
         (*a)->hashtable[newindex].data = data;
         (*a)->count += 1;
         return;
         }
      }
}
/*
   Returns the number of key/data pairs
   currently stored in the table
*/
datatype assoc_count(assoc* a)
{
   if(a == NULL){
      return EMPTY;
      }
   return a->count;
}
/*
   Returns a pointer to the data, given a key
   NULL => not found
*/
void* assoc_lookup(assoc* a, void* key)
{
   char *keyconvert = (char *)key;
   datatype i, newindex, hash2, hashindex;
   void* iffound;

   if (a==NULL){
      on_error("Assoc is NULL");
      }

   hashindex = _hash(a, a->size, keyconvert);
   hash2 = _hash2(a, keyconvert);

   for (i = 0; i < a->size; i += hash2){
      newindex = (hashindex + i) % a->size;
      /*if empty then know is not there*/
      if (a ->hashtable[newindex].key ==  EMPTY){
         return NULL;
         }
      else if (a->hashtable[newindex].key != EMPTY){
         iffound = _typetoreturn(a, key, newindex);
         if (iffound != NULL){
            return iffound;
            }
         }
      }
   return NULL;
}

/* Free up all allocated space from 'a' */
void assoc_free(assoc* a)
{
   array* freeit = a->hashtable;

   free(freeit);
   free(a);
}

/*Supplementary functions*/
/*Adapted from Neill's lecture on hashing - Berstein hashing*/
void* _typetoreturn(assoc* a, void* key, int index)
{
   if (a->type == STR){
      if (strcmp(a->hashtable[index].key, key)==0){
         return a->hashtable[index].data;
         }
      }
   else {
      if (memcmp(a->hashtable[index].key, key, a->type)==0){
         return a->hashtable[index].key;
         }
      }
   return NULL;
}
/*Adapted from Neill's lecture on hashing - Berstein hashing*/
datatype _hash(assoc* a, int size, char* key)
{
   unsigned long hash = HASHVALUE;
   datatype c, i;
   /*if not string*/
   if (a->type != STR){
      for (i = 0; i < a->type; i++){
         c = (*key++);
         hash = HASHNUM * hash ^ c;
         }
      }
   else {
      while ((c = (*key++))){
         hash = HASHNUM * hash ^ c;
         }
      }

   return (datatype)(hash % size);
}
/*Adapted from Neill's lecture on hashing - Berstein hashing*/
datatype _hash2(assoc* a, char* key)
{
   unsigned long hash = HASHVALUE;
   datatype c, i;

   if (a->type != STR){
      for (i = 0; i < a->type; i++){
         c = (*key++);
         hash = HASHNUM * hash ^ c;
         }
      }
   else {
      while ((c = (*key++))){
         hash = HASHNUM * hash ^ c;
         }
      }
   return (datatype)((hash % PRIME)+1);
}

assoc* _resize(assoc* a)
{
   assoc* new;
   unsigned long newsize = ((a->size)*SCALEFACTOR);
   datatype primesize = _nextprime(newsize);

   new = (assoc*)ncalloc(1, sizeof(assoc));
   new->hashtable = (array*)ncalloc(primesize*NUMITEMS, sizeof(array));
   new->size = primesize;
   new->type = a->type;
   /*set to 0 as count will be added when rehashed*/
   new->count = EMPTY;
   _rehash(a, new);
   /*free old struct*/
   assoc_free(a);
   return new;
}

void _rehash(assoc* a, assoc* new)
{
   datatype i;
   /*if not empty then needs rehashing*/
   for (i = 0; i < a->size; i++){
      if (a->hashtable[i].key !=  NULL){
         assoc_insert(&new, a->hashtable[i].key, a->hashtable[i].data);
         }
      }
}

bool _samecheck(assoc* a, void* key)
{
   datatype i, hashindex, hash2, newindex;
   char *keyconvert = (char *)key;

   hashindex = _hash(a, a->size, keyconvert);
   hash2 = _hash2(a, keyconvert);

   for (i = 0; i < a->size; i += hash2){
      newindex = (hashindex + i) % a->size;
      if (a ->hashtable[newindex].key ==  EMPTY){
         return false;
         }
      else if (a->hashtable[newindex].key != EMPTY){
         if ((_typesamecheck(a, key, newindex))==true){
            return true;
            }
         }
      }
   return false;
}

bool _typesamecheck(assoc* a, void* key, int index)
{
   if (a->type == STR){
      if (strcmp(a->hashtable[index].key, key)==0){
         return true;
         }
      }
   else {
      if (memcmp(a->hashtable[index].key, key, a->type)==0){
         return true;
         }
      }
   return false;
}

datatype _nextprime(datatype a)
{
   datatype counter = a;

   while (_isprime(counter)==false){
      counter++;
      }
   return counter;
}

bool _isprime(datatype a)
{
 datatype i;

   for (i = 2; i < a; i++){
    if (a % i == NOTPRIME){
      return false;
     }
    }
   return true;
}

void test(void)
{
   char strs[35][12] = {{0}};
   int i[35] = {0};
   short s[5] = {0};
   float floaty[5] = {0};
   assoc* a;
   int j;
   void *p;
   int result;
   tester tests[5];

   a = assoc_init(0);

   strcpy(strs[0], "Abc");
   strcpy(strs[1], "Apple");
   strcpy(strs[2], "Banana");
   strcpy(strs[3], "abc");
   strcpy(strs[4], "Orange");

   for (j = 0; j < 5; j++){
      i[j] = j;
      assoc_insert(&a, &strs[j], &i[j]);
      }

   p = assoc_lookup(a, "Abc");
   result = *(int*)p;
   assert(result==(0));
   p = assoc_lookup(a, "Orange");
   result = *(int*)p;
   assert(result==(4));
   p = assoc_lookup(a, "Banana");
   result = *(int*)p;
   assert(result==(2));
   p = assoc_lookup(a, "abc");
   result = *(int*)p;
   assert(result==(3));
   p = assoc_lookup(a, "Apple");
   result = *(int*)p;
   assert(result==(1));
   p = assoc_lookup(a, "apple");
   assert(p==(NULL));
   /*as not here*/
   p = assoc_lookup(a, "a");
   assert(p==(NULL));

   assoc_free(a);

   a = assoc_init(0);

   strcpy(strs[0], "Abc");
   strcpy(strs[1], "Abc");
   strcpy(strs[2], "Abc");
   strcpy(strs[3], "abc");
   strcpy(strs[4], "Abc");

   for (j = 0; j < 5; j++){
      i[j] = j;
      assoc_insert(&a, &strs[j], &i[j]);
      }
   /*checking for repeats not being inserted and recognises
   difference between upper and lower case*/
   assert((a->count)==(2));

   assoc_free(a);

   a = assoc_init(sizeof(int));

   i[0] = 65;
   i[1] = 20;
   i[2] = 35;
   i[3] = -22;
   i[4] = 25;
   i[5] = 89;

   for (j = 0; j < 6; j++){
      assoc_insert(&a, &i[j], NULL);
      }
   assoc_free(a);

   a = assoc_init(sizeof(int));

   i[0] = 66;
   i[1] = 20;
   i[2] = 20;
   i[3] = 66;
   i[4] = 0;
   i[5] = 25;

   for (j = 0; j < 6; j++){
      assoc_insert(&a, &i[j], NULL);
      }
   /*checks repeats are not inserted*/
   assert((a->count)==(4));
   assoc_free(a);

   j = 465;
   assert(_nextprime(j)==(467));
   j = 67286;
   assert(_nextprime(j)==(67289));
   assert(_isprime(656425)==(false));
   assert(_isprime(64439)==true);
   /*checks negative floats*/
   a = assoc_init(sizeof(short));

   s[0] = -32000;
   s[1] = 205;
   s[2] = -355;
   s[3] = -220;
   s[4] = 25;

   for (j = 0; j < 5; j++){
      assoc_insert(&a, &s[j], NULL);
      }
   assoc_free(a);

   a = assoc_init(sizeof(float));

   floaty[0] = 2.65665;
   floaty[1] = 3.664552;
   floaty[2] = 45;
   floaty[3] = -2.656555;
   floaty[4] = -25.665;

   for (j = 0; j < 5; j++){
      assoc_insert(&a, &floaty[j], NULL);
      }
   assert((a->count)==(5));
   assoc_free(a);

   a = assoc_init(sizeof(float));

   floaty[0] = 2.65665;
   floaty[1] = 2.65665;
   floaty[2] = 45;
   floaty[3] = -2.656555;
   floaty[4] = -2.656555;

   for (j = 0; j < 5; j++){
      assoc_insert(&a, &floaty[j], NULL);
      }
   assert((a->count)==(3));
   assoc_free(a);

   a = assoc_init(sizeof(tester));

   tests[0].a = 5;
   tests[0].b = 35;
   tests[0].c = 5;
   tests[1].a = 3;
   tests[1].b = 3;
   tests[1].c = 3;
   tests[2].c = 1;
   tests[2].a = 4;
   tests[2].c = 76;
   tests[3].a = 3;
   tests[3].b = 43;
   tests[3].c = 32;
   tests[4].b = 456;
   tests[4].a = 4456;
   tests[4].c = 3456;

   for (j = 0; j < 5; j++){
      assoc_insert(&a, &tests[j], &tests[j]);
      }
   assert((a->count)==(5));
   assoc_free(a);

   a = assoc_init(0);

   /*check is resizing properly*/
   strcpy(strs[0], "Abc");
   strcpy(strs[1], "Apple");
   strcpy(strs[2], "Banana");
   strcpy(strs[3], "abc");
   strcpy(strs[4], "Orange");
   strcpy(strs[5], "Ki");
   strcpy(strs[5], "kite");
   strcpy(strs[6], "akd");
   strcpy(strs[7], "kjkfg");
   strcpy(strs[8], "lkfk");
   strcpy(strs[9], "redff");
   strcpy(strs[10], "kia");
   strcpy(strs[11], "adfsdf");
   strcpy(strs[12], "kfbdbfia");
   strcpy(strs[13], "kiacvbc");


   for (j = 0; j < 11; j++){
      i[j] = j;
      assoc_insert(&a, &strs[j], &i[j]);
      }
   assert((a->size)==(17));

   p = assoc_lookup(a, "Abc");
   result = *(int*)p;
   assert(result==(0));
   /*resizes to next prime number*/
   for (j = 11; j < 14; j++){
      i[j] = j;
      assoc_insert(&a, &strs[j], &i[j]);
      }
   assert((a->size)==(37));
   /*has rehashed correctly as can find it*/
   p = assoc_lookup(a, "Abc");
   result = *(int*)p;
   assert(result==(0));

   p = assoc_lookup(a, "redff");
   result = *(int*)p;
   assert(result==(9));

   assoc_free(a);


}
