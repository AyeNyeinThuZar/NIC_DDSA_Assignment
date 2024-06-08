#ifndef DATAHANDLING_H_INCLUDED
#define DATAHANDLING_H_INCLUDED
#define MINIMUM_FEERATE 0.02
#define MAXIMUM_FEERATE 0.05
#define MAXIMUM_RECORD 10

#include <stdio.h>
#include <stdlib.h>
#include "CHECK_EXIST_VALID.h"
#include "AVL.h"
#include "LOAD_STORE_FILE.h"
#include <time.h>

int g_userCount =0;
int key = 0;
int maximum_record=0;
double bank_deposit=100000;

void registration();
void login();
void record_Data();


void admin_privileges(struct AVL_Node* node);
void user_privileges(struct AVL_Node* node);
int ph_exists(struct AVL_Node* root,char phoneno[9]);
void showdata(struct AVL_Node* Node);

void menu(){
    while (1){
        printf("\nWelcome to Our Bank!!!\n");
        int option =0;
        printf("\nPress 1 to User Login: \nPress 2 to Registration: \nPress Any-key to Exit: ");
        scanf("%d",&option);
        if (option == 1){
            login();
        }else if (option == 2){
            registration();
        }else{
            record_Data();
            exit(1);
        }
    }
}

void registration(){
    printf("Welcome User Registration:\n");
    printf("%d users are registered!\n",g_userCount);
    printf("key before registered: %d\n",key);
    char r_uname[20];
    printf("\nEnter username: ");
    scanf(" %[^\n]",&r_uname);
    printf("%s\n",r_uname);

    char r_email[20];
    int email_check_status = 0;
    printf("\nEnter user email: ");
    scanf(" %[^\n]",&r_email);
    while (!email_check_status){
        if ((email_exists(root,r_email))==NULL){
            if (email_invalid(r_email)){
                printf("Email invalid! Use different email!");
                scanf(" %[^\n]",&r_email);
            }else{
                printf("Email valid\n%s\n\n",r_email);
                email_check_status = 1 ;
            }

        }else{
            printf("Email exists! Use different email!");
            scanf(" %[^\n]",&r_email);
        }
    }

    char r_passcode[20];
    int password_check_status =0;
    while(password_check_status==0){
        printf("Enter user password\n-at least\n");
        printf("Minimum length -6 characters\n");
        printf("Password requirement-at least \n-One number\n-One special character\n-One Upper Case letter:  ");
        scanf(" %[^\n]",&r_passcode);
        int pass_len_check_status = pass_length_check(r_passcode);
        int pass_valid_check_status = pass_valid_check(r_passcode);
        if (pass_len_check_status && pass_valid_check_status){
            printf("password valid\n");
            password_check_status=1;
        }else if(!pass_len_check_status ){
            printf("Minimum password length must be fulfilled\n");
        }else if(!pass_valid_check_status){
            printf("Password requirement must be fulfilled\n");
        }
    }
    printf("password to register: %s\n",r_passcode);// check password here

    char r_phoneno[20];
    int phone_check_status=0;

    while( phone_check_status==0){
        printf("Enter user phone number: ");
        scanf(" %[^\n]",&r_phoneno);
        //phone validation
        if(!ph_valid(r_phoneno)){
            printf("Valid number must have 11 numbers starting with '09'!  Please give valid number!!!\n");
        }else{
            if(ph_exists(root,r_phoneno)!=0){
                printf("Use different phone number.This number already exists!!!\n");
            }else{
                printf("Phone Valid!!!");
                break;
            }
        }
    }

    double signs=2000;
    int account_state=1;
    g_userCount++;
    key++;
    printf("key after registered: %d\n",key);

    root = insertNode(root,key,r_uname,r_email,r_passcode,r_phoneno,signs,account_state);
    printf("\n\nRegistration succeed!\n");
    printf("Root node is :%d \n",root->uid);
     if (root->left!=NULL){
        printf("Left node is: %d \n",root->left->uid);
     }
     if(root->right!=NULL){
        printf("Right node is :%d \n",root->right->uid);
     }
     if(root->left==NULL && root->right==NULL){printf("Only Root node exists\n");}

}

