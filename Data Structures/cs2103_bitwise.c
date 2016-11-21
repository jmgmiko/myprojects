#include <stdio.h>

void bitPattern (unsigned int, unsigned int);

int main ()
{
    int x=22, y=11;
    bitPattern (x, y);
    return 0;
}

void bitPattern (unsigned int X, unsigned int Y)
{
    int i, A, O, XO, NX, NY, RX, LX, RY, LY;
    A=X&Y;
    O=X|Y;
    XO=X^Y;
    NX=~X;
    NY=~Y;
    RX=X>>2;
    LX=X<<2;
    RY=Y>>2;
    LY=Y<<2;
    printf("The bit pattern of %d is: ", X);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (X&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d is: ", Y);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (Y&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d & %d (%d) is: ", X, Y, A);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (A&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d | %d (%d) is: ", X, Y, O);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (O&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d ^ %d (%d) is: ", X, Y, XO);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (XO&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d & %d (%d) is: ", X, Y, A);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (A&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of ~%d (%d) is: ", X, NX);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (NX&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of ~%d (%d) is: ", Y, NY);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (NY&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d>>2 (%d) is: ", X, RX);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (RX&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d<<2 (%d) is: ", X, LX);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (LX&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d>>2 (%d) is: ", Y, RY);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (RY&(1u<<i))?printf ("1"):printf("0");
    }
    printf("\nThe bit pattern of %d<<2 (%d) is: ", Y, LY);
    for (i=(sizeof(int)*2)-1; i>=0; i--) {
        (LY&(1u<<i))?printf ("1"):printf("0");
    }
}
