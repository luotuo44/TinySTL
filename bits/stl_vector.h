//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_VECTOR_H
#define STL_VECTOR_H



namespace stl
{


template<typename T, typename Allocator>
class __vector_construct_helper
{
public:
    typedef T* iterator;
    typedef size_t size_type;

    //该类只会申请一次内存
    __vector_construct_helper(size_type cap, const Allocator &allocator)
        : m_start(0), m_finish(0), m_cap(0), m_allocator(allocator)
    {
        m_finish = m_start = m_allocator.allocate(cap);
        m_cap = cap;
    }

    //construct成功后，应该调用release获取之。
    template<typename InputIterator>
    void copy(InputIterator first, InputIterator last)
    {
        m_finish = stl::uninitialized_copy(first, last, m_finish);
    }


    void fill_n(size_type n, const T &val)
    {
        stl::uninitialized_fill_n(m_finish, n, val);
        m_finish += n;
    }

    size_type size()const
    {
        return m_finish - m_start;
    }

    size_type capacity()const
    {
        return m_cap;
    }

    //故意不提供begin()接口，因为如果提供了begin()接口，可能会忘记调用release
    iterator release()
    {
        iterator data = m_start;
        m_cap = 0;
        m_finish = m_start = 0;

        return data;
    }


    ~__vector_construct_helper()
    {
        try
        {
            stl::destroy(m_start, m_finish);
        }
        catch(...)
        {}

        try
        {
            //当m_start为0时，该调用也合法
            m_allocator.deallocate(m_start, m_cap);
        }
        catch(...)
        {}
    }

private:
    __vector_construct_helper(const __vector_construct_helper &);
    __vector_construct_helper& operator = (const __vector_construct_helper &);

private:
    iterator m_start;
    iterator m_finish;//指向未使用的位置
    size_type m_cap;
    Allocator m_allocator;
};


template<typename T, typename Allocator>
class __vector_destroy_helper
{
public:
    typedef T* iterator;
    typedef size_t size_type;

    __vector_destroy_helper(iterator data, size_type size, size_type cap, const Allocator &allocator)
        : m_data(data), m_size(size), m_cap(cap), m_allocator(allocator)
    {}


    ~__vector_destroy_helper()
    {
        try
        {
            stl::destroy(m_data, m_data + m_size);
        }
        catch(...)
        { }

        try
        {
            m_allocator.deallocate(m_data, m_cap);
        }
        catch(...)
        {}
    }

private:
    __vector_destroy_helper(const __vector_destroy_helper &);
    __vector_destroy_helper& operator = (const __vector_destroy_helper &);

private:
    iterator m_data;
    size_type m_size;
    size_type m_cap;
    Allocator m_allocator;
};


//为保证异常安全，局部的资源，须由局部类变量管理。
//为此，vector的内部实现依靠vector_construct_helper和vector_destroy_helper这两个
//类管理局部资源。
template<typename T, typename Allocator = stl::allocator<T> >
class vector
{
private:
    typedef __vector_construct_helper<T, Allocator> vector_construct_helper;
    typedef __vector_destroy_helper<T, Allocator> vector_destroy_helper;

public:
    typedef T  value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef T* iterator;
    typedef const T* const_iterator;
    typedef stl::reverse_iterator<iterator> reverse_iterator;
    typedef stl::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef Allocator allocator_type;

public:
    iterator begin() { return m_start; }
    iterator end() { return m_finish; }
    const_iterator begin()const { return m_start; }
    const_iterator end()const { return m_finish; }
    const_iterator cbegin()const { return m_start; }
    const_iterator cend()const { return m_finish; }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin()const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend()const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin()const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend()const { return const_reverse_iterator(begin()); }


    bool empty()const { return begin() == end(); }
    size_type size()const { return size_type(end() - begin()); }
    size_type capacity()const { return m_end_of_storage - begin(); }
    size_type max_size()const { return size_type(-1)/sizeof(T); }

    reference operator [] (size_type n) { return *(begin() + n); }
    const_reference operator [] (size_type n)const { return *(begin() + n); }

    reference front() { return *begin(); }
    const_reference front()const { return *begin(); }
    reference back()  { return *(end()-1); }
    const_reference back()const { return *(end()-1); }
    pointer data() { return begin(); }
    const_pointer data()const { return begin(); }

    Allocator get_allocator()const { return m_allocator; }

public:
    explicit vector(const Allocator &allocator = Allocator());
    explicit vector(size_type n, const T &val = T(), const Allocator &allocator = Allocator());

