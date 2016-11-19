//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_DEQUE
#define STL_DEQUE


namespace stl
{

template<typename T, typename Ref, typename Ptr, size_t BufferSize>
struct __DequeIterator
{
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef random_access_iterator_tag iterator_category;
    typedef T** map_pointer;
    typedef __DequeIterator self;

    __DequeIterator()
        : m_cur(0), m_first(0), m_last(0), m_node(0)
    {
    }

    __DequeIterator(pointer cur, pointer first, pointer last, map_pointer node)
        : m_cur(cur), m_first(first), m_last(last), m_node(node)
    {
    }


    template<typename U, typename URef, typename UPtr, size_t UBufferSize>
    __DequeIterator(const __DequeIterator<U, URef, UPtr, UBufferSize> &x)
        : m_cur(x.m_cur), m_first(x.m_first), m_last(x.m_last), m_node(x.m_node)
    {
        //编译期判别Buffsize 和 UBufferSize是否相等
        int tmp[(BufferSize == UBufferSize)? 1 : -1];
        (void)tmp;//避免未使用警告
    }


    template<typename U, typename URef, typename UPtr, size_t UBufferSize>
    __DequeIterator& operator = (const __DequeIterator<U, URef, UPtr, UBufferSize> &x)
    {
        m_cur = x.m_cur;
        m_first = x.m_first;
        m_last = x.m_first;
        m_node = x.m_node;

        //编译期判别Buffsize 和 UBufferSize是否相等
        int tmp[(BufferSize == UBufferSize)? 1 : -1];
        (void)tmp;//避免未使用警告
    }


    void swap(__DequeIterator &x)
    {
        stl::swap(m_node, x.m_node);
        stl::swap(m_cur, x.m_cur);
        stl::swap(m_first, x.m_first);
        stl::swap(m_last, x.m_last);
    }


    reference operator * ()const { return *m_cur; }
    pointer operator -> ()const { return m_cur; }

    self& operator ++ ()
    {
        ++m_cur;
        if( m_cur == m_last )
        {
            set_node(m_node+1);
            m_cur = m_first;
        }

        return *this;
    }

    self operator ++ (int)
    {
        self tmp(*this);
        ++*this;
        return tmp;
    }

    self& operator -- ()
    {
        if( m_cur == m_first )
        {
            set_node(m_node-1);
            m_cur = m_last;
        }

        --m_cur;
        return *this;
    }

    self operator -- (int)
    {
        self tmp(*this);
        --*this;
        return tmp;
    }


    difference_type operator - (const self &x)const
    {
        return static_cast<difference_type>(BufferSize) * (m_node-x.m_node)
                + (m_cur - m_first) - (x.m_cur - x.m_first);
    }

    self& operator += (difference_type n)
    {
        //n可能为负数，offset用于判断移动后的位置是否和当前的在同一个buffer里面
        difference_type offset = n + (m_cur - m_last);

        if( offset >= 0 )
        {
            if(offset < difference_type(BufferSize) )//在同一个buffer里
                m_cur += n;
            else
            {
                //前进node_offset个node的位置
                difference_type node_offset = offset / BufferSize;
                set_node(m_node + node_offset);
                m_cur = m_first + offset % BufferSize;
            }
        }
        else //向后退
        {
            difference_type node_offset = (-offset-1)/BufferSize + 1;
            set_node(m_node - node_offset);
            m_node = m_first + (offset + node_offset*BufferSize);
        }

        return *this;
    }


    self operator + (difference_type n)const
    {
        self tmp(*this);
        tmp += n;
        return tmp;
    }

    self& operator -= (difference_type n)
    {
        return *this += -n;
    }

    self operator - (difference_type n)const
    {
        self tmp(*this);
        tmp -= n;
        return tmp;
    }

    bool operator == (const self &x)const
    {
        return m_cur == x.m_cur;
    }

    bool operator != (const self &x)const
    {
        return !(*this == x);
    }

    bool operator < (const self &x)const
    {
        return m_node == x.m_node ? m_cur < x.m_cur : m_node < x.m_node;
    }


    void set_node(map_pointer node)
    {
        m_node = node;
        m_first = *m_node;
        m_last = m_first + static_cast<difference_type>(BufferSize);
    }

    pointer m_cur;
    pointer m_first;
    pointer m_last;
    map_pointer m_node;
};


template<typename T, typename Allocator, size_t SIZE>
class __deque_buffer_construct_helper
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef size_t size_type;

    __deque_buffer_construct_helper()
        : m_start(0), m_finish(0)
    {
    }

    //使用二段式是因为需要无参构造参数，并且需要使用外界传递过来的分配器
    void allocate(const Allocator &allocator)
    {
        m_allocator = allocator;
        m_data = m_allocator.allocate(SIZE);
        m_start = m_data;
        m_finish = m_start;
    }

    //offset是指m_start不再指向数组的开始，而是加上一个偏移量。这一般是用于第一个buffer
    void allocateWithOffset(size_type offset, const Allocator &allocator)
    {
        m_allocator = allocator;
        m_data = m_allocator.allocate(SIZE);

        m_start = m_data + offset;
        m_finish = m_start;
    }


    size_type left()const
    {
        return (m_data+SIZE) - m_finish;
    }

    //返回fill了多少个元素
    size_type fill_n(size_type n, const T &val)
    {
        size_type fill_num = stl::min(n, left());
        stl::uninitialized_fill_n(m_finish, fill_num, val);
        m_finish += fill_num;

        return fill_num;
    }


    //允许distance(first, last)大于left(), 返回[first, last)中最后一个被copy的下一位置
    template<typename InputIterator>
    InputIterator copy(InputIterator first, InputIterator last)
    {
        return __copy_dispatch(first, last);
    }


