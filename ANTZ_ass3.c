#include<stdio.h>
#include<stdlib.h>

void menu();
void registration();
void login();
void copy_char_data_(char destination[30],char source[30]);
int comp_cha_arr(char first[30],char second[30]);
int size_of_cha_arr(char arr[30]);
void goto_app();
void choose_option();
void profile();
void setting();
void history();
void logout();

int no_of_users = 0;

struct Db{

    char username[30];
    char email[30];
    char passcode[30];
    int phone_no;

};
struct Db data[5];

int main(){

    menu();

    return 0;
}
void menu(){
    while (1){
        int option =0;
        printf("Enter '1' for User registration: \nEnter '2' for User login: ");
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
    int no_of_reg = 0;
    char r_username[30];
    char r_email[30];
    char r_passcode[30];
    int r_phone_no = 0;

    printf("Welcome User Registration:\nGive no. of users to register :");
    scanf("%d",&no_of_reg);
    for (int i=0;i<no_of_reg;i++){
        printf("\nEnter username: ");
        scanf(" %[^\n]",&r_username);
        copy_char_data_(data[i].username,r_username);

        printf("Enter user email: ");
        scanf(" %[^\n]",&r_email);
        copy_char_data_(data[i].email,r_email);

        printf("Enter password(at least 6-characters): ");
        scanf(" %[^\n]",&r_passcode);
        copy_char_data_(data[i].passcode,r_passcode);

        printf("Enter user phone number: ");
        scanf("%d",&r_phone_no);
        data[i].phone_no = r_phone_no;

        no_of_users ++;
    }printf("Registration Complete!!!\n\n");
}

void login(){
    int no_check_users =0;
    char l_email[30];
    char l_passcode[30];

    printf("Enter email: ");
    scanf(" %[^\n]",&l_email);
    printf("Enter password: ");
    scanf(" %[^\n]",&l_passcode);

    for (int i=0;i<no_of_users ;i++){
        no_check_users++;

        if (comp_cha_arr(l_email,data[i].email)){
            if (comp_cha_arr(l_passcode,data[i].passcode)){
                printf("Login Succeed!!!\n\n");
                goto_app();
                break;
                }else{
                    printf("Username and password did not match!!!\n\n");
                    break;
                }
        }
        if (no_of_users==no_check_users){
            printf("Login Failed!!!\n\n");
        }
    }
}

void copy_char_data_(char destination[30],char source[30]){
    int i =0;
    for (i=0;i<30;i++){
        if (source[i]=='\0'){
            break;
        }else{
            destination[i]=source[i];
        }
    }
}

int comp_cha_arr(char cha_arr1[30],char cha_arr2[30]){

    int size_1 = size_of_cha_arr(cha_arr1);
    int size_2 = size_of_cha_arr(cha_arr2);
    //printf("size1 = %d, size2 =%d\n",size_1,size_2);

    if (size_1==size_2){
        for (int i=0;i<size_1;i++){
            if (cha_arr1[i]==cha_arr2[i]){
                continue;
            }else{
                return 0;
            }

        }return 1;

    }else{
        return 0;
    }

}
int size_of_cha_arr(char arr[30]){
    int size =0;
    for (int i=0;i<30;i++){
        if (arr[i] == '\0'){
            break;
        }
        size++;
    }

    return size;
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
    exit(1);
}
