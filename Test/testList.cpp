//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testList.h"

#include"../list"

#include<assert.h>
#include<time.h>
#include<stdlib.h>


#include<algorithm>
#include<list>
#include<string>
#include<functional>
#include<iostream>
#include<vector>


#include"../bits/stl_numeric.h"

namespace stl
{

template<typename T>
void testListConstructorCase1()
{
    stl::list<T> alist;
    assert(alist.empty());
    assert(alist.size() == 0);
    assert(alist.begin() == alist.end());
}


template<typename T>
void testListConstructorCase2(const T &val)
{
    int i_num = 13;
    stl::list<T> alist1(i_num, val);
    assert(!alist1.empty() );
    assert(alist1.size() == static_cast<size_t>(i_num) );
    assert(stl::count(alist1.begin(), alist1.end(), val) == i_num);

    size_t num = 8;
    stl::list<T> alist2(num, val);
    assert(!alist2.empty() && alist2.size() == num);
    assert(stl::count(alist2.begin(), alist2.end(), val) == static_cast<int>(num) );


    //边界情况
    stl::list<T> alist3(0, val);
    assert(alist3.empty() && alist3.size()==0);

    stl::list<T> alist4(1, val);
    assert(!alist4.empty() && alist4.size() == 1 && alist4.front() == val);
}



void testListConstructorCase3()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::list<double> alist1(d1, d1+n1);

    assert(!alist1.empty() && alist1.size() == n1);
    stl::list<double>::iterator it = alist1.begin(), end = alist1.end();
    for(size_t i = 0; i < n1; ++i)
        assert(d1[i] == *it++);
    assert(it == end);

    std::string str[] = {"a", "bb", "ccc", "dddd"};
    size_t n2 = sizeof(str)/sizeof(str[0]);

    stl::list<std::string> alist2(str, str+n2);
    assert(!alist2.empty() && alist2.size() == n2);
    stl::list<std::string>::iterator first = alist2.begin(), last = alist2.end();
    for(size_t i = 0; i < n2; ++i)
        assert(str[i] == *first++);
    assert(first == last);

    //边界情况
    stl::list<double> alist3(d1, d1);
    assert(alist3.empty());
    stl::list<std::string> alist4(str, str);
    assert(alist4.empty());

    stl::list<double> alist5(d1, d1+1);
    assert(alist5.size()==1 && alist5.front() == d1[0]);
}



void testListCopyConstructorAndOperatorAssignCase1()
{
    stl::list<int> alist1;
    stl::list<int> alist1_copy(alist1);

    assert(alist1.empty() && alist1_copy.empty());


    stl::list<int> alist2(1, 2);
    stl::list<int> alist2_copy(alist2);
    assert(alist2.size()==1 && alist2_copy.size()==1 && alist2.front()==alist2_copy.back());


    std::string str[] = {"a", "bb", "ccc", "dddd"};
    size_t n1 = sizeof(str)/sizeof(str[0]);
    stl::list<std::string> alist3(str, str+n1);
    stl::list<std::string> alist3_copy(alist3);
    assert(alist3.size() == n1 && alist3_copy.size()==n1);
    assert(stl::equal(alist3.begin(), alist3.end(), str));
    assert(stl::equal(alist3_copy.begin(), alist3_copy.end(), str));


    alist1 = alist1;
    assert(alist1.empty());
    alist2 = alist2;
    assert(alist2.size()==1 && alist2.back()==2);

    stl::list<int> alist1_op = alist1;
    assert(alist1_op.empty());
    stl::list<int> alist2_op = alist2;
    assert(alist2_op.size()==1 && alist2.front()==2);

    stl::list<std::string> alist3_op = alist3;
    assert(alist3_op.size()==n1);
    assert(stl::equal(alist3_op.begin(), alist3_op.end(), str));
}


