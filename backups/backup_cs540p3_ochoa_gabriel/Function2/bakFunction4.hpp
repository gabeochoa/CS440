#include <utility>
#include <type_traits>
#include <exception>
#include <typeinfo>
#include <memory>

#define FUNC_NOEXCEPT noexcept
#define FUNC_TEMPLATE_NOEXCEPT(FUNCTOR, ALLOCATOR) noexcept(detail::is_inplace_allocated<FUNCTOR, ALLOCATOR>::value)
#define FUNC_CONSTEXPR constexpr
#define FUNC_MOVE(value) static_cast<typename std::remove_reference<decltype(value)>::type &&>(value)
#define FUNC_FORWARD(type, value) static_cast<type &&>(value)

namespace cs540
{
    struct BadFunctionCall : std::exception
    {
        const char * what() const FUNC_NOEXCEPT override
        {
            return "Bad Function call";
        }
    };

    template<typename>
    class Function;

    namespace detail
    {
        struct manager_storage_type;
        struct Function_manager;
        struct functor_padding
        {
        protected:
            size_t padding_first;
            size_t padding_second;
        };

        struct empty_struct
        {
        };

        template<typename Result, typename... Arguments>
        Result empty_call(const functor_padding &, Arguments...)
        {
            throw BadFunctionCall();
        }

        template<typename T, typename Allocator>
        struct is_inplace_allocated
        {
            static const bool value
                // so that it fits
                = sizeof(T) <= sizeof(functor_padding);
        };

        template<typename T>
        T to_functor(T && func)
        {
            return static_cast<T &&>(func);
        }
        template<typename Result, typename Class, typename... Arguments>
        auto to_functor(Result (Class::*func)(Arguments...)) -> decltype(std::mem_fn(func))
        {
            return std::mem_fn(func);
        }
        template<typename Result, typename Class, typename... Arguments>
        auto to_functor(Result (Class::*func)(Arguments...) const) -> decltype(std::mem_fn(func))
        {
            return std::mem_fn(func);
        }

        template<typename T>
        struct functor_type
        {
            typedef decltype(to_functor(std::declval<T>())) type;
        };

        template<typename T>
        bool is_null(const T &)
        {
            return false;
        }
        template<typename Result, typename... Arguments>
        bool is_null(Result (* const & Function_pointer)(Arguments...))
        {
            return Function_pointer == nullptr;
        }

        template<typename, typename>
        struct is_valid_Function_argument
        {
            static const bool value = false;
        };

        template<typename Result, typename... Arguments>
        struct is_valid_Function_argument<Function<Result (Arguments...)>, Result (Arguments...)>
        {
            static const bool value = false;
        };

        template<typename T, typename Result, typename... Arguments>
        struct is_valid_Function_argument<T, Result (Arguments...)>
        {
            template<typename U>
            static decltype(to_functor(std::declval<U>())(std::declval<Arguments>()...)) check(U *);
            template<typename>
            static empty_struct check(...);

            static const bool value = std::is_convertible<decltype(check<T>(nullptr)), Result>::value;
        };

        typedef const Function_manager * manager_type;

        struct manager_storage_type
        {
            template<typename Allocator>
            Allocator & get_allocator() FUNC_NOEXCEPT
            {
                return reinterpret_cast<Allocator &>(manager);
            }
            template<typename Allocator>
            const Allocator & get_allocator() const FUNC_NOEXCEPT
            {
                return reinterpret_cast<const Allocator &>(manager);
            }

            functor_padding functor;
            manager_type manager;
        };

        template<typename T, typename Allocator, typename Enable = void>
        struct Function_manager_inplace_specialization
        {
            template<typename Result, typename... Arguments>
            static Result call(const functor_padding & storage, Arguments... arguments)
            {
                // do not call get_functor_ref because I want this Function to be fast
                // in debug when nothing gets inlined
                return const_cast<T &>(reinterpret_cast<const T &>(storage))(static_cast<Arguments &&>(arguments)...);
            }

            static void store_functor(manager_storage_type & storage, T to_store)
            {
                new (&get_functor_ref(storage)) T(FUNC_FORWARD(T, to_store));
            }
            static void move_functor(manager_storage_type & lhs, manager_storage_type && rhs) FUNC_NOEXCEPT
            {
                new (&get_functor_ref(lhs)) T(FUNC_MOVE(get_functor_ref(rhs)));
            }
            static void destroy_functor(Allocator &, manager_storage_type & storage) FUNC_NOEXCEPT
            {
                get_functor_ref(storage).~T();
            }
            static T & get_functor_ref(const manager_storage_type & storage) FUNC_NOEXCEPT
            {
                return const_cast<T &>(reinterpret_cast<const T &>(storage.functor));
            }
        };
        template<typename T, typename Allocator>
        struct Function_manager_inplace_specialization<T, Allocator, typename std::enable_if<!is_inplace_allocated<T, Allocator>::value>::type>
        {
            template<typename Result, typename... Arguments>
            static Result call(const functor_padding & storage, Arguments... arguments)
            {
                // do not call get_functor_ptr_ref because I want this Function to be fast
                // in debug when nothing gets inlined
                return (*reinterpret_cast<const typename std::allocator_traits<Allocator>::pointer &>(storage))(FUNC_FORWARD(Arguments, arguments)...);
            }

