//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_ALGO_H
#define STL_ALGO_H


#include<string.h>

#include"../iterator"
#include"../type_traits"
#include"stl_algobase.h"
#include"stl_function.h"
#include"utility"

namespace stl
{


template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    while(first1 != last1 && first2 != last2)
    {
        if( *first1 < *first2 )
        {
            *result = *first1++;
        }
        else if( *first2 < *first1 )
        {
            *result = *first2++;
        }
        else //equals
        {
            *result = *first1++;
            ++first2;
        }

        ++result;
    }

    return stl::copy(first1, last1, stl::copy(first2, last2, result));
}


template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename StrictWeakCompare>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, StrictWeakCompare comp)
{
    while(first1 != last1 && first2 != last2)
    {
        if( comp(*first1, *first2) )
        {
            *result = *first1++;
        }
        else if( comp(*first2, *first1) )
        {
            *result = *first2++;
        }
        else //equals
        {
            *result = *first1++;
            ++first2;
        }

        ++result;
    }

    return stl::copy(first1, last1, stl::copy(first2, last2, result));
}



template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    while(first1 != last1 && first2 != last2)
    {
        if( *first1 < *first2 )
        {
            ++first1;
        }
        else if( *first2 < *first1 )
        {
            ++first2;
        }
        else //equals
        {
            *result++ = *first1++;
            ++first2;
        }
    }

    return result;
}


template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename StrictWeakCompare>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, StrictWeakCompare comp)
{
    while(first1 != last1 && first2 != last2)
    {
        if( comp(*first1, *first2) )
        {
            ++first1;
        }
        else if( comp(*first2, *first1) )
        {
            ++first2;
        }
        else //equals
        {
            *result++ = *first1++;
            ++first2;
        }
    }

    return result;
}



template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    while(first1 != last1 && first2 != last2)
    {
        if( *first1 < *first2 )
        {
            *result++ = *first1++;
        }
        else if( *first2 < *first1 )
        {
            ++first2;
        }
        else //equals
        {
            ++first1;
            ++first2;
        }
    }

    return stl::copy(first1, last1, result);
}


template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename StrictWeakCompare>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, StrictWeakCompare comp)
{
    while(first1 != last1 && first2 != last2)
    {
        if( comp(*first1, *first2) )
        {
            *result++ = *first1++;
        }
        else if( comp(*first2, *first1) )
        {
            ++first2;
        }
        else //equals
        {
            ++first1;
            ++first2;
        }
    }

    return stl::copy(first1, last1, result);
}


template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    while(first1 != last1 && first2 != last2)
    {
        if( *first1 < *first2 )
        {
            *result++ = *first1++;
        }
        else if( *first2 < *first1 )
        {
            *result++ = *first2++;
        }
        else //equals
        {
            ++first1;
            ++first2;
        }
    }

    return stl::copy(first1, last1, stl::copy(first2, last2, result));
}


template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename StrictWeakCompare>
OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, StrictWeakCompare comp)
{
    while(first1 != last1 && first2 != last2)
    {
        if( comp(*first1, *first2) )
        {
            *result++ = *first1++;
        }
        else if( comp(*first2, *first1) )
        {
            *result++ = *first2++;
        }
        else //equals
        {
            ++first1;
            ++first2;
        }
    }

    return stl::copy(first1, last1, stl::copy(first2, last2, result));
}



template<typename ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
{
    if( first == last )
        return first;

    ForwardIterator second = first;

    for(++second; second != last; ++first, ++second)
    {
        if( *first == *second )
            return first;
    }

    return last;
}


template<typename ForwardIterator, typename BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
{
    if( first == last )
        return first;

    ForwardIterator second = first;

    for(++second; second != last; ++first, ++second)
    {
        if( pred(*first, *second) )
            return first;
    }

    return last;
}


template<typename InputIterator, typename T>
typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T &val)
{
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(;first != last; ++first)
    {
        if(*first == val)
            ++n;
    }

    return n;
}


template<typename InputIterator, typename Predicate>
typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, Predicate pred)
{
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first)
    {
        if( pred(*first) )
            ++n;
    }

    return n;
}



