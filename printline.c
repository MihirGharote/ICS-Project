#include<stdio.h>
#include<string.h>
#include "printline.h"


void printline(char filename[]){
    FILE*instream;
    instream=fopen(filename,"r");
    if(instream==NULL){
        printf("OOPS! We had some trouble opening this file ");
    }
    char line[1000];
    while(fgets(line,streln(line)-1,instream)){
        printf("%s",line);
    }
}
fclose(file);


int main(){
     

    return 0;
}