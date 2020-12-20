#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep()関数を使う
#include <string.h>

void my_init_cells(const int height, const int width, int cell[height][width], FILE* fp){
  if(fp == NULL){
    fp = fopen("default.lif","r");
  }
  const size_t bufsize = 500;
  char buf[bufsize];
  while (fgets(buf, bufsize, fp) != NULL) {
    if(buf[0] == '#'){
    } else {
      cell[atoi(buf+2)][atoi(buf)] = 1;
    }
  }
}

void my_print_cells(FILE* fp,int gen, const int height,const int width,int cell[height][width]){
  //上の壁
  fprintf(fp,"generation = %d\n",gen); // この場合 (fp = stdout), printfと同じ
  fprintf(fp,"+");
  for (int x = 0 ; x < width ; x++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");
  
  /* 外壁と 内側のゲーム部分 */
  for (int y = 0; y < height; y++) {
    fprintf(fp,"|");
    for (int x = 0; x < width; x++) {
      // ANSIエスケープコードを用いて、赤い"#" を表示
      // \e[31m で 赤色に変更
      // \e[0m でリセット（リセットしないと以降も赤くなる）
      if(cell[y][x]){
	fprintf(fp, "\e[31m#\e[0m");
      } else {
	fprintf(fp, " ");
      }
    }
    fprintf(fp,"|\n");
  }

  // 下の壁
  fprintf(fp, "+");
  for (int x = 0 ; x < width ; x++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");
  
  fflush(fp); // バッファされている文字列を出力する
}

int my_count_adjacent_cells(int h, int w, const int height, const int width, int cell[height][width]){
  int expanded_cell[height+2][width+2];
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      expanded_cell[i+1][j+1] = cell[i][j];
    }
  }
  int alive_adjacent_cells = 0;
  for(int i = -1; i < 2; ++i){
    for(int j = -1; j < 2; ++j){
      if(expanded_cell[h+1+i][w+1+j] == 1 && !(i == 0 && j == 0)){
	alive_adjacent_cells++;
      }
    }
  }
  return alive_adjacent_cells;
}

void my_update_cells(const int height, const int width, int cell[height][width]){
  int old_cell[height][width];
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      old_cell[i][j] = cell[i][j];
    }
  }
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      if(cell[i][j] == 1){
	if(my_count_adjacent_cells(i, j, height, width, old_cell) == 2 || my_count_adjacent_cells(i, j, height, width, old_cell) == 3){
	  cell[i][j] = 1;
	} else {
	  cell[i][j] = 0;
	}
      }
      if(cell[i][j] == 0){
	if(my_count_adjacent_cells(i, j, height, width, old_cell) == 3){
	  cell[i][j] = 1;
	}
      }
    }
  }
}

int main(int argc, char **argv)
{
  FILE *fp = stdout;
  const int height = 40;
  const int width = 70;

  int cell[height][width];
  for(int y = 0 ; y < height ; y++){
    for(int x = 0 ; x < width ; x++){
      cell[y][x] = 0;
    }
  }

  printf("asdlfasdf\n");
  
  /* ファイルを引数にとるか、ない場合はデフォルトの初期値を使う */
  if ( argc > 2 ) {
    fprintf(stderr, "usage: %s [filename for init]\n", argv[0]);
    return EXIT_FAILURE;
  }
  else if (argc == 2) {
    FILE *lgfile;
    if ( (lgfile = fopen(argv[1],"r")) != NULL ) {
      my_init_cells(height,width,cell,lgfile); // ファイルによる初期化
    }
    else{
      fprintf(stderr,"cannot open file %s\n",argv[1]);
      return EXIT_FAILURE;
    }
    fclose(lgfile);
  }
  else{
    my_init_cells(height, width, cell, NULL); // デフォルトの初期値を使う
  }

  my_print_cells(fp, 0, height, width, cell); // 表示する
  usleep(100000); // 1秒休止
  /* 世代を進める*/
  for (int gen = 1 ;; gen++) {
    my_update_cells(height, width, cell); // セルを更新 
    my_print_cells(fp, gen, height, width, cell); // 表示する
    //    sleep(0.3); //1秒休止する
    usleep(100000);
    fprintf(fp,"\e[%dA",height+3);//height+3 の分、カーソルを上に戻す(壁2、表示部1)
  }

  return EXIT_SUCCESS;
}
