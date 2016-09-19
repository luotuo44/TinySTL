//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testAlgobase.h"

#include<assert.h>
#include<stdlib.h>
#include<time.h>

#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<iostream>
#include<iterator>
#include<functional>


#include"../bits/stl_algobase.h"
#include"../bits/stl_numeric.h"
#include"../iterator"

namespace stl
{


void testEqualCase1()
{
    srand(time(NULL));
    std::vector<int> vec;
    vec.reserve(100);
    for(int i = 0; i < 100; ++i)
        vec.push_back(rand()%1000);

    assert(stl::equal(vec.begin(), vec.begin(), vec.begin()));
    assert(stl::equal(vec.begin(), ++vec.begin(), vec.begin()));
    assert(stl::equal(vec.begin(), vec.end(), vec.begin()));

    std::vector<int> cp_vec(vec);
    assert(stl::equal(vec.begin(), vec.end(), cp_vec.begin()));

    cp_vec.back() += 1;
    assert(!stl::equal(vec.begin(), vec.end(), cp_vec.begin()));
    cp_vec.back() -= 1;

    cp_vec.front() += 1;
    assert(!stl::equal(vec.begin(), vec.end(), cp_vec.begin()));
    cp_vec.front() -= 1;

    cp_vec.push_back(100);
    assert(stl::equal(vec.begin(), vec.end(), cp_vec.begin()));
}


void testEqualCase2()
{
    srand(time(NULL));
    std::vector<int> vec;
    vec.reserve(100);
    for(int i = 0; i < 100; ++i)
        vec.push_back(rand()%1000);

    assert(stl::equal(vec.begin(), vec.begin(), vec.begin(), std::equal_to<int>()));
    assert(stl::equal(vec.begin(), ++vec.begin(), vec.begin(), std::equal_to<int>()));
    assert(stl::equal(vec.begin(), vec.end(), vec.begin(), std::equal_to<int>()));

    std::vector<int> cp_vec(vec);
    assert(stl::equal(vec.begin(), vec.end(), cp_vec.begin(), std::equal_to<int>()));

    cp_vec.back() += 1;
    assert(!stl::equal(vec.begin(), vec.end(), cp_vec.begin(), std::equal_to<int>()));
    cp_vec.back() -= 1;

    cp_vec.front() += 1;
    assert(!stl::equal(vec.begin(), vec.end(), cp_vec.begin(), std::equal_to<int>()));
    cp_vec.front() -= 1;

    cp_vec.push_back(100);
    assert(stl::equal(vec.begin(), vec.end(), cp_vec.begin(), std::equal_to<int>()));
}


void testFill()
{
    std::vector<int> vec;
    vec.resize(10);

    stl::iota(vec.begin(), vec.end(), 0);

    stl::fill(vec.begin(), vec.begin(), 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 0);

    stl::fill(vec.begin(), ++vec.begin(), 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 1);


    stl::fill(vec.begin(), --vec.end(), 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 9);

    stl::fill(vec.begin(), vec.end(), 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 10);
}



void testFillN()
{
    std::vector<int> vec;
    vec.resize(10);

    stl::iota(vec.begin(), vec.end(), 0);

    stl::fill_n(vec.begin(), -1, 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 0);

    stl::fill_n(vec.begin(), 0, 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 0);

    stl::fill_n(vec.begin(), 1, 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 1);


    stl::fill_n(vec.begin(), vec.size()-1, 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 9);

    stl::fill_n(vec.begin(), vec.size(), 100);
    assert(std::count(vec.begin(), vec.end(), 100) == 10);
}


void testIterSwap()
{
    int a[2] = {1, 2};
    stl::iter_swap(a, a+1);
    assert( (a[0]==2) && (a[1]==1));


    std::vector<int> vec(a, a+2);
    stl::iter_swap(vec.begin(), ++vec.begin());
    assert( (vec[0] == 1) && (vec[1] == 2));
}


void testMin()
{
    assert(stl::min(2, 3) == 2);
    assert(stl::min(3, 2) == 2);

    assert(stl::min(2, 3, std::less<int>()) == 2);
    assert(stl::min(3, 2, std::less<int>()) == 2);
}


void testMax()
{
    assert(stl::max(2, 3) == 3);
    assert(stl::max(3, 2) == 3);

    assert(stl::max(2, 3, std::greater<int>()) == 3);
    assert(stl::max(3, 2, std::greater<int>()) == 3);
}


template<typename T>
void testLexicographicalCompareCase1()
{
    const T *str1 = reinterpret_cast<const T*>("abcde");
    const T *str2 = reinterpret_cast<const T*>("abcde");

    assert(lexicographical_compare(str1, str1+5, str2, str2+5) == false);
    assert(lexicographical_compare(str1, str1+4, str2, str2+5) == true);
    assert(lexicographical_compare(str1, str1+5, str2, str2+4) == false);


    str1 = reinterpret_cast<const T*>("ab");
    str2 = reinterpret_cast<const T*>("cd");

    assert(lexicographical_compare(str1, str1+2, str2, str2+2) == true);
    assert(lexicographical_compare(str2, str2+2, str1, str1+2) == false);

    assert(lexicographical_compare(str1, str1, str2, str2) == false);
    assert(lexicographical_compare(str1, str1, str2, str2+2) == true);
    assert(lexicographical_compare(str1, str1+2, str2, str2) == false);
}


void testLexicographicalCompareCase2()
{
    std::vector<int> vec1, vec2;
    vec1.resize(10);
    vec2.resize(10);
    stl::iota(vec1.begin(), vec1.end(), 0);
    stl::iota(vec2.begin(), vec2.end(), 0);


    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()) == false);
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end()-1, vec2.begin(), vec2.end()) == true);
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()-1) == false);


    vec1[0] = 1;
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()) == false);
    assert(stl::lexicographical_compare(vec2.begin(), vec2.end(), vec1.begin(), vec1.end()) == true);


    assert(stl::lexicographical_compare(vec1.begin(), vec1.begin(), vec2.begin(), vec2.end()) == true);
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.begin()) == false);
}



