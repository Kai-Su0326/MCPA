
#include "mon.h"
#include<stdio.h>
int main(int argc, char* argv[])
{
  // This is the example code that was used to generate sample.mon
  // It could be written much more nicely using create_left and create_right
  Element z = { .name = "zebra", .left_child = NULL, .right_child = NULL };
  Element y = { .name = "yak", .left_child = NULL, .right_child = NULL };
  Element x = { .name = "xylophone", .left_child = NULL, .right_child = NULL };
  Element b = { .name = "baboon", .left_child = &x, .right_child = &y };
  Element a = { .name = "aardvark", .left_child = &b, .right_child = &z };

  FILE* fr = fopen("sample.mon", "r");
  //write_tree(f, &a);
  FILE* f = fopen("test_write.txt", "w");
  //write_tree(f, &a);
  write_tree(f,load_tree(fr));
  fclose(f);
  free_tree(load_tree(fr)); 
  return 0; 
}

