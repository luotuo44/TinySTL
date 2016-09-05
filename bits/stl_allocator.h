//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_ALLOCATOR_H
#define STL_ALLOCATOR_H

#include<malloc.h>

#include<cstddef>

#include"pthread_alloc.h"
#include"stl_construct.h"


namespace stl
{


//实现std::allocator模板类的接口。具体的空间分配由pthread_alloc.h文件提供
template<typename T>
class allocator
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    template<typename U>
    struct rebind
    {
        typedef allocator<U> other;
    };

public:
    allocator() {}
    allocator(const allocator &) {}

    void printAllocateDetail();//打印各个freelist桶的分配详情
    pointer allocate(size_type n, const_pointer = 0);
    void deallocate(pointer p, size_type n);
    size_type max_size()const;
    void construct(pointer p, const_reference val);
    void destroy(pointer p);
    pointer address(reference val);
    const_pointer address(const_reference val);
};


template<typename T>
typename allocator<T>::pointer allocator<T>::allocate(size_type n, const_pointer)
{
    void *p = NULL;
    size_t total_size = n * sizeof(T);

    if(total_size > 128)
        p = ::malloc(total_size);
    else
    {
        p = PthreadAlloc::allocate(PthreadAlloc::roundUp(total_size));
    }

    return reinterpret_cast<pointer>(p);
}


template<typename T>
void allocator<T>::deallocate(pointer p, size_type n)
{
    size_t total_size = n * sizeof(T);
    if(total_size > 128)
        ::free(p);
    else
        PthreadAlloc::deallocate(p, PthreadAlloc::roundUp(total_size) );
}


template<typename T>
inline typename allocator<T>::size_type allocator<T>::max_size()const
{
    return size_t(-1)/sizeof(T);
}



template<typename T>
inline void allocator<T>::construct(pointer p, const_reference val)
{
    stl::construct(p, val);
}


template<typename T>
inline void allocator<T>::destroy(pointer p)
{
    stl::destroy(p);
}

template<typename T>
inline typename allocator<T>::pointer allocator<T>::address(reference val)
{
    return static_cast<reference>(&val);
}


template<typename T>
inline typename allocator<T>::const_pointer allocator<T>::address(const_reference val)
{
    return static_cast<const_reference>(&val);
}

}

#endif // STL_ALLOCATOR_H