            static void store_functor(manager_storage_type & self, T to_store)
            {
                Allocator & allocator = self.get_allocator<Allocator>();;
                static_assert(sizeof(typename std::allocator_traits<Allocator>::pointer) <= sizeof(self.functor), "The allocator's pointer type is too big");
                typename std::allocator_traits<Allocator>::pointer * ptr = new (&get_functor_ptr_ref(self)) typename std::allocator_traits<Allocator>::pointer(std::allocator_traits<Allocator>::allocate(allocator, 1));
                std::allocator_traits<Allocator>::construct(allocator, *ptr, FUNC_FORWARD(T, to_store));
            }
            static void move_functor(manager_storage_type & lhs, manager_storage_type && rhs) FUNC_NOEXCEPT
            {
                static_assert(std::is_nothrow_move_constructible<typename std::allocator_traits<Allocator>::pointer>::value, "we can't offer a noexcept swap if the pointer type is not nothrow move constructible");
                new (&get_functor_ptr_ref(lhs)) typename std::allocator_traits<Allocator>::pointer(FUNC_MOVE(get_functor_ptr_ref(rhs)));
                // this next assignment makes the destroy Function easier
                get_functor_ptr_ref(rhs) = nullptr;
            }
            static void destroy_functor(Allocator & allocator, manager_storage_type & storage) FUNC_NOEXCEPT
            {
                typename std::allocator_traits<Allocator>::pointer & pointer = get_functor_ptr_ref(storage);
                if (!pointer) return;
                std::allocator_traits<Allocator>::destroy(allocator, pointer);
                std::allocator_traits<Allocator>::deallocate(allocator, pointer, 1);
            }
            static T & get_functor_ref(const manager_storage_type & storage) FUNC_NOEXCEPT
            {
                return *get_functor_ptr_ref(storage);
            }
            static typename std::allocator_traits<Allocator>::pointer & get_functor_ptr_ref(manager_storage_type & storage) FUNC_NOEXCEPT
            {
                return reinterpret_cast<typename std::allocator_traits<Allocator>::pointer &>(storage.functor);
            }
            static const typename std::allocator_traits<Allocator>::pointer & get_functor_ptr_ref(const manager_storage_type & storage) FUNC_NOEXCEPT
            {
                return reinterpret_cast<const typename std::allocator_traits<Allocator>::pointer &>(storage.functor);
            }
        };

        template<typename T, typename Allocator>
        static const Function_manager & get_default_manager();

        template<typename T, typename Allocator>
        static void create_manager(manager_storage_type & storage, Allocator && allocator)
        {
            new (&storage.get_allocator<Allocator>()) Allocator(FUNC_MOVE(allocator));
            storage.manager = &get_default_manager<T, Allocator>();
        }

        // this struct acts as a vtable. it is an optimization to prevent
        // code-bloat from rtti. see the documentation of boost::Function
        struct Function_manager
        {
            template<typename T, typename Allocator>
            inline static FUNC_CONSTEXPR Function_manager create_default_manager()
            {
                return Function_manager
                {
                    &templated_call_move_and_destroy<T, Allocator>,
                    &templated_call_copy<T, Allocator>,
                    &templated_call_copy_functor_only<T, Allocator>,
                    &templated_call_destroy<T, Allocator>,
                };
            }

            void (* const call_move_and_destroy)(manager_storage_type & lhs, manager_storage_type && rhs);
            void (* const call_copy)(manager_storage_type & lhs, const manager_storage_type & rhs);
            void (* const call_copy_functor_only)(manager_storage_type & lhs, const manager_storage_type & rhs);
            void (* const call_destroy)(manager_storage_type & manager);