    struct tuple
    {
        pointer data;
        pointer start;
        pointer finish;

        tuple()
            : data(0), start(0), finish(0)
        {}
    };

    struct tuple release()
    {
        struct tuple tp;
        tp.data = m_data;
        tp.start = m_start;
        tp.finish = m_finish;

        m_finish = m_start = m_data = 0;

        return tp;
    }


    ~__deque_buffer_construct_helper()
    {
        try
        {
            stl::destroy(m_start, m_finish);
        }
        catch(...)//eat it
        {}

        try
        {
            //当m_start为0时，该调用也合法
            m_allocator.deallocate(m_start, SIZE);
        }
        catch(...)
        {}
    }


private:
    template<typename InputIterator>
    InputIterator __copy_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
    {
        for(; first != last && left()>0; ++m_finish, ++first)
        {
            m_allocator.construct(m_finish, *first);
        }

        return first;
    }


    template<typename ForwardIterator>
    ForwardIterator __copy_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
    {
        typename iterator_traits<ForwardIterator>::difference_type n = stl::distance(first, last);
        size_type copy_n = stl::min<size_type>(n, left());

        ForwardIterator copy_last = stl::next(first, copy_n);
        m_finish = stl::uninitialized_copy(first, copy_last, m_finish);
        return copy_last;
    }


private:
    __deque_buffer_construct_helper(const __deque_buffer_construct_helper& );
    __deque_buffer_construct_helper& operator = (const __deque_buffer_construct_helper &);


private:
    pointer m_data;
    pointer m_start;
    pointer m_finish;//指向未使用的位置
    Allocator m_allocator;
};


template<typename T, typename Allocator, size_t SIZE>
class __deque_2d_buffer_construct_helper
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef size_t size_type;
    typedef pointer* map_pointer;

    typedef Allocator allocator_type;
    typedef __deque_buffer_construct_helper<T, Allocator, SIZE> buffer_construct_helper;
    typedef typename __deque_buffer_construct_helper<T, Allocator, SIZE>::tuple tuple;

public:
    //不同于deque中的map, 这里的map会为每一个元素(即使指针)都分配一个buffer
    __deque_2d_buffer_construct_helper(size_type buffer_num, size_type first_buffer_offset, const Allocator &allocator)
        : m_map(0), m_allocator(allocator)
    {
        if( buffer_num == 0)
            return ;

        m_map = new buffer_construct_helper[buffer_num];

        try
        {
            //第一个buffer需要考虑offset问题
            m_map[0].allocateWithOffset(first_buffer_offset, m_allocator);
            for(size_t i = 1; i < buffer_num; ++i)
            {
                m_map[i].allocate(m_allocator);
            }
        }catch(...)
        {
            delete [] m_map;
            throw;
        }
    }


    size_type fill_n(size_type map_index, size_t n, const T &val)
    {
        return m_map[map_index].fill_n(n, val);
    }


    template<typename InputIterator>
    InputIterator copy(size_type map_index, InputIterator first, InputIterator last)
    {
        return m_map[map_index].copy(first, last);
    }


    tuple release(size_type map_index)
    {
        return m_map[map_index].release();
    }


    ~__deque_2d_buffer_construct_helper()
    {
        try
        {
            delete [] m_map;
        }
        catch(...)//eat it
        {}
    }


private:
    __deque_2d_buffer_construct_helper(const __deque_2d_buffer_construct_helper &);
    __deque_2d_buffer_construct_helper& operator = (const __deque_2d_buffer_construct_helper &);


private:
    buffer_construct_helper* m_map;
    Allocator m_allocator;
};


template<typename T, typename Allocator, size_t SIZE>
class __deque_buffer_destroy_helper
{
public:
    typedef T  value_type;
    typedef T* pointer;

public:
    __deque_buffer_destroy_helper(pointer data, pointer start, pointer finish, const Allocator &allocator)
        : m_data(data), m_start(start), m_finish(finish), m_allocator(allocator)
    {
    }

    ~__deque_buffer_destroy_helper()
    {
        try
        {
            stl::destroy(m_start, m_finish);
        }
        catch(...)//eat it
        {}

        try
        {
            m_allocator.deallocate(m_data, SIZE);
        }
        catch(...)//eat it
        {}
    }


private:
    __deque_buffer_destroy_helper(const __deque_buffer_destroy_helper &);
    __deque_buffer_destroy_helper& operator = (const __deque_buffer_destroy_helper &);

private:
    pointer m_data;
    pointer m_start;
    pointer m_finish;
    Allocator m_allocator;
};



template<typename T, typename Allocator = stl::allocator<T>, size_t BufferSize = 64 >
class deque
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef __DequeIterator<T, T&, T*, BufferSize> iterator;
    typedef __DequeIterator<T, const T&, const T*, BufferSize> const_iterator;
    typedef stl::reverse_iterator<iterator> reverse_iterator;
    typedef stl::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef Allocator allocator_type;

    typedef __deque_buffer_construct_helper<T, Allocator, BufferSize> deque_buffer_construct_helper;
    typedef __deque_buffer_destroy_helper<T, Allocator, BufferSize> deque_buffer_destroy_helper;
    typedef __deque_2d_buffer_construct_helper<T, Allocator, BufferSize> deque_2d_buffer_construct_helper;


private:
    typedef pointer* map_pointer;
    //Allocator是用于分配缓冲区，而map_allocator则用于分配map
    typedef typename Allocator::template rebind<pointer>::other map_allocator;

