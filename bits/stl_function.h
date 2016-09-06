//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_FUNCTION_H
#define STL_FUNCTION_H


namespace stl
{

template<typename Arg, typename Result>
struct unary_function
{
    typedef Arg argument_type;
    typedef Result result_type;
};


template<typename Arg1, typename Arg2, typename Result>
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};



template<typename T>
struct plus : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x + y;
    }
};


template<typename T>
struct minus : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x - y;
    }
};




template<typename T>
struct multiplies : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x * y;
    }
};


template<typename T>
struct divides : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x / y;
    }
};


template<typename T>
struct modulus : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x % y;
    }
};


template<typename T>
struct negate : public unary_function<T, T>
{
    T operator () (const T &x)const
    {
        return -x;
    }
};


//====================================================================================


template<typename T>
struct equal_to : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x == y;
    }
};


template<typename T>
struct not_equal_to : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x != y;
    }
};


template<typename T>
struct less : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x < y;
    }
};


template<typename T>
struct greater : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x > y;
    }
};


template<typename T>
struct less_equal : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x <= y;
    }
};


template<typename T>
struct greater_equal : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x >= y;
    }
};


//=====================================================================================

template<typename T>
struct logical_and : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x && y;
    }
};


template<typename T>
struct logical_or : public binary_function<T, T, bool>
{
    bool operator () (const T &x, const T &y)const
    {
        return x || y;
    }
};


template<typename T>
struct logical_not : public unary_function<T, bool>
{
    bool operator () (const T &x)const
    {
        return !x;
    }
};

//=======================================================================================

template<typename T>
struct bit_and : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x & y;
    }
};


template<typename T>
struct bit_or : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x | y;
    }
};


template<typename T>
struct bit_xor : public binary_function<T, T, T>
{
    T operator () (const T &x, const T &y)const
    {
        return x ^ y;
    }
};

//=======================================================================================

template<typename T>
struct identity : public unary_function<T, T>
{
    const T& operator () (const T &x)const
    {
        return x;
    }
};


template<typename Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type>
{
    const typename Pair::first_type& operator () (const Pair &p)const
    {
        return p.first;
    }
};


template<typename Pair>
struct select2nd : public unary_function<Pair, typename Pair::second_type>
{
    const typename Pair::second_type& operator () (const Pair &p)const
    {
        return p.second;
    }
};



template<typename Arg1, typename Arg2>
struct project1st : public binary_function<Arg1, Arg2, Arg1>
{
    const Arg1& operator () (const Arg1 &x, const Arg2&)const
    {
        return x;
    }
};


template<typename Arg1, typename Arg2>
struct project2nd : public binary_function<Arg1, Arg2, Arg2>
{
    const Arg2& operator () (const Arg1 &, const Arg2 &y)const
    {
        return y;
    }
};


}

#endif // STL_FUNCTION_H