    template<typename InputIterator>
    vector(InputIterator first, InputIterator last, const Allocator &allocator = Allocator());

    vector(const vector &vec);
    vector& operator = (const vector &vec);//Basic guarantee
    ~vector();

    void swap(vector &vec);
    void clear();

    void reserve(size_type n);
    void resize(size_type n, const T &val = T());

private:
    //之所以有range和fill的分派，是因为vector(n, val)和vector(first, last)在调用的时候无法正确模板deduce
    //比如vector(10, 20),既可以是n,val 也可以是first,last。因此需要分派
    template<typename InputIterator>
    void __vector_range_fill_dispatch(InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __vector_range_fill_dispatch(InputIterator first, InputIterator last, false_type);


    void __vector_fill_n(size_type n, const T &val);
    template<typename InputIterator>
    void __vector_range(InputIterator first, InputIterator last);

    template<typename InputIterator>
    void __vector_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag);
    template<typename ForwardIterator>
    void __vector_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag);


    template<typename InputIterator>//call by vector constructor
    void __vector_copy_n(InputIterator first, InputIterator last, size_type n);


    void __resize_small(size_type n);
    void __resize_big(size_type n, const T &val);

public:
    void assign(size_type n, const T& val = T());
    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);

private:
    template<typename InputIterator>
    void __assign_range_fill_dispatch(InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __assign_range_fill_dispatch(InputIterator first, InputIterator last, false_type);

    void __assign_fill_n(size_type n, const T &val);

    template<typename InputIterator>
    void __assign_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag);
    template<typename ForwardIterator>
    void __assign_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag);


public:
    void push_back(const T &val);
    void pop_back();


    iterator insert(iterator pos, const T &val);
    void insert(iterator pos, size_type n, const T &val);
    template<typename InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last);


private:
    void __insert_without_enough_capacity(iterator pos, size_type n, const T &val);

    template<typename InputIterator>
    void __insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, false_type);
    template<typename InputIterator>
    void __insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, true_type);

    void __insert_fill_n(iterator pos, size_type n, const T &val);

    template<typename InputIterator>
    void __insert_range_dispatch(iterator pos, InputIterator first, InputIterator last, input_iterator_tag);

    template<typename ForwardIterator>
    void __insert_range_dispatch(iterator pos, ForwardIterator first, ForwardIterator last, forward_iterator_tag);


public:
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

private:
    iterator m_start;
    iterator m_finish;
    iterator m_end_of_storage;

    Allocator m_allocator;
};


template<typename T, typename Allocator>
inline vector<T, Allocator>::vector(const Allocator &allocator)
            : m_start(0), m_finish(0), m_end_of_storage(0), m_allocator(allocator)
{
}


