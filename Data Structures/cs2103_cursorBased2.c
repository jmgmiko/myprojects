#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2 /*Number of members in a dynamically allocated array*/

typedef struct {
	char fName [30];
	char MI;
	char lName [30];
}nameType;

typedef struct {
	nameType name;	
	unsigned long idNum;
	char course [10];
	int year;
}studInfo;

typedef struct {
	studInfo *elem;
	int last;
}nodeType, *LIST;

void initializeList (LIST *);
void displayList (LIST );
void insertUnique (LIST *);
void deleteOccur (LIST *);
void replaceSurname (LIST *);
void releaseList (LIST );

int main ()
{
	LIST L=NULL;
	initializeList (&L);
	int opt;
	do {
		system ("cls");
		printf ("1-Insert student information\n2-Display all students\n3-Delete all occurences (per course)\n4-Replace a surname\n5-Exit\n");
		printf ("Enter an option: ");
		fflush (stdin);
		scanf ("%d", &opt);
		switch (opt) {
			case 1:
				insertUnique (&L);
				break;
			case 2:
				displayList (L);
				break;
			case 3:
				deleteOccur (&L);
				break;
			case 4:
				replaceSurname (&L);
				break;
			case 5:
				printf ("Bye-bye.");
				releaseList (L);
				break;
			default:
				printf ("Sorry.");	
		}
		getch ();
	} while (opt!=5);
	return 0;
}

//initializes the structure in which memory is allocated for it and the array within it
void initializeList (LIST *L)
{
	int i;
	*L=(LIST) malloc (sizeof (nodeType));
	if (*L!=NULL) {
		(*L)->elem=(studInfo *) malloc (sizeof (studInfo)*MAX);
		if ((*L)->elem!=NULL) {
			(*L)->last=-1;
		}
	}
}

//lets a user input information then, if the id num isn't on the array yet, inserts it into the sorted array 
void insertUnique (LIST *L)
{
	char fN[30], lN[30], MI, course[10];
	int year, ID, i;
	int lim=(*L)->last+1;
	printf ("Enter a student's id number: ");
	fflush (stdin);
	scanf ("%d", &ID);
	printf ("Enter a student's first name: ");
	fflush (stdin);
	gets (fN);
	printf ("Enter a student's middle initial: ");
	fflush (stdin);
	scanf (" %c", &MI);
	printf ("Enter a student's surname: ");
	fflush (stdin);
	gets (lN);
	printf ("Enter a student's course: ");
	fflush (stdin);
	gets (course);
	printf ("Enter a student's year: ");
	fflush (stdin);
	scanf ("%d", &year);
	if (lim<MAX) {
		for (i= (*L)->last; i>=0 && (*L)->elem[i].idNum>ID; i--) { //traverses array from the last
			(*L)->elem[i+1]=(*L)->elem[i];
		}
		if ((*L)->last==-1 || (ID!=(*L)->elem[i].idNum&&
		(strcmp(fN, (*L)->elem[i].name.fName)!=0
		||strcmp(lN, (*L)->elem[i].name.lName)!=0
		||MI!=(*L)->elem[i].name.MI
		||strcmp(course, (*L)->elem[i].course)!=0))) {//checks if the given record isn't found
			(*L)->elem[i+1].idNum=ID;
			strcpy ((*L)->elem[i+1].name.fName, fN);
			strcpy ((*L)->elem[i+1].name.lName, lN);
			strcpy ((*L)->elem[i+1].course, course);
			(*L)->elem[i+1].name.MI=MI;
			(*L)->elem[i+1].year=year;
			(*L)->last+=1;
		} else {
			printf ("Try again."); //error if the record to be inserted already exists
		}
	} else {
		printf ("Whoops!");
	}
}

//displays the records of students
void displayList (LIST L)
{
	int i;
	int lim=L->last+1;
	system ("cls");
	for (i=0; i<lim; i++) {
		printf ("Id: %d\n", L->elem[i].idNum);
		printf ("Name: %s, %s %c.\n", L->elem[i].name.lName, L->elem[i].name.fName, L->elem[i].name.MI);
		printf ("Course: %s\n", L->elem[i].course);
		printf ("Year: %d\n", L->elem[i].year);
	}
}

//deletes all occurrences of a record with a given course from an array
void deleteOccur (LIST *L)
{
	studInfo *temp;
	char remove [10];
	int i, k;
	int j=(*L)->last+1, find=0; //find determines whether the course is on the records(1) or not(0)
	if ((*L)->last!=-1) { //checks whether the array is empty or not
		printf ("Enter the course to delete all records related to it: ");
		fflush (stdin);
		gets (remove);
		for (i=0; i<=j; ) {
			if (strcmp(remove, (*L)->elem[i].course)==0) {
				for (k=i; k<=(*L)->last; k++) {
					(*L)->elem[k]=(*L)->elem[k+1];
				}
				(*L)->elem[k].idNum=0;
				strcpy ((*L)->elem[k].name.fName, " ");
				strcpy ((*L)->elem[k].name.lName, " ");
				strcpy ((*L)->elem[k].course, " ");
				(*L)->elem[k].name.MI=' ';
				(*L)->elem[k].year=0;
				(*L)->last=(*L)->last-1;
				find=1;
			} else {
				i++;
			}
		}
		find?printf ("All %s records deleted", remove):printf ("%s records not found", remove);
	} else {
		printf ("The array is empty.");
	}
}

//replaces a certain surname with another one, displays a message if it fails
void replaceSurname (LIST *L)
{
	int find=0, lim=(*L)->last+1; //find indicates whether the surname is found(1) or not(0)
	int i;
	char look [30], replace[30];
	if ((*L)->last!=-1) { //checks whether the array is empty or not
		printf ("Enter a surname you're looking for: ");
		fflush (stdin);
		gets (look);
		printf ("Enter a surname to replace: ");
		fflush (stdin);
		gets (replace);
		for (i=0; i<(*L)->last; i++) {
			if (strcmp (look, (*L)->elem[i].name.lName)==0) {
				strcpy ((*L)->elem[i].name.lName, replace);
				find=1;
			}
		}
		find?printf ("%s replaced", look):printf ("Surname not found");
	}	else {
		printf ("The array is empty.");
	}
}

//returns the allocated memory back to the heap
void releaseList (LIST L)
{
	free (L->elem);
	free (L);
}
