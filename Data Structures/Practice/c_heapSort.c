#include <stdlib.h>
#include <stdio.h>
#define SIZE 10

typedef struct {
	int elem [SIZE];
	int last;
} Heap;

void initialize (Heap *H) 
{
	H->last=-1;
}

void heapify (Heap *H, int indx)
{
	int parent=(indx-1)/2;
	int temp;
	for (; indx!=0 && H->elem[parent]<H->elem[indx]; indx=parent, parent=(indx-1)/2) {
		temp=H->elem[indx];
		H->elem[indx]=H->elem[parent];
		H->elem[parent]=temp;
	}	
}

void insert (Heap *H, int val[])
{
	int i;
	for (i=0; i<8; i++) {
		++H->last;
		H->elem[H->last]=val[i];
		heapify (H, H->last);
	}
}

int Delete (Heap *H)
{
	int num=H->elem[0];
	H->elem[0]=H->elem[H->last];
	H->last--;
	int indx, left, right, max, temp;
	for (indx=0, left=(indx*2)+1, right=(indx*2)+2; left<=H->last || right<=H->last; left=(indx*2)+1, right=(indx*2)+2) {
		max=(H->elem[left]<=H->elem[right])?right:left;
		temp=H->elem[max];
		H->elem[max]=H->elem[indx];
		H->elem[indx]=temp;
		indx=max;
	}
	return num;
}

int *sort (Heap *H, int *size)
{
	int *sorted=NULL;
	int oldSize=H->last+1;
	int i;
	*size=oldSize;
	sorted=(int *) malloc (sizeof(int)*oldSize);
	if (sorted!=NULL) {
		for (i=oldSize-1; i>=0; i--) {
			sorted[i]=Delete (H);
		}
	}
	return sorted;
}

int main ()
{
	Heap H;
	int values []={16, 11, 8, 4, 6, 23, 10, 9}; 
	int *S=NULL;
	int i, size;
	initialize (&H);
	insert (&H, values);
	printf ("Old set: ");
	for (i=0; i<=H.last; i++) {
		printf ("%d  ", H.elem[i]);
	}
	printf ("\n");
	S=sort (&H, &size);
	printf ("Sorted set: ");
	for (i=0; i<size; i++) {
		printf ("%d  ", S[i]);
	}
	return 0;
}
