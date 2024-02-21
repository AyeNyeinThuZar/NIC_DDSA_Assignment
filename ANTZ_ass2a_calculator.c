
#include<stdio.h>

int operation();
float calculator(float num1,float num2,int opr);

int num1=0;
int num2=0;
int operator=0;

int main(){
    printf("Enter the first number: ");
    scanf("%d",&num1);

    printf("Enter the second number: ");
    scanf("%d",&num2);

    operator = operation();
    calculator(num1,num2,operator);


    return 0;
}


 float calculator(float num1,float num2, int opr){

     if (opr==1){
        printf("The result is %.1f + %.1f = %.2f\n",num1,num2,num1+num2);
     }else if(opr==2){
        printf("The result is %.1f - %.1f = %.2f\n",num1,num2,num1-num2);
     }else if(opr==3){
        printf("The result is %.1f * %.1f = %.2f\n",num1,num2,num1*num2);
     }else if(opr==4){
        printf("The result is %.1f / %.1f = %.2f\n",num1,num2,num1/num2);
     }else{
        printf("NO OPERATION!!");
     }


      return 0;
 }
int operation(){
    int opr =0;
    printf("Enter '1' for add \n '2' for subtract \n '3' for multiply \n '4' for division:  ");
    scanf("%d",&opr);
    puts("");
    return opr;
}



