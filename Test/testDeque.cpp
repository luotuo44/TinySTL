//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#include"testDeque.h"

#include"../deque"


#include<assert.h>
#include<time.h>
#include<stdlib.h>

#include<string>
#include<vector>
#include<list>
#include<iostream>
#include<iterator>

#include"memory"
#include"algorithm"
#include"iterator"
#include"../vector"
#include"../list"

namespace stl
{

template<typename T>
void testDequeConstructorCase1()
{
    stl::deque<T> deq;
    assert(deq.empty() && deq.size() == 0);
}


template<typename T>
void testDequeConstructorCase2(const T &val)
{
    typename stl::deque<T, stl::allocator<T>, 8>::iterator b , e;

    size_t num = 7;
    stl::deque<T, stl::allocator<T>, 8> deq1(num, val);
    b = deq1.begin(), e = deq1.end();
    assert(!deq1.empty() && b.m_node == e.m_node && b.m_cur+num==e.m_cur && b.m_first==e.m_first);
    assert(deq1.size() == num && stl::count(b, e, val)==static_cast<int>(num) );

    num = 0;
    stl::deque<T, stl::allocator<T>, 8> deq2(num, val);
    assert(deq2.empty() && deq2.size()==num);

    //测试__deque_range_fill_dispatch能够正确分派
    int i_num = 4;
    stl::deque<T, stl::allocator<T>, 8> deq3(i_num, val);
    assert(!deq3.empty());
    assert(deq3.size()==static_cast<size_t>(i_num) && stl::count(deq3.begin(), deq3.end(), val)==i_num);
}


template<typename T>
void testDequeConstructorCase3SubTest(const T &val, size_t num)
{
    stl::deque<T, stl::allocator<T>, 8> deq(num, val);
    typename stl::deque<T, stl::allocator<T>, 8>::iterator b = deq.begin(), e = deq.end();
    assert(!deq.empty() && e-b==static_cast<int>(num));
    assert(deq.size()==num && stl::count(b, e, val)==static_cast<int>(num));

    size_t diff_node = num / 8;
    assert(b.m_node == e.m_node-diff_node);
}


//测试多个buffer的情况
void testDequeConstructorCase3()
{
    testDequeConstructorCase3SubTest<int>(2, 8);
    testDequeConstructorCase3SubTest<double>(2.718281828, 8);
    testDequeConstructorCase3SubTest<std::string>("Deque", 8);

    testDequeConstructorCase3SubTest<int>(2, 9);
    testDequeConstructorCase3SubTest<double>(2.718281828, 12);
    testDequeConstructorCase3SubTest<std::string>("Deque", 15);

    testDequeConstructorCase3SubTest<int>(2, 16);
    testDequeConstructorCase3SubTest<double>(2.718281828, 16);
    testDequeConstructorCase3SubTest<std::string>("Deque", 16);

    testDequeConstructorCase3SubTest<int>(2, 23);
    testDequeConstructorCase3SubTest<double>(2.718281828, 20);
    testDequeConstructorCase3SubTest<std::string>("Deque", 17);

    testDequeConstructorCase3SubTest<int>(2, 24);
    testDequeConstructorCase3SubTest<double>(2.718281828, 24);
    testDequeConstructorCase3SubTest<std::string>("Deque", 24);

    //最小map_pointer size
    testDequeConstructorCase3SubTest<int>(2, 64);
    testDequeConstructorCase3SubTest<double>(2.718281828, 64);
    testDequeConstructorCase3SubTest<std::string>("Deque", 64);

    testDequeConstructorCase3SubTest<int>(2, 65);
    testDequeConstructorCase3SubTest<double>(2.718281828, 66);
    testDequeConstructorCase3SubTest<std::string>("Deque", 65);
    testDequeConstructorCase3SubTest<std::string>("Deque", 63);

    testDequeConstructorCase3SubTest<int>(2, 100);
    testDequeConstructorCase3SubTest<double>(2.718281828, 100);
    testDequeConstructorCase3SubTest<std::string>("Deque", 100);
    testDequeConstructorCase3SubTest<std::string>("Deque", 102);
}


stl::vector<std::string> generateRandomString(size_t n)
{
    srand(time(NULL) + rand());

    const char base[] = "abcdefghijklmnopqrtsuvwxyzABCDEFGHIJKLMNOPQRTSUVWXYZ";
    size_t size = sizeof(base)/sizeof(base[0]) -1;

    stl::vector<std::string> vec;
    vec.reserve(n);

    std::string str;
    for(size_t i = 0; i < n; ++i)
    {
        str.clear();
        size_t len = 1 + rand()%20;
        for(size_t j = 0; j < len; ++j)
        {
            str.push_back(base[rand()%size]);
        }

        vec.push_back(str);
    }

    return vec;
}


std::string generateRandomSplitString(size_t n)
{
    srand(time(NULL) + rand());

    const char base[] = "abcdefghijklmnopqrtsuvwxyzABCDEFGHIJKLMNOPQRTSUVWXYZ!@#$%^&*()_+";
    size_t size = sizeof(base)/sizeof(base[0]);

    std::string str;
    str.reserve(n);

    for(size_t i = 0; i < n; ++i)
    {
        str.push_back(base[rand()%size]);
        str.push_back(' ');
    }

    str.resize(n-1);//erase the last blank

    return str;
}


stl::vector<int> generateRandomInt(size_t n)
{
    srand(time(NULL) + rand());

    stl::vector<int> vec;
    vec.reserve(n);

    for(size_t i = 0; i < n; ++i)
    {
        vec.push_back(rand()%100);
    }

    return vec;
}


template<typename Category>
class DequeSplitString
{
public:

    typedef std::string value_type;
    typedef ptrdiff_t difference_type;
    typedef std::string* pointer;
    typedef std::string& reference;
    typedef Category iterator_category;

public:
    DequeSplitString(const std::string &str, const std::string &dem)
        : m_str(str), m_dem(dem)
    {
        if(str.empty())
            m_last_pos = m_pos = std::string::npos;
        else
        {
            m_last_pos = 0;
            m_pos = m_str.find(m_dem, m_last_pos);
        }
    }

    DequeSplitString()
        : m_str(std::string("")), m_dem(std::string("")),
          m_pos(std::string::npos), m_last_pos(std::string::npos)
    {
    }


    std::string operator * ()const
    {
        return m_str.substr(m_last_pos, m_pos-m_last_pos);
    }


    DequeSplitString& operator ++()
    {
        if(m_pos == std::string::npos)//reach the end
        {
            m_last_pos = m_pos;
            return *this;
        }

        m_last_pos = m_pos + m_dem.size();
        m_pos = m_str.find(m_dem, m_last_pos);

        return *this;
    }


