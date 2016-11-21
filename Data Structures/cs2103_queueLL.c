#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
	char elem;
	struct cell *next;
	struct cell *prev;
} *Q;

void initQueue (Q *);
void freedom (Q , int);
void Display (Q, int);
void Dequeue (Q *, int *);
void Enqueue (Q *, char, int *);

int main ()
{
    Q head;
    int choice;
    int count=0;
    char data;
    initQueue (&head);
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
                Enqueue (&head, data, &count);
                break;
            case 2:
                Display (head, count);
                break;
            case 3:
                Dequeue (&head, &count);
                break;
            case 4:
                printf("Bye bye.");
                freedom (head, count);
                break;
            default:
                printf("Sorry.");
        }
    } while (choice!=4);
    return 0;
}

void initQueue (Q *head)
{
    *head=NULL;
}

void Enqueue (Q *head, char data, int *count)
{
    Q temp;
    temp= (Q) malloc (sizeof (Q));
    temp->elem=data;
    if (*count==0) {
        *head=temp;
        (*head)->next=*head;
        (*head)->prev=*head;

    } else {
        temp->prev=(*head)->prev;
        temp->next=*head;
        (*head)->prev->next=temp;
        (*head)->prev=temp;
    }
    ++*count;
}

void Display (Q head, int count)
{
    while (count!=0){
        printf ("%c ", head->elem);
        head=head->prev;
        count--;
    }
}

void Dequeue (Q *head, int *count)
{
    Q temp;
    if (*count>0) {
        temp=*head;
        (*head)->prev->next=(*head)->next;
        (*head)->next->prev=(*head)->prev;
        *head=(*head)->next;
        free (temp);
        --*count;
    }
}

void freedom (Q head, int count)
{
    Q temp;
    while (count!=0) {
        temp=head;
        head=head->next;
        free (temp);
        count--;
    }
}
