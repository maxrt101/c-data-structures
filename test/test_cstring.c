#include <cds/cstring.h>
#include <cds/memory.h>
#include <string.h>
#include <stdio.h>

int main() {
  cstring_t* str1 = cstring_new("Test String 123");
  if (strcmp(cstring_data(str1), "Test String 123")) return 1;

  cstring_t* str2 = cstring_new("");

  cstring_append(str2, 'c');
  cstring_append(str2, "abc");
  if (strcmp(cstring_data(str2), "cabc")) return 2;

  cstring_insert(str1, 5, "TestInsert ");
  if (strcmp(cstring_data(str1), "Test TestInsert String 123")) return 3;

  cstring_t* str3 = cstring_copy(str2);
  if (strcmp(cstring_data(str3), "cabc")) return 4;
  
  cstring_t* str4 = cstring_substr(str1, 5, 15);
  if (strcmp(cstring_data(str4), "TestInsert")) return 5;

  cstring_free(str1);
  cstring_free(str2);
  cstring_free(str3);
  cstring_free(str4);

  return 0;
}
