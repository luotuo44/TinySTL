//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testVector.h"


#include"../vector"


#include<assert.h>

#include<string>
#include<vector>
#include<algorithm>
#include<functional>


namespace stl
{

template<typename T>
void testVectorConstructorCase1()
{
    stl::vector<T> vec;
    assert(vec.size() == 0 && vec.capacity() == 0);
    assert(vec.begin() == vec.end());

    vec.clear();
    assert(vec.size() == 0 && vec.capacity() == 0);
    assert(vec.begin() == vec.end());
}


template<typename T>
void testVectorConstructorCase2(const T &t)
{
    stl::vector<T> vec(30, t);
    assert(vec.size() == 30 && vec.capacity() >= 30);
    assert(vec.begin()+vec.size() == vec.end());

    typename stl::vector<T>::iterator first = vec.begin();
    for(; first != vec.end(); ++first)
    {
        assert(*first == t);
    }

    size_t capacity = vec.capacity();
    vec.clear();
    assert(vec.size() == 0 && capacity == vec.capacity());


    stl::vector<T> cp_vec(vec);//copy constructor
    assert(cp_vec.size() == vec.size());
    for(size_t i = 0; i < vec.size(); ++i)
        assert(cp_vec[i] == vec[i]);

    cp_vec = vec;//operator =
    assert(cp_vec.size() == vec.size());
    for(size_t i = 0; i < vec.size(); ++i)
        assert(cp_vec[i] == vec[i]);

    cp_vec.clear();
    assert(cp_vec.empty());


    //边界情况
    stl::vector<T> vec2(0, t);
    assert(vec2.empty());

    stl::vector<T> vec3(1, t);
    assert(vec3.size() == 1 && vec3[0] == t);
}


void testVectorConstructorCase3()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::vector<double> vec1(d1, d1+n1);

    assert(vec1.size() == n1);
    for(size_t i = 0; i < n1; ++i)
        assert(d1[i] == vec1[i]);


    std::string str[] = {"a", "bb", "ccc", "dddd"};
    size_t n2 = sizeof(str)/sizeof(str[0]);

    stl::vector<std::string> vec2(str, str+n2);
    assert(vec2.size() == n2);
    for(size_t i = 0; i < n2; ++i)
        assert(str[i] == vec2[i]);


    //边界情况
    stl::vector<double> vec3(d1, d1);
    assert(vec3.empty());

    stl::vector<double> vec4(d1, d1+1);
    assert(vec4.size()==1 && vec4[0] == d1[0]);
}



void testVectorOperateAssignCase1()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::vector<double> vec1(d1, d1+n1);

    stl::vector<double> vec2;
    vec2 = vec1;

    assert(vec2.size() == vec1.size());
    for(size_t i = 0; i < vec1.size(); ++i)
        assert(vec2[i] == vec1[i]);


    vec2 = vec2;//测试赋值给自己
    assert(vec2.size() == vec1.size());
    for(size_t i = 0; i < vec1.size(); ++i)
        assert(vec2[i] == vec1[i]);



    std::string str[] = {"a", "bb", "ccc", "dddd"};
    size_t n2 = sizeof(str)/sizeof(str[0]);

    stl::vector<std::string> vec3(str, str+n2);

    stl::vector<std::string> vec4;
    vec4 = vec4;
    assert(vec4.empty());

    vec4 = vec3;
    assert(vec4.size() == vec3.size());
    for(size_t i = 0; i < vec3.size(); ++i)
        assert(vec3[i] == vec4[i]);


    vec3.clear();
    vec4 = vec3;
    assert(vec4.empty());
}


