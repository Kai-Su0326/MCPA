#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
using namespace std;
//hear is almost empty and I put the definitions in the array.h file
//    void Array::initialize(int size, int val)
//    {
//        this->cur_size = size;    //give the variable cur_size the value of size
//        this->data_size = size;    //give the variable data_size the value of size
//        this->arr = (int*)malloc(size * sizeof(int));    //request a space for the arr
//        for(int i=0;i<size;i++)    //loop to initiallize all of the elements in the arr
//        {
//            this->arr[i] = val;
//        }
//    }

//    void Array::cleanup()
//    {
//      if (arr){  
//        free(this->arr);    //free the space where arr is pointing
//        arr = NULL;    //let the arr point to nowhere
//	this->cur_size = 0;
//	this->data_size = 0;
//        return; 
//      }
//    }

    Array<T>::Array()    //default constructor
    {
	arr = NULL;    //set arr as NULL
	cur_size = 0;
	data_size = 0;
    }
    
    Array<T>::Array(int length,T value)    //constructor that takes two int as input
    {
	arr = (T*)malloc(sizeof(T)*length);    //request a space of length long for arr
	for(int i=0;i<length;i++)    //initialize all of the elements in arr as value
	    {
		arr[i] = value;
	    };
	cur_size = length;    //update the cur_size
	data_size = length;    //update the data_size
    }

    Array<T>::Array(int length,T* values)    //constructor that takes a int and a int pointer
    {
    if(length != 0)    //check if the length is 0 or values is a valid pointer
    {
	arr = (T*)malloc(sizeof(T)*length);    //request a space of length long for the arr
	for(int i=0;i<length;i++)    //initialize the elements in arr using the values of former length elements of values
	    {
		arr[i] = values[i];
	    };
    }
    else    //if the values is invalid(NULL)
    {
	arr = NULL;    //set arr as NULL
    };
	cur_size = length;    //update the cur_size
        data_size = length;    //update the data_size
    }
    
    Array<T>::Array(Array<T>& x)    //a copy constructor which takes a reference of Array as input
    {
	arr = (T*)malloc(sizeof(T)*x.cur_size);    //request a space of the same size of the input's arr
	for(int i=0;i<x.data_size;i++)    //initialize all of the elements in arr using the corresponding ones in input's arr
	    {
		arr[i] = x.arr[i];
	    };
	cur_size = x.cur_size;
	data_size = x.data_size;
    }

    Array<T>::~Array()    //the destructor of the class
    {
	if(arr)    
	free(arr);
	arr = NULL;
    }

    ostream &operator<< (ostream& out,const Array<T>& a)    //overload the << operator
    {
	out << "[";    //output "[" into ostream object out
	for(int i=0;i<a.size()-1;i++)
	    {
		out << a.arr[i] << ", ";
	    };
	out << a.arr[a.size()-1] << "]";
	return out;    //return ostream object out
    }
   
    size_t Array<T>::size() const    //acquire the size of data_size
    {
        return data_size;
    }

    void Array<T>::append(T x)    //(old arr and new arr actually are same pointer pointing different spaces)
    {
	if(data_size == 0)
	    {
		arr = (T*)malloc(sizeof(T)*2);
	        arr[0] = x;
	        data_size = 1;
	        cur_size = 2;
	        return;
	    };
        if(data_size == cur_size)    //check if the old arr is full
        {
	    T* temp = (T*)malloc(data_size*sizeof(T));    //request a space to store the old stuff in the arr
            for(int i=0;i<data_size;i++)    //traverse old arr and give all of the old elements to the temp
                {
          	     temp[i] = arr[i];
                };
            arr = (T*)realloc(arr,2*sizeof(T)*(this->data_size));    //request a new space for the new arr that is two times big as the old one
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

    void Array<T>::append(Array<T>& y)
    {
        if (data_size+y.data_size > cur_size)    //pretty much the same as what I did when the arr is full of elements
        {
            T* temp = (T*)malloc(data_size*sizeof(T));
            for(int i=0;i<data_size;i++)
            {
                temp[i] = arr[i];
            }
            arr = (T*)realloc(arr,2*(data_size+y.data_size)*sizeof(T));
            this->cur_size *= 2*(data_size+y.data_size);
            for(int i=0;i<this->data_size;i++)
            {
                this->arr[i] = temp[i];
            }
            free(temp);
	    temp = NULL;
        };
        for(int i=data_size,j=0;i<data_size+y.data_size,j<y.data_size;i++,j++)    //traverse the arr and y and input the y's elements into arr
        {
            this->arr[i] = y.arr[j];
        }
        this->data_size += y.data_size;    //renew the data_size
    }

    T& Array<T>::operator[](size_t i)    //redefine the [] operator to access specific elements in arr
    {
        return arr[i];
    }

    Array<T>& Array<T>::operator=(Array<T> y)    //redefine the = operator of class Array
    {
        if(&y == this)    //if the right value of "=" is the same thing of the left value
            return *this;    //return this thing(dereference this pointer
       // this->cleanup();    //call the cleanup function to free the space of the left value
        if (arr)
	{  
            free(this->arr);    //free the space where arr is pointing
            arr = NULL;    //let the arr point to nowhere
	};
        this->arr = (T*)malloc(y.cur_size * sizeof(T));    //request a space for new arr
        for(int i=0;i<y.data_size;i++)    //copy the stuff of y's arr to this->arr
        {
            this->arr[i] = y.arr[i];
        }
        this->data_size = y.data_size;    //renew the data_size
        this->cur_size = y.cur_size;    //renew the cur_size
        return *this;    //return the left value of "="
    }

    Array<T>& Array<T>::operator+ (Array<T>& x)    //overload the operator +, which enable it to add Array
    {
	Array<T>& y(*this);    //declare an Array reference y and initalize it using the copy constructor
	y.arr = (T*)realloc(y.arr, sizeof(T) * (y.cur_size + x.cur_size));    //expand the arr size of y to the sum of x's and y's cur_size
	for(int i=y.data_size, j=0;i<y.data_size+x.data_size, j<x.data_size;i++, j++)    //concatenate x to y
	    {
		y.arr[i] = x.arr[j];
	    };
	y.cur_size += x.cur_size;    //update y's cur_size
	y.data_size += x.data_size;    //update y's data_size
	return y;
    }
/*     Reference: http://www.cplusplus.com/reference/cstdlib/realloc/
	          https://www.geeksforgeeks.org/operator-overloading-c/ 
		  https://www.runoob.com/cplusplus/cpp-friend-functions.html
		  https://blog.csdn.net/caroline_wendy/article/details/15336063
		  https://medium.com/@nonuruzun/overloading-input-output-operators-in-c-a2a74c5dda8a       */
