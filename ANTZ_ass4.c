#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// variable declaration and initialization
int no_of_reg_user = 0;


// function declaration
void menu();
void registration();
void reg_username(int num);
void reg_email(int num);
void reg_passcode(int num);
int check_length(char password[]);
int check_consists_number(char password[]);
int check_special_char(char password[]);
int check_Up_case(char password[]);
void reg_phone_no(int num);
void login();
void goto_app();
void choose_option();
void profile();
void setting();
void history();
void logout();

// create a structure
struct Db{

    char username[30];
    char email[30];
    char passcode[30];
    int phone_no;

};
struct Db data[5];

// main function
int main(){

    menu();

    return 0;
}

// Choice menu
void menu(){
    while (1){
        int option =0;
        printf("\nPress 1 to Register: \nPress 2 to User login: \nPress Any-key to Exit: ");
        scanf("%d",&option);
        if (option == 1){
            registration();
        }else if (option == 2){
            login();
        }else{
            exit(1);
        }
    }
}

void registration(){

    printf("Welcome User Registration:\n");

    reg_username(no_of_reg_user);
    reg_email(no_of_reg_user);
    reg_passcode(no_of_reg_user);
    reg_phone_no(no_of_reg_user);

    printf("Registration Complete!!!\n");
    //printf("%d %s %s %s %d\n",no_of_reg_user+1,data[no_of_reg_user].username,data[no_of_reg_user].email,data[no_of_reg_user].passcode,data[no_of_reg_user].phone_no);
    no_of_reg_user++;
}

void reg_username(int num){

    char r_username[30];
    printf("\nEnter username: ");
    scanf(" %[^\n]",&r_username);
    strcpy(data[num].username,r_username);

    }

void reg_email(int num){

    char r_email[30];
    printf("Enter your email: ");
    scanf(" %[^\n]",&r_email);

    // check if same user email stored in the array
    for (int i=0;i<=num;i++){
        int check_status = strcmp(data[i].email,r_email);
        //printf("check status value %d\n",check_status);

        if (check_status==0){
            printf("email exists! Use different email!\n");
            printf("Enter your email: ");
            scanf(" %[^\n]",&r_email);
        }else{
            if (i==num){
                strcpy(data[i].email,r_email);
                //printf("i=%d   num=%d   copy email\n",i,num);
            }
        }
    }
}


void reg_passcode(int num){
    char r_passcode[30];
    printf("Enter user password\nPassword requirement-at least\n");
    printf("-6 characters\n-a number\n-a special character\n-Upper Case letter:  ");
    scanf("%s",&r_passcode);
    //printf("%s\n",r_passcode);

    int xx = check_length(r_passcode);
    int xy = check_consists_number(r_passcode);
    int yx = check_special_char(r_passcode);
    int yy = check_Up_case(r_passcode);
    //printf("%d  %d  %d  %d",xx,xy,yx,yy);
    if (xx && xy && yx && yy){
        strcpy(data[num].passcode,r_passcode);
       // printf("%s\n",data[num].passcode);
    }else{
        printf("\nCheck and fulfill password requirements!\n");
        reg_passcode(no_of_reg_user);
    }
}

int check_length(char passcode[]){
    int len_str = strlen(passcode);
    if (len_str <6){
        return 0;
    }else{
        return 1;
    }
}
int check_consists_number(char passcode[]){
    int len_str = strlen(passcode);
    int int_ascii[]={48,49,50,51,52,53,54,55,56,57};
    int size = sizeof(int_ascii)/sizeof(int_ascii[0]);

    for (int j=0;j<len_str;j++){
        char ch = passcode[j];
       // printf("%c\n",ch);
        int c = (int) ch;
      //  printf("%d\n",c);

        for (int i=0;i<size;i++){
            int x = int_ascii[i];
           // printf("%d = %d?  \n",c,x);
            if (c == x){
                return 1;
                break;
            }
        }
    }return 0;
}
int check_special_char (char passcode[]){
    int len_str = strlen(passcode);
    int spec_ascii[]={33,35,36,37,38,42,64};
    int size = sizeof(spec_ascii)/sizeof(spec_ascii[0]);

    for (int j=0;j<len_str;j++){
        char ch = passcode[j];
        int c = (int) ch;

        for (int i=0;i<size;i++){
            int x = spec_ascii[i];
            if (c == x){
                return 1;
                break;
            }
        }
    }return 0;
}

int check_Up_case(char passcode[]){
    int len_str = strlen(passcode);
    int upCase_ascii[]={65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
    int size = sizeof(upCase_ascii)/sizeof(upCase_ascii[0]);

    for (int j=0;j<len_str;j++){
        char ch = passcode[j];
        int c = (int) ch;

        for (int i=0;i<size;i++){
            int x = upCase_ascii[i];
            if (c == x){
                return 1;
                break;
            }
        }
    }return 0;
}

void reg_phone_no(int num){
    int r_phone_no = 0;
    printf("Enter user phone number: ");
    scanf("%d",&r_phone_no);
    data[num].phone_no = r_phone_no;
}

void login(){
    int no_check_users =0;
    char l_email[30];
    char l_passcode[30];

    printf("Enter email: ");
    scanf(" %[^\n]",&l_email);
    printf("Enter password: ");
    scanf(" %[^\n]",&l_passcode);

    for (int i=0;i<no_of_reg_user ;i++){
        no_check_users++;
        if (!strcmp(l_email,data[i].email)){
            if (!strcmp(l_passcode,data[i].passcode)){
                printf("Login Succeed!!!\n\n");
                goto_app();
                break;
            }else{
                printf("Username and password did not match!!!\n\n");
                break;
            }
        }
        if (no_of_reg_user==no_check_users){
            printf("Login Failed!!!\n\n");
        }
    }
}

void goto_app(){
    printf("Welcome Our Home Page or Application!!!\n\n");
    choose_option();
}
void choose_option(){
    int option=0;
    printf("Choose options:\n1 for check profile\n2 for change settings\n3 for show history\n4 for logging out: ");
    scanf("%d",&option);
    if (option==1){
        profile();
    }else if(option==2){
        setting();
    }else if(option==3){
        history();
    }else if(option==4){
        logout();
    }else{
        printf("Use Application!!\n");
    }

}
void profile(){
    printf("\nThis is my profile!\n");
    goto_app();
}
void setting(){
    printf("\nChange setting\n");
    goto_app();
}
void history(){
    printf("\nSee History\n");
    goto_app();
}
void logout(){
    menu();
}

