#include <stdio.h>

typedef struct
{
  char *loc;   // location name
  double alt;  // altitude (km)
  double temp; // temperature (centigrade)
} Sample;

int f_dimension()
{
  return 2;
}

double f_value(const double x[])
{
  
  return 0;
}

void f_gradient(const double x[], Sample *cities_p, double g[])
{
  #define N 14
  double x2sum = 0;
  double y2sum = 0;
  double xysum = 0;
  double ysum = 0;
  double xsum = 0;  

  for(int i = 0; i < N; i++){
    x2sum += cities_p[i].alt * cities_p[i].alt;
    y2sum += cities_p[i].temp * cities_p[i].temp;
    xysum += cities_p[i].temp * cities_p[i].alt;
    xsum += cities_p[i].alt;
    ysum += cities_p[i].temp;
  }

  g[0] = 2*x2sum*x[0] - 2*xysum + 2*xsum*x[1];
  g[1] = -2*ysum + 2*xsum*x[0] + 2*N*x[1];
  
}
