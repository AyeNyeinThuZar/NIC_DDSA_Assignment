#include<stdio.h>
#include<stdlib.h>


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

void showNodedata(struct Node* node);
void showback_Nodedata(struct Node* node);
void Add_Node(struct Node** node,int key,int mode);
void deleteNode(struct Node** node,int key);

int main (){
    struct Node* head=NULL;
    // join appending node
    Add_Node(&head,6,2);
    Add_Node(&head,7,2);
    Add_Node(&head,9,2);
    Add_Node(&head,10,2);

    // join leading node
    Add_Node(&head,5,1);
    Add_Node(&head,4,1);
    Add_Node(&head,2,1);
    Add_Node(&head,1,1);

    //join intermediate node
    Add_Node(&head,8,3);
    Add_Node(&head,3,3);


    deleteNode(&head,1);
    showNodedata(head);
    showback_Nodedata(head);

    deleteNode(&head,3);
    showNodedata(head);
    showback_Nodedata(head);

    deleteNode(&head,10);
    showNodedata(head);
    showback_Nodedata(head);

    return 0;
}

void showNodedata(struct Node* node){
    printf("Forward Display Node:\n");
    while (node!=NULL){
        printf("-Node is Node %d\n",node->data);
        node = node->next;
    }
}

void showback_Nodedata(struct Node* node){
    // go to the last node
    printf("\nBackward Display Node:\n");
    while (node->next!=NULL){
        node = node->next;
    }
    while (node!=NULL){
        printf("-Node is Node %d\n",node->data);
        node = node->prev;
    }
}
// create new node and link
void Add_Node(struct Node** node,int key,int mode){
// mode=1 => set as begin node
// mode=2 => set as last node
// moce=3 => set as middle node
    struct Node* temp;
    temp = *node;
    if (mode==1){
        struct Node* start = createNewnode(key);
        if (temp==NULL){
            temp = start;
        }else{
            start->next=temp;
            start->next->prev= start;
            temp = start;
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
    printf("\nAfter adding Node:%d\n",key);
    showNodedata(temp);
    showback_Nodedata(temp);
}

void deleteNode(struct Node** node,int key){

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
    }printf("\nAfter deleting Node %d\n",key);
}
