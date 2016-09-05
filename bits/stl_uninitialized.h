//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_UNINITIALIZED_H
#define STL_UNINITIALIZED_H

#include"stl_construct.h"

#include"../iterator"
#include"../type_traits"
#include"../algorithm"

namespace stl
{

template<typename InputIterator, typename ForwardIterator>
ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, false_type)
{
    ForwardIterator cur = result;

    try
    {
        for(; first != last; ++first, ++cur)
        {
            construct(&(*cur), *first);
        }

        return cur;
    }
    catch(...)
    {
        ForwardIterator it = result;
        while( it != cur ) destroy(&(*it++));//<<More Effective C++>> 条款11，使用者需保证"异常不流出destructors之外"

        throw;//再次抛出该异常通知用户
    }
}


template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, true_type)
{
    return stl::copy(first, last, result);//pod类型构造时不会抛异常
}


template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
    typedef typename iterator_traits<InputIterator>::value_type val_type;
    return __uninitialized_copy(first, last, result, typename _type_traits<val_type>::is_pod_type());
}


//------------------------------------------------------------------------------------------------------


template<typename ForwardIterator, typename T>
void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &val, false_type)
{
    ForwardIterator begin = first;

    try
    {
        for(; first != last; ++first)
            stl::construct(&(*first), val);
    }
    catch(...)
    {
        while(begin != first) stl::destroy(&(*begin++));
        throw ;//再次抛出该异常通知用户
    }
}


template<typename ForwardIterator, typename T>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &val, true_type)
{
    stl::fill(first, last, val);//pod类型构造时不会抛异常
}


template<typename ForwardIterator, typename T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &val)
{
    typedef typename iterator_traits<ForwardIterator>::value_type val_type;
    __uninitialized_fill(first, last, val, typename _type_traits<val_type>::is_pod_type());
}



//------------------------------------------------------------------------------------------------------


template<typename ForwardIterator, typename Size, typename T>
inline void __uninitialized_fill_n(ForwardIterator first, Size n, const T &val, true_type)
{
    stl::fill_n(first, n, val);//pod类型构造时不会抛异常
}


template<typename ForwardIterator, typename Size, typename T>
inline void __uninitialized_fill_n(ForwardIterator first, Size n, const T &val, false_type)
{
    ForwardIterator begin = first;

    try
    {
        for(; n > 0; --n, ++first)
            stl::construct(&(*first), val);
    }
    catch(...)
    {
        while(begin != first) stl::destroy(&(*begin++));
        throw;//再次抛出该异常通知用户
    }
}


template<typename ForwardIterator, typename Size, typename T>
inline void uninitialized_fill_n(ForwardIterator first, Size n, const T &val)
{
    typedef typename iterator_traits<ForwardIterator>::value_type val_type;
    __uninitialized_fill_n(first, n, val, typename _type_traits<val_type>::is_pod_type());
}


}

#endif // STL_UNINITIALIZED_H

