#ifndef TSP_PLOT_H
#define TSP_PLOT_H

#include "city.h"

// 描画用
typedef struct
{
  int width;
  int height;
  char **dot;
} Map;

void draw_line(Map map, City a, City b);
void draw_route(Map map, City *city, int n, const int *route);
void plot_cities(FILE* fp, Map map, City *city, int n, const int *route);

Map init_map(const int width, const int height);
void free_map_dot(Map m);

#endif
