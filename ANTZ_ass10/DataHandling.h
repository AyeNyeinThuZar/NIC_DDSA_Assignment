#ifndef DATAHANDLING_H_INCLUDED
#define DATAHANDLING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

/*
LINKED LIST STRUCTURE
required function
creation of newnode
joining node at head,tail and intermediate
deleting node at head,tail and intermediate
displaying node for forward and backward directions
*/

//create linked list structure
struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};


struct Node* createNewnode(int newData){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// create new node and link
void Add_Node(struct Node** node,int key,int mode){
// mode=1 => add as begin node, mode=2 => add as last node, moce=3 => add as middle node
    printf("\nAdd Node:%d",key);
    struct Node* temp;
    temp = *node;
    if (mode==1){
        struct Node* start = createNewnode(key);
        if (temp==NULL){
             temp= start;
        }else{
            start->next=temp;
            temp->prev= start;
            temp= start;
        }
    }
    else if (mode==2){
        struct Node* last = createNewnode(key);
        struct Node* temp_1;
        temp_1 = temp;
        if (temp==NULL){
            temp = last;
        }else{
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = last;
            last->prev = temp;
            temp = temp_1;
         }
    }else{
        struct Node* middle = createNewnode(key);
        struct Node* temp_1;
        temp_1=temp;
        while (1){
            if ((temp->data<key && key<temp->next->data)||(temp->data>key && key>temp->next->data)){
                middle->prev = temp;
                middle->next = temp->next;
                middle->prev->next = middle;
                middle->next->prev = middle;
                break;
            }else{
                temp = temp->next;
            }
        }temp = temp_1;
    }
    *node = temp;
}

void deleteNode(struct Node** node,int key){
    printf("\nDelete Node:%d",key);
    struct Node* temp=*node;
    //delete head
    if (temp->data==key){
        *node = temp->next;
        temp->next->prev = NULL;
        free(temp);
    }else{
        while (temp->data!=key){
            temp = temp->next;
        }
        //delete tail
        if(temp->prev!=NULL && temp->next==NULL){
            temp->prev->next=NULL;
            free(temp);

        }else{//delete middle node
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
    }
}

void showNodedata(struct Node* node,char ch){
    if (ch == 'f'){
        printf("\n\nForward Display Node:\n");
        while (node!=NULL){
            printf("-Node %d\n",node->data);
            node = node->next;
        }
    }else if(ch =='b'){
        // go to the last node
        printf("Backward Display Node:\n");
        while (node->next!=NULL){
            node = node->next;
        }
        while (node!=NULL){
            printf("-Node %d\n",node->data);
            node = node->prev;
        }
    }
}


/*
STACK STRUCTURE
required function
creation of newnode
joining node at head,tail and intermediate
deleting node at head,tail and intermediate
displaying node for forward and backward directions
*/
// create stack structure
//struct Stack{
//    int item[MAX_SIZE];
//    int top;
//};
//
//struct Stack stack;


struct Stack{
    int item[MAX_SIZE];
    int top;
};
//struct Stack stack_name;

void Initialize_struct(struct Stack *stack_name){
    stack_name->top =-1;
}

int isFull(struct Stack *stack_name){
     return (stack_name->top == MAX_SIZE-1);
}

int isEmpty(struct Stack *stack_name){
     return (stack_name->top == -1);
}

void push(struct Stack *stack_name,int value){
    if (isFull(stack_name)){
        printf("\nStack overflow occurs!\n");
        exit(1);
    }else{
        stack_name->item[++stack_name->top] = value;
    }
}

int pop(struct Stack *stack_name){
    if (isEmpty(stack_name)){
        printf("\nEmpty Stack!\n");
        exit(1);
    }else{
       return stack_name->item[stack_name->top--];
    }
}
int peek(struct Stack *stack_name){
    if (isEmpty(stack_name)){
        printf("\nEmpty Stack!\n");
        exit(1);
    }else{
        return stack_name->item[stack_name->top];
    }
}

void display_stack(struct Stack *stack_name){
    for (int i=0;i<=stack_name->top;i++){
        printf("Stack[%d]:%d\n",i,stack_name->item[i]);
    }

}
#endif // DATAHANDLING_H_INCLUDED
