#include <stdio.h>
#include <stdlib.h>

typedef struct factor{
	int num;
	struct factor *next;
	struct factor *prev;
}*factorTree;

void insertValue (int , factorTree *);
factorTree findValue (int , factorTree );

int main ()
{
	factorTree root=NULL;
	factorTree find;
	insertValue (40, &root);
	find=findValue (40, root);
	printf ("%d", find->num);
	getch ();
	return 0;
}

void insertValue (int value, factorTree *root)
{
	factorTree *trav;
	for (trav=root; *trav!=NULL && (*trav)->num%value==0; ) {
		trav=(value>(*trav)->num)?&(*trav)->next:&(*trav)->prev;
	}	
	*trav=malloc (sizeof(factorTree));
	(*trav)->num=value;
	(*trav)->prev=(*trav)->next=NULL;
}

factorTree findValue (int value, factorTree root)
{
	factorTree trav;
	for (trav=root; trav!=NULL && value!=trav->num; )
	{
		trav=(value>trav->num)?trav->next:trav->prev;
	}
	return trav;
}
