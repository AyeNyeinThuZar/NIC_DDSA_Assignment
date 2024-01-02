#include<stdio.h>

char stu_arr[3] = {'A','B','C'};
int stu_marks[3][6] = {};
int total_marks[3] ={};

char result_arr[3] = {};
int dist_count[6] ={};

void isPass();
void isTop();
void couunt_distinction();

int main(){
    int p =0;
    int i =0;
    int j =0;

    for(i = 0; i < 3; i++){
        for( j = 0; j < 6; j++){
            printf("Enter subject mark : ");
            scanf("%d",&stu_marks[i][j]);
            total_marks[i]+=stu_marks[i][j];
        }

        printf("Total_marks of %c is %d\n",stu_arr[i],total_marks[i]);
        puts("");
    }
    isPass();
    puts("");
    isTop();
    puts("");
    couunt_distinction();

    return 0;
}


void isPass(){

    int i =0;
    int j=0;
    for(i = 0; i < 3; i++){
        for( j = 0; j < 6; j++){
            if (stu_marks[i][j]<60){
                result_arr[i]= 'F';
                printf("Student %c is Fail!\n",stu_arr[i]);
                break;
            }
            else{
                if (j+1==6){
                    result_arr[i]='P';
                    printf("Student %c is Pass!\n",stu_arr[i]);
                }
            }

        }
    }
}

void isTop(){
    int i = 0;
    int top_mark = 0;
    int top_mark1 = 0;
    int count_F =0;
    char stu = ' ';
    char stu1 =' ';


    while(i<3){
        if (result_arr[i]=='P'){
            if (total_marks[i]>top_mark){
                top_mark = total_marks[i];
                stu = stu_arr[i];
            }else{
                i++;
            }

        }else{
            if (total_marks[i]>top_mark1){
                top_mark1 = total_marks[i];
                stu1 = stu_arr[i];
                count_F++;
            }else{
                i++;
            }
        }

    }
    if (count_F==3){
        printf("Student %c gets top marks.\n",stu1);

    }else{
         printf("Student %c gets top marks.\n",stu);
    }

}

void couunt_distinction(){
    int i =0;
    int j=0;
    //int count =0;


    for(i = 0; i < 3; i++){
        if (result_arr[i]=='P'){
            for( j = 0; j < 6; j++){
                if (stu_marks[i][j]>80){
                    dist_count[i]++;
                }
            }

            printf("Student %c gets %d distinctions!\n",stu_arr[i],dist_count[i]);
        }


    }


}

