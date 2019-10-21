#include "mon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int flag = 0;
Element* create_left(Element* root, char* data)
{
    if(root->left_child == NULL)    //check if the left child is NULL
    {					//if it is, we would be supposed to create a new tree on that side
        Element *left = malloc(sizeof(Element));     //request space for the new Element 
        left->name = malloc(sizeof(data));   	//request an amount of space for left's name
	strcpy(left->name,data);	//copy the input argument data string and pass the copy to left's name
        left->left_child = NULL;	//new Element does not have children, so they are NULL temporarily
        left->right_child = NULL;
        root->left_child = left;	//make the newly created Element the left child of the root(father node)
	return left;		//return a pointer pointing to the new Element
    }
    else
    {
        return NULL;    //if the father node already has left child, then we return none.
    };
}

Element* create_right(Element* root, char* data)	//pretty much the same as the left one stated above
{
    if(root->right_child == NULL)
    {
        Element *right = malloc(sizeof(Element));
        right->name = malloc(sizeof(data));
	strcpy(right->name,data);
        right->left_child = NULL;
        right->right_child = NULL;
        root->right_child = right;
        return right;
    }
    else
    { 
        return NULL;
    };
}

void free_tree(Element* root)
{
    if(!root)
    {
	return;		//if the input is a NULL, there would not be anything to free. So, return!(complete the local recursion)
    }
    else
    {
	free_tree(root->left_child);	//recursively find and free left children
	free_tree(root->right_child);	   //recursively find and free right children
        free(root->name);	//first behavior of each recursion: free the name
	free(root);	//then free the whole node
    };

}

int write_tree(FILE* f, Element* e)
{
    if(!e)
	{
	    fprintf(f,"NULL ");		//if the input Element* is a NULL, just print NULL
            if(flag)
	    {
		return 0;
	    }
	    else
	    {
		return -1;	
	    };
	}
    else 
	{
	    flag = 1;	//a static vriable serving as a flag to identify if the input is a non-valid one
	    fprintf(f,"{");	//draw the tree into the target file
	    write_tree(f,e->left_child);
	    write_tree(f,e->right_child);
	    fprintf(f,"%s}",e->name);
	    return 0;
	};
}

Element* load_tree(FILE* f)
{
    char c = fgetc(f);		//get one char in the file and store it in variable c
    if(c =='{')	//if the char we get is '{'
    {
        Element* left = load_tree(f);	//recurse on the left branch
        Element* right = load_tree(f);	//recurse on the right branch
	char n[500];	//declare a char array to store the name
	int g = 0;	//record the location of the char array's end
	for(int i=0;c!='}';i++)	//store the cs into the n
	{
	    c = fgetc(f);
	    n[i] = c;
	    g = i;		
        };
	n[g] = '\0';	//end the name string
	Element* root = malloc(sizeof(Element));	//request a space for the new tree
	root->name = malloc(strlen(n)+1);	//request a space for the name of the new tree
	strcpy(root->name,n);	//give the name
	root->left_child = left;	//let the return value of last recursion be the left child
	root->right_child = right;	//let the return value of last recursion be the right child
	return root;	//return the pointer of the root node
	    
    }	    
    else if(c == 'N')
    {
	
	fseek(f,4L,SEEK_CUR);	//each time we reach 'N', we let the FILE* f to move forward for 4 to skip the "NULL"   
    };
    return NULL;
}

//Reference: https://www.runoob.com/cprogramming/c-function-fseek.html
