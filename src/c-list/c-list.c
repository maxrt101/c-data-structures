#include "c-list.h"

#include <stdlib.h>


void c_list_init(CList* list) {
  list->next = NULL;
  list->prev = NULL;
}


void c_list_free(CList* list) {
  if (list->next) c_list_free(list->next);
  free(list);
}


void c_list_free_del(CList* list, CListFunction deleter) {
  if (list->next) c_list_free_del(list->next, deleter);
  deleter(list);
}


int c_list_size(CList* list) {
  int i = 0;
  while (list->next) {
    c_list_next(&list);
    i++;
  }
  return i;
}


void c_list_next(CList** list) {
  *list = (*list)->next;
}


void c_list_prev(CList** list) {
  *list = (*list)->prev;
}


CList* c_list_get(CList* list, int i) {
  for (int n = 0; n < i; n++) {
    c_list_next(&list);
  }
  return list;
}


int c_list_get_idx(CList* list, CList* element) {
  int i = 0;
  while (list != element) {
    c_list_next(&list);
    i++;
  }
  return i;
}


void c_list_append(CList* list, CList* element) {
  while (list->next) c_list_next(&list);
  list->next = element;
  element->prev = list;
}


void c_list_insert(CList* list, CList* element, int i) {
  for (int n = 0; n < i-1; n++) c_list_next(&list);
  CList* next = list->next;
  list->next = element;
  element->prev = list;
  c_list_append(list->next, next);
}


void c_list_insert_here(CList* list, CList* element) {
  element->next = list->next;
  element->prev = list;
  list->next = element;
  element->next->prev = element;
}


void c_list_remove(CList* list, CList* element) {
  element->prev->next = element->next;
  element->next->prev = element->prev;
}


CList* c_list_remove_idx(CList* list, int i) {
  for (int n = 0; n < i-1; n++) c_list_next(&list);
  CList* removed = list->next;
  list->next = list->next->next;
  list->next->prev = list;
  return removed;
}


void c_list_remove_if(CList* list, CListPredicate condition) {
  CLIST_FOR(list, itr) {
    if (condition(itr)) {
      itr->prev->next = itr->next;
      itr->next->prev = itr->prev;
      CList* deleted = itr;
      itr = itr->prev;
      free(deleted);
    }
  }
}


void c_list_remove_if_del(CList* list, CListPredicate condition, CListFunction deleter) {
  CLIST_FOR(list, itr) {
    if (condition(itr)) {
      itr->prev->next = itr->next;
      itr->next->prev = itr->prev;
      CList* deleted = itr;
      itr = itr->prev;
      deleter(deleted);
    }
  }
}


int c_list_find(CList* list, CList* element) {
  int idx = 0;
  CLIST_FOR(list, itr) {
    if (itr == element) {
      return idx;
    }
    idx++;
  }
  return -1;
}


CList* c_list_find_cmp(CList* list, CListPredicate comparator) {
  CLIST_FOR(list, itr) {
    if (comparator(itr)) {
      return itr;
    }
  }
  return NULL;
}