template<typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T &val)
{
    for(; first != last; ++first)
    {
        if( *first == val)
            break;
    }

    return first;
}


template<typename InputIterator, typename Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
{
    for(; first != last; ++first)
    {
        if(pred(*first))
            break;
    }

    return first;
}



template<typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator1 __find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
                          BidirectionalIterator2 first2, BidirectionalIterator2 last2,
                          bidirectional_iterator_tag, bidirectional_iterator_tag)
{

    BidirectionalIterator2 not_find = last1;

    for(; last1 != first1 && last2-- != first2;)
    {
        while( last1 != first1 )
        {
            --last1;
            if( *last2 == *last1 )
                break;
        }

    }
}



template<typename ForwardIterator1, typename ForwardIterator2>
inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
    return __find_end(first1, last1, first2, last2, iterator_category(first1), iterator_category(first2));
}


template<typename InputIterator, typename ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2)
{
    for(; first1 != last1; ++first1)
    {

        for(ForwardIterator it = first2; it != last2; ++it)
        {
            if( *first1 == *it )
                return first1;
        }
    }

    return last1;
}



template<typename InputIterator, typename ForwardIterator, typename BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2, BinaryPredicate pred)
{
    for(; first1 != last1; ++first1)
    {

        for(ForwardIterator it = first2; it != last2; ++it)
        {
            if( pred(*first1, *it) )
                return first1;
        }
    }

    return last1;
}



template<typename InputIterator, typename UnaryFunction>
UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction func)
{
    for(; first != last; ++first)
        func(*first);

    return func;
}


template<typename ForwardIterator, typename Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen)
{
    while( first != last) *first++ = gen();
}


template<typename OutputIterator, typename Size, typename Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen)
{
    for(; n > 0; --n, ++first)
        *first = gen();

    return first;
}


template<typename InputIterator1, typename InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
    while( first1 != last1 && first2 != last2 )
    {
        if( *first1 < *first2 )
        {
            ++first1;
        }
        else if( *first2 < *first1 )
        {
            return false;
        }
        else
        {
            ++first1;
            ++first2;
        }
    }

    return first2 == last2;
}


template<typename InputIterator1, typename InputIterator2, typename Compare>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
{
    while( first1 != last1 && first2 != last2 )
    {
        if( comp(*first1, *first2) )
        {
            ++first1;
        }
        else if( comp(*first2, *first1) )
        {
            return false;
        }
        else
        {
            ++first1;
            ++first2;
        }
    }

    return first2 == last2;
}


template<typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
{
    ForwardIterator it = first;
    for(; first != last; ++first)
    {
        if( *it < *first )
            it = first;
    }

    return it;
}


template<typename ForwardIterator, typename Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp)
{
    ForwardIterator it = first;
    for(; first != last; ++first)
    {
        if( comp(*it, *first) )
            it = first;
    }

    return it;
}


template<typename ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
{
    ForwardIterator it = first;
    for(; first != last; ++first)
    {
        if( *first < *it )
            it = first;
    }

    return it;
}


template<typename ForwardIterator, typename Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp)
{
    ForwardIterator it = first;
    for(; first != last; ++first)
    {
        if( comp(*first, *it) )
            it = first;
    }

    return it;
}



template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    while(first1 != last1 && first2 != last2)
    {
        if( *first2 < *first1 )
            *result++ = *first2++;
        else
            *result++ = *first1++;
    }

    return stl::copy(first1, last1, stl::copy(first2, last2, result));
}



template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
{
    while(first1 != last1 && first2 != last2)
    {
        if( comp(*first2, *first1) )
            *result++ = *first2++;
        else
            *result++ = *first1++;
    }

    return stl::copy(first1, last1, stl::copy(first2, last2, result));
}


template<typename BidireationalIterator, typename UnaryPredicate>
BidireationalIterator partition(BidireationalIterator first, BidireationalIterator last, UnaryPredicate pred)
{
    while( first != last )
    {
        //first 指向第一个不符合pred的元素
        while( first != last && pred(*first) ) ++first;
        if( first == last )
            break;

        while( first != --last ) //last指向第一个符合pred的元素
        {
            if( pred(*last) )
                break;
        }

        if(first == last)
            break;

        stl::swap(*first, *last);
        ++first;
    }

    return first;
}