void testLexicographicalCompareCase3()
{
    std::vector<int> vec1, vec2;
    vec1.resize(10);
    vec2.resize(10);
    stl::iota(vec1.begin(), vec1.end(), 0);
    stl::iota(vec2.begin(), vec2.end(), 0);


    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::less<int>()) == false);
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end()-1, vec2.begin(), vec2.end(), std::less<int>()) == true);
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()-1, std::less<int>()) == false);


    vec1[0] = 1;
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::less<int>()) == false);
    assert(stl::lexicographical_compare(vec2.begin(), vec2.end(), vec1.begin(), vec1.end(), std::less<int>()) == true);


    assert(stl::lexicographical_compare(vec1.begin(), vec1.begin(), vec2.begin(), vec2.end(), std::less<int>()) == true);
    assert(stl::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.begin(), std::less<int>()) == false);
}

void testMismatchCase1()
{
    typedef std::vector<int>::iterator Iter;

    srand(time(NULL));
    std::vector<int> vec;
    vec.resize(10);
    stl::iota(vec.begin(), vec.end(), 0);

    std::vector<int> vv;

    stl::pair<Iter, Iter> p = stl::mismatch(vec.begin(), vec.begin(), vv.begin());
    assert((p.first == vec.begin()) && (p.second == vv.begin()));

    p = stl::mismatch(vv.begin(), vv.end(), vec.begin());
    assert( (p.first == vv.end()) && (p.second == vec.begin()));


    vv.assign(vec.begin(), vec.end());
    p = stl::mismatch(vv.begin(), vv.end(), vec.begin());
    assert( (p.first == vv.end()) && (p.second == vec.end()));

    vv.front() += 1;
    p = stl::mismatch(vec.begin(), vec.end(), vv.begin());
    assert((p.first == vec.begin()) && (p.second == vv.begin()));
    vv.front() -= 1;

    vv.back() += 1;
    p = stl::mismatch(vec.begin(), vec.end(), vv.begin());
    assert( (p.first == --vec.end()) && (p.second == --vv.end()));


    vv[1] += 1;
    p = stl::mismatch(vec.begin(), vec.end(), vv.begin());
    assert( (p.first == ++vec.begin()) && (p.second == ++vv.begin()));
}



