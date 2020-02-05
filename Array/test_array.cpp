#include "array.h"
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  // Here's some quick test code to get you started.  You'll need much more
  // thorough testing, of course.

  Array<int> arr(5,10);
//  Array<char> arr(5,'c');    //initialize a Array with template of char
  Array<int> z;
try{
  cout << arr[19] << endl;
}
catch(OutOfBoundsException &exp)
{
  cout<<exp.what()<<endl;
}

  Array<int> y(arr);
//  arr.initialize(10, 5);
  int ret[10] = {1,2,3,4,5,6,7,8,9,0};

  Array<int> rtoo(8,ret);
//  rtoo.initialize(0, 0);
//  for(int i = 0; i < rtoo.size(); i++){
//    printf("rtoo[%d] = %c\n", i, rtoo[i]);
//  };

  for(int i = 0; i < arr.size(); i++){
    arr[i] = 66;
  };
 // *arr.append(777);
  cout << rtoo << endl;
  
  z = y + arr + rtoo;
  z = y + y + y; 
  std::cout<<z.size()<<y.size()<<arr.size()<<rtoo.size()<<std::endl;  
for(int i = 0; i < arr.size(); i++){
    printf(" arr[%d] = %d\n", i, arr[i]);
  };
  for(int i = 0; i<y.size(); i++){
    printf(" y[%d] = %d\n", i, y[i]);
  };
  for(int i = 0; i<rtoo.size(); i++){
    printf(" rtoo[%d] = %d\n", i, rtoo[i]);
  };
  
  int bb = z.size();
  printf("bb = %d\n",bb);
  for(int i = 0; i < bb ; i++){
    printf(" z[%d] = %d\n", i, z[i]);
  };

//  for(int i = 0; i < rtoo.size(); i++){
//    printf("rtoo[%d] = %c\n", i, rtoo[i]);
//  };

//  for(int i = 0; i < z.size(); i++){
  //  printf("z[%d] = %c\n", i, z[i]);
 // };
  //arr.cleanup();
  //rtoo.cleanup();
  return(0);
}
