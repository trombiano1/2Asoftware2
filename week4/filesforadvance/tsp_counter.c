#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <errno.h> // strtol のエラー判定用

// 町の構造体（今回は2次元座標）を定義
typedef struct
{
  int x;
  int y;
} City;

// 描画用
typedef struct
{
  int width;
  int height;
  char **dot;
} Map;

// 整数最大値をとる関数
int max(const int a, const int b)
{
  return (a > b) ? a : b;
}

// プロトタイプ宣言
// draw_line: 町の間を線で結ぶ
// draw_route: routeでの巡回順を元に移動経路を線で結ぶ
// plot_cities: 描画する
// distance: 2地点間の距離を計算
// solve(): TSPをといて距離を返す/ 引数route に巡回順を格納

void draw_line(Map map, City a, City b);
void draw_route(Map map, City *city, int n, const int *route);
void plot_cities(FILE* fp, Map map, City *city, int n, const int *route);
double distance(City a, City b);
double solve(const City *city, int n, int *route, int *visited, int q);
Map init_map(const int width, const int height);
void free_map_dot(Map m);
City *load_cities(const char* filename,int *n);
int factorial(int n);

Map init_map(const int width, const int height)
{
  char **dot = (char**) malloc(width * sizeof(char*));
  char *tmp = (char*)malloc(width*height*sizeof(char));
  for (int i = 0 ; i < width ; i++)
    dot[i] = tmp + i * height;
  return (Map){.width = width, .height = height, .dot = dot};
}
void free_map_dot(Map m)
{
  free(m.dot[0]);
  free(m.dot);
}

City *load_cities(const char *filename, int *n)
{
  City *city;
  FILE *fp;
  if ((fp=fopen(filename,"rb")) == NULL){
    fprintf(stderr, "%s: cannot open file.\n",filename);
    exit(1);
  }
  fread(n,sizeof(int),1,fp);
  city = (City*)malloc(sizeof(City) * *n);
  for (int i = 0 ; i < *n ; i++){
    fread(&city[i].x, sizeof(int), 1, fp);
    fread(&city[i].y, sizeof(int), 1, fp);
  }
  fclose(fp);
  return city;
}
int main(int argc, char**argv)
{

  srand((unsigned int)time(NULL));
  // const による定数定義
  const int width = 70;
  const int height = 40;
  const int max_cities = 100;
  double probab = 0;

  Map map = init_map(width, height);
  
  FILE *fp = stdout; // とりあえず描画先は標準出力としておく
  if (argc != 2){
    fprintf(stderr, "Usage: %s <city file>\n", argv[0]);
    exit(1);
  }
  int n = 20;
  assert( n > 1 && n <= max_cities); // さすがに都市数100は厳しいので

  City *city = load_cities(argv[1],&n);

  // 町の初期配置を表示
  plot_cities(fp, map, city, n, NULL);
  sleep(1);

  // 訪れる順序を記録する配列を設定
  int *route = (int*)calloc(n, sizeof(int));
  // 訪れた町を記録するフラグ
  int *visited = (int*)calloc(n, sizeof(int));

  for(int q = 1; q < 100; q++){
    const double d = solve(city,n,route,visited,q);
    printf("%d:%f\n",q,d);
    if(d < 155.7172){
      probab++;
    }
  }
    
  printf("probability:%f\n",probab/100);
  /* for (int i = 0 ; i < n ; i++){ */
  /*   printf("%d -> ", route[i]); */
  /* } */
  /* printf("0\n"); */

  // 動的確保した環境ではfreeをする
  free(route);
  free(visited);
  free(city);
  
  return 0;
}

// 繋がっている都市間に線を引く
void draw_line(Map map, City a, City b)
{
  const int n = max(abs(a.x - b.x), abs(a.y - b.y));
  for (int i = 1 ; i <= n ; i++){
    const int x = a.x + i * (b.x - a.x) / n;
    const int y = a.y + i * (b.y - a.y) / n;
    if (map.dot[x][y] == ' ') map.dot[x][y] = '*';
  }
}

void draw_route(Map map, City *city, int n, const int *route)
{
  if (route == NULL) return;

  for (int i = 0; i < n; i++) {
    const int c0 = route[i];
    const int c1 = route[(i+1)%n];// n は 0に戻る必要あり
    draw_line(map, city[c0], city[c1]);
  }
}

void plot_cities(FILE *fp, Map map, City *city, int n, const int *route)
{
  fprintf(fp, "----------\n");

  memset(map.dot[0], ' ', map.width * map.height); 

  // 町のみ番号付きでプロットする
  for (int i = 0; i < n; i++) {
    char buf[100];
    sprintf(buf, "C_%d", i);
    for (int j = 0; j < strlen(buf); j++) {
      const int x = city[i].x + j;
      const int y = city[i].y;
      map.dot[x][y] = buf[j];
    }
  }

  draw_route(map, city, n, route);

  for (int y = 0; y < map.height; y++) {
    for (int x = 0; x < map.width; x++) {
      const char c = map.dot[x][y];
      fputc(c, fp);
    }
    fputc('\n', fp);
  }
  fflush(fp);
}

