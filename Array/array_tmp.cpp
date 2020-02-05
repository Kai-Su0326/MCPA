#include <iostream>
#include <stdlib.h>
#include "array.h"
using namespace std;

    void Array::initialize(int size, int val)
    {
        this->cur_size = size;    //give the variable cur_size the value of size
        this->data_size = size;    //give the variable data_size the value of size
        this->arr = (int*)malloc(size * sizeof(int));    //request a space for the arr
        for(int i=0;i<size;i++)    //loop to initiallize all of the elements in the arr
        {
            this->arr[i] = val;
        }
    }

    void Array::cleanup()
    {
      if (arr){  
        free(this->arr);    //free the space where arr is pointing
        arr = NULL;    //let the arr point to nowhere
	this->cur_size = 0;
	this->data_size = 0;
        return; 
      }
    }

    size_t Array::size()    //acquire the size of data_size
    {
        return this->data_size;
    }

    void Array::append(int x)    //(old arr and new arr actually are same pointer pointing different spaces)
    {
        if(data_size == cur_size)    //check if the old arr is full
        {
	    int* temp = (int*)malloc(data_size*sizeof(int));    //request a space to store the old stuff in the arr
            for(int i=0;i<data_size;i++)    //traverse old arr and give all of the old elements to the temp
                {
          	     temp[i] = arr[i];
                };
            arr = (int*)realloc(arr,2*sizeof(int)*(this->data_size));    /*request a new space for the new arr that is two times big as the old one*/
            this->cur_size = this->data_size * 2;    //renew the current space size of arr
            for(int i=0;i<this->data_size;i++)    //retrieve the old stuff in old arr and put them in the new space
                {
                    this->arr[i] = temp[i];
                };
        free(temp);    //free the temp space
	};
        this->arr[data_size] = x;    //let the last valid element in arr have the value of x
        this->data_size++;    //increment the number of element----data_size
    }

    void Array::append(Array &y)
    {
        if (data_size+y.data_size > cur_size)    //pretty much the same as what I did when the arr is full of elements
        {
            int* temp = (int*)malloc(data_size*sizeof(int));
            for(int i=0;i<data_size;i++)
            {
                temp[i] = arr[i];
            }
            arr = (int*)realloc(arr,2*(data_size+y.data_size)*sizeof(int));
            this->cur_size *= 2*(data_size+y.data_size);
            for(int i=0;i<this->data_size;i++)
            {
                this->arr[i] = temp[i];
            }
            free(temp);
//	    temp = NULL;
        };
        for(int i=data_size,j=0;i<data_size+y.data_size,j<y.data_size;i++,j++)    //traverse the arr and y and input the y's elements into arr
        {
            this->arr[i] = y.arr[j];
        }
        this->data_size += y.data_size;    //renew the data_size
    }

    int& Array::operator[](size_t i)    //redefine the [] operator to access specific elements in arr
    {
        return arr[i];
    }

    Array& Array::operator=(Array y)    //redefine the = operator of class Array
    {
        if(&y == this)    //if the right value of "=" is the same thing of the left value
            return *this;    //return this thing(dereference this pointer
        this->cleanup();    //call the cleanup function to free the space of the left value
        this->arr = (int*)malloc(y.cur_size * sizeof(int));    //request a space for new arr
        for(int i=0;i<y.data_size;i++)    //copy the stuff of y's arr to this->arr
        {
            this->arr[i] = y.arr[i];
        }
        this->data_size = y.data_size;    //renew the data_size
        this->cur_size = y.cur_size;    //renew the cur_size
        return *this;    //return the left value of "="
    }

/*     Reference: http://www.cplusplus.com/reference/cstdlib/realloc/
	          https://www.geeksforgeeks.org/operator-overloading-c/        */
