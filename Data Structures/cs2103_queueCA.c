#include <stdio.h>
#define MAX 10

typedef struct cell {
	char elem [MAX];
	int front;
	int rear;
} Q;

void initQueue(Q *);
void Enqueue (Q *, char);
void Display (Q);
void Dequeue (Q *);

int main ()
{
    Q queue;
    int choice;
    char data;
    initQueue(&queue);
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
                Enqueue (&queue, data);
                break;
            case 2:
                Display (queue);
                break;
            case 3:
                Dequeue (&queue);
                break;
            case 4:
                printf("Bye bye.");
                break;
            default:
                printf("Sorry.");
        }
    } while (choice!=4);
    return 0;
}

void initQueue(Q *queue)
{
    queue->front=-1;
    queue->rear=-1;
}

void Enqueue (Q *queue, char data)
{
    if (((queue->rear+2)%MAX)!=queue->front) {
        queue->rear=(queue->rear+1)%MAX;
        queue->elem[queue->rear]=data;
        if (queue->front==-1) {
            queue->front=0;
        }
    }
}

void Display (Q queue)
{
    int i;
    int lim=(queue.rear+1)%MAX;
    for (i=queue.front; i!=lim; i=(i+1)%MAX) {
        printf ("%c ", queue.elem[i]);
    }
}

void Dequeue (Q *queue)
{
    if (queue->front!=-1) {
        if (queue->front==queue->rear) {
            queue->front=-1;
            queue->rear=-1;
        } else {
            queue->front=(queue->front+1)%MAX;
        }
    }
}
