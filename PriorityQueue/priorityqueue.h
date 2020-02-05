#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<math.h>
#include<thread>
#include<mutex>
using namespace std;
template <class T>
class PriorityQueue{
  // You'll need to fill in the function declarations here, since writing them
  // correctly is half the challenge of some of these functions.  Be careful to
  // give them the same names as specified in the README, and pay special
  // attention to things which should be const, references, or both.
	vector<T> heap;
	int h_size;
	mutex mu;
	int parent(int child);    //parent() function to use child's index as input and output its parent's index
	int left(int parent);    //similar to above
	int right(int parent);
	void swap(T& x,T& y);    //swap two element in the heap by exchanging the values at two spot
	int max(int x,int y);    //inputs arguments are two children's index, return value is the index of the bigger child
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue<T>& x);
	~PriorityQueue() {}
	PriorityQueue<T>& operator=(const PriorityQueue<T>& x);
	T& operator[](int i);    //help me access specific value in the heap
	int size();
	T top();
	void push(T x); 
	void pop();
};

template <class T>
PriorityQueue<T>::PriorityQueue()
{
	h_size = 0;
}

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& x)    //copy constructor
{
	h_size = 0;
	if(heap.size() || x.heap.empty())    //if one of heap is not empty or x is empty, clean up heap
		heap.clear();
	if(x.heap.size())
	{
		for(int i = 0;i < x.heap.size();i++)    //traverse the x.heap and copy the values into this->heap
		{
			heap.push_back(x.heap[i]);
			h_size++;
		}
	}
}

template <class T>
void PriorityQueue<T>::swap(T& x,T& y)
{
	if(x==y)
		return;
        T temp = x;
        x = y;
        y = temp;
        return;
}

template <class T>
int PriorityQueue<T>::max(int x,int y)
{
	if(heap[x] > heap[y])
		return x;
	else
		return y;
}

template <class T>
int PriorityQueue<T>::parent(int child)
{
	int pa = (child - 1)/2;
	return pa;
}

template <class T>
int PriorityQueue<T>::left(int parent)
{
	int lef = 2*parent + 1;
	return lef;
}

template <class T>
int PriorityQueue<T>::right(int parent)
{
	int ri = 2*parent + 2;
	return ri;
}

template <class T>
int PriorityQueue<T>::size()
{
	return h_size;
}

template <class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& x)
{
	h_size = 0;
       	if(heap.size() || x.heap.empty())
               	heap.clear();        
        if(x.heap.size())
        {
        for(int i = 0;i < x.heap.size();i++)
        {
                heap.push_back(x.heap[i]);
                h_size++;
        }
        }
	return *this;
}

template <class T>
T& PriorityQueue<T>::operator[](int i)
{
	return heap[i];
}

template <class T>
T PriorityQueue<T>::top()
{
	return heap[0];
}

template <class T>
void PriorityQueue<T>::push(T x)
{
//	pthread_rwlock_rdlock(&re_lock);
//	pthread_mutex_lock(&wr_lock);
	lock_guard<mutex> wLock(mu);
	heap.push_back(x);
	int x_index = h_size;
	h_size++;
	while(x_index != 0 && heap[x_index] > heap[parent(x_index)]) 	//push new element and update the heap
	{
		swap(heap[x_index],heap[parent(x_index)]);
		x_index = parent(x_index);
	}
//	pthread_mutex_unlock(&wr_lock);
//	pthread_rwlock_unlock(&re_lock);
	return;
}

template <class T>
void PriorityQueue<T>::pop()
{
//	pthread_rwlock_rdlock(&re_lock);
//	pthread_mutex_lock(&wr_lock);
	lock_guard<mutex> wLock(mu);
	if(h_size == 0)
		return;
	swap(heap[0],heap[h_size-1]);
	heap.pop_back();
	h_size--;
	int i = 0;
	int layer =(int)log2((double)h_size);
	while(layer>0)    //the thing is, I need to check if the a parent's have two children or just one. I should not access the second(right) child if there is only one (left) child.
	{
		if(right(i)<h_size && heap[i] < heap[max(left(i),right(i))])    //check if it is the two children case
		{	
			int k = max(left(i),right(i));
			swap(heap[i],heap[max(left(i),right(i))]);
			i = k;
			layer--;
			
		}
		else if(heap[i] < heap[left(i)] && left(i)<h_size)	//check if it is the single left child case
		{
			int t = left(i);
			swap(heap[i],heap[left(i)]);
			i = t;
			layer--;
		}
		else
		{
			layer--;
			continue;
		}
	}
//	pthread_mutex_unlock(&wr_lock);	
//	pthread_rwlock_rdlock(&re_lock);
	return;
}
#endif
