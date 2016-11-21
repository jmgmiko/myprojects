/******************************************************************
 * Project Name:  Graph                                    *
 * Programmer  :  Gaid, Jan Mikhail M.                             *
 * Date Completed: March 28, 2016                                 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************************
 * Data Structure Definition of a Graph Implementation                      *
 ********************************************************/
#define SIZE 5                               /* Maximum size of the array, thus vertices are: 0, 1, 2, 3, 4 */
#define SENTINEL 999      					 /* instead of infinity */
#define APSPMatrix LabeledAdjMatrix

typedef int vertex;

/* arc or directed edge representation */
typedef struct {
	vertex tail;      /* tail vertex of the arc */
	vertex head;      /* head vertex of the arc */
	int weight;       /* weight of the arc      */ 
}arcType;

/* Adjacency List Representation */
typedef struct node {
	vertex adjVertex;    /* adjacent vertex */
	int weight;         /* weight of the associated arc */
	struct node *next;
}*List;
typedef List AdjList[SIZE];                   

/* Labeled Adjacency matrix Representation*/   
typedef int LabeledAdjMatrix[SIZE][SIZE];                                               

/* Bit-Vector Implementation of the set of vertices */
typedef vertex SET[SIZE];    					


/**************************************************
 * Function Prototypes                            *
 **************************************************/
void createAdjList(AdjList L);
void displayAdjList(AdjList L); 
 
void createLabeledAdjMatrix(LabeledAdjMatrix M, AdjList L);
void displayMatrix(LabeledAdjMatrix M, char *titleMsg);

int *dijkstraSource(LabeledAdjMatrix M, vertex source);
void displayShortestPath(int *D, vertex source);


APSPMatrix * findAPSP(LabeledAdjMatrix M);     /* All Pairs Shortest Path -> dijktra called N times */

int * findEccentricity(APSPMatrix A);
void displayEccentricity(int *ecc);
void displayCenterGraph(int *ecc);

 
 
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *   4)  Uncomment or copy the print statement in each PROBLEM#  if the task is     *
 *       completed.                                                                 *
 ***********************************************************************************/
 int main( ) 
 {	
  /*-------------------------------------------------------------------------------
   * Write all variable declaration here.                                         *
   *------------------------------------------------------------------------------*/
    AdjList L;
    LabeledAdjMatrix LAM;
	LabeledAdjMatrix *A;
    int *least;
  
/*---------------------------------------------------------------------------------
 * 	Problem #1 ::  Create the adjacency list L representing the directed graph    *
 *                 by calling createAdjList() then call displayAdjList() to       *
 *                 display the adjacent vertices.                                 *
 *                                                                                *
 *                                                  *
 *--------------------------------------------------------------------------------*/
 	printf("\n\n\nProblem #1:: ");
  	createAdjList(L);
	displayAdjList(L);
  
/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  Create the labeled adjacency matrix M using the adjacency    *
 *                 list L, then call displayMatrix() to display the Labeled       *
 *                 adjacency matrix.                                              *
                                                          *
 *                                              *
 *--------------------------------------------------------------------------------*/
 	system ("cls");
	printf("\n\n\nProblem #2:: ");    
 	createLabeledAdjMatrix(LAM, L);
 	displayMatrix(LAM, "Labeled Adjacency Matrix :: ");

   
/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  Determine the cost of the shortest path from Vertex 2 to the   * 
 *                 other vertices by calling dijkstraSource(), passing the        *
 *                 labeled adjacency matrix M and Vertex 2.                       * 
 *                 Call displayShortestPath() to display the result               *
 *                                                                                *                                         
 *                                                 *
 *--------------------------------------------------------------------------------*/
 	system ("cls");
	printf("\n\n\nProblem #3:: "); 
 	least=dijkstraSource(LAM, 2);
    displayShortestPath(least, 2);
 
  
/*---------------------------------------------------------------------------------
 * 	Problem #4 ::   Determine the APSP cost matrix by calling findAPSP(), then    *
 *                  call displayMatrix().                                         *
 *  printf("\n\n\nProblem #4:: ");                                                *
 *--------------------------------------------------------------------------------*/	
 	system ("cls");
	A=findAPSP(LAM);
 	displayMatrix(*A, "All Pairs Shortest Path (APSP) Matrix :: ");
 	
/*---------------------------------------------------------------------------------
 * 	Problem #5 ::  Determine the center of the graph by finding the eccentricity  *
 *                 of each vertex by calling findEccentricity, then display the   *
 *                 the eccentricity of each vertex. Call displayCenterGraph to    *
 *                 display the center(s) of the graph.                            *
 *                                                                                *
 *  printf("\n\n\nProblem #5:: ");                                                *
 *--------------------------------------------------------------------------------*/		     
  
  
	
 getch();
 return 0;
}


/************************************************************
 *  Problem 1 Function Definitions                          *
 ************************************************************/
 
