#ifndef SharedPtr_GO
#define SharedPtr_GO

#include <stdio.h>
#include <iostream>
#include <atomic>
#include <pthread.h>
#include <mutex>

//#define DEBUG 1
#undef DEBUG

namespace cs540
{
    class Referer {
        private:
            int count;
            //std::atomic_uint count;
        public:
            Referer(): count(1)
            {
            }
            virtual ~Referer(){}
            int decrement() 
            {
                count--;
                return count;
            }
            int increment() 
            {
                count++;
                return count;
            }
    };
    template <typename A>
    class Ref : public Referer 
    {
        private:
            A* obj;
        public:
            Ref(A* o) : obj(o) {}
            ~Ref() 
            { 
                delete obj;
            }
    };

    template <typename T> 
    struct SharedPtr
    {

        mutable std::mutex suo;
        T* raw = nullptr;
        Referer* counter = nullptr;
        //Constructs a smart pointer that points to null.
        SharedPtr(): raw(nullptr), counter(nullptr){}
        
        //Constructs a smart pointer that points to the given object. 
        //The reference count is initialized to one.
        template <typename U> 
        explicit SharedPtr(U * u):
            raw(u),
            counter(new Ref<U>(u))
        {
            #ifdef DEBUG 
            std::cout << "Explicit Constructor" << std::endl; 
            #endif
        }

        //If p is not null, then reference count of the managed object is incremented. 
        //If U * is not implicitly convertible to T *, 
        //the second constructor will result in a syntax error.
        SharedPtr(const SharedPtr &p)
        {
            #ifdef DEBUG 
            std::cout << "Copy notemp" << std::endl; 
            #endif
            
            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);
            
            raw = p.raw;
            counter = p.counter;
            if(p != nullptr)
            {
                counter->increment();
            }
        }
        template <typename U> 
        SharedPtr(const SharedPtr<U> &p)
        {
            #ifdef DEBUG 
            std::cout << "Copy template" << std::endl; 
            #endif
            
            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);
            
            if(counter != nullptr && counter->decrement() == 0)
            {
                delete counter;
            }

            raw = static_cast<T*>(p.raw);
            counter = p.counter;

