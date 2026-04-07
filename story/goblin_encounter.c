#include<stdio.h>
#include "printline.h"
#include "wisdom_check.h"
int main(){

  int response;
  int health ,wisdom,wisdom_threshold;
  printline("encounter.txt");
  printline("options.txt");
  scanf("%d",&response);

check_wisdom_threshold(wisdom,wisdom_threshold,"hints.txt");

switch(response){
case 1 :
    printline("wooden_mallet.txt");
    health-=-10;
    wisdom+=5;
    
case 2 :
  printline("hanuman_gada.txt");


    health-=0;
    wisdom+=25;
    
  }
   
printf("your current score is:\n health:%d\n wisdom:%d",health , wisdom);
    return 0;
}