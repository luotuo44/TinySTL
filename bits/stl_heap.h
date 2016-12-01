//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_HEAP_H
#define STL_HEAP_H

#include"stl_iterator_base.h"
#include"stl_function.h"

namespace stl
{


template<typename RandomAccessIterator, typename Compare>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    if( first == last || first+1 == last)
        return true;

    while( first != last )
    {
        if( 2*first < last && !comp(2*first, first))
            return false;

        if( 2*first+1 < last && !comp(2*first+1, first) )
            return false;

        ++first;
    }

    return true;
}


template<typename RandomAccessIterator>
inline bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
    return stl::is_heap(first, last, stl::less_equal<value_type>());
}



template<typename RandomAccessIterator, typename Compare>
void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    if( first == last || first+1 == last)
        return ;

    for(RandomAccessIterator it = (last-1)/2; it >= first; --it)
    {
        RandomAccessIterator pos = it;
        typename iterator_traits<RandomAccessIterator>::value_type val = *pos;

        while( 2*pos < last )
        {
            RandomAccessIterator min_child = 2*pos;
            if( min_child+1 < last && comp(*min_child, *(min_child+1)) )
            {
                ++min_child;
            }

            if( comp(val, *min_child) )
            {
                *pos = *min_child;
                pos = min_child;
            }
            else
            {
                break;
            }
        }

        if( pos != it)
            *pos = val;
    }
}


template<typename RandomAccessIterator>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
    stl::make_heap(first, last, stl::less_equal<value_type>());
}





template<typename RandomAccessIterator, typename Compare>
void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    if( first == last || first+1 == last )
        return ;

    typename iterator_traits<RandomAccessIterator>::value_type val = *(last-1);
    RandomAccessIterator replace_pos = last-1;

    while( replace_pos >= first )
    {
        RandomAccessIterator father = first + (replace_pos-first)/2;
        if( comp(val, father) )
            break;
        else
        {
            *replace_pos = *father;
            replace_pos = father;
        }
    }

    if( replace_pos != last-1 )
        *replace_pos = val;
}


template<typename RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
    stl::push_heap(first, last, stl::less_equal<value_type>());
}



template<typename RandomAccessIterator, typename Compare>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    if(first == last || first+1 == last)
        return ;

    typename iterator_traits<RandomAccessIterator>::value_type val = *(last-1);
    *(last-1) = *first;


    --last;//最后一个元素已被删除
    RandomAccessIterator replace_pos = first;
    RandomAccessIterator replace_child;

    while( replace_pos < last )
    {
        if( 2*replace_pos+1 < last )//have two children
        {
            if( comp(2*replace_pos, 2*replace_pos+1) )
                replace_child = 2*replace_pos + 1;
            else
                replace_child = 2*replace_pos;

            if( comp(val, replace_child) )
            {
                *replace_pos = *replace_child;
                replace_pos = replace_child;
            }
            else//two children all less than val
            {
                break;
            }
        }
        else if( 2*replace_pos < last && comp(val, 2*replace_pos))//only one child
        {
            *replace_pos = *(2*replace_pos);
            replace_pos = 2*replace_pos;
        }
        else//no child
        {
            break;
        }
    }

    *replace_pos = val;
}


template<typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
    stl::pop_heap(first, last, stl::less_equal<value_type>());
}




template<typename RandomAccessIterator, typename Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    while(first < last)
    {
        stl::pop_heap(first, last, comp);
        --last;
    }
}


template<typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
    stl::sort_heap(first, last, stl::less_equal<value_type>());
}


}

#endif // STL_HEAP_H

