//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef STL_LIST_H
#define STL_LIST_H



namespace stl
{

template<typename T>
 struct __ListNode
{
    __ListNode *prev;
    __ListNode *next;
    T data;
};


//__ListIteator其实就是__ListNode的指针，只是其类化了而已
template<typename T, typename Ref, typename Ptr, typename LinkNode>
struct __ListIterstor
{
    typedef __ListIterstor<T, Ref, Ptr, LinkNode> self;

    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef bidirectional_iterator_tag iterator_category;

    //typedef __ListNode<T>* link_type;
    typedef LinkNode link_type;

    link_type m_node;//指向本iterator所指的list节点


    __ListIterstor(){}
    explicit __ListIterstor(link_type x) : m_node(x){}

    //用于确保一个non-const iterator可以初始化一个const iterator
    template<typename U, typename URef, typename UPtr, typename ULinkNode>
    __ListIterstor(const __ListIterstor<U, URef, UPtr, ULinkNode> &x) : m_node(x.m_node) {}

    //用于确保一个non-const iterator可以赋值给一个const iterator
    template<typename U, typename URef, typename UPtr, typename ULinkNode>
    self& operator = (const __ListIterstor<U, URef, UPtr, ULinkNode> &x)
    {
        m_node = x.m_node;
        return *this;
    }

    self& operator = (link_type x)
    {
        m_node = x;
        return *this;
    }

    //__ListIterstor变量本身是否为const不影响其解引用后的结果
    reference operator *()const
    {
        return m_node->data;
    }

    pointer operator ->()const
    {
        return &(operator*());
    }


    self& operator ++()
    {
        m_node = m_node->next;
        return *this;
    }

    self operator ++(int)
    {
        self tmp(*this);
        ++*this;
        return tmp;
    }

    self& operator --()
    {
        m_node = m_node->prev;
        return *this;
    }

    self operator --(int)
    {
        self tmp(*this);
        --*this;
        return tmp;
    }

    bool operator == (const self& x)const
    {
        return m_node == x.m_node;
    }

    bool operator != (const self& x)const
    {
        return m_node != x.m_node;
    }
};



template<typename T, typename Allocator = stl::allocator<__ListNode<T> > >
class __list_construct_helper
{
public:
    typedef __ListNode<T>* LinkNode;
    typedef __ListNode<T> ListNode;
    typedef size_t size_type;

public:
    __list_construct_helper()
        : m_head(0), m_tail(0)
    {
        m_head = m_tail = allocateNodeAndInit(T());
    }

    //只会复制到最后
    template<typename InputIterator>
    void copy(InputIterator first, InputIterator last)
    {
        while(first != last)
        {
            push_back(allocateNodeAndInit(*first++));
        }
    }

    //只会填充到最后
    void fill_n(size_type n , const T &val)
    {
        while( n-- )
        {
            push_back(allocateNodeAndInit(val));
        }
    }

    void push_back(LinkNode node)
    {
        node->next = m_tail;
        node->prev = m_tail->prev;
        m_tail->prev = node;

        if( node->prev )//有前驱节点，说明m_head和m_tail不是指向同一个节点
            node->prev->next = node;
        else
            m_head = node;
    }

    bool empty()const
    {
        return m_head == m_tail;
    }


    //故意不提供firstNode()和endNode()接口，因为如果提供了，可能会忘记调用release
    stl::pair<LinkNode, LinkNode> release()
    {
        stl::pair<LinkNode, LinkNode> p(0, 0);
        if(!empty())
        {
            p = stl::make_pair(m_head, m_tail->prev);
            m_head = m_tail;//释放链表
            m_tail->prev = 0;

            p.first->prev = p.second->next = 0;
        }

        return p;
    }


    ~__list_construct_helper()
    {
        while( m_head != m_tail )
        {
            deleteNodeNoThrow(m_head);
        }

        deleteNodeNoThrow(m_tail);
    }

private:
    LinkNode allocateNodeAndInit(const T &val)
    {
        LinkNode node = m_allocator.allocate(1);
        node->next = node->prev = NULL;

        try
        {
            stl::construct(&node->data, val);
        }
        catch(...)
        {
            m_allocator.deallocate(node, 1);
            throw;
        }

        return node;
    }


