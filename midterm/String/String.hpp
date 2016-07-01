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
*/

#ifndef ARRAY2_GO
#define ARRAY2_GO
#include <string>
#include <string.h>
#include <cstring>
#include <iostream>

namespace cs540
{
    struct String
    {
        char* val = nullptr;
        int size = 0;
        int alloc = -1;
        String(): val(nullptr){}
        String(const String& other)
        {
            val = other.val;
        }
        String(const std::string& other)
        {
            val = strdup(other.c_str());
            // if(alloc > 0)
            //     delete tmp;
            // alloc++;

        }
        ~String()
        {
            // if(alloc > 0)
            // {
            //     alloc--;
            // }
            // else if(alloc == 0)
            //     delete val;
        }

        String& operator+(const char* c)
        {
            // char* tmp = val;
            val = strcat(String(val).val, String(c).val);
            // if(alloc > 0)
            // {
                // delete tmp;
                // alloc--;
            // }
            return *this;
        }
        String& operator+(const String& c)
        {
            // char* tmp = val;
            val = strcat(String(val).val, c.val);
            // if(alloc > 0)
            // {
            //     delete tmp;
            //     alloc--;
            // }
            return *this;
        }

        char& operator[](const int& index)
        {
            return val[index];
        } 

        operator std::string() const 
        {
            return std::string(val);    
        }
        friend std::ostream& operator<<(std::ostream& os, const String& dt);
};

std::ostream& operator<<(std::ostream& os, const String& dt)
{
    os << dt.val;
    return os;
}


}

#endif