    DequeSplitString operator ++ (int)
    {
        DequeSplitString tmp(*this);
        ++(*this);
        return tmp;
    }

    bool operator == (const DequeSplitString &ss)const
    {
        return m_pos == ss.m_pos && m_last_pos == ss.m_last_pos;
    }


    bool operator != (const DequeSplitString &ss)const
    {
        return !(*this == ss);
    }

private:
    const std::string &m_str;
    const std::string &m_dem;

    std::string::size_type m_pos;
    std::string::size_type m_last_pos;
};



template<typename ForwardIterator>
void testDequeConstructorCase4SubTest(ForwardIterator first, ForwardIterator last)
{
    typedef typename iterator_traits<ForwardIterator>::value_type T;
    stl::deque<T, stl::allocator<T>, 4> deq(first, last);

    assert(stl::distance(first, last) == static_cast<int>(deq.size()) );
    assert(stl::equal(first, last, deq.begin()));
}


void testDequeConstructorCase4()
{
    stl::vector<std::string> vec = generateRandomString(100);
    testDequeConstructorCase4SubTest(vec.begin(), vec.begin());
    testDequeConstructorCase4SubTest(vec.begin(), vec.begin()+1);
    testDequeConstructorCase4SubTest(vec.begin(), vec.begin()+4);
    testDequeConstructorCase4SubTest(vec.begin(), vec.begin()+15);
    testDequeConstructorCase4SubTest(vec.begin(), vec.begin()+70);
    testDequeConstructorCase4SubTest(vec.begin(), vec.end());

    stl::vector<int> vec2 = generateRandomInt(100);
    testDequeConstructorCase4SubTest(vec2.begin(), vec2.begin());
    testDequeConstructorCase4SubTest(vec2.begin(), vec2.begin()+1);
    testDequeConstructorCase4SubTest(vec2.begin(), vec2.begin()+6);
    testDequeConstructorCase4SubTest(vec2.begin(), vec2.begin()+16);
    testDequeConstructorCase4SubTest(vec2.begin(), vec2.begin()+70);
    testDequeConstructorCase4SubTest(vec2.begin(), vec2.end());
}



void testDequeConstructorCase5SubTest(const std::string &str)
{
    stl::deque<std::string, stl::allocator<std::string>, 4> deq(DequeSplitString<stl::input_iterator_tag>(str, " "), DequeSplitString<stl::input_iterator_tag>());
    stl::vector<std::string> vec(DequeSplitString<stl::input_iterator_tag>(str, " "), DequeSplitString<stl::input_iterator_tag>());

    assert(deq.size() == vec.size() && stl::equal(vec.begin(), vec.end(), deq.begin()));
}


void testDequeConstructorCase5()
{
    testDequeConstructorCase5SubTest(generateRandomSplitString(3));
    testDequeConstructorCase5SubTest(generateRandomSplitString(4));
    testDequeConstructorCase5SubTest(generateRandomSplitString(12));
    testDequeConstructorCase5SubTest(generateRandomSplitString(32));
    testDequeConstructorCase5SubTest(generateRandomSplitString(100));
}



void testDequeCopyConstructorCase1()
{
    //复制构造函数的内部实现和range costruct一样，无需过多测试
    stl::deque<std::string> deq(3, "deque");
    stl::deque<std::string> deq_cp(deq);

    assert(deq.size() == deq_cp.size());
    assert(stl::equal(deq.begin(), deq.end(), deq_cp.begin()));


    std::string str[] = {"a", "bb", "ccc", "dddd", "ee", "ff", "gg", "hh", "JJ", "KK"};
    size_t n = sizeof(str)/sizeof(str[0]);

    stl::deque<std::string, stl::allocator<std::string>, 5> deq1(str, str+n);
    stl::deque<std::string, stl::allocator<std::string>, 5> deq1_cp(deq1);

    assert(deq1.size() == deq1_cp.size() && deq1_cp.size()==n);
    assert(stl::equal(str, str+n, deq1.begin()));
    assert(stl::equal(str, str+n, deq1_cp.begin()));
}


void testDequeOperatorAssignCase1()
{
    //多个buffer
    std::string str[] = {"a", "bb", "ccc", "dddd", "ee", "ff", "gg", "hh", "JJ", "KK"};
    size_t n = sizeof(str)/sizeof(str[0]);
    stl::deque<std::string, stl::allocator<std::string>, 4> deq(str, str+n);


    stl::deque<std::string, stl::allocator<std::string>, 4> deq1;
    deq1 = deq;
    assert(deq1.size() == deq.size() && deq1.size() == n);
    assert(stl::equal(str, str+n, deq1.begin()));


    stl::deque<std::string, stl::allocator<std::string>, 4> deq2(2, "Deque");
    deq2 = deq;
    assert(deq2.size() == deq.size() && deq2.size() == n);
    assert(stl::equal(str, str+n, deq2.begin()));


    stl::deque<std::string, stl::allocator<std::string>, 4> deq3(5, "Deque");
    deq3 = deq;
    assert(deq3.size() == deq.size() && deq3.size() == n);
    assert(stl::equal(str, str+n, deq3.begin()));


    //一个buffer
    stl::deque<std::string, stl::allocator<std::string>, 4> dd(str, str+2);
    deq1 = dd;
    assert(deq1.size() == dd.size() && deq1.size()==2);
    assert(stl::equal(str, str+2, deq1.begin()));
}


template<typename T>
void testDequePopFrontCase1SubTest(const T *first, const T *last)
{
    size_t n = last - first;
    stl::deque<T, stl::allocator<T>, 4> deq(first, last);

    while( first != last )
    {
        assert(deq.size()==n && stl::equal(first, last, deq.begin()));
        ++first;
        --n;
        deq.pop_front();
    }
}


void testDequePopFrontCase1()
{
    std::string str[] = {"a", "bb", "ccc", "dddd", "ee", "ff", "gg", "hh", "JJ", "KK"};
    size_t n1 = sizeof(str)/sizeof(str[0]);
    testDequePopFrontCase1SubTest(str, str+n1);//最后一个buffer未占满
    testDequePopFrontCase1SubTest(str, str+8);//刚好两个buffer
    testDequePopFrontCase1SubTest(str, str);
    testDequePopFrontCase1SubTest(str, str+1);
    testDequePopFrontCase1SubTest(str, str+3);
    testDequePopFrontCase1SubTest(str, str+4);//刚好一个buffer


    int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    testDequePopFrontCase1SubTest(a2, a2+n2);//最后一个buffer未占满
    testDequePopFrontCase1SubTest(a2, a2+8);//刚好两个buffer
    testDequePopFrontCase1SubTest(a2, a2);
    testDequePopFrontCase1SubTest(a2, a2+1);
    testDequePopFrontCase1SubTest(a2, a2+3);
    testDequePopFrontCase1SubTest(a2, a2+4);//刚好一个buffer
}


template<typename T>
void testDequePopBackCase1SubTest(const T *first, const T *last, bool need_pop_front)
{
    size_t n = last - first;
    stl::deque<T, stl::allocator<T>, 4> deq(first, last);

    if( first != last && need_pop_front )
    {
        deq.pop_front();
        --n;
        ++first;
    }

    while( first != last )
    {
        assert(deq.size()==n && stl::equal(first, last, deq.begin()));
        --last;
        --n;
        deq.pop_back();
    }
}


void testDequePopBackCase1()
{
    std::string str[] = {"a", "bb", "ccc", "dddd", "ee", "ff", "gg", "hh", "JJ", "KK"};
    size_t n1 = sizeof(str)/sizeof(str[0]);

    testDequePopBackCase1SubTest(str, str+n1, false);
    testDequePopBackCase1SubTest(str, str+n1, true);//使得第一个buffer前面有空闲空间
    testDequePopBackCase1SubTest(str, str+8, false);
    testDequePopBackCase1SubTest(str, str+8, true);

    testDequePopBackCase1SubTest(str, str+4, false);
    testDequePopBackCase1SubTest(str, str+4, true);

    testDequePopBackCase1SubTest(str, str+2, false);
    testDequePopBackCase1SubTest(str, str+2, true);


    int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);

