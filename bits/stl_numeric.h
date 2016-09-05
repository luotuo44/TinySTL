//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_NUMERIC_H
#define STL_NUMERIC_H

#include"../iterator"

namespace stl
{


template<typename InputIterator, typename T>
T accumulate(InputIterator first, InputIterator last, T init)
{
    for(; first != last; ++first)
        init = init + *first;

    return init;
}


template<typename InputIterator, typename T, typename BinaryFunction>
T accumulate(InputIterator first, InputIterator last, T init, BinaryFunction op)
{
    for(; first != last; ++first)
        init = op(init, *first);

    return init;
}



template<typename InputIterator1, typename InputIterator2, typename T>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
{
    for(; first1 != last1; ++first1, ++first2)
        init = init + ( (*first1) * (*first2) );

    return init;
}


template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryFunction1, typename BinaryFunction2>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryFunction1 op1, BinaryFunction2 op2)
{
    for(; first1 != last1; ++first1, ++first2)
        init = op1(init, op2(*first1, *first2));

    return init;
}


template<typename InputIterator, typename OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result)
{
    if( first == last )
        return result;

    typename stl::iterator_traits<InputIterator>::value_type init = *first;
    *result = init;

    for(++first, ++result; first != last; ++first, ++result)
    {
        init = init + *first;
        *result = init;
    }

    return result;
}


template<typename InputIterator, typename OutputIterator, typename BinaryFunction>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryFunction op)
{
    if( first == last)
        return result;

    typename stl::iterator_traits<InputIterator>::value_type init = *first;
    *result = init;

    for(++first, ++result; first != last; ++first, ++result)
    {
        init = op(init, *first);
        *result = init;
    }

    return result;
}


template<typename InputIterator, typename OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result)
{
    if( first == last )
        return result;

    typename stl::iterator_traits<InputIterator>::value_type init = *first;
    *result = init;

    for(++first, ++result; first != last; ++first, ++result)
    {
        *result = *first - init;
        init = *first;
    }

    return result;
}


template<typename InputIterator, typename OutputIterator, typename BinaryFunction>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryFunction op)
{
    if( first == last )
        return result;

    typename stl::iterator_traits<InputIterator>::value_type init = *first;
    *result = init;

    for(++first, ++result; first != last; ++first, ++result)
    {
        *result = op(*first, init);
        init = *first;
    }

    return result;
}



template<typename ForWardIterator, typename T>
void iota(ForWardIterator first, ForWardIterator last, T value)
{
    while(first != last) *first++ = value++;
}


}

#endif // STL_NUMERIC_H

