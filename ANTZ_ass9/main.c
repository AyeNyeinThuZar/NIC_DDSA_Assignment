#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Encryption.h"
#include"Decryption.h"


typedef struct {
    char name[15];
    char pwd[15];
    char phno[15];
}info;

info user[3];
info user_back[3];
info temp[3];
int field_len[3];

int main(){
    char collect_data[150]={};
    char cipher_data[150]={};
    char write_data[3][150]={};
    char collect_data1[3][150]={};
    char ci2pl_data[3][150]={};
    int len[3];

//    user initialization
    info user[]={{"admin1","@tMi&1*","094200001"},{"admin2","@tMi&2*","094211115"},{"user1","Y0u1#r","094203579"}};
    int no_of_user = sizeof(user)/sizeof(user[0]);
    printf("Number of users: %d\n\n",no_of_user);

    char key[15];
    strcpy(key,"keytoencrypt");

    // collect data from structure and encrypt
     for (int i= 0; i<no_of_user;i++){

        sprintf(collect_data,"%s%s%s",user[i].name,user[i].pwd,user[i].phno);
        //sprintf(collect_data,"%d%s%d%s%d%s",strlen(user[i].name),user[i].name,strlen(user[i].pwd),user[i].pwd,strlen(user[i].phno),user[i].phno);
        printf("\nPlaintxt data%d => %s , datalength is: %d\n",i,collect_data,strlen(collect_data));          // make a single string data
        len[i]=strlen(collect_data);

        field_len[i] = strlen(user[i].name);
        field_len[i+1] =strlen(user[i].pwd);
        field_len[i+2] =strlen(user[i].phno);
        printf("Field length => namelen:%d - pwlen:%d - phlen:%d\n",strlen(user[i].name),strlen(user[i].pwd),strlen(user[i].phno));

        encryption(collect_data,cipher_data,"keytoencrypt");       // encrypt single string data and return cipher
        strcpy(write_data[i],cipher_data);
        printf("Cipher_data user%d => %s\n",i,write_data[i]);
    }

    //    write data to file
    FILE* stdata = fopen("Encrypt.txt","wb");
    if(!stdata){
        perror("Recording Data Error!\n"); }
    printf("\n");
    for (int i=0;i<no_of_user;i++){
        printf("Stored Data to file => User%d :%s\n",i,write_data[i]);
        fprintf(stdata,write_data[i]);
    }

    fclose(stdata);

    //    retrieve data
    printf("\nLoading cipher data from the file!!!\n");
    //int len = strlen(collect_data);
    int users=0;
    char ch;
    int rdlen =0;
    stdata = fopen("Encrypt.txt","rb");
    while (users<no_of_user){
        while(rdlen != len[users]){
            ch = fgetc(stdata);
            cipher_data[rdlen]=ch;
            rdlen++;
        }
        strcpy(collect_data1[users],"");
        strcpy(collect_data1[users],cipher_data);
        printf("User%d data: %s\n",users,collect_data1[users]);
        users++;
        rdlen=0;

    }
    fclose(stdata);

//    decrypt and restore database
    printf("\nDecryption Started\n"); // call decryption

    for (int i=0;i<no_of_user;i++){
        decryption(collect_data1[i],ci2pl_data[i],key,no_of_user);
    }
//    for (int )
return 0;
}
