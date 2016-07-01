#ifndef FUNCTION_GO
#define FUNCTION_GO

#include <exception>
#include <memory>
#include <stdio.h>
#include <iostream>
#include <stdexcept>

namespace cs540_backup
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
            Callable(Func a)
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
            fn = new Callable<ResultType(ArgumentTypes...)>(a);
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

namespace cs540
{
    struct BadFunctionCall : std::exception
    {
        const char * what() const noexcept override
        {
            return "Bad Function call";
        }
    };

    template<typename>
    class Function;

    namespace subclass
    {
        struct s_type;
        struct Func_Controller;
        struct pad
        {
            protected:
                size_t padding_first;
                size_t padding_second;
        };

        struct empty_struct
        {
        };

        template<typename Result, typename... Arguments>
        Result empty_call(const pad &, Arguments...)
        {
            throw BadFunctionCall();
        }

        typedef const Func_Controller * control;

        struct s_type
        {
            pad functor;
            control controller;
        };

        template<typename T>
        struct spec
        {
            template<typename Result, typename... Arguments>
            static Result call(const pad & storage, Arguments... arguments)
            {
                // do not call get_functor_ref because I want this Function to be fast
                // in debug when nothing gets inlined
                return const_cast<T &>(reinterpret_cast<const T &>(storage))(static_cast<Arguments &&>(arguments)...);
            }

            static void store_functor(s_type & storage, T to_store)
            {
                new (&get_functor_ref(storage)) T(static_cast<T &&>(to_store));
            }
            static void move_functor(s_type & lhs, s_type && rhs) 
            {
                new (&get_functor_ref(lhs)) T( static_cast<T&>(get_functor_ref(rhs)));
            }
            static void destroy_functor(s_type & storage) 
            {
                get_functor_ref(storage).~T();
            }
            static T & get_functor_ref(const s_type & storage) 
            {
                return const_cast<T &>(reinterpret_cast<const T &>(storage.functor));
            }
        };

        template<typename T>
        static const Func_Controller & get_default_controller();

        template<typename T>
        static void create_controller(s_type & storage)
        {
            storage.controller = &get_default_controller<T>();
        }

        // this struct acts as a vtable. it is an optimization to prevent
        // code-bloat from rtti. see the documentation of boost::Function
        
        struct Func_Controller
        {
            template<typename T>
            inline static constexpr Func_Controller create_default_controller()
            {
                return Func_Controller
                {
                    &templated_call_move_and_destroy<T>,
                    &templated_call_copy<T>,
                    &templated_call_copy_functor_only<T>,
                    &templated_call_destroy<T>,
                };
            }

            void (* const call_move_and_destroy)(s_type & lhs, s_type && rhs);
            void (* const call_copy)(s_type & lhs, const s_type & rhs);
            void (* const call_copy_functor_only)(s_type & lhs, const s_type & rhs);
            void (* const call_destroy)(s_type & controller);

            template<typename T>
            static void templated_call_move_and_destroy(s_type & lhs, s_type && rhs)
            {
                spec<T>::move_functor(lhs,  static_cast<subclass::s_type>(rhs));
                spec<T>::destroy_functor(rhs);
                create_controller<T>(lhs);
            }
            template<typename T>
            static void templated_call_copy(s_type & lhs, const s_type & rhs)
            {
                create_controller<T>(lhs);
                spec<T>::store_functor(lhs, spec<T>::get_functor_ref(rhs));
            }
            template<typename T>
            static void templated_call_destroy(s_type & self)
            {
                spec<T>::destroy_functor(self);
            }
            template<typename T>
            static void templated_call_copy_functor_only(s_type & lhs, const s_type & rhs)
            {
                spec<T>::store_functor(lhs, spec<T>::get_functor_ref(rhs));
            }
        };
        
        template<typename T>
        inline static const Func_Controller & get_default_controller()
        {
            static constexpr Func_Controller default_controller = Func_Controller::create_default_controller<T>();
            return default_controller;
        }
    }

    template<typename Result, typename... Arguments>
    class Function<Result (Arguments...)>
    {public:
    
        subclass::s_type s_val;
        Result (*call)(const subclass::pad &, Arguments...);
        typedef Result(*Empty_Function_Type)(Arguments...);
        
        Function() 
        {
            subclass::create_controller<Empty_Function_Type>(s_val);
            subclass::spec<Empty_Function_Type>::store_functor(s_val, nullptr);
            call = &subclass::empty_call<Result, Arguments...>;
        }
        Function(const Function & other)
            : call(other.call)
        {
            other.s_val.controller->call_copy(s_val, other.s_val);
        }
        template<typename T>
        Function(T functor)
        {
            subclass::create_controller<T>(s_val);
            subclass::spec<T>::store_functor(s_val, static_cast<T &&>(functor));
            call = &subclass::spec<T>::template call<Result, Arguments...>;
        }

        Function & operator=(Function other)
        {
            swap(other);
            return *this;
        }
        ~Function()
        {
            s_val.controller->call_destroy(s_val);
        }

        Result operator()(Arguments... arguments) const
        {
            return call(s_val.functor, static_cast<Arguments &&>(arguments)...);
        }

        template<typename T>
        void assign(T && functor)
        {
            Function(functor).swap(*this);
        }
        
        void swap(Function & other)
        {
            subclass::s_type temp_storage;
            other.s_val.controller->call_move_and_destroy(temp_storage, static_cast<subclass::s_type>(other.s_val));
            s_val.controller->call_move_and_destroy(other.s_val, static_cast<subclass::s_type>(s_val));
            temp_storage.controller->call_move_and_destroy(s_val, static_cast<subclass::s_type>(temp_storage));

            std::swap(call, other.call);
        }


        operator bool() const
        {
            return call != &subclass::empty_call<Result, Arguments...>;
        }
    };

    template<typename T>
    bool operator==(std::nullptr_t, const Function<T> & rhs)
    {
        return !rhs;
    }
    template<typename T>
    bool operator==(const Function<T> & lhs, std::nullptr_t)
    {
        return !lhs;
    }
    template<typename T>
    bool operator!=(std::nullptr_t, const Function<T> & rhs)
    {
        return rhs;
    }
    template<typename T>
    bool operator!=(const Function<T> & lhs, std::nullptr_t)
    {
        return lhs;
    }
    template<typename T>
    void swap(Function<T> & lhs, Function<T> & rhs)
    {
        lhs.swap(rhs);
    }
} // end namespace cs540

#endif
//FUNCTION_GO