double distance(City a, City b)
{
  const double dx = a.x - b.x;
  const double dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

double solve(const City *city, int n, int *route, int *visited, int q)
{
  // 以下はとりあえずダミー。ここに探索プログラムを実装する
  // 現状は町の番号順のルートを回っているだけ
  // 実際は再帰的に探索して、組み合わせが膨大になる。
  const int tries = 4000;
  int *best_routes = (int*)calloc(tries, sizeof(int)*n);
  int temp_route[n];
  double  best_routes_sum_d[tries];
  for(int i = 0; i < tries; ++i){
    best_routes_sum_d[i] = 0.0;
  }
  double sum_d = 0;
  int visited_copy[n];
  int temp = 0;
  int the_flag = 0;
  
  for(int a = 0; a < tries; ++a){
    srand(a*q*(unsigned)time( NULL ));
    for(int k = 0; k < n; ++k){
      visited_copy[k] = visited[k];
    }

    // ランダムで生成
    route[0] = 0; // 循環した結果を避けるため、常に0番目からスタート
    visited_copy[0] = 1;
    for (int i = 0 ; i < n ; i++){
      route[i] = i;
      visited_copy[i] = 1; // 訪問済みかチェック
    }

    for(int o = 1; o < n; o++) {
        int p = rand()%n;
        int q = route[o];
	if(p != 0){
	  route[o] = route[p];
	  route[p] = q;
	}
    }
    
    for(int c = 0; c < n; ++c){
      temp_route[c] = route[c];
    }

    
    // トータルの巡回距離を計算する
    // 実際には再帰の末尾で計算することになる
    sum_d = 0;
    for (int i = 0 ; i < n ; i++){
      const int c0 = temp_route[i];
      const int c1 = temp_route[(i+1)%n]; // nは0に戻る
      sum_d += distance(city[c0],city[c1]);
    }

    /* printf("random: %d", temp_route[0]); */
    /* for(int j = 1; j < n; ++j){ */
    /*   printf(" -> %d",temp_route[j]); */
    /* } */
    /* printf("\n"); */

    best_routes_sum_d[a] = sum_d;
    for(int b = 0; b < n; ++b){
      best_routes[a*n + b] = temp_route[b];
    }

    while(1){
      the_flag = 0;
      for(int j = 1; j < n; ++j){
	//ここで置き換えを作る
	for(int p = j+1; p < n; ++p){
	  for(int c = 0; c < n; ++c){
	    temp_route[c] = best_routes[a*n + c];
	  }
	  temp = temp_route[p];
	  temp_route[p] = temp_route[j];
	  temp_route[j] = temp;
	  
	  // トータルの巡回距離を計算する
	  // 実際には再帰の末尾で計算することになる
	  sum_d = 0;
	  for (int i = 0 ; i < n ; i++){
	    const int c0 = temp_route[i];
	    const int c1 = temp_route[(i+1)%n]; // nは0に戻る
	    sum_d += distance(city[c0],city[c1]);
	  }
	  
	  /* printf("%d", temp_route[0]); */
	  /* for(int j = 1; j < n; ++j){ */
	  /*   printf(" -> %d",temp_route[j]); */
	  /* } */
	  /* printf("\n"); */
	  
	  //もしsum_dが今回のやつより小さかったら書き換える
	  if(sum_d < best_routes_sum_d[a] || best_routes_sum_d[a] == 0.0){
	    best_routes_sum_d[a] = sum_d;
	    for(int b = 0; b < n; ++b){
	      the_flag = 1;
	      best_routes[a*n + b] = temp_route[b];
	    }
	  }
	}
      }
      if(the_flag == 0){
	break;
      }
    }
  }
  
  /* for(int i = 0; i < tries; ++i){ */
  /*   printf("HERE1"); */
  /*   printf("i:%d, tries:%d\n",i,tries); */
  /*   printf("%f\n",best_routes_sum_d[i]); */
  /*   printf("%d ", best_routes[i*n]); */
  /*   for(int j = 1; j < n; ++j){ */
  /*     printf("->%d",best_routes[i*n + j]); */
  /*   } */
  /* } */

  double min_sum = best_routes_sum_d[0];
  for(int j=0; j < n; ++j){
    route[j] = best_routes[j];
  }
  
  for(int i = 0; i < tries; ++i){
    if(best_routes_sum_d[i] < min_sum){
      min_sum = best_routes_sum_d[i];
      for(int j = 0; j < n; ++j){
	route[j] = best_routes[i*n + j];
      }
    }
  }
  sum_d = min_sum;

  free(best_routes);
  
  //ここで最後にbest_routesの中の最後を決める
  return sum_d;
}
