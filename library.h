#ifndef LIBRARY_H
#define LIBRARY_H
#include <ctype.h>
#include<stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define WORDLENGTH 8
#define KEYLENGTH 10
#define DEBUG false
#define MEMORY_LEAKS false
#define BIG_SIZE 8
#define MED_SIZE 4
#define SMALL_SIZE 2

static const int CUSTOMKEY[] = {0,1,0,1,0,0,1,1,0,0};
static const int CUSTOMPLAIN[] = {0,1,0,1,0,0,0,1};
static const int IP[] = {1,5,2,0,3,7,4,6}; //add one to check
static const int FP[] = {3,0,2,4,6,1,7,5}; //add one to check
static const int P10[] = {2,4,1,6,3,9,0,8,7,5}; //add one to check
static const int EP[] = {3,0,1,2,1,2,3,0}; //add one to check
static const int P4[] = {1,3,2,0}; //add one to check
static const int P8[] = {5,2,6,3,7,4,9,8}; //add one to check
static const int LS1[] = {1,2,3,4,0}; //add one to check
static const int LS2[] = {2,3,4,0,1}; //add one to check
static const int S0[][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
static const int S1[][4] = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
extern int* plaintext , *key ;

void fillTextandKey(int parameters,char *argv[]);
bool checkForm(char *word,int size);
void printArray(int *sw,int sze);
void permuteKey();
void permutePlainText();
void xor(int* base,int* offset,int* dest,int length);
void applyLS1();
void applyLS2();
void printKey();
void extend(int *table,int *dest,int size);
void permuteKeyP8(int* dest,int size);
void permuteP4(int *src,int *dest,int size);
void permuteFinal(int *src,int *dest,int size);
void merge(int *left,int *right,int *dest,int sL,int sR);
void copy(int* src,int *dest,int size);
void breakText(int *right,int *left);
void breakSRC(int *right,int *left,int *src,int size);
void SBOX1(int *src,int *dest,int size);
void SBOX2(int *src,int *dest,int size);
void crossSwitch(int *left,int *right,int size);
void convertToBits(int inputValue, int *outputArray);
int* stringToBinary(char* s);
#endif