            template<typename T, typename Allocator>
            static void templated_call_move_and_destroy(manager_storage_type & lhs, manager_storage_type && rhs)
            {
                typedef Function_manager_inplace_specialization<T, Allocator> specialization;
                specialization::move_functor(lhs, FUNC_MOVE(rhs));
                specialization::destroy_functor(rhs.get_allocator<Allocator>(), rhs);
                create_manager<T, Allocator>(lhs, FUNC_MOVE(rhs.get_allocator<Allocator>()));
                rhs.get_allocator<Allocator>().~Allocator();
            }
            template<typename T, typename Allocator>
            static void templated_call_copy(manager_storage_type & lhs, const manager_storage_type & rhs)
            {
                typedef Function_manager_inplace_specialization<T, Allocator> specialization;
                create_manager<T, Allocator>(lhs, Allocator(rhs.get_allocator<Allocator>()));
                specialization::store_functor(lhs, specialization::get_functor_ref(rhs));
            }
            template<typename T, typename Allocator>
            static void templated_call_destroy(manager_storage_type & self)
            {
                typedef Function_manager_inplace_specialization<T, Allocator> specialization;
                specialization::destroy_functor(self.get_allocator<Allocator>(), self);
                self.get_allocator<Allocator>().~Allocator();
            }
            template<typename T, typename Allocator>
            static void templated_call_copy_functor_only(manager_storage_type & lhs, const manager_storage_type & rhs)
            {
                typedef Function_manager_inplace_specialization<T, Allocator> specialization;
                specialization::store_functor(lhs, specialization::get_functor_ref(rhs));
            }
        };
        template<typename T, typename Allocator>
        inline static const Function_manager & get_default_manager()
        {
            static FUNC_CONSTEXPR Function_manager default_manager = Function_manager::create_default_manager<T, Allocator>();
            return default_manager;
        }

        template<typename Result, typename...>
        struct typedeffer
        {
            typedef Result result_type;
        };
        template<typename Result, typename Argument>
        struct typedeffer<Result, Argument>
        {
            typedef Result result_type;
            typedef Argument argument_type;
        };
        template<typename Result, typename First_Argument, typename Second_Argument>
        struct typedeffer<Result, First_Argument, Second_Argument>
        {
            typedef Result result_type;
            typedef First_Argument first_argument_type;
            typedef Second_Argument second_argument_type;
        };
    }

    template<typename Result, typename... Arguments>
    class Function<Result (Arguments...)>
        : public detail::typedeffer<Result, Arguments...>
    {
    public:
        Function() FUNC_NOEXCEPT
        {
            initialize_empty();
        }
        Function(const Function & other)
            : call(other.call)
        {
            other.manager_storage.manager->call_copy(manager_storage, other.manager_storage);
        }
        template<typename T>
        Function(T functor,
                typename std::enable_if<detail::is_valid_Function_argument<T, Result (Arguments...)>::value, 
                detail::empty_struct>::type = detail::empty_struct()
        )
                FUNC_TEMPLATE_NOEXCEPT(T, std::allocator<typename detail::functor_type<T>::type>)
        {
            if (detail::is_null(functor))
            {
                initialize_empty();
            }
            else
            {
                typedef typename detail::functor_type<T>::type functor_type;
                initialize(detail::to_functor(FUNC_FORWARD(T, functor)), std::allocator<functor_type>());
            }
        }

        Function & operator=(Function other)
        {
            swap(other);
            return *this;
        }
        ~Function()
        {
            manager_storage.manager->call_destroy(manager_storage);
        }

        Result operator()(Arguments... arguments) const
        {
            return call(manager_storage.functor, FUNC_FORWARD(Arguments, arguments)...);
        }

        template<typename T, typename Allocator>
        void assign(T && functor, const Allocator & allocator) FUNC_TEMPLATE_NOEXCEPT(T, Allocator)
        {
            Function(std::allocator_arg, allocator, functor).swap(*this);
        }
        
        void swap(Function & other) FUNC_NOEXCEPT
        {
            detail::manager_storage_type temp_storage;
            other.manager_storage.manager->call_move_and_destroy(temp_storage, FUNC_MOVE(other.manager_storage));
            manager_storage.manager->call_move_and_destroy(other.manager_storage, FUNC_MOVE(manager_storage));
            temp_storage.manager->call_move_and_destroy(manager_storage, FUNC_MOVE(temp_storage));

            std::swap(call, other.call);
        }

        operator bool() const FUNC_NOEXCEPT
        {
            return call != &detail::empty_call<Result, Arguments...>;
        }

    private:
        detail::manager_storage_type manager_storage;
        Result (*call)(const detail::functor_padding &, Arguments...);

        template<typename T, typename Allocator>
        void initialize(T functor, Allocator && allocator)
        {
            call = &detail::Function_manager_inplace_specialization<T, Allocator>::template call<Result, Arguments...>;
            detail::create_manager<T, Allocator>(manager_storage, FUNC_FORWARD(Allocator, allocator));
            detail::Function_manager_inplace_specialization<T, Allocator>::store_functor(manager_storage, FUNC_FORWARD(T, functor));
        }

        typedef Result(*Empty_Function_Type)(Arguments...);
        void initialize_empty() FUNC_NOEXCEPT
        {
            typedef std::allocator<Empty_Function_Type> Allocator;
            static_assert(detail::is_inplace_allocated<Empty_Function_Type, Allocator>::value, "The empty Function should benefit from small functor optimization");

            detail::create_manager<Empty_Function_Type, Allocator>(manager_storage, Allocator());
            detail::Function_manager_inplace_specialization<Empty_Function_Type, Allocator>::store_functor(manager_storage, nullptr);
            call = &detail::empty_call<Result, Arguments...>;
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