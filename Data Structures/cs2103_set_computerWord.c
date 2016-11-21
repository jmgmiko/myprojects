#include <stdio.h>
#include <stdlib.h>

typedef char SET;

SET member (int num, SET S);
SET insert (int num, SET S);
SET delete (int num, SET S);
SET UNION (SET A, SET B);
SET intersection (SET A, SET B);
SET difference (SET A, SET B);
void displayElements (SET S);

int main ()
{
	SET A=0;
	SET B=0;
	SET U=0;
	SET I=0;
	SET D=0;
	int choice, input;
	do {
		system ("clear");
        printf ("\n1-Insert an element into set A\n");
        printf ("2-Insert an element into set B\n");
        printf ("3-Display the elements of set A\n");
        printf ("4-Display the elements of set B\n");
        printf ("5-Check the membership of an element (set A)\n");
        printf ("6-Check the membership of an element (set B)\n");
        printf ("7-Delete an element from set A\n");
        printf ("8-Delete an element from set B\n");
        printf ("9-Display the union of sets A and B\n");
        printf ("10-Display the intersection of sets A and B\n");
        printf ("11-Display the difference of sets A and B\n");
        printf ("12-Exit\n");
        printf ("Choose an option: ");
        fflush(stdin);
        scanf ("%d", &choice);
        switch (choice) {
			case 1:
                printf ("Insert an element into set A: ");
                fflush(stdin);
                scanf ("%d", &input);
                A=insert (input, A);
                break;
            case 2:
                printf ("Insert an element into set B: ");
                fflush(stdin);
                scanf ("%d", &input);
                B=insert (input, B);
                break;
            case 3:
				displayElements (A);
                break;
            case 4:
				displayElements (B);
                break;
            case 5:
                printf ("Enter an element to find in set A: ");
                fflush(stdin);
                scanf ("%d", &input);
                (member (input, A))?printf ("%d found.", input):printf ("%d not found", input);
                break;
            case 6:
                printf ("Enter an element to find in set B: ");
                fflush(stdin);
                scanf ("%d", &input);
                (member (input, B))?printf ("%d found.", input):printf ("%d not found", input);
                break;
            case 7:
                printf ("Enter an element to delete from set A: ");
                fflush(stdin);
                scanf ("%d", &input);
                A=delete (input, A);
                break;
            case 8:
                printf ("Enter an element to delete from set B: ");
                fflush(stdin);
                scanf ("%d", &input);
                B=delete (input, B);
                break;
            case 9:
				U=UNION (A, B);
				displayElements (U);
                break;
            case 10:
				I=intersection (A, B);
				displayElements (I);
                break;
            case 11:
				D=difference (A, B);
				printf ("A-B= ");
				displayElements (D);
				D=difference (B, A);
				printf ("\nB-A= ");
				displayElements (D);
                break;                
            case 12:
                printf ("Goodbye.");
                break;
            default:
                printf ("Sorry.");
		}
	} while (choice!=12);
	return 0;
}
 
SET insert (int num, SET S)
{
	return (num>=0&&num<8)?S|(1<<num):S;
}

SET member (int num, SET S) 
{
	return (num>=0&&num<8)?S&(1<<num):0;
}

SET delete (int num, SET S)
{
	return (num>=0&&num<8)?S&~(1<<num):S;
}

SET UNION (SET A, SET B)
{
	return A|B;
}

SET intersection (SET A, SET B)
{
	return A&B;
}

SET difference (SET A, SET B)
{
	return ~A&B;
}

void displayElements (SET S)
{
	int i;
	for (i=(sizeof(int)*2)-1; i>=0; i--) {
		(S&(1<<i))?printf ("1"):printf ("0");
	}
}
