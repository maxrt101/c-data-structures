# clist

To use clist you should create your own struct that will represent an element, and use `clist_t` as a first field. Also you can define some utility functions for convenience.
Example:
```c
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
```