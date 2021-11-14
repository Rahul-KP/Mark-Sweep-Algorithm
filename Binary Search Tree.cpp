#include<stdio.h>
#include<stdlib.h>
struct BstNode
{
	int data;
	BstNode *left;
	BstNode *right;
};

// Global Variable
int num;

BstNode* Create(int data)
{
	BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}
BstNode* Insert(BstNode* root,int data)
{
	if(root == NULL) // empty tree
	{
		root = Create(data);
		return root;
	}
	else if(data <= root->data)
	{
		root->left = Insert(root->left,data);
		return root;
	}
	else
	{
		root->right = Insert(root->right,data);
		return root;
	}
}
bool Search(BstNode* root,int data)
{
	if(root == NULL)
	{
		return false;
	}
	else if(root->data == data)
	{
		return true;
	}
	else if(data <= root->data)
	{
		return Search(root->left,data);
	}
	else
	{
		return Search(root->right,data);
	}
}

void disp(struct BstNode *root)
{
  struct BstNode *t = root;
  if(t == NULL)
  {
    printf("Tree is deleted or does not exist!\n");
  }
  else
  {
    int f = 1, e = -1;
    while(f == 1)
    {
      printf("Current node is %d\n",t->data);
      if(t->left !=NULL)
      {
        printf("Left: %d\t",t->left->data);
      }
      if(t->right != NULL)
      {
        printf("Right: %d",t->right->data);
      }
      printf("\n1. Left\n2. Right\n3. Root\n4. Delete Left node\n5. Delete Right node\n0. Exit\n> ");
      scanf("%d",&e);
      switch(e)
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
        case 0:
        f = 0; break;
        default:
        printf("Enter a correct choice(0-3)!\n");break;
      }
    }
  }
}

void inorder(struct BstNode*root)
{
	if(root==NULL)
	{
		return;
	}
	inorder(root->left);
	printf("%d , ",root->data);
	inorder(root->right);
}

void preorder(struct BstNode *root)
{
	if(root==NULL)
	{
		return;
	}
	printf("%d , ",root->data);
	preorder(root->left);
	preorder(root->right);
}

void postorder(struct BstNode *root)
{
	if(root==NULL)
	{
		return;
	}
	postorder(root->left);
	postorder(root->right);
	printf("%d , ",root->data);
}

BstNode *root = NULL;
int main()
{	
	printf("\nEnter 1 to create a Binary Tree\n");
	printf("Enter 2 to Search for an element in the Binary tree\n");
	printf("Enter 3 to display Binary tree and delete desired node \n");
	printf("Enter 4 to display Inorder traversal\n");
	printf("Enter 5 to display Preorder traversal\n");
	printf("Enter 6 to display Postorder traversal\n");
	printf("Press 7 to quit\n");
	int ch;
	scanf("%d",&ch);
	switch (ch)
	{
		case 1:
			printf("Enter -1 to stop entering numbers\n");
			do
			{
				printf("Enter a number : ");
				scanf("%d",&num);
				root=Insert(root,num);	
			}while(num != -1 );
			main();
			break;
			case 2:
				printf("Enter a number to search \n");
				scanf("%d",&num);
				if(Search(root,num) == true) 
				printf("Found\n");
				else
				printf("Not Found\n");
				main();
			case 3:
				disp(root);
				main();
			case 4:
				inorder(root);
				main();
			case 5:
				preorder(root);
				main();
			case 6:
				postorder(root);
				main();
			case 7:
				exit(0);			
			break;			
		}
	return 0;	
}
