#ifndef LOADFILE_H_INCLUDED
#define LOADFILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "BANKING.h"

void load_file(){

////Loading User Data
    int uid=0;
    char uname[20];
    char email[20];
    char password[20];
    char phone[20];
    double signs=0;
    double deposit=0;
    int account_state;
    FILE *stdata = fopen("database.txt","r");
    if(!stdata){
        perror("Retrieving Data Error!\n");
    }
    else{
        fscanf(stdata,"%lf",&deposit);
        bank_deposit = deposit;
        while(fscanf(stdata,"%d %s %s %s %s %lf %d",&uid,&uname[0],&email[0],&password[0],&phone[0],&signs,&account_state)!=EOF){
            key = uid;
            root = insertNode(root,uid,uname,email,password,phone,signs,account_state);
            g_userCount++;
        }
        fclose(stdata);
    }

////Loading Transaction Records
    int no_record=0;
    char time[50];
    char sender[20];
    char receiver[20];
    double amount=0;
    FILE *sttrans = fopen("transaction.txt","r");
    if(!sttrans){
        perror("Retrieving Data Error!\n");
    }

    else{
        while(fscanf(sttrans,"%s %s %s %lf",&time[0],&sender[0],&receiver[0],&amount)!=EOF){
            //printf("insert loaded data to avl time:%s sender:%s receiver:%s amount:%lf\n",time,sender,receiver,amount);
            tree = insertRec_Node(tree,time,sender,receiver,amount);
            no_record++;
        }maximum_record=no_record;
        fclose(sttrans);
    }
}

void writeData(struct AVL_Node* root,FILE* ptr){
    if (root!=NULL){
        writeData(root->left,ptr);
        fprintf(ptr,"%d %s %s %s %s %lf %d\n",root->uid,root->uname,root->email,root->passcode,root->phno,root->signs,root->account_state);
        writeData(root->right,ptr);
        }
};
void writeTransData(struct AVL_Record* tree,FILE* ptr){
    if (tree!=NULL){
        writeTransData(tree->left,ptr);
        fprintf(ptr,"%s %s %s %lf\n",tree->tran_time,tree->sender,tree->receiver,tree->trf_amount);
        writeTransData(tree->right,ptr);
        }
};

void record_Data(){
    printf("\n\nSaving User Data to File!!!\n");
   //// printf("Transaction bank record of asset(%.2f) is stored !!!\n",transaction_bank);
    printf("%d registered users' record is stored!!!\n",g_userCount);
    // restore data
    FILE* stdata = fopen("database.txt","w");
    if(!stdata){
        perror("File not found Error!\n"); }
    fprintf(stdata,"%lf\n",bank_deposit);
    writeData(root,stdata);
    fclose(stdata);

    printf("\n\nSaving Transaction Records to File!!!\n");
    FILE* sttrans = fopen("transaction.txt","w");
    if(!sttrans){
        perror("File not found Error!\n"); }

    writeTransData(tree,sttrans);
    fclose(sttrans);
};


#endif // LOADFILE_H_INCLUDED
