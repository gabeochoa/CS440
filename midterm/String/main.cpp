/*
 * 50 pts:
 *
 * Implement a string which uses *reference* semantics, as opposed to value
 * semantics.  As usual:
 *
 *     - No memory leaks or other memory errors.
 *     - No warnings when compiled with -Wall -Wextra -pedantic.
 *
 * You may put all your code in the header file as inlined functions, or you
 * may put code in String.cpp.
 *
 * You may find the following useful:
 *
 *     std::string::c_str()
 *     strdup()
 *
 * Hint: Internally, you will need to use reference counting.
 *
 * This program prints out

Output operator:
hello
Test reference semantics:
jello
jello
Test concatenation:
hello, goodbye

 */



#include "String.hpp"
#include <string>

int
main() {

    cs540::String s1; // Initialize to "".
    // Consider using ctor delegation for these.
    cs540::String s2("hello");
    cs540::String s3(std::string("hello"));

    // After the below, s4 and s2 should point to the same data object.  Also,
    // no memory allocation should occur.
    cs540::String s4(s2);

    cs540::String s5;
    s5 = s2; // After this, also point to same data object.  Also, no memory allocation should occur.
    s5 = s5; // Handle self-assignment correctly.

    // Output.
    std::cout << "Output operator:" << std::endl;
    std::cout << s2 << std::endl;

    std::cout << "Test reference semantics:" << std::endl;
    // Index.
    s2[0] = 'j'; // Changes to 'j'.
    // Prints "jello".
    std::cout << s2 << std::endl;
    // Also prints "jello", since we are using reference semantics.
    std::cout << s5 << std::endl;

    // +5 pts, EC: Convert to std::string, implicitly.  Note that, as member functions,
    // conversion operators may also be const, and thus a non-const conversion
    // operator cannot be applied to a const object.
    std::string ss(s5);

    // +5 pts, EC: Concatentation, if you have time.
    {
        std::cout << "Test concatenation:" << std::endl;
        cs540::String s1("hello");
        cs540::String s2("goodbye");
        std::cout << s1 + ", " + s2 << std::endl;
    }
}