void testMismatchCase2()
{
    typedef std::vector<int>::iterator Iter;

    srand(time(NULL));
    std::vector<int> vec;
    vec.resize(10);
    stl::iota(vec.begin(), vec.end(), 0);

    std::vector<int> vv;

    stl::pair<Iter, Iter> p = stl::mismatch(vec.begin(), vec.begin(), vv.begin(), std::equal_to<int>());
    assert((p.first == vec.begin()) && (p.second == vv.begin()));

    p = stl::mismatch(vv.begin(), vv.end(), vec.begin(), std::equal_to<int>());
    assert( (p.first == vv.end()) && (p.second == vec.begin()));


    vv.assign(vec.begin(), vec.end());
    p = stl::mismatch(vv.begin(), vv.end(), vec.begin(), std::equal_to<int>());
    assert( (p.first == vv.end()) && (p.second == vec.end()));

    vv.front() += 1;
    p = stl::mismatch(vec.begin(), vec.end(), vv.begin(), std::equal_to<int>());
    assert((p.first == vec.begin()) && (p.second == vv.begin()));
    vv.front() -= 1;

    vv.back() += 1;
    p = stl::mismatch(vec.begin(), vec.end(), vv.begin(), std::equal_to<int>());
    assert( (p.first == --vec.end()) && (p.second == --vv.end()));


    vv[1] += 1;
    p = stl::mismatch(vec.begin(), vec.end(), vv.begin(), std::equal_to<int>());
    assert( (p.first == ++vec.begin()) && (p.second == ++vv.begin()));
}


void testCopyCase1()//测试重载版本copy(const char *, const char *, char *)
{
    char p[5] = "abcd";
    char dst[5];

    stl::copy(p, p+5, dst);

    assert(std::equal(p, p+5, dst) == true);

    unsigned char ch[5] = "abcd";
    unsigned char str[5];
    stl::copy(ch, ch+5, str);
    assert(std::equal(ch, ch+5, str) == true);
}


struct CopyTest
{
    int a;
    int b;

    bool operator == (const CopyTest &ct)
    {
        return a == ct.a && b == ct.b;
    }
};


