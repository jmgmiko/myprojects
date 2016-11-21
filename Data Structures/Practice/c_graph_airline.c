/*This program has one of the applications of the graph theory-transport networks.
  The type of transport that is used in this program is a plane.
  So, the establishment involved is an airline company.*/
  
#define SIZE 50
#define SENTINEL INT_MAX

typedef struct {
	int flightNum;
	int hours;	
} **Airline, *AirlineCol, airlineInfo;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initializeAirline (Airline A, int places);

int main ()
{
	Airline A;
	int places, i;
	printf ("Enter the number of destinations: ");
	scanf ("%d", &places);
	initializeAirline (A, places);
	for (i=0; i<places; i++) {
		printf ("%d", A[i][0].flightNum);
	}
	return 0;
}

void initializeAirline (Airline A, int places)
{
	int i, j;
	A=(Airline) malloc (sizeof(AirlineCol)*places);
	if (A!=NULL) {
		for (i=0; i<places; i++) {
			A[i]=(AirlineCol) malloc (sizeof(airlineInfo)*places);
			if (A[i]!=NULL) {
				for (j=0; j<places; j++) {
					A[i][j].hours=0;
					A[i][j].flightNum=SENTINEL;
				}
			}
		}
	}
}
