#ifndef SharedPtr_GO
#define SharedPtr_GO

#include <stdio.h>
#include <iostream>
#include <exception>
#include <stdexcept>

namespace cs540
{

    class BadFunctionCall : public std::runtime_error
    {
        public:
            BadFunctionCall(const std::string& message) 
                : std::runtime_error(message) { };
            virtual const char* what() const throw()
            {
                return "Bad Function Call";
            }
    };
    /*
    class Base
    {
        public:
            virtual ~Base(){}
            virtual ResultType operator()(ArgumentTypes...) const = 0;
    };
    */
    template <typename T>
    class Callable;
    
    template <typename ResultType, typename ... ArgumentTypes> 
    class Callable<ResultType(ArgumentTypes...)> 
    {
        typedef ResultType (*Func)(ArgumentTypes ...);
        Func* func;
        public:
            Callable()
            {
                func = nullptr;
            }
            Callable(ResultType(ArgumentTypes...) a)
            {
                func = a;
            }
            virtual ~Callable()
            {
                delete func;
            }
            virtual ResultType operator()(ArgumentTypes... args) const
            {
                if(func == nullptr)
                    throw BadFunctionCall("Bad Function Call");
                return ((*func)(std::forward<ArgumentTypes>(args)...));
            }
    };
    template <typename T>
    class Function;  
 
    template <typename ResultType, typename ... ArgumentTypes> 
    class Function<ResultType(ArgumentTypes...)>
    {
        public:
        Callable<ResultType(ArgumentTypes...)>* fn;
        //Constructs a function wrapper that does not yet reference a target function.
        Function()
        {
            fn = nullptr;
        }

        //Constructs a function wrapper with a function of FunctionType as its target.
        template <typename FunctionType> Function(FunctionType a)
        {
            fn = new Callable<ResultType(ArgumentTypes...)>( ResultType (*a)(ArgumentTypes...));
        }
        
        //Copy construct from an existing cs540::Function
        Function(const Function & ne)
        {
            delete fn;
            fn = ne.fn;
        }
        
        template<typename T>
        void swap(Function<T> & lhs, Function<T> & rhs)
        {
            lhs.swap(rhs);
        }

        //Copy assignment.
        //Must handle self assignment.
        //Must be able to freely assign between cs540::Function objects that contain a free function, 
        //lambda, or functor given that they have the same type signature.
        Function &operator=(const Function & ne)
        {
            /*
            if(this == &ne)
            {
                return *this;
            }
            delete fn;
            fn = ne.fn;
            return *this;
            */
            swap(ne);
            return *this;
        }
        
        //Properly destroy the object and clear any memory as necessary.
        ~Function()
        {
            if(fn != nullptr)
                delete fn;
        }

        //Call the wrapped function target with the given arguments and return its result.
        //Throw cs540::BadFunctionCall if a callable function is not stored.
        ResultType operator()(ArgumentTypes... args)
        {
            if(fn == nullptr)
                throw BadFunctionCall("Function not callable");
            return ((*fn)(std::forward<ArgumentTypes>(args)...));
        }

        //Return true if the cs540::Function references a callable function and false otherwise.
        //Return true if the cs540::Function references a callable function and false otherwise.
        explicit operator bool() const
        {
            return fn!=nullptr;
        }
        
        typedef Result(*Empty_Function_Type)(Arguments...);
        void initialize_empty() FUNC_NOEXCEPT
        {
            detail::create_manager<Empty_Function_Type, Allocator>(manager_storage, Allocator());
            detail::function_manager_inplace_specialization<Empty_Function_Type, Allocator>::store_functor(manager_storage, nullptr);
            fn = nullptr;
        }

    };
    
   

    template <typename ResultType, typename... ArgumentTypes>
    bool operator==(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t)
    {
        return false;
    } //

    template <typename ResultType, typename... ArgumentTypes>
    bool operator==(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> & f)
    {
        return false;
    } //Returns !f.

    template <typename ResultType, typename... ArgumentTypes>
    bool operator!=(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t)
    {
        return false;
    } //

    template <typename ResultType, typename... ArgumentTypes>
    bool operator!=(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> & f)
    {
        return false;
    } //Returns bool(f).

}




#endif