#include <cds/carray.h>
#include <cds/memory.h>
#include <stdio.h>

carray_def(int, carray_int_t);

int expected[] = {300, 1, 2, 3, 4, 125, 5, 7, 8, 500};

int main() {
  carray_int_t* iarr = carray_new(int);

  for (int i = 0; i < 10; i++) {
    carray_append(int, iarr, i);
  }

  carray_insert(int, iarr, 5, 125);
  carray_remove(int, iarr, 7);
  carray_remove(int, iarr, 0);
  carray_remove(int, iarr, carray_size(iarr)-1);
  carray_insert(int, iarr, 0, 300);
  carray_insert(int, iarr, 8, 500);

  int i125;
  carray_find(int, iarr, i125, 125);

  if (i125 != 5) return 1;

  CARRAY_FOR_I(iarr) {
    if (carray_get(int, iarr, i) != expected[i]) return 2;
  }

  carray_int_t* iarr2 = carray_copy(iarr);

  CARRAY_FOR_I(iarr2) {
    if (carray_get(int, iarr2, i) != expected[i]) return 3;
  }

  carray_free(iarr);
  carray_free(iarr2);
}