void testVectorBeginEndCase1()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::vector<double> vec1(d1, d1+n1);
    *vec1.begin() = 6.66666;
    assert(*vec1.begin() == 6.66666);
    *(vec1.end()-1) = 7.77777;
    assert(*(vec1.end()-1) == 7.77777);

    const stl::vector<double> &vec1_ref = vec1;
    assert(*vec1_ref.begin() == vec1[0]);
    assert(*(vec1_ref.end()-1) == vec1[n1-1]);


    //*vec1.cbegin() = 6.66666; 无法编译通过
    //*(vec1.cend()-1) = 7.77777; 无法编译通过
    //*vec1_ref.begin() = 6.66666; 无法编译通过
    //*(vec1_ref.end()-1) = 7.77777; 无法编译通过

    //iterator 可以赋值给 const iterator
    stl::vector<double>::const_iterator const_it = vec1.begin();
    const_it = vec1.end();
    const_it = vec1.cbegin();
    const_it = vec1.cend();

    //测试const iterator
    //stl::vector<double>::iterator non_const_it = vec1.cbegin();无法编译通过
    //stl::vector<double>::iterator non_const_it = vec1.cend();无法编译通过
    //stl::vector<double>::iterator non_const_it = vec1_ref.begin();无法编译通过
    //stl::vector<double>::iterator non_const_it = vec1_ref.end();无法编译通过
}



void testVectorBeginEndCase2()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::vector<double> vec1(d1, d1+n1);
    std::vector<double> vec2(d1, d1+n1);

    assert(vec1.size() == vec2.size());
    assert(stl::equal(vec1.rbegin(), vec1.rend(), vec2.rbegin()));
    assert(stl::equal(vec1.crbegin(), vec1.crend(), vec2.rbegin()));

    stl::vector<double>::reverse_iterator non_const_it = vec1.rbegin();
    non_const_it = vec1.rend();

    stl::vector<double>::const_reverse_iterator const_it = vec1.rbegin();
    const_it = vec1.rend();
    //测试const reverse itereator
    //non_const_it = vec1.crbegin();无法编译通过
    //non_const_it = vec1.crend();无法编译通过
}


template<typename T>
void testVectorSizeCase1(const T &t)
{
    stl::vector<T> vec(10, t);

    assert(!vec.empty());
    assert(vec.size() == 10);
    assert(vec.capacity() >= 10);


    size_t cap = vec.capacity();

    vec.clear();
    assert(vec.empty());
    assert(vec.size() == 0);
    assert(vec.capacity() == cap);
}



void testVectorFronBackDataCase1()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::vector<double> vec1(d1, d1+n1);

    assert(vec1.front() == d1[0]);
    assert(vec1.back() == d1[n1-1]);

    vec1.front() = 6.6666;
    assert(vec1[0] == 6.6666);
    vec1.back() = 7.7777;
    assert(vec1[vec1.size()-1] == 7.7777);

    const stl::vector<double> &vec2 = vec1;
    assert(vec2.front() == 6.6666);
    assert(vec2.back() == 7.7777);


    //vec2.front() = 2.223; 无法编译通过
    //vec2.back() = 2.223; 无法编译通过


    double *p = vec1.data();
    p[0] = d1[0];
    p[n1-1] = d1[n1-1];

    assert(std::equal(p, p+n1, d1));

    //p = vec2.data(); 无法编译通过
}



void testVectorResizeReserveCase1()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::vector<double> vec1(d1, d1+n1);
    size_t size = vec1.size();

    assert(!vec1.empty());
    vec1.reserve(3*size/2);
    double *p = vec1.data();

    assert(vec1.size() == size);
    assert(vec1.capacity() >= 3*size/2);

    size_t cap = vec1.capacity();

    vec1.resize(1);
    assert(vec1.size() == 1);
    assert(vec1.capacity() == cap);
    assert(p == vec1.data());

    vec1.resize(size, 6.6666);
    assert(vec1.size() == size);
    assert(vec1.capacity() == cap);
    assert(p == vec1.data());

    vec1.reserve(cap);
    assert( p == vec1.data());


    size = vec1.size();
    vec1.reserve(3*cap);
    assert(vec1.capacity() >= 3*cap);
    assert(p != vec1.data());//重新开辟空间
    assert(size == vec1.size());//不会改变其大小

    cap = vec1.capacity();
    p = vec1.data();

    vec1.clear();
    assert(vec1.empty());
    assert(vec1.capacity() == cap);
    assert(vec1.data() == p);
}


