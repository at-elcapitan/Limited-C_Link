#include <stdlib.h>

struct hashtable_item_ull {
  unsigned long long *key;
  unsigned long long *value;
};

struct hashtable_table_ull {
  struct hashtable_item_ull **items;
  int size;
  int count;
};
