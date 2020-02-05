#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<iostream>
#include<cstddef>
#include<exception>
class OverBoundException: public std::exception    //customize an exception class
{
	const char* msg;   
	public:
	OverBoundException(const char* x)
		{ msg = x; }
	virtual const char* what() const throw()    //redefine the what() function from the std::exception class
		{ return msg;}
};
//std::cout<<"--1--";
template <class T>
class LinkedList{
  // You'll need to fill in the function declarations here, since writing them
  // correctly is half the challenge of some of these functions.  Be careful to
  // give them the same names as specified in the README, and pay special
  // attention to things which should be const, references, or both.
	class Node
	{
		public:
		T data;    
		Node* next;
		Node(const T& d) : data(d), next(NULL) {}    //initialization list for one input arguments
		Node(const T& d, Node* n) : data(d), next(n) {}    //initialization list for two input arguments
	};
	Node* head;    //class member: head pointer of the linked list
	unsigned int siz;    //class member: an int variable recording the size of the linked list

	Node* remove_helper(int pos, Node* current)    //a recursion healper of remove function, we only recurse this function multiple times
        {
                if(current == NULL)    //check if the current pointer is NULL, if its NULL, it means we have recurse to the last element in the linked list.
                {
                        return NULL;
                }
                if(!pos)    //if the input pos is not 0, we would save the next node position and delete the node
                {
                        Node* temp = current->next;    
                        delete current;
			siz--;
                        return temp;
                }
                current->next = remove_helper(pos-1,current->next);    //recurse with smaller pos and current pointer moved forward
                return current;
        }

	public:
	LinkedList() : head(NULL), siz(0) {}    //initialization list of LinkedList

	LinkedList(int length, T* values)    //constructor with two input arguments
	{
		if(!length)    //if the length is 0, use the initialization list of LinkedList
		{
			LinkedList();
		}
		else
		{
		siz = 0;
		head = new Node(values[length-1]);    //head's next become the length'th value in the array 
		siz += 1;
		for(int i = length-2; i > -1; i--)    //traverse the array in a backward order
			{
				head = new Node(values[i],head);
				siz += 1;
			}
		}
	}

	LinkedList(const LinkedList& x)    //copy constructor
	{
		if(!x.head)    //check if the x linked list is empty
		{
			head = NULL;
			siz = 0;
		}
		else
		{
			siz = 0;    //initialize the siz as 0
			Node* current = x.head->next;    //creat a current pointer pointing to the next counterpart of temp in x
			head = new Node(x.head->data);    //insert a deep copy of a node in x
			siz++;
			Node* temp = head;    //creat a moving pointer called temp start from the first node
			while(current)    //as long as current is pointing to something instead of NULL, we traverse the two linked list and make a deep copy of x
			{
				temp->next = new Node(current->data);
				siz++;
				current = current->next;
				temp = temp->next;
			}
		}
	}
	
	~LinkedList()    //destructor
	{
		if(head)    //if there is something in the list, we use a temp pointer to record each node and delete them
		{
			Node* temp = head;
			while(temp)
			{
				head = temp->next;
				delete temp;
				temp = head;
				siz--;
			}
		}
	}

	unsigned int size()
	{
		return siz;
	}

	T getItem(int n)
	{
		if(n >= size() || !head)    //to check if the input n is valid
		{
			throw OverBoundException("Error: You are selecting something out of bound!");
		}
		Node* temp = head;    //initialize a temp pointer as head, we kinda use it in a similar way as iterator
		while(n)
		{
			temp = temp->next;
			n--;
		}
		return temp->data;
	}

	void insert(T x, int pos)	
	{
		if(pos>size())    
		{
			throw OverBoundException("Error: You are selecting something out of bound!");
		}
		Node* temp = head;
                if(pos == 0)    //check if we want to insert things right after the head pointer
                {
                        head = new Node(x,temp);
                        siz++;
                }
		else    //otherwise we use the temp to traverse the list to find the posotion and insert a node there
		{
                	while(pos>1)
                	{
                        	temp = temp->next;
                        	pos--;
                	}
                	Node* ans = new Node(x,temp->next);
                	temp->next = ans;
                	siz++;		
		}
	}

	void remove(int pos)
	{
                if(pos >= size())
                {
                        throw OverBoundException("Error: You are selecting something out of bound!");
                }
		
		head = remove_helper(pos, head);    //recurseively call this remove_helper to update each pointer in the list
	}
	
	LinkedList<T>& operator=(const LinkedList& x)
	{
		if(&x == this)    //if the assignment operator is assigning the same thing, we return that thing without doing a deep copy
			return *this;
		if(head)
                {
                        Node* temp = head;
                        while(temp)
                        {
                                head = temp->next;
                                delete temp;
                                temp = head;
                                siz--;
                        }
                }
		   //call the destructor to empty the lvalue's old stuff
		if(!x.head)    //if x is empty too, then ok, we get two empty list
                {
                        head = NULL;
                        siz = 0;
                }
                else    //otherwise we pretty much do the same thing in copy constructor makeing a deep copy
                {
                        Node* current = x.head->next;
                        head = new Node(x.head->data);
                        siz++;
                        Node* temp = head;
                        while(current)
                        {
                                temp->next = new Node(current->data);
                                siz++;
                                current = current->next;
                                temp = temp->next;
                        }
                }
		return *this;    //return waht this pointer is pointing
	}

		 			
  // Note that if your function declarations are incorrect, the autograder will
  // fail to compile.  We'll make sure the autograder is at least able to test
  // compiling your code before the submission deadline.
};


#endif
