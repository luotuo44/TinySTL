//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_ITERATOR_BASE_H
#define STL_ITERATOR_BASE_H



#include<cstddef>

namespace stl
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


template<typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
struct iterator
{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};



template<typename T>
struct iterator_traits
{
    typedef typename T::value_type value_type;
    typedef typename T::pointer pointer;
    typedef typename T::reference reference;
    typedef typename T::difference_type difference_type;
    typedef typename T::iterator_category iterator_category;
};


template<typename T>
struct iterator_traits<T*>
{
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::ptrdiff_t difference_type;
    typedef random_access_iterator_tag iterator_category;
};


template<typename T>
struct iterator_traits<const T*>
{
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef std::ptrdiff_t difference_type;
    typedef random_access_iterator_tag iterator_category;
};


template<typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator &)
{
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}


template<typename Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator &)
{
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}


template<typename Iterator>
inline typename iterator_traits<Iterator>::difference_type* distance_type(const Iterator &)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}



template<typename InputIterator>
typename iterator_traits<InputIterator>::difference_type __distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
    iterator_traits<InputIterator>::difference_type n = 0;
    while( first != last)
    {
        ++first;
        ++n;
    }

    return n;
}



template<typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type __distance_dispatch(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
{
    return last - first;
}


template<typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
{
    return __distance_dispatch(first, last, iterator_category(first));
}




template<typename InputIterator, typename Distance>
void __advance_dispatch(InputIterator &it, Distance n, input_iterator_tag)
{
    while( n-- ) ++it;

    return it;
}


template<typename BidirectionalIterator, typename Distance>
void __advance_dispatch(BidirectionalIterator &it, Distance n, bidirectional_iterator_tag)
{
    if( n > 0)
        while(n--) ++it;
    else
        while(n++) --it;

}


template<typename RandomAccessIterator, typename Distance>
inline void __advance_dispatch(RandomAccessIterator &it, Distance n, random_access_iterator_tag)
{
    it += n;
}



template<typename InputItertor, typename Distance>
inline void advance(InputItertor &it, Distance n)
{
    __advance_dispatch(it, n, iterator_category(it));
}

}


#endif // STL_ITERATOR_BASE_H