    testDequePopBackCase1SubTest(a2, a2+n2, false);
    testDequePopBackCase1SubTest(a2, a2+n2, true);//使得第一个buffer前面有空闲空间
    testDequePopBackCase1SubTest(a2, a2+8, false);
    testDequePopBackCase1SubTest(a2, a2+8, true);

    testDequePopBackCase1SubTest(a2, a2+4, false);
    testDequePopBackCase1SubTest(a2, a2+4, true);

    testDequePopBackCase1SubTest(a2, a2+2, false);
    testDequePopBackCase1SubTest(a2, a2+2, true);
}






template<typename T>
void testDequePushBackCase1SubTest(const T *arr, size_t n)
{
    stl::deque<T, stl::allocator<T>, 4> deq;

    for(size_t i = 0; i < n; ++i)
    {
        deq.push_back(arr[i]);
        assert(deq.size()==i+1 && stl::equal(arr, arr+i+1, deq.begin()));

        typename stl::deque<T, stl::allocator<T>, 4>::iterator b = deq.begin(), e = deq.end();
        assert(static_cast<size_t>(e.m_node-b.m_node) == deq.size()/4);
    }
}


void testDequePushBackCase1()
{
    stl::vector<std::string> vec = generateRandomString(10);
    assert(vec.size() == 10);
    testDequePushBackCase1SubTest(vec.data(), vec.size());

    stl::vector<std::string> vec1 = generateRandomString(100);
    assert(vec1.size() == 100);
    testDequePushBackCase1SubTest(vec1.data(), vec1.size());

    stl::vector<int> vec2 = generateRandomInt(12);
    testDequePushBackCase1SubTest(vec2.data(), vec2.size());
}


template<typename T>
void testDequePushBackCase2SubTest(const T *arr, size_t n)//开始位置不是buffer的第一个元素
{
    stl::deque<T, stl::allocator<T>, 4> deq(3, arr[0]);
    deq.pop_front();
    deq.pop_front();
    assert(deq.size()==1 && deq.front()==arr[0]);

    for(size_t i = 1; i < n; ++i)
    {
        deq.push_back(arr[i]);
        assert(deq.size()==i+1 && stl::equal(arr, arr+i+1, deq.begin()));
    }
}


void testDequePushBackCase2()//开始位置不是buffer的第一个元素
{
    stl::vector<std::string> vec = generateRandomString(10);
    testDequePushBackCase2SubTest(vec.data(), vec.size());

    stl::vector<std::string> vec1 = generateRandomString(100);
    testDequePushBackCase2SubTest(vec1.data(), vec1.size());

    stl::vector<int> vec2 = generateRandomInt(12);
    testDequePushBackCase2SubTest(vec2.data(), vec2.size());

    stl::vector<int> vec3 = generateRandomInt(100);
    testDequePushBackCase2SubTest(vec3.data(), vec3.size());
}


template<typename T>
void testDequePushFrontCase1SubTest(const T *arr, size_t n)
{
    stl::deque<T, stl::allocator<T>, 4> deq;

    for(size_t i = n; i-- > 0; )
    {
        deq.push_front(arr[i]);
        assert(deq.size()==n-i && stl::equal(arr+i, arr+n, deq.begin()));

        typename stl::deque<T, stl::allocator<T>, 4>::iterator b = deq.begin(), e = deq.end();
        assert(static_cast<size_t>(e.m_node-b.m_node) == (3+deq.size())/4);
    }
}


void testDequePushFrontCase1()
{
    stl::vector<std::string> vec = generateRandomString(10);
    testDequePushFrontCase1SubTest(vec.data(), vec.size());

    stl::vector<std::string> vec1 = generateRandomString(100);
    testDequePushFrontCase1SubTest(vec1.data(), vec1.size());



    stl::vector<int> vec2 = generateRandomInt(12);
    testDequePushFrontCase1SubTest(vec2.data(), vec2.size());

    stl::vector<int> vec3 = generateRandomInt(100);
    testDequePushFrontCase1SubTest(vec3.data(), vec3.size());
}


template<typename T>
void testDequePushFrontCase2SubTest(const T *arr, size_t n)//结束位置不是buffer的第一个元素
{
    if( n == 0 )  return ;

    stl::deque<T, stl::allocator<T>, 4> deq(3, arr[n-1]);
    deq.pop_front();
    deq.pop_front();
    assert(deq.size()==1 && deq.front()==arr[n-1]);


    for(size_t i = n-1; i-- > 0; )
    {
        deq.push_front(arr[i]);
        assert(deq.size()==n-i && stl::equal(arr+i, arr+n, deq.begin()));
    }
}


