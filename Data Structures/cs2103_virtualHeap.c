#include <stdio.h>
#define MAX 20

typedef struct {
	char elem;
	int next;
} HeapSpace [MAX];

typedef struct {
	HeapSpace H;
	int Avail;
} VirtualHeap;

typedef int list;

void initList (VirtualHeap *);
void inputUnique (VirtualHeap *, list *, char );
void display (VirtualHeap , list );
void deleteOccur (VirtualHeap *, list *, char );
void replaceElem (VirtualHeap *, list , char , char );

int main ()
{	
	VirtualHeap VH;
	list l=-1;
	initList (&VH);
	int choice;
	char input, replace;
	do {
		system ("cls");
		printf ("1-Insert a unique character\n");
		printf ("2-Display all characters\n");
		printf ("3-Delete all occurrences\n");
		printf ("4-Replace an element\n");
		printf ("5-Exit\n");
		printf ("Select an option: ");
		fflush (stdin);
		scanf ("%d", &choice);
		switch (choice) {
			case 1:
				printf ("Enter a character you want to add: ");
				fflush (stdin);
				scanf (" %c", &input);
				inputUnique (&VH, &l, input);
				break;
			case 2:
				display (VH, l);
				break;
			case 3:
				printf ("Enter a character whose occurrence you want to delete: ");
				fflush (stdin);
				scanf (" %c", &input);
				deleteOccur (&VH, &l, input);
				break;
			case 4:
				printf ("Enter a character you want to replace: ");
				fflush (stdin);
				scanf (" %c", &replace);
				printf ("Enter a character to take its place: ");
				fflush (stdin);
				scanf (" %c", &input);
				replaceElem (&VH, l, replace, input);
				break;
			case 5:
				printf ("Goodbye.");
				break;
			default:
				printf ("Sorry.");
				break;
		}
		getch ();
	} while (choice!=5);
	return 0;
}

void initList (VirtualHeap *V)
{
	int n, lim;
	V->Avail=0;
	lim=MAX-1;
	for(n=0; n < lim; n++){
	 	V->H[n].next = n+1;
	}
	V->H[n].next = -1;
}

void inputUnique (VirtualHeap *VH, list *L, char let)
{
	int *p, temp, place;
	if (VH->Avail!=-1) {
		VH->H[VH->Avail].elem=let;
		temp=VH->Avail;
		VH->Avail=VH->H[VH->Avail].next;
		for (p=L; *p!=-1 && let>VH->H[*p].elem; p=&VH->H[*p].next){}
		/*if (*p==-1 || let!=VH->H[*p].elem) {*/
			VH->H[temp].next=*p;
			*p=temp;
		/*} else {
			VH->H[temp].elem=' ';
			VH->Avail=temp;
		}*/
	} else {
		printf ("No available heap");
	}
}

void display (VirtualHeap VH, list L)
{
	int trav;
	printf ("%d\n", VH.Avail);
	for (trav=L; trav!=-1; trav=VH.H[trav].next) {
		printf ("%c ", VH.H[trav].elem);
	}
}

void deleteOccur (VirtualHeap *VH, list *L, char del)
{
	int *p, temp, found;
	found=0; // 0-not found
	if (*L!=-1) {
		for (p=L; *p!=-1; ) {
			if (del==VH->H[*p].elem) {
				temp=*p;
				*p=VH->H[temp].next;
				VH->H[temp].elem=' ';
				VH->H[temp].next=VH->Avail;
				VH->Avail=temp;
				found=1; //1-found
			} else {
				p=&VH->H[*p].next;
			}
		}
		found?printf ("All %cs deleted", del):printf ("%c not found", del);
	} else {
		printf ("The list is empty.");
	}
}

void replaceElem (VirtualHeap *VH, list L, char out, char in)
{
	int trav, sorted, i;
	char temp;
	for (trav=L; trav!=-1 && out>VH->H[trav].elem; trav=VH->H[trav].next) {}
	if (trav!=-1 && out==VH->H[trav].elem) {
		VH->H[trav].elem=in;
	} else {
		printf ("%c not found", out);
	}
	do { //checks if the list is sorted or not
		sorted=0;
		for (i=L; VH->H[i].next!=-1; i=VH->H[i].next) {
			if (VH->H[i].elem>VH->H[VH->H[i].next].elem) {
				temp=VH->H[i].elem;
				VH->H[i].elem=VH->H[VH->H[i].next].elem;
				VH->H[VH->H[i].next].elem=temp;
				sorted=1;
			}
		}
	} while (sorted);
}
