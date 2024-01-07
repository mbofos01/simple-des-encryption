#include "library.h"

/**
* This function applies XOR function
* to a set of arrays, and returns the result
*
* int *base   -> xor input 1
* int *offser -> xor input 2
* int length  -> size of the arrays
*/
void xor(int* base,int* offset,int *dest,int length){
  int i=0;
  for(i=0;i<length;i++)
    if(base[i] != offset[i])
      dest[i] = 1;
    else
      dest[i] = 0;

  }
/**
* This function breaks the plaintext (message)
* to two parts, the first 4 bits to "left" and
* the rest 4 bits to "right"
*
* int *right -> last 4 bits
* int *left  -> first 4 bits
*/
  void breakText(int *right,int *left){
    int i = 0;
    for(i=0;i<WORDLENGTH/2;i++){
      left[i] = plaintext[i];
      right[i]= plaintext[i+WORDLENGTH/2];
    }
  }
/**
* This function breaks a array to two parts
* the first X bits to "left" and the rest X
* bits to "right".
*
* int *right -> last 4 bits
* int *left  -> first 4 bits
* int *src   -> the array we break
* int size   -> the size of the array
*/
  void breakSRC(int *right,int *left,int *src,int size){
    int i = 0;
    for(i=0;i<size/2;i++){
      left[i] = src[i];
      right[i]= src[i+size/2];
    }
  }
/**
* This function extends an array, according
* to the mapping of the array EP
* (from 4-bit to 8-bit)
*
* int *table -> the array we extend
*/
  void extend(int *table,int *dest,int size){
    int i;
    for(i=0;i<size;i++)
      dest[i] = table[EP[i]];
  }
/*
* This function converts an int to a binary
* represantation.
*
* int inputValue    -> the int we want to convert
* int *outputArray  -> the array we store the binary represantation
*/
  void convertToBits(int inputValue, int *outputArray){
    // counter for binary array
    int cnt = 1;

    while (inputValue > 0) {
       // storing remainder in binary array
           outputArray[cnt--] = inputValue % 2;
           inputValue = inputValue / 2;
       }
       if(cnt == 1)
        outputArray[1] = 0;
       if(cnt != -1)
        outputArray[0] = 0;
  }
/**
* This function prints an array
*
* int *sw  -> the array we want to print
* int size -> the size of the array
*/
  void printArray(int *sw,int sze){
    int i = 0;
    for(i=0;i<sze;i++)
      printf("%d",sw[i]);
    printf("\n");
  }
/**
* This function merges and returns together two arrays
*
* int *left  -> array 1
* int *right -> array 2
* int   sL   -> size of array 1
* int   sR   -> size of array 2
*/
  void merge(int *left,int *right,int *dest,int sL,int sR){
    int i=0;
    for(i=0;i<sL;i++)
      dest[i] = left[i];

    for(i=0;i<sR;i++)
      dest[i+sL] = right[i];

  }
/**
* This function copies and returns the
* values of an array
*
* int *src -> the array we copy
* int size -> the size of the array
*/
  void copy(int* src,int* dest,int size){
    int i=0;
    for(i=0;i<size;i++)
      dest[i] = src[i];
  }
/**
* This function swaps two arrays
*
* int *right -> array 1
* int *left  -> array 2
* int size   -> size of the arrays
*/
  void crossSwitch(int *left,int *right,int size){
    int *temp = (int*)malloc(sizeof(int)*size);
    int i = 0;
    for(i=0;i<size;i++)
      temp[i] = left[i];
    for(i=0;i<size;i++)
      left[i] = right[i];
    for(i=0;i<size;i++)
      right[i] = temp[i];
    free(temp);

  }
/**
* This function prints the key
*/
  void printKey(){
    printf("KEY: ");
    int i=0;
    for(i=0;i<KEYLENGTH;i++)
    {
      printf("%d",key[i]);
    }
    printf("\n");
  }
