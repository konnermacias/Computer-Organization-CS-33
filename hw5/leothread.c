#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#define N       4

void *thread(void *vargp);
int leoNum(int n);

struct node{
        int label;
        struct node *left;
        struct node *right;
};

struct node* newNode(int label){
        struct node* node = (struct node*) malloc(sizeof(struct node));
        node->label = label;
        node->left = node->right = NULL;
        return node;
}

void treeMe(struct node* node, int k);

int main(int argc, char *argv[])
{
        int num_threads = leoNum(N)-1;
        pthread_t tid[num_threads];
        int i;
        for (i = 0; i < num_threads; i++){
                pthread_create(&tid[i], NULL, thread, &i);
                pthread_join(tid[i], NULL);
        }
        struct node* root = newNode(0);
        treeMe(root,N);
        exit(0);
}

void *thread(void *vargp)
{
        int *myid = (int*) vargp;
        //printf("Thread ID: %d\n",*myid);      
}

int leoNum(int n){
        if (n == 0 || n == 1)
                return 1;
        else
                return leoNum(n-1) + leoNum(n-2) + 1;
}

void treeMe(struct node* node, int k){
        if (k-1 <= 0){
                printf("[%i]\n",node->label);
                return;
        }else{
                int T = node->label;
                printf("(%i\n",T);
                node->left = newNode(T+1);
                node->right = newNode(T + 1 + leoNum(k-1));
                treeMe(node->left, k-1);
                treeMe(node->right, k-2);
                printf("%i)\n",T);
        }
}

