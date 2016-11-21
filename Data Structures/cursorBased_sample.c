#include<stdio.h>
#include<conio.h>
#define max 50
typedef struct
{
	 int elem;
	 int next;
}heapspace[max];
typedef struct
{
	 heapspace h;
	 int avail;
}virtualheap;
typedef int list;
void initialize(virtualheap *vh);
void insert_end(virtualheap *vh, list *l, int x);
void initialize(virtualheap *vh)
{
	 int n = 0;
	 vh->avail = n;
	 for(; n < max - 1; n++) {
	 	vh->h[n].next=n+1;
	 }
	 vh->h[n].next = -1;
}
void insert_end(virtualheap *vh, list *l, int x)
{
	 int p, temp;
	 if(vh->avail != -1)
	 {
		  vh->h[vh->avail].elem = x;
		  temp = vh->avail;
		  vh->avail = vh->h[vh->avail].next;
		  for(p = *l; p != -1; p = vh->h[p].next);
		  vh->h[temp].next = -1;
		  if(*l == -1)
				*l = temp;
		  else
				vh->h[p].next = temp;
	 }
	 else
		  printf("No available heap\n");
}
int main(void)
{
	 virtualheap vh;
	 list l = -1;
	 int x, i;
	 char ans;
	 initialize(&vh);
	 do
	 {
		  printf("What do you want to put? \n");
		  scanf("%d", &x);
		  insert_end(&vh, &l, x);
		  printf("Do you want to continue? \n");
		  scanf (" %c", &ans);
	 }while(ans == 'Y' || ans == 'y');
	 for (i=0; i!=-1; i=vh.h[i].next) {
	 	printf ("%d ", vh.h[i].elem);
	 }
	 getch ();
	 return 0;
}
