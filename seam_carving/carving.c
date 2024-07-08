#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Requires 1 argument (file name).\n");
    return 1;
  }
  FILE *file = fopen(argv[1], "rb");
  if(!file){
    printf("Failed to read file '%s'.\n", argv[1]);
    return 1;
  }
  fseek(file, 0L, SEEK_END);
  int size = ftell(file);
  rewind(file);
  unsigned char *contents;
  contents = (unsigned char*) malloc(size * sizeof(unsigned char));
  if (fread(contents, 1, size, file) != size) {
      printf("tf did u do dawg\n");
      return 1;
  }
  // Print in hexadecimal
  printf(" 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
  for (size_t i = 0; i < size; i++) {
    printf("%02X ", contents[i]);
    if(i % 16 == 15) printf("\n");
  }
  printf("\n");
  fclose(file);
  return 0;
}