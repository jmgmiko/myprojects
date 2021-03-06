#define MAX 15

#include <stdio.h>
#include <stdlib.h>

void displayArr (int arr[], int size)
{
	int x;
	for (x=0; x<=size; x++) {
		printf ("%d, ",arr[x]);
	}	
	printf ("\n");
}

int *heapifyMin (int num[])
{
	int *sorted;
	int i, j, parent, left, right, temp, small, hold;
	sorted = (int *) malloc (MAX*sizeof(int));
	if (sorted!=NULL) {
		for (i=0; i<MAX; i++) {
			temp=num[i];
			for (j=i, parent=(j-1)/2; j!=0 && temp<sorted[parent];) {
				sorted[j]=sorted[parent];
				j=parent;
				parent=(j-1)/2;
			}
			sorted[j]=temp;
		}	
	}
	displayArr(sorted, MAX-1);
	getch ();
	return sorted;	
}

int *heapifyMax (int num[])
{
	int *sorted;
	int i, j, parent, left, right, temp, small, hold;
	sorted = (int *) malloc (MAX*sizeof(int));
	if (sorted!=NULL) {
		for (i=0; i<MAX; i++) {
			temp=num[i];
			for (j=i, parent=(j-1)/2; j!=0 && temp>sorted[parent];) {
				sorted[j]=sorted[parent];
				j=parent;
				parent=(j-1)/2;
			}
			sorted[j]=temp;
		}	
	}
	displayArr (sorted, MAX-1);
	getch ();
	return sorted;	
}

void sortMin (int sorted[])
{
	int temp, i, j, small, right, left, hold;
	for (i=MAX-1; i>=1; i--) {
			small=0;
			temp=sorted[i];
			sorted[i]=sorted[small];
			sorted[small]=temp;			
			do {
				j=small;
				left=j*2+1;
				right=j*2+2;
				if (left<i && sorted[j]>sorted[left]) {
					small=left;
				} if (right<i && sorted[small]>sorted[right]) {
					small=right;
				}
				if (small!=j) {
					hold=sorted[j];
					sorted[j]=sorted[small];
					sorted[small]=hold;	
				}
			} while (small!=j);
	}	
}

void sortMax (int sorted[])
{
	int temp, i, j, big, right, left, hold;
	for (i=MAX-1; i>=1; i--) {
			big=0;
			temp=sorted[i];
			sorted[i]=sorted[big];
			sorted[big]=temp;			
			do {
				j=big;
				left=j*2+1;
				right=j*2+2;
				if (left<i && sorted[j]<sorted[left]) {
					big=left;
				} if (right<i && sorted[big]<sorted[right]) {
					big=right;
				}
				if (big!=j) {
					hold=sorted[j];
					sorted[j]=sorted[big];
					sorted[big]=hold;	
				}
			} while (big!=j);
	}	
}

int main ()
{
	int numbers [] = {4, 54, 1, 9, 21,
					  34, 2, 39, 10, 109,
					  11, 203, 1222, 19, 22};
	int *min, *max;
	int x;
	printf ("Old array: \n");
	displayArr (numbers, MAX-1);
	min=heapifyMin (numbers);
	sortMin (min);
	printf ("Sorted array (descending order): ");
	for (x=0; x<MAX; x++) {
		printf ("%d ", min[x]);
	}
	printf ("\n");
	getch();
	system ("cls");
	printf ("Old array: \n");
	displayArr (numbers, MAX-1);
	max=heapifyMax (numbers);
	sortMax (max);
	printf ("Sorted array (ascending order): ");
	for (x=0; x<MAX; x++) {
		printf ("%d ", max[x]);
	}
	free (min);
	free (max);
	getch ();
	return 0;
}
