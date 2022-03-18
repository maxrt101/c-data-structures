#include <cds/cstring.h>
#include <cds/memory.h>
#include <string.h>

cstring_t* _cstring_new_wrapper(cstring_new_args_t args) {
  return _cstring_new(args.src, args.begin, args.end);
}

cstring_t* _cstring_new(const char* str, size_t begin, size_t end) {
  if (!str || begin > end) return NULL;
  cstring_t* cstr = new(cstring_t);
  _cstring_create(cstr, str, begin, end);
  return cstr;
}

void _cstring_create_wrapper(cstring_create_args_t args) {
  _cstring_create(args.str, args.src, args.begin, args.end);
}

void _cstring_create(cstring_t* cstr, const char* str, size_t begin, size_t end) {
  if (!cstr || !str || begin > end) return;
  end = end > 0 ? end : strlen(str);
  cstr->data = new(char, end-begin+1);
  // if (!cstr->data) { /* handle error */ }
  memcpy(cstr->data, str+begin, end-begin);
  cstr->data[end-begin] = 0;
  cstr->capacity = cstr->size = end-begin;
}

void cstring_delete(cstring_t* cstr) {
  if (!cstr) return;
  if (!cstr->data) {
    free(cstr->data);
  }
  cstr->capacity = cstr->size = 0;
}

void cstring_free(cstring_t* cstr) {
  if (!cstr) return;
  cstring_delete(cstr);
  free(cstr);
}

void _cstring_append(cstring_t* cstr1, cstring_t* cstr2) {
  if (!cstr1 || !cstr2) return; // TODO: check buffers
  size_t cstr1_end = cstr1->size;
  if (cstr1->size + cstr2->size >= cstr1->capacity) {
    cstr1->data = realloc(cstr1->data, cstr1->size + cstr2->size + 1);
    cstr1->capacity = cstr1->size + cstr2->size;
  }
  memcpy(cstr1->data + cstr1_end, cstr2->data, cstr2->size);
  cstr1->size += cstr2->size;
  cstr1->data[cstr1->size] = 0;
}

void _cstring_append_s(cstring_t* cstr, const char* str) {
  if (!cstr || !str) return;
  size_t cstr_end = cstr->size;
  size_t str_size = strlen(str);
  if (cstr->size + str_size >= cstr->capacity) {
    cstr->data = realloc(cstr->data, cstr->size + str_size + 1);
    cstr->capacity = cstr->size + str_size;
  }
  memcpy(cstr->data + cstr_end, str, str_size);
  cstr->size += str_size;
  cstr->data[cstr->size] = 0;
}

void _cstring_append_c(cstring_t* cstr, char ch) {
  if (!cstr) return;
  if (cstr->size + 1 >= cstr->capacity) {
    cstr->data = realloc(cstr->data, cstr->size + 1);
    cstr->capacity++;
  }
  cstr->data[cstr->size++] = ch;
  cstr->data[cstr->size] = 0;
}

void _cstring_insert(cstring_t* cstr1, size_t index, cstring_t* cstr2) {
  if (!cstr1 || !cstr2 || index > cstr1->size) return; // TODO: check buffers
  if (cstr1->size + cstr2->size >= cstr1->capacity) {
    cstr1->data = realloc(cstr1->data, cstr1->size + cstr2->size + 1);
    cstr1->capacity = cstr1->size + cstr2->size;
  }
  for (size_t i = cstr1->size; i >= index ; i--) {
    cstr1->data[i+cstr2->size] = cstr1->data[i];
  }
  memcpy(cstr1->data + index, cstr2->data, cstr2->size);
  cstr1->size += cstr2->size;
  cstr1->data[cstr1->size] = 0;
}

void _cstring_insert_s(cstring_t* cstr, size_t index, const char* str) {
  if (!cstr || !str || index > cstr->size) return; // TODO: check buffers
  size_t str_size = strlen(str);
  if (cstr->size + str_size >= cstr->capacity) {
    cstr->data = realloc(cstr->data, cstr->size + str_size + 1);
    cstr->capacity = cstr->size + str_size;
  }
  for (size_t i = cstr->size; i >= index ; i--) {
    cstr->data[i+str_size] = cstr->data[i];
  }
  memcpy(cstr->data + index, str, str_size);
  cstr->size += str_size;
  cstr->data[cstr->size] = 0;
}

void _cstring_insert_c(cstring_t* cstr, size_t index, char ch) {
  if (!cstr || index > cstr->size) return; // TODO: check buffers
  if (cstr->size + 1 >= cstr->capacity) {
    cstr->data = realloc(cstr->data, cstr->size + 1);
    cstr->capacity++;
  }
  for (size_t i = cstr->size; i >= index ; i--) {
    cstr->data[i+1] = cstr->data[i];
  }
  cstr->data[index] = 0;
  cstr->data[++cstr->size] = 0;
}

cstring_t* cstring_substr(cstring_t* cstr, size_t begin, size_t end) {
  return cstring_new(cstring_data(cstr), begin, end);
}

cstring_t* cstring_copy(cstring_t* cstr) {
  return cstring_new(cstring_data(cstr));
}

char cstring_get(cstring_t* cstr, size_t index) {
  return cstring_data(cstr)[index];
}

void cstring_set(cstring_t* cstr, size_t index, char value) {
  cstring_data(cstr)[index] = value;
}

char cstring_pop(cstring_t* cstr) {
  cstring_size(cstr)--;
  return cstring_data(cstr)[cstring_size(cstr)];
}