#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "orders.h"

int root()
{ 
    return 0;
}

int parent(int i)
{ 
    return (i-1)/2; 
}

int left_child(int i)
{ 
    return 2*i+1;
}

int right_child(int i)
{ 
    return 2*i+2;
}

int is_root(int i) 
{ 
    return i == root();
}

void* min_value(heap *h)
{
   
    
   return (h)->data ;

}

void build_heap(void* array,size_t n,heap* h)
{ 
    if(h->data){
                   free(h->data);
                   h->size = 0; 
                   h->capacity = 0; 
               }
    
    
     h->size = n; 
     h->capacity = n;
    
     if(n==0) return;
     h->data = (void*)malloc(h->data_size *2*n);
     memcpy(h->data,array,n*h->data_size);
     
    
    
     for(int i = parent(n-1); i>= 0; i--)
              heapify(h,i);
}
void double_dimension(heap* h)
{ 
   
    size_t n = h->size;
    
    

    void *r = malloc(sizeof(h->data_size * n *2));

    if (r != NULL)
    {
        memcpy(r,h->data,h->data_size*n);
        free(h->data);
        h->data = r;

        h->capacity += n;
       
    }
    return;

}
void swap_elements(heap *h, void *a, void *b)
{
    
    void *t = malloc(h->data_size);
   // void *t= h->data + (h->size + h->capacity -1)*(h->data_size);
    memcpy(t, a, h->data_size);
    memcpy(a, b, h->data_size);
    memcpy(b, t, h->data_size);
    free(t);  

}

int is_valid(heap* h, int i)
{
    return i < h->size; 
}
    
int is_leaf(heap* h, int i)
{
    return i >= (h->size)/2;
}
    


void heapify(heap* h, int i)
{
    
    while(!is_leaf(h,i))
    {  
    int left = left_child(i); 
    void* l = h->data +(left)*h->data_size;
    int right = right_child(i); 
    void* r;
    if(is_valid(h,right))
    {
    r = h->data +(right)*h->data_size;
    }
    void* this = h->data +(i)*(h->data_size);
    void* min;
    
    if(!is_valid(h,right))
    {
        min = l;
    }
    else if(h->comp(l,r))
    { 
        min = l;
        i = left;
    }
   else
    { 
        min = r; 
        i = right; 
    }

    if(h->comp(this,min))
    { 
        i = h->size; 
    }
    else
    {   
       swap_elements(h,min,this);
    }
    
    
    }
    
    
   
}

void insert_value(heap* h, void* value)
{   
   if(!h->data){ 
          h->data = malloc(h->data_size*10);
          h->capacity = 10;

   }
    if(h->capacity <= 1) double_dimension(h);
    int p = parent(h->size);
    void* value_parent = h->data + p*(h->data_size);
     void* ins =  (h->comp(value,value_parent))? value_parent: value; 

     void *t= h->data + (h->size)*h->data_size;
      memcpy(t, ins, h->data_size);
      

      decrease_key(h,h->size,value);
      h->size++; 
      h->capacity--;
      return; 


}

 void decrease_key(heap* h,size_t i,void* value)
 {   
     if(!is_valid(h,i)) return;
     void* v = h->data +i*(h->data_size);
     
     
     
     if(h->comp(v,value))    
     {   //the key of the node is smaller or equal value
         //so nothing to do 
          return;
     }
     else  
     {    
           
         void* node = h->data +i*(h->data_size);
         memcpy(node,value,h->data_size);

         int p = parent(i);
         void* parente =  h->data + p*(h->data_size);
        
          while( i!=0  && !h->comp(parente,node))
          {    
             
             swap_elements(h,parente,node);
            
             node = parente; 
             i = p; 
             p = parent(i); 
             parente = h->data + p*(h->data_size);
        
         } 
     }
     
    return; 
 }

 void remove_min(heap* h)
 { 
     if((h->size==0)) return; 

      void* min = h->data; 
      void *last = h->data +(h->size-1)*(h->data_size);
      swap_elements(h,min,last);
      h->size--;
      h->capacity++;
      heapify(h,root());
 }

 void delete_heap(heap* h)
 {
     h->capacity = 0; 
     h->size = 0; 
     free(h->data);
 }



void print_heap(heap *h, 
                void (*key_printer)(const void *value))
{
    if(h->size == 0) return;
    unsigned int next_level_node = 1; 
                                
    for(unsigned int node = 0; node < h->size; node ++) { 
        if(node == next_level_node){ 
            printf("\n"); 
            next_level_node = left_child(node); 

        }else{
            printf("\t"); 
        }
        key_printer(h->data+node* h->data_size); 
    }
    printf("\n"); 

}