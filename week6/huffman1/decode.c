#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

long long int getFileSize(const char* fileName)
{
    FILE* fp = fopen(fileName, "rb");
    if (fp == NULL) {
        return -1LL;
    }

    if (fseek(fp, 0L, SEEK_END) == 0) {
        fpos_t pos;

        if (fgetpos(fp, &pos) == 0) {
            fclose(fp);
            return (long long int)pos;
        }
    }

    fclose(fp);
    return -1LL;
}

//courtesy of https://programming-place.net/ppp/contents/c/rev_res/file005.html#way1

int main(int argc, char **argv){
  FILE * fp = NULL;
  long long int the_filesize;
  the_filesize = getFileSize(argv[1]);
  
  /* unsigned char byte[100000]; */
  unsigned char *byte;
  byte = (unsigned char*)malloc(the_filesize);

  //  バイナリファイルの読み込みでオープン
  fp = fopen(argv[1], "rb");

  //  ファイルからの読み込み
  fread(byte, sizeof(unsigned char), the_filesize, fp);

  //  読み込んだデータを画面に表示
  int binary[8];
  char *entire_text;
  entire_text = (char*)malloc(the_filesize*8);

  /* for(int p = 0; p < 1000000; p++){ */
  /*   entire_text[p] = '+'; */
  /* } */

  //table読み取り
  char number[2];
  char code[32];
  char code1[16];
  char code2[16];
  int tokenlength = 0;

  char * token = "";
  char entirecode[127*2*16];

  int character_length = 127;
  for(int i = 0; i < character_length; i++){
    strcpy(code1, "");
    strcpy(code2, "");
    for(int n = 0; n < 8; n++)
      binary[7-n] = (byte[2*i] >> n) & 1;
    for(int n = 0; n < 8; n++){
      sprintf(number,"%d",binary[n]);
      strcat(code1,number);
    }
    for(int n = 0; n < 8; n++)
      binary[7-n] = (byte[2*i+1] >> n) & 1;
    for(int n = 0; n < 8; n++){
      sprintf(number,"%d",binary[n]);
      strcat(code2,number);
    }
    strcpy(code,"");
    strcat(code,code1);
    strcat(code,code2);
    token = strtok(code,"1");
    token = strtok(NULL,"");
    if(!token){
      tokenlength = 0;
    } else {
      tokenlength = strlen(token);
    }
    for(unsigned int j = 0; j < tokenlength;j++){
      entirecode[2*i*8+j] = token[j];
    }
    entirecode[2*i*8+tokenlength] = 'k';
  }
  
  char scanning_text[32];
  
  for(int i = character_length*2; i < the_filesize; i++){
   for(int n = 0; n < 8; n++)
      binary[7-n] = (byte[i] >> n) & 1;
    for(int n = 0; n < 8; n++){
      sprintf(number,"%d",binary[n]);
      strcat(entire_text,number);
    }
  }

  int counter = 0;
  int scanner_counter = 0;
  strcpy(scanning_text,"");
  for(int p = 0; p < 16; p++){
    scanning_text[p] = '-';
  }
  int flag = 0;
  while(1){
    flag = 1;
    scanning_text[scanner_counter] = entire_text[counter];
    scanning_text[scanner_counter + 1] = 'k';
    for(int q = 0; q < character_length; q++){
      flag = 1;
      for(int p = 0; p < scanner_counter+2; p++){
	if(entirecode[q*16+p] != scanning_text[p]){
	  flag = 0;
	  break;
	}
      }
      if(flag == 1){
	printf("%c",q);
	scanner_counter = -1;
	break;
      }
    }
    scanner_counter++;
    counter++;
    if(scanner_counter>15){
      printf("\n");
      break;
    }
  }

  fclose(fp);
  free(byte);
  free(entire_text);

  return 0;
}