void testDequePushFrontCase2()//结束位置不是buffer的第一个元素
{
    stl::vector<std::string> vec = generateRandomString(10);
    testDequePushFrontCase2SubTest(vec.data(), vec.size());

    stl::vector<std::string> vec1 = generateRandomString(100);
    testDequePushFrontCase2SubTest(vec1.data(), vec1.size());


    stl::vector<int> vec2 = generateRandomInt(12);
    testDequePushFrontCase2SubTest(vec2.data(), vec2.size());

    stl::vector<int> vec3 = generateRandomInt(100);
    testDequePushFrontCase2SubTest(vec3.data(), vec3.size());
}




void testDequeSwapCase1()
{
    stl::deque<std::string> deq1;
    stl::deque<std::string> deq2;

    deq1.swap(deq2);
    assert(deq1.empty() && deq2.empty());

    deq1.push_back("deque");
    deq1.swap(deq2);
    assert(deq1.empty() && deq2.size()==1 && deq2.front()=="deque");


    deq1.push_back("C++");
    deq1.swap(deq2);
    assert(deq1.size()==1 && deq1.front()=="deque" && deq2.size()==1 && deq2.back()=="C++");

    //内部实现是直接交换指针，无需过多测试
}


void testDequeClearCase1()
{
    stl::deque<std::string> deq;
    deq.clear();
    assert(deq.empty());

    //测试只有一个buffer的情况
    stl::vector<std::string> vec = generateRandomString(10);
    stl::deque<std::string> deq1(vec.begin(), vec.end());
    deq1.clear();
    assert(deq1.empty());

    stl::deque<std::string> deq2(vec.begin(), vec.end());
    deq2.pop_front();//开始位置不是第一个元素
    deq2.clear();
    assert(deq2.empty());


    //测试多个buffer的情况
    stl::deque<std::string, stl::allocator<std::string>, 4> deq3(vec.begin(), vec.end());
    deq3.clear();
    assert(deq3.empty());

    stl::deque<std::string, stl::allocator<std::string>, 4> deq4(vec.begin(), vec.end());
    deq4.pop_front();
    deq4.pop_front();
    deq4.clear();
    assert(deq4.empty());


    stl::deque<std::string, stl::allocator<std::string>, 4> deq5(vec.begin(), vec.end());
    deq5.pop_back();
    deq5.pop_back();
    assert(deq5.end().m_cur == deq5.end().m_first);//测试end指向最后一个buffer的第一个元素
    deq5.clear();
    assert(deq5.empty());
}


void testDequeBeginEndCase1()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::deque<double> deq1(d1, d1+n1);
    *deq1.begin() = 6.66666;
    assert(*deq1.begin() == 6.66666);
    *(stl::prev(deq1.end())) = 7.77777;
    assert(*(stl::prev(deq1.end())) == 7.77777);

    const stl::deque<double> &deq1_ref = deq1;
    assert(*deq1_ref.begin() == deq1.front());//begin()const
    assert(*(stl::prev(deq1.end())) == deq1.back());//end()const


    //*deq1.cbegin() = 6.66666; //无法编译通过
    //*(stl::prev(deq1.cend())) = 7.77777; //无法编译通过
    //*deq1_ref.begin() = 6.66666; //无法编译通过
    //*(stl::prev(deq1_ref.end())) = 7.77777; //无法编译通过

    //iterator 可以 初始化/赋值给 const iterator
    stl::deque<double>::const_iterator const_it = deq1.begin();
    const_it = deq1.end();
    const_it = deq1.cbegin();
    const_it = deq1.cend();

    //测试const iterator
    //stl::deque<double>::iterator non_const_it = deq1.cbegin();//无法编译通过
    //stl::deque<double>::iterator non_const_it = deq1.cend();//无法编译通过
    //stl::deque<double>::iterator non_const_it = deq1_ref.begin();//无法编译通过
    //stl::deque<double>::iterator non_const_it = deq1_ref.end();//无法编译通过
}


void testDequeBeginEndCase2()
{
    int d1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::deque<int, stl::allocator<int>, 4> deq1(d1, d1+n1);
    std::vector<int> vec1(d1, d1+n1);

    assert(vec1.size() == deq1.size());
    assert(stl::equal(deq1.rbegin(), deq1.rend(), vec1.rbegin()));
    assert(stl::equal(deq1.crbegin(), deq1.crend(), vec1.rbegin()));

    stl::deque<int, stl::allocator<int>, 4>::reverse_iterator non_const_it = deq1.rbegin();
    non_const_it = deq1.rend();

    stl::deque<int, stl::allocator<int>, 4>::const_reverse_iterator const_it = deq1.rbegin();
    const_it = deq1.rend();

    //测试const reverse itereator
    //non_const_it = deq1.crbegin();//无法编译通过
    //non_const_it = deq1.crend();//无法编译通过

    deq1.assign(d1, d1+1);
    assert(stl::equal(deq1.rbegin(), deq1.rend(), d1));
}


void testDequeBeginEndCase3()//测试不同BufferSize的iterator不能相互赋值
{
    stl::deque<int, stl::allocator<int>, 4> deq1;
    deq1.push_back(1);

    //stl::deque<int, stl::allocator<int>, 8>::iterator it = deq1.begin();//无法编译通过
    //stl::deque<int, stl::allocator<int>, 8>::const_iterator it = deq1.cbegin();//无法编译通过
    //stl::deque<int, stl::allocator<int>, 8>::reverse_iterator it = deq1.rbegin();//无法编译通过
}


template<typename T>
void testDequeSizeCase1(const T &val)
{
    stl::deque<T> deq1;
    assert(deq1.empty() && deq1.size()==0);

    stl::deque<T> deq2(9, val);
    assert(!deq2.empty() && deq2.size()==9);

    stl::deque<T> deq3(&val, &val+1);
    assert(!deq3.empty() && deq3.size()==1);
}


void testDequeFrontBackCase1()
{
    stl::deque<int> deq1(1, 4);
    assert(deq1.size()==1 && deq1.front()==4 && deq1.back()==4);
    deq1.front() = 5;
    assert(deq1.size()==1 && deq1.front()==5 && deq1.back()==5);
    deq1.back() = 6;
    assert(deq1.size()==1 && deq1.front()==6 && deq1.back()==6);

    const stl::deque<int> &deq1_ref = deq1;
    assert(deq1_ref.front()==6 && deq1_ref.back()==6);
    //deq1_ref.front() = 7;//无法编译通过
    //deq1_ref.back() = 8;//无法编译通过



    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::deque<double> deq2(d1, d1+n1);
    assert(deq2.size()==n1 && deq2.front()==d1[0] && deq2.back()==d1[n1-1]);
    deq2.front() = 1.25;
    assert(deq2.front()==1.25 && deq2.back()==d1[n1-1]);
}



