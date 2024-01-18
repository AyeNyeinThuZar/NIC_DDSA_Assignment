#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// variable declaration and initialization
int no_of_reg_user = 0;


// function declaration
void menu();
void registration();
int email_exists(char email[]);
int email_valid(char check_email[]);
int pass_length_check(char password[]);
int pass_valid_check(char password[]);
void login();
void my_privileges(int userid);
void profile(int userid);
void setting(int userid);
void history(int userid);
void logout();
void currency_transaction(int sender_id);
// create a structure
struct Db{

    int user_ID;
    char username[30];
    char email[30];
    char passcode[30];
    char dob[10];
    char addr[30];
    char country[10];
    int postal_code;
    int phone_no;
    float signs;

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
        printf("Welcome to Singularity\n");
        printf("Explore Your Sings!");
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
    int email_check_status =0;
    int password_check_status =0;
    //reg_username
    char r_username[30];
    printf("\nEnter username: ");
    scanf(" %[^\n]",&r_username);
    strcpy(data[no_of_reg_user].username,r_username);
    // end of user name registration

    //reg_email(no_of_reg_user);
    char r_email[30];
    while(email_check_status==0){
        printf("Enter your email: ");
        scanf(" %[^\n]",&r_email);
        int exist_check = email_exists(r_email);
        int valid_check = email_valid(r_email);
        if (!exist_check&&!valid_check){
            email_check_status=1;
        }else if(exist_check){
            //email_check_status=0;
            printf("email exists! Use different email!!!\n");
        }else if(valid_check){
            printf("email format invalid!\nUse 'name@domain.com' format!\nUse 'valid domain'\nUse 'lowercase character and number' only for name\n");
        }
    }
    strcpy(data[no_of_reg_user].email,r_email);
    // End of email registration

    // password registration
    //reg_passcode(no_of_reg_user);
    char r_passcode[30];
    while(password_check_status==0){
        printf("Enter user password\n-at least\n");
        printf("Minimum length -6 characters\n");
        printf("Password requirement-at least \n-One number\n-One special character\n-One Upper Case letter:  ");
        scanf("%s",&r_passcode);
        int pass_len_check_status = pass_length_check(r_passcode);
        int pass_valid_check_status = pass_valid_check(r_passcode);
        if (pass_len_check_status &&pass_valid_check_status){
            printf("password valid\n");
            password_check_status=1;
        }else if(!pass_len_check_status ){
            printf("Minimum password length must be fulfilled\n");
        }else if(!pass_valid_check_status){
            printf("Password requirement must be fulfilled\n");
        }
    }
    strcpy(data[no_of_reg_user].passcode,r_passcode);
// End password registration

// date of birth registration
    char r_dob[10];
    printf("Enter Date of birth! \nUse dd/mm/yy format!\n");
    scanf(" %[^\n]",&r_dob);
    strcpy(data[no_of_reg_user].dob,r_dob);


    char r_addr[30];
    printf("Enter your address! \n");
    scanf(" %[^\n]",&r_addr);
    strcpy(data[no_of_reg_user].addr,r_addr);

    char r_country[10];
    printf("Enter your Country! \n");
    scanf(" %[^\n]",&r_country);
    strcpy(data[no_of_reg_user].country,r_country);

    int r_postal_code;
    printf("Enter postal code! \n");
    scanf(" %[^\n]",&r_postal_code);
    data[no_of_reg_user].postal_code=r_postal_code;

    int r_phone_no = 0;
    printf("Enter user phone number: ");
    scanf("%d",&r_phone_no);
    data[no_of_reg_user].phone_no=r_phone_no;

    printf("Registration Complete!!!\n");
    no_of_reg_user++;
    data[no_of_reg_user-1].user_ID = no_of_reg_user;
    data[no_of_reg_user-1].signs = 500;

    printf("User name : %s DOB %s Ph- %d\n",data[no_of_reg_user-1].username,data[no_of_reg_user-1].dob,data[no_of_reg_user-1].phone_no);
    printf("User id : %d\n",data[no_of_reg_user-1].user_ID);
    printf("You have got %d -Signs!\n",data[no_of_reg_user-1].signs);
}

// check if same user email stored in the array
int email_exists(char email[30]){

    for (int i=0;i<=no_of_reg_user;i++){
        if(strcmp(data[i].email,email)==0){
           return 1;
           break;
        }
    }

    return 0;
}
// check if email format valid
int email_valid(char check_email[30]){
    int first_count =0;
    int email_size = strlen(check_email);
    int valid_status = -1;

    for (int i=0;i<email_size;i++){
       if (check_email[i]=='@'){
            break;
       }else{
            first_count++;
       }
    }
    // check name_valid
    if (first_count!=email_size){
        for (int i=0;i<first_count;i++){
           if  (!((check_email[i]>47&&check_email[i]<58)||(check_email[i]>96&&check_email[i]<123))){
                printf("the first part email is invalid\n");
                return 1;
            }
        }
    }else{
        printf("[+]the first part email is invalid\n");
        return 1;
    }
    //check domain_valid
    int second_count = email_size-first_count;
    int domain_arr_index=0;
    char domain_arr[second_count];

    for (int i =first_count;i<email_size;i++){
        domain_arr[domain_arr_index]=check_email[i];
        domain_arr_index++;
    }
    domain_arr[domain_arr_index]= '\0';
    int len_domain_arr=strlen(domain_arr);

    char domain1[15]={'@','g','m','a','i','l','.','c','o','m'};
    char domain2[15]={'@','y','a','h','o','o','.','c','o','m'};
    char domain3[15]={'@','a','p','p','l','e','.','c','o','m'};
    char domain4[15]={'@','o','u','t','l','o','o','k','.','c','o','m'};
    char domain5[15]={'@','n','1','c','.','c','o','m'};

    int domain1_check = strcmp(domain_arr,domain1);
    int domain2_check = strcmp(domain_arr,domain2);
    int domain3_check = strcmp(domain_arr,domain3);
    int domain4_check = strcmp(domain_arr,domain4);
    int domain5_check = strcmp(domain_arr,domain5);

    if (!(domain1_check&&domain2_check&&domain3_check&&domain4_check&&domain5_check)){
        printf("\nemail is valid\n");
        return 0;
    }else{
        printf("\nemail is invalid\n");
        return 1;
    }
}


