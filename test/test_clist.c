
#include <stdlib.h>
#include <stdio.h>

#include <cds/clist.h>
#include <cds/memory.h>

#define GET(e) *((clist_int_t*)e)->data

int expected[] = {340, 100, 256, 0, 2, 1000, 3, 4, 6, 7, 8, 9};

typedef struct clist_int_t {
  clist_t head;
  int* data;
} clist_int_t;

void clist_int_create(clist_int_t* e, int val) {
  clist_create(e);
  e->data = new(int);
  *e->data = val;
}

clist_int_t* clist_int_new(int val) {
  clist_int_t* e = new(clist_int_t);
  clist_int_create(e, val);
  return e;
}

void clist_int_delete(clist_int_t* e) {
  if (e->data) {
    free(e->data);
  }
  free(e);
}

static bool clist_int_cmp5(clist_t* e) {
  return *((clist_int_t*)e)->data == 5;
}

int main() {
  clist_int_t* list = new(clist_int_t);
  clist_int_create(list, 100);

  for (int i = 0; i < 10; i++) {
    clist_append(list, clist_int_new(i));
  }

  if (clist_size(list) != 11) return 1;

  clist_t* e5 = clist_find(list, clist_int_cmp5);

  if (!e5 || GET(e5) != 5 || clist_find_pos(e5) != 6) return 2;

  clist_remove(e5, clist_int_delete);
  clist_remove_at(list, 2, clist_int_delete);

  clist_insert(list->head.next, clist_int_new(256));
  clist_insert_at(list, 4, clist_int_new(1000));
  clist_prepend(list, clist_int_new(340));

  int i = 0;
  CLIST_FOR(clist_first(list), itr) {
    if (GET(itr) != expected[i++]) return 3;
  }

  clist_delete(list, clist_int_delete);
}
