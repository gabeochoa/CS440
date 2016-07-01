#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

struct Deque_Iterator
{
	int* d_data;
	int d_ind;
	
	void inc(Deque_Iterator* it){it->d_ind++;}
	int deref(Deque_Iterator* it){return it->d_data[it->d_ind];}
	void dec(Deque_Iterator* it){it->d_ind--;}
};

struct Deque
{
	int* d_data; //our data store
	int d_size;  //how much data is stored
	int d_alloc; //how much mem is alloc'd
	int d_front; //point to front
	int d_back;  //point to end
	char* type_name;
	Deque_Iterator* d_dib;
	Deque_Iterator* d_die;

	void push_back(Deque* d, int);
	void push_front(Deque* d, int);

	void pop_back(Deque* d);
	void pop_front(Deque* d);

	int front(Deque* d);
	int back(Deque* d);
	Deque_Iterator& begin(Deque* d);
	Deque_Iterator& end(Deque* d);
	int at(Deque* d, size_t& pos);
	int size(Deque* d);
	bool empty(Deque* d);
	void dtor(Deque* d);
	void clear(Deque* d);

	void printall(Deque* d);

};




static void Deque_ctor(Deque* d, bool (*f)(const int&, const int&))
{
	d->d_data = (int*) malloc(sizeof(int)*10);
    d->d_size = 0;
    d->d_alloc = 10;
    d->d_front = 0;
    d->d_back = 0;
    d->d_dib = new Deque_Iterator();
    d->d_die = new Deque_Iterator();
    char* ty = "Deque_int";
    d->type_name = ty;
}

static void Deque_Iterator_ctor(Deque_Iterator* it, Deque *d, bool front)
{
	it->d_data = d->d_data;
	if(front)
	{
		it->d_ind = d->d_front;
	}
	else
	{
		it->d_ind = d->d_back;
	}
}		


static bool Deque_Iterator_equal(const Deque_Iterator& iter, const Deque_Iterator& iter2)
{
	return iter.d_ind == iter2.d_ind;
}



#endif
