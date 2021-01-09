#include <stdio.h>
#include <stdlib.h>
#include "encode.h"

int main(int argc, char **argv)
{
  if (argc != 3) {
    fprintf(stderr, "usage: %s <input filename> <output filename>\n",argv[0]);
    exit(1);
  }

  encode(argv[1],argv[2]);

  return EXIT_SUCCESS;
}