template<typename T>
void testDequeRandomAccessCase1SubTest(const T *arr, size_t n)
{
    stl::deque<T, stl::allocator<T>, 4> deq(arr, arr+n);

    for(size_t i = 0; i < n; ++i)
    {
        assert(deq[i] == arr[i]);
    }


    stl::deque<T, stl::allocator<T>, 4> deq1(arr, arr+n);
    deq1.pop_front();
    for(size_t i = 0; i < n-1; ++i)
    {
        assert(deq1[i] == arr[i+1]);
    }
}


void testDequeRandomAccessCase1()
{
    stl::vector<std::string> vec = generateRandomString(4);
    testDequeRandomAccessCase1SubTest(vec.data(), vec.size());

    stl::vector<std::string> vec1 = generateRandomString(100);
    testDequeRandomAccessCase1SubTest(vec1.data(), vec.size());


    stl::vector<int> vec2 = generateRandomInt(10);
    testDequeRandomAccessCase1SubTest(vec2.data(), vec2.size());

    stl::vector<int> vec3 = generateRandomInt(100);
    testDequeRandomAccessCase1SubTest(vec3.data(), vec3.size());
}



template<typename T>
void testDequeAssignCase1SubTest(size_t n, const T &old_val, const T &new_val)
{
    stl::deque<T, stl::allocator<T>, 4> deq;
    deq.assign(n/2, old_val);
    assert(deq.size() == n/2 && stl::count(deq.begin(), deq.end(), old_val)==static_cast<int>(n/2) );

    deq.assign(4, new_val);//一个buffer
    assert(deq.size()==4 && stl::count(deq.begin(), deq.end(), new_val) == 4);

    deq.assign(n, old_val);//多个buffer
    assert(deq.size()==n && stl::count(deq.begin(), deq.end(), old_val)==static_cast<int>(n));


    int num = 2;
    deq.assign(num, new_val);
    assert(deq.size()==2 && stl::count(deq.begin(), deq.end(), new_val)==2);

    deq.assign(0, old_val);
    assert(deq.empty());
}


void testDequeAssignCase1()//test assign(size_type n, const T &val)
{
    testDequeAssignCase1SubTest(10, 2, 4);
    testDequeAssignCase1SubTest(100, 1, 5);

    testDequeAssignCase1SubTest<std::string>(12, "deque", "DEQUE");
    testDequeAssignCase1SubTest<std::string>(103, "deque", "DEQUE");
}



void testDequeAssignCase2()//test assign(InputIterator first, InputIterator last)
{
    typedef DequeSplitString<stl::input_iterator_tag> DS;
    stl::deque<std::string, stl::allocator<std::string>, 4> deq;
    stl::vector<std::string> vec;

    std::string str = generateRandomSplitString(3);
    deq.assign(DS(str, " "), DS());
    vec.assign(DS(str, " "), DS());
    assert(deq.size() == vec.size() && stl::equal(deq.begin(), deq.end(), vec.begin()));


    str = generateRandomSplitString(100);
    deq.assign(DS(str, " "), DS());
    vec.assign(DS(str, " "), DS());
    assert(deq.size() == vec.size() && stl::equal(deq.begin(), deq.end(), vec.begin()));

    str = generateRandomSplitString(12);
    deq.assign(DS(str, " "), DS());
    vec.assign(DS(str, " "), DS());
    assert(deq.size() == vec.size() && stl::equal(deq.begin(), deq.end(), vec.begin()));


    str = generateRandomSplitString(2);
    deq.assign(DS(str, " "), DS());
    vec.assign(DS(str, " "), DS());
    assert(deq.size() == vec.size() && stl::equal(deq.begin(), deq.end(), vec.begin()));


    deq.assign(DS(), DS());
    assert(deq.empty());
}



void testDequeAssignCase3()//test assgin(ForwardIterator first, ForwardIterator last)
{
    stl::deque<std::string, stl::allocator<std::string>, 4> deq;

    stl::vector<std::string> vec = generateRandomString(3);
    deq.assign(vec.begin(), vec.end());
    assert(deq.size()==vec.size() && stl::equal(vec.begin(), vec.end(), deq.begin()));


    vec = generateRandomString(20);
    deq.assign(vec.begin(), vec.end());
    assert(deq.size()==vec.size() && stl::equal(vec.begin(), vec.end(), deq.begin()));


    vec = generateRandomString(100);
    deq.assign(vec.begin(), vec.end());
    assert(deq.size()==vec.size() && stl::equal(vec.begin(), vec.end(), deq.begin()));


    vec = generateRandomString(3);
    deq.assign(vec.begin(), vec.end());
    assert(deq.size()==vec.size() && stl::equal(vec.begin(), vec.end(), deq.begin()));

    deq.assign(vec.begin(), vec.begin());
    assert(deq.empty());
}



template<typename T>
void testDequeInsertCase1SubTest(const stl::vector<T> &vec)
{
    stl::deque<T, stl::allocator<T>, 4> deq;
    typename stl::deque<T, stl::allocator<T>, 4>::iterator it;
    stl::vector<T> vv;
    typename stl::vector<T>::iterator iter;


    deq.assign(vec.begin(), vec.begin()+20);
    vv.assign(vec.begin(), vec.begin()+20);

    it = deq.begin() + 17;
    iter = vv.begin() + 17;

    for(size_t i = 20; i < vec.size(); ++i)
    {
        it = deq.insert(it, vec[i]);
        iter = vv.insert(iter, vec[i]);

        assert(deq.size() == vv.size());
        assert(stl::equal(vv.begin(), vv.end(), deq.begin()));
    }



    deq.clear();
    vv.clear();
    deq.assign(vec.begin(), vec.begin()+22);
    deq.pop_front();//使得第一个buffer的位置不是从第一个元素开始
    vv.assign(vec.begin()+1, vec.begin()+22);

    it = deq.begin() + 14;
    iter = vv.begin()+ 14;
    for(size_t i = 20; i < vec.size(); ++i)
    {
        it = deq.insert(it, vec[i]);
        iter = vv.insert(iter, vec[i]);

        assert(deq.size() == vv.size());
        assert(stl::equal(vv.begin(), vv.end(), deq.begin()));
    }
}


