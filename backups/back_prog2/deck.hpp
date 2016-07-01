#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>

                                                         
    struct Deque_int_Iterator                                                    
    {                                                                              
        int *d_data;                                                                 
        int d_ind;                                                                 
                                                                                   
        void inc(Deque_int_Iterator* it){it->d_ind++;}                           
        int& deref(Deque_int_Iterator* it){return it->d_data[it->d_ind];}          
        void dec(Deque_int_Iterator* it){it->d_ind--;}                           
    };                                                                             
                                                                                   
    struct Deque_int                                                               
    {                                                                              
        int *d_data;   /*our data store           */                                 
        int d_size;  /*how much data is stored  */                                 
        int d_alloc; /*how much mem is alloc'd  */                                 
        int d_front; /*point to front           */                                 
        int d_back;  /*point to end             */                                 
        typedef bool (*comp)(const int &a, const int &b);                              
        comp func;                                                                 
        char type_name[6 + sizeof(int)] = "Deque_";                                                          
        Deque_int_Iterator *d_dib;                                               
        Deque_int_Iterator *d_die;                                               
                                                                                   
        void push_back(Deque_int *d, int data);                                      
        void push_front(Deque_int *d, int data);                                     
                                                                                   
        void pop_back(Deque_int *d);                                               
        void pop_front(Deque_int *d);                                              
                                                                                   
        int& front(Deque_int *d);                                                     
        int& back(Deque_int *d);                                                      
        Deque_int_Iterator& begin(Deque_int *d);                                 
        Deque_int_Iterator& end(Deque_int *d);                                   
        int& at(Deque_int *d, int pos);                                               
        int size(Deque_int *d);                                                    
        bool empty(Deque_int *d);                                                  
        void dtor(Deque_int *d);                                                   
        void clear(Deque_int *d); 
        void alloCopy(Deque_int *d);                                                 
        void checkpoint(Deque_int *d);
        void printall(Deque_int *d)
        {
            std:: cout << "d: ";
            for(int i=0; i<d->d_alloc; i++)
            {

                if(i == d->d_back)
                    std::cout << " ]";
                if(i == d->d_front)
                    std::cout << "[ ";
                std::cout << d->d_data[i];
                if(i+1 != d->d_alloc) 
                    std::cout << " , ";
            }
            std::cout << std::endl;
        }
                                                                                   
    };                                                                             
    static void Deque_int_ctor(Deque_int *d, bool (*f)(const int &a, const int &b))  
    {                                                                              
        d->d_data = ( int *) malloc(sizeof( int )*10);  
        for(int i=0; i<10; i++)
            d->d_data[i] = 0;                               
        d->d_size = 0;                                                             
        d->d_alloc = 10;                                                           
        d->d_front = 0;                                                            
        d->d_back = 0;                                                             
        d->d_dib = new Deque_int_Iterator();                                     
        d->d_die = new Deque_int_Iterator();                                     
        d->func = f;                                                               
        strcat(d->type_name, "int");                                             
        /*std::cout << ty << std::endl;*/                                              
    }                                                                              
                                                                                   
    static void Deque_int_Iterator_ctor(Deque_int_Iterator* it, Deque_int *d, bool front)
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
                                                                                   
                                                                                   
    static bool Deque_int_Iterator_equal(const Deque_int_Iterator& iter, const Deque_int_Iterator& iter2)
    {                                                                              
        return iter.d_ind == iter2.d_ind;                                          
    }                                                                              
                                                                                   
    static bool Deque_int_equal( Deque_int &iter, Deque_int &iter2)              
    {                                                                              
        bool ret = true;                                                           
        if(iter.d_size != iter2.d_size)                                            
        {                                                                          
            return false;                                                          
        }                                                                          
                                                                                   
        for(int i=0; i< iter.d_size; i++)                                          
        {                                                                          
            int val =  (iter.d_data[i]);                                             
            int val2 = (iter2.d_data[i]);                                            
            bool alessb = iter.func(val, val2);                                    
            bool blessa = iter.func(val2, val);                                    
            if( !alessb && !blessa )                                               
            { }                                                                    
            else                                                                   
            {                                                                      
                ret = false;                                                       
                break;                                                             
            }                                                                      
        }                                                                          
                                                                                   
        return ret;                                                                
    }                                                                              
    void Deque_int::alloCopy(Deque_int *d)
    {
        /*alloc more space and copy over, fix circular issues*/
        int *temp = ( int *) malloc(sizeof( int )*d->d_alloc*2); 

        for(int i=d->d_front; i<d->d_alloc+d->d_front; i++)
        {
            temp[i] = d->d_data[i%d->d_alloc];
        }

        free(d->d_data);
        d->d_back = d->d_alloc+d->d_front;                                                    
        d->d_data = temp;  
        d->d_alloc *= 2;       
    }                          

    void Deque_int::push_back(Deque_int *d, int data)                                
    {   
        //std::cout << "PB" << data << std::endl;
        /*handle empty array*/
        if(d->d_size == 0)
        {
            d->d_data[d->d_back] = data;
            d->d_back = (d->d_back + 1)%d->d_alloc; 
        }
        else if(d->d_size == d->d_alloc)
        {
            //we try to push, but there is no space
            alloCopy(d);
            
            //insert
            d->d_data[d->d_back] = data;
            d->d_back = (d->d_back + 1)%d->d_alloc; 
        }
        else
        {
            /*append to array, then increment size*/                                  
            d->d_data[d->d_back] = data;         
            //we have looped and the next index is open
            d->d_back = (d->d_back + 1)%d->d_alloc;
        }
        d->d_size++;                                                         
     }                                                                             
     void Deque_int::push_front(Deque_int *d, int data)                              
     {  
        /*handle empty array*/
        if(d->d_size == 0)
        {
            d->d_data[d->d_front] = data;
            d->d_front = (d->d_front == 0? d->d_alloc : d->d_front-1 ); 
        }
        else if(d->d_size == d->d_alloc)
        {
            //we try to push, but there is no space
            alloCopy(d);
            //insert
            d->d_front = (d->d_front == 0? d->d_alloc : d->d_front-1 ); 
            d->d_data[d->d_front] = data;
        }
        else
        {
            /*append to array, then increment size*/  
            d->d_front = (d->d_front == 0? d->d_alloc : d->d_front-1 );                           
            d->d_data[d->d_front] = data;         
        }
        d->d_size++;                                                           
     }         

     void Deque_int::checkpoint(Deque_int *d)                                        
     {   
        return;                                                                            
        
     }
     void Deque_int::pop_back(Deque_int *d)                                        
     {                                                                              
        if(d->d_size == 0)
        {
            return;
        } 

        d->d_back = (d->d_back == 0? d->d_alloc : d->d_back-1 );  
        d->d_size--;
        checkpoint(d);
     }                                                                             
     void Deque_int::pop_front(Deque_int *d)                                       
     {  
        if(d->d_size == 0)
        {
            return;
        } 

        d->d_front = (d->d_front + 1)%d->d_alloc;
        d->d_size--;
        checkpoint(d);
     }                                                                              
                                    
     int&  Deque_int::front(Deque_int *d)                                   
     {                                   
         return d->d_data[d_front];                                   
     }                                   
     int&  Deque_int::back(Deque_int *d)                                   
     {                                     
         return d->d_data[d->d_back];                                   
     }                                   
                                    
     Deque_int_Iterator& Deque_int::begin(Deque_int *d)                                   
     {                                   
         if(d->d_dib)                                   
             free(d->d_dib);                                   
         d_dib = new Deque_int_Iterator();                                   
         Deque_int_Iterator_ctor(d->d_dib, d, true);                                   
         return *d_dib;                                   
     }                                   
     Deque_int_Iterator& Deque_int::end(Deque_int *d)                                   
     {                                   
         if(d->d_die)                                                              
             free(d->d_die);                                                       
         d_die = new Deque_int_Iterator();                                       
         Deque_int_Iterator_ctor(d->d_die, d, false);                            
         return *d_die;                                                            
     }                                                                             
                                                                                   
     int&  Deque_int::at(Deque_int *d, int pos)                                        
     {                                                                             
         return d->d_data[d->d_front+pos];                                         
     }                                                                             
     int Deque_int::size(Deque_int *d)                                             
     {                                                                             
         return d->d_size;                                                         
     }                                                                             
     bool Deque_int::empty(Deque_int *d)                                           
     {                                                                             
         return d->d_size==0;                                                      
     }                                                                             
     void Deque_int::dtor(Deque_int *d)                                            
     {                                                                             
         if(d->d_die)                                                              
             free(d->d_die);                                                       
         if(d->d_dib)                                                              
             free(d->d_dib);                                                       
         free(d->d_data);                                                          
     }                                                                             
     void Deque_int::clear(Deque_int *d)                                           
     {
        free(d->d_data);                                                           
        d->d_data = ( int *) malloc(sizeof( int ) * 10);                               
        d->d_front = 0;                                                           
        d->d_back = 0;                                                            
        d->d_size = 0;                                                            
     }                                                                                                                       
                                                                                   

#endif


