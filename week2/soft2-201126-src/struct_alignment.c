#include <stdio.h>

struct student
{
  int id;
  char name[100];
  int age;
  double height;
  double weight;
};

struct tagged_student1
{
  int id;
  char name[100];
  int age;
  double height;
  double weight;
  char tag;
};

struct tagged_student2
{
  char tag;
  int id;
  char name[100];
  int age;
  double height;
  double weight;
};

void student_printpointers(struct student *the_pointer){
  printf("id(int):\t%p\n",&((*the_pointer).id));
  printf("name(char):\t%p\n",&((*the_pointer).name));
  printf("age(int):\t%p\n",&((*the_pointer).age));
  printf("height(double):\t%p\n",&((*the_pointer).height));
  printf("weight(double):\t%p\n",&((*the_pointer).weight));
  printf("size:\t%zu\n\n",sizeof(*the_pointer));
  
}

void tagged_student1_printpointers(struct tagged_student1 *the_pointer){
  printf("id(int):\t%p\n",&((*the_pointer).id));
  printf("name:(char)\t%p\n",&((*the_pointer).name));
  printf("age:(double)\t%p\n",&((*the_pointer).age));
  printf("height(double):\t%p\n",&((*the_pointer).height));
  printf("weight(double):\t%p\n",&((*the_pointer).weight));
  printf("tag(char):\t%p\n",&((*the_pointer).tag));
  printf("size:\t%zu\n\n",sizeof(*the_pointer));
}


void tagged_student2_printpointers(struct tagged_student2 *the_pointer){
  printf("tag(char):\t%p\n",&((*the_pointer).tag));
  printf("id(int):\t%p\n",&((*the_pointer).id));
  printf("name:(char)\t%p\n",&((*the_pointer).name));
  printf("age(int):\t%p\n",&((*the_pointer).age));
  printf("height(double):\t%p\n",&((*the_pointer).height));
  printf("weight(double):\t%p\n",&((*the_pointer).weight));
  printf("size:\t%zu\n\n",sizeof(*the_pointer));
}

int main (int argc, char**argv)
{
  struct student s_begin;
  struct student s1;
  struct tagged_student1 s2;
  struct tagged_student2 s3;
  struct tagged_student2 s_end;


  struct student *s_begin_p = &(s_begin);
  struct student *s1_p = &(s1);
  struct tagged_student1 *s2_p = &(s2);
  struct tagged_student2 *s3_p = &(s3);
  struct tagged_student2 *s_end_p = &(s_end);
  
  
  /* 以下に各構造体の中身のポインタを表示するプログラムを書く */
  /* printf で %p フォーマットを指定する*/
  /* 逆順に表示（send, s3, s2, s1, sbegin の順）*/

  tagged_student2_printpointers(s_end_p);
  tagged_student2_printpointers(s3_p);
  tagged_student1_printpointers(s2_p);
  student_printpointers(s1_p);
  student_printpointers(s_begin_p);
  

  /* 以下には各構造体のサイズをsizeof演算子で計算し、表示する */
  /* printf 表示には%ld を用いる*/

  // do_something!!
  
  return 0;
}

