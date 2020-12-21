#ifndef TSP_SOLVE_H
#define TSP_SOLVE_H

typedef struct ans{
  double dist;
  int *route;
} Answer;

double solve(const City *city, int n, int *route, int *visited);

#endif
