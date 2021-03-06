#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>

#define Deque_DEFINE(t)                                                            \
    struct Deque_##t##_Iterator                                                    \
    {                                                                              \
        t *d_data;                                                                 \
        int d_ind;                                                                 \
                                                                                   \
        void inc(Deque_##t##_Iterator* it){it->d_ind++;}                           \
        t& deref(Deque_##t##_Iterator* it){return it->d_data[it->d_ind];}          \
        void dec(Deque_##t##_Iterator* it){it->d_ind--;}                           \
    };                                                                             \
                                                                                   \
    struct Deque_##t                                                               \
    {                                                                              \
        t *d_data;   /*our data store           */                                 \
        int d_size;  /*how much data is stored  */                                 \
        int d_alloc; /*how much mem is alloc'd  */                                 \
        int d_front; /*point to front           */                                 \
        int d_back;  /*point to end             */                                 \
        typedef bool (*comp)(const t &a, const t &b);                              \
        comp func;                                                                 \
        char type_name[6 + sizeof(#t)] = "Deque_";                                                          \
        Deque_##t##_Iterator *d_dib;                                               \
        Deque_##t##_Iterator *d_die;                                               \
                                                                                   \
        void push_back(Deque_##t *d, t data);                                      \
        void push_front(Deque_##t *d, t data);                                     \
                                                                                   \
        void pop_back(Deque_##t *d);                                               \
        void pop_front(Deque_##t *d);                                              \
                                                                                   \
        t& front(Deque_##t *d);                                                     \
        t& back(Deque_##t *d);                                                      \
        Deque_##t##_Iterator& begin(Deque_##t *d);                                 \
        Deque_##t##_Iterator& end(Deque_##t *d);                                   \
        t& at(Deque_##t *d, int pos);                                               \
        int size(Deque_##t *d);                                                    \
        bool empty(Deque_##t *d);                                                  \
        void dtor(Deque_##t *d);                                                   \
        void clear(Deque_##t *d);                                                  \
        void checkpoint(Deque_##t *d);\
                                                                                   \
    };                                                                             \
    static void Deque_##t##_ctor(Deque_##t *d, bool (*f)(const t &a, const t &b))  \
    {                                                                              \
        d->d_data = ( t *) malloc(sizeof( t )*10000000);                                 \
        d->d_size = 0;                                                             \
        d->d_alloc = 10000000;                                                           \
        d->d_front = 0;                                                            \
        d->d_back = 0;                                                             \
        d->d_dib = new Deque_##t##_Iterator();                                     \
        d->d_die = new Deque_##t##_Iterator();                                     \
        d->func = f;                                                               \
        strcat(d->type_name, #t);                                             \
        /*std::cout << ty << std::endl;*/                                              \
    }                                                                              \
                                                                                   \
    static void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator* it, Deque_##t *d, bool front)\
    {                                                                              \
        it->d_data = d->d_data;                                                    \
        if(front)                                                                  \
        {                                                                          \
            it->d_ind = d->d_front;                                                \
        }                                                                          \
        else                                                                       \
        {                                                                          \
            it->d_ind = d->d_back;                                                 \
        }                                                                          \
    }                                                                              \
                                                                                   \
                                                                                   \
    static bool Deque_##t##_Iterator_equal(const Deque_##t##_Iterator& iter, const Deque_##t##_Iterator& iter2)\
    {                                                                              \
        return iter.d_ind == iter2.d_ind;                                          \
    }                                                                              \
                                                                                   \
    static bool Deque_##t##_equal( Deque_##t &iter, Deque_##t &iter2)              \
    {                                                                              \
        bool ret = true;                                                           \
        if(iter.d_size != iter2.d_size)                                            \
        {                                                                          \
            return false;                                                          \
        }                                                                          \
                                                                                   \
        for(int i=0; i< iter.d_size; i++)                                          \
        {                                                                          \
            t val =  (iter.d_data[i]);                                             \
            t val2 = (iter2.d_data[i]);                                            \
            bool alessb = iter.func(val, val2);                                    \
            bool blessa = iter.func(val2, val);                                    \
            if( !alessb && !blessa )                                               \
            { }                                                                    \
            else                                                                   \
            {                                                                      \
                ret = false;                                                       \
                break;                                                             \
            }                                                                      \
        }                                                                          \
                                                                                   \
        return ret;                                                                \
    }                                                                              \
                                                                                   \
    void Deque_##t::push_back(Deque_##t *d, t data)                                \
    {\   
                                                                             \
         /*check if array needs space*/                                            \
        if(d->d_alloc == d->d_size)                                                \
         {                                                                         \
             /*alloc more space and copy over */                                   \
             t *temp = ( t *) malloc(sizeof( t )*d->d_alloc*2);                    \
             int c=0;                                                              \
             for(int i=d->d_front; i<d->d_back; i++)                               \
             {                                                                     \
                 temp[c] = d->d_data[i];                                           \
                 c++;                                                              \
             }                                                                     \
             free(d->d_data);                                                      \
             d->d_data = temp;                                                     \
             d->d_alloc *= 2;                                                       \
             d->d_front = 0;                                                       \
             d->d_back = d->d_size+1;                                              \
         }                                                                         \
                                                                                   \
         /*append to array, then increment size*/                                  \
         d->d_data[d->d_back++] = data;                                            \
         d->d_size++;                                                              \
     }                                                                             \
     void Deque_##t::push_front(Deque_##t *d, t data)                              \
     {                                                                             \
         /*check if empty space on left */                                         \
         if(d->d_front == 0)                                                       \
         {                                                                         \
             /*check if we need to alloc*/                                         \
             if(d->d_alloc == d->d_size)                                           \
             {                                                                     \
                 /*alloc more space and copy over*/                                \
                 t *temp = (t *) malloc(sizeof( t )*d->d_alloc*2);                 \
                 int c=1;                                                          \
                 for(int i=d->d_front; i<=d->d_back; i++)                          \
                 {                                                                 \
                     temp[c] = d->d_data[i];                                       \
                     c++;                                                          \
                 }                                                                 \
                 free(d->d_data);                                                  \
                 d->d_data = temp;                                                 \
                 d->d_alloc *= 2;                                                  \
                 d->d_data[0] = data;                                              \
                 d->d_back = d->d_size+1;                                          \
                 d->d_front = 0;                                                   \
             }                                                                     \
             else                                                                  \
             {                                                                     \
                                                                                   \
                 for(int i=d->d_back; i>=d_front; i--)                             \
                 {                                                                 \
                     d->d_data[i] = d->d_data[i-1];                                \
                 }                                                                 \
                 d->d_data[d_front] = data;                                        \
                 d->d_back+=1;                                                     \
             }                                                                     \
         }                                                                         \
         else                                                                      \
         {                                                                         \
             /*we can just move*/                                                  \
             d->d_data[--d_front] = data;                                          \
         }                                                                         \
                                                                                   \
         d->d_size++;                                                              \
     }                                                                             \
     void Deque_##t::checkpoint(Deque_##t *d)                                        \
     {                                                                               \
        if(d->d_front == d->d_back || d->d_front >= d->d_alloc)\
        {   \  
            if(d->d_front != 0)\
            {\
                t *temp = (t *) malloc(sizeof( t )*d->d_alloc);                   \
                int c=0;                                                          \
                for(int i=d->d_front; i<=d->d_back; i++)                          \
                {                                                                 \
                    temp[c] = d->d_data[i];                                       \
                    c++;                                                          \
                }                                                                 \
                free(d->d_data);                                                  \
                d->d_data = temp;                                                 \
                d->d_alloc *= 2;                                                  \
                d->d_back = d->d_size+1;                                          \
                d->d_front = 0;                                                   \ 
            }\
        }   \
        \
     }\
     void Deque_##t::pop_back(Deque_##t *d)                                        \
     {                                                                             \
         if(d->d_back == 0)                                                        \
         {                                                                         \
             /*empty*/                                                             \
         }                                                                         \
         else                                                                      \
         {                                                                         \
             d->d_back--;                                                          \
             d->d_size--;                                                          \
         }                                                          \
         checkpoint(d);\
     }                                                                             \
     void Deque_##t::pop_front(Deque_##t *d)                                       \
     {       \
         if(d->d_front == d->d_back)                                               \
         {                                                                         \
             /*empty*/                                                             \
         }                                                                         \
         else                                                                      \
         {                                                                         \
             d->d_front++;                                   \
             d->d_size--;                                   \
         }\
         checkpoint(d);\
     }                                                                              \
                                    \
     t&  Deque_##t::front(Deque_##t *d)                                   \
     {                                   \
         return d->d_data[d_front];                                   \
     }                                   \
     t&  Deque_##t::back(Deque_##t *d)                                   \
     {                                     \
         return d->d_data[d->d_back-1];                                   \
     }                                   \
                                    \
     Deque_##t##_Iterator& Deque_##t::begin(Deque_##t *d)                                   \
     {                                   \
         if(d->d_dib)                                   \
             free(d->d_dib);                                   \
         d_dib = new Deque_##t##_Iterator();                                   \
         Deque_##t##_Iterator_ctor(d->d_dib, d, true);                                   \
         return *d_dib;                                   \
     }                                   \
     Deque_##t##_Iterator& Deque_##t::end(Deque_##t *d)                                   \
     {                                   \
         if(d->d_die)                                                              \
             free(d->d_die);                                                       \
         d_die = new Deque_##t##_Iterator();                                       \
         Deque_##t##_Iterator_ctor(d->d_die, d, false);                            \
         return *d_die;                                                            \
     }                                                                             \
                                                                                   \
     t&  Deque_##t::at(Deque_##t *d, int pos)                                        \
     {                                                                             \
         return d->d_data[d->d_front+pos];                                         \
     }                                                                             \
     int Deque_##t::size(Deque_##t *d)                                             \
     {                                                                             \
         return d->d_size;                                                         \
     }                                                                             \
     bool Deque_##t::empty(Deque_##t *d)                                           \
     {                                                                             \
         return d->d_size==0;                                                      \
     }                                                                             \
     void Deque_##t::dtor(Deque_##t *d)                                            \
     {                                                                             \
         if(d->d_die)                                                              \
             free(d->d_die);                                                       \
         if(d->d_dib)                                                              \
             free(d->d_dib);                                                       \
         free(d->d_data);                                                          \
     }                                                                             \
     void Deque_##t::clear(Deque_##t *d)                                           \
     {\
        free(d->d_data);                                                           \
        d->d_data = ( t *) malloc(sizeof( t ) * 20);                               \
        d->d_front = 0;                                                           \
        d->d_back = 0;                                                            \
        d->d_size = 0;                                                            \
     }                                                                             \
                                                                                   \

#endif