template<typename T>
void testVectorSwapCase1(const T &t1, const T &t2)
{
    stl::vector<T> vec1(10, t1);
    stl::vector<T> vec2(2, t2);

    assert(vec1.size() == 10);
    assert(vec2.size() == 2);

    vec1.swap(vec2);
    assert(vec1.size() == 2);
    assert(vec2.size() == 10);

    typename stl::vector<T>::iterator it = vec1.begin();
    while( it != vec1.end() )
    {
        assert(*it++ == t2);
    }

    for(it = vec2.begin(); it != vec2.end(); ++it)
    {
        assert(*it == t1);
    }


    size_t size = vec1.size();
    vec1.reserve(3*vec1.capacity());
    assert(vec1.capacity() > size);

    stl::vector<T>(vec1).swap(vec1);
    assert(size == vec1.size());
    assert(vec1.capacity() == size);
}



void testVectorPushPopCase1()
{
    stl::vector<int> vec;

    vec.push_back(1);
    assert(vec.size()==1 && vec.front()==1);

    vec.pop_back();
    assert(vec.empty());

    vec.push_back(2);
    assert(vec.size()==1 && vec.back()==2);

    vec.push_back(3);
    assert(vec.size()==2 && vec.front()==2 && vec.back()==3);

    vec.push_back(4);
    assert(vec.size()==3 && vec[0]==2 && vec[1]==3 && vec[2]==4);

    vec.pop_back();
    assert(vec.size()==2 && vec.front()==2 && vec.back()==3);

    vec.pop_back();
    assert(vec.size()==1 && vec.back()==2);

    vec.pop_back();
    assert(vec.empty());

}



void testVectorAssignCase1()
{
    size_t size = 6;
    stl::vector<std::string> vec(size, "TinySTL");
    assert(vec.size() == size);

    //不会重新分配内存
    long l_size = 4;
    vec.assign(l_size, "C++");
    assert(vec.size() == static_cast<size_t>(l_size) );
    for(size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == "C++");


    //会重新分配内存
    size = vec.capacity() + 1;
    vec.assign(size, "Test");
    assert(vec.size() == size);
    for(size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == "Test");

    //边界测试
    vec.assign(0, "vector");
    assert(vec.empty());


    stl::vector<std::string> vec2;
    vec2.assign(3, "empty");
    assert(vec2.size() == 3);
    for(size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == "empty");
}


void testVectorAssignCase2()//测试random iterator
{
    double d1[] = {2.3, 3,44, 1.56, 34.480, 3.14159, 0.126, 23.1, 5.23434, 1000.00};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::vector<double> vec;
    vec.assign(d1, d1+2);
    assert(vec.size() == 2);
    for(size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == d1[i]);


    //不会重新分配内存
    vec.assign(d1, d1+1);
    assert(vec.size() == 1 && vec[0] == d1[0]);


    //会重新分配内存
    assert(n1 > vec.capacity());
    vec.assign(d1, d1+n1);
    assert(vec.size() == n1);
    for(size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == d1[i]);

    vec.assign(d1, d1);
    assert(vec.empty());
}



template<typename Category>
class SplitString
{
public:

    typedef std::string value_type;
    typedef ptrdiff_t difference_type;
    typedef std::string* pointer;
    typedef std::string& reference;
    typedef Category iterator_category;

public:
    SplitString(const std::string &str, const std::string &dem)
        : m_str(str), m_dem(dem)
    {
        m_last_pos = 0;
        m_pos = m_str.find(m_dem, m_last_pos);
    }

    SplitString()
        : m_str(std::string("")), m_dem(std::string("")),
          m_pos(std::string::npos), m_last_pos(std::string::npos)
    {
    }


    std::string operator * ()const
    {
        return m_str.substr(m_last_pos, m_pos-m_last_pos);
    }


    SplitString& operator ++()
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


    SplitString operator ++ (int)
    {
        SplitString tmp(*this);
        ++(*this);
        return tmp;
    }

    bool operator == (const SplitString &ss)const
    {
        return m_pos == ss.m_pos && m_last_pos == ss.m_last_pos;
    }


    bool operator != (const SplitString &ss)const
    {
        return !(*this == ss);
    }

private:
    const std::string &m_str;
    const std::string &m_dem;

    std::string::size_type m_pos;
    std::string::size_type m_last_pos;
};


