#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define SYN_SIZE 8
#define EMPTY "empty"
#define DEPARTED "departed"

typedef enum {
    FALSE, TRUE
} boolean;

typedef struct {
    char airline [100];
    char num [20];
	char dest [50];
} flightInfo;

typedef struct {
	flightInfo info;
	int next;
} flightSlot;

typedef struct Dic{
	flightSlot slot[MAX];
	flightSlot syn[SYN_SIZE];
	int avail;
} *Dictionary;

void initialize (Dictionary *D);
void displayDictionary (Dictionary D);
void populateDictionary (Dictionary D);
void insert (Dictionary D, flightInfo input);
boolean isMember (Dictionary D, char num[]);
void delete (Dictionary D, char num[]);
int hash (char num[]);

int main ()
{
	Dictionary A;
	char delNum1[]="432";
	char delNum2[]="1123";
	char delNum3[]="187";
	char delNum4[]="156";
	initialize (&A);
	displayDictionary (A);
	getchar ();
	populateDictionary (A);
	displayDictionary (A);
	getchar ();
	delete (A, delNum1);
	delete (A, delNum2);
	delete (A, delNum3);
	delete (A, delNum4);
	displayDictionary (A);
	getchar ();
    return 0;
}

void initialize (Dictionary *D) {
	int i, j;
	*D=(Dictionary) malloc (sizeof(struct Dic));
	if (*D!=NULL) {
		for (i=0; i<MAX; i++) {
			strcpy ( (*D)->slot[i].info.num, EMPTY);
			(*D)->slot[i].next=-1;
		}
		for (j=0; j<SYN_SIZE; j++) {
			(*D)->syn[j].next=(j-1);
		}
		(*D)->avail=(j-1);
	}
}

void displayDictionary (Dictionary D)
{
	int i, j;
	for (i=0; i<MAX; i++) {
		printf ("%-8d", i);
		if (strcmp (D->slot[i].info.num, EMPTY)==0||strcmp (D->slot[i].info.num, DEPARTED)==0) {
			printf ("%-10s", D->slot[i].info.num);
		} else {
			printf ("(%s flight %s)-", D->slot[i].info. airline, D->slot[i].info.num);
			printf ("%-10s", D->slot[i].info.dest);
		}
		for (j=D->slot[i].next; j!=-1; j=D->syn[j].next) {
			printf ("\n        (%s flight %s)-", D->syn[j].info. airline, D->syn[j].info.num);
			printf ("%-10s", D->syn[j].info.dest);
		}
		printf ("\n");
	}
}

void populateDictionary (Dictionary D)
{
	int const COUNT=15;
	flightInfo start[]={ {"Scandinavian Airlines", "156", "Stockholm"},
						 {"KLM", "234", "Amsterdam"},
						 {"Singapore Airlines", "5432", "Singapore"},
						 {"United Airlines", "187", "San Francisco"},
						 {"British Airways", "767", "London"},
						 {"Scandinavian Airlines", "156", "Stockholm"},
						 {"Philippine Airlines", "432", "Manila"},
						 {"Air Canada", "6793", "Vancouver"},
						 {"Iberia Airlines", "323", "Barcelona"},
						 {"Emirates", "813", "Dubai"},
						 {"Qantas", "1244", "Sydney"},
						 {"Delta Airlines", "700", "Atlanta"},
						 {"Singapore Airlines", "5432", "Singapore"},
						 {"Lufthansa", "5662", "Frankfurt"},
						 {"Air France", "6231", "Paris"}
					   };
	int i;
	for (i=0; i<COUNT; i++) {
		insert (D, start[i]);
	}
}

void insert (Dictionary D, flightInfo input) 
{
	boolean verify=isMember (D, input.num);
	int indx=hash (input.num);
	int *j, temp;
	if (verify==FALSE) {
		if (strcmp(D->slot[indx].info.num, EMPTY)==0||strcmp(D->slot[indx].info.num, DEPARTED)==0 ){
			D->slot[indx].info=input;
		} else {
			if (D->avail!=-1) {
				for (j=&D->slot[indx].next; *j!=-1 && strcmp(D->syn[*j].info.airline, input.airline)<0; j=&D->syn[*j].next) {}
				if (*j==-1 || strcmp(D->syn[*j].info.airline, input.airline)!=0) {
					temp=D->avail;
					D->avail=D->syn[temp].next;
					D->syn[temp].info=input;
					D->syn[temp].next=*j;
					*j=temp;
				}
			}
		}
	} else {
		printf ("%s flight %s is on the Dictionary.\n", input.airline, input.num);
	}
}

int hash (char num[])
{
	int total=0;
	int i;
	for (i=0; num[i]!='\0'; i++) {
		total=total+(num[i]-48);
	}
	return total%MAX;
}

boolean isMember (Dictionary D, char num[])
{
	int indx=hash(num);
	int result=FALSE;
	int j;
	if (strcmp(D->slot[indx].info.num, EMPTY)!=0 || D->slot[indx].next!=-1) {
		if (strcmp(D->slot[indx].info.num, num)!=0) {
			for (j=D->slot[indx].next; j!=-1 && strcmp(D->syn[j].info.num, num)!=0; j=D->syn[j].next) {}
			if (strcmp(D->syn[j].info.num, num)==0) {
				result=TRUE;
			}
 		} else {
			result=TRUE;
		}
	}
	return result;
}

void delete (Dictionary D, char num[])
{
	boolean verify=isMember(D, num);
	int indx=hash (num);
	int *i, temp;
	if (verify==TRUE) {
		if (strcmp(D->slot[indx].info.num, num)==0) {
			strcpy (D->slot[indx].info.num, DEPARTED);
		} else {
			for (i=&D->slot[indx].next; *i!=0 && strcmp(D->syn[*i].info.num, num)!=0; i=&D->syn[*i].next){}
			temp=*i;
			*i=D->syn[temp].next;
			D->syn[temp].next=D->avail;
			D->avail=temp;
		}
	} else {
		printf ("Flight %s is not found.\n", num);
	}
}
