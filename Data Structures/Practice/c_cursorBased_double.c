#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
	char name [20];
	int num;
} cellType;

typedef struct {
	cellType CT;
	int next;
	int prev;
} HeapSpace[MAX];

typedef struct {
	HeapSpace HP;
	int avail;
	int last;
} VirtualHeap;

typedef int head;

void initVH (VirtualHeap *VH, head *H);
void Enqueue (char *name, int num, VirtualHeap *VH, head *H);
void Dequeue (VirtualHeap *VH, head *H);

int main ()
{
	VirtualHeap VH;
	head H;
	initVH (&VH, &H);
	int choice, num;
	char name [20];
	do {
		system ("clear");
		printf ("1-Insert elements\n");
		printf ("2-Display elements\n");
		printf ("3-Remove elements\n");
		printf ("4-Exit\n");
		printf ("Choose an option: ");
		fflush (stdin);
		scanf ("%d", &choice);
		switch (choice) {
			case 1:
				printf ("Enter a person's name: ");
				fflush (stdin);
				scanf ("%s", name);
				printf ("Enter %s's favorite number: ", name);
				fflush (stdin);
				scanf ("%d", &num);	
				Enqueue (name, num, &VH, &H);
				break;
			case 2:
				break;
			case 3:
				Dequeue (&VH, &H);
				break;
			case 4:
				printf ("Bye-bye.");
				break;
			default:
				printf ("Sorry.");
		}
	} while (choice!=4);
	return 0;
}

void initVH (VirtualHeap *VH, head *H)
{
	int i, j;
	VH->avail=0;
	VH->last=MAX-1;
	for (j=VH->last, i=VH->avail; i<MAX; i++, j=(j+1)%MAX) {
		VH->HP[i].next=(i+1)%MAX;
		VH->HP[i].prev=j;
	}
	*H=-1;
}

void Enqueue (char *name, int num, VirtualHeap *VH, head *H)
{
	int temp;
	int lim=MAX-1;
	if (VH->avail!=-1) {
		temp=VH->avail;
		if (VH->avail==lim) {
			VH->avail=-1;
		} else {
			VH->avail=VH->HP[temp].next;
		}
		VH->HP[temp].CT.num=num;
		strcpy (VH->HP[temp].CT.name, name);
		if (*H==-1) {
			VH->HP[temp].prev=VH->HP[temp].next=temp;
			*H=temp;
		} else {
			VH->HP[VH->HP[*H].prev].next=temp;
			VH->HP[temp].prev=VH->HP[*H].prev;
			VH->HP[*H].prev=temp;
			VH->HP[temp].next=*H;
		}
	}
}

void Dequeue (VirtualHeap *VH, head *H)
{
	int temp;
	if (*H!=-1) {
		temp=*H;
		if (VH->HP[temp].next==VH->HP[temp].next) {
			*H=-1;
		} else {
			*H=VH->HP[temp].next;
			VH->HP[VH->HP[temp].prev].next=VH->HP[temp].next;
			VH->HP[VH->HP[temp].next].prev=VH->HP[temp].prev;
			VH->HP[temp].next=VH->avail;
			VH->HP[temp].prev=VH->last;
			VH->avail=temp;
			VH->last=temp;
		}
	}
}