void testDequeInsertCase1()//test  iterator insert(iterator pos, const T &val)
{
    stl::deque<std::string, stl::allocator<std::string>, 4> deq;
    stl::deque<std::string, stl::allocator<std::string>, 4>::iterator it = deq.begin();
    stl::vector<std::string> vec = generateRandomString(100);

    for(size_t i = 0; i < vec.size(); ++i)
    {
        it = deq.insert(it, vec[i]);//insert(begin(), vec[i])
        assert(deq.size() == i+1 && stl::equal(deq.rbegin(), deq.rend(), vec.begin()));
    }


    deq.clear();
    assert(deq.empty());
    it = deq.end();
    for(size_t i = 0; i < vec.size(); ++i)
    {
        it = deq.insert(it, vec[i]);//insert(end(), vec[i])
        ++it;

        assert(deq.size() == i+1 && stl::equal(deq.begin(), deq.end(), vec.begin()));
    }


    testDequeInsertCase1SubTest(generateRandomInt(100));
    testDequeInsertCase1SubTest(generateRandomString(100));
}



template<typename T>
void testDequeInsertCase2(const T *arr, size_t num)//void insert(iterator pos, size_type n, const T &val) 插入尾部
{
    assert(num >= 10);

    stl::deque<T, stl::allocator<T>, 4> deq(1, arr[0]);
    stl::vector<T> vv(1, arr[0]);

    deq.insert(deq.end(), 2, arr[1]);//最后一个buffer的空余空间足够
    vv.insert(vv.end(), 2, arr[1]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    deq.insert(deq.end(), 2, arr[2]);//插入长度小于原始长度
    vv.insert(vv.end(), 2, arr[2]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    deq.insert(deq.end(), 4, arr[3]);
    vv.insert(vv.end(), 4, arr[3]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    assert(deq.size() == 9);
    deq.pop_front();//第一个buffer的开始位置不是第一个元素
    vv.erase(vv.begin());
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    deq.insert(deq.end(), 2, arr[4]);//不跨buffer
    vv.insert(vv.end(), 2, arr[4]);

    deq.insert(deq.end(), 6, arr[5]);//跨buffer
    vv.insert(vv.end(), 6, arr[5]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    deq.insert(deq.end(), 8, arr[6]);//map的后端没有足够的node，但前端够
    vv.insert(vv.end(), 8, arr[6]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    deq.insert(deq.end(), 20, arr[7]);//插入的长度大于已有长度
    vv.insert(vv.end(), 20, arr[7]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    deq.insert(deq.end(), 400, arr[8]);//换map_node
    vv.insert(vv.end(), 400, arr[8]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    size_t n = 2;
    deq.insert(deq.end(), n, arr[9]);//上面的insert都需要调用__insert_range_fill_dispatch进行分派
    vv.insert(vv.end(), n, arr[9]);
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
}



template<typename T>
void testDequeInsertCase3(const T *arr, size_t num)//void insert(iterator pos, size_type n, const T &val) 插入头部
{
    assert(num >= 10);

    stl::deque<T, stl::allocator<T>, 4> deq(4, arr[0]);
    stl::list<T> li(4, arr[0]);

    deq.pop_front(); deq.pop_front();
    li.pop_front(); li.pop_front();
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));

    deq.insert(deq.begin(), 1, arr[1]);//同一个buffer，小于原有元素
    li.insert(li.begin(), 1, arr[1]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));

    deq.pop_front(); deq.pop_back();
    li.pop_front(); li.pop_front();
    assert(deq.size()==1);

    deq.insert(deq.begin(), 2, arr[2]);//同一个buffer，多于原有元素
    li.insert(li.begin(), 2, arr[2]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));

    assert(deq.size()==3);
    deq.insert(deq.begin(), 2, arr[3]);//跨buffer，但小于原有元素
    li.insert(li.begin(), 2, arr[3]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    assert(deq.size()==5);
    deq.insert(deq.begin(), 6, arr[4]);//跨buffer，多于原有元素
    li.insert(li.begin(), 6, arr[4]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.insert(deq.begin(), 8, arr[5]);//map的前端不够node，但后端足够空闲的node
    li.insert(li.begin(), 8, arr[5]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.insert(deq.begin(), 400, arr[6]);//前后端都不够node，需要重新分配
    li.insert(li.begin(), 400, arr[6]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
}


template<typename T>
void testDequeInsertCase4(const T *arr, size_t num)//void insert(iterator pos, size_type n, const T &val) 插入中间
{
    assert( num >= 10);

    stl::deque<T, stl::allocator<T>, 4> deq(4, arr[0]);
    stl::list<T> li(4, arr[0]);

    //移动插入点前面的元素，并且移动的元素个数小于插入的个数
    deq.insert(deq.begin()+1, 3, arr[1]);
    li.insert(stl::next(li.begin()), 3, arr[1]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    //移动插入点前面的元素，但移动的元素个数大于插入的个数
    deq.insert(deq.begin()+3, 2, arr[2]);
    li.insert(stl::next(li.begin(), 3), 2, arr[2]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    assert(deq.size() == 9);
    //移动插入点后面的元素，并且移动的元素个数小于插入的个数
    deq.insert(deq.end()-2, 3, arr[3]);
    li.insert(stl::prev(li.end(), 2), 3, arr[3]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    //移动插入点后面的元素，但移动的元素个数大于插入的个数
    deq.insert(deq.end()-4, 2, arr[4]);
    li.insert(stl::prev(li.end(), 4), 2, arr[4]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    //在前端插入大量元素
    deq.insert(deq.begin()+2, 80, arr[5]);
    li.insert(stl::next(li.begin(), 2), 80, arr[5]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    //在后端插入大量元素
    deq.insert(deq.end()-5, 400, arr[6]);
    li.insert(stl::prev(li.end(), 5), 400, arr[6]);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
}



//insert(iterator pos, InputIterator first, InputIterator last)
void testDequeInsertCase5()
{
    typedef DequeSplitString<stl::input_iterator_tag> DS;
    typedef std::string T;
    stl::deque<T, stl::allocator<T>, 4> deq(4, "Deque");
    stl::list<T> li(4, "Deque");

    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));

    //后面的元素少
    std::string split_str = generateRandomSplitString(2);
    deq.insert(deq.end()-2, DS(split_str, " "), DS());
    li.insert(stl::prev(li.end(), 2), DS(split_str, " "), DS());
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    //后面的元素少
    split_str = generateRandomSplitString(10);
    deq.insert(deq.begin()+2, DS(split_str, " "), DS());
    li.insert(stl::next(li.begin(), 2), DS(split_str, " "), DS());
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    split_str = generateRandomSplitString(5);
    deq.insert(deq.begin(), DS(split_str, " "), DS());
    li.insert(li.begin(), DS(split_str, " "), DS());
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    split_str = generateRandomSplitString(5);
    deq.insert(deq.end(), DS(split_str, " "), DS());
    li.insert(li.end(), DS(split_str, " "), DS());
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
}


//insert(iterator, ForwardIterator last, ForwardIterator last)//插入尾部
template<typename ForwardIterator>
void testDequeInsertCase6(ForwardIterator first, ForwardIterator last)
{
    assert(stl::distance(first, last) >= 500);

    typedef typename iterator_traits<ForwardIterator>::value_type T;
    stl::deque<T, stl::allocator<T>, 4> deq(1, *first);
    stl::vector<T> vv(1, *first++);


    deq.insert(deq.end(), first, stl::next(first, 2));//最后一个buffer的空余空间足够
    vv.insert(vv.end(), first, stl::next(first, 2));
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
    stl::advance(first, 2);


    deq.insert(deq.end(), first, stl::next(first, 2));//插入长度小于原始长度
    vv.insert(vv.end(), first, stl::next(first, 2));
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
    stl::advance(first, 2);


    deq.insert(deq.end(), first, stl::next(first, 4));
    vv.insert(vv.end(), first, stl::next(first, 4));
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
    stl::advance(first, 4);


    assert(deq.size() == 9);
    deq.pop_front();//第一个buffer的开始位置不是第一个元素
    vv.erase(vv.begin());
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    deq.insert(deq.end(), first, stl::next(first, 2));//不跨buffer
    vv.insert(vv.end(), first, stl::next(first, 2));
    stl::advance(first, 2);


    deq.insert(deq.end(), first, stl::next(first, 6));//跨buffer
    vv.insert(vv.end(), first, stl::next(first, 6));
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
    stl::advance(first, 6);


    deq.insert(deq.end(), first, stl::next(first, 8));//map的后端没有足够的node，但前端够
    vv.insert(vv.end(), first, stl::next(first, 8));
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
    stl::advance(first, 8);


    deq.insert(deq.end(), first, stl::next(first, 20));//插入的长度大于已有长度
    vv.insert(vv.end(), first, stl::next(first, 20));
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
    stl::advance(first, 20);

    deq.insert(deq.end(), first, stl::next(first, 400));//换map_node
    vv.insert(vv.end(), first, stl::next(first, 400));
    assert(deq.size()==vv.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));
}



//insert(iterator, ForwardIterator last, ForwardIterator last)//插入头部
template<typename ForwardIterator>
void testDequeInsertCase7(ForwardIterator first, ForwardIterator last)
{
    assert(stl::distance(first, last) >= 500);

    typedef typename iterator_traits<ForwardIterator>::value_type T;

    stl::deque<T, stl::allocator<T>, 4> deq(4, *first);
    stl::list<T> li(4, *first++);

    deq.pop_front(); deq.pop_front();
    li.pop_front(); li.pop_front();
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.insert(deq.begin(), first, stl::next(first));//同一个buffer，小于原有元素
    li.insert(li.begin(), first, stl::next(first));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 1);


    deq.pop_front(); deq.pop_back();
    li.pop_front(); li.pop_front();
    assert(deq.size()==1);


    deq.insert(deq.begin(), first, stl::next(first, 2));//同一个buffer，多于原有元素
    li.insert(li.begin(), first, stl::next(first, 2));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 2);


    assert(deq.size()==3);
    deq.insert(deq.begin(), first, stl::next(first, 2));//跨buffer，但小于原有元素
    li.insert(li.begin(), first, stl::next(first, 2));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 2);


    assert(deq.size()==5);
    deq.insert(deq.begin(), first, stl::next(first, 6));//跨buffer，多于原有元素
    li.insert(li.begin(), first, stl::next(first, 6));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 6);


    deq.insert(deq.begin(), first, stl::next(first, 8));//map的前端不够node，但后端足够空闲的node
    li.insert(li.begin(), first, stl::next(first, 8));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 8);

    deq.insert(deq.begin(), first, stl::next(first, 400));//前后端都不够node，需要重新分配
    li.insert(li.begin(), first, stl::next(first, 400));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
}



//insert(iterator, ForwardIterator last, ForwardIterator last)//插入中间
template<typename ForwardIterator>
void testDequeInsertCase8(ForwardIterator first, ForwardIterator last)
{
    assert(stl::distance(first, last) >= 500);
    typedef typename iterator_traits<ForwardIterator>::value_type T;

    stl::deque<T, stl::allocator<T>, 4> deq(4, *first);
    stl::list<T> li(4, *first++);
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    //移动插入点前面的元素，并且移动的元素个数小于插入的个数
    deq.insert(deq.begin()+1, first, stl::next(first, 3));
    li.insert(stl::next(li.begin()), first, stl::next(first, 3));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 3);


    //移动插入点前面的元素，但移动的元素个数大于插入的个数
    deq.insert(deq.begin()+3, first, stl::next(first, 2));
    li.insert(stl::next(li.begin(), 3), first, stl::next(first, 2));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 2);


    assert(deq.size() == 9);
    //移动插入点后面的元素，并且移动的元素个数小于插入的个数
    deq.insert(deq.end()-2, first, stl::next(first, 3));
    li.insert(stl::prev(li.end(), 2), first, stl::next(first, 3));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 3);


    //移动插入点后面的元素，但移动的元素个数大于插入的个数
    deq.insert(deq.end()-4, first, stl::next(first, 2));
    li.insert(stl::prev(li.end(), 4), first, stl::next(first, 2));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 2);


    //在前端插入大量元素
    deq.insert(deq.begin()+2, first, stl::next(first, 80));
    li.insert(stl::next(li.begin(), 2), first, stl::next(first, 80));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    stl::advance(first, 80);


    //在后端插入大量元素
    deq.insert(deq.end()-5, first, stl::next(first, 400));
    li.insert(stl::prev(li.end(), 5), first, stl::next(first, 400));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
}


