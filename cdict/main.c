#include <stdio.h>
#include "dict.h"

int main(void){
  Dict* dict = new_Dict(16);
  dictSet(dict, "a", "Hello.");
  dictSet(dict, "q", "Test");
  printHashedDict(dict);
  return 0;
}