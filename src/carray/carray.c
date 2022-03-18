#include <cds/carray.h>
#include <cds/memory.h>
#include <string.h>

carray_t* _carray_new(size_t sizeof_element, size_t initial_capacity) {
  carray_t* arr = new(carray_t);
  _carray_create(arr, sizeof_element, initial_capacity);
  return arr;
}

void _carray_create(carray_t* array, size_t sizeof_element, size_t initial_capacity) {
  if (!array) return;
  array->size = 0;
  array->capacity = (initial_capacity > 0) ? initial_capacity : 1;
  array->sizeof_element = (sizeof_element > 0) ? sizeof_element : 1;
  carray_resize(array, array->capacity);
}

void carray_delete(carray_t* array) {
  if (!array) return;
  if (array->data) {
    free(array->data);
  }
  array->size = 0;
  array->capacity = 0;
}

void carray_free(carray_t* array) {
  carray_delete(array);
  free(array);
}

void carray_resize(carray_t* array, size_t new_size) {
  if (!array) return;
  if (!array->data) {
    array->data = malloc(new_size * array->sizeof_element);
  } else {
    array->data = realloc(array->data, new_size * array->sizeof_element);
  }
  // if (!array->data) { /* error */ }
  array->capacity = new_size;
}

void carray_clone(carray_t* src, carray_t* dest) {
  if (!src) return;
  dest->size = src->size;
  dest->capacity = src->capacity;
  dest->sizeof_element = src->sizeof_element;
  carray_resize(dest, dest->capacity);
  memcpy(dest->data, src->data, dest->size * dest->sizeof_element);
}

carray_t* carray_copy(carray_t* array) {
  if (!array) return NULL;
  carray_t* copy = new(carray_t);
  carray_clone(array, copy);
  return copy;
}
