#include "library.h"

/**
* This function permutes a binary array
* according to the array P4.
*
* int* src -> the array we permute
* int size -> the size of the array
*/
void permuteP4(int *src,int *dest,int size){
  int i = 0;
  for(i=0;i<size;i++){
    dest[i] = src[P4[i]];
  }

}
/**
* This function permutes a key array
* according to the array P8.
*
*/
void permuteKeyP8(int *dest,int size){
  int i = 0;
  for(i=0;i<size;i++)
    dest[i] = key[P8[i]];

}
/**
* This function permutes a binary array
* according to the array FP.
*
* int* src -> the array we permute
* int size -> the size of the array
*/
void permuteFinal(int *src,int *dest,int size){
  int i = 0;
  for(i=0;i<size;i++){
    dest[i] = src[FP[i]];
  }
}
