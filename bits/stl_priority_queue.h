//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_PRIORITY_QUEUE_H
#define STL_PRIORITY_QUEUE_H


#include<stddef.h>

#include"../vector"
#include"stl_function.h"
#include"stl_heap.h"


namespace stl
{


template<typename T, typename Sequence = stl::vector<T>, typename Compare = stl::less<T> >
class priority_queue
{
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef Sequence container_type;
    typedef T& reference;
    typedef const T& const_reference;


public:
    bool empty()const { m_seq.empty(); }
    size_type size()const { m_seq.size(); }

    //没有non-const的top函数。因为返回一个non-const引用可能会被用户所修改。而top元素
    //必须是堆的最值，随意修改会使得无法满足最值条件
    const_reference top()const { return m_seq.front(); }

public:
    explicit priority_queue(const Compare &comp = Compare(), const Sequence &seq = Sequence());

    template<typename InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare &comp = Compare(), const Sequence &seq = Sequence());

    void push(const T &val);
    void pop();

private:
    Sequence m_seq;
    Compare m_comp;
};



template<typename T, typename Sequence, typename Compare>
priority_queue<T, Sequence, Compare>::priority_queue(const Compare &comp, const Sequence &seq)
    : m_seq(seq),
      m_comp(comp)
{
}


template<typename T, typename Sequence, typename Compare>
template<typename InputIterator>
priority_queue<T, Sequence, Compare>::priority_queue(InputIterator first, InputIterator last, const Compare &comp, const Sequence &seq)
    : m_seq(seq),
      m_comp(comp)
{
    m_seq.insert(m_seq.end(), first, last);
    stl::make_heap(m_seq.begin(), m_seq.end(), m_comp);
}


template<typename T, typename Sequence, typename Compare>
void priority_queue<T, Sequence, Compare>::push(const T &val)
{
    m_seq.push_back(val);
    stl::push_heap(m_seq.begin(), m_seq.end());
}



template<typename T, typename Sequence, typename Compare>
void priority_queue<T, Sequence, Compare>::pop()
{
    stl::pop_heap(m_seq.begin(), m_seq.end());
    m_seq.pop_back();
}

}

#endif // STL_PRIORITY_QUEUE_H

