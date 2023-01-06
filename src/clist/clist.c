#include <cds/clist.h>
#include <cds/memory.h>

void clist_create(clist_t* list) {
  list->next = NULL;
  list->prev = NULL;
}

void _clist_delete_wrapper(clist_delete_args_t args) {
  _clist_delete(args.list, args.deleter);
}

void _clist_delete(clist_t* list, clist_unary_t deleter) {
  clist_t* node = list;
  while (node) {
    clist_t* next = node->next;
    if (deleter) {
      deleter(node);
    } else {
      free(node);
    }
    node = next;
  }
}

size_t clist_size(clist_t* list) {
  if (!list) return 0;
  size_t size = 1;
  while (list->next) {
    list = list->next;
    size++;
  }
  return size;
}

clist_t* clist_get(clist_t* list, int index) {
  list = clist_first(list);
  for (int i = 0; i < index; i++) {
    if (!list) return NULL;
    list = list->next;
  }
  return list;
}

clist_t* clist_first(clist_t* list) {
  if (!list) return NULL;
  while (list->prev) {
    list = list->prev;
  }
  return list;
}

clist_t* clist_last(clist_t* list) {
  if (!list) return NULL;
  while (list->next) {
    list = list->next;
  }
  return list;
}

void clist_prepend(clist_t* list, clist_t* element) {
  if (!list || !element) return;
  list = clist_first(list);
  list->prev = element;
  element->next = list;
}

void clist_append(clist_t* list, clist_t* element) {
  if (!list || !element) return;
  list = clist_last(list);
  list->next = element;
  element->prev = list;
}

void clist_insert(clist_t* list, clist_t* element) {
  element->prev = list->prev;
  element->next = list;
  list->prev->next = element;
  list->prev = element;
}

void clist_insert_at(clist_t* list, int index, clist_t* element) {
  clist_insert(clist_get(list, index), element);
}

void _clist_remove_wrapper(clist_delete_args_t args) {
  _clist_remove(args.list, args.deleter);
}

void _clist_remove(clist_t* element, clist_unary_t deleter) {
  if (!element) return;
  element->prev->next = element->next;
  element->next->prev = element->prev;
  if (deleter) {
    deleter(element);
  } else {
    free(element);
  }
}

void _clist_remove_at_wrapper(clist_remove_at_args_t args) {
  _clist_remove_at(args.list, args.index, args.deleter);
}

void _clist_remove_at(clist_t* list, int index, clist_unary_t deleter) {
  _clist_remove(clist_get(list, index), deleter);
}

int clist_find_pos(clist_t* element) {
  clist_t* list = clist_first(element);
  int index = 0;
  CLIST_FOR(list, e) {
    if (e == element) {
      return index;
    }
    index++;
  }
  return -1;
}

clist_t* clist_find(clist_t* list, clist_predicate_t fn) {
  if (!list || !fn) return NULL;
  CLIST_FOR(list, e) {
    if (fn(e)) {
      return e;
    }
  }
  return NULL;
}
