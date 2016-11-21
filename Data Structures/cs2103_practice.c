/*******************************************************************************
 * CS/IT 126 Machine Problem 2 : Dictionary implementing Open and Closed Hashing.                                       *
 * *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OPEN_SIZE 26
#define CLOSE_SIZE 53

typedef enum {
  	EMPTY, DELETED, OCCUPIED
}statusType;    

typedef enum {
	TRUE, FALSE
}boolean;

/******************************************************************************
 * Data Structure Definition: Open and Closed Hashing Implementations         *
 ******************************************************************************/

typedef struct { 
   	char FName[24];    /* firstname */
   	char LName[16];    /* lastname */
   	char  MI;          /* middle initial */ 
}nameType; 

typedef struct {
   	char IDen[9];     /* 8-digit ID Number which uniquely identifies the student record */
   	nameType name; 
   	char course[8]; 
   	char year;         /* used as 1-byte integer */ 
   	char gender;       /* F - female, M-male */
}studRec; 
 
typedef struct node {
  	studRec stud;
  	struct node *next;  
}*studPtr;
     
typedef struct {
   	studPtr ptr;    
   	statusType status;    
}closeNode;                 /* closed hash table node */ 

typedef struct {
	studPtr ptr;
	int count;            /*  holds the number of elements in the each group */
}openNode;

typedef struct Dic {
  openNode openHT[OPEN_SIZE];      /* open Hashing */     
  closeNode closeHT[CLOSE_SIZE];   /* Closed Hashing */   
  int closeHashCount;              /* holds the number of elements in the close hash table */
}*Dictionary;

typedef struct  {
	studRec data[CLOSE_SIZE];
	int last;                    /* index of last element */
} dataList;                     /* Array implementation of list */

/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
int openHash(char lastname[]);
int closeHash(char ID[]);
dataList getData();
void displayHashValues(dataList data);

void initDictionary(Dictionary *D); 
char * getClosedHashStatus(Dictionary D, int ndx);
void displayOpenHashDic(Dictionary D);
void displayClosedHashDic(Dictionary D);
void displayDictionary(Dictionary D);

boolean isMember(Dictionary D, char ID[]);
void insertDictionary(studRec stud, Dictionary D);
void populateDictionary(Dictionary D);

boolean deleteMemID(Dictionary D, char ID[]);
void deleteIdManager(Dictionary D, char ID[]);

boolean deleteUniqueName(Dictionary D, char LN[]);
void deleteUniqueNameManager(Dictionary D, char LN[]);

/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *   4)  Uncomment or copy the print statement in each PROBLEM#  if the task is     *
 *       completed.                                                                 *
 ***********************************************************************************/
 int main( ) 
 {	
 
    Dictionary A=NULL;
    dataList L;
    char *deleteID_01 = "12104029";
    char *deleteID_02 = "13101821"; 
    char *deleteID_03 = "13101820";
    char *lname_01 = "Baguio";
    char *lname_02 = "Ang";  
    
   
  
/*---------------------------------------------------------------------------------
 * 	Problem #1 ::  Display the ID, Complete name, and the Open and Closed Hash    *
 *                 values of each student record in one row.  Call function      *
 *                 displayHashValues().                                           * 
 *--------------------------------------------------------------------------------*/
	 printf("\n\n\nProblem #1:: ");
	 displayHashValues (L);
 
 
  
/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  Displays an initially empty dictionary. It shows the  contents  *
 *                 of  both open and closed hash tables                           * 
 *--------------------------------------------------------------------------------*/ 
	printf("\n\n\nProblem #2::");
	initDictionary (&A);
	displayDictionary(A);
 
 
/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  Populate and Display the dictionary by calling the             * 
 *                 displayDictionary().                  *
 *--------------------------------------------------------------------------------*/
	printf("\n\n\nProblem #3:: ");
	populateDictionary(A);
	displayDictionary(A);

 
/*---------------------------------------------------------------------------------
 * 	Problem #4 ::  Call deleteManager 3 times passing deleteID_01, deleteID_02,   *
 *                 and deleteID_03.  Check if the records are deleted by calling  *
 *                 displayDictionary(A);                                          *
 *--------------------------------------------------------------------------------*/	
	system ("clear");
	printf("\n\n\nProblem #4:: \n");                                                
	deleteIdManager(A, deleteID_01);
	deleteIdManager(A, deleteID_02);
	deleteIdManager(A, deleteID_03);
	getchar();
    displayDictionary(A); 
	     
 
/*---------------------------------------------------------------------------------
 * 	Problem #5 ::  Call deleteUniqueManager 2 times passing lname_01 and lname_02. *
 *                 Check if the records are deleted by calling displayDictionary().*
 *---------------------------------------------------------------------------------*/		
	system ("clear");
	printf("\n\n\nProblem #5:: \n");     
	deleteUniqueNameManager(A, lname_01);
    deleteUniqueNameManager(A, lname_02);
    getchar();
    displayDictionary(A);
	
	getchar();
	return 0;
}



