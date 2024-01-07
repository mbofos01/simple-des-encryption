#include "library.h"

/**
* This function implements SBOX1
*
* int *src -> the input of the sbox
* int size -> the size  of the input
*/
void SBOX1(int *src,int *dest,int size){
  int row = 0,col = 0,i = 0, exp = 1;
  for(i=0;i<size;i++)
  {
   if(src[i] == 1){
    if(i == 0 || i == size -1 )
      row += pow(2,exp);
    else
      col += pow(2,exp);
    }
    if( i == 1)
      exp--;
  }
  int number = S0[row][col];
  convertToBits(number,dest);
}

/**
* This function implements SBOX2
*
* int *src -> the input of the sbox
* int size -> the size  of the input
*/
void SBOX2(int *src,int *dest,int size){
  int row = 0,col = 0,i = 0, exp = 1;
  for(i=0;i<size;i++)
  {
   if(src[i] == 1){
    if(i == 0 || i == size -1 )
      row += pow(2,exp);
    else
      col += pow(2,exp);
    }
    if( i == 1)
      exp--;
  }
  int number = S1[row][col];
  convertToBits(number,dest);
}
