#define SIZE 9

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int E[SIZE];
	int last;
}Heap;

int heapify (int num[], int indx)
{
	
}

int *heapsort (Heap H)
{
	int *A;
	int i;
	A=(int *) malloc (SIZE*sizeof(int));
	if (A!=NULL) {
		
	}
	return A;
}

void displayArray (int arr[])
{
	int i;
	for (i=0; i<SIZE; i++) {
		printf ("%d    ", arr[i]);  	
	}
}

void initialize (Heap *H)
{
	H->last=0;
}

void heapInsert (int num[], Heap *H)
{
	int temp, parent, x;
	while (H->last<SIZE) {
		H->E[H->last]=num[H->last];
		parent=(H->last-1)/2;
		for (x=H->last, temp=H->E[x]; x>0 && temp > H->E[parent]; x=parent, parent=(x-1)/2) {
			H->E[x]=H->E[parent];
		}
		H->E[x]=temp;
		++H->last;
	}
}


int main ()
{	
	Heap H;
	int *arr;
	unsigned int S=0;
	S|=(1<<15);
	printf ("%d ", S);
	/*int numbers[]={3,5,7,1,45,2,16,87,21};
	initialize (&H);
	heapInsert (numbers, &H);
	arr=heapsort (H);
	displayArray (arr);*/
	int num=pow(2, 8);
	printf ("%d", num);
	return 0;
}
