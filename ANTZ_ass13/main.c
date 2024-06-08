#include <stdio.h>
#include <stdlib.h>
#include "LOAD_STORE_FILE.h"
#include "BANKING.h"
#include<time.h>


int main(){
    load_file();
    printf("Bank deposits : %lf \n",bank_deposit);

    printf("\nUsers'_Data\n");
    printf("%d users are already registered.\n",g_userCount);
    showInorder(root);

    printf("\nTransaction Records_Data\n");
    printf("%d transaction records are loaded!\n",maximum_record);
    showRecInorder(tree);
    menu();

    return 0;
}
