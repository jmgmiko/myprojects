#include <stdio.h>
#include <stdlib.h>
#define SIZE 30

typedef struct {
	int value;
	int leftCell;
	int rightCell;
} cellType;

typedef struct {
	cellType cell[SIZE];
	int avail;
} heap, *BST;

typedef int Tree;

void initialize (BST *B, Tree *T);
void insert (BST *B, Tree *T, int input);
void display (BST B, Tree T);
void findElem (BST B, Tree T, int look);
void deleteElem (BST *B, Tree *T, int del);

int main ()
{
	BST B;
	Tree T;
	int choice, add, del, look;
	initialize (&B, &T);
	do {
		system ("cls");
		printf ("BST (Cursor-Based)\n");
		printf ("1-Insert a value\n");
		printf ("2-Display all values\n");
		printf ("3-Find a value\n");
		printf ("4-Delete a value\n");
		printf ("5-Exit\n");
		printf ("Enter an option: ");
		fflush (stdin);
		scanf ("%d", &choice);
		switch (choice) {
			case 1:
				printf ("Enter a value to be inserted: ");
				fflush (stdin);
				scanf ("%d", &add);
				insert (&B, &T, add);
				break;
			case 2:
				display (B, T);
				break;
			case 3:
				printf ("Enter a value to find: ");
				fflush (stdin);
				scanf ("%d", &look);
				findElem (B, T, look);
				break;
			case 4:
				printf ("Enter a value to delete: ");
				fflush (stdin);
				scanf ("%d", &del);
				deleteElem (&B, &T, del);
				break;
			case 5:
				printf ("TTFN-Ta-ta for now.\n");
				break;
			default:
				printf ("Sorry.\n");
		}
		getch ();
	} while (choice!=5);
	return 0;
}

void initialize (BST *B, Tree *T)
{
	int i=0;
	int lim=SIZE-1;
	*B=(BST) malloc (sizeof (heap));
	if (*B!=NULL) {
		(*B)->avail=i;
		for (; i<lim; i++) {
			(*B)->cell[i].rightCell=(*B)->cell[i].leftCell=(i+1);
		}
		*T=(*B)->cell[i].rightCell=(*B)->cell[i].leftCell=-1;
	}
}

void insert (BST *B, Tree *T, int input)
{
	int *i, temp;
	if ((*B)->avail!=-1) {
		for (i=T; *i!=-1;) {
			i=(input>(*B)->cell[*i].value)?&(*B)->cell[*i].rightCell:&(*B)->cell[*i].leftCell;
		}
		temp=(*B)->avail;
		(*B)->avail=(*B)->cell[temp].rightCell;
		(*B)->cell[temp].value=input;
		(*B)->cell[temp].leftCell=-1;
		(*B)->cell[temp].rightCell=-1;
		*i=temp;
	}
}

void display (BST B, Tree T)
{
	if (T!=-1) {
		if (B->cell[T].leftCell!=-1) {
			display (B, B->cell[T].leftCell);
		}
		printf ("%d -> ", B->cell[T].value);
		if (B->cell[T].rightCell!=-1) {
			display (B, B->cell[T].rightCell);
		}
	}
}

void findElem (BST B, Tree T, int look) 
{
	int i;
	for (i=T; i!=-1 && look!=B->cell[i].value; ) {
		i=(look>B->cell[i].value)?B->cell[i].rightCell:B->cell[i].leftCell;
	}
	(i!=-1)?printf ("%d is found.", look):printf ("%d is not found.", look);
}

void deleteElem (BST *B, Tree *T, int del)
{
	int *i, *move;
	int temp, hold;
	for (i=T; *i!=-1 && del!=(*B)->cell[*i].value; ) {
		i=(del>(*B)->cell[*i].value)?&(*B)->cell[*i].rightCell:&(*B)->cell[*i].leftCell;
	}
	temp=*i;
	if ((*B)->cell[temp].leftCell==-1||(*B)->cell[temp].rightCell==-1) {
		*i=((*B)->cell[temp].leftCell!=-1)?(*B)->cell[temp].leftCell:(*B)->cell[temp].rightCell;
		(*B)->cell[temp].leftCell=(*B)->cell[temp].rightCell=(*B)->avail;
		(*B)->avail=temp;
	} else {
		for (move=&(*B)->cell[temp].leftCell; (*B)->cell[*move].rightCell!=-1; move=&(*B)->cell[*move].rightCell){}
		hold=*move;
		(*B)->cell[temp].value=(*B)->cell[hold].value;
		*move=((*B)->cell[hold].leftCell!=-1)?(*B)->cell[hold].leftCell:(*B)->cell[hold].rightCell;
		(*B)->cell[hold].leftCell=(*B)->cell[hold].rightCell=(*B)->avail;
		(*B)->avail=hold;
	}
}



