#include <stdio.h>
#include <stdlib.h>
#include "DataHandling.h"
#define MAX_SIZE 10

int main(){
//   // linked list
    struct LLNode* head=NULL;
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


////Struct Stack

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
display_stack(&stack);

////LLStack

struct LLStack* Stack;
initialize_stack(Stack);
LLpush(Stack,10);
LLpush(Stack,20);
LLpush(Stack,30);
LLpush(Stack,40);
LLpush(Stack,50);
LLpush(Stack,60);
LLpush(Stack,70);
showLLStack(Stack);
int data = 0;
data = LLpop(Stack);
printf("%d\n",data);
data = LLpop(Stack);
printf("%d\n",data);
data = LLpeek(Stack);
printf("%d\n",data);


////Tree
struct TNode* root = NULL;
root = insertTNode(root,20);
root = insertTNode(root,10);
root = insertTNode(root,30);
root = insertTNode(root,15);
root = insertTNode(root,25);
root = insertTNode(root,5);
root = insertTNode(root,35);
root = insertTNode(root,7);
root = insertTNode(root,18);
root = insertTNode(root,32);
root = insertTNode(root,4);
root = insertTNode(root,6);
root = insertTNode(root,3);
root = insertTNode(root,37);
printf("\n");
showInorder(root);
root = deleteTNode(root,10);
printf("\n");
showInorder(root);
root = deleteTNode(root,30);
printf("\n");
showInorder(root);
root = deleteTNode(root,5);
printf("\n");
showInorder(root);
    return 0;
}
