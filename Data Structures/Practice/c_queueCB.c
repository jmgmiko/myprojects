#include <stdio.h>
#include <string.h>
#define MAX 20

typedef struct {
    char name[20];
    int num;
}personInfo;

typedef struct {
    personInfo pI;
    int next;
}personCell;

typedef struct {
    personCell *pC;
    int Avail;
}VirtualHeap;

typedef int Queue;

void initQueue (VirtualHeap *, Queue *, Queue *);
void Enqueue (VirtualHeap *, Queue *, Queue *, char *, int);
void Display (VirtualHeap, Queue, Queue);
void Dequeue (VirtualHeap *, Queue *, Queue *);

int main ()
{
    Queue F, R;
    VirtualHeap VH;
    initQueue (&VH, &F, &R);
    int choice, num;
    char name[20];
    do {
        system ("clear");
        printf ("1-Insert an element\n");
        printf ("2-Display all elements\n");
        printf ("3-Delete an element\n");
        printf ("4-Exit\n");
        printf ("Choose an option: ");
        fflush (stdin);
        scanf ("%d", &choice);
        switch (choice) {
            case 1:
                printf ("Enter a name to insert: ");
                fflush (stdin);
                scanf ("%s", &name);
                printf ("Enter its number: ");
                fflush (stdin);
                scanf ("%d", &num);
                Enqueue (&VH, &F, &R, name, num);
                break;
            case 2:
                Display (VH, F, R);
                break;
            case 3:
                Dequeue (&VH, &F, &R);
                break;
            case 4:
                printf ("Bye bye.");
                break;
            default:
                printf ("Sorry.");
        }
    } while (choice!=4);
    free (VH.pC);
    return 0;
}

void initQueue (VirtualHeap *VH, Queue *F, Queue *R)
{
    int i=0;
    int lim=MAX-1;
    VH->pC=(personCell *) malloc (sizeof (personCell)*MAX);
    if (VH->pC!=NULL) {
        VH->Avail=i;
        for ( ; i<lim; i++) {
            VH->pC[i].next=i+1;
        }
        VH->pC[i].next=-1;
        *F=-1;
        *R=-1;
    }
}

void Enqueue (VirtualHeap *VH, Queue *F, Queue *R, char *name, int num)
{
    int temp;
    if (VH->Avail!=-1) {
        temp=VH->Avail;
        VH->Avail=VH->pC[temp].next;
        strcpy (VH->pC[temp].pI.name, name);
        VH->pC[temp].pI.num=num;
        VH->pC[temp].next=-1;
        if (*F==-1) {
            *F=temp;
        } else {
            VH->pC[*R].next=temp;
        }
        *R=temp;
    }
}

void Display (VirtualHeap VH, Queue F, Queue R)
{
    int trav;
    for (trav=F; trav!=-1; trav=VH.pC[trav].next) {
        printf ("%d-%s  ", VH.pC[trav].pI.num, VH.pC[trav].pI.name);
    }
}

void Dequeue (VirtualHeap *VH, Queue *F, Queue *R)
{
    int temp;
    if (*F!=-1 && *R!=-1) {
        temp=*F;
        if (*F==*R) {
            *R=-1;
        }
        *F=VH->pC[temp].next;
        VH->pC[temp].next=VH->Avail;
        VH->Avail=temp;
    }
}