template<typename ForwardIterator>
void testDequeEraseCase1(ForwardIterator first, ForwardIterator last)//erase(iterator pos)
{
    typedef typename iterator_traits<ForwardIterator>::value_type T;
    stl::deque<T, stl::allocator<T>, 4> deq(first, last);
    stl::list<T> li(first, last);

    assert(li.size()==deq.size() && stl::equal(li.begin(), li.end(), deq.begin()));

    deq.erase(deq.begin());
    li.erase(li.begin());
    assert(li.size()==deq.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.end());
    li.erase(li.end());
    assert(li.size()==deq.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.end()-1);
    li.erase(stl::prev(li.end()));
    assert(li.size()==deq.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.begin()+2);//删除点前面的元素少
    li.erase(stl::next(li.begin(), 2));
    assert(li.size()==deq.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.end()-3);//删除点后面的元素少
    li.erase(stl::prev(li.end(), 3));
    assert(li.size()==deq.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    //m_finish节点指向最后一个buffer的第一个元素，删除后，m_finish要前移一个buffer
    deq.assign(first, stl::next(first, 8));
    li.assign(first, stl::next(first, 8));
    assert(deq.end().m_node-deq.begin().m_node == 2);
    deq.erase(deq.end()-1);
    li.erase(stl::prev(li.end()));
    assert(li.size()==deq.size() && stl::equal(li.begin(), li.end(), deq.begin()));
    assert(deq.end().m_node-deq.begin().m_node == 1);
}


template<typename ForwardIterator>
void testDequeEraseCase2(ForwardIterator first, ForwardIterator last)
{
    assert(stl::distance(first, last) >= 400);

    typedef typename iterator_traits<ForwardIterator>::value_type T;
    stl::deque<T, stl::allocator<T>, 4> deq(first, stl::next(first, 17));
    stl::vector<T> vv(first, stl::next(first, 17));
    assert(vv.size()==deq.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));

    //删除后端
    deq.erase(deq.end()-6, deq.end());//跨buffer删除
    vv.erase(vv.end()-6, vv.end());
    assert(vv.size()==deq.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    assert(deq.end().m_cur - deq.end().m_first >= 3);
    deq.erase(deq.end()-3, deq.end());//一个buffer内删除
    vv.erase(vv.end()-3, vv.end());
    assert(vv.size()==deq.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    deq.erase(deq.begin(), deq.end());
    assert(deq.empty());



    //删除前端
    stl::advance(first, 17);
    deq.assign(first, stl::next(first, 17));
    stl::list<T> li(first, stl::next(first, 17));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));

    deq.erase(deq.begin(), deq.begin()+3);//buffer内删除
    li.erase(li.begin(), stl::next(li.begin(), 3));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.begin(), deq.begin()+8);//跨buffer删除
    li.erase(li.begin(), stl::next(li.begin(), 8));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.begin(), deq.end()-1);
    li.erase(li.begin(), stl::prev(li.end()));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.begin(), deq.end());
    assert(deq.empty());



    //删除中间元素
    stl::advance(first, 17);
    deq.assign(first, stl::next(first, 80));
    li.assign(first, stl::next(first, 80));

    deq.erase(deq.begin()+9, deq.begin()+9+5);//前端较少元素，并且删掉的元素少于前端的元素个数
    li.erase(stl::next(li.begin(), 9), stl::next(li.begin(), 9+5));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));

    deq.erase(deq.begin()+3, deq.begin()+9);//前端较少元素，并且删掉的元素多于前端的元素个数
    li.erase(stl::next(li.begin(), 3), stl::next(li.begin(), 9));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));



    deq.erase(deq.end()-10, deq.end()-8);//后端较少元素，并且删除的元素少于后的的元素个数
    li.erase(stl::prev(li.end(), 10), stl::prev(li.end(), 8));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));


    deq.erase(deq.end()-10, deq.end()-2);//后端较少元素，并且删除的元素多于后的的元素个数
    li.erase(stl::prev(li.end(), 10), stl::prev(li.end(), 2));
    assert(deq.size()==li.size() && stl::equal(li.begin(), li.end(), deq.begin()));
}


