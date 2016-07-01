#ifndef SharedPtr_GO
#define SharedPtr_GO

#include <pthread.h>

namespace cs540 {
  class Proxy {
    private:
      int refCount;
      pthread_mutex_t lock;

    public:
      Proxy() : refCount(1) { pthread_mutex_init(&lock, 0); }
      virtual ~Proxy() {}

      int decrement() {
        int r;
        pthread_mutex_lock(&lock);
        if(refCount > 0) {
          r = --refCount;
        } else {
          r = refCount;
        }
        pthread_mutex_unlock(&lock);
        return r;
      }

      int increment() {
        pthread_mutex_lock(&lock);
        int r = ++refCount;
        pthread_mutex_unlock(&lock);
        return r;
      }
  };

  template <typename U>
  class Proxy_t : public Proxy {
    private:
      U* object;

    public:
      Proxy_t(U* o) : object(o) {}
      virtual ~Proxy_t() { delete object; }
  };

  template <typename T>
  class SharedPtr {
    typedef void (SharedPtr<T>::*unspecified_bool_type)() const;
    void this_type_does_not_support_comparisons() const {}

    template <typename A> friend class SharedPtr;

    public:
      T* object;

    private:
      Proxy* proxy;

    public:
      SharedPtr() : object(0), proxy(0) {}

      ~SharedPtr() {
        if(proxy != 0 && proxy->decrement() == 0) delete proxy;
      }

      template <typename U>
      SharedPtr(U* o) : object(o), proxy(new Proxy_t<U>(o)) {}

      SharedPtr(const SharedPtr& s) : object(s.object), proxy(s.proxy) {
        proxy->increment();
      };

      template <typename U>
      SharedPtr(const SharedPtr<U>& s) : object(static_cast<T*>(s.object)), proxy(s.proxy) {
        proxy->increment();
      }

      // Ugly "hack" to dynamic_cast instead of static_cast
      template <typename U>
      SharedPtr(const SharedPtr<U>& s, int) : object(dynamic_cast<T*>(s.object)), proxy(s.proxy) {
        proxy->increment();
      }

      SharedPtr& operator=(const SharedPtr& s) {
        if(!(*this == s)) {
          if(proxy != 0 && proxy->decrement() == 0) { delete proxy; proxy = 0; object = 0; }
          object = s.object;
          proxy = s.proxy;
          proxy->increment();
        }
        return *this;
      }

      template <typename U>
      SharedPtr<T>& operator=(const SharedPtr<U>& s) {
        if(proxy != 0 && proxy->decrement() == 0) { delete proxy; proxy = 0; object = 0; }
        object = static_cast<T*>(const_cast<U*>(s.object));
        proxy = s.proxy;
        proxy->increment();
        return *this;
      }

      void reset() {
        if(proxy != 0 && proxy->decrement() == 0) { delete proxy; proxy = 0; object = 0; }
        object = 0;
        proxy = 0;
      }

      template <typename U>
      void reset(U *p)
        {
            if(proxy != 0 && proxy->decrement() == 0) 
            { delete proxy; proxy = 0; object = 0; }
            object = static_cast<T*>(const_cast<U*>(p));
            proxy = Proxy_t<U*>(p);
        }

      T& operator*() const { return *object; }
      T* operator->() const { return object; }

      T* get() const { return object; }

      operator unspecified_bool_type() const {
        return object != 0 ? &SharedPtr<T>::this_type_does_not_support_comparisons : 0;
      }
  };

  template <typename T1, typename T2>
  bool operator==(const SharedPtr<T1>& one, const SharedPtr<T2>& two) {
    return one.object == two.object;
  }

  template <typename T, typename U>
  SharedPtr<T> static_pointer_cast(const SharedPtr<U>& s) {
    return SharedPtr<T>(s);
  }

  template <typename T, typename U>
  SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U>& s) {
    return SharedPtr<T>(s, 1);
  }
}

#endif