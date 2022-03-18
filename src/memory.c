#include <cds/memory.h>

void* _new(new_args_t args) {
  return malloc(args.size * (args.count > 0 ? args.count : 1));
}
