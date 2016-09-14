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



}

#endif // STL_ITERATOR

