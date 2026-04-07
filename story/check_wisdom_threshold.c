#include<stdio.h>
#include "printline.h"
int check_wisdom_threshold(int wisdom ,int wisdom_threshold ,char filename[]){
    if(wisdom<wisdom_threshold){
        printline(filename);
    }
}
