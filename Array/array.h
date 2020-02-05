#ifndef ARRAY_H
#define ARRAY_H
#include <cstddef>
#include <iostream>
using namespace std;
class OutOfBoundsException: public exception    //costumize a new exception class
{
	const char* msg;

    public:
	OutOfBoundsException(const char* x)    //the constructor of the class
		{ msg = x; }
	    
	virtual const char* what() const throw()    //redefine the what() function from the base class
		{ return msg; }

};
template<class T>
class Array{
  // You'll need to fill in the function declarations here, since writing them
  // correctly is half the challenge of some of these functions.  Be careful to
  // give them the same names as specified in the README, and pay special
  // attention to things which should be const, references, or both.	 
	T *arr;
	int cur_size;
   	int data_size;
    	 //void initialize(int size,int val);
    	 //void cleanup();
    public:
	Array()
        {
    	arr = NULL;    //set arr as NULL
       	cur_size = 0;
        data_size = 0;
        }

        Array(int length,T value)
        {
        arr = new T[length];    //request a space of length long for arr
        for(int i=0;i<length;i++)    //initialize all of the elements in arr as value
            {
                arr[i] = value;
            };
        cur_size = length;    //update the cur_size
        data_size = length;    //update the data_size
        }

	Array(int length,T* values)
        {
        if(length != 0)    //check if the length is 0 or values is a valid pointer
        {
        arr = new T[length];    //request a space of length long for the arr
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

	Array(const Array<T>& x)

        {
        arr = new T[x.cur_size];    //request a space of the same size of the input's arr
        for(int i=0;i<x.data_size;i++)    //initialize all of the elements in arr using the corresponding ones in input's arr
            {
                arr[i] = x.arr[i];
            };
        cur_size = x.cur_size;
        data_size = x.data_size;
        }

	~Array()   //Destructor
        {
        if(arr)
        delete[] arr;
        arr = NULL;
        }

	int size() const
        {
        return data_size;
        }

	Array<T> operator+ (const Array<T>& x)
        {
        Array<T> y;
//	y.append(x);
        y.arr = new T[this->cur_size + x.cur_size];    //expand the arr size of y to the sum of x's and y's cur_size
	int cur = this->cur_size;
	int data = this->data_size;
        y.cur_size = cur + x.cur_size;    //update y's cur_size
        y.data_size = data + x.data_size;    //update y's data_size    
	for(int i=0;i<data;i++)
	    {
		y.arr[i] = arr[i];
	    };    
	for(int i=data, j=0;i<y.data_size, j<x.data_size;i++, j++)    //concatenate x to y
            {
                y.arr[i] = x.arr[j];
            };
	
        return y;
        }

   	friend ostream &operator<< (ostream &out,const Array<T>& a)
        {
        out << "[";    //output "[" into ostream object out
        for(int i=0;i<a.size()-1;i++)
            {
                out << a.arr[i] << ", ";
            };
        out << a.arr[a.size()-1] << "]";
        return out;    //return ostream object out
        }
 
	void append(T x)
        {
        if(data_size == 0)
            {
		data_size = 1;
                cur_size = 2;
                arr = new T[2];
                arr[0] = x;
                return;
            };
        if(data_size == cur_size)    //check if the old arr is full
        {
            T* temp = new T[data_size];    //request a space to store the old stuff in the arr
            for(int i=0;i<data_size;i++)    //traverse old arr and give all of the old elements to the temp
                {
                     temp[i] = arr[i];
                };
	    delete[] arr;
            arr = new T[2*data_size];    /*request a new space for the new arr that is two times big as the old one*/
            this->cur_size = this->data_size * 2;    //renew the current space size of arr
            for(int i=0;i<this->data_size;i++)    //retrieve the old stuff in old arr and put them in the new space
                {
                    this->arr[i] = temp[i];
                };
        delete[] temp;    //free the temp space
        };
        this->arr[data_size] = x;    //let the last valid element in arr have the value of x
        this->data_size++;    //increment the number of element----data_size
        }

   	void append(Array<T>& y)
        {
        if (data_size+y.data_size > cur_size)    //pretty much the same as what I did when the arr is full of elements
        {
	    data_size += y.data_size;
            T* temp = new T[data_size];
            for(int i=0;i<data_size;i++)
            {
                temp[i] = arr[i];
            }
	    delete[] arr;
            arr = new T[2*(data_size+y.data_size)];
            this->cur_size *= 2*(data_size+y.data_size);
            for(int i=0;i<this->data_size;i++)
            {
                this->arr[i] = temp[i];
            }
            delete[] temp;
            temp = NULL;
        };
	for(int i=data_size,j=0;i<data_size+y.data_size,j<y.data_size;i++,j++)    //traverse the arr and y and input the y's elements into arr
        {
            this->arr[i] = y.arr[j];
        }
        this->data_size += y.data_size;    //renew the data_size
        }
              
   	T& operator[](int i)
        {
	    if(i < 0 || i > data_size)
		{
		    throw OutOfBoundsException("Error: out of bounds");
		}
     	    return arr[i];
        }

   	Array<T>& operator=(const Array<T>& y)
	{
        if(&y == this)    //if the right value of "=" is the same thing of the left value
            return *this;
        if(arr)
        {
        delete[] this->arr;    //free the space where arr is pointing
        arr = NULL;    //let the arr point to nowhere
        };
        this->arr = new T[y.cur_size];    //request a space for new arr
        for(int i=0;i<y.data_size;i++)    //copy the stuff of y's arr to this->arr
        {
            this->arr[i] = y.arr[i];
        }
        this->data_size = y.data_size;    //renew the data_size
        this->cur_size = y.cur_size;    //renew the cur_size
	
        return *this;    //return the left value of "="
        }

     

  // Note that if your function declarations are incorrect, the autograder will
  // fail to compile.  We'll make sure the autograder is at least able to test
  // compiling your code before the submission deadline.
};


#endif
