//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_STACK_H
#define STL_STACK_H


#include"../deque"

namespace stl
{

template<typename T, typename Sequence = stl::deque<T> >
class stack
{
public:
    typedef T  value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef Sequence container_type;

public:
    explicit stack(const Sequence &seq = Sequence());
    void swap(stack &st);

public:
    size_type size()const { return m_seq.size(); }
    bool empty()const { return m_seq.empty(); }
    reference top() { return m_seq.back(); }
    const_reference top()const { return m_seq.back(); }


public:
    void push(const T &val) { m_seq.push_back(val); }
    void pop() { m_seq.pop_back(); }


public:
    bool operator == (const stack &st)const;
    bool operator != (const stack &st)const;
    bool operator <  (const stack &st)const;
    bool operator <= (const stack &st)const;
    bool operator >  (const stack &st)const;
    bool operator >= (const stack &st)const;

private:
    Sequence m_seq;
};


template<typename T, typename Sequence>
stack<T, Sequence>::stack(const Sequence &seq)
    : m_seq(seq)
{}


template<typename T, typename Sequence>
inline void stack<T, Sequence>::swap(stack &st)
{
    m_seq.swap(st.m_seq);
}



template<typename T, typename Sequence>
inline bool stack<T, Sequence>::operator == (const stack &st)const
{
    return m_seq == st.m_seq;
}


template<typename T, typename Sequence>
inline bool stack<T, Sequence>::operator != (const stack &st)const
{
    return m_seq != st.m_seq;
}


template<typename T, typename Sequence>
inline bool stack<T, Sequence>::operator <  (const stack &st)const
{
    return m_seq < st.m_seq;
}


template<typename T, typename Sequence>
inline bool stack<T, Sequence>::operator <= (const stack &st)const
{
    return m_seq <= st.m_seq;
}


template<typename T, typename Sequence>
inline bool stack<T, Sequence>::operator >  (const stack &st)const
{
    return m_seq > st.m_seq;
}


template<typename T, typename Sequence>
inline bool stack<T, Sequence>::operator >= (const stack &st)const
{
    return m_seq >= st.m_seq;
}


//======================================non member function==========================


template<typename T, typename Sequence>
inline void swap(stack<T, Sequence> &lhs, stack<T, Sequence> &rhs)
{
    lhs.swap(rhs);
}

}


#endif // STL_STACK_H

