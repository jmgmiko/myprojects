#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
}*list;

typedef enum {
	TRUE, FALSE
}boolean;

void insertElement (list *, int );
void displayList (list);
boolean compareSet (list , list );
list interSets (list , list );
list uniteSets (list , list );

int main () 
{
	int choice, insert, i;
	list head=NULL, subS=NULL, inter=NULL, unity=NULL;
	do {
		system ("cls");
		printf ("1-Input an element (superset)\n");
		printf ("2-Input an element (subset)\n");
		printf ("3-Display elements (superset)\n");
		printf ("4-Display elements (subset)\n");
		printf ("5-Compare a set with its subset\n");
		printf ("6-Display its intersection\n");
		printf ("7-Display its union\n");
		printf ("8-Exit\n");
		printf ("Enter an option: ");
		fflush (stdin);
		scanf ("%d", &choice);
		switch (choice) {
			case 1:
				printf ("(Superset) Enter a number to insert: ");
				fflush (stdin);
				scanf ("%d", &insert);
				insertElement (&head, insert);
				break;
			case 2:
				printf ("(Subset) Enter a number to insert: ");
				fflush (stdin);
				scanf ("%d", &insert);
				insertElement (&subS, insert);
				break;
    		case 3:
    			displayList (head);
				break;
			case 4:
				displayList (subS);
				break;
			case 5:
				compareSet (head, subS)==TRUE?printf ("It's a subset."):printf ("It's not a subset.");
				break;
			case 6:
				inter=interSets (head, subS);
				displayList (inter);
				break;
			case 7:
				unity=uniteSets (head, subS);
				displayList (unity);
				break;
			case 8:
				printf ("Bye bye.");
				break;
			default:
				printf ("Sorry.");
		} 
		getch ();
	} while (choice!=8);
	return 0;
}

void insertElement (list *H, int num) 
{
	list *trav, temp;
	for (trav=H; *trav!=NULL && (*trav)->data<num; trav=&(*trav)->next) {}
	if (*trav==NULL || (*trav)->data!=num) {
		temp=malloc (sizeof (list));
		temp->data=num;
		temp->next=NULL;
		if (*trav!=NULL) {
		temp->next=*trav;
	}
	*trav=temp;
	}
}

void displayList (list H)
{
	if (H!=NULL) {
		printf ("%d\n", H->data);
		displayList (H->next);
	}
}

boolean compareSet (list Super, list Sub)
{
	boolean ret;
	list sB, sP;
	for (sB=Sub; sB!=NULL && sP!=NULL; sB=sB->next) {
		for (sP=Super; sP!=NULL && sB->data!=sP->data; sP=sP->next) {}
	}
	ret=(sB==NULL)?TRUE:FALSE;
	return ret;
}

list interSets (list Super, list Sub) 
{
	list interS=NULL;
	list temp, x, y, *trav;
	for (x=Sub; x!=NULL; x=x->next) {
		for (y=Super; y!=NULL && x->data!=y->data; y=y->next) {}
		if (y!=NULL) {
			for (trav=&interS; *trav!=NULL; trav=&(*trav)->next) {}
			temp=malloc (sizeof (list));
			temp->data=x->data;
			temp->next=NULL;
			*trav=temp;
		}
	}
	return interS;
}

list uniteSets (list head, list subS)
{
	list uniteS=NULL;
	list temp, i, j, *trav;
	for (i=subS; i!=NULL; i=i->next) {
		for (trav=&uniteS; *trav!=NULL ; trav=&(*trav)->next) {}
		temp=malloc (sizeof (list));
		temp->data=i->data;
		temp->next=NULL;
		*trav=temp;
	} for (j=head; j!=NULL; j=j->next) {
		for (trav=&uniteS; *trav!=NULL && (*trav)->data < j->data; trav=&(*trav)->next) {}
		if (*trav==NULL || j->data!=(*trav)->data) {
			temp=malloc (sizeof (list));
			temp->data=j->data;
			temp->next=NULL;
			if (*trav!=NULL) {
				temp->next=*trav;
			}
			*trav=temp;
		}
	}
	return uniteS;
}