    void deleteNodeNoThrow(LinkNode node)
    {
        try
        {
            m_allocator.destroy(node);
        }
        catch(...)//eat it
        {
        }

        try
        {
            m_allocator.deallocate(node, 1);
        }
        catch(...)//eat it
        {}
    }

private:
    __list_construct_helper(const __list_construct_helper &);
    __list_construct_helper& operator = (const __list_construct_helper &);

private:
    LinkNode m_head;
    LinkNode m_tail;
    Allocator m_allocator;
};

template<typename T, typename Allocator = stl::allocator<T> >
class list
{
private:
    typedef __ListNode<T>* LinkNode;
    typedef const __ListNode<T>* ConstLinkNode;
    typedef __ListNode<T> ListNode;
    typedef typename Allocator::template rebind<ListNode>::other AllocatorType;
    typedef __list_construct_helper<T, AllocatorType> list_construct_helper;

public:
    typedef T  value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Allocator allocator_type;

    typedef __ListIterstor<T, T&, T*, LinkNode> iterator;
    typedef __ListIterstor<T, const T&, const T*, ConstLinkNode> const_iterator;
    typedef stl::reverse_iterator<iterator> reverse_iterator;
    typedef stl::reverse_iterator<const_iterator> const_reverse_iterator;



public:
    iterator begin() { return iterator(m_head); }
    iterator end() { return iterator(m_tail); }
    const_iterator begin()const { return const_iterator(m_head); }
    const_iterator end()const { return const_iterator(m_tail); }
    const_iterator cbegin()const { return const_iterator(m_head); }
    const_iterator cend()const { return const_iterator(m_tail); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin()const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend()const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin()const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend()const { return const_reverse_iterator(begin()); }


    bool empty()const { return begin() == end(); }
    size_type max_size()const { return size_type(-1)/sizeof(T); }
    size_type size()const { return stl::distance(begin(), end()); }
    reference front() { return *begin(); }
    const_reference front()const { return *begin(); }
    reference back() { return *stl::prev(end()); }
    const_reference back()const { return *stl::prev(end()); }
    Allocator get_allocator()const { return Allocator(); }


public:
    explicit list(const Allocator &allocator = Allocator());
    explicit list(size_type n, const T &val = T(), const Allocator &allocator = Allocator());

    template<typename InputIterator>
    list(InputIterator first, InputIterator last, const Allocator &allocator = Allocator());
    list(const list &l);
    list& operator = (const list &l);
    ~list();

    void swap(list &l);
    void clear();
    void resize(size_t n, const T &val = T());

private:
    template<typename InputIterator>
    void __list_range_fill_dispatch(InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __list_range_fill_dispatch(InputIterator first, InputIterator last, false_type);


public:
    void assign(size_type n, const T &val);
    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);

private:
    template<typename InputIterator>
    void __assign_range_fill_dispatch(InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __assign_range_fill_dispatch(InputIterator first, InputIterator last, false_type);


public:
    void push_front(const T &val);
    void push_back(const T &val);
    void pop_front();
    void pop_back();

    iterator insert(iterator pos, const T &val);
    void insert(iterator pos, size_type n, const T &val);
    template<typename InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last);


private:
    template<typename InputIterator>
    void __insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, true_type);
    template<typename InputIterator>
    void __insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, false_type);

    void __insert_fill_n(iterator pos, size_type n, const T &val);
    template<typename InputIterator>
    void __insert_range(iterator pos, InputIterator first, InputIterator last);

public:
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);


public:
    void remove(const T &val);
    template<typename UnaryPredicate>
    void remove_if(UnaryPredicate pred);

    void unique();
    template<typename BinaryPredicate>
    void unique(BinaryPredicate pred);

    void merge(list &x);
    template<typename StrictWeakOrdering>
    void merge(list &x, StrictWeakOrdering comp);

    void reverse();

    void splice(iterator pos, list &x);
    void splice(iterator pos, list &x, iterator i);
    void splice(iterator pos, list &x, iterator first, iterator last);

    void sort();
    template<typename StrictWeakOrdering>
    void sort(StrictWeakOrdering comp);

private:
    LinkNode allocateNodeAndInit(const T &val);
    void initBlankNode();

    void deleteNodeNoThrow(LinkNode node);

private:
    LinkNode m_head;
    LinkNode m_tail;
    AllocatorType m_allocator;
};


