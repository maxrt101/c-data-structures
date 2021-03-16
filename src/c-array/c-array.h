#ifndef CDS_C_ARRAY_H_
#define CDS_C_ARRAY_H_

#include <stdbool.h>

typedef struct {
  int size;
  int capacity;
  int sizeof_element;
  void* data;
} CArray;

#define CArrayAlias(T, name)\
  typedef struct {\
    int size;\
    int capacity;\
    int sizeof_element;\
    T* data;\
  } name

#define CARRAY_NEW(T) (c_array_new(sizeof(T)))
#define CARRAY_GET(T, a, i) (((T*)(a)->data)[i])
#define CARRAY_SIZE(a) ((a)->size)
#define CARRAY_CAPACITY(a) ((a)->capacity)

#define CARRAY_FOR(T, a, iter)      for (int i = 0; i < CARRAY_SIZE(a); iter=CARRAY_GET(T, a, i), i++)
#define CARRAY_FOR_PTR(T, a, iter)  for (T* iter = (a)->data; iter-(T*)(a)->data < CARRAY_SIZE(a); iter++)
#define CARRAY_FOREACH(T, a, f)     for (int i = 0; i < CARRAY_SIZE(a); i++) f(CARRAY_GET(T, a, i))
#define CARRAY_FOREACH_PTR(T, a, f) for (T* x= (a)->data; x-(T*)(a)->data < CARRAY_SIZE(a); x++) f(x)

#define CARRAY_PUSH(T, a, e)\
  if ((a)->size < (a)->capacity) {\
    CARRAY_GET(T, a, CARRAY_SIZE(a)++) = e;\
  } else {\
    c_array_resize(a, CARRAY_CAPACITY(a)*2);\
    CARRAY_GET(T, a, CARRAY_SIZE(a)++) = e;\
  }

#define CARRAY_POP(a) ((a)->size--)

#define CARRAY_ERASE(T, a, i)\
  if (i < CARRAY_SIZE(a)) {\
    for (int n = 0; n < CARRAY_SIZE(a); n++) {\
      if (n >= i && n+1 < CARRAY_SIZE(a))\
        CARRAY_GET(T, a, n) = CARRAY_GET(T, a, n+1);\
    }\
    a->size--;\
  }

#define CARRAY_FIND(T, a, idx, cond) {\
  idx = 0;\
  CARRAY_FOR_PTR(T, a, x) {\
    if (cond) break;\
    idx++;\
  }\
}


CArray* c_array_new(int sizeof_element);
void    c_array_free(CArray* array);
void    c_array_init(CArray* array, int sizeof_element);
void    c_array_cleanup(CArray* array);
void    c_array_resize(CArray* array, int new_size);
void    c_array_copy(CArray* dest, CArray* src);
CArray* c_array_make_copy(CArray* src);
bool    c_array_contains(CArray* array, void* data);

#endif