/************************************************************
 *  Problem 1 Function Definitions                          *
 ************************************************************/

int openHash(char lastname[])
{
 	return toupper(lastname[0])-'A';
}

int closeHash(char ID[])
{
 	int num=(atoi(ID)%10000)/10;
 	return (num*num)%CLOSE_SIZE;
}

dataList getData()
{
	dataList L;
	int const DATA_COUNT = 15;
	studRec data[] = { 	{"12104029", {"Mary Grace", "Tan", 'A'}, "BSCS", 4, 'F'},
                    	{"14100686", {"John Joseph", "Mendoza", 'B'}, "BSCS", 2, 'M'},
						{"13101813", {"Bernardina", "Velasco", 'C'}, "BSCS", 3, 'F'},
						{"14101125", {"Faith Therese", "Flores", 'D'}, "BSCS", 2, 'F'},
						{"15101848", {"Ryan Christian", "Mercado", 'E'}, "BSCS", 1, 'M'},
						{"15104179", {"Simon Peter", "Amolo", 'F'}, "BSIT", 1, 'M'},
						{"15103188", {"Mikee", "Seno", 'G'}, "BSIT", 1, 'F'},
						{"14104110", {"Tom Christian", "Fernandez", 'H'}, "BSIT", 2, 'M'},
						{"13101845", {"Janine Angela", "Ang", 'I'}, "BSIT", 3, 'F'},
						{"12102385", {"Hans Christian", "Anderson", 'J'}, "BSIT", 4, 'M'},
						{"15102424", {"Albert John", "Baguio", 'K'}, "BSICT", 1, 'M'},
						{"14101125", {"Maria Sonia", "Gaviola", 'L'}, "BSCS", 2, 'F'},
						{"12107777", {"Antonette Marie", "Lee", 'M'}, "BSICT", 4, 'F'},
						{"13101820", {"Juan", "Zozobrano", 'N'}, "BSCS", 3, 'F'},
						{"15101824", {"Josephine", "Baguio", 'O'}, "BSICT", 1, 'M'},
				   };
	
	/* Write the necessary code fragment in order for this function to work correctly. */  
	int i;
	for (i=0; i<DATA_COUNT; i++) {
		strcpy (L.data[i].IDen, data[i].IDen);
		strcpy (L.data[i].name.FName, data[i].name.FName);
		strcpy (L.data[i].name.LName, data[i].name.LName);
		strcpy (L.data[i].course, data[i].course);
		L.data[i].name.MI=data[i].name.MI;
		L.data[i].gender=data[i].gender;
		L.data[i].year=data[i].year;
	}
	L.last=(i-1);
	return L;			
				
}


void displayHashValues(dataList L)
{
	/* variable declaration here */
	int i, open, closed;
	char MI[2], name[15][50];
	system("clear");
	printf("\n\n%s", "Displaying Open and Closed Hash Values");
	printf("\n--------------------------------------\n");
	printf("\n%-10s","ID");
	printf("%-30s","Name");
	printf("%-15s","Open HValues");
	printf("%-15s","Closed HValues");
 
  	printf("\n");  
 
/*--------------------------------------------------------------------------------
  * Put the necessary code fragment here                                *
  *--------------------------------------------------------------------------------*/
	L=getData();
    for (i=0; i<=L.last; i++) {
		open=openHash (L.data[i].name.LName);
		closed=closeHash (L.data[i].IDen);
		MI[0]=L.data[i].name.MI;
		MI[1]='.';
		strcpy (name[i], L.data[i].name.LName);
		strcat (name[i], ", ");
		strcat (name[i], L.data[i].name.FName);
		strcat (name[i], " ");
		strcat (name[i], MI);
		printf ("%-10s%-30s", L.data[i].IDen, name[i]);
		printf ("%-14d %-15d\n", open, closed);
	}
    printf("\n\nPress any key to continue...  ");
    getchar();
}


