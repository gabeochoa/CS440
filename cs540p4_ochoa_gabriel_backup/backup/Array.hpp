#ifndef ARRAY2_GO
#define ARRAY2_GO

#include <vector>
#include <iostream>
#include <exception>
#include <tuple> 

namespace cs540
{
    class OutOfRange : public std::runtime_error
    {
        public:
            OutOfRange(const std::string& message) 
                : std::runtime_error(message) { };
            virtual const char* what() const throw()
            {
                return "OutOfRange Call";
            }
    };

	template <class T, size_t I, size_t... Dims>
	struct Array 
	{
		using Nested = typename Array<T, Dims...>::type;
	 	using type = std::array<Nested, I>;
	 	type data;
		std::vector<int> dims;
        
        class FirstDimensionMajorIterator;
        class LastDimensionMajorIterator;

        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  { I, Dims... }; 
            int total = 1;
            for(int i =0; i < dims.size(); i++)
            {
                total *= dims[i];
            }
            printf("%d\n", total);
        }
        
        // The copy constructor must work. 
        // The dimensionality of the source array must be the same.
        // Note that a non-template copy constructor must be provided, in addtion to the member template copy constructor.
        Array(const Array &);

        //   The copy constructor must work. The dimensionality of the source array must be the same.
        template <typename U>
        Array(const Array<U, I, Dims...> &);
        
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same. 
        // Self-assignment must be a no-op. Note that this non-template 
        // assignment operator must be provided, in addtion to the member 
        // template assignment operator.
        Array &operator=(const Array &);
        
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same.
        // Self-assignment must be a no-op.
        template <typename U>
        Array &operator=(const Array<U, I, Dims...> &);
        
        // T &operator[](int dim)
        // {
        //     return data[dim];
        // };//size_t i_1][size_t i_2]...[size_t i_D];

        // This is used to index into the array with range-checking.
        // If any given indices are out-of-range, then an OutOfRange
        // exception must be thrown. Note that this is a “conceptual”
        // operator only. Such an operator does not really exist. 
        // Instead, you must figure out how to provide this functionality. 
        // (Helper classes may be useful.)
		Nested operator[](unsigned i) { return data[i]; }
        
        //  Returns a FirstDimensionMajorIterator (nested classes) object pointing to the first element.
        FirstDimensionMajorIterator fmbegin();
        //    Returns a FirstDimensionMajorIterator (nested classes) object pointing one past the last element.
        FirstDimensionMajorIterator fmend();
        //   Returns a LastDimensionMajorIterator pointing to the first element.
        LastDimensionMajorIterator lmbegin();
        LastDimensionMajorIterator lmend();
	};
	 
	template <class T, size_t I>
	struct Array<T, I> 
	{
		using type = std::array<T, I>;  
		type data;
		T operator[](unsigned i) { return data[i]; }

	};


/*
	template<typename U, int dim>
    struct dataobj
    {
        dataobj<U, dim-1> operator[](int i){return dataobj<U, dim-1>();}
    };

    template<typename U, int dim>
    struct dataobj<U, 0>
    {  
        dataobj(int value)
        {

        }
        dataobj<U, 0>& operator=(dataobj<U, 0>&)
        {

        }
        dataobj<U, 0>& operator=(int value)
        {

        }
        U& operator[](int i){return U{};}
    };

    template <typename T, int ... Dims> 
    struct Array
    { 
        std::vector<T> data;
        std::vector<int> dims;
        
        dataobj<T, sizeof...(Dims)-1> operator[](unsigned i) { return dataobj<T, sizeof...(Dims)-1>(); }

        

        class FirstDimensionMajorIterator;
        class LastDimensionMajorIterator;

        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  { Dims... }; 
            int total = 1;
            for(int i =0; i < dims.size(); i++)
            {
                total *= dims[i];
            }
            printf("%d\n", total);
            data = std::vector<T>(total);
        }
        
        // The copy constructor must work. 
        // The dimensionality of the source array must be the same.
        // Note that a non-template copy constructor must be provided, in addtion to the member template copy constructor.
        Array(const Array &);

        //   The copy constructor must work. The dimensionality of the source array must be the same.
        template <typename U>
        Array(const Array<U, Dims...> &);
        
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same. 
        // Self-assignment must be a no-op. Note that this non-template 
        // assignment operator must be provided, in addtion to the member 
        // template assignment operator.
        Array &operator=(const Array &);
        
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same.
        // Self-assignment must be a no-op.
        template <typename U>
        Array &operator=(const Array<U, Dims...> &);
        
        // T &operator[](int dim)
        // {
        //     return data[dim];
        // };//size_t i_1][size_t i_2]...[size_t i_D];

        // This is used to index into the array with range-checking.
        // If any given indices are out-of-range, then an OutOfRange
        // exception must be thrown. Note that this is a “conceptual”
        // operator only. Such an operator does not really exist. 
        // Instead, you must figure out how to provide this functionality. 
        // (Helper classes may be useful.)
        //const T &operator[size_t i_1][size_t i_2]...[size_t i_D] const;

        //  Returns a FirstDimensionMajorIterator (nested classes) object pointing to the first element.
        FirstDimensionMajorIterator fmbegin();
        //    Returns a FirstDimensionMajorIterator (nested classes) object pointing one past the last element.
        FirstDimensionMajorIterator fmend();
        //   Returns a LastDimensionMajorIterator pointing to the first element.
        LastDimensionMajorIterator lmbegin();

        LastDimensionMajorIterator lmend();
        //
    };//
*/
/*
    struct Array2
    {
        struct ROW_OBJ
        {
            Array2& data;//
            int row,r;//
            ROW_OBJ(Array2& _data, int _row, int _r):
            data(_data), row(_row), r(_r)
            {

            }
           int& operator[](const int& index)
            {
                return data.get(r,index);//
            }  
        };//

        std::vector<int> data;//
        int rows;//
        int cols;//

        Array2():Array2(0){}
        Array2(int r):Array2(r,0){}
        Array2(int r, int c): rows(r), cols(c)
        {
            data = std::vector<int>(rows*cols);////= (int*) new int[rows*cols];//
        }
    
        ~Array2()
        {
            //delete data;//
        }
        std::vector<int>::iterator begin()
        {
            return data.begin();////Iterator(data, rows, 0, 0);//
        }
        std::vector<int>::iterator end()
        {
            return data.end();////Iterator();//
        }

        int& get(int a, int b)
        {
            return data[a*rows + b];//
        } 
        ROW_OBJ operator[](const int& index)
        {
            return ROW_OBJ(*this, rows, index);//
        } 

    };//
*/
}
#endif