template<typename ForwardIterator, typename T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T &val)
{
    ForwardIterator it = first;
    for(; first != last; ++first)
    {
        if( !(*first == val) )
            *it++ = *first;
    }

    return it;
}

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
{
    ForwardIterator it = first;
    for(; first != last; ++first)
    {
        if(!pred(*first))
            *it++ = *first;
    }

    return it;
}


template<typename InputIterator, typename OutputIterator, typename T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T &val)
{
    for(; first != last; ++first)
    {
        if( !(*first == val) )
            *result++ = *first;
    }

    return result;
}



template<typename InputIterator, typename OutputIterator, typename UnaryPredicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred)
{
    for(; first != last; ++first)
    {
        if( !pred(*first) )
            *result++ = *first;
    }

    return result;
}


template<typename ForwardIterator, typename T>
void replace(ForwardIterator first, ForwardIterator last, const T &old_value, const T &new_value)
{
    for(; first != last; ++first)
    {
        if( *first == old_value )
            *first = new_value;
    }
}


template<typename ForwardIterator, typename UnaryPredicate, typename T>
void replace_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred, const T &new_value)
{
    for(; first != last; ++first)
    {
        if( pred(*first) )
            *first = new_value;
    }
}


template<typename InputIterator, typename OutputIterator, typename T>
OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T &old_vale, const T &new_value)
{
    for(; first != last; ++first, ++result)
    {
        if( *first == old_vale )
            *result = new_value;
        else
            *result = *first;
    }

    return result;
}


template<typename InputIterator, typename OutputIterator, typename UnaryPredicate, typename T>
OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred, const T &new_value)
{
    for(; first != last; ++first, ++result)
    {
        if( pred(*first) )
            *result = new_value;
        else
            *result = *first;
    }

    return result;
}



template<typename BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag)
{
    while(first != last && first != --last)
        stl::swap(*first++, *last);
}


template<typename RandomIterator>
void __reverse(RandomIterator first, RandomIterator last, random_access_iterator_tag)
{
    while( first < last ) stl::swap(*first++, *--last);
}


template<typename BidirectionalIterator>
inline void reverse(BidirectionalIterator first, BidirectionalIterator last)
{
    __reverse(first, last, stl::iterator_category(first));
}


template<typename BidirectionalIterator, typename OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result)
{
    while( first != last )
    {
        --last;
        *result++ = *last;
    }

    return result;
}


template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
    if(first1 == last1 || first2 == last2 )
        return first1;

    for(; first1 != last1; ++first1)
    {
        if( *first1 == *first2 )
        {
            ForwardIterator1 it1 = first1;
            ForwardIterator2 it2 = first2;

            for(++it1, ++it2;it1 != last1 && it2 != last2; ++it1, ++it2)
            {
                if(*it1 != *it2)
                    break;
            }

            if(it2 == last2)//find it
                break;
        }
    }

    return first1;
}



template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
{
    if(first1 == last1 || first2 == last2 )
        return first1;

    for(; first1 != last1; ++first1)
    {
        if( pred(*first1, *first2) )
        {
            ForwardIterator1 it1 = first1;
            ForwardIterator2 it2 = first2;

            for(++it1, ++it2;it1 != last1 && it2 != last2; ++it1, ++it2)
            {
                if(!pred(*it1, *it2) )
                    break;
            }

            if(it2 == last2)//find it
                break;
        }
    }

    return first1;
}



template<typename ForwardIterator, typename Integer, typename T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer n, const T &val)
{
    if( n <= 0 )
        return first;

    for(; first != last; ++first)
    {
        if( *first == val)
        {
            ForwardIterator it = first;
            Integer num = n;
            for(++it; it != last && --num > 0; ++it)
            {
                if( *it != val )
                    break;
            }

            if( num == 0)
                break;
        }
    }

    return first;
}