void testListBeginEndCase1()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::list<double> list1(d1, d1+n1);
    *list1.begin() = 6.66666;
    assert(*list1.begin() == 6.66666);
    *(stl::prev(list1.end())) = 7.77777;
    assert(*(stl::prev(list1.end())) == 7.77777);

    const stl::list<double> &list1_ref = list1;
    assert(*list1_ref.begin() == list1.front());//begin()const
    assert(*(stl::prev(list1.end())) == list1.back());//end()const


    //*list1.cbegin() = 6.66666; //无法编译通过
    //*(stl::prev(list1.cend())) = 7.77777; //无法编译通过
    //*list1_ref.begin() = 6.66666; //无法编译通过
    //*(stl::prev(list1_ref.end())) = 7.77777; //无法编译通过

    //iterator 可以 初始化/赋值给 const iterator
    stl::list<double>::const_iterator const_it = list1.begin();
    const_it = list1.end();
    const_it = list1.cbegin();
    const_it = list1.cend();

    //测试const iterator
    //stl::list<double>::iterator non_const_it = list1.cbegin();//无法编译通过
    //stl::list<double>::iterator non_const_it = list1.cend();//无法编译通过
    //stl::list<double>::iterator non_const_it = list1_ref.begin();//无法编译通过
    //stl::list<double>::iterator non_const_it = list1_ref.end();//无法编译通过
}


void testListBeginEndCase2()
{
    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::list<double> alist1(d1, d1+n1);
    std::vector<double> vec1(d1, d1+n1);

    assert(vec1.size() == alist1.size());
    assert(stl::equal(alist1.rbegin(), alist1.rend(), vec1.rbegin()));
    assert(stl::equal(alist1.crbegin(), alist1.crend(), vec1.rbegin()));

    stl::list<double>::reverse_iterator non_const_it = alist1.rbegin();
    non_const_it = alist1.rend();

    stl::list<double>::const_reverse_iterator const_it = alist1.rbegin();
    const_it = alist1.rend();

    //测试const reverse itereator
    //non_const_it = alist1.crbegin();//无法编译通过
    //non_const_it = alist1.crend();//无法编译通过
}


template<typename T>
void testListSizeCase1(const T &val)
{
    stl::list<T> alist1;
    assert(alist1.empty() && alist1.size()==0);

    stl::list<T> alist2(9, val);
    assert(!alist2.empty() && alist2.size()==9);

    stl::list<T> alist3(&val, &val+1);
    assert(!alist3.empty() && alist3.size()==1);
}


void testListFrontBackCase1()
{
    stl::list<int> alist1(1, 4);
    assert(alist1.size()==1 && alist1.front()==4 && alist1.back()==4);
    alist1.front() = 5;
    assert(alist1.size()==1 && alist1.front()==5 && alist1.back()==5);
    alist1.back() = 6;
    assert(alist1.size()==1 && alist1.front()==6 && alist1.back()==6);

    const stl::list<int> &alist1_ref = alist1;
    assert(alist1_ref.front()==6 && alist1_ref.back()==6);
    //alist1_ref.front() = 7;//无法编译通过
    //alist1_ref.back() = 8;//无法编译通过



    double d1[] = { 2.3, 3,44, 1.56, 34.480, 3.14159, 0.126};
    size_t n1 = sizeof(d1)/sizeof(d1[0]);

    stl::list<double> alist2(d1, d1+n1);
    assert(alist2.size()==n1 && alist2.front()==d1[0] && alist2.back()==d1[n1-1]);
    alist2.front() = 1.25;
    assert(alist2.front()==1.25 && alist2.back()==d1[n1-1]);
}


void testListSwapCase1()
{
    stl::list<int> alist1;
    stl::list<int> alist2;
    alist1.swap(alist2);

    assert(alist1.empty() && alist2.empty());



    stl::list<double> alist3(1, 3.14);
    stl::list<double> alist4;
    assert(alist3.size()==1 && alist3.back()==3.14 && alist4.empty());
    alist3.swap(alist4);
    assert(alist3.empty() && alist4.size()==1 && alist4.back()==3.14);


    stl::list<int> alist5(1, 9);
    stl::list<int> alist6(1, 13);
    assert(alist5.size()==1 && alist5.front()==9 && alist6.size()==1 && alist6.back()==13);
    alist5.swap(alist6);
    assert(alist5.size()==1 && alist5.front()==13 && alist6.size()==1 && alist6.front()==9);


    int a1[] = {0, 1, 2, 3};
    int a2[] = {4, 5, 6, 7, 8, 9};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);

    stl::list<int> alist7(a1, a1+2);
    stl::list<int> alist8(a2, a2+n2);
    assert(alist7.size()==2 && alist8.size()==n2);

    alist7.swap(alist8);
    assert(alist7.size()==n2 && alist8.size()==2);
    assert(stl::equal(a2, a2+n2, alist7.begin()));
    assert(stl::equal(alist8.begin(), alist8.end(), a1));
}


