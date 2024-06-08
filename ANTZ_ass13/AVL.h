#ifndef AVLSTRUCTURE_H_INCLUDED
#define AVLSTRUCTURE_H_INCLUDED



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CHECK_EXIST_VALID.h"

struct AVL_Node{
    int uid;
    char uname[20];
    char email[20];
    char passcode[20];
    char phno[20];
    double signs;
    struct AVL_Node* left;
    struct AVL_Node* right;
    int height;
    int account_state;
};

struct AVL_Record{
    char tran_time[50];
    char sender[20];
    char receiver[20];
    double trf_amount;
    struct AVL_Record* left;
    struct AVL_Record* right;
    int height;
};
//
struct AVL_Node* root = NULL;
//
struct AVL_Node* createNode(int userID,char name[20],char mail[20],char password[20],char phoneno[9],double signs,int state){
    struct AVL_Node* newNode = (struct AVL_Node*)malloc(sizeof(struct AVL_Node));
    if (newNode == NULL){
        printf("Memory Allocation Failed!\n");
        exit(1);
    }
    newNode->uid = userID;
    strcpy(newNode->uname , name);
    strcpy(newNode->email , mail);
    strcpy(newNode->passcode,password);
    strcpy(newNode->phno,phoneno);
    newNode->signs = signs;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height=1;
    newNode->account_state=state;
    return newNode;
}

int AVL_height(struct AVL_Node* Node){
    if(Node==NULL){
        return 0;
    }
    return Node->height;
}

int max_height(int a,int b){
    return (a>b)?a:b;
}

int AVL_balance(struct AVL_Node* Node){
    if (Node==NULL){
        return 0;
    }
    return AVL_height(Node->left)- AVL_height(Node->right);

}

struct AVL_Node* AVL_R_Rotate(struct AVL_Node* y){
    struct AVL_Node* x = y->left;
    struct AVL_Node* T2 = x->right ;
    x->right = y;
    y->left =T2;

    y->height = max_height(AVL_height(y->left) , AVL_height(y->right))+1;
    x->height = max_height(AVL_height(x->left) , AVL_height(x->right))+1;
//    printf("R rotation %d height & %d height\n",y->height,x->height);
    return x;
}

struct AVL_Node* AVL_L_Rotate(struct AVL_Node* y){
    struct AVL_Node* x = y->right;
    struct AVL_Node* T2 = x->left ;
    x->left = y;
    y->right =T2;

    y->height = max_height(AVL_height(y->left) , AVL_height(y->right))+1;
    x->height = max_height(AVL_height(x->left) , AVL_height(x->right))+1;

//    printf("L rotation %d height & %d height\n",y->height,x->height);
    return x;

}
struct AVL_Node* AVL_RL_Rotate(struct AVL_Node* y){
    //right rotation
    struct AVL_Node* T = y->right;
    y->right = AVL_R_Rotate(T);
   // left rotation
    struct AVL_Node* root = AVL_L_Rotate(y);

    return root;

};
struct AVL_Node* AVL_LR_Rotate(struct AVL_Node* y){
    // left rotation
    struct AVL_Node* T = y->left;
    y->left = AVL_L_Rotate(T);
    // right rotation
    struct AVL_Node*root = AVL_R_Rotate(y);
    return root;
};

struct AVL_Node* insertNode(struct AVL_Node* root,int id, char name[20],char mail[20],char password[20],char phoneno[20],double signs,int account_state){
    if (root == NULL){
       return (createNode(id,name,mail,password,phoneno,signs,account_state));
    }
    if (id<root->uid){
        root->left = insertNode(root->left,id,name,mail,password,phoneno,signs,account_state);
    }else if(id>root->uid){
        root->right = insertNode(root->right,id,name,mail,password,phoneno,signs,account_state);
    }else{
        printf("User ID Error!\n");
        return root;
    }

//    finding current node height
    root->height = max_height(AVL_height(root->left),AVL_height(root->right))+1;
//    printf("Height of node-%d : %d\n",root->uid,root->height);
    int bal_fac = AVL_balance(root);
//    printf("BF of node-%d : %d\n",root->uid,bal_fac);


    if (bal_fac==1 || bal_fac==0 || bal_fac==-1){
//        printf("No rotation takes place\n");
    }
    else if (bal_fac>1 && id<root->left->uid){
//        printf("Before rotation, root id is: %d\n",root->uid);
        root = AVL_R_Rotate(root);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }
    else if (bal_fac<-1 && id>root->right->uid){
//        printf("Before rotation, root id is: %d\n",root->uid);
        root = AVL_L_Rotate(root);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }

    else if (bal_fac>1 && id>root->left->uid){
//        printf("Before rotation, root id is: %d\n",root->uid);
        root = AVL_LR_Rotate(root);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }
    else if (bal_fac<-1 && id<root->right->uid){
//        printf("Before rotation, root id is: %d\n",root->uid);
        root = AVL_RL_Rotate(root);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }
    return root;
}
struct  AVL_Node* findInorderSuccessor(struct  AVL_Node* root){
    while (root->right != NULL){
        root = root->right;
    }
    return root;
}

struct AVL_Node* deleteNode(struct AVL_Node* root, struct AVL_Node* delNode){
    if (root==NULL){
        return root;
    }else if(delNode->uid<root->uid){
        root->left = deleteNode(root->left,delNode);
    }else if (delNode->uid>root->uid){
        root->right = deleteNode(root->right,delNode);
    }else { // delete case
        if (root->left == NULL){
            struct AVL_Node* temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL){
             struct AVL_Node* temp = root->left;
             free(root);
             return temp;
        }
         struct AVL_Node* temp = findInorderSuccessor(root->left);
         root->uid = temp->uid;
         root->left = deleteNode(root->left,temp);
    }
//    finding current node height
    root->height = max_height(AVL_height(root->left),AVL_height(root->right))+1;
//    printf("Height of node-%d : %d\n",root->uid,root->height);
    int bal_fac = AVL_balance(root);
//    printf("BF of node-%d : %d\n",root->uid,bal_fac);


    if (bal_fac==1 || bal_fac==0 || bal_fac==-1){
//        printf("No rotation takes place\n");
        return root;
    }
    else if (bal_fac>1){
//        printf("Before rotation, root id is: %d\n",root->uid);
        if (AVL_balance(root->left)<0){
            root = AVL_LR_Rotate(root);
        }else{
            root = AVL_R_Rotate(root);
        }
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
        //return root;
    }
    else if (bal_fac<-1){
//        printf("Before rotation, root id is: %d\n",root->uid);
        if (AVL_balance(root->right)>0){
            root = AVL_RL_Rotate(root);
        }else{
            root = AVL_L_Rotate(root);
        }
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
       // return root;
    }
    return root;
}

void showInorder(struct AVL_Node* root){

    if(root != NULL){
        showInorder(root->left);
        printf("%d-%s-%s-%s-%s-%lf\n",root->uid,root->uname,root->email,root->passcode,root->phno,root->signs);
        showInorder(root->right);
    }
}

struct AVL_Node* search_node(struct AVL_Node* root,int userID){

    if (root==NULL){
        printf("No user exists");
        return root;
    }
    if (userID==root->uid){
        return root;
    }else if (userID>root->uid){
        root = search_node(root->right,userID);
    }else{
        root =search_node(root->left,userID);
    }
    return root;
};

//// RECORD TREE PART
struct AVL_Record* tree = NULL;


struct AVL_Record* createRecNode(char time[50],char sender[20],char receiver[20],double amount){
    struct AVL_Record* newRecNode = (struct AVL_Record*)malloc(sizeof(struct AVL_Record));
    if (newRecNode == NULL){
        printf("Memory Allocation Failed!\n");
        exit(1);
    }

    strcpy(newRecNode->tran_time,time);
    strcpy(newRecNode->sender,sender);
    strcpy(newRecNode->receiver,receiver);
    newRecNode->trf_amount=amount;
    newRecNode->left = NULL;
    newRecNode->right = NULL;
    newRecNode->height=1;
    return newRecNode;
}
int RECAVL_height(struct AVL_Record* Node){
    if(Node==NULL){
        return 0;
    }
    return Node->height;
}

int recmax_height(int a,int b){
    return (a>b)?a:b;
}

int RECAVL_balance(struct AVL_Record* Node){
    if (Node==NULL){
        return 0;
    }
    return RECAVL_height(Node->left)- RECAVL_height(Node->right);

}

struct AVL_Record* RECAVL_R_Rotate(struct AVL_Record* y){
    struct AVL_Record* x = y->left;
    struct AVL_Record* T2 = x->right ;
    x->right = y;
    y->left =T2;

    y->height = recmax_height(RECAVL_height(y->left) , RECAVL_height(y->right))+1;
    x->height = recmax_height(RECAVL_height(x->left) , RECAVL_height(x->right))+1;
//    printf("R rotation %d height & %d height\n",y->height,x->height);
    return x;
}

struct AVL_Record* RECAVL_L_Rotate(struct AVL_Record* y){
    struct AVL_Record* x = y->right;
    struct AVL_Record* T2 = x->left ;
    x->left = y;
    y->right =T2;

