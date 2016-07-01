#include "SharedPtr.hpp"
#include <stdio.h>
#include <new>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <errno.h>
#include <assert.h>


using namespace std;
using namespace cs540;


class A {
    public:
    virtual ~A() {
        //printf("%p deleted\n", (Obj *) this);
    }
};

class B : public A {
    public:
    virtual ~B() {}
};

class C : public A {
    public:
    virtual ~C() {}
};

// These tests overlap a lot with the ones in basic tests 1.
void
basic_tests_2() {

    {
        // Test default constructor.
        {
            SharedPtr<A> np;
            assert(!np);
        }

        // Test construction from object.
        {
            A *ap = new A;
            SharedPtr<A> a(ap);
            assert(a.get() == ap);
        }

        // Test construction from another SharedPtr of the same type.
        {
            SharedPtr<A> a(new A);
            SharedPtr<A> a2(a);
        }

        // Test construction from another SharedPtr of a derived type.
        {
            SharedPtr<B> b(new B);
            SharedPtr<A> a(b);
        }

        // Test assignment operator.
        {
            // Same type.
            SharedPtr<A> a1, a2(new A);
            a1 = a2;

            // Derived to base.
            SharedPtr<B> b(new B);
            a1 = b;

            // Object ptr.
            a1.reset(new A);

            // To Null.
            a1.reset();
        }

        // More misc tests.
        {
            SharedPtr<B> b(new B);
            SharedPtr<C> c(new C);

            
            printf("new B: %p\n", static_cast<B *>(b.get()));
            printf("new C: %p\n", static_cast<C *>(c.get()));

            printf("b: %p\n", &b);
            printf("c: %p\n", &c);
            

            // Initialization from base should not require cast.
            SharedPtr<A> a_base(b);

            // Default initialization and cast to base.
            SharedPtr<A> a_dc(b);
            // Note that this will use the templated constructor to do a conversion.
            // if a templated assignment does not exist.
            a_dc = b;

            // Static cast to base.
            SharedPtr<A> a_b = b;
            SharedPtr<A> a_c = c;
            
            printf("a_b: %p\n", &a_b);
            printf("a_c: %p\n", &a_c);
            

            // Dynamic downcast.
            SharedPtr<B> b2 = dynamic_pointer_cast<B>(a_b);
            // If the below is uncommented, we should get an error in the templated
            // assignment operator.  This will verify that that is being used rather
            // than templated constructors, etc.
            b2 = a_b;
            assert(b2);
            SharedPtr<C> c2 = dynamic_pointer_cast<C>(a_b);
            assert(!c2);
            
            printf("b2: %p\n", &b2);
            printf("c2: %p\n", &c2);
            

            // Dynamic downcast.
            SharedPtr<B> b3 = dynamic_pointer_cast<B>(a_c);
            assert(!b3);
            SharedPtr<C> c3 = dynamic_pointer_cast<C>(a_c);
            assert(c3);
            
            printf("b3: %p\n", &b3);
            printf("c3: %p\n", &c3);
            
        }
    }

    printf("Basic tests 2 passed.\n");
}

int main()
{
    basic_tests_2();
}