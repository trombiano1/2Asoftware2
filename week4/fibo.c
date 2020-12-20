#include <stdio.h>

void calc_matrix(int *a, int n);

int fibo(int n){
  if(n == 1){
    return 1;
  } else {
    int a[4] = {1,1,1,0};
    calc_matrix(a, n-1);
    return a[0];
  }
}

void calc_matrix(int *a, int n){
  int temp[4];
  temp[0] = a[0];
  temp[1] = a[1];
  temp[2] = a[2];
  temp[3] = a[3];
  if(n == 1){
    return;
  }
  if(n % 2 == 0){
    calc_matrix(temp, n/2);
    a[0] = temp[0]*temp[0] + temp[1]*temp[2];
    a[1] = temp[0]*temp[1] + temp[1]*temp[3];
    a[2] = temp[0]*temp[2] + temp[2]*temp[3];
    a[3] = temp[1]*temp[2] + temp[3]*temp[3];
    return;
  } else {
    calc_matrix(temp, (n-1)/2);
    a[0] = (temp[0]*temp[0] + temp[1]*temp[2]) + (temp[0]*temp[1] + temp[1]*temp[3]);
    a[1] = temp[0]*temp[0] + temp[1]*temp[2];
    a[2] = (temp[0]*temp[2] + temp[2]*temp[3]) + (temp[1]*temp[2] + temp[3]*temp[3]);
    a[3] = temp[0]*temp[2] + temp[2]*temp[3];
    return;
  }
}

int main(void){
  for(int i = 1; i <= 10; ++i){
    printf("F(%d)=%d\n",i,fibo(i));
  }
  return 0;
}
