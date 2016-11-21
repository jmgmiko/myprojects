#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
	char elem;
	struct cell *next;
} *Stack, nodeType;

void initStack (Stack *);
void Push (Stack *, char );
void Display (Stack );
void Pop (Stack *);
void freedom (Stack );

int main()
{
    Stack S;
    int choice;
    char data;
    initStack (&S);
    do {
        system ("clear");
        printf ("1-Insert an element\n");
        printf ("2-Display all elements\n");
        printf ("3-Delete an element\n");
        printf ("4-Exit\n");
        printf ("Choose an option: ");
        fflush(stdin);
        scanf ("%d", &choice);
        switch (choice) {
            case 1:
                printf ("Enter an element to insert: ");
                fflush(stdin);
                scanf (" %c", &data);
                Push (&S, data);
                break;
            case 2:
                Display (S);
                break;
            case 3:
                Pop (&S);
                break;
            case 4:
                printf("Bye bye.");
                freedom (S);
                break;
            default:
                printf("Sorry.");
        }
    } while (choice!=4);
    return 0;
}

void initStack (Stack *S)
{
    *S=NULL;
}

void Push (Stack *S, char data)
{
    Stack temp;
    Stack trav=*S;
    temp=(Stack) malloc (sizeof(Stack));
    temp->elem=data;
    temp->next=*S;
    *S=temp;
}

void Display (Stack S)
{
    Stack trav;
    for (trav=S; trav!=NULL; trav=trav->next) {
        printf ("%c ", trav->elem);
    }
}

void Pop (Stack *S)
{
    Stack temp;
    if (*S!=NULL) {
        temp=*S;
        *S=(*S)->next;
        free (temp);
    }
}

void freedom (Stack S)
{
    Stack temp;
    while (S!=NULL) {
        temp=S;
        S=S->next;
        free (temp);
    }
}
