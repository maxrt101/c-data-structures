#ifndef _CDS_MEMORY_H_
#define _CDS_MEMORY_H_ 1

#include <stddef.h>
#include <stdlib.h>

typedef struct new_args_t new_args_t;

struct new_args_t {
  size_t size;
  size_t count;
};

#define new(type, ...) _new((new_args_t){sizeof(type), __VA_ARGS__})

void* _new(new_args_t args);

#endif /* _CDS_MEMORY_H_ */