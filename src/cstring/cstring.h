#ifndef _CDS_CSTRING_H_
#define _CDS_CSTRING_H_ 1

#include <stddef.h>

typedef struct cstring_t cstring_t;

struct cstring_t {
  size_t size;
  size_t capacity;
  char* data;
};

typedef struct cstring_new_args_t cstring_new_args_t;

struct cstring_new_args_t {
  const char* src;
  size_t begin;
  size_t end;
};

typedef struct cstring_create_args_t cstring_create_args_t;

struct cstring_create_args_t {
  cstring_t* str;
  const char* src;
  size_t begin;
  size_t end;
};

#define cstring_capacity(cstr) ((cstr)->capacity)
#define cstring_size(cstr) ((cstr)->size)
#define cstring_data(cstr) ((cstr)->data)

#define cstring_new(...) _cstring_new_wrapper((cstring_new_args_t){__VA_ARGS__})
#define cstring_create(...) _cstring_create_wrapper((cstring_create_args_t){__VA_ARGS__})

#define cstring_append(cstr, val) \
  _Generic((val), \
     cstring_t*: _cstring_append,\
    const char*: _cstring_append_s, \
          char*: _cstring_append_s, \
           int: _cstring_append_c \
  )(cstr, val)

#define cstring_insert(cstr, idx, val) \
  _Generic((val), \
     cstring_t*: _cstring_insert,\
    const char*: _cstring_insert_s, \
          char*: _cstring_insert_s, \
           int: _cstring_insert_c \
  )(cstr, idx, val)

cstring_t* _cstring_new_wrapper(cstring_new_args_t args);
cstring_t* _cstring_new(const char* str, size_t begin, size_t end);

void _cstring_create_wrapper(cstring_create_args_t args);
void _cstring_create(cstring_t* cstr, const char* str, size_t begin, size_t end);

void cstring_delete(cstring_t* cstr);
void cstring_free(cstring_t* cstr);

void _cstring_append(cstring_t* cstr1, cstring_t* cstr2);
void _cstring_append_s(cstring_t* cstr, const char* str);
void _cstring_append_c(cstring_t* cstr, char ch);

void _cstring_insert(cstring_t* cstr1, size_t index, cstring_t* cstr2);
void _cstring_insert_s(cstring_t* cstr, size_t index, const char* str);
void _cstring_insert_c(cstring_t* cstr, size_t index, char ch);

cstring_t* cstring_substr(cstring_t* cstr, size_t begin, size_t end);
cstring_t* cstring_copy(cstring_t* cstr);

char cstring_get(cstring_t* cstr, size_t index);
void cstring_set(cstring_t* cstr, size_t index, char value);

char cstring_pop(cstring_t* cstr);

// size_t _cstring_find(cstring_t* cstr1, cstring_t* cstr2);
// size_t _cstring_find_s(cstring_t* cstr, const char* str);
// size_t _cstring_find_c(cstring_t* cstr, char ch);

#endif /* _CDS_CSTRING_H_ */