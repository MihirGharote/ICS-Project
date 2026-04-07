#include<stdio.h>
#include "printline.h"
int main(){

  int response;
  int health ,wisdom;
  printline("encounter.txt");
  printline("opitons.txt");
  scanf("%d",&response);

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