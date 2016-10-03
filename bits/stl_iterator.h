//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_ITERATOR
#define STL_ITERATOR


namespace stl
{


template<typename Container>
class back_insert_iterator
{
public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

public:
    explicit back_insert_iterator(Container &con)
        : m_con(&con)
    {}


    back_insert_iterator& operator = (const typename Container::value_type &val)
    {
        m_con->push_back(val);
        return *this;
    }

    back_insert_iterator& operator ++ ()
    {
        return *this;
    }

    back_insert_iterator& operator ++ (int)
    {
        return *this;
    }

    back_insert_iterator& operator * ()
    {
        return *this;
    }

private:
    //为了保证Assignable，必须使用指针而非引用
    Container *m_con;
};


template<typename Container>
inline back_insert_iterator<Container> back_inserter(Container &con)
{
    return back_insert_iterator<Container>(con);
}



template<typename Container>
class front_insert_iterator
{
public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

public:
    explicit front_insert_iterator(Container &con)
        : m_con(&con)
    {}


    front_insert_iterator& operator = (const typename Container::value_type &val)
    {
        m_con->push_front(val);
        return *this;
    }


    front_insert_iterator& operator *()
    {
        return *this;
    }

    front_insert_iterator& operator ++()
    {
        return *this;
    }

    front_insert_iterator& operator ++(int)
    {
        return *this;
    }

private:
    //为了保证Assignable，必须使用指针而非引用
    Container *m_con;
};


template<typename Container>
inline front_insert_iterator<Container> front_inserter(Container &con)
{
    return front_insert_iterator<Container>(con);
}




template<typename Container>
class insert_iterator
{
public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;


public:
    insert_iterator(Container &con, typename Container::iterator it)
        : m_con(&con), m_it(it)
    {}

    insert_iterator& operator = (const typename Container::value_type &val)
    {
        m_it = m_con->insert(m_it, val);
        ++m_it;
        return *this;
    }

    insert_iterator& operator *()
    {
        return *this;
    }

    insert_iterator& operator ++()
    {
        return *this;
    }

    insert_iterator& operator ++(int)
    {
        return *this;
    }

private:
    //为了保证Assignable，必须使用指针而非引用
    Container *m_con;
    typename Container::iterator m_it;
};



template<typename Container, typename Iterator>
inline insert_iterator<Container> inserter(Container &con, Iterator it)
{
    typename Container::iterator iter(it);
    return insert_iterator<Container>(con, iter);
}



//================================================================================

template<typename Iterator>
class reverse_iterator
{
public:
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::reference reference;
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

    typedef Iterator iterator_type;
    typedef reverse_iterator<Iterator> self;
public:

    reverse_iterator()
    {}

    explicit reverse_iterator(Iterator it)
        : m_it(it)
    {}

    reverse_iterator(const reverse_iterator &ri)
        : m_it(ri.m_it)
    {}

    //一个non-const iterator 可以复制构造一个const iterator
    template<typename I>
    reverse_iterator(const reverse_iterator<I> &ri)
        : m_it(ri.base())//不能直接使用ri.m_it，I不等于Iterator时，无法访问私有成员
    {
    }

    //一个non-const iterator 可以赋值给一个const iterator
    template<typename I>
    self& operator = (const reverse_iterator<I> &ri)
    {
        m_it = ri.base();
        return *this;
    }

    Iterator base()const
    {
        return m_it;
    }


    //不需要有non-const版本。因为reverse_iterator是否const 和 m_it指向的值无关
    reference operator * ()const
    {
        Iterator tmp(m_it);
        return *--tmp;
    }


    //同上，没有non-const版本
    pointer operator -> ()const
    {
        return &(operator *());
    }

    self& operator ++ ()
    {
        --m_it;
        return *this;
    }

    self operator ++ (int)
    {
        reverse_iterator tmp(*this);
        --m_it;
        return tmp;
    }

    self& operator -- ()
    {
        ++m_it;
        return *this;
    }

    self operator -- (int)
    {
        reverse_iterator tmp(*this);
        ++m_it;
        return tmp;
    }


    self& operator += (difference_type n)
    {
        m_it -= n;
        return *this;
    }

    self operator + (difference_type n)const
    {
        reverse_iterator tmp(*this);
        tmp += n;
        return tmp;
    }

    self& operator -= (difference_type n)
    {
        m_it += n;
        return *this;
    }

    self operator - (difference_type n)const
    {
        reverse_iterator tmp(*this);
        tmp -= n;
        return tmp;
    }

    reference operator [] (difference_type n)const
    {
        return *(*this + n);
    }

private:
    Iterator m_it;
};



template<typename Iterator>
inline typename reverse_iterator<Iterator>::difference operator - (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
    return lhs - rhs;
}


template<typename Iterator>
inline reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &ri)
{
    return ri + n;
}


template<typename Iterator>
inline bool operator == (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
    return lhs.base() == rhs.base();
}


template<typename Iterator>
inline bool operator != (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
    return lhs.base() != rhs.base();
}


template<typename Iterator>
inline bool operator < (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
    return lhs.base() > rhs.base();
}

template<typename Iterator>
inline bool operator <= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
    return lhs.base() >= rhs.base();
}


template<typename Iterator>
inline bool operator > (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
    return lhs.base() < rhs.base();
}

template<typename Iterator>
inline bool operator >= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
    return lhs.base() <= rhs.base();
}


}

#endif // STL_ITERATOR

