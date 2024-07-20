#include <stdio.h>
#include <stdlib.h>

/** options:
 *  compile.exe                     (0)
 *  compile.exe -h                  (1)
 *  compile.exe -i file.bf          (2)
 *  compile.exe -o out.x            (2)
 *  compile.exe -i file.bf -o out.x (4)
 */

char *input = NULL;
char *output = NULL;

char *read_file(char *fname){
    FILE *fptr = fopen(fname, "r");
    fseek(fptr, 0, SEEK_END);
    long len = ftell(fptr); rewind(fptr);
    char *buffer = (char*) malloc(len * sizeof(char));
    fread(buffer, len, 1, fptr); 
    return buffer;
}

int main(int argc, char *argv[]){
    switch(argc){
        case 0: ;
        case 1: ;
        case 2: ;
        case 4: ;
        default: printf("too many word");
    }
    return 0;
}