template<typename T, typename Allocator>
typename list<T, Allocator>::LinkNode list<T, Allocator>::allocateNodeAndInit(const T &val)
{
    LinkNode node = m_allocator.allocate(1);
    node->next = node->prev = NULL;

    try
    {
        stl::construct(&node->data, val);
    }
    catch(...)
    {
        m_allocator.deallocate(node, 1);
        throw;
    }

    return node;
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::initBlankNode()
{
    m_head = m_tail = allocateNodeAndInit(T());//指向一个空白 Node
}


template<typename T, typename Allocator>
void list<T, Allocator>::deleteNodeNoThrow(LinkNode node)
{
    try
    {
        m_allocator.destroy(node);
    }
    catch(...)//eat it
    {
    }

    try
    {
        m_allocator.deallocate(node, 1);
    }
    catch(...)//eat it
    {}
}

template<typename T, typename Allocator>
list<T, Allocator>::list(const Allocator&)
    : m_head(0), m_tail(0)
{
    initBlankNode();//指向一个空白 Node
}


template<typename T, typename Allocator>
inline list<T, Allocator>::list(size_type n, const T &val, const Allocator&)
        : m_head(0), m_tail(0)
{
    initBlankNode();//指向一个空白 Node
    __insert_fill_n(end(), n, val);
}



template<typename T, typename Allocator>
inline list<T, Allocator>::list(const list &l)
        : m_head(0), m_tail(0)
{
    initBlankNode();//指向一个空白 Node
    __insert_range(end(), l.begin(), l.end());
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline list<T, Allocator>::list(InputIterator first, InputIterator last, const Allocator&)
        : m_head(0), m_tail(0)
{
    initBlankNode();//指向一个空白 Node
    __list_range_fill_dispatch(first, last, typename _type_traits<InputIterator>::is_integer());
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::__list_range_fill_dispatch(InputIterator first, InputIterator last, true_type)
{
    __insert_fill_n(end(), first, last);
}



template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::__list_range_fill_dispatch(InputIterator first, InputIterator last, false_type)
{
    __insert_range(end(), first, last);
}



template<typename T, typename Allocator>
list<T, Allocator>& list<T, Allocator>::operator = (const list &l)
{
    if( this != &l )
    {
        clear();
        __insert_range(end(), l.begin(), l.end());
    }

    return *this;
}


template<typename T, typename Allocator>
list<T, Allocator>::~list()
{
    clear();
    deleteNodeNoThrow(m_tail);
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::swap(list &l)
{
    stl::swap(m_head, l.m_head);
    stl::swap(m_tail, l.m_tail);
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::clear()
{
    erase(begin(), end());
}


template<typename T, typename Allocator>
void list<T, Allocator>::resize(size_t n, const T &val)
{
    size_type old_size = size();

    if( old_size < n)
    {
        __insert_fill_n(end(), n-old_size, val);
    }
    else
    {
        while( old_size > n)
        {
            pop_back();
            --old_size;
        }
    }
}



template<typename T, typename Allocator>
inline void list<T, Allocator>::assign(size_type n, const T &val)
{
    clear();
    __insert_fill_n(end(), n, val);
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::assign(InputIterator first, InputIterator last)
{
    clear();
    __assign_range_fill_dispatch(first, last, typename _type_traits<InputIterator>::is_integer());
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::__assign_range_fill_dispatch(InputIterator first, InputIterator last, true_type)
{
    __insert_fill_n(end(), first, last);
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::__assign_range_fill_dispatch(InputIterator first, InputIterator last, false_type)
{
    __insert_range(end(), first, last);
}



template<typename T, typename Allocator>
inline void list<T, Allocator>::push_front(const T &val)
{
    __insert_fill_n(begin(), 1, val);
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::push_back(const T &val)
{
    __insert_fill_n(end(), 1, val);
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::pop_front()
{
    if(!empty())
    {
        erase(begin());
    }
}


template<typename T, typename Allocator>
void list<T, Allocator>::pop_back()
{
    if(!empty())
    {
        erase(--end());
    }
}


template<typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::insert(iterator pos, const T &val)
{
    __insert_fill_n(pos, 1, val);
    return iterator(pos.m_node->prev);
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::insert(iterator pos, size_type n, const T &val)
{
    __insert_fill_n(pos, n, val);
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::insert(iterator pos, InputIterator first, InputIterator last)
{
    __insert_range_fill_dispatch(pos, first, last, typename _type_traits<InputIterator>::is_integer());
}



template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::__insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, true_type)
{
    __insert_fill_n(pos, first, last);
}


template<typename T, typename Allocator>
template<typename InputIterator>
inline void list<T, Allocator>::__insert_range_fill_dispatch(iterator pos, InputIterator first, InputIterator last, false_type)
{
    __insert_range(pos, first, last);
}


template<typename T, typename Allocator>
void list<T, Allocator>::__insert_fill_n(iterator pos, size_type n, const T &val)
{
    if( n == 0) return ;

    list_construct_helper lc;
    lc.fill_n(n, val);

    stl::pair<LinkNode, LinkNode> p = lc.release();

    LinkNode pos_node = pos.m_node;
    p.second->next = pos_node;
    p.first->prev = pos_node->prev;
    pos_node->prev = p.second;

    if( p.first->prev )//如果有前驱节点
        p.first->prev->next = p.first;

    if(pos_node == m_head)
        m_head = p.first;
}


template<typename T, typename Allocator>
template<typename InputIterator>
void list<T, Allocator>::__insert_range(iterator pos, InputIterator first, InputIterator last)
{
    if(first == last) return ;

    list_construct_helper lc;
    lc.copy(first, last);

    stl::pair<LinkNode, LinkNode> p = lc.release();

    LinkNode pos_node = pos.m_node;
    p.second->next = pos_node;
    p.first->prev = pos_node->prev;
    pos_node->prev = p.second;

    if( p.first->prev )//如果有前驱节点
        p.first->prev->next = p.first;

    if(pos_node == m_head)
        m_head = p.first;
}



template<typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(iterator pos)
{
    if( pos == end() )
        return pos;

    LinkNode pos_node = pos.m_node;
    ++pos;

    if(pos_node == m_head)
        m_head = m_head->next;

    pos_node->next->prev = pos_node->prev;//后驱节点肯定会有

    if( pos_node->prev )
        pos_node->prev->next = pos_node->next;

    deleteNodeNoThrow(pos_node);

    return pos;
}


template<typename T, typename Allocator>
typename list<T, Allocator>::iterator list<T, Allocator>::erase(iterator first, iterator last)
{
    while(first != last)
    {
        erase(first++);
    }

    return last;
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::remove(const T &val)
{
    remove_if(stl::bind2nd(stl::equal_to<T>(), val));
}


template<typename T, typename Allocator>
template<typename UnaryPredicate>
void list<T, Allocator>::remove_if(UnaryPredicate pred)
{
    iterator first = begin();
    iterator last = end();

    while(first != last)
    {
        iterator tmp = first++;
        if(pred(*tmp))
            erase(tmp);
    }
}



template<typename T, typename Allocator>
inline void list<T, Allocator>::unique()
{
    unique(stl::equal_to<T>());
}


template<typename T, typename Allocator>
template<typename BinaryPredicate>
void list<T, Allocator>::unique(BinaryPredicate pred)
{
    if( empty() ) return ;

    iterator first = begin();
    iterator second = ++begin();
    iterator last = end();

    while(second != last)
    {
        if( pred(*first, *second) )
        {
            iterator tmp = second++;
            erase(tmp);
        }
        else
        {
            first = second;
            ++second;
        }
    }
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::merge(list &x)
{
    merge(x, stl::less<T>());
}



template<typename T, typename Allocator>
template<typename StrictWeakOrdering>
void list<T, Allocator>::merge(list &x, StrictWeakOrdering comp)
{
    if(x.empty())
        return ;

    //之所以定义一个和__ListNode相似的结构体，是因为__ListNode里面的data成员需要
    //构造，可能会发生异常。定义一个相似的结构体可以利用头结点的便利
    struct ListNodeSimulate
    {
        LinkNode prev;
        LinkNode next;
    }new_head;

    LinkNode p = reinterpret_cast<LinkNode>(&new_head);

    LinkNode first1 = m_head, first2 = x.m_head;
    LinkNode last1 = m_tail, last2 = x.m_tail;
    while( first1 != last1 && first2 != last2 )
    {
        if(comp(first2->data, first1->data))
        {
            p->next = first2;
            first2->prev = p;
            p = first2;
            first2 = first2->next;
        }
        else
        {
            p->next = first1;
            first1->prev = p;
            p = first1;
            first1 = first1->next;
        }
    }


    if(first2 != last2)
    {
        p->next = first2;
        first2->prev = p;

        //跳到最后一个节点
        p = last2->prev;
        last2->prev = 0;
    }

    //无论最终p是结束于this还是x，其最终都要指向this的tail所在链表
    p->next = first1;
    first1->prev = p;

    x.m_head = x.m_tail;
    x.m_tail->prev = 0;

    m_head = new_head.next;
    m_head->prev = 0;
}


template<typename T, typename Allocator>
void list<T, Allocator>::reverse()
{
    if(empty() || m_head->next == m_tail)
        return ;


    LinkNode p = m_head;
    while( p != m_tail )
    {
        LinkNode tmp = p->next;
        stl::swap(p->prev, p->next);
        p = tmp;
    }


    p = m_tail->prev;
    p->prev = 0;//p指向的节点变成头结点

    m_head->next = m_tail;//m_head指向的节点变成最后一个有数据的节点
    m_tail->prev = m_head;

    m_head = p;
}



template<typename T, typename Allocator>
inline void list<T, Allocator>::splice(iterator pos, list &x)
{
    splice(pos, x, x.begin(), x.end());
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::splice(iterator pos, list &x, iterator i)
{
    splice(pos, x, i, stl::next(i));
}


template<typename T, typename Allocator>
void list<T, Allocator>::splice(iterator pos, list &x, iterator first, iterator last)
{
    if( first == last )
        return ;

    LinkNode first_node = first.m_node;
    LinkNode last_node  = last.m_node;
    LinkNode real_last_node = last_node->prev;

    last_node->prev = first_node->prev;
    if(first_node->prev != 0)//first不是头节点
    {
        first_node->prev->next = last_node;
    }
    else
    {
        x.m_head = last_node;
    }

    //至此，[first, last)已经成功从x中脱离

    LinkNode pos_node = pos.m_node;
    real_last_node->next = pos_node;
    first_node->prev = pos_node->prev;

    if(pos_node->prev != 0)//pos不是头结点
    {
        pos_node->prev->next = first_node;
        pos_node->prev = real_last_node;
    }
    else
    {
        m_head = first_node;
        pos_node->prev = real_last_node;
    }
}


template<typename T, typename Allocator>
inline void list<T, Allocator>::sort()
{
    sort(stl::less<T>());
}


template<typename T, typename Allocator>
template<typename StrictWeakOrdering>
inline void list<T, Allocator>::sort(StrictWeakOrdering comp)
{
    //本质为归并排序.
    //carry从*this链表中偷运一个节点出来(归并排序的最底层),而counter数组的每一个元素代表归并中的每一层。
    //carry偷运的节点与counter[0]进行归并(如果counter[0]没有节点，则carry将偷运的节点放到counter[0])，
    //然后再去偷运一个，进行归并)。归并后，就有两个节点，有资本向counter[1]请求归并(如果counter[1]没有，
    //节点，那么carry将两个节点放到counter[1]中，carry再去偷节点，从counter[0]开始重新积累资本)。归并
    //后，就有4个节点，再向counter[2]请求归并......
    if( empty() || m_head->next == m_tail )
        return ;

    list carry;
    //counter[0]放一个节点，counter[1]放两个节点，counter[2]放四个，counter[3]放八个......
    //64个元素一共可以放2^64 - 1个。
    list counter[64];

    int fill = 0;

    while( !empty() )
    {
        carry.splice(carry.begin(), *this, begin());

        int i = 0;
        while( i<fill && !counter[i].empty())
        {
            carry.merge(counter[i++], comp);
        }

        carry.swap(counter[i]);

        if(i == fill) ++fill;
    }


    for(int i = 0; i < fill; ++i)
    {
        if(!counter[i].empty())
            merge(counter[i], comp);
    }
}



//====================================non member function======================

template<typename T, typename Allocator>
bool operator == (const list<T, Allocator> &lhs, const list<T, Allocator> &rhs)
{
    //之所以不用stl::equals，是因为该函数不能判断size不相同的情况
    typename list<T, Allocator>::const_iterator l_it = lhs.begin(), l_e = lhs.end();
    typename list<T, Allocator>::const_iterator r_it = rhs.begin(), r_e = rhs.end();

    while( l_it != l_e && r_it != r_e )
    {
        if(*l_it != *r_it )
            return false;

        ++l_it;
        ++r_it;
    }

    return l_it == l_e && r_it == r_e;
}



template<typename T, typename Allocator>
inline bool operator != (const list<T, Allocator> &lhs, const list<T, Allocator> &rhs)
{
    return !(lhs == rhs);
}


template<typename T, typename Allocator>
inline bool operator < (const list<T, Allocator> &lhs, const list<T, Allocator> &rhs)
{
    return stl::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


template<typename T, typename Allocator>
inline bool operator > (const list<T, Allocator> &lhs, const list<T, Allocator> &rhs)
{
    return stl::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}


template<typename T, typename Allocator>
inline bool operator <= (const list<T, Allocator> &lhs, const list<T, Allocator> &rhs)
{
    return !(lhs > rhs);
}


template<typename T, typename Allocator>
inline bool operator >= (const list<T, Allocator> &lhs, const list<T, Allocator> &rhs)
{
    return !(lhs < rhs);
}


template<typename T, typename Allocator>
inline void swap(list<T, Allocator> &lhs, list<T, Allocator> &rhs)
{
    lhs.swap(rhs);
}

}

#endif // STL_LIST_H

