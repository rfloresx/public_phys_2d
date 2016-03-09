/*
Smart Pointer from oxygine.
*/

#ifndef INSTRUSIVE_PTR_H
#define INSTRUSIVE_PTR_H

namespace SFMLGame
{
    template <class T>
    class intrusive_ptr
    {
        T* _ptr;
    public:
        typedef T element_type;

        intrusive_ptr(): _ptr(0) {}
        intrusive_ptr(const intrusive_ptr& s): _ptr(s._ptr)
        {
            if (s._ptr)
                intrusive_ptr_add_ref(s._ptr);
        }

        template<class U>
        intrusive_ptr(intrusive_ptr<U> const& rhs)
            : _ptr(rhs.get())
        {
            if (_ptr != 0) intrusive_ptr_add_ref(_ptr);
        }

        T* get() const
        {
            return _ptr;
        }

        T& operator*() const
        {
            return *_ptr;
        }

        T* operator->() const
        {
            return _ptr;
        }

        intrusive_ptr& operator = (const intrusive_ptr& s)
        {
            intrusive_ptr(s).swap(*this);
            return *this;
        }

        intrusive_ptr& operator = (T* ptr)
        {
            intrusive_ptr(ptr).swap(*this);
            return *this;
        }

        intrusive_ptr(T* p): _ptr(p)
        {
            if (p)
                intrusive_ptr_add_ref(p);
        }

        bool operator!() const
        {
            return _ptr == 0;
        }

        void swap(intrusive_ptr& s)
        {
            T* p = s._ptr;
            s._ptr = _ptr;
            _ptr = p;
        }
        operator bool ()const
        {
            return _ptr != 0;
        }

        ~intrusive_ptr()
        {
            if (_ptr)
                intrusive_ptr_release(_ptr);
        }
    };

    template<class T, class U> inline bool operator==(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b)
    {
        return a.get() == b.get();
    }

    template<class T, class U> inline bool operator!=(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b)
    {
        return a.get() != b.get();
    }

    template<class T> inline bool operator==(intrusive_ptr<T> const& a, T* b)
    {
        return a.get() == b;
    }

    template<class T> inline bool operator!=(intrusive_ptr<T> const& a, T* b)
    {
        return a.get() != b;
    }

    template<class T> inline bool operator==(T* a, intrusive_ptr<T> const& b)
    {
        return a == b.get();
    }

    template<class T> inline bool operator!=(T* a, intrusive_ptr<T> const& b)
    {
        return a != b.get();
    }

    template<class T> T* get_pointer(intrusive_ptr<T> const& p)
    {
        return p.get();
    }

    template<class T, class U> intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const& p)
    {
        return static_cast<T*>(p.get());
    }

    template<class T, class U> intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const& p)
    {
        return const_cast<T*>(p.get());
    }

    template<class T, class U> intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const& p)
    {
        return dynamic_cast<T*>(p.get());
    }

		/** RefCounter **/
    class ref_counter
    {
    public:
        int _ref_counter;

        ref_counter(): _ref_counter(0) {}
        virtual ~ref_counter() {}

        void addRef()
        {
            ++_ref_counter;
        }

        void releaseRef()
        {
            if (0 == --_ref_counter)
                delete this;
        }

    private:
        ref_counter(const ref_counter&);
        const ref_counter& operator=(const ref_counter&);

    };

    template <class T>
    class RefHolder : public T
    {
    public:
        RefHolder() {this->_ref_counter = -1;}
        void addRef()
        {}

        void releaseRef()
        {}
    };


    inline void intrusive_ptr_add_ref(ref_counter* p)
    {
        p->addRef();
    }

    inline void intrusive_ptr_release(ref_counter* p)
    {
        p->releaseRef();
    }

	#define SMART_POINTER(class_name, counter_class, spname) class counter_class : public ref_counter, public class_name {}; \
	typedef intrusive_ptr<counter_class> spname;

	#define DECLARE_SMART(class_name, spname) class class_name;\
    typedef intrusive_ptr<class_name> spname;

	#define DECLARENS_SMART(name_space, class_name, spname) namespace name_space \
    {\
        class class_name;\
        typedef intrusive_ptr<class_name> spname;\
    }
}

#endif