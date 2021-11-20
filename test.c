#include <stdio.h>
#include <stdlib.h>
typedef struct test {
	int data;
	struct test *next;
}test;

test *t = (test *)malloc(sizeof(test));

int main() 
{
	test t[3];
	for(int i=0 ; i<3 ;i++)
	{
		printf("Enter a number\n");
		scanf(" %d",&t[i].data);
		t[i].address = &t[i].data;
	}
	for(int i = 0; i < 3; i++)
	{
        printf("Address of %d: %p\n",t[i].data,t[i].address);
	}
	return 0;
}
