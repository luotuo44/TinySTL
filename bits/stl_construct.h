//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_CONSTRUCT_H
#define STL_CONSTRUCT_H

#include<new>

#include"../type_traits"
#include"../iterator"

namespace stl
{

template<typename T1, typename T2>
inline void construct(T1 *p, const T2 &val)
{
    new(p) T1(val);
}


template<typename T>
inline void destroy( T *p)
{
    p->~T();
}


template<typename ForwardIterator>
void __destroy(ForwardIterator first, ForwardIterator last, true_type)
{
    (void)first; (void)last;
    //do nothing
}


template<typename ForwardIterator>
void __destroy(ForwardIterator first, ForwardIterator last, false_type)
{
    for(; first != last; ++first)
    {
        destroy(&(*first));
    }
}


template<typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
    typedef typename iterator_traits<ForwardIterator>::value_type val_type;

    __destroy(first, last, typename _type_traits<val_type>::has_trivial_destructor());
}


inline void destroy(char *, char *)
{
    //do nothing
}


inline void destroy(unsigned char *, unsigned char *)
{
    //do nothing
}




}


#endif // STL_CONSTRUCT_H