void testListResizeCase1()
{
    stl::list<int> alist1;
    assert(alist1.empty());

    alist1.resize(4, 3);
    assert(alist1.size()==4 && stl::count(alist1.begin(), alist1.end(), 3)==4);

    alist1.resize(6, 9);
    assert(alist1.size()==6);
    assert(stl::count(alist1.begin(), stl::next(alist1.begin(), 4), 3) == 4);
    assert(stl::count(stl::next(alist1.begin(), 4), alist1.end(), 9) == 2);


    alist1.resize(2, 1);
    assert(alist1.size()==2 && alist1.front()==3 && alist1.back()==3);


    alist1.resize(0, 23);
    assert(alist1.empty());
}


template<typename T>
void testListClearCase1(const T &val)
{
    stl::list<T> alist1;
    assert(alist1.empty());

    alist1.clear();
    assert(alist1.empty());

    stl::list<T> alist2(3, val);
    assert(alist2.size()==3);
    alist2.clear();
    assert(alist2.empty());

}

//先测试insert，因assign和push都是调用insert
void testListInsertCase1()//测试insert N个值
{
    //测试void insert(iterator , size_type , const T &);
    stl::list<int> alist1;
    size_t num = 1;

    alist1.insert(alist1.begin(), num, 1);
    alist1.insert(alist1.end(), num, 4);
    alist1.insert(stl::next(alist1.begin()), num, 2);
    alist1.insert(stl::prev(alist1.end()), num, 3);
    alist1.insert(alist1.begin(), num, 0);

    stl::list<int>::iterator it = alist1.begin(), end = alist1.end();
    for(int i = 0; i < 5; )
    {
        assert(*it++ == i++);
    }

    alist1.clear();
    assert(alist1.empty() && alist1.begin() == alist1.end());



    alist1.insert(alist1.end(), 4, 4);
    alist1.insert(alist1.begin(), 2, 2);
    alist1.insert(stl::next(alist1.begin(), 2), 3, 3);
    alist1.insert(alist1.end(), 5, 5);
    alist1.insert(alist1.begin(), 1, 1);
    alist1.insert(alist1.begin(), 0, 0);

    assert(alist1.size() == 1 + 2 + 3 + 4 + 5);

    //alist1的内容为 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5
    it = alist1.begin();
    for(int i = 0; i < 6; ++i)
    {
        assert(stl::count(it, stl::next(it, i), i) == i);
        stl::advance(it, i);
    }
}


void testListInsertCase2()//测试iterator insert(iterator pos, const T &val);
{
    stl::list<int> alist;
    stl::list<int>::iterator it ;

    it = alist.insert(alist.end(), 1);
    assert(alist.size()==1 && *it == 1 && it == alist.begin());

    it = alist.insert(it, 0);
    assert(alist.size()==2 && it == alist.begin() && *it == 0 && alist.back()==1);

    it = alist.insert(stl::next(alist.begin()), 2);
    assert(alist.size()==3 && *it == 2);
    assert(alist.front()==0 && alist.back()==1);

    it = alist.insert(it, 3);
    assert(alist.size()==4 && *it == 3);
    assert(alist.front()==0 && alist.back()==1 && *++it == 2);

    alist.clear();
    assert(alist.empty());

    for(int i = 5; i > 0; --i)
    {
        it = alist.insert(alist.end(), i);
        assert(*it == i && it == stl::prev(alist.end()) && alist.size()==static_cast<size_t>(6-i));
    }

    it = alist.begin();
    for(int i = 5; i > 0; --i)
    {
        assert(*it++ == i);
    }



    alist.clear();
    assert(alist.empty());
    for(int i = 5; i > 0; --i)
    {
        it = alist.insert(alist.begin(), i);
        assert(*it == i && it == alist.begin() && alist.size()==static_cast<size_t>(6-i));
    }
    it = alist.begin();
    for(int i = 1; i < 6; ++i)
    {
        assert(*it++ == i);
    }
}