public:
    iterator begin() { return m_start; }
    iterator end()   { return m_finish;}
    const_iterator begin()const  { return m_start;  }
    const_iterator end()const    { return m_finish; }
    const_iterator cbegin()const { return m_start;  }
    const_iterator cend()const   { return m_finish; }

    reverse_iterator rbegin() { return reverse_iterator(m_start);  }
    reverse_iterator rend()   { return reverse_iterator(m_finish); }
    const_reverse_iterator rbegin()const  { return const_reverse_iterator(m_start); }
    const_reverse_iterator rend()const    { return const_reverse_iterator(m_finish);}
    const_reverse_iterator crbegin()const { return const_reverse_iterator(m_start); }
    const_reverse_iterator crend()const   { return const_reverse_iterator(m_finish);}


    bool empty()const { return begin() == end(); }
    size_type max_size()const { return size_type(-1)/sizeof(T); }
    size_type size()const { return stl::distance(begin(), end()); }
    reference front() { return *begin(); }
    const_reference front()const { return *begin(); }
    reference back()  { return *stl::prev(end()); }
    const_reference back()const { return *stl::prev(end()); }
    allocator_type get_allocator()const { return m_allocator; }


public:
    explicit deque(const Allocator &allocator = Allocator());
    explicit deque(size_type n, const T &val = T(), const Allocator &allocator = Allocator());
    template<typename InputIterator>
    deque(InputIterator first, InputIterator last, const Allocator &allocator = Allocator());

    deque(const deque &de);
    deque& operator = (const deque &de);
    ~deque();

    void swap(deque &x);
    void clear();
    void resize(size_type n, const T &val = T());

private:
    void __deque_fill_n(size_type n, const T &val);
    template<typename InputIterator>
    void __deque_range_fill_dispatch(InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __deque_range_fill_dispatch(InputIterator first, InputIterator last, false_type);

    template<typename InputIterator>
    void __deque_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag);
    template<typename ForwardIterator>
    void __deque_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag);

    void __delete();


public:
    void assign(size_type n, const T &val);
    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);

private:
    void __assign_fill_n(size_type n, const T &val);

    template<typename InputIterator>
    void __assign_range_fill_dispatch(InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __assign_range_fill_dispatch(InputIterator first, InputIterator last, false_type);

    template<typename InputIterator>
    void __assign_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag);
    template<typename ForwardIterator>
    void __assign_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag);


public:
    void push_back(const T &val);
    void push_front(const T &val);
    void pop_back();
    void pop_front();


private:
    void __push_back_aux(const T &val);
    void __push_front_aux(const T &val);
    void __reserve_map_node_at_back(size_type nodes_to_add);
    void __reserve_map_node_at_front(size_type nodes_to_add);
    void __expand_map_node(size_type nodes_to_add);

    void __destroyElementWithoutThrow(pointer p);


public:
    iterator insert(iterator pos, const T &val);
    void insert(iterator pos, size_type n, const T &val);
    template<typename InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last);


private:

    template<typename ForwardIterator1, typename ForwardIterator2>
    void __insert_at_front(size_type n, ForwardIterator1 first, const ForwardIterator2 &last);

    template<typename ForwardIterator1, typename ForwardIterator2>
    void __insert_at_back(size_type n, ForwardIterator1 first, const ForwardIterator2 &last);

    template<typename ForwardIterator1, typename ForwardIterator2>
    void __insert_at_mid(iterator pos, size_type n, ForwardIterator1 first, const ForwardIterator2 &last);

    void __insert_fill_n(iterator pos, size_type n, const T &val);

    template<typename InputIterator>
    void __insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, false_type);

    template<typename InputIterator>
    void __insert_range_dispatch(iterator pos, InputIterator first, InputIterator last, input_iterator_tag);
    template<typename ForwardIterator>
    void __insert_range_dispatch(iterator pos, ForwardIterator first, ForwardIterator last, forward_iterator_tag);

public:
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

private:
    map_pointer m_map;
    size_type m_map_size;
    iterator m_start;
    iterator m_finish;

    Allocator m_allocator;
    map_allocator m_map_allocator;

private:
    static size_t s_min_map_size;
};


template<typename T, typename Allocator, size_t BufferSize>
size_t deque<T, Allocator, BufferSize>::s_min_map_size = 8;


template<typename T, typename Allocator, size_t BufferSize>
inline deque<T, Allocator, BufferSize>::deque(const Allocator &allocator)
        : m_map(0), m_map_size(0), m_allocator(allocator)
{
    __deque_fill_n(0, T());
}


