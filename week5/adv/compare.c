#include <stdio.h>
#include "func1.h"

int compare_samples(const void * n1, const void * n2){
  if(((Sample *)n1)->alt > ((Sample *)n2)->alt){
    return 1;
  } else if (((Sample *)n1)->alt < ((Sample *)n2)->alt){
    return -1;    
  } else {
    return 0;
  }
};
