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

    T& operator () (T &x)const
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

    typename Pair::first_type& operator () (Pair &p)const
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

    typename Pair::second_type& operator () (Pair &p)const
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

    Arg1& operator () (Arg1 &x, const Arg2 &)const
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

    Arg2& operator () (const Arg1 &, Arg2 &y)const
    {
        return y;
    }
};


//====================================================================================


template<typename Predicate>
class unary_negate : public unary_function<typename Predicate::argument_type, bool>
{
public:
    explicit unary_negate(const Predicate &pred)
        : m_pred(pred)
    {}

    bool operator () (const typename Predicate::argument_type &x)const
    {
        return !m_pred(x);
    }

private:
    Predicate m_pred;
};


template<typename Predicate>
inline unary_negate<Predicate> not1(const Predicate &pred)
{
    return unary_negate<Predicate>(pred);
}



template<typename Predicate>
class binary_negate : public binary_function<typename Predicate::first_argument_type, typename Predicate::second_argument_type, bool>
{
public:
    explicit binary_negate(const Predicate &pred)
        : m_pred(pred)
    {
    }

    bool operator () (const typename Predicate::first_argument_type &x, const typename Predicate::second_argument_type &y)const
    {
        return !m_pred(x, y);
    }

private:
    Predicate m_pred;
};



template<typename Predicate>
inline binary_negate<Predicate> not2(const Predicate &pred)
{
    return binary_negate<Predicate>(pred);
}




template<typename BinaryFunction>
class binder1st : public unary_function<typename BinaryFunction::second_argument_type, typename BinaryFunction::result_type>
{
public:
    binder1st(const BinaryFunction &op, const typename BinaryFunction::first_argument_type &x)
        : m_op(op), m_x(x)
    {}

    typename BinaryFunction::result_type operator () (const typename BinaryFunction::second_argument_type &y)const
    {
        return m_op(m_x, y);
    }

    typename BinaryFunction::result_type operator () (typename BinaryFunction::second_argument_type &y)const
    {
        return m_op(m_x, y);
    }


private:
    BinaryFunction m_op;
    typename BinaryFunction::first_argument_type m_x;
};



template<typename BinaryFunction, typename T>
inline binder1st<BinaryFunction> bind1st(const BinaryFunction &op, const T &x)
{
    return binder1st<BinaryFunction>(op, typename BinaryFunction::first_argument_type(x) );
}



template<typename BinaryFunction>
class binder2nd : public unary_function<typename BinaryFunction::first_argument_type, typename BinaryFunction::result_type>
{
public:
    binder2nd(const BinaryFunction &op, const typename BinaryFunction::second_argument_type &y)
        : m_op(op), m_y(y)
    {
    }

    typename BinaryFunction::result_type operator ()(const typename BinaryFunction::first_argument_type &x)const
    {
        return m_op(x, m_y);
    }

    typename BinaryFunction::result_type operator ()(typename BinaryFunction::first_argument_type &x)const
    {
        return m_op(x, m_y);
    }

private:
    BinaryFunction m_op;
    typename BinaryFunction::second_argument_type m_y;
};


template<typename BinaryFunction, typename T>
inline binder2nd<BinaryFunction> bind2nd(const BinaryFunction &op, const T &y)
{
    return binder2nd<BinaryFunction>(op, typename BinaryFunction::second_argument_type(y));
}



template<typename Arg, typename Result>
class pointer_to_unary_function : public unary_function<Arg, Result>
{
public:
    pointer_to_unary_function(Result (*p)(Arg))
        : m_p(p)
    {}

    Result operator () (const Arg &x)const
    {
        return m_p(x);
    }

private:
    Result (*m_p)(Arg);
};


template<typename Arg1, typename Arg2, typename Result>
class pointer_to_binary_function : public binary_function<Arg1, Arg2, Result>
{
public:
    pointer_to_binary_function(Result (*p)(Arg1, Arg2) )
        : m_p(p)
    {}

    Result operator () (const Arg1 &x, const Arg2 &y)const
    {
        return m_p(x, y);
    }

private:
    Result (*m_p)(Arg1, Arg2);
};



template<typename Arg, typename Result>
inline pointer_to_unary_function<Arg, Result> ptr_fun(Result (*p)(Arg) )
{
    return pointer_to_unary_function<Arg, Result>(p);
}


template<typename Arg1, typename Arg2, typename Result>
inline pointer_to_binary_function<Arg1, Arg2, Result> ptr_fun(Result (*p)(Arg1, Arg2) )
{
    return pointer_to_binary_function<Arg1, Arg2, Result>(p);
}




template<typename Operator1, typename Operator2>
class unary_compose : public unary_function<typename Operator2::argument_type, typename Operator1::result_type>
{
public:
    unary_compose(const Operator1 &op1, const Operator2 &op2)
        : m_op1(op1), m_op2(op2)
    {
    }

    typename Operator1::result_type operator () (const typename Operator2::argument_type &x)const
    {
        return m_op1(m_op2(x));
    }

private:
    Operator1 m_op1;
    Operator2 m_op2;
};


template<typename Operator1, typename Operator2>
inline unary_compose<Operator1, Operator2> compose1(const Operator1 &op1, const Operator2 &op2)
{
    return unary_compose<Operator1, Operator2>(op1, op2);
}


template<typename Operator1, typename Operator2, typename Operator3>
class binary_compose : public unary_function<typename Operator2::argument_type, typename Operator1::result_type>
{
public:
    binary_compose(const Operator1 &op1, const Operator2 &op2, const Operator3 &op3)
        : m_op1(op1), m_op2(op2), m_op3(op3)
    {}

