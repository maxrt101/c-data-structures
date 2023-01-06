#ifndef _CDS_CARRAY_H_
#define _CDS_CARRAY_H_ 1

#include <stddef.h>
#include <stdbool.h>

#define CDS_CARRAY_INIT_CAPACITY 8

typedef struct carray_t carray_t; 

struct carray_t {
  size_t size;
  size_t capacity;
  size_t sizeof_element;
  void* data;
};

#define carray(T) \
  struct { \
    size_t size; \
    size_t capacity; \
    size_t sizeof_element; \
    T* data; \
  }

#define carray_def(T, name) \
  typedef struct name { \
    size_t size; \
    size_t capacity; \
    size_t sizeof_element; \
    T* data; \
  } name

#define CARRAY_FOR(T, arr, itr) for (size_t i = 0; i < carray_size(arr); i++, itr = carray_get(T, arr, i))
#define CARRAY_FOR_REV(T, arr, itr) for (size_t i = carray_size(arr)-1; i >= 0; i--, itr = carray_get(T, arr, i))
#define CARRAY_FOR_I(arr) for (size_t i = 0; i < carray_size(arr); i++)
#define CARRAY_FOR_I_REV(arr) for (size_t i = carray_size(arr)-1; i >= 0; i--)
#define CARRAY_FOR_PTR(T, arr, itr) for (T* itr = (arr)->data; itr-(arr)->data < carray_size(arr); itr++)
#define CARRAY_FOR_PTR_REV(T, arr, itr) for (T* itr = ((T*)(arr)->data) + carray_size(arr); itr-(arr)->data >= 0; itr++)
#define CARRAY_FOREACH(T, arr, fn) CARRAY_FOR_I(arr) fn(carray_get(T, arr, i))
#define CARRAY_FOREACH_REV(T, arr, fn) CARRAY_FOR_I_REV(arr) fn(carray_get(T, arr, i))

#define carray_new(T) _carray_new(sizeof(T), CDS_CARRAY_INIT_CAPACITY)
#define carray_create(T, arr) _carray_create(&arr, sizeof(T), CDS_CARRAY_INIT_CAPACITY)
#define carray_size(arr) ((arr)->size)
#define carray_capacity(arr) ((arr)->capacity)
#define carray_get(T, arr, i) (((T*)(arr)->data)[i])

#define carray_append(T, arr, val) \
  do { \
    if ((arr)->size >= carray_capacity(arr)) { \
      carray_resize(arr, carray_capacity(arr)*2); \
    } \
    carray_get(T, arr, carray_size(arr)++) = val; \
  } while (0)

#define carray_insert(T, arr, idx, val) \
  do { \
    if (idx < carray_size(arr)) { \
      if (carray_size(arr) + 1 >= carray_capacity(arr)) { \
        carray_resize(arr, carray_capacity(arr)*2); \
      } \
      if (idx == carray_size(arr)-1) { \
        carray_get(T, arr, idx+1) = val; \
        carray_size(arr)++; \
      } else { \
        for (size_t i = carray_size(arr); i > idx; i--) { \
          carray_get(T, arr, i) = carray_get(T, arr, i-1); \
        } \
        carray_get(T, arr, idx) = val; \
        carray_size(arr)++; \
      } \
    } \
  } while (0)

#define carray_remove(T, arr, idx) \
  do { \
    if (idx < carray_size(arr)) {\
      for (size_t i = idx; i < carray_size(arr)-1; i++) { \
        carray_get(T, arr, i) = carray_get(T, arr, i+1); \
      } \
      carray_size(arr)--; \
    } \
  } while (0)

#define carray_find(T, arr, result, element) \
  do { \
    result = -1; \
    CARRAY_FOR_I(arr) { \
      if (carray_get(T, arr, i) == element) { \
        result = i; \
        break; \
      } \
    } \
  } while (0)

#define carray_find_inline(T, arr, element) _carry_find(arr, sizeof(T), element)

carray_t* _carray_new(size_t sizeof_element, size_t initial_capacity);
void _carray_create(carray_t* array, size_t sizeof_element, size_t initial_capacity);
void carray_delete(carray_t* array);
void carray_free(carray_t* array);
void carray_resize(carray_t* array, size_t new_size);
void carray_clone(carray_t* src, carray_t* dest);
carray_t* carray_copy(carray_t* array);
size_t _carry_find(carray_t* array, size_t sizeof_element, void* element);

// void carray_sort(carray_t* array, pred) // macro?
// void carray_remove_if() // macro? (T, arr, rhs > lhs)
// carray_t* carray_slice();

#endif /* _CDS_CARRAY_H_ */