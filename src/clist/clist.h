#ifndef _CDS_CLIST_H_
#define _CDS_CLIST_H_ 1

#include <stddef.h>
#include <stdbool.h>

typedef struct clist_t clist_t;

struct clist_t {
  clist_t* prev;
  clist_t* next;
};

typedef bool (*clist_predicate_t)(clist_t*);
typedef void (*clist_unary_t)(clist_t*);
typedef bool (*clist_binary_t)(clist_t*, clist_t*);

typedef struct clist_delete_args_t clist_delete_args_t;

struct clist_delete_args_t {
  clist_t* list;
  clist_unary_t deleter;
};

typedef struct clist_remove_at_args_t clist_remove_at_args_t;

struct clist_remove_at_args_t {
  clist_t* list;
  int index;
  clist_unary_t deleter;
};

#define clist_delete(...) _clist_delete_wrapper((clist_delete_args_t){__VA_ARGS__})
#define clist_remove(...) _clist_remove_wrapper((clist_delete_args_t){__VA_ARGS__})
#define clist_remove_at(...) _clist_remove_at_wrapper((clist_remove_at_args_t){__VA_ARGS__})

#define CLIST_FOR(list, iter) for (clist_t* iter = list; iter; iter = iter->next)
#define CLIST_FOR_REV(list, iter) for (clist_t* iter = list; iter; iter = iter->prev)
#define CLIST_FOREACH(list, fn) CLIST_FOR(list, iter) fn(iter)
#define CLIST_FOREACH_REV(list, fn) CLIST_FOR_REV(list, iter) fn(iter)

#define CLIST_FIND(list, index, cond) \
  do { \
    index = -1; \
    int iter_index = 0; \
    CLIST_FOR(list, iter) { \
      if (cond) { \
        index = iter_index; \
        break; \
      } \
      iter_index++; \
    } \
  } while(0)


void clist_create(clist_t* list);

void _clist_delete_wrapper(clist_delete_args_t args);
void _clist_delete(clist_t* list, clist_unary_t deleter);

size_t clist_size(clist_t* list);

clist_t* clist_get(clist_t* list, int index);
clist_t* clist_first(clist_t* list);
clist_t* clist_last(clist_t* list);

void clist_prepend(clist_t* list, clist_t* element);
void clist_append(clist_t* list, clist_t* element);
void clist_insert(clist_t* list, clist_t* element);
void clist_insert_at(clist_t* list, int index, clist_t* element);

void _clist_remove_wrapper(clist_delete_args_t args);
void _clist_remove(clist_t* list, clist_unary_t deleter);
void _clist_remove_at_wrapper(clist_remove_at_args_t args);
void _clist_remove_at(clist_t* list, int index, clist_unary_t deleter);

// void clist_remove_if(clist* list, clist_predicate_t pred);
// void clist_sort(clist_t* list, clist_binary_t comparator);

int clist_find_pos(clist_t* list, clist_t* element);
clist_t* clist_find(clist_t* list, clist_predicate_t fn);

#endif /* _CDS_CLIST_H_ */