            counter->increment();
            
        }
        template <typename U> 
        SharedPtr(const SharedPtr<U> &p, int)
        {
            #ifdef DEBUG 
            std::cout << "Copy template" << std::endl; 
            #endif
             
            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);
            
            if(counter != nullptr && counter->decrement() == 0)
            {
                delete counter;
            }

            raw = dynamic_cast<T*>(p.raw);
            if(raw != nullptr)
            {
                counter = p.counter;
                counter->increment();
            }
            else
            {
                counter = nullptr;
            }
        }
    
        //Move the managed object from the given smart pointer. 
        //The reference count must remain unchanged. 
        //After this function, p must be null. 
        //This must work if U * is implicitly convertible to T *.
        SharedPtr(SharedPtr &&p)
        {
            #ifdef DEBUG 
            std::cout << "Move" << std::endl; 
            #endif
            
            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);
            raw = p.raw;
            counter = p.counter;
            p.raw = nullptr;
            p.counter = nullptr;
        }
        template <typename U> SharedPtr(SharedPtr<U> &&p)
        {
            #ifdef DEBUG 
            std::cout << "Move temp" << std::endl; 
            #endif

            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);

            raw = p.raw;
            counter = p.counter;
            p.raw = nullptr;
            p.counter = nullptr;
        }

        //Copy assignment. Must handle self assignment. 
        //Decrement reference count of current object, 
        //if any, and increment reference count of the given object. 
        //If U * is not implicitly convertible to T *, this will result in a syntax error.
        // Note that both the normal assignment operator and a member template assignment 
        //operator must be provided for proper operation.
        SharedPtr &operator=(const SharedPtr & p)
        {
            #ifdef DEBUG 
            std::cout << "assign " << std::endl; 
            #endif
            if(this == &p){return *this;}
            else
            {
                {
                    std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
                    std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
                    std::lock(lock1, lock2);

                    if(counter != nullptr && counter->decrement() == 0)
                    {
                        //we are done, just delete it
                        delete counter;
                        counter = nullptr;
                        raw = nullptr;
                    }
                }
                {
                    std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
                    std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
                    std::lock(lock1, lock2);

                    //copy everything else
                    raw = p.raw;
                    counter = p.counter;
                    //now there is one more ref
                    if(counter != nullptr)
                        counter->increment();
                }
            }
            return *this;
        }

        template <typename U>
        SharedPtr<T> &operator=(const SharedPtr<U> & p)
        { 
            #ifdef DEBUG 
            std::cout << "assign temp" << std::endl; 
            #endif
            if(raw == p.raw) {return *this;}
            else
            {
                
            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);
            
                if(counter != nullptr && counter->decrement() == 0)
                {
                    //we are done, just delete it
                    delete counter;
                    //safety 
                    counter = nullptr;
                    raw = nullptr;
                }
                //copy everything else
                raw = static_cast<T*>(p.raw);
                counter = p.counter;
                //now there is one more ref
                if(counter != nullptr)
                    counter->increment();
            }
            return *this;
        }

        //Move assignment.
        //After this operation, p must be null.
        //The reference count associated with the object 
        //(if p is not null before the operation) will 
        //remain the same after this operation. 
        //This must compile and run correctly if U * is 
        //implicitly convertible to T *, 
        //otherwise, it must be a syntax error. 
        SharedPtr &operator=(SharedPtr &&p)
        {
            #ifdef DEBUG 
            std::cout << "assign move" << std::endl; 
            #endif
            
            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);
            
            if (counter && counter->decrement() == 0) {
                delete counter;
            }
            std::swap(counter, p.counter);
            std::swap(raw, p.raw);
            return *this;
        }
           
        template <typename U> SharedPtr &operator=(SharedPtr<U> &&p)
        {
            #ifdef DEBUG 
            std::cout << "assign move temp" << std::endl; 
            #endif
            
            std::unique_lock<std::mutex> lock1(suo, std::defer_lock);          
            std::unique_lock<std::mutex> lock2(p.suo, std::defer_lock);       
            std::lock(lock1, lock2);
            
            if (counter && counter->decrement() == 0) {
                delete counter;
                counter = nullptr;
                raw = nullptr;
            }
            std::swap(counter, p.counter);
            std::swap(raw, p.raw);
            return *this;
        }

        //Decrement reference count of managed object. 
        //If the reference count is zero, delete the object.
        ~SharedPtr()
        {
            #ifdef DEBUG 
            std::cout << "destructor" << std::endl; 
            #endif
            std::lock_guard<std::mutex> lock(suo);
            if(counter != nullptr && counter->decrement() == 0)
            {
                //we are done, just delete it
                delete counter;
                counter = nullptr;
                raw = nullptr;
            }
        }

        //The smart pointer is set to point to the null pointer. 
        //The reference count for the currently pointed to object, 
        //if any, is decremented.
        void reset()
        {
            #ifdef DEBUG 
            std::cout << "reset" << std::endl; 
            #endif
            std::lock_guard<std::mutex> lock(suo);
            if(counter != nullptr && counter->decrement() == 0)
            {
                //we are done, just delete it
                delete counter;
            }
            counter = nullptr;
            raw = nullptr;
        }

        //Replace owned resource with another pointer. 
        //If the owned resource has no other references, 
        //it is deleted. If p has been associated with some other smart pointer, 
        //the behavior is undefined.
        template <typename U> void reset(U *p)
        {
            reset();
            std::lock_guard<std::mutex> lock(suo);
            raw = static_cast<T*>(p);
            counter = new Ref<U>(p);
        }

        //Returns a pointer to the owned object. 
        //Note that this will be a pointer-to-const if T is a const-qualified type.
        T *get() const
        {
            return raw;
        }
        //A reference to the pointed-to object is returned. 
        //Note that this will be a const-reference if T is a const-qualified type.
        T &operator*() const
        {
            return *raw;
        }

        //The pointer is returned. 
        //Note that this will be a pointer-to-const if T is a const-qualified type.
        T *operator->() const
        {
            return raw;
        }

        //Returns true if the SharedPtr is not null.
        explicit operator bool() const
        {
            if(raw != nullptr)
                return true;
            return false;
        }

        void* ptr()
        {
            return raw;
        }

    };//

    //Returns true if the two smart pointers point 
    //to the same object or if they are both null. 
    //Note that implicit conversions may be applied.
    template <typename T1, typename T2>
    bool operator==(const SharedPtr<T1> & a, const SharedPtr<T2> & b)
    {
        if(a.raw == b.raw)
            return true;
        return false;
    }

    template <typename T>
    bool operator==(const SharedPtr<T> & a, std::nullptr_t)
    {
        if(!a.raw)
            return true;
        return false;
    }

    template <typename T>
    bool operator==(std::nullptr_t, const SharedPtr<T> & b)
    {   
        if(!b.raw)
            return true;
        return false;
    }
    template <typename T1, typename T2>
    bool operator!=(const SharedPtr<T1>& a, const SharedPtr<T2> & b)
    {
        return !(a==b);
    }
    //True if the SharedPtrs point to different objects, 
    //or one points to null while the other does not.
    template <typename T>
    bool operator!=(const SharedPtr<T> & a, std::nullptr_t b)
    {
        return !(a==b);
    }
    template <typename T>
    bool operator!=(std::nullptr_t a, const SharedPtr<T> & b)
    {
        return !(a==b);
    }
    template <typename T, typename U>
    SharedPtr<T> static_pointer_cast(const SharedPtr<U>& r) {
        return SharedPtr<T>(r);
    }

    template <typename T, typename U>
    SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U>& r) {
        return SharedPtr<T>(r, 1);
    }
}




#endif