void testListInsertCase3()
{
    int a1[] = {0, 1, 2, 3, 7, 8, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    int a2[] = {4, 5, 6};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);


    stl::list<int> alist;
    alist.insert(alist.begin(), a1, a1);
    assert(alist.empty());
    alist.insert(alist.end(), a1, a1);
    assert(alist.empty());

    alist.insert(alist.begin(), a1, a1+2);
    assert(alist.size()==2 && alist.front()==a1[0] && alist.back()==a1[1]);

    alist.insert(alist.begin(), a1+2, a1+2);
    assert(alist.size()==2 && alist.front()==a1[0] && alist.back()==a1[1]);

    alist.insert(alist.end(), a1+2, a1+n1);
    assert(alist.size()==n1 && stl::equal(a1, a1+n1, alist.begin()));

    alist.insert(stl::next(alist.begin(), 4), a2, a2+n2);
    assert(alist.size() == n1+n2);

    stl::list<int>::iterator it = alist.begin(), end = alist.end();
    for(int i = 0; i < 10; ++i)
    {
        assert(*it++ == i);
    }
    assert(it == end);
}




//先测试erase，因为pop和assign都会调用erase
void testListEraseCase1()
{
    stl::list<int> alist1;
    assert(alist1.empty());
    alist1.erase(alist1.end());
    assert(alist1.empty());

    alist1.insert(alist1.end(), 1, 3);
    assert(alist1.size()==1 && alist1.back()==3);
    alist1.erase(alist1.end());
    assert(alist1.size()==1 && alist1.back()==3);
    stl::list<int>::iterator it = alist1.erase(alist1.begin());
    assert(alist1.empty() && it == alist1.end());
    alist1.erase(alist1.end());
    assert(alist1.empty());


    int a1[] = {1, 2, 3, 3, 4, 5, 6};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    alist1.insert(alist1.begin(), a1, a1+n1);

    it = alist1.erase(stl::next(alist1.begin(), 3));
    assert(*it == 4);

    std::list<int> alist2(a1, a1+n1);
    alist2.resize(alist1.size());
    stl::iota(alist2.begin(), alist2.end(), 1);
    assert(alist1.size() == alist2.size() && stl::equal(alist1.begin(), alist1.end(), alist2.begin()));


    alist1.erase(alist1.end());

    assert(alist1.size() == alist2.size());
    assert(stl::equal(alist1.begin(), alist1.end(), alist2.begin()));

    while( !alist1.empty() )
    {
        it = alist1.erase(alist1.begin());
        alist2.erase(alist2.begin());

        assert(alist1.size() == alist2.size() && it == alist1.begin());
        assert(stl::equal(alist1.begin(), alist1.end(), alist2.begin()));
    }
}


void testListEraseCase2()
{
    stl::list<int> alist1;
    alist1.erase(alist1.begin(), alist1.begin());
    assert(alist1.empty());
    alist1.erase(alist1.end(), alist1.end());
    assert(alist1.empty());


    alist1.insert(alist1.end(), 1, 2);
    assert(alist1.size()==1 && alist1.front()==2);
    alist1.erase(alist1.begin(), alist1.begin());
    assert(alist1.size()==1 && alist1.front()==2);
    alist1.erase(alist1.end(), alist1.end());
    assert(alist1.size()==1 && alist1.front()==2);

    stl::list<int>::iterator it = alist1.erase(alist1.begin(), alist1.end());
    assert(alist1.empty() && it == alist1.end());


    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    alist1.insert(alist1.begin(), a1, a1+n1);
    std::vector<int> vec(a1, a1+n1);

    assert(alist1.size() == n1 );

    //删除头一个节点
    it = alist1.erase(alist1.begin(), stl::next(alist1.begin()));
    vec.erase(vec.begin(), vec.begin()+1);
    assert(alist1.size() == vec.size() && it == alist1.begin());
    assert(stl::equal(vec.begin(), vec.end(), alist1.begin()));

    //删除头两个节点
    it = alist1.erase(alist1.begin(), stl::next(alist1.begin(), 2));
    vec.erase(vec.begin(), vec.begin()+2);
    assert(alist1.size() == vec.size() && it == alist1.begin());
    assert(stl::equal(vec.begin(), vec.end(), alist1.begin()));

    //删除中间几个节点
    it = alist1.erase(stl::next(alist1.begin(), 2), stl::next(alist1.begin(), 4));
    vec.erase(vec.begin()+2, vec.begin()+4);
    assert(alist1.size() == vec.size() && it == stl::next(alist1.begin(), 2));
    assert(stl::equal(vec.begin(), vec.end(), alist1.begin()));

    it = alist1.erase(stl::next(alist1.begin(), 3), alist1.end());
    vec.erase(vec.begin()+3, vec.end());
    assert(alist1.size() == vec.size() && it == alist1.end());
    assert(stl::equal(vec.begin(), vec.end(), alist1.begin()));

    it = alist1.erase(alist1.begin(), alist1.end());
    vec.erase(vec.begin(), vec.end());
    assert(alist1.empty() && it == alist1.end());
}


