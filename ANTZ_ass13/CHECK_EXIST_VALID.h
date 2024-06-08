#ifndef CHECKEXISTS_H_INCLUDED
#define CHECKEXISTS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"


int size_of_cha_arr(char arr[]){
    int size =0;
    for (int i=0;i<20;i++){
        if (arr[i] == '\0'){
            break;
        }
        size++;
    }
    return size;
}
int comp_cha_arr(char first[],char second[]){
    int size_1 = size_of_cha_arr(first);
    int size_2 = size_of_cha_arr(second);

    if (size_1==size_2){
        for (int i=0;i<size_1;i++){
            if (first[i]==second[i]){
                continue;
            }else{
                return 0;
            }
        }return 1;// return for same array
    }else{
        return 0;// return for different array
    }
}

struct AVL_Node* email_exists(struct AVL_Node* root,char email[]){
    if (root==NULL){
        return NULL;
    }
    if (comp_cha_arr(root->email,email)){
        return root;
    }
    struct AVL_Node* leftNode = email_exists(root->left,email);
    if (leftNode!=NULL){
        return leftNode;
    }
    return email_exists(root->right,email);
}

int email_invalid(char email[]){
    int first_count =0;
    int email_size = size_of_cha_arr(email);

    for (int i=0;i<email_size;i++){
       if (email[i]=='@'){
            break;
       }else{
            first_count++;
       }
    }
    // check name_valid
    if (first_count!=email_size){
        for (int i=0;i<first_count;i++){
           if  (!((email[i]>47&&email[i]<58)||(email[i]>96&&email[i]<123))){
                return 1;  //the first part email is invalid
            }
        }
    }else{
        return 1; //the first part email is invalid
    }
    //check domain_valid
    int second_count = email_size-first_count;
    int domain_arr_index=0;
    char domain_arr[second_count];

    for (int i =first_count;i<email_size;i++){
        domain_arr[domain_arr_index]=email[i];
        domain_arr_index++;
    }
    domain_arr[domain_arr_index]= '\0';

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
        return 0;
    }else{
        return 1;
    }
}

int pass_length_check(char passcode[20]){
    int len_str = size_of_cha_arr(passcode);
    if (len_str <6){
        return 0;
    }else{
        return 1;
    }
}
int pass_valid_check(char passcode[]){
    //char passcode[30];//={'@','Y','e','1','2'};
    int len_str = size_of_cha_arr(passcode);
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

int ph_valid(char ph_no[]){
    int len_str = size_of_cha_arr(ph_no);
    if (len_str == 11){
        if (ph_no[0]==48 && ph_no[1]==57){
            for (int j=2;j<len_str;j++){
                if(ph_no[j]>47 && ph_no[j]<58){
                    if (j==(len_str-1)){
                    return 1;}
                }
            }printf("must have numbers only");return 0;
        }else{printf("starting wrong number");return 0;}
    }else{printf("length requirement");return 0;}
}

int ph_exists(struct AVL_Node* node, char phoneno[20]){

    if (node==NULL){
        return 0;
    }
    if (comp_cha_arr(node->phno,phoneno)){
        return 1;
    }
    return ph_exists(node->left,phoneno)||ph_exists(node->right,phoneno);
}

struct AVL_Node* trph_node(struct AVL_Node* root,char phoneno[20]){
    if (root==NULL){
        return NULL;
    }
    if (comp_cha_arr(root->phno,phoneno)){
        return root;
    }
    struct AVL_Node* leftNode = trph_node(root->left,phoneno);
    if (leftNode!=NULL){
        return leftNode;
    }
    return trph_node(root->right,phoneno);
}

//struct AVL_Node* search_trNode(struct AVL_Node* node,char t_phoneno[20]){
//
//    if (node==NULL){
//        return NULL;
//    }
//    if (comp_cha_arr(node->phno,t_phoneno)){
//        return node;
//    }
//    struct AVL_Node* retNode = search_trNode(node->left,t_phoneno)||search_trNode(node->right,t_phoneno);
//    return retNode;
//};

struct AVL_Node* login_check(struct AVL_Node* root,char email[20],char password[20]) {

    if (root==NULL){
        printf("No user exists");
        return root;
    }
    struct AVL_Node* loginNode = email_exists(root,email);
    if (loginNode!=NULL){
        if (comp_cha_arr(loginNode->passcode,password)){
            return loginNode;
        }else{
            printf("Password Incorrect!!!Please enter correct password!!!\n");
            char password[20];

            printf("Enter password: ");
            scanf(" %[^\n]",&password);
            return login_check(root,email,password);
        }
    }printf("Account does not exist!!!\n");
    return NULL;
};

#endif // CHECKEXISTS_H_INCLUDED
