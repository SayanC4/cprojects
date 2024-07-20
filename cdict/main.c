#include <stdio.h>
#include "dict.h"

int main(void){
  Dict* dict = new_dict(16);
  dict_set(dict, "a", "Hello.");
  dict_set(dict, "q", "Test");
  print_hashed_dict(dict);
  return 0;
}
