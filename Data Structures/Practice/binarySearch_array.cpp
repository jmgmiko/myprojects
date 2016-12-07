#include <iostream>

using namespace std;

int binarySearch (int arr[], int seek, int size)
{
	int result;
	int first=0;
	int last=size-1;
	int mid=(last+first)/2;
	for ( ;first<last &&arr[mid]!=seek; mid=(last+first)/2){
		if (seek>arr[mid]) {
			++mid;
			first=mid;
		} else {
			--mid;
			last=mid;
		}
	}
	result=(arr[mid]!=seek)?0:1;
	return result;
}

int main ()
{
	int values[]={3, 5, 12, 9, 1, 10, 101, 23};
	int size=sizeof(values)/sizeof(values[0]);
	int look, result;
	cout<<"Enter a number to find: ";
	cin>>look;
	result=binarySearch (values, look, size);
	(result)?cout<<look<<" found."<<endl:cout<<look<<" not found."<<endl;
	return 0;
}
