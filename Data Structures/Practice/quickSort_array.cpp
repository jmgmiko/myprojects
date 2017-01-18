#include <iostream>

using namespace std;

int partition (int arr[], int low, int high)
{
	int p=arr[high];
	
	int l=(low-1);
	int i, temp, hold;
	for (i=low; i<high; i++) {
		if (arr[i]<=p) {
			l++;
			temp=arr[i];
			arr[i]=arr[l];
			arr[l]=temp;
		} 
	}
	l+=1;
	hold=arr[high];
	arr[high]=arr[l];
	arr[l]=hold;
	return (p+1);
}

void quickSort (int arr[], int low, int high)
{
	if (low<high) {
		int pivot=partition (arr, low, high);
		quickSort (arr, low, pivot-1);
		quickSort (arr, pivot+1, high);
	}	
}

int main ()
{
	int numbers[]={3, 5, 12, 9, 1, 10, 101, 23};
	int size=sizeof(numbers)/sizeof(numbers[0]);
	int x;
	quickSort (numbers, 0, size-1);
	for (x=0; x<size; x++) {
		cout<<numbers[x]<<" "<<endl;
	}
	return 0;
}
