#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>
typedef struct objectTree {
	int data;
	struct objectTree *left;
	struct objectTree *right;
	int marked_bit;
}objectTree;

// typedef struct heap {
// 	int addr;
// 	int marked_bit;
// }heap;

//Free list is a linked list of all free blocks currently availabe on the heap
typedef struct freeList {
	int address;
	struct freeList* next;
}fl;

// Global Variables
// heap h[100];
// int h_free = 0;

objectTree *root = NULL;

objectTree* Create(int data) {
	objectTree* newNode = (objectTree*)malloc(sizeof(objectTree));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->marked_bit = 0;
	return newNode;
}

objectTree* Insert(objectTree* root,int data) {
	if(root == NULL) /*empty tree*/{
		root = Create(data);
		// heap_alloc(root);
		return root;
	}
	else if(data <= root->data) {
		root->left = Insert(root->left,data);
		// heap_alloc(root->left);
		return root;
	}
	else {
		root->right = Insert(root->right,data);
		// heap_alloc(root_right);
		return root;
	}
}

// void heap_alloc(objectTree obj) {
// 	h[h_free].addr = &obj;
// 	h[h_free].marked_bit = 0;
// 	h_free++;
// }

void mark(objectTree* root) {
	if(root != NULL) {
		root->marked_bit = 1;
	}
	mark(root->left);
	mark(root->right);
}

int Search(objectTree* root,int data) {
	if(root == NULL) {
		return 0;
	}
	else if(root->data == data) {
		return 1;
	}
	else if(data <= root->data) {
		return Search(root->left,data);
	}
	else {
		return Search(root->right,data);
	}
}

void disp(struct objectTree *root) {
  struct objectTree *t = root;
  if(t == NULL) {
    printf("Tree is deleted or does not exist!\n");
  }
  else {
    int f = 1, choice = -1;
    while(f == 1) 
    {
      printf("Current node is %d\n",t->data);
      printf("Status - %d\n",t->marked_bit);
      if(t->left !=NULL) {
        printf("Left: %d\t",t->left->data);
      }
      if(t->right != NULL) {
        printf("Right: %d",t->right->data);
      }
      printf("\n1. Left\n2. Right\n3. Root\n4. Delete Left node\n5. Delete Right node\n6. Mark\n0. Exit\n> ");
      scanf("%d",&choice);
      switch(choice)
      {
        case 1:
        if(t->left == NULL)
        {
          printf("Left node does not exist!\n");
        }
        else
        {
          t = t->left;
        }break;
        case 2:
        if(t->right == NULL)
        {
          printf("Right node does not exist!\n");
        }
        else
        {
          t = t->right;
        }break;
        case 3:
        t = root; break;
        case 4:
        t->left = NULL; break;
        case 5:
        t->right = NULL; break;
        case 6:
        mark(root);
        printf("Done Marking");
        break;
        case 0:
        f = 0; break;
        default:
        printf("Enter a correct choice(0-5)!\n");break;
      }
    }
  }
}

int main() {
	printf("\nEnter 1 to create a Binary Tree\n");
	printf("Enter 2 to Search for an element in the Binary tree\n");
	printf("Enter 3 to display Binary tree and delete desired node \n");
	printf("Press 4 to quit\n");
	int ch;
	int num = 0;
	scanf("%d",&ch);
	switch (ch)
	{
		case 1:
			printf("Enter -1 to stop entering numbers\n");
			while(1)
			{
				printf("Enter a number : ");
				scanf("%d",&num);
				if(num == -1)
					break;
				root=Insert(root,num);	
			}
			main();
			break;
			case 2:
				printf("Enter a number to search \n");
				scanf("%d",&num);
				if(Search(root,num) == 1) 
				printf("Found\n");
				else
				printf("Not Found\n");
				main();
			case 3:
				disp(root);
				main();
			case 4:
				exit(0);			
			break;			
		}
	return 0;	
}