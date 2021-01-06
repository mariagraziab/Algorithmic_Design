#include "matrix.h"
#include <stdio.h>
void sum_matrix_blocks(float **C, float const *const *const A,
                       float const *const *const B,
                       const size_t C_f_row,const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
    for(size_t y=0; y<n; y++)  
    { 
        for(size_t x = 0; x<n; x++)
        {
            C[y+C_f_row][x+C_f_col]=A[y+A_f_row][x+A_f_col]+B[y+B_f_row][x+B_f_col];
        }

    }

}
void sub_matrix_blocks(float **C, float const *const *const A,
                       float const *const *const B,
                       const size_t C_f_row,const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
                       
{
    for(size_t y=0; y<n; y++)  
    { 
        for(size_t x = 0; x<n; x++)
        {
            C[y+C_f_row][x+C_f_col]=A[y+A_f_row][x+A_f_col]-B[y+B_f_row][x+B_f_col];
        }

    }
}
void naive_aux(float **C, float const *const *const A, 
                  float const *const *const B,
                   const size_t C_f_row,const size_t C_f_col,
                   const size_t A_f_row, const size_t A_f_col,
                   const size_t B_f_row, const size_t B_f_col,
                   const size_t n)
{ 


  for(size_t y=0; y<n; y++)
  {
    for(size_t x = 0; x<n; x++)
    {
      float value = 0.0; 
      for(size_t z = 0; z<n; z++)
      {
        value += A[y+A_f_row][z+A_f_col]*B[z+B_f_row][x+B_f_col];
      }
      C[y+C_f_row][x +C_f_col]= value; 
         
    }
  }

}
void strassen_aux(float **C, float const *const *const A, 
                  float const *const *const B, float **S,
                   const size_t C_f_row,const size_t C_f_col,
                   const size_t A_f_row, const size_t A_f_col,
                   const size_t B_f_row, const size_t B_f_col,
                   const size_t S_f_row, const size_t S_f_col,
                   const size_t n)
{
    if (n<=64)    {   //naive matrix moltiplication
        naive_aux(C,A,B,
                  C_f_row,C_f_col,
                  A_f_row,A_f_col,
                  B_f_row,B_f_col,n);
        return; 
    }

    size_t n2 = n/2; 
   

    
     sub_matrix_blocks(S,B,B,              
                     S_f_row,S_f_col,
                    B_f_row,B_f_col +n2,
                    B_f_row +n2, B_f_col +n2,
                    n2);
    // SALVO P1 
     strassen_aux(S,A,(const float* const *const )S, S,   
                 S_f_row,S_f_col+n2,   
                A_f_row,A_f_col,    
                 S_f_row,S_f_col,               
                  S_f_row+n2,S_f_col+n2,
                n2); 
      
    
     //S2 = A11+A12
   
    sum_matrix_blocks(S,A,A,
                     S_f_row,S_f_col,
                    A_f_row,A_f_col ,
                    A_f_row , A_f_col +n2,
                    n2);
    
  // SALVO P2 IN C12
    strassen_aux(C,(const float* const const*)S,B,S,
                 C_f_row,C_f_col+n2,
                 S_f_row,S_f_col,
                B_f_row +n2, B_f_col+n2,
                 S_f_row +n2,S_f_col+n2,
                n2); 
               

      //S3 = A21 +A22 
 
    sum_matrix_blocks(S,A,A,
                      S_f_row,S_f_col,
                    A_f_row+n2,A_f_col ,
                    A_f_row+n2 , A_f_col +n2,
                    n2);
        //P3 = S3 x B11
       //  salvo p3 in C21
    strassen_aux(C,(const float* const const*)S,B,S,
                 C_f_row+n2,C_f_col,
                 S_f_row,S_f_col,
                B_f_row,B_f_col,
                 S_f_row+n2,S_f_col+n2,
                n2);   
                   
      //S4 = B21-B11
     sub_matrix_blocks(S,B,B,
                      S_f_row,S_f_col,
                    B_f_row+n2,B_f_col ,
                    B_f_row , B_f_col,
                    n2);
                     
        //P4 = A22 x S4 
        //salvol p4 in C11
     strassen_aux(C,A,(const float* const const*)S,S,
                 C_f_row ,C_f_col,
                A_f_row +n2, A_f_col +n2,
                 S_f_row,S_f_col,
                  S_f_row+n2,S_f_col+n2,
                n2);  

                
        
    
    //1   :  C22 = P1 -P3 = S12 -C21
    sub_matrix_blocks(C,(const float* const *const )S,(const float* const *const )C,
                      C_f_row +n2,C_f_col+n2,
                       S_f_row,S_f_col+n2,
                      C_f_row +n2, C_f_col,
                      n2); 
    // p3 +p4 :   C21 = c21 + C11 //
    sum_matrix_blocks(C,(const float* const *const )C,(const float* const *const )C,
                      C_f_row +n2,C_f_col,
                      C_f_row+n2, C_f_col,
                      C_f_row,C_f_col,
                      n2); 
    // P4 -p2 =   C11 = C11-C12
     sub_matrix_blocks(C,(const float* const *const )C,(const float* const *const )C,
                      C_f_row ,C_f_col,
                      C_f_row , C_f_col,
                      C_f_row , C_f_col+n2,
                      n2);  
    //p2 +p1 =    C12 = C12 +S12

    sum_matrix_blocks(C,(const float* const *const )C,(const float* const *const )S,
                      C_f_row ,C_f_col+n2,
                      C_f_row  , C_f_col+n2,
                       S_f_row,S_f_col+n2,
                      n2);  
   

    
//S5 = A11 +A22
     sum_matrix_blocks(S,A,A,
                      S_f_row,S_f_col,  //salvo il S11
                    A_f_row ,A_f_col ,
                    A_f_row+n2 , A_f_col +n2,
                    n2);
    //S6 = B11 + B22
     sum_matrix_blocks(S,B,B,
                      S_f_row,S_f_col+n2,    //salvo in S12 
                    B_f_row ,B_f_col ,
                    B_f_row+n2 , B_f_col +n2,
                    n2);
//calcolo p5 

    strassen_aux(S,(const float* const const*)S,(const float* const const*)S,S, //salvo p5 in S21
                  S_f_row+n2,S_f_col,            
                  S_f_row,S_f_col,
                 S_f_row,S_f_col+n2,
                  S_f_row+n2,S_f_col+n2,
                n2); 

    //aggiungo p5 a c11 e c22     

   sum_matrix_blocks(C,(const float* const *const )C,(const float* const const*)S,
                      C_f_row ,C_f_col,
                      C_f_row  , C_f_col,
                       S_f_row+n2,S_f_col,
                      n2);  
    
     sum_matrix_blocks(C,(const float* const *const )C,(const float* const const*)S,
                      C_f_row +n2,C_f_col+n2,
                      C_f_row+n2  , C_f_col+n2,
                       S_f_row+n2,S_f_col,
                      n2);  
    //s7 = A12 -A22 
     sub_matrix_blocks(S,A,A,
                      S_f_row,S_f_col,    //salvo in S11
                    A_f_row,A_f_col +n2 ,
                    A_f_row+n2 , A_f_col+n2,
                    n2);
      //S8 = B21 + B22
    sum_matrix_blocks(S,B,B,
                      S_f_row,S_f_col+n2,
                    B_f_row+n2,B_f_col ,
                    B_f_row +n2 , B_f_col+n2,
                    n2); 
       //P6 = S7 x S8
     strassen_aux(S,(const float* const const*)S,(const float* const const*)S,S,
                  S_f_row+n2,S_f_col,
                  S_f_row,S_f_col,
                 S_f_row,S_f_col+n2,
                  S_f_row+n2,S_f_col+n2,
                n2);       
    //  aggiungo p6 a c11 

     sum_matrix_blocks(C,(const float* const *const )C,(const float* const const*)S,
                      C_f_row ,C_f_col,
                      C_f_row  , C_f_col,
                       S_f_row+n2,S_f_col,
                      n2); 
     //S9 = A11 -A21 
    sub_matrix_blocks(S,A,A,
                      S_f_row,S_f_col,
                    A_f_row,A_f_col  ,
                    A_f_row+n2 , A_f_col,
                    n2);  
    //S10 = B11 +B12
     sum_matrix_blocks(S,B,B,
                      S_f_row,S_f_col+n2,
                    B_f_row,B_f_col ,
                    B_f_row , B_f_col+n2,
                    n2);   

       //P7 = S9 x S10 
    strassen_aux(S,(const float* const const*)S,(const float* const const*)S,S,
                 S_f_row+n2,S_f_col,
                 S_f_row,S_f_col,
                 S_f_row,S_f_col+n2,
                 S_f_row+n2,S_f_col+n2,
                 n2);  
                 
    //sottraggo p7 da c22 
      sub_matrix_blocks(C,(const float* const *const )C,(const float* const const*)S,
                      C_f_row +n2 ,C_f_col+n2,
                      C_f_row +n2 , C_f_col+n2,
                      S_f_row+n2,S_f_col,
                      n2); 

                      
    
    
}

void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, size_t n) 
{
   float **S = allocate_matrix(n, n);
  
 

  strassen_aux(C,A,B,S,
              0,0,
              0,0,
              0,0,
              0,0,
              n);
  deallocate_matrix(S, n);
 
}

