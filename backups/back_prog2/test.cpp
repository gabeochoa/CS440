#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <random>
#include <unistd.h>
#include "deck.hpp"

// May assume memcpy()-able.
// May assume = operator.

/*
 * Track memory allocation.
 */

// This functions like an assert(), but is careful not to do anything that
// calls malloc(), so can be used before malloc has been initialized.
#define xyzzy_check(e) do {                                                    \
    if (!(e)) {                                                                \
        const char s[] = #e "\n";                                              \
        write(2, s, sizeof s);                                                 \
        abort();                                                               \
    }                                                                          \
} while (0)

size_t alloc_call_count;
size_t total_bytes_allocated;

namespace {
    bool initialized;
    void *(*default_malloc)(size_t);
    void *(*default_realloc)(void *, size_t);
    void *(*default_calloc)(size_t, size_t);
    void
    alloc_init() {
        if (!initialized) {
            default_malloc = (void*(*)(size_t)) dlsym(RTLD_NEXT, "malloc"); xyzzy_check(default_malloc != nullptr);
            default_realloc = (void*(*)(void*,size_t)) dlsym(RTLD_NEXT, "realloc"); xyzzy_check(default_realloc != nullptr);
            default_calloc = (void*(*)(size_t,size_t)) dlsym(RTLD_NEXT, "calloc"); xyzzy_check(default_calloc != nullptr);
            initialized = true;
        }
    }
}

void *
malloc(size_t size) noexcept {
    alloc_init();
    void *ptr = default_malloc(size);
    alloc_call_count++;
    total_bytes_allocated += size;
    return ptr;
}

void *
realloc(void *p, size_t size) noexcept {
    alloc_init();
    void *ptr = default_realloc(p, size);
    alloc_call_count++;
    total_bytes_allocated += size;
    return ptr;
}

void *
calloc(size_t num, size_t size) noexcept {
    alloc_init();
    void *ptr = default_calloc(num, size);
    alloc_call_count++;
    total_bytes_allocated += size;
    return ptr;
}

/*
 * Test for int.
 */

bool
int_less(const int &o1, const int &o2) {
    return o1 < o2;
}

int
main() {

    // Test that it can handle other types.  Tests are the same, more or less.
    /*
    {
        Deque_int deq;
        Deque_int_ctor(&deq, int_less);

        assert(deq.size(&deq) == 0);
        assert(deq.empty(&deq));

        // Should print "---- Deque_int, 10".
        printf("---- %s, %d\n", deq.type_name, int(sizeof(deq.type_name)));
        // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        assert(sizeof deq.type_name == 10);

        deq.push_back(&deq, 1);
        deq.push_back(&deq, 2);
        deq.push_back(&deq, 3);
        deq.push_front(&deq, 0);
        deq.push_front(&deq, -1);

        printf("%d\n", deq.front(&deq));
        printf("%d\n", deq.back(&deq));
        assert(deq.front(&deq) == -1);
        assert(deq.back(&deq) == 3);

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq) == 0);
        assert(deq.back(&deq) == 2);

        assert(deq.size(&deq) == 3);

        for (Deque_int_Iterator it = deq.begin(&deq);
         !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
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
*/
    {
        Deque_int deq;
        Deque_int_ctor(&deq, int_less);

        deq.push_back(&deq, 0);
        deq.push_back(&deq, 1);
        deq.push_back(&deq, 2);
        deq.push_back(&deq, 3);
        deq.push_back(&deq, 4);
        deq.push_back(&deq, 5);
        deq.push_back(&deq, 6);
        deq.push_back(&deq, 7);
        deq.push_back(&deq, 8);
        assert(deq.at(&deq, 0)== 0);
        assert(deq.at(&deq, 1)== 1);
        assert(deq.at(&deq, 2)== 2);
        deq.pop_front(&deq);
        assert(deq.at(&deq, 0)== 1);
        deq.pop_front(&deq);
        assert(deq.at(&deq, 0)== 2);
        assert(deq.front(&deq)== 2);
        deq.push_back(&deq, 99);
        deq.push_back(&deq, 100);
        deq.push_back(&deq, 69);
        deq.push_back(&deq, 42);

        int correct[] = {0 , 0 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 99 , 100 , 69 , 42 ,  0 , 0 , 0 , 0 , 0 , 0 , 0};
        for(int i=0; i<deq.d_alloc; i++)
            assert(deq.d_data[i] == correct[i]);
        deq.clear(&deq);
        deq.dtor(&deq);
    }


        Deque_int deq;
        Deque_int_ctor(&deq, int_less);

        deq.printall(&deq);

        deq.push_front(&deq, 0);
        deq.printall(&deq);
        deq.push_front(&deq, 1);
        deq.printall(&deq);
        deq.push_front(&deq, 2);
        deq.printall(&deq);
        deq.push_front(&deq, 3);
        deq.printall(&deq);
        deq.push_front(&deq, 4);
        deq.printall(&deq);
        deq.push_front(&deq, 5);
        deq.printall(&deq);
        
        deq.pop_back(&deq);
        deq.printall(&deq);
        
        deq.pop_back(&deq);
        deq.printall(&deq);
        
        deq.pop_back(&deq);
        deq.printall(&deq);
        deq.pop_back(&deq);
        deq.printall(&deq);
        deq.pop_back(&deq);
        deq.printall(&deq);
        deq.pop_back(&deq);
        deq.printall(&deq);
        
        deq.clear(&deq);
        deq.dtor(&deq);
/*
    // Test equality.  It is undefined behavior if the two deques were constructed with different
    // comparison functions.
    {
        Deque_int deq1, deq2;
        Deque_int_ctor(&deq1, int_less);
        Deque_int_ctor(&deq2, int_less);

        deq1.push_back(&deq1, 1);
        deq1.push_back(&deq1, 2);
        deq1.push_back(&deq1, 3);
        deq2.push_back(&deq2, 1);
        deq2.push_back(&deq2, 2);
        deq2.push_back(&deq2, 3);

        assert(Deque_int_equal(deq1, deq2));

        deq1.pop_back(&deq1);
        assert(!Deque_int_equal(deq1, deq2));
        deq1.push_back(&deq1, 4);
        assert(!Deque_int_equal(deq1, deq2));

        deq1.dtor(&deq1);
        deq2.dtor(&deq2);
    }
    */
   // Print allocation info
   printf("%zd allocations totalling %zd bytes\n", alloc_call_count, total_bytes_allocated);
}
