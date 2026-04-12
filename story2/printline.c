#include <stdio.h>
#include <stdlib.h> 
#include "printline.h"

char* read_file_to_string(char filename[]) {
    FILE *instream = fopen(filename, "r");

    if (instream == NULL) {
        return NULL; 
    }

  
    fseek(instream, 0, SEEK_END);
    long size = ftell(instream);

    fseek(instream, 0, SEEK_SET); 
    char *content = malloc(size + 1);
    if (content == NULL) {
        fclose(instream);
        return NULL;
    }
  
    fread(content, 1, size, instream);
    content[size] = '\0';

    fclose(instream);
    return content;
}