template<typename T, typename Allocator, size_t BufferSize>
inline deque<T, Allocator, BufferSize>::deque(size_type n, const T &val, const Allocator &allocator)
        : m_map(0), m_map_size(0), m_allocator(allocator)
{
    __deque_fill_n(n, val);
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline deque<T, Allocator, BufferSize>::deque(InputIterator first, InputIterator last, const Allocator &allocator)
    : m_map(0), m_map_size(0), m_allocator(allocator)
{
    __deque_range_fill_dispatch(first, last, typename  _type_traits<InputIterator>::is_integer());
}



template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::__deque_range_fill_dispatch(InputIterator first, InputIterator last, true_type)
{
    __deque_fill_n(first, last);
}



template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::__deque_range_fill_dispatch(InputIterator first, InputIterator last, false_type)
{
    __deque_range_dispatch(first, last, iterator_category(first));
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
void deque<T, Allocator, BufferSize>::__deque_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
    __deque_fill_n(0, T());//先构造出map结构

    try
    {
        while( first != last )
        {
            push_back(*first);
            ++first;
        }
    }
    catch(...)
    {
        //一旦发生异常就释放之前已经构造的，确保是构造函数是strong guarantee
        //实际上，如果不释放的话以后也没有办法释放了，因为构造失败，析构函数就不会调用
        __delete();
        throw;
    }
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename ForwardIterator>
void deque<T, Allocator, BufferSize>::__deque_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
{
    difference_type element_num = stl::distance(first, last);
    size_type node_num = element_num/BufferSize + 1;
    size_t map_size = stl::max(s_min_map_size, node_num + 2);


    deque_2d_buffer_construct_helper d2b(node_num, 0, m_allocator);
    for(size_type i = 0; i < node_num; ++i)
    {
        first = d2b.copy(i, first, last);
    }

    //此时first必定等于last

    m_map = m_map_allocator.allocate(map_size);


    //以下操作不会抛异常
    m_map_size = map_size;
    size_t map_start_index = (m_map_size-node_num)/2;
    for(size_type i = 0; i < node_num; ++i)
    {
        typename deque_buffer_construct_helper::tuple tp = d2b.release(i);
        m_map[map_start_index+i] = tp.data;
    }

    m_start.set_node(m_map+map_start_index);
    m_start.m_cur = m_start.m_first;
    m_finish.set_node(m_map + map_start_index + node_num-1);
    m_finish.m_cur = m_finish.m_first + element_num%BufferSize;
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>:: __deque_fill_n(size_type n, const T &val)
{
    size_type node_num = n/BufferSize + 1;
    size_t map_size = stl::max(s_min_map_size, node_num + 2);

    deque_2d_buffer_construct_helper d2d(node_num, 0, m_allocator);
    size_type left_n = n;
    for(size_t i = 0; i < node_num; ++i)
    {
        size_t fill_num = d2d.fill_n(i, left_n, val);
        left_n -= fill_num;
    }

    //left_n肯定等于0

    m_map = m_map_allocator.allocate(map_size);

    //以下操作不会抛异常
    m_map_size = map_size;
    size_t map_start_index = (m_map_size-node_num)/2;
    for(size_type i = 0; i < node_num; ++i)
    {
        typename deque_buffer_construct_helper::tuple tp = d2d.release(i);
        m_map[map_start_index+i] = tp.data;
    }

    m_start.set_node(m_map + map_start_index);
    m_start.m_cur = m_start.m_first;
    m_finish.set_node(m_map + map_start_index + node_num - 1);
    m_finish.m_cur = m_finish.m_first + n%BufferSize;
}


template<typename T, typename Allocator, size_t BufferSize>
inline deque<T, Allocator, BufferSize>::deque(const deque &de)
        : m_map(0), m_map_size(0), m_allocator(de.m_allocator)
{
    __deque_range_dispatch(de.begin(), de.end(), iterator_category(de.begin()));
}



template<typename T, typename Allocator, size_t BufferSize>
deque<T, Allocator, BufferSize>& deque<T, Allocator, BufferSize>::operator = (const deque &de)
{
    if( this != &de )
    {
        assign(de.begin(), de.end());
    }

    return *this;
}


template<typename T, typename Allocator, size_t BufferSize>
inline deque<T, Allocator, BufferSize>::~deque()
{
    __delete();
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__delete()
{
    map_pointer start_node = m_start.m_node;
    map_pointer finish_node = m_finish.m_node;

    {
        //第一个buffer中的前几个元素可能并没有存有数据
        deque_buffer_destroy_helper dd(m_start.m_first, m_start.m_cur, m_start.m_last, m_allocator);
    }

    //上面已经处理的第一个buffer
    for(++start_node; start_node < finish_node; ++start_node)
    {
        //中间这些buffer必定是填满BufferSize个元素的
        deque_buffer_destroy_helper dd(*start_node, *start_node, *start_node + BufferSize, m_allocator);
    }

    if(m_start.m_node != m_finish.m_node)//最后一个buffer也要额外处理
    {
        deque_buffer_destroy_helper dd(m_finish.m_first, m_finish.m_first, m_finish.m_cur, m_allocator);
    }

    try
    {
        //最后释放map本身，里面存的是指针，因此无需调用destroy
        m_map_allocator.deallocate(m_map, m_map_size);
    }
    catch(...)
    {}
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::swap(deque &x)
{
    stl::swap(m_map, x.m_map);
    stl::swap(m_map_size, x.m_map_size);
    m_start.swap(x.m_start);
    m_finish.swap(x.m_finish);
}



template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::clear()
{
    map_pointer reserve_node = m_start.m_node;

    map_pointer start_node = m_start.m_node;
    map_pointer finish_node = m_finish.m_node;


    try
    {
        //第一个buffer中的前几个元素可能并没有存有数据
        //保留第一个buffer
        stl::destroy(m_start.m_cur, m_start.m_last);
    }
    catch(...)
    {}

    //上面已经处理的第一个buffer
    for(++start_node; start_node < finish_node; ++start_node)
    {
        //中间这些buffer必定是填满BufferSize个元素的
        deque_buffer_destroy_helper dd(*start_node, *start_node, *start_node + BufferSize, m_allocator);
    }

    if(m_start.m_node != m_finish.m_node)//最后一个buffer要额外处理
    {
        deque_buffer_destroy_helper dd(m_finish.m_first, m_finish.m_first, m_finish.m_cur, m_allocator);
    }


    m_start.set_node(reserve_node);
    m_start.m_cur = m_start.m_first;
    m_finish.set_node(reserve_node);
    m_finish.m_cur = m_start.m_first;
}



template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::resize(size_type n, const T &val)
{
    if( size() < n )
    {
        insert(end(), n-size(), val);
    }
    else if( size() > n )
    {
        size_type erase_num = size() - n;
        erase(end()-erase_num, end());
    }
}


template<typename T, typename Allocator, size_t BufferSize>
inline void deque<T, Allocator, BufferSize>::assign(size_type n, const T &val)
{
    __assign_fill_n(n, val);
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__assign_fill_n(size_type n, const T &val)
{
    size_type node_num = n/BufferSize + 1;
    size_t map_size = stl::max(s_min_map_size, node_num + 2);

    deque_2d_buffer_construct_helper d2d(node_num, 0, m_allocator);
    size_type left_n = n;
    for(size_t i = 0; i < node_num; ++i)
    {
        size_t fill_num = d2d.fill_n(i, left_n, val);
        left_n -= fill_num;
    }

    //left_n肯定等于0

    map_pointer tmp_map = m_map_allocator.allocate(map_size);

    __delete();//清除当前的值,连同map结构一起清除


    //以下操作不会抛异常
    m_map = tmp_map;
    m_map_size = map_size;
    size_t map_start_index = (m_map_size-node_num)/2;
    for(size_type i = 0; i < node_num; ++i)
    {
        typename deque_buffer_construct_helper::tuple tp = d2d.release(i);
        m_map[map_start_index+i] = tp.data;
    }

    m_start.set_node(m_map + map_start_index);
    m_start.cur = m_start.first;
    m_finish.set_node(m_map + map_start_index + node_num - 1);
    m_finish.cur = m_finish.first + n%BufferSize;
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::assign(InputIterator first, InputIterator last)
{
    __assign_range_fill_dispatch(first, last, typename _type_traits<InputIterator>::is_integer());
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::__assign_range_fill_dispatch(InputIterator first, InputIterator last, true_type)
{
    __assign_fill_n(first, last);
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::__assign_range_fill_dispatch(InputIterator first, InputIterator last, false_type)
{
    __assign_range_dispatch(first, last, iterator_category(first));
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
void deque<T, Allocator, BufferSize>::__assign_range_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
    clear();

    //无需捕抓异常
    while( first != last )
    {
        push_back(*first);
        ++first;
    }
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename ForwardIterator>
void deque<T, Allocator, BufferSize>::__assign_range_dispatch(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
{
    difference_type element_num = stl::distance(first, last);
    size_type node_num = element_num/BufferSize + 1;
    size_t map_size = stl::max(s_min_map_size, node_num + 2);


    deque_2d_buffer_construct_helper d2b(node_num, 0, m_allocator);
    for(size_type i = 0; i < node_num; ++i)
    {
        first = d2b.copy(i, first, last);
    }

    //此时first必定等于last

    map_pointer tmp_map = m_map_allocator.allocate(map_size);

    __delete();//清除当前的值,连同map结构一起清除

    //以下操作不会抛异常
    m_map = tmp_map;
    m_map_size = map_size;
    size_t map_start_index = (m_map_size-node_num)/2;
    for(size_type i = 0; i < node_num; ++i)
    {
        typename deque_buffer_construct_helper::tuple tp = d2b.release(i);
        m_map[map_start_index+i] = tp.data;
    }

    m_start.set_node(m_map+map_start_index);
    m_start.m_cur = m_start.m_first;
    m_finish.set_node(m_map + map_start_index + node_num-1);
    m_finish.m_cur = m_finish.m_first + element_num%BufferSize;
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::push_back(const T &val)
{
    if( m_finish.m_cur != m_finish.m_last-1 )//还有空闲空间
    {
        m_allocator.construct(m_finish.m_cur, val);
        ++m_finish.m_cur;
    }
    else
    {
        //由于m_finish需要指向最后一个元素的下一个位置。因此当最后一个元素
        //位于buffer的最后面时，m_finish应该指向下一个buffer的第一个元素
        __push_back_aux(val);
    }
}



template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__push_back_aux(const T &val)
{
    __reserve_map_node_at_back(1);//确保后面有一个空闲的map node

    deque_buffer_construct_helper db;
    db.allocate(m_allocator);

    //先确保新的buffer分配成功，才构造新的元素
    m_allocator.construct(m_finish.m_cur, val);


    typename deque_buffer_construct_helper::tuple tp = db.release();
    map_pointer new_node = m_finish.m_node + 1;
    *new_node = tp.data;

    m_finish.set_node(new_node);
    m_finish.m_cur = m_finish.m_first;
}



template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__reserve_map_node_at_back(size_type nodes_to_add)
{
    if( m_finish.m_node < m_map + m_map_size-nodes_to_add )//m_map数组最后有空闲的位置
        return ;
    else if( m_start.m_node > m_map+nodes_to_add-1 )//m_map数组前面有空闲的位置, 将数组内容向前移动，腾出空间
    {
        stl::copy(m_start.m_node, m_finish.m_node+nodes_to_add, m_start.m_node - nodes_to_add);

        //只需调整m_start和m_finish的node指向，另外三个指向buffer的指针无需修改
        //因为其还是指向同一个buffer
        m_start.m_node = m_start.m_node   - nodes_to_add;
        m_finish.m_node = m_finish.m_node - nodes_to_add;
    }
    else
    {
        //山穷水尽，此时需要扩展map数组
        __expand_map_node(nodes_to_add);
    }
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__expand_map_node(size_type nodes_to_add)
{
    size_t old_map_size = m_map_size;
    size_t new_map_size = old_map_size + 2*stl::max(old_map_size, nodes_to_add);
    map_pointer new_map = m_map_allocator.allocate(new_map_size);

    size_t map_start_index = (new_map_size-m_map_size)/2;
    stl::uninitialized_copy(m_map, m_map+m_map_size, new_map+map_start_index);


    stl::swap(m_map, new_map);
    stl::swap(m_map_size, new_map_size);

    m_start.m_node = m_map + map_start_index;
    m_finish.m_node = m_map + map_start_index + old_map_size-1;

    m_map_allocator.deallocate(new_map, new_map_size);//释放旧的map 数组
}



template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::push_front(const T &val)
{
    if( m_start.m_cur != m_start.m_first )
    {
        m_allocator.construct(m_start.m_cur-1, val);
        --m_start.m_cur;
    }
    else
    {
        //需要申请一个buffer，才能存放
        __push_front_aux(val);
    }
}



template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__push_front_aux(const T &val)
{
    __reserve_map_node_at_front(1);//确保m_map数组前面有空闲的位置


    //为确保异常安全，先分配新的buffer以及构造新的元素
    deque_buffer_construct_helper db;
    db.allocateWithOffset(BufferSize-1, m_allocator);

    db.fill_n(1, val);


    typename deque_buffer_construct_helper::tuple tp = db.release();
    map_pointer new_node = m_start.m_node - 1;
    *new_node = tp.data;

    m_start.set_node(new_node);
    m_start.m_cur = tp.start;
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__reserve_map_node_at_front(size_type nodes_to_add)
{
    if(m_map < m_start.m_node - nodes_to_add + 1)//m_map数组开始位置有空闲位置
        return ;
    else if( m_finish.m_node < m_map + m_map_size-nodes_to_add )//m_map数组后面有空闲位置，数组内容向后移动，腾出空间
    {
        stl::copy_backward(m_start.m_node, m_finish.m_node, m_finish.m_node+nodes_to_add);

        //只需调整m_start和m_finish的node指向，另外三个指向buffer的指针无需修改
        //因为其还是指向同一个buffer
        m_start.m_node = m_start.m_node   + nodes_to_add;
        m_finish.m_node = m_finish.m_node + nodes_to_add;
    }
    else
    {
        //山穷水尽，此时需要扩展map数组
        __expand_map_node(nodes_to_add);
    }
}




template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::pop_back()
{
    if( empty() )
        return ;

    if( m_finish.m_cur != m_finish.m_first )//不是buffer的第一个元素
    {
        --m_finish.m_cur;//必须先--，因为destroy可能会失败抛异常
        __destroyElementWithoutThrow(m_finish.m_cur);
    }
    else
    {
        //此时需要释放最后一个buffer
        deque_buffer_destroy_helper dd(*m_finish.m_node, m_finish.m_first, m_finish.m_cur, m_allocator);

        m_finish.set_node(m_finish.m_node-1);//指向前一个node
        m_finish.m_cur = m_finish.m_last - 1;
        __destroyElementWithoutThrow(m_finish.m_cur);
    }
}



template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::pop_front()
{
    if( empty() )
        return ;

    if( m_start.m_cur != m_start.m_last - 1)//不是buffer的最后一个元素
    {
        __destroyElementWithoutThrow(m_start.m_cur);
        ++m_start.m_cur;
    }
    else
    {
        //此时第一个buffer的最后一个元素需要释放，接着这个buffer也要被释放
        deque_buffer_destroy_helper dd(*m_start.m_node, m_start.m_cur, m_start.m_last, m_allocator);

        m_start.set_node(m_start.m_node+1);//指向后一个buffer
        m_start.m_cur = m_start.m_first;
    }
}



template<typename T, typename Allocator, size_t BufferSize>
typename deque<T, Allocator, BufferSize>::iterator deque<T, Allocator, BufferSize>::insert(iterator pos, const T &val)
{
    if(pos == begin())
    {
        push_front(val);
        pos = begin();
    }
    else if( pos == end() )
    {
        push_back(val);
        pos = stl::prev(end());
    }
    else
    {
        difference_type elements_before = pos - begin();
        if( elements_before < size()/2 )//插入点之前的元素比较少
        {
            push_front(front());

            //push_front可能会使得pos失效，因此需要重新调整pos，使得其指向原先的位置
            pos = begin() + elements_before + 1;
            stl::copy(stl::next(begin(), 2), pos, stl::next(begin()));
        }
        else
        {
            push_back(back());

            pos = begin() + elements_before;
            stl::copy_backward(pos, stl::prev(end(), 2), stl::prev(end()));
        }
    }

    *pos = val;
    return pos;
}


template<typename T, typename Allocator, size_t BufferSize>
inline void deque<T, Allocator, BufferSize>::insert(iterator pos, size_type n, const T &val)
{
    __insert_fill_n(pos, n, val);
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename ForwardIterator1, typename ForwardIterator2>
void deque<T, Allocator, BufferSize>::__insert_at_mid(iterator pos, size_type n, ForwardIterator1 first, const ForwardIterator2 &last)
{
    difference_type elements_before = pos - begin();
    typename _type_traits<ForwardIterator1>::is_integer bool_type;

    if( elements_before <= size()/2 )//前面的元素较少，通过移动前面的元素完成插入
    {
        if( elements_before >= n )
        {
            __insert_at_front(n, m_start, m_start+n);

            iterator old_start = m_start + n;
            pos = old_start + elements_before;
            iterator insert_start = stl::copy(old_start+n, pos, old_start);

            if( bool_type )//fill
                stl::fill_n(insert_start, n, last);
            else
                stl::copy(first, last, insert_start);
        }
        else
        {
            //此时将elements_before个元素向前移动，仍留有空白
            size_type blank_num = n - elements_before;
            if( bool_type )//fill
            {
                __insert_at_front(blank_num, blank_num, last);
                __insert_at_front(elements_before, m_start + blank_num, m_start+n);//将原先的元素copy到最前面
                stl::fill_n(m_start+n, elements_before, last);
            }
            else
            {
                __insert_at_front(blank_num, first, last);
                first += blank_num;

                __insert_at_front(elements_before, m_start + blank_num, m_start+n);//将原先的元素copy到最前面
                stl::copy(first, last, m_start+n);
            }
        }
    }
    else
    {
        difference_type elements_after = end() - pos;

        if( elements_after >= n )
        {
            __insert_at_back(n, m_finish-n, m_finish);
            iterator old_finish = m_finish - n;
            pos = old_finish - elements_after;
            stl::copy_backward(pos, old_finish-n, old_finish);

            if(bool_type)//fill
                stl::fill_n(pos, n, last);
            else
                stl::copy(first, last, pos);
        }
        else
        {
            //此时将elements_after个元素向后移动，仍留有空白
            size_type blank_num = n - elements_after;
            if(bool_type)//fill
            {
                __insert_at_back(blank_num, blank_num, last);
                __insert_at_back(elements_after, m_finish-n, m_finish-blank_num);//将原来的元素copy到最后

                stl::fill_n(m_finish-n-elements_after, elements_after, last);
            }
            else
            {
                __insert_at_back(blank_num, first, last);
                first += blank_num;

                __insert_at_back(elements_after, m_finish-n, m_finish-blank_num);//将原来的元素copy到最后
                stl::copy(first, last, m_finish-n-elements_after);
            }
        }
    }
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename ForwardIterator1, typename ForwardIterator2>
void deque<T, Allocator, BufferSize>::__insert_at_front(size_type n, ForwardIterator1 first, const ForwardIterator2 &last)
{
    difference_type cur_buffer_reserve_num = m_start.m_cur - m_start.m_first;
    typename _type_traits<ForwardIterator1>::is_integer bool_type;

    if( cur_buffer_reserve_num >= n)//第一个buffer有足够的空闲空间
    {
        if( bool_type )//fill
            stl::uninitialized_fill_n(m_start.m_cur - n, n, last);
        else//range
            stl::uninitialized_copy(first, last, m_start.m_cur-n);

        m_start.m_cur -= n;
    }
    else
    {
        difference_type elements_in_new_buffer = n - cur_buffer_reserve_num;
        size_type need_nodes = (elements_in_new_buffer + 7)/BufferSize;
        __reserve_map_node_at_front(need_nodes);

        size_type first_buffer_offset = elements_in_new_buffer%BufferSize;
        first_buffer_offset = first_buffer_offset == 0 ? 0 : 8 - first_buffer_offset;

        deque_2d_buffer_construct_helper d2b(need_nodes, first_buffer_offset, m_allocator);

        if( bool_type )
        {
            for(size_type i = 0; i < need_nodes; ++i)
                first -= d2b.fill_n(i, first, last);//now, first is n, last is val

            stl::uninitialized_fill_n(m_start.m_first, first, last);
        }
        else
        {
            for(size_type i = 0; i < need_nodes; ++i)
                first = d2b.copy(i, first, last);

            stl::uninitialized_copy(first, last, m_start.m_first);
        }

        //以下操作不会抛异常
        map_pointer new_node = m_start.m_node - need_nodes;
        for(size_type i = 0; i < need_nodes; ++i)
        {
            typename deque_buffer_construct_helper::tuple tp = d2b.release(i);
            *new_node++ = tp.data;
        }

        m_start.set_node(m_start.m_node - need_nodes);
        m_start.m_cur = m_start.m_first + first_buffer_offset;
    }
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename ForwardIterator1, typename ForwardIterator2>
void deque<T, Allocator, BufferSize>::__insert_at_back(size_type n, ForwardIterator1 first, const ForwardIterator2 &last)//insert_fill
{
    difference_type cur_buffer_reserve_num = m_finish.m_last - m_finish.m_cur;
    difference_type elements_in_new_buffer = n - cur_buffer_reserve_num;
    typename _type_traits<ForwardIterator1>::is_integer bool_type;

    if( cur_buffer_reserve_num >= n)//最后一个buffer有足够的空闲空间
    {
        if( bool_type )
            stl::uninitialized_fill_n(m_finish.m_cur, n, last);
        else//range
            stl::uninitialized_copy(first, last, m_finish.m_cur);

        m_finish.m_cur += n;
    }
    else
    {
        size_type need_nodes = (elements_in_new_buffer + 7)/BufferSize;
        __reserve_map_node_at_back(need_nodes);

        deque_2d_buffer_construct_helper d2b(need_nodes, 0, m_allocator);

        if( bool_type )
        {
            first -= cur_buffer_reserve_num;
            for(size_type i = 0; i < need_nodes; ++i)
                first -= d2b.fill_n(i, first, last);//now, first is n, last is val

            //先插入到新的buffer中，然后再m_finish指向的buffer，是因为uninitialized_fill_n
            //抛异常后，d2b里面的值能释放。反之如果uninitialized_fill_n先执行，并且在向d2b插入
            //值时抛异常，uninitialized_fill_n已经插入的将无法释放
            stl::uninitialized_fill_n(m_finish.m_cur, cur_buffer_reserve_num, last);
        }
        else
        {
            ForwardIterator1 mid_last = stl::next(first, cur_buffer_reserve_num);
            ForwardIterator1 mid_first = mid_last;
            for(size_type i = 0; i < need_nodes; ++i)
                mid_first = d2b.copy(i, mid_first, last);

            stl::uninitialized_copy(first, mid_last, m_finish.m_cur);
        }

        //以下操作不会抛异常
        map_pointer new_node = m_finish.m_node + 1;
        for(size_type i = 0; i < need_nodes; ++i)
        {
            typename deque_buffer_construct_helper::tuple tp = d2b.release(i);
            *new_node++ = tp.data;
        }

        m_finish.set_node(m_finish.m_node + need_nodes);
        m_finish.m_cur = m_finish.m_first + elements_in_new_buffer%BufferSize;
    }
}


template<typename T, typename Allocator, size_t BufferSize>
void deque<T, Allocator, BufferSize>::__insert_fill_n(iterator pos, size_type n, const T &val)
{
    if( pos == begin() )
    {
        __insert_at_front(n, n, val);
    }
    else if( pos == end() )
    {
        __insert_at_back(n, n, val);
    }
    else
    {
        __insert_at_mid(pos, n, n, val);
    }
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::insert(iterator pos, InputIterator first, InputIterator last)
{
    __insert_range_fill_dispatch(pos, first, last, _type_traits<InputIterator>::is_integer());
}



template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::__insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, true_type)
{
    __insert_fill_n(pos, first, last);
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
inline void deque<T, Allocator, BufferSize>::__insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, false_type)
{
    __insert_range_dispatch(pos, first, last, iterator_category(first));
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename InputIterator>
void deque<T, Allocator, BufferSize>::__insert_range_dispatch(iterator pos, InputIterator first, InputIterator last, input_iterator_tag)
{
    //无需捕抓异常
    for(; first != last; ++pos, ++first)
    {
        pos = insert(pos, *first);
    }
}


template<typename T, typename Allocator, size_t BufferSize>
template<typename ForwardIterator>
void deque<T, Allocator, BufferSize>::__insert_range_dispatch(iterator pos, ForwardIterator first, ForwardIterator last, forward_iterator_tag)
{
    typename iterator_traits<ForwardIterator>::difference_type n = stl::distance(first, last);

    if( pos == begin() )
    {
        __insert_at_front(n, first, last);
    }
    else if( pos == end() )
    {
        __insert_at_back(n, first, last);
    }
    else
    {
        __insert_at_mid(pos, n, first, last);
    }
}



template<typename T, typename Allocator, size_t BufferSize>
typename deque<T, Allocator, BufferSize>::iterator deque<T, Allocator, BufferSize>::erase(iterator pos)
{
    if( pos == end() )
        return pos;


    //使用copy或者copy_backward直接覆盖被删除的节点
    iterator next = stl::next(pos);

    difference_type num = pos - m_start;
    if( num < size()/2 )//清除点之前的元素较少，消耗更小
    {
        stl::copy_backward(m_start, pos, next);
        pop_front();//第一个元素已经向后覆盖了，出现重复，需要删除
    }
    else
    {
        stl::copy(next, m_finish, pos);
        pop_back();//最后一个元素已经向前覆盖，出现重复，需要删除
    }

    return m_start + num;
}


template<typename T, typename Allocator, size_t BufferSize>
typename deque<T, Allocator, BufferSize>::iterator deque<T, Allocator, BufferSize>::erase(iterator first, iterator last)
{
    //erase有异常安全要求。本函数实现时，destroy和deallocate都不会抛异常，而copy或者copy_backward则可能抛异常

    if( first == begin() && last == end() )//清除整个区间
    {
        clear();
        return m_finish;
    }
    else
    {
        difference_type num = last - first;
        difference_type elements_before = first - m_start;//清除区间前方的元素个数

        if( elements_before < (size()-num)/2 )//前方的元素较少，此时需要向后覆盖
        {
            stl::copy_backward(m_start, first, last);//如果m_start等于first,将不进行任何处理

            iterator new_start = m_start + num;
            try
            {
                stl::destroy(m_start, new_start);
            }
            catch(...)
            {}

            for(map_pointer cur = m_start.m_node; cur < new_start.m_node; ++cur)
            {
                try
                {
                    m_allocator.deallocate(cur, BufferSize);
                }
                catch(...)
                {}
            }

            m_start = new_start;
        }
        else //后方的元素较少，此时需要向前覆盖元素
        {
            stl::copy(last, m_finish, first);

            iterator new_finish = m_finish - num;

            try
            {
                stl::destroy(new_finish, m_finish);
            }
            catch(...)
            {}

            for(map_pointer cur = m_finish.m_node; cur > new_finish.m_node; --cur)
            {
                try
                {
                    m_allocator.deallocate(*cur, BufferSize);
                }
                catch(...)
                {}
            }

            m_finish = new_finish;
        }

        return m_start + elements_before;
    }

}



template<typename T, typename Allocator, size_t BufferSize>
inline bool operator == (const deque<T, Allocator, BufferSize> &lhs, const deque<T, Allocator, BufferSize> &rhs)
{
    return lhs.size()==rhs.size() && stl::equal(lhs.begin(), lhs.end(), rhs.begin());
}


template<typename T, typename Allocator, size_t BufferSize>
inline bool operator != (const deque<T, Allocator, BufferSize> &lhs, const deque<T, Allocator, BufferSize> &rhs)
{
    return !(lhs == rhs);
}


template<typename T, typename Allocator, size_t BufferSize>
inline bool operator < (const deque<T, Allocator, BufferSize> &lhs, const deque<T, Allocator, BufferSize> &rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


template<typename T, typename Allocator, size_t BufferSize>
inline bool operator > (const deque<T, Allocator, BufferSize> &lhs, const deque<T, Allocator, BufferSize> &rhs)
{
    return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}


template<typename T, typename Allocator, size_t BufferSize>
inline bool operator <= (const deque<T, Allocator, BufferSize> &lhs, const deque<T, Allocator, BufferSize> &rhs)
{
    return !(lhs > rhs);
}


template<typename T, typename Allocator, size_t BufferSize>
inline bool operator >= (const deque<T, Allocator, BufferSize> &lhs, const deque<T, Allocator, BufferSize> &rhs)
{
    return !(lhs < rhs);
}


template<typename T, typename Allocator, size_t BufferSize>
inline void swap(deque<T, Allocator, BufferSize> &lhs, deque<T, Allocator, BufferSize> &rhs)
{
    lhs.swap(rhs);
}


}

#endif // STL_DEQUE