void testVectorAssignCase3()//测试 input iterator
{
    std::string str("a test");
    stl::vector<std::string> vec;
    vec.assign(SplitString<stl::input_iterator_tag>(str, " "), SplitString<stl::input_iterator_tag>());

    assert(vec.size() == 2);
    assert(vec[0] == "a" && vec[1] == "test");


    vec.assign(SplitString<stl::input_iterator_tag>("test", " "), SplitString<stl::input_iterator_tag>());
    assert(vec.size() == 1 && vec[0] == "test");


    assert(vec.capacity() < 4);
    str = "this is just a test";
    vec.assign(SplitString<stl::input_iterator_tag>(str, " "), SplitString<stl::input_iterator_tag>());
    assert(vec.size() == 5);
    std::vector<std::string> vvec(SplitString<std::input_iterator_tag>(str, " "), SplitString<std::input_iterator_tag>());
    assert(stl::equal(vec.begin(), vec.end(), vvec.begin()));


    vec.assign(SplitString<stl::input_iterator_tag>(), SplitString<stl::input_iterator_tag>());
    assert(vec.empty());
}


//需要测试 插入位置为 前中后，是否需要分配内存
void testVectorInsertCase1()
{
    int val = 0;
    stl::vector<int> vec;
    typename vector<int>::iterator pos;
    pos = vec.insert(vec.end(), val++);
    assert(vec.end()-1 == pos && vec.size()==1 && vec.back()==val-1);

    pos = vec.insert(vec.end(), val++);
    assert(vec.end()-1 == pos && vec.size()==2 && vec.front() == val-2 && vec.back()==val-1);

    pos = vec.insert(vec.end(), val++);
    assert(vec.end()-1 == pos && vec.size()==3 && vec.front()==val-3 && vec[1] == val-2 && vec[2] == val-1);

    assert(vec.capacity() >= 4);
    pos = vec.insert(vec.end(), val);//不需要分配内存
    assert(vec.end()-1 == pos && vec.size() == 4 );

    for(size_t i = 0; i < vec.size(); ++i)
        assert((size_t)vec[i] == i);
}


void testVectorInsertCase2()
{
    int val = 3;
    stl::vector<int> vec;
    typename vector<int>::iterator pos;

    pos = vec.insert(vec.begin(), val--);
    assert(pos == vec.begin() && vec.size() == 1 && vec.front() == val+1);

    pos = vec.insert(vec.begin(), val--);
    assert(pos == vec.begin() && vec.size() == 2 && vec.front() == val+1 && vec.back() == val+2);

    pos = vec.insert(vec.begin(), val--);
    assert(pos == vec.begin() && vec.size() == 3 && vec[0] == val+1 && vec[1] == val+2 && vec[2] == val+3);


    assert(vec.capacity() >= 4);
    pos = vec.insert(vec.begin(), val);//不需要分配内存
    assert(vec.begin() == pos && vec.size() == 4 );

    for(size_t i = 0; i < vec.size(); ++i)
        assert((size_t)vec[i] == i);
}


