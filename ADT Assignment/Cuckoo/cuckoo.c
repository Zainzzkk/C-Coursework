#include "specific.h"
#include "../general.h"
#include "../assoc.h"

unsigned int _hash(assoc* a, char* key);
unsigned int _hash2(assoc* a, char* key);
void* _typetoreturn(assoc* a, void* key, int index, int side);
bool _typesamecheck(assoc* a, void* key, int index, int side);
bool _samecheck(assoc* a, void* key);
bool _isprime(unsigned int a);
unsigned int _nextprime(unsigned int a);
void _rehash(assoc* a, assoc* new);
assoc* _resize(assoc* a);
void _reinsert(assoc** a, void* key, void* data);

/*
   Initialise the Associative array
   keysize : number of bytes (or 0 => string)
   This is important when comparing keys since
   we'll need to use either memcmp() or strcmp()
*/
assoc* assoc_init(int keysize)
{
   assoc *new;

   new = (assoc*)ncalloc(1, sizeof(assoc));
   new->hashtable1 = (array*)ncalloc(SIZE*2, sizeof(array));
   new->hashtable2 = (array*)ncalloc(SIZE*2, sizeof(array));
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
   unsigned int hashindex1;
   char *keyconvert = (char *)key;
   void* tmpkey;
   void* tmpdata;
   assoc* new;

   if (key == NULL){
      return;
      }
   if ((*a)==NULL){
      on_error("Assoc is NULL");
      }

   if ((*a)->count > ((*a)->size * CAPACITYLIMIT)) {
      new = _resize((*a));
      (*a) = new;
      }

   if (_samecheck((*a), key) == true){
      return;
      }

   hashindex1 = _hash((*a), keyconvert);
      if ((*a)->hashtable1[hashindex1].key==NULL){
         (*a)->hashtable1[hashindex1].key = key;
         (*a)->hashtable1[hashindex1].data = data;
         (*a)->count += 1;
         (*a)->loopcounter = 0;
         return;
         }
      else {
         tmpkey = (*a)->hashtable1[hashindex1].key;
         tmpdata = (*a)->hashtable1 [hashindex1].data;
         (*a)->hashtable1[hashindex1].key = key;
         (*a)->hashtable1[hashindex1].data = data;
         (*a)->loopcounter += 1;
         _reinsert(a, tmpkey, tmpdata);
         }
}

void _reinsert(assoc** a, void* key, void* data)
{
   unsigned int hashindex2;
   void* tmpkey;
   void* tmpdata;
   char *keyconvert = (char *)key;

   if (_samecheck((*a), key) == true){
      return;
      }

   hashindex2 = _hash2((*a), keyconvert);
   if ((*a)->hashtable2[hashindex2].key==NULL){
      (*a)->hashtable2[hashindex2].key = key;
      (*a)->hashtable2[hashindex2].data = data;
      (*a)->loopcounter = 0;
      (*a)->count += 1;
      return;
      }
   else {
      tmpkey = (*a)->hashtable2[hashindex2].key;
      tmpdata = (*a)->hashtable2[hashindex2].data;
      (*a)->hashtable2[hashindex2].key = key;
      (*a)->hashtable2[hashindex2].data = data;
      (*a)->loopcounter += 1;
      assoc_insert(a, tmpkey, tmpdata);
      }
}
/*
   Returns the number of key/data pairs
   currently stored in the table
*/
unsigned int assoc_count(assoc* a)
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
   unsigned int hashindex2, hashindex1;
   void* iffound;

   if (a==NULL){
      on_error("Assoc is NULL");
      }

   hashindex1 = _hash(a, keyconvert);
   hashindex2 = _hash2(a, keyconvert);
   if ((a->hashtable1[hashindex1].key == EMPTY)&&(a->hashtable2[hashindex2].key == EMPTY)){
      return NULL;
   }

   if (a->hashtable1[hashindex1].key != EMPTY){
      iffound = _typetoreturn(a, key, hashindex1, TABLEONE);
      if (iffound != NULL){
         return iffound;
         }
      }
   else if (a->hashtable2[hashindex2].key != EMPTY){
      iffound = _typetoreturn(a, key, hashindex2, TABLETWO);
      if (iffound != NULL){
         return iffound;
         }
      }
   return NULL;
}

/* Free up all allocated space from 'a' */
void assoc_free(assoc* a)
{
   array* freeit1 = a->hashtable1;
   array* freeit2 = a->hashtable2;

   free(freeit1);
   free(freeit2);
   free(a);
}
/*Supplementary functions*/

