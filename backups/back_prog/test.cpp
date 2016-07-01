#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <random>
#include <iostream>
#include "Deque.hpp"


// May assume memcpy()-able.
// May assume = operator.

/*
 * Test for int.
 */

bool
int_less(const int &o1, const int &o2) {
    return o1 < o2;
}

int main()
{
    // Test that it can handle other types.  Tests are the same, more or less.
    {
        Deque deq;

        Deque_ctor(&deq, int_less);
 
        assert(deq.size(&deq) == 0);
        assert(deq.empty(&deq));

        // Should print "---- Deque_int, 10".
        printf("---- %s, %d\n", deq.type_name, int(sizeof(deq.type_name)));
        //std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        assert(sizeof deq.type_name == 8);

        //deq.printall(&deq);

        deq.push_back(&deq, 1);
        //deq.printall(&deq);
        deq.push_back(&deq, 2);
        //deq.printall(&deq);
        deq.push_back(&deq, 3);
        //deq.printall(&deq);
        deq.push_front(&deq, 0);
        //deq.printall(&deq);
        deq.push_front(&deq, -1);

        //deq.printall(&deq);

        printf("%d\n", deq.front(&deq));
        printf("%d\n", deq.back(&deq));
        assert(deq.front(&deq) == -1);
        assert(deq.back(&deq) == 3);

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq) == 0);
        assert(deq.back(&deq) == 2);
        assert(deq.size(&deq) == 3);

        for (Deque_Iterator it = deq.begin(&deq);
         !Deque_Iterator_equal(it, deq.end(&deq)); 
         it.inc(&it))
        {
            printf("%d\n", it.deref(&it));
        }

        // Test decrement.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it) == 2);
        }

        printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            printf("%d: %d\n", int(i), deq.at(&deq, i));
        }

        deq.clear(&deq);

        deq.dtor(&deq);

    }
}