void testVectorInsertCase3()
{
    int a1[] = {1, 2, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    stl::vector<int> vec(a1, a1+n1);

    typename stl::vector<int>::iterator pos, it;

    int val = 8, v;
    size_t size = vec.size();
    pos = vec.insert(vec.end()-1, val--);//分配新内存
    ++size;
    assert(vec.size() == size && vec[size-2] == val+1);

    pos = vec.insert(pos, val--);
    assert(vec.size() == ++size);
    for(it = pos, v = val+1; it != vec.end(); ++it, v++)
    {
        assert(*it == v);
    }

    pos = vec.insert(pos, val--);
    assert(vec.size() == ++size);
    for(it = pos, v = val+1; it != vec.end(); ++it, v++)
    {
        assert(*it == v);
    }


    pos = vec.insert(pos, val--);//分配新内存
    assert(vec.size() == ++size);
    for(it = pos, v = val+1; it != vec.end(); ++it, v++)
    {
        assert(*it == v);
    }


    pos = vec.insert(pos, val--);
    assert(vec.size() == ++size);
    for(it = pos, v = val+1; it != vec.end(); ++it, v++)
    {
        assert(*it == v);
    }


    pos = vec.insert(pos, val--);
    assert(vec.size() == ++size);
    for(it = pos, v = val+1; it != vec.end(); ++it, v++)
    {
        assert(*it == v);
    }

    vec.insert(vec.begin(), 0);
    assert(vec.size() == 10);

    for(size_t i = 0; i < vec.size(); ++i)
    {
        assert((size_t)vec[i] == i);
    }
}



void testVectorInsertFillCase1()
{
    stl::vector<int> vec;

    vec.insert(vec.begin(), static_cast<size_t>(3), 13);
    assert(vec.size() == 3 && vec.capacity() == 3);
    for(size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == 13);


    vec.insert(vec.begin()+1, static_cast<size_t>(5), 14);
    assert(vec.size() == 8 && vec.front() == 13);
    size_t j = 1;
    for(; j < 6; ++j)
    {
        assert(vec[j] == 14);
    }

    while(j < vec.size())
    {
        assert(vec[j] == 13);
        ++j;
    }
}


void testVectorInsertFillCase2()
{
    stl::vector<int> vec;
    vec.reserve(10);
    assert(vec.capacity() >= 10 && vec.empty());

    vec.insert(vec.end(), 2, 1);
    assert(vec.size()==2 && vec.back()==1 && vec.front() == 1);


    stl::vector<int> vec1;
    vec1.reserve(10);
    assert(vec1.capacity()>=10);
    int a1[] = {0, 1, 3, 4};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    vec1.assign(a1, a1+n1);
    assert(vec1.size() == n1);

    //插入的长度小于backward
    vec1.insert(vec1.begin()+2, 1, 2);
    assert(vec1.size() == n1+1);
    for(size_t i = 0; i < vec.size(); ++i)
        assert((size_t)vec1[i] == i);


    //插入的长度大于backward
    vec1.insert(vec1.begin()+3, 4, 5);
    assert(vec1.size() == n1+1+4);
    assert(vec1[0]==0 && vec1[1]==1 && vec1[2] ==2);
    assert(vec1.back()==4 && vec1[vec1.size()-2]==3);

    for(size_t i=0; i<4; ++i)
        assert(vec1[i+3] == 5);


    stl::vector<int> vec2(vec1);
    vec1.insert(vec1.begin(), 5, -1);
    assert(vec1.size() == n1+1+4+5);
    size_t j = 0;
    while( j < 5)
    {
        assert(vec1[j++] == -1);
    }

    assert(stl::equal(vec2.begin(), vec2.end(), vec1.begin()+j));
}




void testVectorInsertRangeCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);


    stl::vector<int> vec;
    vec.reserve(10);
    vec.insert(vec.end(), a1, a1+3);
    assert(vec.size() == 3);
    for(size_t i = 0; i < vec.size(); ++i)
        assert((size_t)vec[i] == i+1);


    stl::vector<int> vec1;
    vec1.reserve(10);
    vec1.insert(vec1.begin(), a1, a1+4);
    assert(vec1.size() == 4);
    for(size_t i = 0; i < 4; ++i)
        assert(vec1[i] == a1[i]);


    int a2[] = {1, 2, 5, 3, 4};
    vec1.insert(vec1.begin()+2, a1+4, a1+5);
    assert(vec1.size() == 5);
    assert(stl::equal(vec1.begin(), vec1.end(), a2));


    int a3[] = {1, 2, 5, 6, 7, 8, 9, 3, 4};
    vec1.insert(vec1.begin()+3, a1+5, a1+n1);
    assert(vec1.size() == n1);
    assert(stl::equal(vec1.begin(), vec1.end(), a3));


    int a4[] = {-2, -1, 0};
    int a5[] = {-2, -1, 0, 1, 2, 5, 6, 7, 8, 9, 3, 4};
    vec1.insert(vec1.begin(), a4, a4+3);
    assert(vec1.size() == n1+3);
    assert(stl::equal(vec1.begin(), vec1.end(), a5));
}



