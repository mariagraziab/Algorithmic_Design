#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utility.h"
#include "graph.h" 
//#include "node.h" 
#include "math.h"

#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec +	\
		   (double)ts.tv_nsec * 1e-9)

int main()
{ 
 
 int n = 20; 

 int **matrix = allocate_matrix(n);
 srand(2); 
 random_matrix(matrix,n); 



 matrix[2][4] = 0; 
 matrix[3][5] = 0; 
 matrix[3][4] = 0; 
 matrix[4][5] = 0; 
 matrix[2][3] = 0; 
 matrix[1][4] = 0; 
 matrix[1][3] = 0; 
 matrix[0][2] = 0; 
 matrix[0][1] = 0; 
 matrix[6][2] = 0; 
 matrix[2][6] = 0; 
 matrix[0][7] = 0; 
 matrix[2][7] = 0; 
 matrix[7][1] = 0; 
 matrix[1][7] = 0; 
 matrix[4][8] = 0; 
 matrix[3][8] = 0; 
 matrix[5][9] = 0;
 matrix[8][9] = 0; 
 matrix[9][6] = 0; 
 matrix[9][1]= 0;


FILE *fp; 
fp=fopen("graph.txt", "wt");

for(int i = 0; i< n; i++)
{
    for(int j = 0; j< n; j++)
    { 
       if(matrix[i][j] != 0) fprintf(fp,"e %d %d %d\n",i,j,matrix[i][j]);
    }
}



Graph* G = init_graph(matrix,n);
Graph* G2 = init_graph(matrix,n); 

dijkstra_array(G,0);
dijkstra_heap(G2,0);
printf("Distances calculated with array version\n");
print_dist(G,0);
print_dist(G,1);
print_dist(G,2);
print_dist(G,3);
print_dist(G,4);
print_dist(G,5);
print_dist(G,6);
print_dist(G,7);
print_dist(G,8);
print_dist(G,9);
print_dist(G,10);
print_dist(G,11);
print_dist(G,12);
print_dist(G,13);
print_dist(G,14);
print_dist(G,15);
print_dist(G,16);
print_dist(G,17);
print_dist(G,18);
print_dist(G,19);
printf("Distances calculated with heap version\n");
print_dist(G2,0);
print_dist(G2,1);
print_dist(G2,2);
print_dist(G2,3);
print_dist(G2,4);
print_dist(G2,5);
print_dist(G2,6);
print_dist(G2,7);
print_dist(G2,8);
print_dist(G2,9);
print_dist(G2,10);
print_dist(G2,11);
print_dist(G2,12);
print_dist(G2,13);
print_dist(G2,14);
print_dist(G2,15);
print_dist(G2,16);
print_dist(G2,17);
print_dist(G2,18);
print_dist(G2,19);


fclose(fp);
delete_graph(G);
delete_graph(G2);
delete_matrix(matrix,n);


///////TIME TEST /////////

 printf("Performance Test\n"); 
 struct timespec ts;
 double tstart, tstop,t2;
 
 
double tvector = 0; 
double theap = 0; 
FILE *file1, *file2; 
file1=fopen("HeapData.txt", "wt");
file2 =fopen("ArrayData.txt","wt");

for(n = 500; n<=10000; n+=500)
{   int** m = allocate_matrix(n);
    tvector = 0; 
    theap= 0;
    for(int i= 0; i<10; i++)
    {   
        srand(i);
        random_matrix(m,n);
        Graph* graph = init_graph(m,n);
        Graph* graph2 = init_graph(m,n);
        tstart = TCPU_TIME;
        dijkstra_array(graph,0);
        t2 = TCPU_TIME;
        dijkstra_heap(graph2,0);
        tstop = TCPU_TIME;
        delete_graph(graph);
        delete_graph(graph2); 
        tvector += (t2-tstart);
        theap += (tstop -t2);

    }
    tvector = tvector/10; 
    theap = theap/10; 
    printf("n\tarray \t \t heap  \n");
    printf("%d\t %g \t %g\n",n,tvector, theap);
    fprintf(file1,"%d %g\n",n,theap);
    fprintf(file2,"%d %g\n",n,tvector);
    delete_matrix(m,n);
}






fclose(file1); 
fclose(file2); 



 
 return 0; 
}
