#include "c-array.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define __CARRAY_INIT_SIZE 8


CArray* c_array_new(int sizeof_element) {
  CArray* array = malloc(sizeof(CArray));
  if (!array) return NULL;
  c_array_init(array, sizeof_element);
  return array;
}


void c_array_free(CArray* array) {
  c_array_cleanup(array);
  free(array);
}


void c_array_init(CArray* array, int sizeof_element) {
  array->sizeof_element= sizeof_element;
  array->data = malloc(sizeof_element * __CARRAY_INIT_SIZE);
  array->capacity = __CARRAY_INIT_SIZE;
  array->size = 0;
}


void c_array_cleanup(CArray* array) {
  free(array->data);
  array->size = 0;
  array->capacity = 0;
}


void c_array_resize(CArray* array, int new_size) {
  if (!array->data) {
    array->data = malloc(new_size * array->sizeof_element);
    return;
  }
  void* data = realloc(array->data, new_size * array->sizeof_element);
  if (!data) {
    printf("c_array_resize(): Allocation error.\n");
  } else {
    array->data = data;
    array->capacity = new_size;
  }
}


void c_array_copy(CArray* dest, CArray* src) {
  dest->size = src->size;
  dest->capacity = src->capacity;
  dest->sizeof_element = src->sizeof_element;
  dest->data = malloc(dest->capacity * dest->sizeof_element);
  memcpy(dest->data, src->data, src->size * src->sizeof_element);
}


CArray* c_array_make_copy(CArray* src) {
  CArray* copy = malloc(sizeof(CArray));
  c_array_copy(copy, src);
  return copy;
}


bool c_array_contains(CArray* array, void* data) {
  for (int i = 0; i < array->size; i++) {
    if (!memcmp((char*)array->data+(i*array->sizeof_element), data, array->sizeof_element))
      return true;
  }
  return false;
}

