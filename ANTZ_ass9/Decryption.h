#ifndef DECRYPTION_H_INCLUDED
#define DECRYPTION_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void decryption(char data[],char cipher[],char key[],int num){
    int data_len = strlen(data);
    int key_len = strlen(key);
    char cipher_ch = '\0';


    int p =0;
    while(p<data_len){
        cipher_ch = data[p];
        for (int k=0;k<key_len;k++){//
            cipher_ch = cipher_ch-key[k];
        }
        cipher[p] = cipher_ch;
        p++;
    } printf("Decrypted data is:%s\n",cipher);

    int ind =0;
    for (int i=0;i<num;i++){
        //ind = field_len[i];
//        while
    }

}

#endif // DECRYPTION_H_INCLUDED
