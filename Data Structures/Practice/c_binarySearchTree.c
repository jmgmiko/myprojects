#include <stdio.h>
#include <stdlib.h>
#define MAX 12

typedef struct node {
	int elem;
	struct node *RC;
	struct node *LC;	
} *BST;

void initialize (BST *B)
{
	*B=NULL;	
}

void insert (int val, BST *B)
{
	BST *trav=B;
	for (trav=B; *trav!=NULL; ) {
		trav=(val>(*trav)->elem)?&(*trav)->RC:&(*trav)->LC;
	}
	//if (*trav==NULL) {
		*trav=(BST) malloc (sizeof(struct node));
		(*trav)->elem=val;
		(*trav)->RC=NULL;
		(*trav)->LC=NULL;
	/*} else if (val>(*trav)->elem) {
		insert (val, &(*trav)->RC);
	} else  {
		insert (val, &(*trav)->LC);
	}*/
}

void display (BST B) 
{
	if (B->LC!=NULL) {
		display (B->LC);
	}
	printf ("%d - ", B->elem);
	if (B->RC!=NULL) {
		display (B->RC);
	}
}

int main ()
{
	BST B;
	int set[MAX]={5, 3, 8, 6, 10, 1, 4, 9, 12, 11, 2, 7};
	int i;
	initialize (&B);
	for (i=0; i<MAX; i++) {
		insert (set[i], &B);
	}
	display (B);
	return 0;
}
