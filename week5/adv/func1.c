#include <stdio.h>

typedef struct
{
  char *loc;   // location name
  double alt;  // altitude (km)
  double temp; // temperature (centigrade)
  double lat;
  double lon;
} Sample;

int f_dimension()
{
  return 4;
}

double f_value(const double x[])
{
  return 0;
}

void f_gradient(const double x[], Sample *cities_p, double g[])
{
  #define N 14

  double tempsum = 0;
  double tempaltsum = 0;
  double templatsum = 0;
  double templonsum = 0;
  double altsum = 0;
  double latsum = 0;
  double lonsum = 0;
  double alt2sum = 0;
  double lat2sum = 0;
  double lon2sum = 0;
  double altlatsum = 0;
  double latlonsum = 0;
  double altlonsum = 0;

  for(int i = 0; i < N; ++i){
    tempsum += cities_p[i].temp;
    tempaltsum += cities_p[i].temp*cities_p[i].alt;
    templatsum += cities_p[i].temp*cities_p[i].lat;
    templonsum += cities_p[i].temp*cities_p[i].lon;
    altsum += cities_p[i].alt;
    latsum += cities_p[i].lat;
    lonsum += cities_p[i].lon;
    alt2sum += cities_p[i].alt * cities_p[i].alt;
    lat2sum += cities_p[i].lat * cities_p[i].lat;
    lon2sum += cities_p[i].lon * cities_p[i].lon;
    altlatsum += cities_p[i].alt * cities_p[i].lat;
    latlonsum += cities_p[i].lat * cities_p[i].lon;
    altlonsum += cities_p[i].alt * cities_p[i].lon;
  }
  
  
  g[0] = -2*tempsum + 2*x[0] + 2*x[1]*altsum + 2*x[2]*latsum + 2*x[3]*lonsum;
  g[1] = -2*tempaltsum + 2*x[1]*alt2sum + 2*x[0]*altsum + 2*x[2]*altlatsum + 2*x[3]*altlonsum;
  g[2] = -2*templatsum + 2*x[2]*lat2sum + 2*x[3]*latlonsum + 2*x[0]*latsum + 2*x[1]*altlatsum;
  g[3] = -2*templonsum + 2*x[3]*lon2sum + 2*x[2]*latlonsum + 2*x[0]*lonsum + 2*x[1]*altlonsum;
  
}
