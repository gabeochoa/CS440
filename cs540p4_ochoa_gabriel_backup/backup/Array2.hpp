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
        
        class BaseIterator
        {public:
        	
        	friend bool operator==(const BaseIterator& a, const BaseIterator & b)
            {
                return true;
            }
            friend bool operator==(const BaseIterator& a, BaseIterator & b)
            {
                return (a == const_cast<const BaseIterator&>(b));
            }
            friend bool operator==( BaseIterator& a, const BaseIterator & b)
            {
                return b == a;
            }
            friend bool operator!=( BaseIterator & a, BaseIterator & b)
            {return !(a==b);}
            friend bool operator!=( const BaseIterator & a, BaseIterator & b)
            {return !(a==b);}
            friend bool operator!=( BaseIterator & a, const BaseIterator & b)
            {return !(a==b);}
            friend bool operator!=( const BaseIterator & a, const BaseIterator & b)
            {return !(a==b);}
        };
        class FirstDimensionMajorIterator : BaseIterator
        { 
        	FirstDimensionMajorIterator& operator++()
            {
                //increment 
                return *this;
            }

            FirstDimensionMajorIterator operator++(int )
            {
                FirstDimensionMajorIterator rt = *this;
                operator++();
                return rt;
            }
        };
        class LastDimensionMajorIterator : BaseIterator
        {
        	LastDimensionMajorIterator& operator++()
            {
                //increment 
                return *this;
            }

            LastDimensionMajorIterator operator++(int )
            {
                FirstDimensionMajorIterator rt = *this;
                operator++();
                return rt;
            }
        };

        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  { I, Dims... }; 
            int total = 1;
            for(size_t i =0; i < dims.size(); i++)
            {
                total *= dims[i];
            }
            //printf("%d\n", total);
        }
        
        // The copy constructor must work. 
        // The dimensionality of the source array must be the same.
        // Note that a non-template copy constructor must be provided, in addtion to the member template copy constructor.
        Array(const Array &){}

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
		Nested operator[](unsigned i) const { return data[i]; }
        
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
}
#endif