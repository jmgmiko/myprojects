#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    int elem;
    struct cell *next;
} ctype, *SET;

void insertUnsorted (int num, SET* S);
void unionUnsorted (SET A, SET B, SET *U);
void displayList (SET S);
void freedom (SET S);

int main ()
{
    SET A=NULL;
    SET B=NULL;
    SET U=NULL;
    int choice, input;
    do {
		system ("clear");
		displayList (A);
		displayList (B);
        printf ("1-Insert an element into set A (Unsorted)\n");
        printf ("2-Insert an element into set B (Unsorted)\n");
        printf ("3-Exit\n");
        printf ("Choose an option: ");
        fflush(stdin);
        scanf ("%d", &choice);
        switch (choice) {
            case 1:
                printf ("Insert an element into set A: ");
                fflush(stdin);
                scanf ("%d", &input);
                insertUnsorted (input, &A);
                break;
            case 2:
                printf ("Insert an element into set B: ");
                fflush(stdin);
                scanf ("%d", &input);
                insertUnsorted (input, &B);
                break;
            case 3:
                printf ("Goodbye.");
                break;
            default:
                printf ("Sorry.");
        }
    } while (choice!=3);
    unionUnsorted (A, B, &U);
	displayList (U);
    freedom (U);
    freedom (A);
    freedom (B);
    return 0;
}

void insertUnsorted (int num, SET* S)
{
    SET trav, temp;
    for (trav=*S; trav!=NULL && num!=trav->elem; trav=trav->next) {}
	if (trav==NULL || num!=trav->elem) {
		temp=(SET) malloc (sizeof(ctype));
		temp->elem=num;
		temp->next=*S;
		*S=temp;
	}
}

void unionUnsorted (SET A, SET B, SET *U)
{
    SET temp;
    SET travA, travB;
    for (travA=A, travB=B; travA!=NULL && travB!=NULL; ) {
		temp=(SET) malloc (sizeof(ctype));
		if (travA->elem > travB->elem) {
			temp->elem=travA->elem;
			travA=travA->next;
		} else if (travA->elem <= travB->elem) {
			temp->elem=travB->elem;
			if (travA->elem == travB->elem) {
				travA=travA->next;
			}
			travB=travB->next;
		}
		temp->next=*U;
		*U=temp;
	}
	if (travA==NULL) {
		while (travB!=NULL) {
			temp=(SET) malloc (sizeof(ctype));
			temp->elem=travB->elem;
			travB=travB->next;
			temp->next=*U;
			*U=temp;			
		}
	} else if (travB==NULL) {
		while (travA!=NULL) {
			temp=(SET) malloc (sizeof(ctype));
			temp->elem=travA->elem;
			travA=travA->next;
			temp->next=*U;
			*U=temp;			
		}
	}
}

void displayList (SET S)
{
	SET trav;
	for (trav=S; trav!=NULL; trav=trav->next) {
		printf ("%d ", trav->elem);
	}
	printf ("\n");
}

void freedom (SET S)
{
	SET temp;
	while (S!=NULL) {
		temp=S;
		S=S->next;
		free (temp);
	}
}

