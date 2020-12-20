#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// シミュレーション条件を格納する構造体
// 反発係数CORを追加
typedef struct condition
{
  const int width; // 見えている範囲の幅
  const int height; // 見えている範囲の高さ
  const double G; // 重力定数
  const double dt; // シミュレーションの時間幅
  const double cor; // 壁の反発係数
} Condition;

// 個々の物体を表す構造体
typedef struct object
{
  double m;
  double y;
  double x;
  double prev_y; // 壁からの反発に使用
  double prev_x;
  double vy;
  double vx;
} Object;

double distance(Object objs[], int m, int n){
  return sqrt((objs[m].x - objs[n].x)*(objs[m].x - objs[n].x)+(objs[m].y - objs[n].y)*(objs[m].y - objs[n].y));
}

void my_plot_objects(Object objs[], const size_t numobj, const double t, const Condition cond){
  FILE *fp = stdout;

  /*information*/
  for(size_t i = 0; i < numobj; ++i){
    printf("t = \t%f, objs[%zu]: (x,y) = (%f,%f), (vx,vy) = (%f,%f)\n",t,i,objs[i].x,objs[i].y,objs[i].vx,objs[i].vy);
  }
  /*上の壁*/
  fprintf(fp,"+");
  for (int x = 0 ; x < cond.width ; x++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");

  int print_flag = 0;
  
  /* 外壁と 内側のゲーム部分 */
  for (int y = 0; y < cond.height; y++) {
    fprintf(fp,"|");
    for (int x = 0; x < cond.width; x++) {
      print_flag = 0;
      // ANSIエスケープコードを用いて、赤い"#" を表示
      // \e[31m で 赤色に変更
      // \e[0m でリセット（リセットしないと以降も赤くなる）
      for(size_t i = 0; i < numobj; ++i){
	if((int)objs[i].y+(cond.height/2) == y && (int)objs[i].x+(cond.width/2) == x){ 
	  print_flag = 1;
	}
      }
      if(print_flag){
	fprintf(fp, "o");
      }else{ 
	fprintf(fp, " ");
      }
    }
    fprintf(fp,"|\n");
  }

  /*下の壁*/
  fprintf(fp, "+");
  for (int x = 0 ; x < cond.width ; x++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");
  
  fflush(fp);
}

void my_update_velocities(Object objs[], const size_t numobj, const Condition cond){
  double a_y;
  double a_x;
  for(size_t i = 0; i < numobj; ++i){
    a_y = 0.0;
    a_x = 0.0;
    for(size_t j = 0; j < numobj; ++j){
      if(i != j){
	a_x += (cond.G * (objs[j].m) / (pow(distance(objs, i, j),3)))*(objs[j].x-objs[i].x);
	a_y += (cond.G * (objs[j].m) / (pow(distance(objs, i, j),3)))*(objs[j].y-objs[i].y);
      }
    }
    objs[i].vy += a_y * cond.dt;
    objs[i].vx += a_x * cond.dt;
  }
}

void my_update_positions(Object objs[], const size_t numobj, const Condition cond){
  for(size_t i = 0; i < numobj; ++i){
    objs[i].prev_y = objs[i].y;
    objs[i].y += objs[i].vy * cond.dt;
    objs[i].prev_x = objs[i].x;
    objs[i].x += objs[i].vx * cond.dt;
  }
}

void my_bounce(Object objs[], const size_t numobj, const Condition cond){
  for(size_t i = 0; i < numobj; ++i){
    if((cond.height / 2 > objs[i].prev_y) && (objs[i].y > cond.height / 2)){ //下の壁
      objs[i].vy = -1 * objs[i].vy * cond.cor;
      objs[i].y = -1 * (objs[i].y - cond.height/2) + cond.height/2;
    }
    if((-1 * cond.height / 2 < objs[i].prev_y) && (objs[i].y < -1 * cond.height / 2)){ //上の壁
      objs[i].vy = -1 * objs[i].vy * cond.cor;
      objs[i].y = (-1 * cond.height/2 - objs[i].y) - cond.height/2;
    }
    if((cond.width / 2 > objs[i].prev_x) && (objs[i].x > cond.width / 2)){ //下の壁
      objs[i].vx = -1 * objs[i].vx * cond.cor;
      objs[i].x = -1 * (objs[i].x - cond.width/2) + cond.width/2;
    }
    if((-1 * cond.width / 2 < objs[i].prev_x) && (objs[i].x < -1 * cond.width / 2)){ //上の壁
      objs[i].vx = -1 * objs[i].vx * cond.cor;
      objs[i].x = (-1 * cond.width/2 - objs[i].x) - cond.width/2;
    }
  }
}

int main(int argc, char **argv)
{
  const Condition cond = {
		    .width  = 75,
		    .height = 40,
		    .G = 1.0,
		    .dt = 1.0,
		    .cor = 0.8
  };
  
  size_t objnum = 2;
  Object objects[objnum];

  // objects[1] は巨大な物体を画面外に... 地球のようなものを想定
  objects[0] = (Object){ .m = 60.0, .x = 0.0, .y = -19.9, .vx = 0.0, .vy = 2.0};
  objects[1] = (Object){ .m = 60.0, .x = 0.0, .y = 19.9, .vx = 10.0, .vy = 2.0};
  /* objects[1] = (Object){ .m = 100000.0, .x = 500.0, .y =  1000.0, .vx = 0.0, .vy = 0.0}; */
  /* objects[2] = (Object){ .m = 60.0, .y = 0, .vy = 2.0}; */

  // シミュレーション. ループは整数で回しつつ、実数時間も更新する
  const double stop_time = 400;
  double t = 0;
  printf("\n");
  for (int i = 0 ; t <= stop_time ; i++){
    t = i * cond.dt;
    my_update_velocities(objects, objnum, cond);
    my_update_positions(objects, objnum, cond);
    my_bounce(objects, objnum, cond);
    
    // 表示の座標系は width/2, height/2 のピクセル位置が原点となるようにする
    my_plot_objects(objects, objnum, t, cond);
    usleep(200 * 1000); // 200 x 1000us = 200 ms ずつ停止
    printf("\e[%dA", cond.height+4);// 壁とパラメータ表示分で3行
  }
  return EXIT_SUCCESS;
}

// 実習: 以下に my_ で始まる関数を実装する
// 最終的に phisics2.h 内の事前に用意された関数プロトタイプをコメントアウト
