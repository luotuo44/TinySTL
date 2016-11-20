//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_ALGOBASE_H
#define STL_ALGOBASE_H


#include"../iterator"
#include"../utility"
#include"../type_traits"

#include<string.h>

namespace stl
{


template<typename InputIterator1, typename InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    for(; first1 != last1; ++first1, ++first2)
    {
        if( !(*first1 == *first2) )
            return false;
    }

    return true;
}


template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
    for(; first1 != last1; ++first1, ++first2)
    {
        if( !pred(*first1, *first2) )
            return false;
    }

    return true;
}



template<typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T &val)
{
    while( first != last) *first++ = val;
}


template<typename OutputIterator, typename Size, typename T>
OutputIterator fill_n(OutputIterator first, Size n, const T& val)
{
    for( ; n > 0; --n, ++first)
    {
        *first = val;
    }

    return first;
}


template<typename ForwardIterator1, typename ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
{
    typename iterator_traits<ForwardIterator1>::value_type tmp = *a;
    *a = *b;
    *b = tmp;
}



template<typename T>
inline const T& min(const T &a, const T &b)
{
    return a < b ? a : b;
}


template<typename T, typename Compare>
inline const T& min(const T &a, const T &b, Compare comp)
{
    return comp(a, b) ? a : b;
}


template<typename T>
inline const T& max(const T &a, const T &b)
{
    return a > b ? a : b;
}


template<typename T, typename Compare>
inline const T& max(const T &a, const T &b, Compare comp)
{
    return comp(a, b) ? a : b;
}


template<typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
    for(; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
        if( *first1 < *first2 )
            return true;
        else if( *first2 < *first1 )
            return false;
    }

    if( first1 == last1 && first2 != last2 )
        return true;

    return false;
}


//这里的inline是必需的，不然当本文件被多个源文件包含时编译器会报重复定义
inline bool lexicographical_compare(const unsigned char *first1, const unsigned char *last1, const unsigned char *first2, const unsigned char *last2)
{
    size_t len1 = last1 - first1;
    size_t len2 = last2 - first2;
    int ret = ::memcmp(first1, first2, min(len1, len2));

    return ret != 0 ? ret == -1 : len1 < len2;
}


inline bool lexicographical_compare(const char *first1, const char *last1, const char *first2, const char *last2)
{
    size_t len1 = last1 - first1;
    size_t len2 = last2 - first2;
    int ret = ::memcmp(first1, first2, min(len1, len2));

    return ret != 0 ? ret == -1 : len1 < len2;
}


template<typename InputIterator1, typename InputIterator2, typename Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
{
    for(; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
        if( comp(*first1, *first2) )
            return true;
        else if( comp(*first2, *first1) )
            return false;
    }

    if( first1 == last1 && first2 != last2 )
        return true;

    return false;
}



template<typename InputIterator1, typename InputIterator2>
stl::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    for(; first1 != last1; ++first1, ++first2)
    {
        if( !(*first1 == *first2) )
            break;
    }

    return stl::make_pair(first1, first2);
}



template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
stl::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
    for(; first1 != last1; ++first1, ++first2)
    {
        if( !pred(*first1, *first2) )
            break;
    }

    return stl::make_pair(first1, first2);
}


//======================================copy=================================


template<typename InputIterator, typename OutputIterator, typename Distance>
OutputIterator __copy_aux(InputIterator first, InputIterator last, OutputIterator result, Distance n)
{
    for(; n > 0; --n)
    {
        *result++ = *first++;
    }

    (void)last;
    return result;
}


template<typename T>
inline T* __copy_t(const T *first, const T *last, T *result, false_type)
{
    return stl::__copy_aux(first, last, result, last-first);
}


template<typename T>
inline T* __copy_t(const T *first, const T *last, T *result, true_type)
{
    memmove(result, first, sizeof(T) *(last-first));
    return result + (last - first);
}


template<typename RandomAccessIterator, typename OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag)
{
    return stl::__copy_aux(first, last, result, last-first);
}


template<typename InputIterator, typename OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
{
    while(first != last) *result++ = *first++;

    return result;
}



template<typename InputIterator, typename OutputIterator>
struct __copy_dispatch
{
    OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result)
    {
        return stl::__copy(first, last, result, stl::iterator_category(first));
    }
};


template<typename T>
struct __copy_dispatch<T*, T*>
{
    T* operator()(T *first, T *last, T *result)
    {
        return stl::__copy_t(first, last, result, typename _type_traits<T>::has_trivial_assignment_operator());
    }
};


template<typename T>
struct __copy_dispatch<const T*, T*>
{
    T* operator()(const T *first, const T *last, T *result)
    {
        return stl::__copy_t(first, last, result, typename _type_traits<T>::has_trivial_assignment_operator());
    }
};


template<typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    stl::__copy_dispatch<InputIterator, OutputIterator> cd;
    return cd(first, last, result);
}


inline char* copy(const char *first, const char *last, char *result)
{
    memmove(result, first, last - first);
    return result + (last - first);
}

inline unsigned char* copy(const unsigned char *first, const unsigned char *last, unsigned char *result)
{
    memmove(result, first, last - first);
    return result + (last - first);
}





//================================copy_backward=========================


template<typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2 __copy_backward_aux(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result, bidirectional_iterator_tag)
{
    while(last != first)
    {
        *--result = *--last;
    }

    return result;
}


template<typename RandomAccessIterator, typename BidirectionalIterator2>
BidirectionalIterator2 __copy_backward_aux(RandomAccessIterator first, RandomAccessIterator last, BidirectionalIterator2 result, random_access_iterator_tag)
{
    typename iterator_traits<RandomAccessIterator>::difference_type distance = last - first;

    while( distance-- > 0)
    {
        *--result = *--last;
    }

    return result;
}


template<typename BidirectionalIterator1, typename BidirectionalIterator2, typename BoolType>
struct __copy_backward_dispatch
{
public:
    BidirectionalIterator2 operator()(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
    {
        return __copy_backward_aux(first, last, result, iterator_category(first));
    }
};


template<typename T>
struct __copy_backward_dispatch<T*, T*, true_type>
{
    T* operator() (T *first, T *last, T *result)
    {
        return __copy_backward_dispatch<const T*, T*, true_type>()(first, last, result);
    }
};


template<typename T>
struct __copy_backward_dispatch<const T*, T*, true_type>
{
    T* operator() (const T *first, const T *last, T *result)
    {
        ptrdiff_t n = last - first;
        ::memmove(result-n, first, n*sizeof(T));

        return result - n;
    }
};


template<typename BidirectionalIterator1, typename BidirectionalIterator2>
inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
{
    typedef typename _type_traits<typename iterator_traits<BidirectionalIterator2>::value_type>::has_trivial_assignment_operator trivial;
    return __copy_backward_dispatch<BidirectionalIterator1, BidirectionalIterator2, trivial>()(first, last, result);
}


}

#endif // STL_ALGOBASE_H