/************************************************************
 *  Problem 2 Function Definitions                           *
 ************************************************************/
 void displayDictionary(Dictionary D)
{
	displayOpenHashDic(D);
	displayClosedHashDic(D);
}

void initDictionary (Dictionary *D) 
{
	int i;
	*D=(Dictionary) malloc (sizeof(struct Dic));
	if (*D!=NULL) {
		for (i=0; i<OPEN_SIZE; i++) {
			(*D)->openHT[i].ptr=NULL;
			(*D)->openHT[i].count=0;
		}
		for (i=0; i<CLOSE_SIZE; i++) {
			(*D)->closeHT[i].ptr=NULL;
			(*D)->closeHT[i].status=EMPTY;
		}
		(*D)->closeHashCount=0;
	}
}

char * getClosedHashStatus(Dictionary D, int ndx)
{
	char *stat=NULL;
	stat=(char *)malloc(sizeof(char)*20);
	if (stat!=NULL) {
		switch (D->closeHT[ndx].status){
			case EMPTY:
				strcpy (stat, "EMPTY");
				break;
			case DELETED:
				strcpy (stat, "DELETED");
				break;
			case OCCUPIED:
				strcpy (stat, "OCCUPIED");
				break;	
		}
	}
	return stat;
}

void displayOpenHashDic(Dictionary D)
{
	int i;
	studPtr trav;
	system("clear");
	printf ("\nDisplaying Open Hash Table\n");
	printf ("--------------------------\n\n");
	for (i=0; i<OPEN_SIZE; i++) {
		printf ("Group %2d, Count %2d : : ", i, D->openHT[i].count);
		if (D->openHT[i].ptr==NULL) {
			printf ("NULL");
		} else {
			for (trav=D->openHT[i].ptr; trav!=NULL; trav=trav->next) {
				printf ("%-15s", trav->stud.name.LName);
			}
		}
		printf ("\n");
	}
	printf("\n\nPress any key to continue...  ");
	getchar();
}

void displayClosedHashDic(Dictionary D)
{
	int i;
	char status[10];
	system("clear");
	printf ("\nDisplaying Closed Hash Table\n");
	printf ("----------------------------\n\n");
	for (i=0; i<CLOSE_SIZE; i++) {
		strcpy (status, getClosedHashStatus(D, i));
		printf ("Index %3d : : ", i);
		if (strcmp (status, "EMPTY")==0) {
			printf ("EMPTY\n");
		} else if (strcmp(status, "DELETED")==0) {
			printf ("DELETED\n");
		} else {
			printf ("OCCUPIED  %s  [%s]\n", D->closeHT[i].ptr->stud.IDen, D->closeHT[i].ptr->stud.name.LName);
		}
	}
	printf("\n\nPress any key to continue...  ");
	getchar();
}

/************************************************************
 *  Problem 3 Function Definitions                           *
 ************************************************************/
void populateDictionary(Dictionary D)
{
	dataList List = getData();
	int i;
	for (i=0; i<=List.last; i++) {
		insertDictionary (List.data[i], D);
	}
	getchar();
}

void insertDictionary(studRec stud, Dictionary D)
{
	int open=openHash(stud.name.LName);
	int closed=closeHash(stud.IDen);
	int move;
	studPtr *trav, temp;
	boolean verify = isMember (D, stud.IDen);
	if (verify==FALSE) {
		temp=(studPtr) malloc (sizeof(struct node));
		if (temp!=NULL) {
			strcpy(temp->stud.name.FName, stud.name.FName);
			strcpy(temp->stud.name.LName, stud.name.LName);
			strcpy(temp->stud.IDen, stud.IDen);
			strcpy(temp->stud.course, stud.course);
			temp->stud.year=stud.year;
			temp->stud.name.MI=stud.name.MI;
			temp->stud.gender=stud.gender;
			for (move=closed; D->closeHashCount<CLOSE_SIZE && D->closeHT[move].status==OCCUPIED; move=(move+1)%CLOSE_SIZE) {}
			if (D->closeHashCount<CLOSE_SIZE && D->closeHT[move].status!=OCCUPIED) {
				temp->next=NULL;
				D->closeHT[move].ptr=temp;
				D->closeHT[move].status=OCCUPIED;
				D->closeHashCount++;
			}
			for (trav=&D->openHT[open].ptr; *trav!=NULL && strcmp(stud.name.LName, (*trav)->stud.name.LName)>0; trav=&(*trav)->next) {}
			if (*trav==NULL || strcmp(stud.name.LName, (*trav)->stud.name.LName)<=0) {
				temp->next=*trav;
				*trav=temp;
				D->openHT[open].count++;
			}
		}
	} else {
		printf ("\n%s record owned by %s is on the Dictionary.\n", stud.IDen, stud.name.LName);
	}
}

