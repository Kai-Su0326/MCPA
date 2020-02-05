#include "linkedlist.h"
#include <cstdio>
#include <stdio.h>
int main(int argc, char* argv[])
{
  // Here's some quick test code to get you started.  You'll need much more
  // thorough testing, of course.

  LinkedList<int> list;

  // Push three elements onto the front
  list.insert(1, 0);

  list.insert(2, 0);

  list.insert(3, 0);
  // Make a copy
  LinkedList<int> another = list;
	printf("list.size():%d\n",list.size());
  // Push some more elements onto the front of the original
  list.insert(4, 0);
  list.insert(5, 0);
	printf("list.size():%d\n",list.size());
  list.remove(2);
  int p[5] = {1,3,5,7,9};
  LinkedList<int> list22(5, p);

  for(int i = 0; i < list22.size(); i++){
    printf(" list22[%d] = %d\n", i, list22.getItem(i));
  }
  for(int i = 0; i < list.size(); i++){
    printf(" list[%d] = %d\n", i, list.getItem(i));
  }
	printf("another.size():%d\n",another.size());
  for(int i = 0; i < another.size(); i++){
    printf("another[%d] = %d\n", i, another.getItem(i));
  }

  return(0);
}
