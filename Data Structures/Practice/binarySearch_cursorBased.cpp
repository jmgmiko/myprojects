#define SIZE 50
#define MAX 100

#include <iostream>

#include <cstring>

using namespace std;

typedef struct {
	char name [SIZE];
	int next;
	int prev;	
} CellType;

typedef struct {
	CellType cell [MAX];
	int avail; 	
} Heap, *HeapPtr;

typedef int Tree;

void initHeap (HeapPtr *H, Tree *T)
{
	int i=0, limit=MAX-1;
	*H=new Heap;
	if (H!=NULL) {
		*T=i;
		for (; i<limit; i++) {
			strcpy ((*H)->cell[i].name, "");
			(*H)->cell[i].prev=(*H)->cell[i].next=i+1;
		}
		strcpy ((*H)->cell[i].name, "");
		(*H)->cell[i].prev=(*H)->cell[i].next=-1;
	}		
}

void Insert (HeapPtr *H, Tree *T, char name[])
{
	int temp;
	temp=(*H)->avail;
	(*H)->avail=(*H)->cell[temp].next;
		
}

int main ()
{
	Tree T;
	HeapPtr H;
	int choice;
	char input [SIZE];
	initHeap (&H, &T);
	do {
		system ("cls");
		cout<<"Cursor-Based Binary Search Tree"<<endl;
		cout<<"1-Input a name"<<endl;
		cout<<"2-Display all names"<<endl;
		cout<<"3-Search a name"<<endl;
		cout<<"4-Delete a name"<<endl;
		cout<<"5-Exit"<<endl;
		cout<<"Input an option number. ";		
		cin>>choice;
		switch (choice) {
			case 1:
				cout<<"Input a name: ";
				cin>>input;
				Insert (&H, &T, input);
				break;
			case 2:
				break;
			case 5:
				cout<<"Bye-bye!"<<endl;
				break;
			default:
				cout<<"Sorry."<<endl;
		}
	} while (choice!=5);
	delete H;
	return 0;
}