boolean isMember(Dictionary D, char ID[])
{
	int move;
	boolean ret;
	for (move=closeHash(ID); D->closeHT[move].status==OCCUPIED && strcmp (ID, D->closeHT[move].ptr->stud.IDen)!=0; move=(move+1)%CLOSE_SIZE) {}
	ret=(D->closeHT[move].status==OCCUPIED && strcmp (ID, D->closeHT[move].ptr->stud.IDen)==0)?TRUE:FALSE;
	return ret;
}


/************************************************************
 *  Problem 4 Function Definition                           *
 ************************************************************/
void deleteIdManager(Dictionary D, char ID[])
{
	 boolean result=deleteMemID(D, ID);
	 if (result==TRUE){
		 printf ("Record with ID# %s is DELETED\n", ID);
	 } else {
		 printf ("Record with ID# %s does not exist\n", ID);
     }
}

boolean deleteMemID(Dictionary D, char ID[])
{
	boolean verify=isMember(D, ID);
	boolean ret=FALSE;
	int open, find;
	studPtr *trav, temp;
	if (verify==TRUE) {
		for (find=closeHash(ID); strcmp(D->closeHT[find].ptr->stud.IDen, ID)!=0; find=(find+1)%CLOSE_SIZE) {}
		open=openHash(D->closeHT[find].ptr->stud.name.LName);
		for (trav=&D->openHT[open].ptr; *trav!=NULL && strcmp(ID, (*trav)->stud.IDen)!=0; trav=&(*trav)->next) {}
		if (*trav!=NULL && strcmp(ID, (*trav)->stud.IDen)==0) {
			temp=*trav;
			*trav=temp->next;
			D->openHT[open].count--;
			temp=D->closeHT[find].ptr;
			D->closeHT[find].ptr=temp->next;
			free (temp);
			D->closeHT[find].status=DELETED;
			D->closeHashCount--;
		}
		ret=TRUE;
	}
	return ret;
}
/************************************************************
 *  Problem 5 Function Definition                           *
 ************************************************************/
void deleteUniqueNameManager(Dictionary D, char LN[])
{
	boolean result=deleteUniqueName(D, LN);
	if (result==TRUE) {
		printf ("%s Record is DELETED.\n", LN);
	} else {
		printf ("%s Record does NOT exist or not unique.\n", LN);
	}
}

boolean deleteUniqueName(Dictionary D, char LN[])
{
	int open =openHash(LN);
	int closed;
	boolean verify=FALSE;
	studPtr *trav, temp, tempC, prev;
	for (trav=&D->openHT[open].ptr, prev=*trav; *trav!=NULL && strcmp (LN, (*trav)->stud.name.LName)!=0; trav=&(*trav)->next){
		prev=*trav;
	}
	if (*trav!=NULL &&  strcmp ((*trav)->stud.name.LName, prev->stud.name.LName)!=0) {
		temp=*trav;
		for (closed=closeHash(temp->stud.IDen); strcmp(D->closeHT[closed].ptr->stud.IDen, temp->stud.IDen)!=0; 
			closed=(closed+1)%CLOSE_SIZE) {}
		*trav=temp->next;
		free (temp);
		D->openHT[open].count--;
		tempC=D->closeHT[closed].ptr;
		D->closeHT[closed].ptr=tempC->next;
		free (tempC);
		D->closeHT[closed].status=DELETED;
		D->closeHashCount--;
		verify=TRUE;
	}
	return verify;
}