template<typename T, typename Allocator>
inline vector<T, Allocator>::vector(size_type n, const T &val, const Allocator &allocator)
            : m_start(0), m_finish(0), m_end_of_storage(0), m_allocator(allocator)
{
    __vector_fill_n(n, val);
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline vector<T, Allocator>::vector(InputIterator first, InputIterator last, const Allocator &allocator)
            : m_start(0), m_finish(0), m_end_of_storage(0), m_allocator(allocator)
{
    __vector_range_fill_dispatch(first, last, typename  _type_traits<InputIterator>::is_integer());
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::__vector_range_fill_dispatch(InputIterator first, InputIterator last, true_type)
{
    __vector_fill_n(first, last);
}


template<typename T, typename Allocator>
void vector<T, Allocator>::__vector_fill_n(size_type n, const T &val)
{
    vector_construct_helper vc(n, m_allocator);
    vc.fill_n(n, val);

    m_start = vc.release();
    m_finish = m_start + n;
    m_end_of_storage = m_finish;
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::__vector_range_fill_dispatch(InputIterator first, InputIterator last, false_type)
{
    __vector_range(first, last);
}



template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::__vector_range(InputIterator first, InputIterator last)
{
    __vector_range_dispatch(first, last, iterator_category(first));
}


template<typename T, typename Allocator>
template<typename InputIterator>
void vector<T, Allocator>::__vector_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
    while(first != last)
    {
        insert(end(), *first);
        ++first;
    }
}


template<typename T, typename Allocator>
template<typename ForwardIterator>
inline void vector<T, Allocator>::__vector_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
{
    __vector_copy_n(first, last, size_type(stl::distance(first, last)));
}


template<typename T, typename Allocator>
template<typename InputIterator>//call by vector constructor
void vector<T, Allocator>::__vector_copy_n(InputIterator first, InputIterator last, size_type n)
{
    vector_construct_helper vc(n, m_allocator);
    vc.copy(first, last);

    m_start = vc.release();
    m_finish = m_start + n;
    m_end_of_storage = m_start + n;
}


template<typename T, typename Allocator>
inline vector<T, Allocator>::vector(const vector &vec)
            : m_start(0), m_finish(0), m_end_of_storage(0)
{
    __vector_copy_n(vec.begin(), vec.end(), vec.size());
}


template<typename T, typename Allocator>
inline vector<T, Allocator>& vector<T, Allocator>::operator = (const vector &vec)
{
    if( this != &vec )
    {
        assign(vec.begin(), vec.end());
    }

    return *this;
}


template<typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
    {
        vector_destroy_helper(m_start, size(), capacity(), m_allocator);
    }
}


template<typename T, typename Allocator>
void vector<T, Allocator>::swap(vector &vec)
{
    stl::swap(m_start, vec.m_start);
    stl::swap(m_finish, vec.m_finish);
    stl::swap(m_end_of_storage, vec.m_end_of_storage);
}


template<typename T, typename Allocator>
void vector<T, Allocator>::clear()
{
    try
    {
        stl::destroy(begin(), end());
    }
    catch(...)//eat it
    {
    }

    m_finish = m_start;
}



template<typename T, typename Allocator>
inline void vector<T, Allocator>::assign(size_type n, const T& val)
{
    __assign_fill_n(n, val);
}



template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::assign(InputIterator first, InputIterator last)
{
    __assign_range_fill_dispatch(first, last, typename  _type_traits<InputIterator>::is_integer());
}



template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::__assign_range_fill_dispatch(InputIterator first, InputIterator last, true_type)
{
    __assign_fill_n(first, last);
}


template<typename T, typename Allocator>
template<typename InputIterator>
void vector<T, Allocator>::__assign_range_fill_dispatch(InputIterator first, InputIterator last, false_type)
{
    __assign_range_dispatch(first, last, iterator_category(first));
}


template<typename T, typename Allocator>
void vector<T, Allocator>::__assign_fill_n(size_type n, const T &val)
{
    if( capacity() >= n)
    {
        clear();

        stl::uninitialized_fill_n(begin(), n, val);
        m_finish = begin() + n;
    }
    else//except safe: strong guarantee
    {
        size_type old_size = size();
        size_type old_capacity = capacity();
        size_type new_capacity = stl::max(2*old_capacity, n);

        vector_construct_helper vc(new_capacity, m_allocator);
        vc.fill_n(n, val);

        vector_destroy_helper vd(m_start, old_size, old_capacity, m_allocator);
        m_start = vc.release();
        m_finish = m_start + n;
        m_end_of_storage = m_start + new_capacity;
    }
}



template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::__assign_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
    clear();

    while( first != last)
    {
        insert(end(), *first);
        ++first;
    }
}



template<typename T, typename Allocator>
template<typename ForwardIterator>
void vector<T, Allocator>::__assign_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
{
    size_type n = size_type(stl::distance(first, last));

    if( capacity() >= n)
    {
        clear();
        m_finish = stl::uninitialized_copy(first, last, m_start);
    }
    else//except safe: strong guarantee
    {
        size_type old_size = size();
        size_type old_capacity = capacity();
        size_type new_capacity = stl::max(2*old_capacity, n);

        vector_construct_helper vc(new_capacity, m_allocator);
        vc.copy(first, last);

        vector_destroy_helper vd(m_start, old_size, old_capacity, m_allocator);
        m_start = vc.release();
        m_finish = m_start + n;
        m_end_of_storage = m_start + new_capacity;
    }
}



template<typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type n)
{
    if( n > capacity() )
    {
        size_type old_size = size();
        //相信调用方，将新的容量设置为n而不是max(2*capacity(), n)
        vector_construct_helper vc(n, m_allocator);
        vc.copy(begin(), end());

        vector_destroy_helper vd(m_start, size(), capacity(), m_allocator);
        m_start = vc.release();
        m_finish = m_start + old_size;
        m_end_of_storage = m_start + n;
    }
}


template<typename T, typename Allocator>
inline void vector<T, Allocator>::resize(size_type n, const T &val)
{
    if( n < size() )
        __resize_small(n);
    else
        __resize_big(n, val);
}


