#include <stdio.h>
#include <string.h>
#include "printline.h"

void printline(char filename[]) {
    FILE *instream;
    
    instream = fopen(filename, "r");
    
  
    if (instream == NULL) {
        printf("\n[ ERROR ]: OOPS! We had some trouble opening the file: \"%s\"\n", filename);
        printf("Check if the filename is spelled correctly and is in the right folder.\n");
        return; 
    }

    char line[1000];


    while (fgets(line, sizeof(line), instream)) {
        printf("%s", line);
    }

   
    fclose(instream);
}


