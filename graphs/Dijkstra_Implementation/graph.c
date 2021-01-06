#include <stdio.h>
#include "binheap.h"
#include "graph.h"


Graph* init_graph(int** matrix, int n)
{
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->size = n; 
    G->adj_matrix = matrix; 
    G->infinity = find_infinity_value(matrix,n); 
    G->nodes = (Node*)malloc(sizeof(Node)*n); 
    return G;
}

void delete_graph(Graph* G)
{
    free(G->nodes);
    free(G);
}


const int find_infinity_value(int** matrix,int n)
{
    int infinity = 0; 
    for(size_t i = 0; i<n; i++)
    { 
        for(size_t j = 0; j<n; j++)
        { 
            infinity+=matrix[i][j];
        }
    }
    infinity+=1; 

    return infinity; 
} 

void init_nodes(Graph* G)
{ 
   for(int i = 0; i< (G->size); i++)
   {

      init_node(&G->nodes[i],i,-1,G->infinity);
       
   }
}

void dijkstra_array(Graph* G, int src)
{
    init_nodes(G);
    
    set_distance(&G->nodes[src],0);


    Node** queue = build_queue(G);
    Node** Q = queue;
    int dim = G->size; 
    Node * u; 
    while(dim>0)
    {  
        u = extract_min_new(Q,dim); 
       
        
        dim--; 
        
        Q = &Q[1];
        int id = u->id; 
        
       

        for(int i = 0; i<dim; i++)
        {
            Node* v = Q[i];
            int w = G->adj_matrix[id][v->id];
            if(w !=0) relax(u,v,w);

        }

    

       
    }
   free(queue);


}





void dijkstra_heap(Graph* G, int src)
{
    init_nodes(G);
    
    set_distance(&G->nodes[src],0);

    Node* tmp = (Node*)malloc(sizeof(Node));
    binheap_type *h = build_heap(G->nodes,G->size,G->size,sizeof(Node),leq_node);
    int dim = G->size; 
    Node * u; 
    while(dim>0)
    {  
        u = extract_min(h);
        
        dim--; 
        
        int id = u->id; 
       
      int w; 
      int numb = h->num_of_elem; 
      for(int i=0; i<numb; i++)
      {
          Node* v = h->A+h->Pos[i]*h->key_size;
          int id_node = v->id; 
          if(G->adj_matrix[id][id_node]!=0)
          {
            w = G->adj_matrix[id][id_node]; 
            if((u->distance +w)<v->distance)
            {
                tmp->id = v->id; 
                tmp->distance = u->distance +w; 
                set_pred(tmp,u->id);
                decrease_key(h,i,tmp);
            }

          }
      }
     
     
       
    }
   
free(tmp);
delete_heap(h);
}

void relax(Node* u, Node* v, int w)
{  
    
    if((u->distance +w)<v->distance)
    {
       
        set_distance(v,u->distance +w);
        set_pred(v,u->id);
    }
     

}

Node** build_queue(Graph* G)
{ 
    Node** queue = malloc(sizeof(Node*)*(G->size));
    for(size_t i= 0; i<(G->size);i++)
    {
        queue[i] = &(G->nodes[i]);
    }
    return queue; 
}

Node* extract_min_new(Node** Q,int dim)
{ 
    
    int min = 0; 
    for(int i = 1; i<dim; i++)
    {   
        
        if(Q[i]->distance < Q[min]->distance)
        {
            min = i;
        }
    }

    //save min in first position

    Node* tmp = Q[min]; 
    Q[min] = Q[0]; 
    
    return tmp;
}

void print_dist(Graph* G, int id)
{
    Node* u = &G->nodes[id]; 
    int dist = u->distance; 
    if(u->distance < G->infinity)
    {
        printf("Distance of %d from source = %d\n", id,dist);
    } 
    else
    {
        printf("The node is not connected to the source"); 
    }
    
}