template<typename T, typename Allocator>
void vector<T, Allocator>::__resize_small(size_type n)
{
    iterator new_finish = begin() + n;

    try
    {
        stl::destroy(new_finish, end());
    }
    catch(...)//eat it
    {
    }

    m_finish = new_finish;
}


template<typename T, typename Allocator>
void vector<T, Allocator>::__resize_big(size_type n, const T &val)
{
    size_type old_size = size();

    if( n < capacity() )
    {
        stl::uninitialized_fill_n(end(), n-old_size, val);
        m_finish += n - old_size;
    }
    else
    {
        size_type old_capacity = capacity();
        size_type new_capacity = stl::max(2*old_capacity, n);
        vector_construct_helper vc(new_capacity, m_allocator);

        vc.copy(begin(), end());
        vc.fill_n(n-old_size, val);

        vector_destroy_helper vd(m_start, old_size, old_capacity, m_allocator);
        m_start = vc.release();
        m_finish = m_start + n-old_size;
        m_end_of_storage = m_start + new_capacity;
    }
}


//=========================================================================
template<typename T, typename Allocator>
inline void vector<T, Allocator>::push_back(const T &val)
{
    insert(end(), val);
}


template<typename T, typename Allocator>
void vector<T, Allocator>::pop_back()
{
    if( size() == 0)
        return ;

    try
    {
        //必须先--,然后才调用destroy。这样可以防止当destroy失败抛异常后，end()-1这个元素
        //以后都不会再次调用destroy。即保证同一元素不会两次调用析构函数
        --m_finish;
        m_allocator.destroy(m_finish);
    }catch(...)//eat it
    {
    }
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const T &val)
{
    if( size() < capacity() )//有足够的空间
    {
        if(pos == end())
        {
            m_allocator.construct(m_finish, val);
            ++m_finish;
        }
        else
        {
            m_allocator.construct(m_finish, back());
            ++m_finish;

            stl::copy_backward(pos, m_finish-2, m_finish-1);
            *pos = val;
        }
    }
    else
    {
        size_type dis = size_type(pos - begin());
        __insert_without_enough_capacity(pos, 1, val);

        pos = m_start + dis;
    }

    //返回值的语义: *(insert(pos, val))是val的一个复制品
    return pos;
}



template<typename T, typename Allocator>
void vector<T, Allocator>::__insert_without_enough_capacity(iterator pos, size_type n, const T &val)
{
    size_type old_size = size();
    size_type old_capacity = capacity();
    size_type new_capacity = stl::max(2*old_capacity, old_capacity + n);

    vector_construct_helper vc(new_capacity, m_allocator);
    vc.copy(begin(), pos);
    vc.fill_n(n, val);
    vc.copy(pos, end());

    vector_destroy_helper vd(m_start, old_size, old_capacity, m_allocator);
    m_start = vc.release();
    m_finish = m_start + old_size + n;
    m_end_of_storage = m_start + new_capacity;
}


