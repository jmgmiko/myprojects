#define SIZE 8
#define MAX 20

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char fName [MAX];
	char mName;
	char lName [MAX];
} givenName;

typedef struct {
	givenName name;
	char cellNum [SIZE];
}cellInfo;

typedef struct node {
	cellInfo cell;
	struct node *next;
} *Cell [MAX], *prisonCell;

void initializePrison (Cell C);
void firstPrison (Cell C, cellInfo prisoner);
void displayPrisoners (Cell C);
int prisonHash (char *number);

int main ()
{
	Cell C;
	initializePrison (C);
	int choice, i;
	cellInfo names[20] ={{{"Howard", 'M', "Morris"}, "44322476"},
						 {{"Sasha", 'L', "Wilson"}, "22165567"},
						 {{"Billy", 'K', "Smith"}, "16633348"},
						 {{"Gustavo", 'D', "de los Reyes"}, "12216744"},
						 {{"Warwick", 'A', "Melvien"}, "96959434"},
						 {{"Emilio", 'S', "Gonzales"}, "43223435"},
						 {{"Joe", 'G', "Shigeta"}, "89906605"},
						 {{"Arianne", 'L', "Lim"}, "22487557"},
						 {{"Farouk", 'M', "Adib"}, "33343433"},
						 {{"Jean Claude", 'E', "Varnier"}, "99696010"},
						 {{"Jim", 'E', "Wills"}, "43434220"},
						 {{"Susanna", 'H', "Wurtzmann"}, "23223292"},
						 {{"Chanad", 'E', "Patel"}, "12200010"},
						 {{"Paulo", 'G', "Cunha"}, "11233455"},
						 {{"Steven", 'R', "Meritt"}, "98839320"},
						 {{"Hannah", 'D', "Graham"}, "94800321"},
						 {{"Manuel", 'H', "Guzman"}, "65003292"},
						 {{"Roderick", 'C', "Santos"}, "85439853"},
						 {{"Jim Henderson", 'L', "Park"}, "54696045"},
						 {{"Fritz", 'K', "Warner"}, "84458032"}};
	for (i=0; i<20; i++) {
		firstPrison (C, names[i]);	
	}
	do {
		system ("cls");
		printf ("My Prison\n");
		printf ("1-Insert prisoner\n");
		printf ("2-Display all prisoners\n");
		printf ("My Prison\n");
		printf ("My Prison\n");
		printf ("5-\n");
		printf ("6-Exit\n");
		printf ("Enter an option: ");
		fflush (stdin);
		scanf ("%d", &choice);
		switch (choice) {
			case 2:
				displayPrisoners (C);
				break;
			case 6:
				printf ("Bye bye.");
				break;
			default:
				printf ("Sorry.");
		}
		getch ();
	} while (choice!=6);
	return 0;
}

void initializePrison (Cell C)
{
	int i; 
	for (i=0; i<MAX; i++) {
		C[i]=NULL;
	}
}

void firstPrison (Cell C, cellInfo prisoner)
{
	int hash=prisonHash(prisoner.cellNum);
	prisonCell *trav, temp;
	for (trav=&C[hash]; *trav!=NULL && strcmp(prisoner.name.lName, (*trav)->cell.name.lName)>0; trav=&(*trav)->next){}
	temp=(prisonCell) malloc(sizeof(struct node));
	if (temp!=NULL) {
		temp->cell=prisoner;
		temp->next=*trav;
		*trav=temp;
	}
}

void displayPrisoners (Cell C)
{
	int i;
	prisonCell trav;
	system ("cls");
	for (i=0; i<MAX; i++) {
		printf ("%d-> ", i);
		if (C[i]==NULL) {
			printf ("EMPTY");
		} else {
			for (trav=C[i]; trav!=NULL; trav=trav->next) {
				printf ("%s-> ", trav->cell.name.lName);
			}
		}
		printf ("\n");
	}
}

int prisonHash (char *number)
{
	int i;
	int sum=0;
	for (i=0; number[i]!='\0'; i++) {
		sum+=(number[i]-48);
	}
	return sum%MAX;
}
