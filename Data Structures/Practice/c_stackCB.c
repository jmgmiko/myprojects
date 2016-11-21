#include <stdio.h>
#define MAX 20

typedef struct {
    char elem;
    int next;
} heapSpace;

typedef struct {
    heapSpace *memb;
    int Avail;
} VirtualHeap;

typedef enum {
    TRUE, FALSE
} boolean;

typedef int Stack;

void initVH (VirtualHeap **, Stack *);
void Push (VirtualHeap **, Stack *, char );
void Display (VirtualHeap *, Stack );
void Pop (VirtualHeap **, Stack *);
void freedom (VirtualHeap *);

int main ()
{
    Stack S;
    VirtualHeap *VH;
    initVH (&VH, &S);
    int choice;
    char data;
    do {
        system ("clear");
        printf ("1-Insert an element\n");
        printf ("2-Display all elements\n");
        printf ("3-Delete an element\n");
        printf ("4-Is the stack full?\n");
        printf ("5-Is the stack empty?\n");
        printf ("6-Display the topmost index\n");
        printf ("7-Exit\n");
        printf ("Choose an option: ");
        fflush (stdin);
        scanf ("%d", &choice);
        switch (choice) {
            case 1:
                printf ("Enter a character to insert: ");
                fflush (stdin);
                scanf (" %c", &data);
                Push (&VH, &S, data);
                break;
            case 2:
                Display (VH, S);
                break;
            case 3:
                Pop (&VH, &S);
                break;
            case 4:
                (VH->Avail==-1)?printf("Stack is full"):printf("Stack is not full");
                break;
            case 5:
                (S==-1)?printf("Stack is empty"):printf("Stack is not empty");
                break;
            case 6:
                (S==-1)?printf("Stack is empty"):printf("Index of the latest element: %d", S);
                break;
            case 7:
                printf ("Bye bye.");
                break;
            default:
                printf ("Sorry.");
        }
    } while (choice!=7);
    freedom (VH);
    return 0;
}

void initVH (VirtualHeap **VH, Stack *S)
{
    int i=0;
    int lim=MAX-1;
    *VH=(VirtualHeap *) malloc (sizeof(VirtualHeap));
    if (*VH!=NULL) {
        (*VH)->memb=(heapSpace *) malloc (sizeof(heapSpace)*MAX);
        if ((*VH)->memb!=NULL) {
            (*VH)->Avail=i;
            for ( ; i<lim; i++) {
                (*VH)->memb[i].next=i+1;
            }
            (*VH)->memb[i].next=-1;
            *S=-1;
        }
    }
}

void Push (VirtualHeap **VH, Stack *S, char data)
{
    int temp;
    if ((*VH)->Avail!=-1) {
        temp=(*VH)->Avail;
        (*VH)->Avail=(*VH)->memb[temp].next;
        (*VH)->memb[temp].elem=data;
        (*VH)->memb[temp].next=*S;
        *S=temp;
    }
}

void Display (VirtualHeap *VH, Stack S)
{
    int trav;
    for (trav=S; trav!=-1; trav=VH->memb[trav].next) {
        printf ("%c  ", VH->memb[trav].elem);
    }
}

void Pop (VirtualHeap **VH, Stack *S)
{
    int temp;
    if (*S!=-1) {
        temp=*S;
        *S=(*VH)->memb[temp].next;
        (*VH)->memb[temp].next=(*VH)->Avail;
        (*VH)->Avail=temp;
    }
}

void freedom (VirtualHeap *VH)
{
    free (VH->memb);
    free (VH);
}

