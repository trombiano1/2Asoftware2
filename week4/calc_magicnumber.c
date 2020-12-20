#include <stdio.h>
//macOS Catalina 10.15.7
//2.8GHz Quad-Core Intel Core i7
//eshell on Emacs Version 27.1
int main(void){

  float f[4];
  f[0] = *(float *)"Hell";
  f[1] = *(float *)"o,Wo";
  f[2] = *(float *)"rld\n";
  f[3] = *(float *)"\0";

  printf("%.100f\n",f[0]);
  printf("%.100f\n",f[1]);
  printf("%.100f\n",f[2]);
  printf("%.100f\n",f[3]);
  
  return 0;
}
