#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "encode.h"


// 各シンボルの数を数える為にポインタを定義
// 数を数える為に、1byteの上限+1で設定しておく
static const int nsymbols = 256 + 1; 
//int symbol_count[nsymbols];
int * symbol_count;

// ノードを表す構造体
typedef struct node
{
  int symbol;
  int count;
  char code[20];
  struct node *left;
  struct node *right;
} Node;

// このソースで有効なstatic関数のプロトタイプ宣言
// 一方で、ヘッダファイルは外部からの参照を許す関数の宣言のみ


// ファイルを読み込み、static配列の値を更新する関数
static void count_symbols(const char *filename);

// 与えられた引数でNode構造体を作成し、そのアドレスを返す関数
static Node *create_node(int symbol, int count, Node *left, Node *right);

// Node構造体へのポインタが並んだ配列から、最小カウントを持つ構造体をポップしてくる関数
// n は 配列の実効的な長さを格納する変数を指している（popするたびに更新される）
static Node *pop_min(int *n, Node *nodep[]);

// ハフマン木を構成する関数（根となる構造体へのポインタを返す）
static Node *build_tree(void);

// 木を深さ優先で操作する関数
static void traverse_tree(const int depth, Node *np, char *code);

static void count_symbols(const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    fprintf(stderr, "error: cannot open %s\n", filename);
    exit(1);
  }

  symbol_count = (int*)calloc(nsymbols, sizeof(int));
  
  // 以下がカウント用
  int c;
  while( ( c = fgetc(fp)) != EOF ){
    symbol_count[c]++;
  }

  fclose(fp);
}

static Node *create_node(int symbol, int count, Node *left, Node *right)
{
  Node *ret = (Node *)malloc(sizeof(Node));
  *ret = (Node){ .symbol = symbol, .count = count, .left = left, .right = right};
  return ret;
}

static Node *pop_min(int *n, Node *nodep[])
{
  // Find the node with the smallest count
  // カウントが最小のノードを見つけてくる
  int argmin = 0;
  for (int i = 0; i < *n; i++) {
    if (nodep[i]->count < nodep[argmin]->count) {
      argmin = i;
    }
  }

  Node *node_min = nodep[argmin];

  // Remove the node pointer from nodep[]
  // 見つかったノード以降の配列を前につめていく
  for (int i = argmin; i < (*n) - 1; i++) {
    nodep[i] = nodep[i + 1];
  }
  // 合計ノード数を一つ減らす
  (*n)--;

  return node_min;
}

static Node *build_tree()
{
  int n = 0;
  Node *nodep[nsymbols];

  for (int i = 0; i < nsymbols; i++) {
    // カウントの存在しなかったシンボルには何もしない
    if (symbol_count[i] == 0) continue;

    // 以下は nodep[n++] = create_node(i, symbol_count[i], NULL, NULL); と1行でもよい
    nodep[n] = create_node(i, symbol_count[i], NULL, NULL);
    n++;
  }

  const int dummy = -1; // ダミー用のsymbol を用意しておく
  while (n >= 2) {
    Node *node1 = pop_min(&n, nodep); //left
    Node *node2 = pop_min(&n, nodep); //right
    nodep[n++] = create_node(dummy, node1->count + node2->count, node1, node2);
  }
  // 気にした後は symbol_counts は free
  free(symbol_count);
  return (n==0)?NULL:nodep[0];
}

// Perform depth-first traversal of the tree
// 深さ優先で木を走査する
// 現状は何もしていない（再帰してたどっているだけ）
static void traverse_tree(const int depth, Node *np, char *code)
{
  strcpy(np->code,code);
  char str1[30];
  char str2[30];
  strcpy(str1,np->code);
  strcpy(str2,np->code);
  if (np->left == NULL){
    printf("  ");
    for(int i = 0; i < depth-1; i++){
      if(np->code[i] == '0'){
	printf("  ");
      }else{
	printf("│ ");
      }
    }
    if(np->code[strlen(np->code)-1] == '1'){
      if(np->symbol == 10){
	printf("├─ \\n:%s(%d)\n",np->code,np->count);
      }else{
	printf("├─ %c:%s(%d)\n",np->symbol,np->code,np->count);
      }
    } else {
      printf("└─ %c:%s(%d)\n",np->symbol,np->code,np->count);
    }
    return;
  }
  if(np->code[strlen(np->code)-1] == '0' || np->code[strlen(np->code)-1] == '1'){
    printf("  ");
    for(int i = 0; i < depth-1; i++){
      if(np->code[i] == '0'){
	printf("  ");
      }else{
	printf("│ ");
      }
    }
  }
  /* printf("% code:%s\n",np->symbol,np->code); */
  if(np->code[strlen(np->code)-1] == '1'){
    printf("├─┐\n");
  } else if (np->code[strlen(np->code)-1] == '0'){
    printf("└─┐\n");
  }
  traverse_tree(depth + 1, np->left, strcat(str1,"1"));
  traverse_tree(depth + 1, np->right, strcat(str2,"0"));
}

// この関数のみ外部 (main) で使用される (staticがついていない)
int encode(const char *filename)
{
  count_symbols(filename);
  Node *root = build_tree();

  if (root == NULL){
    fprintf(stderr,"A tree has not been constructed.\n");
    return EXIT_FAILURE;
  }
  
  traverse_tree(0, root, "");
  return EXIT_SUCCESS;
}