    typename Operator1::result_type operator () (const typename Operator2::argument_type &x)const
    {
        return m_op1(m_op2(x), m_op3(x));
    }

private:
    Operator1 m_op1;
    Operator2 m_op2;
    Operator3 m_op3;
};


template<typename Operator1, typename Operator2, typename Operator3>
inline binary_compose<Operator1, Operator2, Operator3> compose2(const Operator1 &op1, const Operator2 &op2, const Operator3 &op3)
{
    return binary_compose<Operator1, Operator2, Operator3>(op1, op2, op3);
}



//===============================================================================================


template<typename R, typename X>
class mem_fun_t : public unary_function<X*, R>
{
public:
    explicit mem_fun_t(R (X::*p)())
        : m_p(p)
    {
    }


    R operator ()(X *x)const
    {
        return (x->*m_p)();
    }

private:
    R (X::*m_p)();
};




template<typename R, typename X>
class mem_fun_ref_t : public unary_function<X, R>
{
public:
    explicit mem_fun_ref_t(R (X::*p)())
        : m_p(p)
    {
    }

    R operator ()(X &x)const
    {
        return (x.*m_p)();
    }

private:
    R (X::*m_p)();
};




template<typename R, typename X>
class const_mem_fun_t : public unary_function<const X*, R>
{
public:
    explicit const_mem_fun_t(R (X::*p)()const)
        : m_p(p)
    {}

    R operator () (const X *x)const
    {
        return (x->*m_p)();
    }

private:
    R (X::*m_p)()const;
};




template<typename R, typename X>
class const_mem_fun_ref_t : public unary_function<X, R>
{
public:
    explicit const_mem_fun_ref_t(R (X::*p)()const)
        : m_p(p)
    {
    }

    R operator () (const X &x)const
    {
        return (x.*m_p)();
    }

private:
    R (X::*m_p)()const;
};



template<typename R, typename X, typename A>
class mem_fun1_t : public binary_function<X*, A, R>
{
public:
    explicit mem_fun1_t(R (X::*p)(A))
        : m_p(p)
    {
    }


    R operator ()(X *x, A a)const
    {
        return (x->*m_p)(a);
    }

private:
    R (X::*m_p)(A);
};



template<typename R, typename X, typename A>
class mem_fun1_ref_t : public binary_function<X, A, R>
{
public:
    explicit mem_fun1_ref_t(R (X::*p)(A))
        : m_p(p)
    {}

    R operator () (X &x, A a)const
    {
        return (x.*m_p)(a);
    }

private:
    R (X::*m_p)(A);
};



template<typename R, typename X, typename A>
class const_mem_fun1_t : public binary_function<const X*, A, R>
{
public:
    explicit const_mem_fun1_t(R (X::*p)(A)const)
        : m_p(p)
    {}

    R operator () (const X *x, A a)const
    {
        return (x->*m_p)(a);
    }

private:
    R (X::*m_p)(A)const;
};




template<typename R, typename X, typename A>
class const_mem_fun1_ref_t : public binary_function<X, A, R>
{
public:
    explicit const_mem_fun1_ref_t(R (X::*p)(A) const)
        : m_p(p)
    {}

    R operator () (const X &x, A a)const
    {
        return (x.*m_p)(a);
    }

private:
    R (X::*m_p)(A)const;
};




template<typename R, typename X>
inline mem_fun_t<R, X> mem_fun(R (X::*p)())
{
    return mem_fun_t<R, X>(p);
}


template<typename R, typename X>
inline mem_fun_ref_t<R, X> mem_fun_ref(R (X::*p)())
{
    return mem_fun_ref_t<R, X>(p);
}



template<typename R, typename X>
inline const_mem_fun_t<R, X> mem_fun( R (X::*p)()const )
{
    return const_mem_fun_t<R, X>(p);
}


template<typename R, typename X>
inline const_mem_fun_ref_t<R, X> mem_fun_ref(R (X::*p)() const)
{
    return const_mem_fun_ref_t<R, X>(p);
}


//---------------------------------------

template<typename R, typename X, typename A>
inline mem_fun1_t<R, X, A> mem_fun(R (X::*p)(A))
{
    return mem_fun1_t<R, X, A>(p);
}


template<typename R, typename X, typename A>
inline mem_fun1_ref_t<R, X, A> mem_fun_ref(R (X::*p)(A))
{
    return mem_fun1_ref_t<R, X, A>(p);
}



template<typename R, typename X, typename A>
inline const_mem_fun1_t<R, X, A> mem_fun(R (X::*p)(A)const)
{
    return const_mem_fun1_t<R, X, A>(p);
}



template<typename R, typename X, typename A>
inline const_mem_fun1_ref_t<R, X, A> mem_fun_ref(R (X::*p)(A)const)
{
    return const_mem_fun1_ref_t<R, X, A>(p);
}


//========================================================================================

template<typename R, typename X>
class mem_fun_type : public unary_function<X, R>
{
public:
    explicit mem_fun_type(R (X::*p)())
        : m_p(p)
    {}

    R operator () (X &x)const
    {
        return (x.*m_p)();
    }

    R operator () (X *x)const
    {
        return (x->*m_p)();
    }

private:
    R (X::*m_p)();
};


template<typename R, typename X>
inline mem_fun_type<R, X> mem_fn(R (X::*p)())
{
    return mem_fun_type<R, X>(p);
}



}

#endif // STL_FUNCTION_H