template<typename T>
void testListAssignCase1(const T &val, const T &value)
{
    stl::list<T> alist1;
    int i_num = 0;
    alist1.assign(i_num, val);
    assert(alist1.empty());

    i_num = 3;
    alist1.assign(i_num, val);//空list中调用assgin
    assert(alist1.size()==static_cast<size_t>(i_num) && stl::count(alist1.begin(), alist1.end(), val)==i_num);

    i_num = 4;
    alist1.assign(i_num, value);//非空list中调用assgin
    assert(alist1.size()==static_cast<size_t>(i_num) && stl::count(alist1.begin(), alist1.end(), value)==i_num);

    i_num = 0;
    alist1.assign(i_num, val);
    assert(alist1.empty());



    size_t num = 0;
    stl::list<T> alist2;
    alist2.assign(num, val);
    assert(alist2.empty());

    num = 2;
    alist2.assign(num, val);
    assert(alist2.size()==num && stl::count(alist2.begin(), alist2.end(), val)==static_cast<int>(num));

    num = 5;
    alist2.assign(num, value);
    assert(alist2.size()==num && stl::count(alist2.begin(), alist2.end(), value)==static_cast<int>(num));

    num = 0;
    alist2.assign(num, val);
    assert(alist2.empty());
}


template<typename T>
void testListAssignCase2(const T *a1, size_t n1)
{
    assert(n1 > 7);

    stl::list<T> alist1;
    alist1.assign(a1, a1);
    assert(alist1.empty());

    alist1.assign(a1, a1+2);
    assert(alist1.size() == 2);
    assert(stl::equal(alist1.begin(), alist1.end(), a1));

    alist1.assign(a1+3, a1+n1);
    assert(alist1.size() == n1-3);
    assert(stl::equal(alist1.begin(), alist1.end(), a1+3));

    alist1.assign(a1, a1);
    assert(alist1.empty());
}


template<typename T>
void testListPushPopCase1(const T *a1, size_t n1)
{
    stl::list<T> alist1;
    std::list<T> alist2;

    alist1.push_back(a1[0]);
    alist2.push_back(a1[0]);
    assert(alist1.size()==alist2.size() && stl::equal(alist1.begin(), alist1.end(), alist2.begin()));

    alist1.pop_front();
    alist2.pop_front();
    assert(alist1.empty());


    alist1.push_front(a1[0]);
    alist2.push_front(a1[0]);
    assert(alist1.size()==alist2.size() && stl::equal(alist1.begin(), alist1.end(), alist2.begin()));

    alist1.pop_back();
    alist2.pop_back();
    assert(alist1.empty());


    for(size_t i = 0; i < n1 -1; i += 2)
    {
        alist1.push_back(a1[i]);
        alist2.push_back(a1[i]);

        alist1.push_front(a1[i+1]);
        alist2.push_front(a1[i+1]);

        assert(alist1.size()==alist2.size() && stl::equal(alist1.begin(), alist1.end(), alist2.begin()));
    }


    alist1.pop_back();
    alist2.pop_back();
    alist1.push_back(a1[0]);
    alist2.push_back(a1[0]);

    alist1.pop_front();
    alist2.pop_front();
    alist1.push_front(a1[0]);
    alist2.push_front(a1[0]);



    assert(alist1.size()%2 == 0);
    while(!alist1.empty())
    {
        alist1.pop_back();
        alist2.pop_back();

        alist1.pop_front();
        alist2.pop_front();

        assert(alist1.size()==alist2.size() && stl::equal(alist1.begin(), alist1.end(), alist2.begin()));
    }

}


