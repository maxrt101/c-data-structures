#ifndef CDS_C_LIST_H_
#define CDS_C_LIST_H_

#include <stdbool.h>

typedef struct CList CList;

struct CList {
  CList* prev;
  CList* next;
};

#define CLIST_FOR(l, iter)      for (CList* iter = l; iter != NULL; c_list_next(&iter))
#define CLIST_FOR_REV(l, iter)  for (CList* iter = l; iter != NULL; c_list_prev(&iter))
#define CLIST_FOREACH(l, f)     for (CList* iter = l; iter != NULL; c_list_next(&iter)) f(iter)
#define CLIST_FOREACH_REV(l, f) for (CList* iter = l; iter != NULL; c_list_prev(&iter)) f(iter)

#define CLIST_FIND(l, idx, cond) {\
  idx = -1;\
  int _iter_index = 0;\
  CLIST_FOR(l, x) {\
    if (cond) {\
      idx = _iter_index;\
      break;\
    }\
    _iter_index++;\
  }\
}

typedef bool (*CListPredicate)(CList*);
typedef void (*CListFunction)(CList*);

void   c_list_init(CList* list);
void   c_list_free(CList* list);
void   c_list_free_del(CList* list, CListFunction deleter);
int    c_list_size(CList* list);
void   c_list_next(CList** list);
void   c_list_prev(CList** list);
CList* c_list_get(CList* list, int i);
int    c_list_get_idx(CList* list, CList* element);
void   c_list_append(CList* list, CList* element);
void   c_list_insert(CList* list, CList* element, int i);
void   c_list_insert_here(CList* list, CList* element);
void   c_list_remove(CList* list, CList* element);
CList* c_list_remove_idx(CList* list, int i);
void   c_list_remove_if(CList* list, CListPredicate condition);
void   c_list_remove_if_del(CList* list, CListPredicate condition, CListFunction deleter);
int    c_list_find(CList* list, CList* element);
CList* c_list_find_cmp(CList* list, CListPredicate comparator);

#endif

