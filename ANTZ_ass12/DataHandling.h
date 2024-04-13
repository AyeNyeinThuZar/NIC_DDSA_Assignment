#ifndef DATAHANDLING_H_INCLUDED
#define DATAHANDLING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define FRONT 0

/*
STACK STRUCTURE
required function
stack initialization
stack full_check
stack empty_check
push stack
pop stack
peek stack
display stack
*/


struct Stack{
    int item[MAX_SIZE];
    int top;
};
//struct Stack stack_name;

void Initialize_struct(struct Stack *stack_name){
    stack_name->top =-1;
}

int isFull_stack(struct Stack *stack_name){
     return (stack_name->top == MAX_SIZE-1);
}

int isEmpty_stack(struct Stack *stack_name){
     return (stack_name->top == -1);
}

void push(struct Stack *stack_name,int value){
    if (isFull_stack(stack_name)){
        printf("\nStack overflow occurs!\n");
        exit(1);
    }else{
        stack_name->item[++stack_name->top] = value;
    }
}

int pop(struct Stack *stack_name){
    if (isEmpty_stack(stack_name)){
        printf("\nEmpty Stack!\n");
        exit(1);
    }else{
       return stack_name->item[stack_name->top--];
    }
}
int peek(struct Stack *stack_name){
    if (isEmpty_stack(stack_name)){
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

/*
Queue STRUCTURE
required function
queue initialization
queue full_check
queue empty_check
enqueue queue
dequeue queue
re_queue queue
display queue
*/

struct Queue{
    int item[MAX_SIZE];
    int front;
    int rear;
    int Q_size;
};

void initialize_queue(struct Queue* queue){
    queue->front = FRONT;
    queue->rear =-1;
    queue->Q_size =0;
}

int isFull_queue(struct Queue* queue){
    return (queue->Q_size==MAX_SIZE);
}
int isEmpty_queue(struct Queue* queue){
    return (queue->Q_size==0);
 }

void enqueue(struct Queue* queue,int data){
    if (isFull_queue(queue)){
        printf("Queue is Full\n");
    }else{
        queue->rear++;
        queue->item[queue->rear]=data;
        queue->Q_size++;
    }
}

void re_queue(struct Queue* queue){
    queue->rear = queue->Q_size - queue->rear;
    for (int i=0;i<queue->Q_size-1;i++){
        queue->item[queue->rear-1] = queue->item[queue->rear];
        queue->rear++;
    }
    queue->Q_size--;
    queue->rear = queue->Q_size-1;
}

int dequeue(struct Queue* queue){
    if (isEmpty_queue(queue)){
        printf("Queue is Empty.\n");
    }else{
        int deque_data = queue->item[queue->front];
        re_queue(queue);
        return deque_data;
    }
}



void show_Qdata(struct Queue* queue){
    printf("Queue size is : %d--Queue data are:",queue->Q_size);
    for (int i=0;i<queue->Q_size;i++){
        printf(" %d-",queue->item[i]);
    }printf("\n");
}
/*
LINKED LIST STRUCTURE
required function
creation of newnode
joining node at head,tail and intermediate
deleting node at head,tail and intermediate
displaying node for forward and backward directions
*/

//create linked list structure
struct LLNode{
    int data;
    struct LLNode* next;
    struct LLNode* prev;
};


struct LLNode* createNewnode(int newData){
    struct LLNode* newNode = (struct LLNode*)malloc(sizeof(struct LLNode));
    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// create new node and link
void Add_Node(struct LLNode** node,int key,int mode){
// mode=1 => add as begin node, mode=2 => add as last node, moce=3 => add as middle node
    printf("\nAdd Node:%d",key);
    struct LLNode* temp;
    temp = *node;
    if (mode==1){
        struct LLNode* start = createNewnode(key);
        if (temp==NULL){
             temp= start;
        }else{
            start->next=temp;
            temp->prev= start;
            temp= start;
        }
    }
    else if (mode==2){
        struct LLNode* last = createNewnode(key);
        struct LLNode* temp_1;
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
        struct LLNode* middle = createNewnode(key);
        struct LLNode* temp_1;
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

void deleteNode(struct LLNode** node,int key){
    printf("\nDelete Node:%d",key);
    struct LLNode* temp=*node;
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

void showNodedata(struct LLNode* node,char ch){
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
LLSTACK
create LLstack structure
required function
-stack initialization
-push
-pop
-peek
-check empty stack

*/

// create LLstack structure
struct LLStack{
    struct LLNode* top;
};


//LLstack initialization
void initialize_stack(struct LLStack* stack){
    stack->top = NULL;
}

int isEmptyLLStack(struct LLStack* stack){
    return (stack->top == NULL);

}

void LLpush(struct LLStack* stack, int data){
    struct LLNode* newNode = (struct LLNode*)malloc(sizeof(struct LLNode));
    if (newNode == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int LLpop(struct LLStack* stack){
    if(isEmptyLLStack(stack)){
        printf("Stack underflow!\n");
        return -1;
    }
    else{
        struct LLNode* temp = stack->top;
        int data = temp->data;
        stack->top = temp->next;
        free(temp);
        return data;
    }
}

int LLpeek(struct LLStack* stack){
    if(isEmptyLLStack(stack)){
        printf("Stack is Empty!\n");
        return -1;
    }
    else{
        int data = stack->top->data;
        return data;
    }
}

void showLLStack(struct LLStack* stack){
    struct LLNode* temp =  stack->top;
    while (!(isEmptyLLStack(stack))){
        printf("%d-",stack->top->data) ;
        stack->top = stack->top->next;
    }
    printf("\n");
    stack->top = temp;
}


/*
Tree Data structure
create Tree structure
required function
-create tree node
-insert tree node
-delete tree node
-find inorder successor
-display inorder node

*/
struct TNode{
    int data;
    struct TNode* left;
    struct TNode* right;
};

struct TNode* createTNode(int data){
    struct TNode* newTNode = (struct TNode*)malloc(sizeof(struct TNode));
    if (newTNode == NULL){
        printf("Memory Allocation Failed!\n");
        exit(1);
    }
    newTNode->data = data;
    newTNode->left = NULL;
    newTNode->right = NULL;
    return newTNode;
}
struct TNode* insertTNode(struct TNode* root, int data){
    if (root == NULL){
       root = createTNode(data);
    }else if (data<root->data){
        root->left = insertTNode(root->left,data);
    }else{
        root->right = insertTNode(root->right,data);
    }
    return root;
}

struct TNode* findInorderSuccessor(struct TNode* root){
//    while (root->left != NULL){
//        root = root->left;
//    }
//    return root;

    while (root->right != NULL){
        root = root->right;
    }
    return root;
}


struct TNode* deleteTNode(struct TNode* root, int data){
    if (root==NULL){
        return root;
    }else if(data<root->data){
        root->left = deleteTNode(root->left,data);
    }else if (data>root->data){
        root->right = deleteTNode(root->right,data);
    }else{
        if (root->left == NULL){
            struct TNode* temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL){
             struct TNode* temp = root->left;
             free(root);
             return temp;
        }
//         struct TNode* temp = findInorderSuccessor(root->right); // finding inorder successor
         struct TNode* temp = findInorderSuccessor(root->left);
         root->data = temp->data;
//         root->right = deleteTNode(root->right,temp->data);
         root->left = deleteTNode(root->left,temp->data);
    }
}
void showInorder(struct TNode* root){

    if(root != NULL){
        showInorder(root->left);
        printf("%d-",root->data);
        showInorder(root->right);
    }

}
#endif // DATAHANDLING_H_INCLUDED
