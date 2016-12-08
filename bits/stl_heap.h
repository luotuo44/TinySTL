//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_HEAP_H
#define STL_HEAP_H

#include"stl_iterator_base.h"
#include"stl_function.h"

namespace stl
{


template<typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type __iterator_num(RandomAccessIterator first, RandomAccessIterator last)
{
    //last指向一个有意义的节点
    return stl::distance(first, last+1);
}


template<typename RandomAccessIterator>
inline bool __hasLeftChild(RandomAccessIterator first, RandomAccessIterator it, RandomAccessIterator last)
{
    return 2*__iterator_num(first, it) <= stl::distance(first, last);
}


template<typename RandomAccessIterator>
inline bool __hasRightChild(RandomAccessIterator first, RandomAccessIterator it, RandomAccessIterator last)
{
    return 2*__iterator_num(first, it)+1 <= stl::distance(first, last);
}


template<typename RandomAccessIterator>
inline RandomAccessIterator __leftChild(RandomAccessIterator first, RandomAccessIterator it)
{
    return first + 2*__iterator_num(first, it)-1;
}


template<typename RandomAccessIterator>
inline RandomAccessIterator __rightChild(RandomAccessIterator first, RandomAccessIterator it)
{
    return first + 2*__iterator_num(first, it);
}


template<typename RandomAccessIterator>
inline RandomAccessIterator __fatherNode(RandomAccessIterator first, RandomAccessIterator it)
{
    if( first == it )
        return it;

    return first + __iterator_num(first, it)/2 - 1;
}

template<typename RandomAccessIterator, typename Compare>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    if( first == last || first+1 == last)
        return true;

    RandomAccessIterator it = first;
    while( __hasLeftChild(first, it, last) )
    {
        if( __hasLeftChild(first, it, last) && !comp(*__leftChild(first, it), *it) )
            return false;

        if( __hasRightChild(first, it, last) && !comp(*__rightChild(first, it), *it) )
            return false;

        ++it;
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

    RandomAccessIterator it = first + stl::distance(first, last)/2 - 1;
    for(; it >= first; --it)
    {
        RandomAccessIterator pos = it;
        typename iterator_traits<RandomAccessIterator>::value_type val = *pos;

        while( __hasLeftChild(first, pos, last) )
        {
            RandomAccessIterator min_child = __leftChild(first, pos);

            //min_child+1为右子节点。这里是找到左右孩子节点中最comp的那个
            if( min_child+1 < last && comp(*min_child, *(min_child+1) ) )
                ++min_child;

            if(comp(val, *min_child))
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

    while( replace_pos > first )
    {
        RandomAccessIterator father = __fatherNode(first, replace_pos);
        if(comp(val, *father))
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
        if( __hasRightChild(first, replace_pos, last) )//have two children
        {
            if( comp(*__leftChild(first, replace_pos), *__rightChild(first, replace_pos)))
                replace_child = __rightChild(first, replace_pos);
            else
                replace_child = __leftChild(first, replace_pos);

            if( comp(val, *replace_child) )
            {
                *replace_pos = *replace_child;
                replace_pos = replace_child;
            }
            else//two children all comp to val
            {
                break;
            }
        }
        else if( __hasLeftChild(first, replace_pos, last) && comp(val, *__leftChild(first, replace_pos)) )//only one child
        {
            RandomAccessIterator child = __leftChild(first, replace_pos);
            *replace_pos = *child;
            replace_pos = child;
        }
        else //no child or all children !comp val
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
inline void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
    stl::sort_heap(first, last, stl::less_equal<value_type>());
}


}

#endif // STL_HEAP_H

