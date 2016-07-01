#include "Deque.hpp"


void Deque::push_back(Deque* d, int data)
{
    //check if array needs space
    if(d->d_alloc == d->d_size)
    {
        //alloc more space and copy over
        int* temp = (int*) malloc(sizeof(int)*d->d_alloc*2);
        int c=0;
        for(int i=d->d_front; i<d->d_back; i++)
        {
            temp[c] = d->d_data[i];
            c++;
        }
        free(d->d_data);
        d->d_data = temp;
        d->d_front = 0;
        d->d_back = d->d_size+1;
    }

    //append to array, then increment size
    d->d_data[d->d_back++] = data;
    d->d_size++;
}
void Deque::push_front(Deque* d, int data)
{
    //check if empty space on left
    if(d->d_front == 0)
    {
        //check if we need to alloc
        if(d->d_alloc == d->d_size)
        {
            //alloc more space and copy over
            int* temp = (int*) malloc(sizeof(int)*d->d_alloc*2);
            int c=1;
            for(int i=d->d_front; i<=d->d_back; i++)
            {
                temp[c] = d->d_data[i];
                c++;
            }
            free(d->d_data);
            d->d_data = temp;
            d->d_data[0] = data;
            d->d_back = d->d_size+1;
            d->d_front = 0;
        }
        else
        {

            for(int i=d->d_back; i>=d_front; i--)
            {
                d->d_data[i] = d->d_data[i-1];
            }
            d->d_data[d_front] = data;
            d->d_back+=1;
        }
    }
    else
    {
        //we can just move
        d->d_data[--d_front] = data;
    }

    d->d_size++;
}

void Deque::pop_back(Deque* d)
{
    if(d->d_back == 0)
    {
        //empty
    }
    else
    {
        d->d_back--;
        d->d_size--;
    }
}
void Deque::pop_front(Deque* d)
{
    if(d->d_front == d->d_back)
    {
        //empty
    }
    else
    {
        d->d_front++;
        d->d_size--;
    }
}

int Deque::front(Deque* d)
{
    return d->d_data[d_front];
}
int Deque::back(Deque* d)
{
    if(d->d_back == 0)
        return 0;
    return d->d_data[d->d_back-1];
}

Deque_Iterator& Deque::begin(Deque* d)
{
    if(d->d_dib)
        free(d->d_dib);
    d_dib = new Deque_Iterator();
    Deque_Iterator_ctor(d->d_dib, d, true);
    return *d_dib;
}
Deque_Iterator& Deque::end(Deque* d)
{
    if(d->d_die)
        free(d->d_die);
    d_die = new Deque_Iterator();
    Deque_Iterator_ctor(d->d_die, d, false);
    return *d_die;
}
void Deque::printall(Deque* d)
{
    if(d->d_front == d->d_back)
    {
        std:: cout << "d: ";
        return;
    }
    std:: cout << "d: ";
    for(int i=0; i<d->d_front; i++)
    {
        std::cout << d->d_data[i] << " , ";
    }
    std::cout << "[ ";
    for(int i=d->d_front; i<d->d_back; i++)
    {
        std::cout << d->d_data[i] << " , ";
    }
    std::cout << "] ";
    for(int i=d->d_back; i<d->d_alloc; i++)
    {
        std::cout << d->d_data[i] << " , ";
    }
    std::cout << std::endl;
}
int Deque::at(Deque* d, size_t& pos)
{
    return d->d_data[d->d_front+pos];
}
int Deque::size(Deque* d)
{
    return d->d_size;
}
bool Deque::empty(Deque* d)
{
    return d->d_size==0;
}
void Deque::dtor(Deque* d)
{
    if(d->d_die)
        free(d->d_die);
    if(d->d_dib)
        free(d->d_dib);
    free(d->d_data);
}
void Deque::clear(Deque* d)
{
    d->d_front = 0;
    d->d_back = 0;
    d->d_size = 0;
}





