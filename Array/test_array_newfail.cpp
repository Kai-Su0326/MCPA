// Implement a version of `new` that fails on command
// Based on https://stackoverflow.com/questions/1923664/simulating-low-memory-using-c
#include <cstdlib>
#include <iostream>
#include "array.h"
// Global flag that sets whether or not `new` will fail
bool memoryAllocFail = false; // Succeed by default

// Custom implementation of new
void* operator new(std::size_t size)
{
    std::cout << "New allocation of size " << size << std::endl;
    if (memoryAllocFail)
    {
       throw std::bad_alloc();
    }

    return malloc(size);
}

void operator delete(void* block)
{
    std::cout << "Freed allocation" << std::endl;
    free(block);
}

int main(int argc, char* argv[])
{
    try{
	memoryAllocFail = true;
	Array<int> *p = new Array<int>(15,5);
	}
    catch(std::bad_alloc& x)
	{
	std::cout<<"new operation fail"<<std::endl;
	}

    memoryAllocFail = false;
    int* b = new int[10];
    delete b;

    return(0);
}