void profile(struct AVL_Node* node){
    printf("\nThis is my profile!\n");
    if (comp_cha_arr(node->uname,"admin1") || comp_cha_arr(node->uname,"admin3") ||comp_cha_arr(node->uname,"admin3")){
        admin_privileges(node);
    }else{
        user_privileges(node);
    }
}
void setting(struct AVL_Node* node){
    printf("\nChange setting\n");
    if (comp_cha_arr(node->uname,"admin1") || comp_cha_arr(node->uname,"admin3") ||comp_cha_arr(node->uname,"admin3")){
        admin_privileges(node);
    }else{
        user_privileges(node);
    }
}
void history(struct AVL_Node* node){
    printf("\nSee History\n");
    printf("usernode is : %s\n",node->uname);
     if (comp_cha_arr(node->uname,"admin1") || comp_cha_arr(node->uname,"admin3") ||comp_cha_arr(node->uname,"admin3")){
        admin_privileges(node);
    }else{
        user_privileges(node);
    }
}
void showdata(struct AVL_Node* Node){
    printf("%d-%s-%s-%s-%s-%lf",Node->uid,Node->uname,Node->email,Node->passcode,Node->phno,Node->signs);

    if (comp_cha_arr(Node->uname,"admin1")||comp_cha_arr(Node->uname,"admin2")||comp_cha_arr(Node->uname,"admin3")){
            admin_privileges(Node);
        }else{
            user_privileges(Node);
        }
}

void  suspend_user(struct AVL_Node* node, struct AVL_Node* suspNode){
    suspNode->account_state = 0;
    printf("Account suspending complete!");
}
void  resume_user(struct AVL_Node* node, struct AVL_Node* resumeNode){
    resumeNode->account_state = 1;
    printf("Account resuming complete!");
}

void manage_user(struct AVL_Node* node){
    printf("This is User Management Session!!!\n");
    int puser_ID=0;
    int manage_option=0;
    printf("Give user_ID to manage:    ");
    scanf("%d",&puser_ID);
    if (puser_ID==1 ||puser_ID==2||puser_ID==3){
        printf("You can't manage this account!!!\n");
        admin_privileges(node);
    }else{
        struct AVL_Node* manageNode = search_node(root,puser_ID);
        printf("Press 1 for delete user\nPress 2 for suspend user\nPress 3 for resume user\n");
        scanf("%d", &manage_option);
        switch(manage_option){
        case 1:
                printf("Manage to :  %s\n",manageNode->uname);
                root =  deleteNode(root,manageNode);
                showInorder(root);
                g_userCount--;
                break;
        case 2:
                printf("Manage to :  %s\n",manageNode->uname);
                suspend_user(root,manageNode);
                break;
        case 3:
                printf("Manage to :  %s\n",manageNode->uname);
                resume_user(root,manageNode);
                break;
        }
    }admin_privileges(node);
}