int pass_length_check(char passcode[]){
    int len_str = strlen(passcode);
    if (len_str <6){
        return 0;
    }else{
        return 1;
    }
}
int pass_valid_check(char passcode[]){
    //char passcode[30];//={'@','Y','e','1','2'};
    int len_str = strlen(passcode);
    int number_check =0;
    int upCase_check = 0;
    int specialChar = 0;

    for (int i=0;i<len_str;i++){
        if (passcode[i]>47&&passcode[i]<57){//number check
            number_check =1;
            break;
        }
    }
    for (int i=0;i<len_str;i++){
        if (passcode[i]>64&&passcode[i]<91){//upper&@ check
            upCase_check =1;
            break;
        }
    }
    for (int i=0;i<len_str;i++){
        if(passcode[i]==33||passcode[i]==42||passcode[i]==35||passcode[i]==36||passcode[i]==37||passcode[i]==38||passcode[i]==64){
            specialChar = 1;
            break;
        }
    }
    if (number_check&&upCase_check&&specialChar){
        return 1;
    }
    return 0;
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
                my_privileges(data[i].user_ID);
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

void my_privileges(int userid){
    int option=0;
    printf("Welcome %s. Your user id is %d!!!\n",data[userid-1].username,userid);
    printf("Choose options:\n1 for currency_transaction\n2 for change settings\n3 for show history\n4 for check profile\n5 for logging out: ");
    scanf("%d",&option);

    if (option==1){
        currency_transaction(userid);
    }else if(option==2){
        setting(userid);
    }else if(option==3){
        history(userid);
    }else if(option==4){
        profile(userid);
    }else if(option==5){
        logout();
    }
}

void profile(int userid){
    printf("\nThis is my profile!\n");
    my_privileges(userid);
}
void setting(int userid){
    printf("\nChange setting\n");
    my_privileges(userid);
}
void history(int userid){
    printf("\nSee History\n");
    my_privileges(userid);
}
void logout(){
    menu();
}
void currency_transaction(int sender_id){
    int trans_option;
    int make_transaction;
    char t_email[30];
    int receiver_id=0;
    float amount=0;
    float total_amount=0;
    float transaction_fee =0;
    float transaction_bank =0;

    printf("Press 1 to check transaction fee! Press 2 to make a transaction! Press 3 to do nothing \n");
    scanf("%d",&trans_option);
    if (trans_option==1){
        printf("0.1 percent for Signs<200 \n0.2 percent for 200<=Signs<500\n");
        currency_transaction(sender_id);
    }else if(trans_option==2){
        printf("Confirm transaction, press 1! To cancel press 2\n" );
        scanf("%d",&make_transaction);
        while(make_transaction){
            printf("Give email you want to transfer:\n");
            scanf(" %[^\n]",&t_email);
            //check user exists
            for(int i=0;i<no_of_reg_user;i++){
                int valid_receiver = strcmp(t_email,data[i].email);
                if (valid_receiver==0){
                    receiver_id=data[i].user_ID;
                    make_transaction =0;
                    break;
                }
                    printf("Wrong email address!Try again:\n");
            }
        }
        //check signs and transferr
        printf("Give amount you want to transfer:\n");
        scanf("%f",&amount);
        if (amount>0&&amount<200){
            transaction_fee = amount*0.001;
        }else if (amount>=200){
            transaction_fee = amount*0.002;
        }
        total_amount=amount+transaction_fee;
        printf("Required signs is %f\n",total_amount);

        if (data[sender_id-1].signs>=total_amount){
            printf("Before transaction %s has %f and %s has %f.\n",data[sender_id-1].username,data[sender_id-1].signs,data[receiver_id-1].username,data[receiver_id-1].signs);
            data[sender_id-1].signs-=total_amount;
            data[receiver_id-1].signs+=amount;
            transaction_bank+=
            printf("After transaction %s has %f and %s has %f.\n",data[sender_id-1].username,data[sender_id-1].signs,data[receiver_id-1].username,data[receiver_id-1].signs);
            printf("Transaction bank got the charges of %f.\n",transaction_fee);
            printf("Transaction Successful!!!\n");

        }else{
            printf("Not enough sings!\nTry again: press 1! To cancel  press 2\n");
            scanf("%d",&make_transaction);
        }


        }else if(trans_option==3){
            my_privileges(sender_id);

    }
}
