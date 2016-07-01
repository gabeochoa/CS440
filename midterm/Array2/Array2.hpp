/*
* 50 pts:
*
* For this problem, you are to implement a 2D array class. The array is
* dynamic in the sense that the dimensions can be determined at run time. As
* usual:
*
*     - No memory leaks or other memory errors.
*     - No warnings when compiled with -Wall -Wextra -pedantic.
*
* You may put all your code in the header file as inlined functions, or you
* may put code in Array2.cpp.
*/
#ifndef ARRAY2_GO
#define ARRAY2_GO

#include <vector>
#include <string>


namespace cs540
{
    struct Array2
    {
        /*
        struct Iterator
        {
            int* data;
            int row;
            int r,c;
            Iterator(): data(nullptr), r(0), c(0){}
            Iterator(int* _dt): data(_dt), row(0),r(0), c(0){}
            Iterator(int* _dt, int width, int ro, int co): data(_dt), row(width), r(ro), c(co){}
            Iterator(const Iterator & it)
            {
                data = it.data;
                row = it.row;
                r = it.r;
                c = it.c;
            }
            ~Iterator()
            {

            }
            Iterator& operator=(const Iterator & it)
            {
                data = it.data;
                row = it.row;
                r = it.r;
                c = it.c;
                return *this;
            }
            Iterator& operator--()
            {
                Iterator rt = *this;
                c--;
                if(c <= 0)
                {
                    c = row;
                    r--;
                }
                return rt;
            }
            Iterator operator--(int dummy)
            {
                c--;
                if(c <= 0)
                {
                    c = row-1;
                    r--;
                }
                return *this;
            }
            Iterator &&operator++()
            {
                Iterator rt = *this;
                c++;
                if(c == row)
                {
                    c = 0;
                    r++;
                }
                return Iterator(rt);
            }
            Iterator operator++(int dummy)
            {
                c++;
                if(c == row)
                {
                    c = 0;
                    r++;
                }
                return *this;
            }
            int& operator*() const
            {
                return data[r*row+c];
            }
            int* operator->() const
            {
                return &(data[r*row+c]);
            }

            bool operator==(const Iterator & b)
            {
                return false;
            }

            bool operator!=(const Iterator & b)
            {return !((*this)==b);}
        };
        */

        struct ROW_OBJ
        {
            Array2& data;
            int row,r;
            ROW_OBJ(Array2& _data, int _row, int _r):
            data(_data), row(_row), r(_r)
            {

            }
           int& operator[](const int& index)
            {
                return data.get(r,index);
            }  
        };

        std::vector<int> data;
        //int* data;
        int rows;
        int cols;

        Array2():Array2(0){}
        Array2(int r):Array2(r,0){}
        Array2(int r, int c): rows(r), cols(c)
        {
            data = std::vector<int>(rows*cols);//= (int*) new int[rows*cols];
        }
    
        ~Array2()
        {
            //delete data;
        }
        std::vector<int>::iterator begin()
        {
            return data.begin();//Iterator(data, rows, 0, 0);
        }
        std::vector<int>::iterator end()
        {
            return data.end();//Iterator();
        }

        int& get(int a, int b)
        {
            return data[a*rows + b];
        } 
        ROW_OBJ operator[](const int& index)
        {
            return ROW_OBJ(*this, rows, index);
        } 

    };


}
#endif