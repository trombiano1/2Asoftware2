#include <stdio.h>
#include <stdlib.h>

//macOS Catalina 10.15.7
//2.8GHz Quad-Core Intel Core i7
//eshell on Emacs Version 27.1

int main(void){
  float f[4];

  // 以下に適切な値を設定する
  f[0] = 1143139122437582505939828736.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000;
  f[1] = 66592994030331831990133719040.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000;
  f[2] = 0.0000000000000000000000000000000109981969793619495785417168125755632059844305155696543964752298627729;
  f[3] = 0.0;

  // "Hello,World\n" と出力してほしい
  printf("%s",(char*)f);
  return 0;
}