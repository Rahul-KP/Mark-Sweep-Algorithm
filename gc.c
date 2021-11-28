#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>
typedef struct objectTree {
	int data;
	struct objectTree *left;
	struct objectTree *right;
}objectTree;

//Free list is a linked list of all unreachable memory blocks currently availabe on the heap
typedef struct freeList {
	struct freeList* next;
	objectTree *address;
}freeList;

freeList *r = NULL;

objectTree *root = NULL;

objectTree* Create(int data) {
	objectTree* newNode = (objectTree*)malloc(sizeof(objectTree));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

objectTree* Insert(objectTree* root,int data) {
	if(root == NULL) /*empty tree*/{
		root = Create(data);
		return root;
	}
	else if(data <= root->data) {
		root->left = Insert(root->left,data);
		return root;
	}
	else {
		root->right = Insert(root->right,data);
		return root;
	}
}

void insert_freeList(objectTree* deleted) {
	if (r == NULL) {
		r = (freeList*)malloc(sizeof(freeList));
		r->next = NULL;
		r->address = deleted;
	}
	else {
		freeList *head = r;
		while(r->next != NULL) {
			r = r->next; 
		}
		freeList *temp = (freeList*)malloc(sizeof(freeList));
		temp->next = NULL;
		temp->address = deleted;
		r->next = temp;
		r = head;
	}
}

void delete(objectTree* deleted) {
	if(deleted != NULL) {
		insert_freeList(deleted);
		delete(deleted->left);
		delete(deleted->right);
		deleted = NULL;
	}
}

void display_garbage()
{
	printf("Addresses lost\n");
	freeList *head = r;
	while(r->next != NULL) {
		printf("Address of %d : %p \n",r->address->data,r->address);
		r = r->next;
	}
	printf("Address of %d : %p \n",r->address->data,r->address);
	r = head;
}

void free_memory(freeList *head) {
	
		if(head->next != NULL) {
		free_memory(head->next);
	}
	free(head->address);
	free(head);
	printf("Memory freed\n");
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
      if(t->left !=NULL) {
        printf("Left: %d\t",t->left->data);
      }
      if(t->right != NULL) {
        printf("Right: %d",t->right->data);
      }
      printf("\n1. Left\n2. Right\n3. Root\n4. Delete Left node\n5. Delete Right node\n6. Display Garbage\n7. Free Memory\n0. Exit\n> ");
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
        delete(t->left);
        t->left = NULL; break;
        case 5:
        delete(t->right);
        t->right = NULL; break;
        case 6:
        display_garbage(); break;
        case 7:
        free_memory(r); break;
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