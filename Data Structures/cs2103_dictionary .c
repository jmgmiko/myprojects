#define EMPTY "EMPTY"
#define DELETED "DELETED"
#define SIZE 20

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    	char elem[20];
    	int link;
}elemType[SIZE];

typedef struct {
    	elemType E;
    	int Avail;
}Dictionary;

void initialize (Dictionary *D);
void insert (Dictionary *D, char input[20]);
int hash (char input [20]);
void display (Dictionary D);
int member (Dictionary D, char input [20]);
int Delete (Dictionary *D, char input[20]);

int main ()
{
	Dictionary D;
	int choice;
	char input [20];
	initialize (&D);
	do {
		system ("clear");
		printf ("1-Insert an element\n");
		printf ("2-Display all elements\n");
		printf ("3-Verify element's membership\n");
		printf ("4-Delete an element\n");
		printf ("5-Exit\n");
		printf ("Select an option: ");
		fflush (stdin);
		scanf ("%d", &choice);
		switch (choice) {
			case 1:
				printf ("Enter a string to insert: ");
				fflush (stdin);
				scanf ("%s", input);
				insert (&D, input);
				break;
			case 2:
				display (D);
				break;
			case 3:
				printf ("Enter a string to find: ");
				fflush (stdin);
				scanf ("%s", input);
				member (D, input)!=0?printf ("Found."):printf ("Not found");
				break;
			case 4:
				printf ("Enter a string to insert: ");
				fflush (stdin);
				scanf ("%s", input);
				Delete (&D, input)!=0?printf ("Deleted."):printf ("Not deleted");;
				break;
			case 5:
				printf ("Goodbye.");
				break;
			default:
				printf ("Sorry.");
		}
	} while (choice!=5);
	return 0;
}

void initialize (Dictionary *D)
{
	int i;
	int lim=SIZE-1;
	D->Avail=SIZE/2;
	for (i=0; i<lim; i++) {
		if (i<D->Avail) {
			strcpy (D->E[i].elem, EMPTY);
			D->E[i].link=-1;
		} else {
			strcpy (D->E[i].elem, "");
			D->E[i].link=i+1;			
		}
	}
	strcpy (D->E[i].elem, "");
	D->E[i].link=-1;
}

void display (Dictionary D)
{
	int i;
	for (i=0; i<SIZE; i++) {
		printf ("Element [%d] = %s ", i, D.E[i].elem);
	}
}

void insert (Dictionary *D, char input[20])
{
	int temp;
	int indx=hash(input);
	if (strcmp(D->E[indx].elem, EMPTY)==0 || strcmp(D->E[indx].elem, DELETED)==0) {
		strcpy(D->E[indx].elem, input);
	} else {
		if (D->Avail>-1) {
			temp=D->Avail;
			D->Avail=D->E[temp].link;
			D->E[temp].link=D->E[indx].link;
			strcpy(D->E[temp].elem, input);
			D->E[indx].link=temp;
		}
	}
}

int member (Dictionary D, char input [20])
{
	int indx=hash(input);
	while (indx!=-1 && strcmp (D.E[indx].elem, input)!=0) {
		indx=D.E[indx].link;
	}
	return (strcmp (D.E[indx].elem, input)==0)?1:0;  //1 if found, 0 otherwise
}

int Delete (Dictionary *D, char input[20])
{
	int indx=hash(input);
	int *trav;
	int temp;
	for (trav=&indx; *trav!=-1 && strcmp (D->E[*trav].elem, input)!=0; trav=&D->E[*trav].link) {}
	if (*trav!=-1 && strcmp (D->E[*trav].elem, input)==0) {
		temp=*trav;
		if (temp==indx) {
			strcpy (D->E[temp].elem, DELETED);
		} else {
			*trav=D->E[temp].link;
			strcpy (D->E[temp].elem, "");
			D->E[temp].link=D->Avail;
			D->Avail=temp;
		}
		return 1; //1 if deleted
	} else {
		return 0; //0 otherwise
	}
}

int hash (char input [20])
{
	return toupper(input[0])%(SIZE/2);
}