//实际使用的是insert和erase，因此无需过多测试
void testDequeResizeCase1()
{
    stl::deque<std::string> deq(5, "Deque");
    stl::vector<std::string> vv(5, "Deque");
    assert(vv.size()==deq.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    deq.resize(5);
    vv.resize(5);
    assert(vv.size()==deq.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    deq.resize(10, "Vector");
    vv.resize(10, "Vector");
    assert(vv.size()==deq.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    deq.resize(8);
    vv.resize(8);

    assert(vv.size()==deq.size() && stl::equal(vv.begin(), vv.end(), deq.begin()));


    deq.resize(0);
    assert(deq.empty());
}


//===============================================================================


void testDeque()
{
    testDequeConstructorCase1<int>();
    testDequeConstructorCase1<char>();
    testDequeConstructorCase1<double>();
    testDequeConstructorCase1<std::string>();


    testDequeConstructorCase2<int>(2);
    testDequeConstructorCase2<char>('D');
    testDequeConstructorCase2<double>(3.14159);
    testDequeConstructorCase2<std::string>("Deque");


    testDequeConstructorCase3();

    testDequeConstructorCase4();

    testDequeConstructorCase5();


    testDequeCopyConstructorCase1();

    testDequeOperatorAssignCase1();

    testDequePopFrontCase1();
    testDequePopBackCase1();


    testDequePushBackCase1();
    testDequePushBackCase2();

    testDequePushFrontCase1();
    testDequePushFrontCase2();


    testDequeSwapCase1();

    testDequeClearCase1();

    testDequeBeginEndCase1();
    testDequeBeginEndCase2();
    testDequeBeginEndCase3();

    testDequeSizeCase1(1);
    testDequeSizeCase1(3.14159);
    testDequeSizeCase1<std::string>("deque");

    testDequeFrontBackCase1();

    testDequeRandomAccessCase1();


    testDequeAssignCase1();
    testDequeAssignCase2();
    testDequeAssignCase3();


    testDequeInsertCase1();

    stl::vector<int> int_vec = generateRandomInt(500);
    stl::vector<std::string> str_vec = generateRandomString(500);


    testDequeInsertCase2(int_vec.data(), int_vec.size());
    testDequeInsertCase2(str_vec.data(), str_vec.size());

    testDequeInsertCase3(int_vec.data(), int_vec.size());
    testDequeInsertCase3(str_vec.data(), str_vec.size());

    testDequeInsertCase4(int_vec.data(), int_vec.size());
    testDequeInsertCase4(str_vec.data(), str_vec.size());

    testDequeInsertCase5();

    testDequeInsertCase6(int_vec.begin(), int_vec.end());
    testDequeInsertCase6(str_vec.begin(), str_vec.end());

    testDequeInsertCase7(int_vec.begin(), int_vec.end());
    testDequeInsertCase7(str_vec.begin(), str_vec.end());

    testDequeInsertCase8(int_vec.begin(), int_vec.end());
    testDequeInsertCase8(str_vec.begin(), str_vec.end());


    testDequeEraseCase1(int_vec.begin(), int_vec.end());
    testDequeEraseCase1(str_vec.begin(), str_vec.end());

    testDequeEraseCase2(int_vec.begin(), int_vec.end());
    testDequeEraseCase2(str_vec.begin(), str_vec.end());


    testDequeResizeCase1();
}

}
