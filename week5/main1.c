#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimize1.h"
#include "func1.h"

int main(const int argc, const char **argv)
{
  // 引数の個数が1の時だけ、alpha に第1引数を採用し、それ以外は0.01
  const double alpha = (argc == 2) ? atof(argv[1]) : 0.01;

  const int dim = f_dimension();

  FILE *fp;
  char buf[14];
  fp = stdout;
  
  FILE *file;
  char row[100];
  char * token;

  Sample cities[14];
  
  file = fopen("data.csv","r");
  int count = 0;
  while(fgets(buf, sizeof(row), file) != NULL){
    token = strtok(buf, ",");
    cities[count].loc = token;
    token = strtok(NULL, ",");
    cities[count].alt = atof(token);
    token = strtok(NULL, ",");
    cities[count].temp = atof(token);
    count++;
  }
  fclose(file);
  
  Sample *cities_p;
  cities_p = cities;
  
  double *x = malloc(dim * sizeof(double));
  
  for (int i = 0; i < dim; i++) {
    x[i] = 0;
  }

  printf("alpha = %f\n", alpha);

  const int iter = optimize(alpha, dim, x, cities_p, f_gradient);
  printf("number of iterations = %d\n", iter);

  printf("asdf");

  free(x);
  return 0;
}