template<typename T, typename Allocator>
inline void vector<T, Allocator>::insert(iterator pos, size_type n, const T &val)
{
    __insert_fill_n(pos, n, val);
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::insert(iterator pos, InputIterator first, InputIterator last)
{
    __insert_range_fill_dispatch(pos, first, last, typename  _type_traits<InputIterator>::is_integer());
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::__insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, false_type)
{
    __insert_range_dispatch(pos, first, last, iterator_category(first));
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void vector<T, Allocator>::__insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, true_type)
{
    __insert_fill_n(pos, first, last);
}


template<typename T, typename Allocator>
void vector<T, Allocator>::__insert_fill_n(iterator pos, size_type n, const T &val)
{
    if( size() + n > capacity() )//容量不够
    {
        __insert_without_enough_capacity(pos, n, val);
    }
    else
    {
        size_type backward_size = end() - pos;
        iterator old_finish = end();

        //之所以这里要if-else，是因为uninitialized_前缀函数的行为和非uninitialized_前缀函数
        //的行为有许多不同。前者的目标位置未初始化，被覆盖时不需要调用析构函数。而后者的目标位置
        //已经初始化，被覆盖时需要调用析构函数。
        if( n >= backward_size )
        {
            stl::uninitialized_fill_n(old_finish, n - backward_size, val);
            m_finish += n - backward_size;

            //上面和下面语句的调用顺序不要颠倒。这样可以保证在出现异常时也能处理合法状态
            //now, end() equals to pos+n
            stl::uninitialized_copy(pos, old_finish, pos + n);
            m_finish += old_finish - pos;

            stl::fill_n(pos, backward_size, val);
        }
        else
        {
            stl::uninitialized_copy(old_finish-n, old_finish, old_finish);
            m_finish += n;

            stl::copy_backward(pos, old_finish-n, old_finish);
            stl::fill_n(pos, n, val);
        }
    }
}





template<typename T, typename Allocator>
template<typename InputIterator>
void vector<T, Allocator>::__insert_range_dispatch(iterator pos, InputIterator first, InputIterator last, input_iterator_tag)
{
    for(; first != last; ++pos, ++first)
    {
        pos = insert(pos, *first);
    }
}


template<typename T, typename Allocator>
template<typename ForwardIterator>
void vector<T, Allocator>::__insert_range_dispatch(iterator pos, ForwardIterator first, ForwardIterator last, forward_iterator_tag)
{
    size_type n = size_type(stl::distance(first, last));

    if( size() + n > capacity() )//容量不够
    {
        size_type old_size = size();
        size_type old_capacity = capacity();
        size_type new_capacity = stl::max(2*old_capacity, old_capacity+n);

        vector_construct_helper vc(new_capacity, m_allocator);

        vc.copy(begin(), pos);
        vc.copy(first, last);
        vc.copy(pos, end());

        vector_destroy_helper vd(m_start, old_size, old_capacity, m_allocator);
        m_start = vc.release();
        m_finish = m_start + old_size + n;
        m_end_of_storage = m_start + new_capacity;
    }
    else
    {
        size_type backward_size = end() - pos;
        iterator old_finish = end();

        //之所以这里要if-else，是因为uninitialized_前缀函数的行为和非uninitialized_前缀函数
        //的行为有许多不同。前者的目标位置未初始化，被覆盖时不需要调用析构函数。而后者的目标位置
        //已经初始化，被覆盖时需要调用析构函数。
        if( n >= backward_size )
        {
            stl::uninitialized_copy(first+backward_size, last, old_finish);
            m_finish += n - backward_size;

            //上面和下面语句的调用顺序不要颠倒。这样可以保证在出现异常时也能处理合法状态
            //now, end() equals to pos + n
            stl::uninitialized_copy(pos, old_finish, pos+n);
            m_finish += backward_size;

            stl::copy(first, first+backward_size, pos);
        }
        else
        {
            stl::uninitialized_copy(old_finish-n, old_finish, old_finish);
            m_finish += n;

            stl::copy_backward(pos, old_finish-n, old_finish);
            stl::copy(first, last, pos);
        }
    }
}


//==========================================================================

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator pos)
{
    if( pos >= end() )
        return pos;
    else if( pos + 1 == end() )//最后一个元素，此时不no-throw guarantee
    {
        try
        {
            --m_finish;
            m_allocator.destroy(m_finish);
        }
        catch(...)//eat it
        {}
    }
    else
    {
        stl::copy(pos+1, end(), pos);

        --m_finish;
        m_allocator.destroy(m_finish);
    }

    return pos;
}


template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
{
    if( last == end() )//包含最后一个元素，此时不应抛异常
    {
        try
        {
            stl::destroy(first, last);
        }
        catch(...)//eat it
        {}

        m_finish -= last - first;
    }
    else
    {
        iterator old_finish = m_finish;
        stl::copy(last, end(), first);

        m_finish -= last - first;

        stl::destroy(m_finish, old_finish);
    }

    return first;
}

//================================non member function========================

template<typename T, typename Allocator>
inline bool operator == (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
    return (lhs.size() == rhs.size()) && equal(lhs.begin(), lhs.end(), rhs.begin());
}


template<typename T, typename Allocator>
inline bool operator != (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
    return !(lhs == rhs);
}


template<typename T, typename Allocator>
inline bool operator < (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


template<typename T, typename Allocator>
inline bool operator > (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
    return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}



template<typename T, typename Allocator>
inline bool operator <= (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
    return !(rhs > lhs);
}


template<typename T, typename Allocator>
inline bool operator >= (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
    return !(rhs < lhs);
}


template<typename T, typename Allocator>
inline void swap(vector<T, Allocator> &lhs, vector<T, Allocator> &rhs)
{
    lhs.swap(rhs);
}


}

#endif // STL_VECTOR_H