template<typename ForwardIterator, typename Integer, typename T, typename BinaryPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer n, const T &val, BinaryPredicate pred)
{
    if( n <= 0 )
        return first;

    for(; first != last; ++first)
    {
        if( pred(*first, val) )
        {
            ForwardIterator it = first;
            Integer num = n;
            for(++it; it != last && --num > 0; ++it)
            {
                if( !pred(*it, val) )
                    break;
            }

            if( num == 0)
                break;
        }
    }

    return first;
}


template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
{
    while(first1 != last1 ) stl::swap(*first1++, *first2++);

    return first2;
}


template<typename InputIterator, typename OutputIterator, typename UnaryFunction>
OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryFunction op)
{
    while(first != last) *result++ = op(*first++);

    return result;
}


template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryFunction>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, BinaryFunction op)
{
    while(first1 != last1) *result++ = op(*first1++, *first2++);

    return result;
}


template<typename ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last)
{
    if(first == last)
        return first;

    ForwardIterator it = first;
    while( ++it != last )
    {
        if( *it != *first )
        {
            *++first = *it;
        }
    }

    return ++first;
}


template<typename ForwardIterator, typename BinaryPredicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
{
    if(first == last)
        return first;

    ForwardIterator it = first;
    while( ++it != last )
    {
        if( !pred(*it, *first) )
        {
            *++first = *it;
        }
    }

    return ++first;
}



template<typename ForwardIterator, typename OutputIterator>
OutputIterator unique_copy(ForwardIterator first, ForwardIterator last, OutputIterator result)
{
    if( first == last )
        return result;

    *result++ = *first;
    ForwardIterator it = first;
    while( ++it != last)
    {
        if( *first != *it )
        {
            *result++ = *it;
            first = it;
        }
    }

    return result;
}



template<typename ForwardIterator, typename OutputIterator, typename BinaryPredicate>
OutputIterator unique_copy(ForwardIterator first, ForwardIterator last, OutputIterator result, BinaryPredicate pred)
{
    if( first == last )
        return result;

    *result++ = *first;
    ForwardIterator it = first;
    while( ++it != last)
    {
        if( !pred(*first, *it) )
        {
            *result++ = *it;
            first = it;
        }
    }

    return result;
}



template<typename ForwardIterator, typename T, typename StrictWeaklyCompare>
bool __binary_search_dispatch(ForwardIterator first, ForwardIterator last, const T &val, StrictWeaklyCompare comp, stl::forward_iterator_tag)
{
    while(first != last)
    {
        if(!comp(*first, val) && !(comp(val, *first)))
            break;

        ++first;
    }

    return first != last;
}



template<typename RandomAccessItreator, typename T, typename StrictWeaklyCompare>
bool __binary_search_dispatch(RandomAccessItreator first, RandomAccessItreator last, const T &val, StrictWeaklyCompare comp, stl::random_access_iterator_tag)
{
    while(first < last)
    {
        RandomAccessItreator mid = first + stl::distance(first, last)/2;

        if( !comp(val, *mid) && !comp(*mid, val) )
            return true;
        else if( comp(val, *mid) )
            last = mid;
        else
            first = mid+1;
    }

    return false;
}


template<typename ForwardIterator, typename T, typename StrictWeaklyCompare>
inline bool binary_search(ForwardIterator first, ForwardIterator last, const T &val, StrictWeaklyCompare comp)
{
    return __binary_search_dispatch(first, last, val, comp, stl::iterator_category(first));
}


template<typename ForwardIterator, typename T>
inline bool binary_search(ForwardIterator first, ForwardIterator last, const T &val)
{
    return stl::binary_search(first, last, val, stl::less<T>());
}


//__lower_bound_dispatch中何时将结束循环呢？当first等于last，还是first > last?
//首先有[first, last)、[first, mid]和[mid, last)，即first < last 并且 first <= mid < last
//因此有，first < mid+1 以及mid+1 <= last。所以当进行一次循环后，仍然有first <= last
//当first 等于last时 将结束循环。因为每次循环后都有first <= last，所以结束循环时first等于last

