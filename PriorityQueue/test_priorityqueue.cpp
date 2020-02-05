#include "priorityqueue.h"
#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

/*void* multi_push(PriorityQueue<int>* hp)
{
	for(int i = 0; i < 10000; i++)
	{
		hp->push(i);
	}
	return NULL;
}
void* multi_pop(PriorityQueue<int>* hp)
{
	for(int i = 0; i < 9000; i++)
	{
		hp->pop();
	}
	return NULL;
}
*/		
int main(int argc, char* argv[])
{
  // Here's some quick test code to get you started.  You'll need much more
  // thorough testing, of course.
 /* pthread_t read;
  pthread_t write1;
  pthread_t write2;
*/
  PriorityQueue<int> q;
/*
  PriorityQueue<int> qq = q;
  PriorityQueue<int>* qp = &qq;
  pthread_mutex_init(&wr_lock,NULL);
  pthread_create(&write1,NULL,multi_push,&qq);
  pthread_create(&write2,NULL,multi_pop,&qq);
*/
  // Push three elements onto the front
 /* q.push(1);
  q.push(2);
  q.push(3);
  // Make a copy
  PriorityQueue<int> another = q;
  // Push some more elements onto the front of the original
  q.push(4);
  q.push(5);*/
 
//for(int i=0;i<q.size();i++)
//	printf("%d ", q[i]);
 /* while(q.size() > 0){
    printf("%d ", q.top());
    q.pop();
  }*/
 // printf("\n");

 /* while(another.size() > 0){
    printf("%d ", another.top());
    another.pop();
  }*/
  //printf("\n"); 
	for(int i=0;i<10;i++)
	{
		q.push(i);
                std::cout<<q[0]<<std::endl;
	}
		cout<<endl;	
	while(q.size()>0){
		cout<<"size():"<<q.size()<<endl;
		q.pop();
		std::cout<<q[0]<<std::endl;
        }
	//printf("%d ", q.top());
/*
  pthread_join(write1,NULL);
  pthread_join(write2,NULL);
  pthread_mutex_destroy(&wr_lock);
*/
  return(0);
}
