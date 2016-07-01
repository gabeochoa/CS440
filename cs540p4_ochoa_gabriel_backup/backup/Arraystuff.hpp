#ifndef ARRAY2_GO
#define ARRAY2_GO

#include <vector>
#include <iostream>
#include <exception>
#include <initializer_list>

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
    // Returns the product of all elements.
    constexpr auto product(std::initializer_list<std::size_t> il) {
        std::size_t prod = 1;
        for (auto f : il) {
            prod *= f;
        }
        return prod;
    }
	
	template <class Type, size_t F, size_t... Dims>
	struct BaseArray
	{
		std::vector<Type> data;
		std::vector<size_t> dims;
		BaseArray() 
        {
            dims =  { F, Dims... }; 
            int total = product({F, Dims...});
            static_assert(product({F, Dims...}) != 0, "Zeroed Dimension");
            data = std::vector<Type>(total);
            //printf("%d\n", total);
        }
	};  

    template <class Type, size_t A, size_t... Dims>
    struct Array : public BaseArray<Type, A, Dims...>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R, size_t S, size_t T, size_t U, size_t V, size_t W, size_t X, size_t Y>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y>
    {};


    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R, size_t S, size_t T, size_t U, size_t V, size_t W, size_t X>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R, size_t S, size_t T, size_t U, size_t V, size_t W>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R, size_t S, size_t T, size_t U, size_t V>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R, size_t S, size_t T, size_t U>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R, size_t S, size_t T>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R, size_t S>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q, size_t R>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P, size_t Q>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O, size_t P>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N, size_t O>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M, size_t N>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M, N>
    {};
    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L, size_t M>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L, M> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L, M>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K, size_t L>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K, L> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K, L>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J, size_t K>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J, K> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J, K>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I, size_t J>
    struct Array< Type, A, B, C, D, E, F, G, H, I, J> : public BaseArray<Type, A, B, C, D, E, F, G, H, I, J>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H, size_t I>
    struct Array< Type, A, B, C, D, E, F, G, H, I> : public BaseArray<Type, A, B, C, D, E, F, G, H, I>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G, size_t H>
    struct Array< Type, A, B, C, D, E, F, G, H> : public BaseArray<Type, A, B, C, D, E, F, G, H>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F, size_t G>
    struct Array< Type, A, B, C, D, E, F, G> : public BaseArray<Type, A, B, C, D, E, F, G>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E, size_t F>
    struct Array< Type, A, B, C, D, E, F> : public BaseArray<Type, A, B, C, D, E, F>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D, size_t E>
    struct Array< Type, A, B, C, D, E> : public BaseArray<Type, A, B, C, D, E>
    {};

    template <class Type,size_t A, size_t B, size_t C, size_t D>
    struct Array< Type, A, B, C, D> : public BaseArray<Type, A, B, C, D>
    {};

    template <class Type,size_t A, size_t B, size_t C>
    struct Array< Type, A, B, C> : public BaseArray<Type, A, B, C>
    {
     std::vector<Type> data;
        std::vector<size_t> dims;
        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  {A, B, C}; 
            int total = product({A, B, C});
            static_assert(product({A, B, C}) != 0, "Zeroed Dimension");
            data = std::vector<Type>(total);
            printf("%d\n", total);
        }
        
        // The copy constructor must work. 
        // The dimensionality of the source array must be the same.
        // Note that a non-template copy constructor must be provided, in addtion to the member template copy constructor.
        Array(const Array & n)
        {
            if(this != &n)
            {
                dims = n.dims;
                copy( n.data.begin(),  n.data.end(), back_inserter(data));
            }
        }
        //   The copy constructor must work. The dimensionality of the source array must be the same.
        template <typename Utype>
        Array(const Array<Utype, A> & n)
        {
            dims = n.dims;
            copy( n.data.begin(),  n.data.end(), back_inserter(data));
        }
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same. 
        // Self-assignment must be a no-op. Note that this non-template 
        // assignment operator must be provided, in addtion to the member 
        // template assignment operator.
        Array &operator=(const Array & n)
        {
            if(this != &n)
            {
                dims = n.dims;
                copy( n.data.begin(),  n.data.end(), back_inserter(data));
            }
            return *this;
        }
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same.
        // Self-assignment must be a no-op.
        template <typename Utype>
        Array &operator=(const Array<Utype, A> & n)
        {
            dims = n.dims;
            copy( n.data.begin(),  n.data.end(), back_inserter(data));
            return *this;
        }
        // This is used to index into the array with range-checking.
        // If any given indices are out-of-range, then an OutOfRange
        // exception must be thrown. Note that this is a “conceptual”
        // operator only. Such an operator does not really exist. 
        // Instead, you must figure out how to provide this functionality. 
        // (bracket classes may be useful.)
        struct threedim
        {
            std::vector<Type> data;
            int index;
            std::vector<size_t> dims;
            
            threedim(const std::vector<Type>& dt, int idx, const std::vector<size_t>& dms)
            :data(dt), index(idx), dims(dms)
            {

            }
            Type& operator[](size_t i) const
            {
                if(i > dims[2]){
                    std::cout << i << std::endl;
                    std::cout << dims[2] << std::endl;
                    throw cs540::OutOfRange("Third Dimension Out of Range");
                }
                return const_cast<Type&>(data[index + i]);
            }
        };
        struct twodim
        {
            std::vector<Type> data;
            int index;
            std::vector<size_t> dims;
            
            twodim(const std::vector<Type>& dt, int idx, const std::vector<size_t>& dms)
            :data(dt), index(idx), dims(dms)
            {

            }
            threedim operator[](size_t i) const
            {
                if(i > dims[1])
                    throw cs540::OutOfRange("Second Dimension Out of Range");
                return threedim(data, index*dims[1], dims);
            }
        };
        twodim operator[](size_t i) const
        {
            if(i > dims[0])
                throw cs540::OutOfRange("First Dimension Out of Range");
            return twodim(data, i*dims[0], dims);
        }
        /*
        //  Returns a FirstDimensionMajorIterator (nested classes) object pointing to the first element.
        FirstDimensionMajorIterator fmbegin()
        {
            return FirstDimensionMajorIterator(data, dims, 0);
        }
        //    Returns a FirstDimensionMajorIterator (nested classes) object pointing one past the last element.
        FirstDimensionMajorIterator fmend()
        {
            return FirstDimensionMajorIterator(data, dims, -1);
        }
        //   Returns a LastDimensionMajorIterator pointing to the first element.
        LastDimensionMajorIterator lmbegin()
        {
            return LastDimensionMajorIterator(data, dims, 0);
        }
        LastDimensionMajorIterator lmend()
        {
            return LastDimensionMajorIterator(data, dims, -1);
        }
        */
    };

    template <class Type,size_t A, size_t B>
    struct Array< Type, A, B> : public BaseArray<Type, A, B>
    {   
        std::vector<Type> data;
        std::vector<size_t> dims;
        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  {A, B}; 
            int total = product({A, B});
            static_assert(product({A, B}) != 0, "Zeroed Dimension");
            data = std::vector<Type>(total);
            printf("%d\n", total);
        }
        
        // The copy constructor must work. 
        // The dimensionality of the source array must be the same.
        // Note that a non-template copy constructor must be provided, in addtion to the member template copy constructor.
        Array(const Array & n)
        {
            if(this != &n)
            {
                dims = n.dims;
                copy( n.data.begin(),  n.data.end(), back_inserter(data));
            }
        }
        //   The copy constructor must work. The dimensionality of the source array must be the same.
        template <typename Utype>
        Array(const Array<Utype, A> & n)
        {
            dims = n.dims;
            copy( n.data.begin(),  n.data.end(), back_inserter(data));
        }
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same. 
        // Self-assignment must be a no-op. Note that this non-template 
        // assignment operator must be provided, in addtion to the member 
        // template assignment operator.
        Array &operator=(const Array & n)
        {
            if(this != &n)
            {
                dims = n.dims;
                copy( n.data.begin(),  n.data.end(), back_inserter(data));
            }
            return *this;
        }
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same.
        // Self-assignment must be a no-op.
        template <typename Utype>
        Array &operator=(const Array<Utype, A> & n)
        {
            dims = n.dims;
            copy( n.data.begin(),  n.data.end(), back_inserter(data));
            return *this;
        }
        // This is used to index into the array with range-checking.
        // If any given indices are out-of-range, then an OutOfRange
        // exception must be thrown. Note that this is a “conceptual”
        // operator only. Such an operator does not really exist. 
        // Instead, you must figure out how to provide this functionality. 
        // (bracket classes may be useful.)
        struct twodim
        {
            std::vector<Type> data;
            int index;
            std::vector<size_t> dims;
            
            twodim(const std::vector<Type>& dt, int idx, const std::vector<size_t>& dms)
            :data(dt), index(idx), dims(dms)
            {

            }
            Type& operator[](size_t i) const
            {
                if(i > dims[1])
                    throw cs540::OutOfRange("Out of Range");
                return const_cast<Type&>(data[index + i]);
            }
        };
        twodim operator[](size_t i) const
        {
            if(i > dims[0])
                throw cs540::OutOfRange("Out of Range");
            return twodim(data, i*dims[0], dims);
        }
        /*
        //  Returns a FirstDimensionMajorIterator (nested classes) object pointing to the first element.
        FirstDimensionMajorIterator fmbegin()
        {
            return FirstDimensionMajorIterator(data, dims, 0);
        }
        //    Returns a FirstDimensionMajorIterator (nested classes) object pointing one past the last element.
        FirstDimensionMajorIterator fmend()
        {
            return FirstDimensionMajorIterator(data, dims, -1);
        }
        //   Returns a LastDimensionMajorIterator pointing to the first element.
        LastDimensionMajorIterator lmbegin()
        {
            return LastDimensionMajorIterator(data, dims, 0);
        }
        LastDimensionMajorIterator lmend()
        {
            return LastDimensionMajorIterator(data, dims, -1);
        }
        */     
    };

    template <class Type,size_t A>
    struct Array< Type, A> : public BaseArray<Type, A>
    {
        struct FirstDimensionMajorIterator
        { 
            std::vector<Type> data;
            typename std::vector<Type>::iterator iter;
            std::vector<size_t> dims;
            FirstDimensionMajorIterator(const std::vector<Type>& _data, const std::vector<size_t>& _dims, int e)
            : data(_data), dims(_dims)
            {
                if(e == -1)
                    iter = data.end();
                else
                    iter = data.begin();
            }
            FirstDimensionMajorIterator& operator++()
            {iter++;return *this;}
            FirstDimensionMajorIterator operator++(int )
            {
                FirstDimensionMajorIterator rt = *this;
                operator++();
                return rt;
            }
            Type &operator*() const{return *iter;}
        };
        struct LastDimensionMajorIterator : public FirstDimensionMajorIterator
        {};
        std::vector<Type> data;
        std::vector<size_t> dims;
        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  {A}; 
            int total = product({A});
            static_assert(product({A}) != 0, "Zeroed Dimension");
            data = std::vector<Type>(total);
            printf("%d\n", total);
        }
        
        // The copy constructor must work. 
        // The dimensionality of the source array must be the same.
        // Note that a non-template copy constructor must be provided, in addtion to the member template copy constructor.
        Array(const Array & n)
        {
            if(this != &n)
            {
                dims = n.dims;
                copy( n.data.begin(),  n.data.end(), back_inserter(data));
            }
        }
        //   The copy constructor must work. The dimensionality of the source array must be the same.
        template <typename Utype>
        Array(const Array<Utype, A> & n)
        {
            dims = n.dims;
            copy( n.data.begin(),  n.data.end(), back_inserter(data));
        }
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same. 
        // Self-assignment must be a no-op. Note that this non-template 
        // assignment operator must be provided, in addtion to the member 
        // template assignment operator.
        Array &operator=(const Array & n)
        {
            if(this != &n)
            {
                dims = n.dims;
                copy( n.data.begin(),  n.data.end(), back_inserter(data));
            }
            return *this;
        }
        // The assignment operator must work. 
        // The dimensionality of the source array must be the same.
        // Self-assignment must be a no-op.
        template <typename Utype>
        Array &operator=(const Array<Utype, A> & n)
        {
            dims = n.dims;
            copy( n.data.begin(),  n.data.end(), back_inserter(data));
            return *this;
        }
        // This is used to index into the array with range-checking.
        // If any given indices are out-of-range, then an OutOfRange
        // exception must be thrown. Note that this is a “conceptual”
        // operator only. Such an operator does not really exist. 
        // Instead, you must figure out how to provide this functionality. 
        // (bracket classes may be useful.)
        Type& operator[](size_t i) const
        {
            if(i > dims[0])
                throw cs540::OutOfRange("Out of Range");
            return const_cast<Type&>(data[i]);
        }
        
        //  Returns a FirstDimensionMajorIterator (nested classes) object pointing to the first element.
        FirstDimensionMajorIterator fmbegin()
        {
            return FirstDimensionMajorIterator(data, dims, 0);
        }
        //    Returns a FirstDimensionMajorIterator (nested classes) object pointing one past the last element.
        FirstDimensionMajorIterator fmend()
        {
            return FirstDimensionMajorIterator(data, dims, -1);
        }
        //   Returns a LastDimensionMajorIterator pointing to the first element.
        LastDimensionMajorIterator lmbegin()
        {
            return LastDimensionMajorIterator(data, dims, 0);
        }
        LastDimensionMajorIterator lmend()
        {
            return LastDimensionMajorIterator(data, dims, -1);
        }
        
    };

}//ends namespace
#endif