//__lower_bound_dispatch结束循环时，*first是否等于val，或者如果*first != val时，是否first的
//位置就是val要存放的位置？
//当val < *first，有val < *mid，由下面循环体可知，每次都是last在变化，first不会变。由上面的结论：
//循环结束时，first等于last。因此循环结束时first还是等于一开始的值。符合上述的说法
//当*(last-1) < val，有*mid < val，因此每次都是first在变化，last不会变。由上面的结论可知:
//循环结束时，first等于last。因此循环结束时last还是等于一开始的值，并且first等于last。符合上述的说法。
//当*first <= val <= *(last-1)时，如果comp(*mid, val),比如*mid < val,执行first = mid+1，此时
//仍然有*first <= val <= *(last-1)。如果!comp(*mid, val)，比如mid >= val, 指向last=mid,此时
//仍然有*first <= val,但不一定有val <= *(last-1)。假设有val <= *(last-1)，则回到一开始*first <= val <= *(last-1)。
//循环继续进行。假如val > *(last-1)，会有*(last-1) < val <= *last。在以后的循环中，mid都是小于last的
//换言之，comp(*mid, val)恒成立。因此每次都是first在变化。由前面的结论：退出循环时first等于last
//所以当退出循环时，对于first有 *(first-1) < val <= *first
template<typename RandomAccessItreator, typename T, typename StrictWeaklyCompare>
RandomAccessItreator __lower_bound_dispatch(RandomAccessItreator first, RandomAccessItreator last, const T &val, StrictWeaklyCompare comp, stl::random_access_iterator_tag)
{
    while(first < last)
    {
        RandomAccessItreator mid = first + stl::distance(first, last)/2;

        if( comp(*mid, val) )
            first = mid + 1;
        else
            last = mid;
    }

    return first;
}


template<typename ForwardIterator, typename T, typename StrictWeaklyCompare>
ForwardIterator __lower_bound_dispatch(ForwardIterator first, ForwardIterator last, const T &val, StrictWeaklyCompare comp, stl::forward_iterator_tag)
{
    while(first != last)
    {
        if( comp(*first, val) && !comp(val, *first) )
        {
            ++first;
            continue;
        }

        break;
    }

    return first;
}



template<typename ForwardIterator, typename T, typename StrictWeaklyCompare>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T &val, StrictWeaklyCompare comp)
{
    return __lower_bound_dispatch(first, last, val, comp, stl::iterator_category(first));
}


template<typename ForwardIterator, typename T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T &val)
{
    return stl::lower_bound(first, last, val, stl::less<T>());
}



template<typename RandomAccessItreator, typename T, typename StrictWeaklyCompare>
RandomAccessItreator __upper_bound_dispatch(RandomAccessItreator first, RandomAccessItreator last, const T &val, StrictWeaklyCompare comp, stl::random_access_iterator_tag)
{
    while(first < last)
    {
        RandomAccessItreator mid = first + stl::distance(first, last)/2;

        if( comp(val, *mid) )
            last = mid;
        else
            first = mid + 1;
    }

    return first;
}


template<typename ForwardIterator, typename T, typename StrictWeaklyCompare>
ForwardIterator __upper_bound_dispatch(ForwardIterator first, ForwardIterator last, const T &val, StrictWeaklyCompare comp, stl::forward_iterator_tag)
{
    while(first != last)
    {
        if( comp(val, *first) && !comp(*first, val) )//greater
            break;

        ++first;
    }

    return first;
}



template<typename ForwardIterator, typename T, typename StrictWeaklyCompare>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T &val, StrictWeaklyCompare comp)
{
    return __upper_bound_dispatch(first, last, val, comp, stl::iterator_category(first));
}


template<typename ForwardIterator, typename T>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T &val)
{
    return stl::upper_bound(first, last, val, stl::less<T>());
}




template<typename BidirectionalIterator, typename StrictWeaklyCompare>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, StrictWeaklyCompare comp)
{
    if( first == last || stl::next(first) == last)
        return false;


    BidirectionalIterator i = stl::prev(last);
    while(true)
    {
        BidirectionalIterator ii = i--;
        if( comp(*i, *ii) )
        {
            BidirectionalIterator j = stl::prev(last);
            while( !comp(*i, *j) ) --j;

            stl::swap(*i, *j);
            stl::reverse(ii, last);
            return true;
        }

        if(i == first )
        {
            stl::reverse(first, last);
            return false;
        }
    }
}


