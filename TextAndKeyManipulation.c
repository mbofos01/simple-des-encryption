#include "library.h"

int* plaintext = NULL, *key = NULL;

/**
* This function loads the message and the key of
* the encryption sequence, if parameters equals
* to zero we load a default key and message, otherwise
* the first parameter is the message (8-bit) and the
* second is the key (10-bit)
*
* int parameters -> number of parameters
* char *argv[]   -> parameters
*/
void fillTextandKey(int parameters,char *argv[]){
  int i=0;
  plaintext = (int*)malloc(sizeof(int)*WORDLENGTH);
  key = (int*)malloc(sizeof(int)*KEYLENGTH);

  if(parameters == 0){
    for(i=0;i<WORDLENGTH;i++)
      plaintext[i] = CUSTOMPLAIN[i];
    for(i=0;i<KEYLENGTH;i++)
      key[i] = CUSTOMKEY[i];
  }
  else{
    if(!checkForm(argv[1],WORDLENGTH))
      {
        printf("Wrong input, plaintext should be a binary with size %d!\n",WORDLENGTH);
        exit(-1);
    }
    if(!checkForm(argv[2],KEYLENGTH))
      {
        printf("Wrong input, key should be a binary with size %d!\n",KEYLENGTH);
        exit(-1);
    }
    for(i=0;i<WORDLENGTH;i++)
      plaintext[i] = (int)(argv[1][i]) - 48;
    for(i=0;i<KEYLENGTH;i++)
      key[i] = (int)(argv[2][i]) - 48;

  }
}
/**
* This function checks if a string of bits
* is corruted, in other words if it has a
* character different than 0 or 1
*/
bool checkForm(char *word,int size){
  int i = 0;
  int length = strlen(word);
  if(length != size)
    return false;
  for(i=0;i<size;i++)
    if(!isdigit(word[i]))
      return false;
    else if(word[i] - 48 != 0 && word[i] - 48 != 1)
      return false;

  return true;

}

/**
* This function permutes the key according to
* the array P10
*
*/
void permuteKey(){
  int* temp_key = (int*)malloc(sizeof(int)*KEYLENGTH);
  int i = 0;
  for(i=0;i<KEYLENGTH;i++)
    temp_key[i] = key[P10[i]];
  for(i=0;i<KEYLENGTH;i++)
    key[i] = temp_key[i];
  free(temp_key);
}
/**
* This function permutes the plaintext according to
* the array IP
*
*/
void permutePlainText(){
  int* temp_text = (int*)malloc(sizeof(int)*WORDLENGTH);
  int i = 0;
  for(i=0;i<WORDLENGTH;i++)
    temp_text[i] = plaintext[IP[i]];
  for(i=0;i<WORDLENGTH;i++)
    plaintext[i] = temp_text[i];
  free(temp_text);

}

/**
* This function applies the LS1 filter to
* the left part of the key
*
*/
void applyLS1(){
  int i = 0;
  int *ls_left  = (int*)malloc(sizeof(int)*KEYLENGTH/2);
  int *ls_right = (int*)malloc(sizeof(int)*KEYLENGTH/2);

  for(i=0;i<KEYLENGTH/2;i++)
    ls_left[i] = key[LS1[i]];

  for(i=0;i<KEYLENGTH/2;i++)
    ls_right[i] = key[LS1[i] + KEYLENGTH/2];

  for(i=0;i<KEYLENGTH/2;i++){
    key[i] = ls_left[i];
    key[i + KEYLENGTH/2] = ls_right[i];
  }
  free(ls_left);
  free(ls_right);

}
/**
* This function applies the LS2 filter to
* the right part of the key
*
*/
void applyLS2(){
  int i = 0;
  int *ls_left  = (int*)malloc(sizeof(int)*KEYLENGTH/2);
  int *ls_right = (int*)malloc(sizeof(int)*KEYLENGTH/2);
  for(i=0;i<KEYLENGTH/2;i++)
    ls_left[i] = key[LS2[i]];

  for(i=0;i<KEYLENGTH/2;i++)
    ls_right[i] = key[LS2[i] + KEYLENGTH/2];

  for(i=0;i<KEYLENGTH/2;i++){
    key[i] = ls_left[i];
    key[i + KEYLENGTH/2] = ls_right[i];
  }
  free(ls_left);
  free(ls_right);

}