assoc* _resize(assoc* a)
{
   assoc* new;
   unsigned int newsize = ((a->size)*SCALEFACTOR);
   unsigned int primesize = _nextprime(newsize);

   new = (assoc*)calloc(1, sizeof(assoc));
   new->hashtable1 = (array*)ncalloc(primesize*NUMITEMS, sizeof(array));
   new->hashtable2 = (array*)ncalloc(primesize*NUMITEMS, sizeof(array));
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
   unsigned int i;
   /*if not empty then needs rehashing*/
   for (i = 0; i < a->size; i++){
      if (a->hashtable1[i].key !=  NULL){
         assoc_insert(&new, a->hashtable1[i].key, a->hashtable1[i].data);
         }
      }
   for (i = 0; i < a->size; i++){
      if (a->hashtable2[i].key !=  NULL){
         assoc_insert(&new, a->hashtable2[i].key, a->hashtable2[i].data);
         }
      }
}
unsigned int _hash(assoc* a, char* key)
{
   unsigned long hash = HASHVALUE;
   unsigned int c, i;
   /*if not string*/
   if (a->type != STR){
      for (i = 0; i < a->type; i++){
         c = (*key++);
         hash = HASHNUM * hash ^ c;
         }
      }
   else  {
      while ((c = (*key++))){
         hash = HASHNUM * hash ^ c;
         }
      }
   return (unsigned int)(hash % a->size);
}
unsigned int _hash2(assoc* a, char* key)
{
   unsigned long hash = 0;
   unsigned int c, i;
   if (a->type != STR){
      for (i = 0; i < a->type; i++){
         c = (*key++);
         hash = c + (hash << 6) + (hash << 16) - hash;
         }
      }
   else {
      while ((c = (*key++))){
         hash = c + (hash << 6) + (hash << 16) - hash;
         }
      }
   return (unsigned int)(hash % a->size);
}

bool _samecheck(assoc* a, void* key)
{
   unsigned int hashindex1, hashindex2;
   char *keyconvert = (char *)key;
   hashindex1 = _hash(a, keyconvert);
   hashindex2 = _hash2(a, keyconvert);

   if (a->hashtable1[hashindex1].key == EMPTY){
      if (a->hashtable2[hashindex2].key == EMPTY){
         return false;
         }
      }

   if (a->hashtable1[hashindex1].key != EMPTY){
      if ((_typesamecheck(a, key, hashindex1, 1))==true){
         return true;
         }
      }
   if (a->hashtable2[hashindex2].key != EMPTY){
      if ((_typesamecheck(a, key, hashindex2, 2))==true){
         return true;
         }
      }
   return false;
}

bool _typesamecheck(assoc* a, void* key, int index, int side)
{
   if (side == TABLEONE){
      if (a->type == STR){
         if (strcmp(a->hashtable1[index].key, key)==0){
            return true;
            }
         }
      else {
         if (memcmp(a->hashtable1[index].key, key, a->type)==0){
            return true;
            }
         }
      }
   if (side == TABLETWO){
      if (a->type == STR){
         if (strcmp(a->hashtable2[index].key, key)==0){
            return true;
            }
         }
      else {
         if (memcmp(a->hashtable2[index].key, key, a->type)==0){
            return true;
            }
         }

      }

   return false;
}

void* _typetoreturn(assoc* a, void* key, int index, int side)
{
   if (side == 1){
      if (a->type == STR){
         if (strcmp(a->hashtable1[index].key, key)==0){
            return a->hashtable1[index].data;
            }
         }
      else {
         if (memcmp(a->hashtable1[index].key, key, a->type)==0){
            return a->hashtable1[index].key;
            }
         }
      }
   if (side == 2) {
      if (a->type == STR){
         if (strcmp(a->hashtable2[index].key, key)==0){
            return a->hashtable2[index].data;
            }
         }
      else {
         if (memcmp(a->hashtable2[index].key, key, a->type)==0){
            return a->hashtable2[index].key;
            }
         }
      }

   return NULL;
}

unsigned int _nextprime(unsigned int a)
{
   unsigned int counter = a;

   while (_isprime(counter)==false){
      counter++;
      }
   return counter;
}

bool _isprime(unsigned int a)
{
 unsigned int i;

   for (i = 2; i < a; i++){
    if (a % i == 0){
      return false;
     }
    }
   return true;
}
