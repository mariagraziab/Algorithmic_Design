#include "binheap.h" 
#include <string.h> 
#include <stdio.h> 

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*node+1)
#define RIGHT_CHILD(node) (2*(node+1 ))
#define VALID_NODE(H,node) ((H)->num_of_elem > (node))
#define ADDR(H,node) ((H)->A+(node)*(H)->key_size)



binheap_type* build_heap(void *A,
                         const unsigned int num_of_elem,
                         const unsigned int max_size,
                         const size_t key_size,
                         total_order_type leq)
{
    
  
    binheap_type *H = (binheap_type*)malloc(sizeof(binheap_type));
   
    H->A = A; 

    H->num_of_elem = num_of_elem; 

    H->max_size = max_size; 

    H->key_size = key_size; 

    H->leq = leq; 

    H->max_order_value = malloc(key_size); 

    H->total_nodes = num_of_elem; 
      
    const void *value = find_the_max(A,num_of_elem,key_size,leq);
     
     
    
    
    H->Pos = (unsigned int*)malloc(sizeof(unsigned int)*max_size);
   
    H->Free_pos = (unsigned int*)malloc(sizeof(unsigned int)*max_size);
    
    H->place = 0; 
    
    if(num_of_elem==0){
        
         return H; 
    }


    memcpy(H->max_order_value,value,key_size);
    
    for(unsigned int i = 0; i<num_of_elem; i++)
        H-> Pos[i] = i;
     
    for(unsigned int i = num_of_elem/2-1;i>0; i--)
    {    
         
          
          heapify(H,i);
    }   
       heapify(H,0);
       

      return H;




}

int is_heap_empty(const binheap_type *H)
{
    return H->num_of_elem==0;    //num_of_elem are the active node 
}



void heapify(binheap_type *H, unsigned int node)
{   
     unsigned int dst_node = node,child; 
    

     do
     {
         node = dst_node; 
         child = RIGHT_CHILD(node);

         if(VALID_NODE(H,child) && H->leq(ADDR(H,H->Pos[child]),ADDR(H,H->Pos[dst_node]))){
                dst_node = child;  
            
            }
             child = LEFT_CHILD(node); 
            if(VALID_NODE(H,child) && H->leq(ADDR(H,H->Pos[child]),ADDR(H,H->Pos[dst_node]))){
                dst_node = child;  
             
            
            }

            if(dst_node != node){ 
             int tmp = H->Pos[node];
             H->Pos[node]=H->Pos[dst_node];   
             
             H->Pos[dst_node]= tmp; 
            }
            }while(dst_node!=node);

        
     }

const void *extract_min(binheap_type *H)
{
    if(is_heap_empty(H))
    {
        return NULL;
    }

    int tmp = H->Pos[0]; 

    H->Pos[0]= H->Pos[H->num_of_elem-1]; 

    H->num_of_elem--;

    H->Free_pos[H->place] = tmp; 

    H->place++;

    heapify(H,0);

    return ADDR(H,tmp);


}


void insert_value(binheap_type *H, const void *value)
{  
     
    if ( H->max_size==H->num_of_elem)
    { 
       
        return; 
    }
   
    if(H->num_of_elem == 0 || !H->leq(value, H->max_order_value)) {
       
       memcpy(H->max_order_value,value,H->key_size);
   }
     
   if(H->total_nodes < H->max_size)
   {  
        
       H->Pos[H->num_of_elem] = H->total_nodes; 
       void *t = H->A+ (H->total_nodes)*(H->key_size);
       memcpy(t,H->max_order_value,H->key_size);
        H->total_nodes ++;
        H->num_of_elem++;
       decrease_key(H,H->num_of_elem-1,value);

   }
   else
   {   
       
       H->place--; 
       H->Pos[H->num_of_elem] = H->Free_pos[H->place]; 
       void* t = ADDR(H,H->Pos[H->num_of_elem]); 
       H->num_of_elem++; 
       memcpy(t,H->max_order_value,H->key_size);
        
        
       decrease_key(H,H->num_of_elem-1,value);


   }

   return; 
}


const void *min_value(const binheap_type *H)
{

    
    if (is_heap_empty(H)) {
        return NULL;
    }
    
    return ADDR(H,H->Pos[0]);
}










const void *find_the_max(void *A,
                         const unsigned int num_of_elem,
                         const size_t key_size,
                         total_order_type leq)

{ 
    if(num_of_elem==0) return NULL; 
    
    const void *max_value = A; 
    for(const void *addr = A+key_size;
         addr!=A+num_of_elem*key_size; 
          addr+= key_size){ 
        if(!leq(addr,max_value)){
            max_value = addr;
        }
    }
    return max_value; 


}


void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value))
{   

    unsigned int next_level_node = 1;
                                     
    for(unsigned int node = 0; node < H->num_of_elem; node ++) { 
        if(node == next_level_node){ 
            printf("\n"); 
            next_level_node = LEFT_CHILD(node); 

        }else{
            printf("\t"); 
        }
        key_printer(ADDR(H,H->Pos[node])); 
    }
    printf("\n"); 

}


void decrease_key(binheap_type *H, unsigned int node, const void *value)
{    
    
     unsigned int node_idx = node;  
    
    if(!(VALID_NODE(H,node_idx)) || !(H->leq(value,ADDR(H,H->Pos[node])))){
        
        return;
    }

   
    void* t = ADDR(H,H->Pos[node]);
  
    memcpy(t,value,H->key_size);   
    
    
    
    
    if(node_idx == 0) return;
    unsigned int parent_idx = PARENT(node_idx);
    void *parent = ADDR(H,H->Pos[parent_idx]);   
    
      
    while((node_idx!=0)&&(!H->leq(parent,t))){ 
        
       
            int tmp = H->Pos[node_idx];
             H->Pos[node_idx]=H->Pos[parent_idx];   
             
             H->Pos[parent_idx]= tmp; 

        
        node_idx = parent_idx; 
        if(node_idx!=0){
        parent_idx=PARENT(node_idx); 
              
        parent = ADDR(H,H->Pos[parent_idx]);}
        
    }
           

    return;
}


void delete_heap(binheap_type *H)
{  
    free(H->max_order_value); 
    free(H->Pos);
    free(H->Free_pos);
    free(H);
}
