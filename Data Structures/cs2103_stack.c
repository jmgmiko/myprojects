#include <stdio.h>
#define MAX 10

typedef struct {
    char elem [MAX];
    int top;
} Stack;

typedef enum {
    TRUE, FALSE
} boolean;

void initStack (Stack *);
void insertSorted (Stack *, char);
void Push (Stack *, char);
void insertBottom (Stack *, char);
void displayElements (Stack );
void Pop (Stack *);
int Top (Stack);
boolean isFull (Stack);
boolean isEmpty (Stack);

int main ()
{
    Stack S;
	int choice;
	char data;
	initStack (&S);
    do {
        system ("clear");
        printf("1-Insert an element\n");
        printf("2-Display all elements\n");
        printf("3-Display the topmost index\n");
        printf("4-Delete an element\n");
        printf("5-Checks if the list is empty/full\n");
        printf("6-Exit\n");
        printf("Choose an option: ");
        fflush(stdin);
        scanf ("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter a character: ");
                fflush(stdin);
                scanf (" %c", &data);
                insertSorted (&S, data);
                break;
            case 2:
                displayElements (S);
                break;
            case 3:
                printf("Topmost index: %d", Top(S));
                break;
            case 4:
                Pop (&S);
                break;
            case 5:
                (isFull(S)==TRUE)?printf("The list is full."):printf("The list is not full.");
                (isEmpty(S)==TRUE)?printf("The list is empty."):printf("The list is not empty.");
                break;
            case 6:
                printf ("Bye bye.");
                break;
            default:
                printf("Sorry.");
        }
	} while (choice!=6);
    return 0;
}

void initStack (Stack *S)
{
 	 S->top=-1;
}

void insertSorted (Stack *S, char insert)
{
    if (S->top<MAX-1) {
        if (S->top==-1 || insert>S->elem[S->top]) {
            Push (S, insert);
        } else {
            insertBottom (S, insert);
        }
    }
}

void Push (Stack *S, char insert)
{
    ++S->top;
    S->elem[S->top]=insert;
}

void insertBottom (Stack *S, char insert)
{
    char temp [MAX];
    int i, j, k, l;
    for (i=S->top, j=0; i>=0 && insert<S->elem[i]; i--, j++) {
        temp [j]=S->elem[i];
    }
    j--;
    if (i==-1 || insert!=S->elem[i]) {
        i++;
        S->elem[i]=insert;
    }
    for (k=(i+1), l=j; l>=0; l--, k++) {
        S->elem[k]=temp[l];
    }
    S->top=--k;
}

void displayElements (Stack S)
{
    int x;
    for (x=S.top; x>=0; x--) {
        printf ("%c  ", S.elem[x]);
    }
}

void Pop (Stack *S)
{
    (S->top>-1)?S->top--:printf("The list is empty.");
}

int Top(Stack S)
{
    return (S.top>-1)?S.top:-1; /*If the stack is empty, the function returns -1
                                to indicate an empty stack (-1 is an invalid index.).*/
}

boolean isFull (Stack S)
{
    boolean ret;
    ret=(S.top==MAX-1)?TRUE:FALSE;
    return ret;
}

boolean isEmpty (Stack S)
{
    boolean ret;
    ret=(S.top==-1)?TRUE:FALSE;
    return ret;
}

