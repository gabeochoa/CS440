/*
 * For this problem, you are to implement calln(), which given a count n, a
 * pointer to an object, a pointer to a member function, and arguments; will
 * call the member function n times with the given arguments.  The results are
 * returned in a std::vector of the appropriate type.  If the member function
 * returns void, then calln() will return void also.
 *
 * calln() must be a variadic template, and be able to handle member functions
 * with any number of arguments.
 *
 * You must use the -std=c++14 flag when compiling.
 *
 */
#include <vector>
#include <iostream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <type_traits>



template<class T, class P, typename... Args, typename ... Param>
auto calln(int times, T* t, P p, Args ... args) -> std::vector<decltype(((*t).*p)(args ... ))>
{ 
    std::vector<decltype(((*t).*p)(args ... ))> ret;
    for(int i=0; i<times; i++)
    {
        ret.push_back(((*t).*p)( args ... ));
    }
    return ret;
}
/*
template<class T, class P, typename... Args>
void calln(int times, T* t, P p, Args ... args)
{ 
    for(int i=0; i<times; i++)
    {
        ((*t).*p)( args ... );
    }
}
*/

/*
    
template<class T, typename R, typename... Args,   typename ...Params>
void calln(int times, T* t, R T::*p (Args...), Params ... prm)
{ 
    for(int i=0; i<times; i++)
    {
        ((*t).*p)( prm ... );
    }
}

template<class T, typename R, typename... Args,   typename ...Params>
auto calln(int times, T* t, R T::*p (Args...), Params ... prm)
{ 
    std::vector<R> ret;
    for(int i=0; i<times; i++)
    {
        ret.push_back(((*t).*p)( prm ... ));
    }
    return ret;
}

*/


struct A {
    int foo(double) {
        return i++;
    }
    static int i;
};
int A::i;

struct B {
    std::string f(double x, const char *s) {
        std::ostringstream out;
        out << i++ << ", " << x << ": " << s;
        return out.str();
    }
    static int i;
};
int B::i;

struct C {
    void f(int v) {
        std::cout << "The square of " << v << " is " << v*v << std::endl;
    }
};



int
main() {
    {
        A a;
        // Calls a.f(3.14) 10 times.
        auto rv = calln(10, &a, &A::foo, 3.14);
        assert(rv.size() == 10 && "You should have returned a vector of 10 values");
        static_assert(std::is_integral<decltype(rv)::value_type>::value, "The vector returned here should have been a vector of ints");
        for (auto i : rv) {
            std::cout << i << std::endl;
        }
    }
    {
        B b;
        // Calls b.f(3.14, "hello") 5 times.  Note that 3 is an int, but the
        // parameter type is a double.
        std::vector<std::string> rv = calln(5, &b, &B::f, 3, "hello");
        assert(rv.size() == 5 && "You should have returned a vector of 5 values");
        for (auto i : rv) {
            std::cout << i << std::endl;
        }
    }
    {/*
        C c;
        // Call c.f(12) 12 times. Note that the return type of c.f is void.
        calln(12, &c, &C::f, 12);
        */
    }
}
