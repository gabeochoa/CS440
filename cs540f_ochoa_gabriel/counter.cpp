#include <iostream>

/*
 * For this problem, you must implement the Counter<T> class template and any
 * additional auxilliary funtions or classes to create a way of counting the
 * number of objects of all types, even with multiple inheritance.  Note that
 * subjects don't count as separate objects.
 *
 */
#include <vector>
#include <string>
#include <typeinfo>
#include <map>

struct compare 
{
    bool operator ()(const std::type_info* a, const std::type_info* b) const {
        return a->before(*b);
    }
};

template <typename T>
struct Counter
{public:

    static std::map<const std::type_info*, int> m;

    Counter()
    {
        //if(cc == 0)
        {
            auto pos = m.find(&typeid(T));
            if (pos == m.end()) {
                //cc++;
                m[&typeid(T)] = 1;
            } else {
                m[&typeid(T)] = (m[&typeid(T)]+1);
            }
            cc++;
        }
    }

    virtual ~Counter()
    {
        m[&typeid(T)] = (m[&typeid(T)]-1);
        //--cc;
    }
    static int count()
    {
        return m[&typeid(T)];//cc;
    }
    static int cc;
};
template <typename T> int Counter<T>::cc( 0 );
template <typename T> std::map<const std::type_info*, int> Counter<T>::m;

class A : private Counter<A> {
    int i;
};

class B : private Counter<B> {
    int i;
};

// User must always put Counter base class last, so you may assume that.
class C : public A, public B, private Counter<C> {
    int i;
};

int main() {
    A a1;

    {
        B b1, b2;
        C c1, c2, c3;

        // Should print 1 (subojects don't count).
        std::cout << Counter<A>::count() << std::endl;
        // Should print 2.
        std::cout << Counter<B>::count() << std::endl;
        // Should print 3.
        std::cout << Counter<C>::count() << std::endl;
    }
    // Should now print 0.
    std::cout << Counter<C>::count() << std::endl;
    // Should also print 0.
    std::cout << Counter<B>::count() << std::endl;
    // Should still print 1.
    std::cout << Counter<A>::count() << std::endl;
}
