#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct node {
	int data;
	struct node *next;
} *list;

void insertElement (list *, int);
void displayList (list);
int deleteFirst (list *, int );
void deleteOccur (list *, int );
int compareSets (list , list );
void replaceValue (list *, int , int);

int main () 
{
	list head=NULL, second=NULL;
	int num, choice, out, outOcc, replace, find, delMessage, compMess;
	do {
		system ("cls");
		printf ("1-Input an element\n");
		printf ("2-Display elements\n");
		printf ("3-Remove an element\n");
		printf ("4-Remove the occurence of an element\n");
		printf ("5-Replace an element\n");
		printf ("6-Compare a list\n");
		printf ("7-Exit\n");
		printf ("Enter an option: ");
		fflush (stdin);
		scanf ("%d", &choice);
		switch (choice) {
			case 1:
				printf ("(First set) Enter a number to add: ");
				fflush (stdin);
				scanf ("%d", &num);
				insertElement (&head, num);
				printf ("(Second set) Enter a number to add: ");
				fflush (stdin);
				scanf ("%d", &num);
				insertElement (&second, num);
				break;
    		case 2:
    			displayList (head);
				break;
			case 3:
				if (head!=NULL) {
					printf ("Enter a number to remove: ");
					fflush (stdin);
					scanf ("%d", &out);
					delMessage=deleteFirst (&head, out);
					delMessage==0?printf ("Number not found"):printf ("%d deleted", delMessage);
				} else {
					printf ("List is empty");
				}
				break;
			case 4:
				if (head!=NULL) {
					printf ("Enter a number to remove: ");
					fflush (stdin);
					scanf ("%d", &outOcc);
					deleteOccur (&head, outOcc);
				} else {
					printf ("List is empty");
				}
				break;
			case 5:
				printf ("Enter a number you're looking for: ");
				fflush (stdin);
				scanf ("%d", &find);
				printf ("Enter a number to replace %d: ", find);
				fflush (stdin);
				scanf ("%d", &replace);
				replaceValue (&head, find, replace);
				break;
			case 6:
				compMess=compareSets (head, second);
				compMess?printf ("Both sets are equal."):printf("They are not equal.");
				break;
			case 7:
				printf ("Bye bye.");
				break;
			default:
				printf ("Sorry.");
		} 
		getch ();
	} while (choice!=7);
	return 0;
}

/*This function inserts a number into a linked list which is later sorted.
Before that process, this function scans the linked list to check if the number which is to be inserted exists.
Once the given number is found on the list, an error message is displayed.*/
void insertElement (list *H, int insert)
{
	list *trav, temp;
	for (trav=H; *trav!=NULL && (*trav)->data<insert; trav=&(*trav)->next) {}
	if (*trav==NULL || (*trav)->data!=insert) {
		temp=malloc (sizeof (list));
		temp->data=insert;
		temp->next=NULL;
		if (*trav!=NULL) {
		temp->next=*trav;
	}
	*trav=temp;
	}
}

void displayList (list H)
{
	list trav;
	for (trav=H; trav!=NULL; trav=trav->next) {
		printf ("%d\n", trav->data);
	}
}

/* This function deletes only the first occurrence of a given element. 
If it fails, 0 is returned to display an error message (to let the program keep on running).
Otherwise, the number deleted is returned.*/
int deleteFirst (list *H, int num) 
{	
	int deleted;
	list temp, trav, prev;
	for (trav=*H; trav!=NULL && num!=trav->data; trav=trav->next) {
		prev=trav;
	}
	if (trav!=NULL) {
		deleted=trav->data;
		temp=trav;
		if (trav==*H){
			*H=trav->next;
		}	else {
			prev->next=trav->next;
		}
		free (temp);
	}	else {
		deleted=0;
	}
	return deleted;
}

/*This function deletes all occurrences of the given number.
There is a variable that determines the function's success.
1 is assigned to it once the sought value is found on the list, otherwise 0 (which is its initial value).
An error message comes out once 0 is assigned to that variable at the end of the for loop.*/
void deleteOccur (list *H, int num) 
{
	list *trav, temp;
	int stat=0;
	for (trav=H; *trav!=NULL; trav= &(*trav)->next) {
		if ((*trav)->data==num) {
			temp=*trav;
			*trav=temp->next;
			free (temp);
			stat=1;
		}
	}    
	stat?printf ("All %d values successfully removed", num):printf ("%d not found", num);                                                                                                                                                       
}

/*This function compares a set containing unique values with another set containing unique values.
If both of them are equal, 1 is returned.
Otherwise, it's 0.*/
int compareSets (list One, list Two) 
{
	int equal;
	list travOne, travTwo;
	for (travOne=One; travOne!=NULL && travTwo!=NULL; travOne=travOne->next) {
		for (travTwo=Two; travTwo!=NULL && travOne->data!=travTwo->data; travTwo=travTwo->next ) {}
	}
	equal=travTwo!=NULL?1:0;
	return equal;
}

/*This function looks for any member of the list equal to the given value and replaces it with another value.
But when the value this function is looking for is not on the list, there comes an error.
There is a variable that determines the success of this operation which is initially set to 0.
1 is assigned to it once the sought value is found on the list.*/
void replaceValue (list *H, int x, int y)
{
	int success=0;
	list trav;
	for (trav=*H; trav!=NULL; trav=trav->next) {
		if (trav->data==x){
			trav->data=y;
			success=1;
		}
	}
	success?printf ("%d is successfully replaced by %d.", x, y):printf ("%d not found", x);
}