void testCopyCase2()//测试特化版本<T*, T*>和<const T*, T*>
{
    int arr[10];
    stl::iota(arr, arr+10, 0);
    int brr[10];

    stl::copy(arr, arr+10, brr);
    assert(std::equal(arr, arr+10, brr));

    int crr[10];
    const int *p = arr;
    stl::copy(p, p+10, crr);
    assert(std::equal(arr, arr+10, crr));



    CopyTest ct[2] = { {1, 2}, {2, 3} };
    CopyTest ct2[2];
    stl::copy(ct, ct+2, ct2);

    assert(std::equal(ct, ct+2, ct2));

    CopyTest ct3[2];
    const CopyTest *q = ct;
    stl::copy(q, q+2, ct3);
    assert(std::equal(ct, ct+2, ct3));
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


void testCopyCase3()//测试InputIterator 的泛化版本
{
    std::vector<std::string> vec1, vec2;

    std::string str1("a=34&b=223&c=37249&d=32423");
    stl::copy(SplitString<stl::input_iterator_tag>(str1, "&"), SplitString<stl::input_iterator_tag>(), std::back_inserter(vec1));

    std::copy(SplitString<std::input_iterator_tag>(str1, "&"), SplitString<std::input_iterator_tag>(), std::back_inserter(vec2));

    assert(vec1 == vec2);
}

//一个递减迭代器，与iota相对应
template<typename Category>
class IntDec
{
public:
    typedef std::string value_type;
    typedef ptrdiff_t difference_type;
    typedef std::string* pointer;
    typedef std::string& reference;
    typedef Category iterator_category;

public:
    IntDec(int start)
        : m_pos(start)
    {
    }


    IntDec& operator ++()
    {
        --m_pos;
        return *this;
    }

    IntDec operator ++(int)
    {
        IntDec tmp(*this);
        --m_pos;
        return tmp;
    }



    IntDec& operator --()
    {
        ++m_pos;
        return *this;
    }

    IntDec operator --(int)
    {
        IntDec tmp(*this);
        ++m_pos;
        return tmp;
    }


    IntDec operator + (difference_type n)
    {
        IntDec tmp(*this);
        tmp.m_pos -= n;
        return tmp;
    }


    IntDec& operator += (difference_type n)
    {
        m_pos -= n;
        return *this;
    }


    IntDec operator -= (difference_type n)
    {
        m_pos += n;
        return *this;
    }

    IntDec operator - (difference_type n)
    {
        IntDec tmp(*this);
        tmp.m_pos += n;
        return tmp;
    }


    difference_type operator - (const IntDec &id)const
    {
        return m_pos - id.m_pos;
    }


    int operator * ()const
    {
        return m_pos;
    }


    bool operator == (const IntDec &id)const
    {
        return m_pos == id.m_pos;
    }


    bool operator != (const IntDec &id)const
    {
        return m_pos != id.m_pos;
    }


    bool operator < (const IntDec &id)const
    {
        return m_pos > id.m_pos;
    }

    bool operator > (const IntDec &id)const
    {
        return m_pos < id.m_pos;
    }

    bool operator <= (const IntDec &id)const
    {
        return m_pos >= id.m_pos;
    }

    bool operator >= (const IntDec &id)const
    {
        return m_pos <= id.m_pos;
    }


private:
    int m_pos;
};



void testCopyCase4()//测试RandomIterator 泛化版本
{
    std::vector<int> vec1, vec2;
    stl::copy(IntDec<stl::random_access_iterator_tag>(10), IntDec<stl::random_access_iterator_tag>(0), std::back_inserter(vec1));
    std::copy(IntDec<std::random_access_iterator_tag>(10), IntDec<std::random_access_iterator_tag>(0), std::back_inserter(vec2));

    assert(vec1 == vec2);
}


void testCopyBackwardCase1()//测试特化版本<T*, T*>和<const T*, T*>
{
    int arr[10];
    stl::iota(arr, arr+10, 0);
    int brr[10];

    stl::copy_backward(arr, arr+10, brr+10);
    assert(std::equal(arr, arr+10, brr));

    int crr[10];
    const int *p = arr;
    stl::copy_backward(p, p+10, crr+10);
    assert(std::equal(arr, arr+10, crr));



    CopyTest ct[2] = { {1, 2}, {2, 3} };
    CopyTest ct2[2];
    stl::copy_backward(ct, ct+2, ct2+2);

    assert(std::equal(ct, ct+2, ct2));

    CopyTest ct3[2];
    const CopyTest *q = ct;
    stl::copy_backward(q, q+2, ct3+2);
    assert(std::equal(ct, ct+2, ct3));
}


void testCopyBackwardCase2()//测试RandomIterator和BidirectionalIterator版本
{
    std::vector<int> vec1(10), vec2(10);
    stl::copy_backward(IntDec<stl::random_access_iterator_tag>(10), IntDec<stl::random_access_iterator_tag>(0), vec1.end());
    std::copy_backward(IntDec<std::random_access_iterator_tag>(10), IntDec<std::random_access_iterator_tag>(0), vec2.end());
    assert(vec1 == vec2);


    stl::copy_backward(IntDec<stl::bidirectional_iterator_tag>(10), IntDec<stl::bidirectional_iterator_tag>(0), vec1.end());
    std::copy_backward(IntDec<std::bidirectional_iterator_tag>(10), IntDec<std::bidirectional_iterator_tag>(0), vec2.end());
    assert(vec1 == vec2);
}


void testAlgoBase()
{
    testEqualCase1();
    testEqualCase2();

    testFill();
    testFillN();

    testIterSwap();

    testMin();
    testMax();


    testLexicographicalCompareCase1<char>();
    testLexicographicalCompareCase1<unsigned char>();

    testLexicographicalCompareCase2();
    testLexicographicalCompareCase3();

    testMismatchCase1();
    testMismatchCase2();


    testCopyCase1();
    testCopyCase2();
    testCopyCase3();
    testCopyCase4();


    testCopyBackwardCase1();
    testCopyBackwardCase2();
}

}
