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

	template <typename T, size_t n> struct bracket;

	template <typename T, size_t N>
	struct bracket 
	{
        std::vector<size_t> dims;
        std::vector<T> data;
		size_t n;
		bracket(const std::vector<size_t>& ds, const std::vector<T>& dt, size_t i) : dims(ds), data(dt), n(i) { }
		bracket<T, N - 1> operator[](size_t i) 
		{
            std::cout << "Dims " << dims.size();
			std::cout << "\tN: " << N;
			std::cout << "\ti: " << i << std::endl;
			if(N > dims.size()){
				throw cs540::OutOfRange("Out of Range");
			}
			//std::cout << "Dims " << dims.size()-N << std::endl;
			//std::cout << i << std::endl;
			if(dims[dims.size()-N] < i)
			{
				throw cs540::OutOfRange("Out of Range");
			}
			return bracket<T, N - 1>(dims, data, i*N);
		}
	};

	template <typename T> 
	struct bracket<T, 2> 
	{
		std::vector<size_t> dims;
        std::vector<T> data;
		size_t n;
        bracket(const std::vector<size_t>& ds, const std::vector<T>& dt, size_t i) : dims(ds), data(dt), n(i) { }
		bracket(const bracket<T, 2>& b)
		{
			dims = (b.dims);
			n = (b.n);
		}
		T& operator=(int na)
		{
			data[n] = na;
			return const_cast<T&>(data[n]);
		}
		T& operator[](size_t i) 
		{
			n = i;
            std::cout << "**** " << dims.size();
            std::cout << "\tN: " << 1;
            std::cout << "\ti: " << i << std::endl;
			if(dims[dims.size()-1] < i)
			{
				throw cs540::OutOfRange("Out of Range");
			}
            return const_cast<T&>(data[i]);
		}
	};

	template <class T, size_t F, size_t... Dims>
	struct Array 
	{
		std::vector<T> data;
		std::vector<size_t> dims;

        struct BaseIterator
        {public:
            friend std::ostream &operator<<(std::ostream &os, const BaseIterator &ind) 
            {
                return os << ind.cur_ind;
            }
            size_t cur_ind;
            bool isend = false;
            typename Array<T, Dims...>::BaseIterator nested_BI;
            BaseIterator(): cur_ind(0){}
            BaseIterator(int a)
            {
                cur_ind = 0;
                if(a == -1)
                    isend = true;
            }
            bool FDinc()
            {
                if(isend)
                    return false;
                if(nested_BI.FDinc())
                {
                    nested_BI.cur_ind = 0;
                    if(++cur_ind == F)
                    {
                        return true;
                    }
                }
                return false;
            }
            void LDinc()
            {
                if(isend)
                    return; 
                if(++cur_ind == F)
                {
                    cur_ind = 0;
                    nested_BI.LDinc();
                }
            }
            friend bool operator==(const BaseIterator& a, const BaseIterator & b)
            {
                if(a.isend != b.isend)
                    return false;
                if(a.cur_ind == b.cur_ind)
                {
                    //std::cout << "SAME INDEX" << std::endl;
                    return (a.nested_BI == b.nested_BI);
                }
                return false;
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

        struct FirstDimensionMajorIterator
        {
            typename Array<T, F, Dims...>::BaseIterator ind;
            std::vector<T> data;
            std::vector<size_t> dims;
            FirstDimensionMajorIterator(const std::vector<T>& _data, const std::vector<size_t>& _dims, int e)
            : data(_data), dims(_dims){}

            FirstDimensionMajorIterator& operator++()
            {
                ind.FDinc();
                return *this;
            }

            FirstDimensionMajorIterator operator++(int )
            {
                FirstDimensionMajorIterator rt = *this;
                operator++();
                return rt;
            }

            T &operator*() const
            {
                return const_cast<T&>(data[0]);
            }
        };
        struct LastDimensionMajorIterator : public BaseIterator
        {   typename Array<T, F, Dims...>::BaseIterator ind;
            std::vector<T> data;
            std::vector<size_t> dims;
            LastDimensionMajorIterator(const std::vector<T>& _data, const std::vector<size_t>& _dims, int e)
            : data(_data), dims(_dims){}

            LastDimensionMajorIterator& operator++()
            {
                ind.LDinc();
                return *this;
            }

            LastDimensionMajorIterator operator++(int )
            {
                LastDimensionMajorIterator rt = *this;
                operator++();
                return rt;
            }
        };
        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  { F, Dims... }; 
            int total = product({F, Dims...});
            static_assert(product({F, Dims...}) != 0, "Zeroed Dimension");
            data = std::vector<T>(total);
            //printf("%d\n", total);
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
        template <typename U>
        Array(const Array<U, F, Dims...> & n)
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
        template <typename U>
        Array &operator=(const Array<U, F, Dims...> & n)
        {
            dims = n.dims;
            copy( n.data.begin(),  n.data.end(), back_inserter(data));
            return *this;
        }
        
        // T &operator[](int dim)
        // {
        //     return data[dim];
        // };//size_t i_1][size_t i_2]...[size_t i_D];

        // This is used to index into the array with range-checking.
        // If any given indices are out-of-range, then an OutOfRange
        // exception must be thrown. Note that this is a “conceptual”
        // operator only. Such an operator does not really exist. 
        // Instead, you must figure out how to provide this functionality. 
        // (bracket classes may be useful.)
        inline cs540::bracket<T, sizeof...(Dims)+1> operator[](size_t i) const
        {
			return cs540::bracket<T, sizeof...(Dims)+1>(dims, data, i);
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
        /*
        //   Returns a LastDimensionMajorIterator pointing to the first element.
        LastDimensionMajorIterator lmbegin()
        {
        	return LastDimensionMajorIterator(*this, data, dims, 0);
        }
        LastDimensionMajorIterator lmend()
        {
        	return LastDimensionMajorIterator(*this, data, dims, -1);
        }
        */
	};
	template <class T, size_t F>
	struct Array<T,F>
	{
		std::vector<T> data;
		std::vector<size_t> dims;
        struct BaseIterator
        {public:
            friend std::ostream &operator<<(std::ostream &os, const BaseIterator &ind) 
            {
                return os << ind.cur_ind;
            }
            size_t cur_ind;
            bool isend = false;
            BaseIterator():cur_ind(0){}
            BaseIterator(int a)
            {
                cur_ind = 0;
                if(a == -1)
                    isend = true;
            }
            bool FDinc()
            {
                if(isend)
                    return true;
                if(++cur_ind == F)
                {
                    return true;
                }
                return false;
            }
            void LDinc()
            {
                if(isend)
                    return; 
                cur_ind++;
            }
            friend bool operator==(const BaseIterator& a, const BaseIterator & b)
            {
                if(a.isend != b.isend)
                    return false;
                if(a.cur_ind == b.cur_ind)
                {
                    //std::cout << "SAME INDEX" << std::endl;
                    return true;
                }
                return false;
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

        struct FirstDimensionMajorIterator
        {
            typename Array<T, F>::BaseIterator ind;
            std::vector<T> data;
            std::vector<size_t> dims;
            FirstDimensionMajorIterator(const std::vector<T>& _data, const std::vector<size_t>& _dims, int e)
            : data(_data), dims(_dims){}

            FirstDimensionMajorIterator& operator++()
            {
                ind.FDinc();
                return *this;
            }

            FirstDimensionMajorIterator operator++(int )
            {
                FirstDimensionMajorIterator rt = *this;
                operator++();
                return rt;
            }
        };
        struct LastDimensionMajorIterator : public BaseIterator
        {
            typename Array<T, F>::BaseIterator ind;
            FirstDimensionMajorIterator& operator++()
            {
                ind.LDinc();
                return *this;
            }

            FirstDimensionMajorIterator operator++(int )
            {
                FirstDimensionMajorIterator rt = *this;
                operator++();
                return rt;
            }
        };
        // The default constructor must be defined, either explicitly or implicitly.
        Array() 
        {
            dims =  {F}; 
            int total = product({F});
            static_assert(product({F}) != 0, "Zeroed Dimension");
            data = std::vector<T>(total);
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
        template <typename U>
        Array(const Array<U, F> & n)
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
        template <typename U>
        Array &operator=(const Array<U, F> & n)
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
        T& operator[](size_t i) const
        {
            if(i > dims[0])
                throw cs540::OutOfRange("Out of Range");
			return const_cast<T&>(data[i]);//cs540::bracket<1>(dims, i);
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
        /*
        //   Returns a LastDimensionMajorIterator pointing to the first element.
        LastDimensionMajorIterator lmbegin()
        {
        	return LastDimensionMajorIterator(data, dims, 0);
        }
        LastDimensionMajorIterator lmend()
        {
        	return LastDimensionMajorIterator(data, dims, -1);
        }*/
	};
	
}//ends namespace
#endif