void do_transaction(struct AVL_Node* node,struct AVL_Node* trnode){
    int trans_option;
    double amount=0;
    double minimum_balance=50;
    double required_signs=0;
    double transfer_signs=0;
    double transaction_fee =0;

    printf("\nPress 1 to make a transaction! Press 2 go back: ");
    scanf("%d",&trans_option);
    switch(trans_option){
    case 1:
        printf("Give amount you want to transfer:   ");
        scanf("%lf",&amount);
            if (amount>0&&amount<200){
                transaction_fee = amount*MAXIMUM_FEERATE;
            }else if (amount>=200){
                transaction_fee = amount*MINIMUM_FEERATE;
            }
            required_signs=amount+transaction_fee+minimum_balance;
            transfer_signs = amount+transaction_fee;
            printf("Transaction fee: %lf\nTotal Transfer signs: %f\n",transaction_fee,transfer_signs);

            if (node->signs>=required_signs){
                //printf("Before transaction %s has %lf and %s has %lf.\n",node->uname,node->signs,trnode->uname,trnode->signs);
                node->signs-=transfer_signs;
                trnode->signs+=amount;
                bank_deposit+=transaction_fee;
                //printf("After transaction %s has %lf and %s has %lf.\n",node->uname,node->signs,trnode->uname,trnode->signs);

                time_t t;
                struct tm* time_info;
                char time_now[50];

                time(&t);
                time_info = localtime(&t);
                strftime(time_now,sizeof(time_now),"%Y-%m-%d-%H:%M:%S",time_info);
                tree = insertRec_Node(tree,time_now,node->uname,trnode->uname,amount);
                showRecInorder(tree);
                maximum_record++;
                printf("no of records:%d\n",maximum_record);
                if (maximum_record>MAXIMUM_RECORD){
                    printf("The first record will be deleted!!!");
                    tree = deleteMinNode(tree);
                    maximum_record--;
                    printf("no of records:%d\n",maximum_record);
                }
                break;
            }else{
                printf("Insufficient signs!!!");
                do_transaction(node,trnode);
                break;
            }
    case 2:
        if (node->uid == 1 || node->uid ==2 || node->uid==3){
            admin_privileges(node);
            break;
        }else{
            user_privileges(node);
            break;
        }
    }
}

void currency_transaction(struct AVL_Node* node){
    char t_phoneno[20];
    printf("Enter phone number you want to transfer: \n");
    scanf(" %[^\n]",&t_phoneno);
    struct AVL_Node* tr_Node = trph_node(root, t_phoneno);
    if (tr_Node!=NULL){
        printf("To Transfer user %s\n",tr_Node->uname);
        if (node->uid!=tr_Node->uid){
            do_transaction(node,tr_Node);
            showRecInorder(tree);
        }else{
            printf("You can't transfer yourself!!!");
            if (node->uid==1 ||node->uid==2 || node->uid==3){
                admin_privileges(node);
            }else{
                user_privileges(node);
            }
        }
    }else{
        printf("No user to transfer!");
    }
}

void admin_privileges(struct AVL_Node* node){
    int option=0;

    printf("\nChoose options:\n1 for currency_transaction\n2 for manage_User\n3 for show history\n4 for check profile\n5 for change settings\n6 show transaction record\n7 Go home page\n8 for logging out: ");
    scanf("%d",&option);

    if (option==1){
       currency_transaction(node);
    }else if(option==2){
        manage_user(node);
    }else if(option==3){
        history(node);
    }else if(option==4){
        profile(node);
    }else if (option==5){
        setting(node);
    }else if(option==6){
        showdata(node);
    }else if(option==7){
        menu();
    }else{
        record_Data();
        exit(1);
    }
}
void user_privileges(struct AVL_Node* node){
    int option=0;
    printf("\nChoose options:\n1 for currency_transaction\n2 for check profile\n3 for show history\n4 for change settings\n5 show transaction record\n6 Go Home page\n7 for logging out: ");
    scanf("%d",&option);

    if (option==1){
       currency_transaction(node);
    }else if(option==2){
        profile(node);
    }else if(option==3){
        history(node);
    }else if(option==4){
        setting(node);
    }else if(option==5){
        showdata(node);
    }else if(option==6){
        menu();
    }else{
        record_Data();
        exit(1);
    }
}

void login(){
    printf("\nLogin Session!\n");
    char l_email[20];
    char l_passcode[20];

    printf("Enter email: ");
    scanf(" %[^\n]",&l_email);

    printf("Enter password: ");
    scanf(" %[^\n]",&l_passcode);

    struct AVL_Node* node = login_check(root,l_email,l_passcode);
    if (node!=NULL){
        if (comp_cha_arr(node->uname,"admin1")||comp_cha_arr(node->uname,"admin2")||comp_cha_arr(node->uname,"admin3")){
            printf("Login succeed!\n");
            admin_privileges(node);
        }else{
            if (node->account_state){
                printf("Login succeed!\n");
                user_privileges(node);
            }else{
                printf("You account is suspended for 7 days!!!\n");
            }
        }
    }
}

#endif // DATAHANDLING_H_INCLUDED
