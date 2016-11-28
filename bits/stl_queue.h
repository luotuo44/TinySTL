//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_QUEUE_H
#define STL_QUEUE_H

#include<stddef.h>

#include"../deque"

namespace stl
{

template<typename T, typename Sequence = stl::deque<T> >
class queue
{
public:
    typedef T  value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;


public:
    queue(const Sequence &seq = Sequence());
    void swap(queue &q);

public:
    bool empty()const { return m_seq.empty(); }
    size_type size()const { return m_seq.size(); }
    reference front() { return m_seq.front(); }
    const_reference front()const { return m_seq.front(); }
    reference back() { return m_seq.back(); }
    const_reference back()const { return m_seq.back(); }

public:
    void push(const T &val);
    void pop();


public:
    bool operator == (const queue &q)const;
    bool operator != (const queue &q)const;
    bool operator <  (const queue &q)const;
    bool operator <= (const queue &q)const;
    bool operator >  (const queue &q)const;
    bool operator >= (const queue &q)const;

private:
    Sequence m_seq;
};




template<typename T, typename Sequence>
queue<T, Sequence>::queue(const Sequence &seq)
    : m_seq(seq)
{
}



template<typename T, typename Sequence>
void queue<T, Sequence>::swap(queue &q)
{
    m_seq.swap(q.m_seq);
}



template<typename T, typename Sequence>
inline void queue<T, Sequence>::push(const T &val)
{
    m_seq.push_back(val);
}



template<typename T, typename Sequence>
inline void queue<T, Sequence>::pop()
{
    m_seq.pop_front();
}


template<typename T, typename Sequence>
inline bool queue<T, Sequence>::operator == (const queue &q)const
{
    return m_seq == q.m_seq;
}


template<typename T, typename Sequence>
inline bool queue<T, Sequence>::operator != (const queue &q)const
{
    return m_seq != q.m_seq;
}


template<typename T, typename Sequence>
inline bool queue<T, Sequence>::operator <  (const queue &q)const
{
    return m_seq <  q.m_seq;
}


template<typename T, typename Sequence>
inline bool queue<T, Sequence>::operator <= (const queue &q)const
{
    return m_seq <= q.m_seq;
}


template<typename T, typename Sequence>
inline bool queue<T, Sequence>::operator >  (const queue &q)const
{
    return m_seq >  q.m_seq;
}


template<typename T, typename Sequence>
inline bool queue<T, Sequence>::operator >= (const queue &q)const
{
    return m_seq >= q.m_seq;
}




//======================================non member function==========================

template<typename T, typename Sequence>
inline void swap(queue<T, Sequence> &lhs, queue<T, Sequence> &rhs)
{
    lhs.swap(rhs);
}

}

#endif // STL_QUEUE_H