//无需测试remove_if，因为remove内部调用remove_if
void testListRemoveCase1()
{
    stl::list<int> alist;
    alist.remove(23);
    assert(alist.empty());

    alist.assign(3, 4);
    alist.remove(1);//remove不存在的
    assert(alist.size()==3 && stl::count(alist.begin(), alist.end(), 4)==3);

    alist.remove(4);//remove所有节点
    assert(alist.empty());

    int a1[] = {1, 1, 2, 3, 3, 3, 4, 5, 5, 6, 7, 7};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    alist.assign(a1, a1+n1);
    std::list<int> alist2(a1, a1+n1);

    alist.remove(3);//删除中间的多个节点
    alist2.remove(3);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));


    alist.remove(4);//删除中间的一个节点
    alist2.remove(4);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));


    alist.remove(1);//删除开始的多个节点
    alist2.remove(1);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));

    alist.remove(2);//删除开始的一个节点
    alist2.remove(2);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));


    alist.remove(7);//删除结尾的多个节点
    alist2.remove(7);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));


    alist.remove(6);//删除结尾的一个节点
    alist2.remove(6);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));



    int a2[] = {1, 2, 2, 1, 1, 3, 1, 4, 4, 1, 1, 1, 5, 1, 1};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    alist.assign(a2, a2+n2);
    alist2.assign(a2, a2+n2);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));

    alist.remove(1);//删除多处存在的值
    alist2.remove(1);
    assert(alist.size()==alist2.size() && stl::equal(alist.begin(), alist.end(), alist2.begin()));
}



void testListUniqueCase1()
{
    int a1[] = {1, 1, 2, 3, 3, 3, 4, 5, 5, 6, 7, 7};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    stl::list<int> alist(a1, a1+n1);

    alist.unique();

    stl::list<int>::iterator it = alist.begin(), end = alist.end();
    for(int i = 1; i < 8; ++i)
    {
        assert(*it++ = i);
    }
    assert(it == end);


    alist.assign(3, 1);//测试只有一种取值的情况
    alist.unique();
    assert(alist.size()==1 && alist.back()==1);

    alist.unique();
    assert(alist.size()==1 && alist.back()==1);


    alist.push_back(2);
    alist.push_back(3);
    assert(alist.size()==3);
    alist.unique();//测试没有重复的节点 unqiue情况
    it = alist.begin(), end = alist.end();
    for(int i = 1; i < 4; ++i)
    {
        assert(*it++ = i);
    }
    assert(it == end);
}


void testListMergeCase1()
{
    stl::list<int> alist1;
    stl::list<int> alist2;

    alist1.merge(alist2);//两个空list进行merge
    assert(alist1.empty() && alist2.empty());

    alist2.push_back(1);
    alist1.merge(alist2);//空list merge有节点的list
    assert(alist1.size()==1 && alist1.front()==1 && alist2.empty());

    alist1.merge(alist2);//merge一个空的list
    assert(alist1.size()==1 && alist1.front()==1 && alist2.empty());

    alist2.push_back(2);
    alist1.merge(alist2);
    assert(alist1.size()==2 && alist1.front()==1 && alist1.back()==2 && alist2.empty());
}


void testListMergeCase2()
{
    stl::list<int> alist1(3, 1);
    stl::list<int> alist2(4, 2);

    alist1.merge(alist2);
    assert(alist1.size()==7 && alist2.empty());
    assert(stl::count(alist1.begin(), stl::next(alist1.begin(), 3), 1) == 3);
    assert(stl::count(stl::next(alist1.begin(), 3), alist1.end(), 2) == 4);

    alist2.assign(1, 0);
    alist1.merge(alist2);
    assert(alist1.size()==8 && alist2.empty() && alist1.front()==0);
    assert(stl::count(stl::next(alist1.begin()), stl::next(alist1.begin(), 4), 1) == 3);
    assert(stl::count(stl::next(alist1.begin(), 4), alist1.end(), 2) == 4);


    int a4[] = {1, 1, 2, 3, 5, 8, 13, 15, 16, 21};
    int a5[] = {1, 2, 13, 13};
    int a6[] = {1, 1, 3, 21, 23, 24};

    size_t n4 = sizeof(a4)/sizeof(a4[0]);
    size_t n5 = sizeof(a5)/sizeof(a5[0]);
    size_t n6 = sizeof(a6)/sizeof(a6[0]);

    alist1.assign(a4, a4+n4);
    alist2.assign(a5, a5+n5);
    assert(alist1.size()==n4 && stl::equal(a4, a4+n4, alist1.begin()));
    assert(alist2.size()==n5 && stl::equal(a5, a5+n5, alist2.begin()));

    alist1.merge(alist2);//被merge的链表先结束
    std::list<int> std_list(a4, a4+n4);
    std_list.insert(std_list.end(), a5, a5+n5);
    std_list.sort();

    assert(alist1.size() == n4+n5 && alist2.empty() && std_list.size()==n4+n5);
    assert(stl::equal(alist1.begin(), alist1.end(), std_list.begin()));

    alist2.assign(a6, a6+n6);
    alist1.merge(alist2);//主动merge的链表先结束
    std_list.insert(std_list.end(), a6, a6+n6);
    std_list.sort();

    assert(alist1.size()==n4+n5+n6 && alist2.empty() && std_list.size()==n4+n5+n6);
    assert(stl::equal(alist1.begin(), alist1.end(), std_list.begin()));
}


void testListReverseCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    stl::list<int> alist1;
    alist1.reverse();
    assert(alist1.empty());

    alist1.push_back(1);//1
    alist1.reverse();//1
    assert(alist1.size()==1 && alist1.front()==1);

    alist1.push_back(2);// 1, 2
    assert(alist1.front()==1 && alist1.back()==2);
    alist1.reverse();//2, 1
    assert(alist1.size()==2 && alist1.front()==2 && alist1.back()==1);

    alist1.push_front(3);//3, 2, 1
    alist1.reverse();//1, 2, 3
    assert(alist1.size()==3 && stl::equal(a1, a1+3, alist1.begin()));

    alist1.push_back(4);//1, 2, 3, 4
    alist1.reverse();//4, 3, 2, 1
    assert(alist1.size()==4 && stl::equal(a1, a1+4, alist1.rbegin()));

    stl::list<int> alist2(a1, a1+n1);
    alist2.reverse();
    assert(stl::equal(a1, a1+n1, alist2.rbegin()));
}



void testListSpliceCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    stl::list<int> alist1(a1, a1+4);
    alist1.push_front(5);

    alist1.splice(alist1.begin(), alist1, stl::next(alist1.begin()), alist1.end());
    assert(alist1.size()==5 && stl::equal(a1, a1+5, alist1.begin()));

    alist1.push_front(6);
    alist1.splice(alist1.end(), alist1, alist1.begin());
    assert(alist1.size()==6 && stl::equal(a1, a1+6, alist1.begin()));

    stl::list<int>::iterator it;
    it = alist1.insert(stl::next(alist1.begin(), 3), 7);//1, 2, 3, 7, 4, 5, 6

    alist1.splice(it, alist1, stl::next(it), alist1.end());
    assert(alist1.size()==7 && stl::equal(a1, a1+7, alist1.begin()));


    int a2[] = {1, 2, 5, 6, 3, 4, 7, 8, 9};
    size_t n2 = sizeof(a1)/sizeof(a1[0]);
    stl::list<int> alist2(a2, a2+n2);

    alist2.splice(stl::next(alist2.begin(), 2), alist2, stl::next(alist2.begin(), 4), stl::next(alist2.begin(), 6));
    assert(alist2.size()==n2 && stl::equal(a1, a1+n1, alist2.begin()));


    alist1.clear();
    assert(alist1.empty());
    alist1.splice(alist1.begin(), alist2);
    assert(alist2.empty() && alist1.size()==n1);
    assert(stl::equal(a1, a1+n1, alist1.begin()));

    alist2.splice(alist2.end(), alist1, alist1.begin());
    assert(alist2.size()==1 && alist2.front()==1);
    assert(alist1.size()==n1-1 && stl::equal(a1+1, a1+n1, alist1.begin()));

    alist2.splice(alist2.end(), alist1);
    assert(alist1.empty() && alist2.size()==n1);
    assert(stl::equal(a1, a1+n1, alist2.begin()));

    alist1.assign(a2, a2+6);//1, 2, 5, 6, 3, 4,
    alist2.assign(a2+6, a2+n2);//7, 8, 9

    //从中间偷几个节点
    alist2.splice(alist2.begin(), alist1, stl::next(alist1.begin(), 2), stl::next(alist1.begin(), 4));
    assert(alist1.size()==4 && stl::equal(a1, a1+4, alist1.begin()));
    assert(alist2.size()==5 && stl::equal(a1+4, a1+n1, alist2.begin()));
}


void testListSortCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    stl::list<int> alist1;
    alist1.sort();
    assert(alist1.empty());

    alist1.push_back(1);
    alist1.sort();
    assert(alist1.size()==1 && alist1.front()==1);


    alist1.push_back(2);
    alist1.sort();//已经有序
    assert(alist1.size()==2 && alist1.front()==1 && alist1.back()==2);
    alist1.pop_back();
    assert(alist1.size()==1 && alist1.front()==1);


    alist1.push_front(2);//逆序
    alist1.sort();
    assert(alist1.size()==2 && alist1.front()==1 && alist1.back()==2);


    alist1.push_front(3);//3, 1, 2
    alist1.sort();
    assert(alist1.size()==3 && stl::equal(a1, a1+3, alist1.begin()));

    alist1.push_back(4);//4, 1, 2, 3
    alist1.insert(stl::next(alist1.begin(), 2), 5);//4, 1, 5, 2, 3
    alist1.sort();
    assert(alist1.size()==5 && stl::equal(a1, a1+5, alist1.begin()));

    alist1.push_front(6);//6, 1, 2, 3, 4, 5
    alist1.push_back(7);//6, 1, 2, 3, 4, 5, 7
    alist1.sort();
    assert(alist1.size()==7 && stl::equal(a1, a1+7, alist1.begin()));

    alist1.insert(stl::next(alist1.begin(), 3), 8);//1, 2, 3, 8, 4, 5, 6, 7
    alist1.insert(stl::next(alist1.begin(), 3), 9);//1, 2, 3, 9, 8, 4, 5, 6, 7
    alist1.sort();
    assert(alist1.size()==9 && stl::equal(a1, a1+9, alist1.begin()));

    alist1.reverse();
    assert(alist1.size()==9 && stl::equal(a1, a1+9, alist1.rbegin()));
    alist1.sort();
    assert(alist1.size()==9 && stl::equal(a1, a1+9, alist1.begin()));

    alist1.assign(a1, a1+n1);
    alist1.sort();
    assert(alist1.size()==9 && stl::equal(a1, a1+9, alist1.begin()));
}


inline int randNum()
{
    return rand()%100;
}

template<int SIZE>
void testListSortCase2()
{
    srand(time(NULL) + rand());

    std::vector<int> vec;
    stl::list<int> alist1;

    stl::generate_n(stl::back_inserter(vec), SIZE, randNum);
    alist1.assign(&vec[0], &vec[0]+vec.size());

    alist1.sort();
    std::sort(vec.begin(), vec.end());

    assert(alist1.size()==vec.size() && stl::equal(alist1.begin(), alist1.end(), vec.begin()));
}

//===========================================================================




void testList()
{
    testListConstructorCase1<int>();
    testListConstructorCase1<double>();
    testListConstructorCase1<char>();
    testListConstructorCase1<std::string>();


    testListConstructorCase2<int>(23);
    testListConstructorCase2<size_t>(33);
    testListConstructorCase2<double>(3.14159);
    testListConstructorCase2<char>('d');
    testListConstructorCase2<std::string>("TinySTL");


    testListConstructorCase3();

    testListCopyConstructorAndOperatorAssignCase1();


    testListBeginEndCase1();
    testListBeginEndCase2();


    testListSizeCase1<int>(1);
    testListSizeCase1<size_t>(23);
    testListSizeCase1<double>(2.718281828);
    testListSizeCase1<char>('G');
    testListSizeCase1<std::string>("C++");


    testListFrontBackCase1();

    testListSwapCase1();

    testListResizeCase1();


    testListInsertCase1();
    testListInsertCase2();
    testListInsertCase3();


    testListEraseCase1();
    testListEraseCase2();


    testListAssignCase1<int>(56, 3);
    testListAssignCase1<size_t>(78, 108);
    testListAssignCase1<char>('G', 'F');
    testListAssignCase1<std::string>("C++", "Python");

    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    std::string str[] = {"a", "bb", "ccc", "dddd", "ee", "ff", "gg", "hh", "JJ", "KK"};
    size_t n2 = sizeof(str)/sizeof(str[0]);

    testListAssignCase2<int>(a1, n1);
    testListAssignCase2<std::string>(str, n2);



    testListPushPopCase1<int>(a1, n1);
    testListPushPopCase1<std::string>(str, n2);


    testListRemoveCase1();

    testListUniqueCase1();

    testListMergeCase1();
    testListMergeCase2();


    testListReverseCase1();


    testListSpliceCase1();

    testListSortCase1();
    testListSortCase2<1>();
    testListSortCase2<2>();
    testListSortCase2<3>();
    testListSortCase2<5>();
    testListSortCase2<8>();
    testListSortCase2<12>();
    testListSortCase2<15>();
    testListSortCase2<16>();
    testListSortCase2<20>();
    testListSortCase2<30>();
    testListSortCase2<50>();
    testListSortCase2<80>();
    testListSortCase2<100>();
    testListSortCase2<200>();
    testListSortCase2<500>();
    testListSortCase2<1000>();
}

}
