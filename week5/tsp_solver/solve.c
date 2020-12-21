#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"
#include "solve.h"
#include <math.h>

static Answer search(const City *city, int n, int *route, int *visited){
  static double mindis = 10000000000;
  int start = 0;
  double cum_dis = 0;
  // 訪問した個数を数える
  int c0 = route[0];
  for (int i = 1; i < n ; i++){
    if (!route[i]){
      start = i;
      break;
    }
    else{
      int c1 = route[i];
      cum_dis += distance(city[c0],city[c1]);
      c0 = c1;
    }
  }
  // 全て訪問したケース（ここが再帰の終端条件）
  if (start == 0){
    double sum_d = cum_dis + distance(city[c0],city[0]);
    int *retarg = (int*)malloc(sizeof(int)*n);
    memcpy(retarg, route, sizeof(int)*n);
    if ( sum_d < mindis) mindis = sum_d; 
    return (Answer){.dist = sum_d, .route = retarg};
  }


  // 特定の分岐における最小の巡回経路を調べる
  Answer min = {.dist = 10000000000, .route = NULL};
  for (int i = 1 ; i < n ; i++){
    // 未訪問なら訪れる
    if(!visited[i]){
      if(i == 2 && !visited[1]) continue; // 逆順の巡回経路を抑制

      if ( cum_dis + distance(city[route[start-1]],city[i]) > mindis) continue;
      
      route[start] = i; 
      visited[i] = 1;

      Answer tmp = search(city, n, route, visited);

      // 最小の巡回経路かどうか確認
      if ( tmp.dist < min.dist ){
	free(min.route);
	min = tmp;
      }
      else{
	free(tmp.route);
      }

      route[start] = 0;
      visited[i] = 0;
    }
  }
  
  return min;
}

double solve(const City *city, int n, int *route, int *visited)
{
  route[0] = 0; // 循環した結果を避けるため、常に0番目からスタート
  visited[0] = 1;

  Answer ans = search(city, n, route, visited);
  
  memcpy(route, ans.route, sizeof(int)*n);
  free(ans.route);
  return ans.dist;
}
