#include <stdio.h>
#include <stdlib.h>
#include "DataHandling.h"
#define MAX_SIZE 10

int main(){
   // linked list
    struct Node* head=NULL;
    // join appending node
    Add_Node(&head,6,2);
    Add_Node(&head,7,2);
    Add_Node(&head,9,2);
    Add_Node(&head,10,2);
    showNodedata(head,'f');
    showNodedata(head,'b');
//     join leading node
    Add_Node(&head,5,1);
    Add_Node(&head,4,1);
    Add_Node(&head,2,1);
    Add_Node(&head,1,1);
    showNodedata(head,'f');
    showNodedata(head,'b');
//    join intermediate node
    Add_Node(&head,8,3);
    Add_Node(&head,3,3);

    deleteNode(&head,1);
    showNodedata(head,'f');
    showNodedata(head,'b');

    deleteNode(&head,3);
    showNodedata(head,'f');
    showNodedata(head,'b');

    deleteNode(&head,10);
    showNodedata(head,'f');
    showNodedata(head,'b');


//Stack

struct Stack stack;
Initialize_struct(&stack);
push(&stack,0);
push(&stack,1);
push(&stack,2);
push(&stack,3);
push(&stack,4);
push(&stack,5);
push(&stack,6);
push(&stack,7);
push(&stack,8);
printf("\n");
display_stack(&stack);
push(&stack,9);
printf("\n");
display_stack(&stack);
//push(&stack,10);
//display_stack(&stack);

int peek_value =peek(&stack);
printf("%d\n",peek_value);
display_stack(&stack);

int pop_value = pop(&stack);
printf("%d\n",pop_value);
    return 0;
}