template<typename BidirectionalIterator>
inline bool next_permutation(BidirectionalIterator first, BidirectionalIterator last)
{
    typedef typename iterator_traits<BidirectionalIterator>::value_type ValueType;
    return stl::next_permutation(first, last, stl::less<ValueType>());
}



template<typename BidirectionalIterator, typename StrictWeaklyCompare>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last, StrictWeaklyCompare comp)
{
    if( first == last || stl::next(first)==last )
        return false;

    BidirectionalIterator i = stl::prev(last);

    while(true)
    {
        BidirectionalIterator ii = i--;

        if( comp(*ii, *i) )
        {
            BidirectionalIterator j = stl::prev(last);
            while( !comp(*j, *i) ) --j;

            stl::swap(*i, *j);
            stl::reverse(ii, last);
            return true;
        }

        if( i == first )
        {
            stl::reverse(first, last);
            return false;
        }
    }
}


template<typename BidirectionalIterator>
inline bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last)
{
    typedef typename iterator_traits<BidirectionalIterator>::value_type ValueType;
    return stl::prev_permutation(first, last, stl::less<ValueType>());
}


template<typename ForwardIterator, typename StrictWeaklyCompare>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last, StrictWeaklyCompare comp)
{
    if(first == last)
        return last;

    ForwardIterator next = first;

    for(++next; next != last; ++next)
    {
        if(comp(*next, *first))
            return next;

        //虽然++first也是可以，但++first可能没有直接赋值效率高
        //对于复杂的迭代器，自增有时需要做比较多的操作才能跳到下一位置
        //而赋值直接接受即可
        first = next;
    }

    return last;
}


template<typename ForwardIterator>
inline ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last)
{
    typedef typename iterator_traits<ForwardIterator>::value_type value_type;
    return stl::is_sorted_until(first, last, stl::less<value_type>());
}


template<typename ForwardIterator>
inline bool is_sorted(ForwardIterator first, ForwardIterator last)
{
    return stl::is_sorted_until(first, last) == last;
}


template<typename ForwardIterator, typename Compare>
inline bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp)
{
    return stl::is_sorted_until(first, last, comp) == last;
}


template<typename BidirectionalIterator, typename Compare>
void __sort_bidirectional_iterator(BidirectionalIterator begin, BidirectionalIterator end, Compare comp)
{
    if( begin == end )
        return ;

    BidirectionalIterator first = begin;
    BidirectionalIterator last = end;
    typename stl::iterator_traits<BidirectionalIterator>::value_type k = *first;

    while(first != last)
    {
        for(--last; first != last; --last)
        {
            if(comp(*last, k))
                break;
        }
        *first = *last;

        for(; first != last; ++first)
        {
            if(comp(k, *first))
                break;
        }
        *last = *first;
    }
    *first = k;

    if(first == begin)
    {
        __sort_bidirectional_iterator(++first, end, comp);
    }
    else if( ++last == end)
    {
        __sort_bidirectional_iterator(begin, first, comp);
    }
    else
    {
        __sort_bidirectional_iterator(begin, first, comp);
        __sort_bidirectional_iterator(++first, end, comp);
    }
}


template<typename BidirectionalIterator, typename Compare>
inline void __sort(BidirectionalIterator begin, BidirectionalIterator end, Compare comp, bidirectional_iterator_tag)
{
    __sort_bidirectional_iterator(begin, end, comp);
}


template<typename RandomIterator, typename Compare>
void __sort(RandomIterator begin, RandomIterator end, Compare comp, random_access_iterator_tag)
{

}


template<typename Iterator, typename Compare>
inline void sort(Iterator begin, Iterator end, Compare comp)
{
    __sort(begin, end, comp, iterator_category(begin));
}


template<typename Iterator>
inline void sort(Iterator begin, Iterator end)
{
    typedef typename iterator_traits<Iterator>::value_type value_type;
    stl::sort(begin, end, stl::less<value_type>());
}

}


#endif // STL_ALGO_H

