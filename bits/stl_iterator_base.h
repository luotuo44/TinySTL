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


}


#endif // STL_ITERATOR_BASE_H