void createAdjList(AdjList L)
{
	int const COUNT = 9;
	arcType data[] = { {4, 2, 15}, {0, 1, 10}, {1, 2, 50}, {2, 0, 20}, {0, 4, 100},
					   {3, 4, 60}, {0, 3, 20}, {3, 2, 20}, {2, 4, 10}       
                     };
 
     
              /***********************************************
                * Write  your code fragment here.                                         *
                ***********************************************/                    
    int i;
    List temp, *trav;
    for (i=0; i<COUNT; i++) {
    	L[i]=(List) malloc (sizeof(struct node));
    	if (L[i]!=NULL) {
    		L[i]->adjVertex=i;
    		L[i]->next=NULL;
		}
	}
	for (i=0; i<COUNT; i++) {
		for (trav=&L[data[i].tail]->next; *trav!=NULL && data[i].head>(*trav)->adjVertex; trav=&(*trav)->next) {}
		temp=(List) malloc (sizeof (struct node));
		if (temp!=NULL) {
			temp->adjVertex=data[i].head;
			temp->weight=data[i].weight;
			temp->next=*trav;
			*trav=temp;
		}
	}
}


void displayAdjList(AdjList L)
{
	vertex v;
	List temp;
	
	printf("\n\nThe Adjacency List ::");
	printf("\n%-8s", "VERTEX");
	printf("%-20s", "Adjacent vertices");
	printf("\n%-8s", "------");
	printf("%-20s", "-----------------");
	 /***********************************************
                * Write  your code fragment here.                                         *
                ***********************************************/    
	printf ("\n");                	
	for (v=0; v<SIZE; v++) {
		for (temp=L[v]; temp!=NULL; temp=temp->next) {
			printf ("%-8d", temp->adjVertex);
		}
		printf ("\n");
	}
	printf("\n\nPress any key to continue ... ");
	getch();
		
} 
 
/************************************************************
 *  Problem 2 Function Definitions                          *
 ************************************************************/ 
	
void createLabeledAdjMatrix(LabeledAdjMatrix M, AdjList L)
{
	vertex x, y;
	List trav;
	for (x=0; x<SIZE; x++) {
		trav=L[x]->next;
		for (y=0; y<SIZE; y++) {
			if (trav!=NULL && y==trav->adjVertex) {
				M[x][y]=trav->weight;
				trav=trav->next;
			} else {
				M[x][y]=SENTINEL;
			}
		}
	}
} 

void displayMatrix(LabeledAdjMatrix M, char *titleMsg)
{
	vertex a, b;
	printf ("\n%s \n", titleMsg);
	for (a=0; a<SIZE; a++) {
		for (b=0; b<SIZE; b++) {
			(M[a][b]!=SENTINEL)?printf ("%5d ", M[a][b]):printf ("%5c", 236);
		}
		printf ("\n");
	}
	printf("\n\nPress any key to continue ... ");
	getch();
}


/************************************************************
 *  Problem 3 Function Definitions                          *
 ************************************************************/

int *dijkstraSource(LabeledAdjMatrix M, vertex source)
{
	int *collect, i, j, k, min, mv;
	SET S, V, T;
	for (i=0; i<SIZE; i++) {
		V[i]=1;
		S[i]=(i==source)?1:0;
	}
	collect=(int *) malloc (sizeof(int)*SIZE);
	if (collect!=NULL) {
		for (i=0; i<SIZE; i++) {
			collect[i]=(i!=source)?M[source][i]:0;
			T[i]=V[i]&(~S[i]);
		}
		for (j=1; j<SIZE; j++) {
			for (min=i=0, mv=M[source][i]; i<SIZE; i++) {
				if (T[i]==1&&mv>collect[i]) {
					min=i;
					mv=collect[i];
				} 
			}
			S[min]=1;
			for (k=0; k<SIZE; k++) {
				T[k]=V[k]&(~S[k]);
			}
			for (k=0; k<SIZE; k++) {
				if (T[k]==1) {
					collect[k]=(collect[k]>(collect[min]+M[min][k]))?(collect[min]+M[min][k]):collect[k];
				}
			}
		}
	}
	return collect;
}

void displayShortestPath(int *D, vertex source)
{
	int x;
	
	printf("\n\nShortest Path from Source Vertex %d", source);
    printf("\n----------------------------------") ;
	printf("\n%15s", "Vertex::");
	for(x = 0; x < SIZE; x++){
		printf("%8d", x);
	}
	
	printf("\n%15s", "Distance::");
            	 /***********************************************
                * Write  your code fragment here.                                         *
                ***********************************************/                    
	for(x = 0; x < SIZE; x++){
		printf("%8d", D[x]);
	}
	
	printf("\n\nPress any key to continue ... ");
	getch();	
}


/************************************************************
 *  Problem 4 Function Definitions                          *
 ************************************************************/
APSPMatrix * findAPSP(LabeledAdjMatrix M)
{
	LabeledAdjMatrix *AM;
	int a, b, *res, mult[SIZE][SIZE];
	AM=(LabeledAdjMatrix *)malloc(sizeof(LabeledAdjMatrix));
	if (AM!=NULL) {
		for (a=0; a<SIZE; a++) {
			res=dijkstraSource (M, a);
			*AM[a][0]=res;
		}
	}
	return AM;
}	

/************************************************************
 *  Problem 5 Function Definitions                          *
 ************************************************************/


