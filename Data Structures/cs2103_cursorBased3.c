#include <stdio.h>
#define MAX 100

typedef struct {
    char elem;
    int next;
} nodeType, heapSpace [MAX];

typedef struct {
    heapSpace H;
    int Avail;
} VirtualHeap;

typedef enum {
    TRUE, FALSE
} boolean;

typedef int Set;

void initialize (VirtualHeap *);
void insertSorted (VirtualHeap *, Set *, char);
void displayElements(VirtualHeap, Set, Set);
boolean isSubset (VirtualHeap, Set, Set);
Set setDifference (VirtualHeap *, Set, Set);

int main ()
{
    VirtualHeap VH;
    Set A=-1, B=-1;
    Set C;
    initialize (&VH);
    int choice, cTrav;
    char data;
    do {
        system ("clear");
        printf("1-Insert an element (Set A)\n");
        printf("2-Insert an element (Set B)\n");
        printf("3-Display all elements\n");
        printf("4-Delete an element\n");
        printf("5-Check if set A is a subset of set B\n");
        printf("6-Displaying the set difference of sets A and B\n");
        printf("7-Exit\n");
        printf("Choose an option: ");
        fflush(stdin);
        scanf ("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter a character into Set A: ");
                fflush(stdin);
                scanf (" %c", &data);
                insertSorted (&VH, &A, data);
                break;
            case 2:
                printf("Enter a character into Set B: ");
                fflush(stdin);
                scanf (" %c", &data);
                insertSorted (&VH, &B, data);
                break;
            case 3:
                displayElements (VH, A, B);
                break;
            case 4:
                break;
            case 5:
                isSubset(VH, A, B)==TRUE?printf("A is a subset of B."):printf("A is not a subset of B.");
                break;
            case 6:
                C=setDifference (&VH, A, B);
                printf ("The set difference of A and B: ");
                for (cTrav=C; cTrav!=-1; cTrav=VH.H[cTrav].next) {
                    printf ("%c ", VH.H[cTrav].elem);
                }
                break;
            case 7:
                printf("Bye bye.");
                break;
            default:
                printf ("Sorry.");
        }
    } while (choice != 7);
    return 0;
}

void initialize (VirtualHeap *VH)
{
    int i;
    VH->Avail=0;
    for (i=0; i<MAX-1; i++) {
        VH->H[i].next=i+1;
    }
    VH->H[i].next=-1;
}

void insertSorted (VirtualHeap *VH, Set *S, char insert)
{
    int *trav, temp;
    if (VH->Avail>-1) {
        for (trav=S; *trav!=-1 && insert>VH->H[*trav].elem; trav=&VH->H[*trav].next) {}
        if (*trav==-1 || insert!=VH->H[*trav].elem) {
            VH->H[VH->Avail].elem=insert;
            temp=VH->Avail;
            VH->Avail=VH->H[temp].next;
            VH->H[temp].next=*trav;
            *trav=temp;
        }
    }
}

void displayElements (VirtualHeap VH, Set A, Set B)
{
    int a, b;
    printf ("Set B: ");
    for (b=B; b!=-1; b=VH.H[b].next) {
        printf ("%c ", VH.H[b].elem);
    }
    printf ("Set A: ");
    for (a=A; a!=-1; a=VH.H[a].next) {
        printf ("%c ", VH.H[a].elem);
    }
}

boolean isSubset (VirtualHeap VH, Set A, Set B)
{
    boolean ret;
    int x, y;
    for (x=A, y=B; x!=-1 && y!=-1 && VH.H[x].elem>=VH.H[y].elem; ) {
        if (VH.H[x].elem>VH.H[y].elem) {
            y=VH.H[y].next;
        } else {
            x=VH.H[x].next;
        }
    }
    ret=(x!=-1)?FALSE:TRUE;
    return ret;
}

Set setDifference(VirtualHeap *VH, Set A, Set B)
{
    Set N=-1; //holds the head index of the set difference
    int x, y, temp, prev;
    for (x=A, y=B; y!=-1 && x!=-1 ; ) {
        if (VH->H[x].elem<VH->H[y].elem) {
            VH->H[VH->Avail].elem=VH->H[x].elem;
            temp=VH->Avail;
            VH->Avail=VH->H[temp].next;
            VH->H[temp].next=-1;
            if (N==-1) {
                N=temp;
            } else {
                VH->H[prev].next=temp;
            }
            prev=temp;
            x=VH->H[x].next;
        } else if (VH->H[x].elem>VH->H[y].elem) {
            y=VH->H[y].next;
        } else {
            x=VH->H[x].next;
            y=VH->H[y].next;
        }
    }
    if (y==-1) {
        while (x!=-1) {
            VH->H[VH->Avail].elem=VH->H[x].elem;
            temp=VH->Avail;
            VH->Avail=VH->H[temp].next;
            VH->H[temp].next=-1;
            if (N==-1) {
                N=temp;
            } else {
                VH->H[prev].next=temp;
            }
            prev=temp;
            x=VH->H[x].next;
        }
    }
    return N;
}