    y->height = recmax_height(RECAVL_height(y->left) , RECAVL_height(y->right))+1;
    x->height = recmax_height(RECAVL_height(x->left) , RECAVL_height(x->right))+1;

//    printf("L rotation %d height & %d height\n",y->height,x->height);
    return x;

}
struct AVL_Record* RECAVL_RL_Rotate(struct AVL_Record* y){
    //right rotation
    struct AVL_Record* T = y->right;
    y->right = RECAVL_R_Rotate(T);
   // left rotation
    struct AVL_Record* root = RECAVL_L_Rotate(y);

    return root;

};
struct AVL_Record* RECAVL_LR_Rotate(struct AVL_Record* y){
    // left rotation
    struct AVL_Record* T = y->left;
    y->left = RECAVL_L_Rotate(T);
    // right rotation
    struct AVL_Record* root = RECAVL_R_Rotate(y);
    return root;
};


struct AVL_Record* insertRec_Node(struct AVL_Record* tree,char time[50],char sender[20],char receiver[20],double amount){
    if (tree == NULL){
       return (createRecNode(time,sender,receiver,amount));
    }
    if (strcmp(time,tree->tran_time)<0){
        tree->left = insertRec_Node(tree->left,time,sender,receiver,amount);
    }else if(strcmp(time,tree->tran_time)>0){
        tree->right = insertRec_Node(tree->right,time,sender,receiver,amount);
    }else{
        printf("Time Stamp Error!\n");
        return tree;
    }

//    finding current node height
    tree->height = recmax_height(RECAVL_height(tree->left),RECAVL_height(tree->right))+1;
//    printf("Height of node-%d : %d\n",root->uid,root->height);
    int bal_fac = RECAVL_balance(tree);
//    printf("BF of node-%d : %d\n",root->uid,bal_fac);


    if (bal_fac==1 || bal_fac==0 || bal_fac==-1){
//        printf("No rotation takes place\n");
    }
    else if (bal_fac>1 && strcmp(time,tree->left->tran_time)<0){
//        printf("Before rotation, root id is: %d\n",root->uid);
        tree = RECAVL_R_Rotate(tree);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }
    else if (bal_fac<-1 && strcmp(time,tree->right->tran_time)>0){
//        printf("Before rotation, root id is: %d\n",root->uid);
        tree = RECAVL_L_Rotate(tree);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }

    else if (bal_fac>1 && strcmp(time,tree->left->tran_time)>0){
//        printf("Before rotation, root id is: %d\n",root->uid);
        tree = RECAVL_LR_Rotate(tree);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }
    else if (bal_fac<-1 && strcmp(time,tree->right->tran_time)<0){
//        printf("Before rotation, root id is: %d\n",root->uid);
        tree = RECAVL_RL_Rotate(tree);
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
    }
    return tree;

};

struct AVL_Record* deleteMinNode(struct AVL_Record* tree){

    if(tree==NULL){
        return tree;
    }
    if (tree->left==NULL){
     struct AVL_Record* temp = tree->right;
     free(tree);
     return temp;
    }

    tree->left = deleteMinNode(tree->left);

//    finding current node height
    tree->height = recmax_height(RECAVL_height(tree->left),RECAVL_height(tree->right))+1;
//    printf("Height of node-%d : %d\n",root->uid,root->height);
    int bal_fac = RECAVL_balance(tree);
//    printf("BF of node-%d : %d\n",root->uid,bal_fac);


    if (bal_fac==1 || bal_fac==0 || bal_fac==-1){
//        printf("No rotation takes place\n");
        return tree;
    }
    else if (bal_fac>1){
//        printf("Before rotation, root id is: %d\n",root->uid);
        if (RECAVL_balance(tree->left)<0){
            tree = RECAVL_LR_Rotate(tree);
        }else{
            tree = RECAVL_R_Rotate(tree);
        }
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
        return tree;
    }
    else if (bal_fac<-1){
//        printf("Before rotation, root id is: %d\n",root->uid);
        if (RECAVL_balance(tree->right)>0){
            tree = RECAVL_RL_Rotate(tree);
        }else{
            tree = RECAVL_L_Rotate(tree);
        }
//        printf("After rotation, root id is: %d left node :%d  right node: %d\n",root->uid,root->left->uid,root->right->uid);
        return tree;
    }
    return tree;
}

void showRecInorder(struct AVL_Record* root){
    if(root != NULL){
        showRecInorder(root->left);
        printf("%s-%s-%s-%lf\n",root->tran_time,root->sender,root->receiver,root->trf_amount);
        showRecInorder(root->right);
    }
}


#endif // AVLSTRUCTURE_H_INCLUDED