void testVectorInsertRangeCase2()
{
    stl::vector<std::string> vec;
    vec.reserve(10);
    std::vector<std::string> cp_vec;

    std::string str("just a test");
    vec.insert(vec.end(), SplitString<stl::input_iterator_tag>(str, " "), SplitString<stl::input_iterator_tag>());
    cp_vec.insert(cp_vec.end(), SplitString<std::input_iterator_tag>(str, " "), SplitString<std::input_iterator_tag>());

    assert(vec.size() == cp_vec.size());
    assert(stl::equal(vec.begin(), vec.end(), cp_vec.begin()));


    str = "this is just a test";
    stl::vector<std::string> vec1;
    std::vector<std::string> cp_vec1;
    vec1.insert(vec1.end(), SplitString<stl::input_iterator_tag>(str, " "), SplitString<stl::input_iterator_tag>());
    cp_vec1.insert(cp_vec1.end(), SplitString<std::input_iterator_tag>(str, " "), SplitString<std::input_iterator_tag>());
    assert(vec1.size() == cp_vec1.size());
    assert(stl::equal(vec1.begin(), vec1.end(), cp_vec1.begin()));
}



void testVectorEraseCase1()
{
    int a1[] = {1, 2, 3, 4};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    stl::vector<int> vec(a1, a1+n1);

    typename stl::vector<int>::iterator pos = vec.begin() + 1;
    pos = vec.erase(pos);
    assert(vec.size() == 3 && vec[0]==1 && vec[1]==3 && vec[2]==4);

    pos = vec.erase(pos);
    assert(vec.size()==2 && vec[0]==1 && vec[1]==4);

    pos = vec.erase(pos);
    assert(vec.size()==1 && vec[0]==1 && pos==vec.end());

    vec.erase(vec.begin());
    assert(vec.empty());
}


void testVectorEraseCase2()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    stl::vector<int> vec(a1, a1+n1);
    stl::vector<int>::iterator pos = vec.end()-3;
    pos = vec.erase(pos, vec.end());//包含最后一个元素
    assert(vec.size() == n1-3  && pos == vec.end());
    assert(stl::equal(vec.begin(), vec.end(), a1));

    int a2[] = {1, 2, 5, 6};
    pos = vec.erase(vec.begin()+2, vec.begin()+4);
    assert(vec.size() == 4 && pos == vec.begin()+2);
    assert(stl::equal(vec.begin(), vec.end(), a2));


    pos = vec.erase(vec.begin(), vec.begin()+3);
    assert(vec.size()==1 && vec.begin()==pos && vec.front()==6);

    pos = vec.erase(pos, pos);
    assert(vec.size()==1 && vec.begin()==pos && vec.front()==6);

    vec.erase(vec.begin(), vec.end());
    assert(vec.empty());

    stl::vector<int> vec1(a1, a1+n1);
    vec1.erase(vec1.begin(), vec1.end());
    assert(vec1.empty());
}

//======================================================================


void testVector()
{
    testVectorConstructorCase1<int>();
    testVectorConstructorCase1<double>();
    testVectorConstructorCase1<char>();
    testVectorConstructorCase1<std::string>();


    testVectorConstructorCase2<int>(3);
    testVectorConstructorCase2<double>(3.14159);
    testVectorConstructorCase2<char>('G');
    testVectorConstructorCase2<std::string>("TinySTL");

    testVectorConstructorCase3();


    testVectorOperateAssignCase1();

    testVectorBeginEndCase1();
    testVectorBeginEndCase2();


    testVectorSizeCase1<int>(29);
    testVectorSizeCase1<double>(2.718281828);
    testVectorSizeCase1<char>('T');
    testVectorSizeCase1<std::string>("C++");


    testVectorFronBackDataCase1();


    testVectorResizeReserveCase1();

    testVectorSwapCase1<int>(23, 45);
    testVectorSwapCase1<double>(3.14159, 2.718281828);
    testVectorSwapCase1<char>('G', 'T');
    testVectorSwapCase1<std::string>("STD", "STL");


    testVectorPushPopCase1();

    testVectorAssignCase1();
    testVectorAssignCase2();
    testVectorAssignCase3();


    testVectorInsertCase1();
    testVectorInsertCase2();
    testVectorInsertCase3();


    testVectorInsertFillCase1();
    testVectorInsertFillCase2();


    testVectorInsertRangeCase1();
    testVectorInsertRangeCase2();


    testVectorEraseCase1();
    testVectorEraseCase2();
}

}

