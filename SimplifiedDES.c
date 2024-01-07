#include "library.h"

int main(int argc,char *argv[]){
  int parameters = argc - 1;
  fillTextandKey(parameters,argv);
  if(DEBUG){
    printf("Plaintext: ");
    printArray(plaintext,WORDLENGTH);
    printf("Key: ");
    printArray(key,KEYLENGTH);
  }
  permutePlainText();
  if(DEBUG){
    printf("Plaintext after IP: ");
    printArray(plaintext,WORDLENGTH);
  }
  permuteKey();
  if(DEBUG){
    printf("Key after P10: ");
    printArray(key,KEYLENGTH);
  }
  applyLS1();
  int *K1 = (int*)malloc(sizeof(int)*BIG_SIZE);
  permuteKeyP8(K1,BIG_SIZE);
  if(DEBUG){
    printf("K1: ");
    printArray(K1,BIG_SIZE);
  }
  int *left  = (int*)malloc(sizeof(int)*WORDLENGTH/2);
  int *right = (int*)malloc(sizeof(int)*WORDLENGTH/2);

  breakText(right,left);

  if(DEBUG){
    printf("Text left: ");
    printArray(left,MED_SIZE);
    printf("Text right: ");
    printArray(right,MED_SIZE);
  }
  int * toBeXOR = (int*)malloc(sizeof(int)*BIG_SIZE);
  extend(right,toBeXOR,BIG_SIZE);
  if(DEBUG){
    printf("Extended right: ");
    printArray(toBeXOR,BIG_SIZE);
  }

  int *result =  (int*)malloc(sizeof(int)*BIG_SIZE);
  xor(toBeXOR,K1,result,BIG_SIZE);


  if(DEBUG){
    printf("XORed 1st: ");
    printArray(result,BIG_SIZE);
  }
  int *xored_left  = (int*)malloc(BIG_SIZE*sizeof(int));
  int *xored_right = (int*)malloc(BIG_SIZE*sizeof(int));


  breakSRC(xored_right,xored_left,result,BIG_SIZE);

  if(DEBUG){
    printf("XORed left: ");
    printArray(xored_left,MED_SIZE);
    printf("XORed right: ");
    printArray(xored_right,MED_SIZE);
  }
  //int sze = 4; // ERASE
  int *sb_left  = (int*)malloc(SMALL_SIZE*sizeof(int));
  int *sb_right = (int*)malloc(SMALL_SIZE*sizeof(int));

/************************************/
  SBOX1(xored_left,sb_left,MED_SIZE);
  SBOX2(xored_right,sb_right,MED_SIZE);
/************************************/

  if(DEBUG){
    printf("SBOX left: ");
    printArray(sb_left,SMALL_SIZE);
    printf("SBOX right: ");
    printArray(sb_right,SMALL_SIZE);
  }

  int *sw = (int*)malloc(MED_SIZE*sizeof(int));
  merge(sb_left,sb_right,sw,2,2);

  if(DEBUG){
    printf("Merged after xor: ");
    printArray(sw,MED_SIZE);
  }
  int *permuted_sw = (int*)malloc(sizeof(int)*MED_SIZE);
  permuteP4(sw,permuted_sw,MED_SIZE);

  if(DEBUG){
    printf("Right after permuatation P4: ");
    printArray(permuted_sw,MED_SIZE);
  }
  int *tsw = (int*)malloc(sizeof(int)*MED_SIZE);
  xor(left,permuted_sw,tsw,MED_SIZE);

  if(DEBUG){
    printf("SW: ");
    printArray(tsw,MED_SIZE);
    printf("Text right: ");
    printArray(right,MED_SIZE);
  }
  crossSwitch(tsw,right,MED_SIZE);
  if(DEBUG){
    printf("SW: ");
    printArray(tsw,MED_SIZE);
    printf("Text right: ");
    printArray(right,MED_SIZE);
  }
/****************************************/
// First leg ended - Second leg started //
/****************************************/
  int *final_right = (int*)malloc(sizeof(int)*MED_SIZE);
  copy(right,final_right,MED_SIZE);
  int *ext_right = (int*)malloc(sizeof(int)*BIG_SIZE);
  extend(right,ext_right,BIG_SIZE);

  if(DEBUG){
    printf("Final right: ");
    printArray(final_right,MED_SIZE);
    printf("Extended right: ");
    printArray(ext_right,BIG_SIZE);
  }
  applyLS2();
  int *K2 = (int*)malloc(sizeof(int)*BIG_SIZE);
  permuteKeyP8(K2,BIG_SIZE);
  xor(ext_right,K2,result,BIG_SIZE);

  if(DEBUG){
    printf("K2: ");
    printArray(K2,BIG_SIZE);
    printf("XORed: ");
    printArray(result,BIG_SIZE);
  }

  breakSRC(xored_right,xored_left,result,BIG_SIZE);


  if(DEBUG){
    printf("XORed left: ");
    printArray(xored_left,MED_SIZE);
    printf("XORed right: ");
    printArray(xored_right,MED_SIZE);
  }
  /************************************/
    SBOX1(xored_left,sb_left,MED_SIZE);
    SBOX2(xored_right,sb_right,MED_SIZE);
  /************************************/
  if(DEBUG){
    printf("SBOX left: ");
    printArray(sb_left,SMALL_SIZE);
    printf("SBOX right: ");
    printArray(sb_right,SMALL_SIZE);
  }
  int *sss = (int*)malloc(MED_SIZE*sizeof(int));
  merge(sb_left,sb_right,sss,SMALL_SIZE,SMALL_SIZE);


  if(DEBUG){
    printf("Merged after xor: ");
    printArray(sss,MED_SIZE);
    printf("right: ");
    printArray(final_right,MED_SIZE);
}
  int *permuted_sss = (int*)malloc(sizeof(int)*MED_SIZE);
  permuteP4(sss,permuted_sss,MED_SIZE);

  if(DEBUG){
    printf("Right after permuatation P4: ");
    printArray(permuted_sss,MED_SIZE);
  }

  int *new_s = (int*)malloc(sizeof(int)*MED_SIZE);
  xor(permuted_sss,tsw,new_s,MED_SIZE);


  if(DEBUG){
    printf("SW: ");
    printArray(tsw,MED_SIZE);
    printf("Final right: ");
    printArray(final_right,MED_SIZE);
    printf("After XOR: ");
    printArray(new_s,MED_SIZE);
  }
  int *merged = (int*)malloc(sizeof(int)*BIG_SIZE);
  merge(new_s,final_right,merged,MED_SIZE,MED_SIZE);
  if(DEBUG){
    printf("Merged: ");
    printArray(merged,BIG_SIZE);
  }
  int *final_text = (int*)malloc(sizeof(int)*BIG_SIZE);
  permuteFinal(merged,final_text,BIG_SIZE);

  if(DEBUG)
    printf("Encrypted binary: ");
  printArray(final_text,BIG_SIZE);


  free(final_text);
  free(merged);
  free(new_s);
  free(sw);
  free(permuted_sw);
  free(ext_right);
  free(tsw);
  free(K1);
  free(K2);
  free(xored_left);
  free(xored_right);
  free(sss);
  free(result);
  free(toBeXOR);
  free(left);
  free(right);
  free(final_right);
  free(plaintext);
  free(key);
  free(permuted_sss);
  free(sb_right);
  free(sb_left);

  if(MEMORY_LEAKS){
	  printf("free final_text\n");
	  printf("free merged\n");
	  printf("free new_s\n");
	  printf("free sw\n");
	  printf("free permuted_sw\n");
	  printf("free ext_right\n");
	  printf("free tsw\n");
	  printf("free K1\n");
	  printf("free K2\n");
	  printf("free xored_left\n");
	  printf("free xored_right\n");
	  printf("free sss\n");
	  printf("free result\n");
	  printf("free toBeXOR\n");
	  printf("free left\n");
	  printf("free Right\n");
	  printf("free final_right\n");
	  printf("free plaintext\n");
	  printf("free key\n");
	  printf("free permuted_sss\n");
	  printf("free sb_left\n");
	  printf("free sb_right\n");
	}
  return 0;
}
