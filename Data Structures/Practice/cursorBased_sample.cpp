#define SIZE 100
#define LIMIT 50

#include <iostream>

#include <cstdlib>
#include <cstring>
#include <conio.h>

using namespace std;

typedef struct {
	char name[LIMIT];
	float payment;
	int next;		
} Customer;

typedef struct {
	Customer *turn;
	int last;
} Line, *HeapLine;

typedef int Queue;

void initHeap (HeapLine *H, Queue *L, Queue *R) 
{
	int i;
	*H=new Line;
	if (H!=NULL) {
		(*H)->turn= new Customer [SIZE];
		if ((*H)->turn!=NULL) {
			for (i=1; i<SIZE; i++) {
				(*H)->turn[i].next=i-1;
				strcpy ((*H)->turn[i].name, "vacant");
				(*H)->turn[i].payment=0.00;
			}
			(*H)->last=i-1;
			*L=*R=-1;
		}
	}
}

void Enqueue (HeapLine *H, Queue *L, Queue *R, char name[], float amt)
{
	Queue *trav;
	Queue temp;
	int limit=(*H)->last;
	if (limit!=-1) {
		temp=limit;
		(*H)->last=(*H)->turn[temp].next;
		strcpy ((*H)->turn[temp].name, name);
		(*H)->turn[temp].payment=amt;
		(*H)->turn[temp].next=-1;
		if (*L==-1) {
			*L=temp;
		} else {
			(*H)->turn[*R].next=temp;
		}
		*R=temp;
	} else {
		cout<<"Heap is full."<<endl;
	}
}

void Display (HeapLine H, Queue L, Queue R)
{
	Queue T;
	int i;
	for (i=1, T=L; T!=-1; T=H->turn[T].next) {
		cout<<"Customer #"<<i<<": "<<H->turn[T].name<<endl;
		printf ("Payment: $%.2f", H->turn[T].payment);
		printf ("\n");
	}
	if (L==-1 && R==-1) {
		cout<<"Queue is empty"<<endl;
	}
}

void Dequeue (HeapLine *H, Queue *L, Queue *R)
{
	Queue temp;
	if (*L!=-1 && *R!=-1) {
		temp=*L;
		if (temp==*R) {
			*R=-1;
		}
		*L=(*H)->turn[temp].next;
		(*H)->turn[temp].next=(*H)->last;
		(*H)->last=temp;
	}
}

int main ()
{
	HeapLine HL;
	Queue L, R;
	int choice;
	float payment;
	char input[LIMIT];
	initHeap (&HL, &L, &R);
	do {
		system ("cls");
		cout<<"1-Enqueue"<<endl;
		cout<<"2-Customers currently in line"<<endl;
		cout<<"3-Dequeue"<<endl;
		cout<<"4-Exit"<<endl;
		cout<<"Select an option: ";
		cin>>choice;
		switch (choice) {
			case 1:
				cout<<"Enter your name: ";
				cin>>input;
				cout<<"Enter your amount for payment: ";
				cin>>payment;
				Enqueue (&HL, &L, &R, input, payment);
				break;
			case 2:
				Display (HL, L, R);
				break;
			case 3:
				Dequeue (&HL, &L, &R);
				break;
			case 4:
				cout<<"Bye-bye.";
				break;
			default:
				cout<<"Sorry.";
		}
		getch ();
	} while (choice!=4);
	delete HL->turn;
	delete HL;
	return 0;
}
