//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testHeap.h"


#include"../bits/stl_heap.h"

#include<assert.h>
#include<time.h>
#include<stdlib.h>


#include<string>
#include<algorithm>


#include"../vector"
#include"../algorithm"


namespace stl
{


static stl::vector<std::string> generateRandomString(size_t n)
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


static stl::vector<int> generateRandomInt(size_t n)
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



void testHeapIsHeapCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7 };
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(is_heap(a1, a1+n1, stl::greater<int>()));
    assert(!is_heap(a1, a1+n1));

    a1[0] = 2;
    assert(is_heap(a1, a1+n1, stl::greater_equal<int>()));
    assert(!is_heap(a1, a1+n1));


    a1[1] = 1;
    assert(!is_heap(a1, a1+n1, stl::greater<int>()));
    assert(!is_heap(a1, a1+n1));


    int a2[] = {10, 9, 12, 8, 7, 5, 4};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    assert(!is_heap(a2, a2+n2, stl::greater<int>()));
    assert(!is_heap(a2, a2+n2));


    a2[2] = 6;
    assert(!is_heap(a2, a2+n2, stl::greater<int>()));
    assert(is_heap(a2, a2+n2));



    stl::vector<int> vec(a2, a2+2);
    assert(is_heap(vec.begin(), vec.end()));

    vec[1] = vec[0];
    assert(is_heap(vec.begin(), vec.end()));//use stl::less_equal
    assert(!is_heap(vec.begin(), vec.end(), stl::less<int>()));
}



void testHeapIsHeapSubCase2(const stl::vector<int> &vec1)
{
    stl::vector<int> vec2 = vec1;

    make_heap(vec2.begin(), vec2.end());
    assert((is_heap(vec1.begin(), vec1.end()) && vec1==vec2) || (!is_heap(vec1.begin(), vec1.end()) && vec1 != vec2) );
}



void testHeapIsHeapCase2()
{
    testHeapIsHeapSubCase2(generateRandomInt(1));
    testHeapIsHeapSubCase2(generateRandomInt(2));
    testHeapIsHeapSubCase2(generateRandomInt(3));
    testHeapIsHeapSubCase2(generateRandomInt(4));
    testHeapIsHeapSubCase2(generateRandomInt(5));
    testHeapIsHeapSubCase2(generateRandomInt(6));
    testHeapIsHeapSubCase2(generateRandomInt(7));
    testHeapIsHeapSubCase2(generateRandomInt(8));
    testHeapIsHeapSubCase2(generateRandomInt(9));
    testHeapIsHeapSubCase2(generateRandomInt(10));
    testHeapIsHeapSubCase2(generateRandomInt(16));
    testHeapIsHeapSubCase2(generateRandomInt(22));
    testHeapIsHeapSubCase2(generateRandomInt(31));
    testHeapIsHeapSubCase2(generateRandomInt(32));
    testHeapIsHeapSubCase2(generateRandomInt(48));
    testHeapIsHeapSubCase2(generateRandomInt(69));
    testHeapIsHeapSubCase2(generateRandomInt(86));
    testHeapIsHeapSubCase2(generateRandomInt(100));
    testHeapIsHeapSubCase2(generateRandomInt(126));
    testHeapIsHeapSubCase2(generateRandomInt(255));
    testHeapIsHeapSubCase2(generateRandomInt(256));
    testHeapIsHeapSubCase2(generateRandomInt(257));
}



template<typename T>
void testHeapMakeHeapSubCase1(const T *arr, size_t n)
{
    stl::vector<T> vec(arr, arr+n);
    stl::vector<T> vec2(arr, arr+n);

    std::make_heap(vec.begin(), vec.end());
    stl::make_heap(vec2.begin(), vec2.end());

    assert(vec == vec2);
    assert(stl::is_heap(vec2.begin(), vec2.end()));
}



void testHeapMakeHeapCase1()
{
    int arr[] = {40, 13, 11, 62, 62, 12, 23};
    size_t n1 = sizeof(arr)/sizeof(arr[0]);
    testHeapMakeHeapSubCase1(arr, n1);

    stl::vector<int> vec1 = generateRandomInt(16);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(1);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(2);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(3);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(4);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(5);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(6);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(7);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(8);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());


    vec1 = generateRandomInt(31);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomInt(45);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    int a[] = {27, 33, 73, 75, 90, 10, 64, 74, 94, 65, 87, 55, 11, 48, 49, 45, 81, 9, 3, 91, 46, 90, 64, 22, 63, 32, 10, 60, 60, 98};
    size_t n = sizeof(a)/sizeof(a[0]);
    testHeapMakeHeapSubCase1(a, n);
}


void testHeapMakeHeapCase2()
{
    stl::vector<std::string> vec1 = generateRandomString(16);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(1);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(2);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(3);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(4);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(5);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(6);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(7);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(8);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());


    vec1 = generateRandomString(31);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());

    vec1 = generateRandomString(45);
    testHeapMakeHeapSubCase1(vec1.data(), vec1.size());
}



void testHeapPushHeapCase1SubCase1(stl::vector<int> vec)
{
    stl::vector<int>::iterator it = vec.begin()+1;

    while( it < vec.end() )
    {
        stl::push_heap(vec.begin(), it);
        assert(is_heap(vec.begin(), it));
        ++it;
    }
}


void testHeapPushHeapCase1()
{
    testHeapPushHeapCase1SubCase1(generateRandomInt(1));
    testHeapPushHeapCase1SubCase1(generateRandomInt(2));
    testHeapPushHeapCase1SubCase1(generateRandomInt(3));
    testHeapPushHeapCase1SubCase1(generateRandomInt(4));
    testHeapPushHeapCase1SubCase1(generateRandomInt(5));
    testHeapPushHeapCase1SubCase1(generateRandomInt(6));
    testHeapPushHeapCase1SubCase1(generateRandomInt(7));
    testHeapPushHeapCase1SubCase1(generateRandomInt(8));
    testHeapPushHeapCase1SubCase1(generateRandomInt(9));
    testHeapPushHeapCase1SubCase1(generateRandomInt(10));
    testHeapPushHeapCase1SubCase1(generateRandomInt(15));
    testHeapPushHeapCase1SubCase1(generateRandomInt(16));
    testHeapPushHeapCase1SubCase1(generateRandomInt(17));
    testHeapPushHeapCase1SubCase1(generateRandomInt(28));
    testHeapPushHeapCase1SubCase1(generateRandomInt(42));
    testHeapPushHeapCase1SubCase1(generateRandomInt(66));
    testHeapPushHeapCase1SubCase1(generateRandomInt(72));
    testHeapPushHeapCase1SubCase1(generateRandomInt(92));
    testHeapPushHeapCase1SubCase1(generateRandomInt(127));
    testHeapPushHeapCase1SubCase1(generateRandomInt(234));
    testHeapPushHeapCase1SubCase1(generateRandomInt(256));
    testHeapPushHeapCase1SubCase1(generateRandomInt(511));
}



void testHeapPopHeapCase1SubCase1(stl::vector<int> vec)
{
    stl::make_heap(vec.begin(), vec.end());

    while(!vec.empty())
    {
        int top = vec.front();
        stl::pop_heap(vec.begin(), vec.end());
        assert(top == vec.back());
        vec.pop_back();
        assert(is_heap(vec.begin(), vec.end()));
    }
}



void testHeapPopHeapCase1()
{
    testHeapPopHeapCase1SubCase1(generateRandomInt(1));
    testHeapPopHeapCase1SubCase1(generateRandomInt(2));
    testHeapPopHeapCase1SubCase1(generateRandomInt(3));
    testHeapPopHeapCase1SubCase1(generateRandomInt(4));
    testHeapPopHeapCase1SubCase1(generateRandomInt(5));
    testHeapPopHeapCase1SubCase1(generateRandomInt(6));
    testHeapPopHeapCase1SubCase1(generateRandomInt(7));
    testHeapPopHeapCase1SubCase1(generateRandomInt(8));
    testHeapPopHeapCase1SubCase1(generateRandomInt(9));
    testHeapPopHeapCase1SubCase1(generateRandomInt(10));
    testHeapPopHeapCase1SubCase1(generateRandomInt(11));
    testHeapPopHeapCase1SubCase1(generateRandomInt(15));
    testHeapPopHeapCase1SubCase1(generateRandomInt(16));
    testHeapPopHeapCase1SubCase1(generateRandomInt(17));
    testHeapPopHeapCase1SubCase1(generateRandomInt(24));
    testHeapPopHeapCase1SubCase1(generateRandomInt(36));
    testHeapPopHeapCase1SubCase1(generateRandomInt(63));
    testHeapPopHeapCase1SubCase1(generateRandomInt(178));
    testHeapPopHeapCase1SubCase1(generateRandomInt(256));
    testHeapPopHeapCase1SubCase1(generateRandomInt(312));
    testHeapPopHeapCase1SubCase1(generateRandomInt(444));
    testHeapPopHeapCase1SubCase1(generateRandomInt(512));
    testHeapPopHeapCase1SubCase1(generateRandomInt(516));
    testHeapPopHeapCase1SubCase1(generateRandomInt(517));
}




void testHeapSortHeapCase1SubCase1(stl::vector<int> vec)
{
    stl::make_heap(vec.begin(), vec.end());
    stl::sort_heap(vec.begin(), vec.end());

    assert(stl::is_sorted(vec.begin(), vec.end()));
}


void testHeapSortHeapCase1()
{
    testHeapSortHeapCase1SubCase1(generateRandomInt(1));
    testHeapSortHeapCase1SubCase1(generateRandomInt(2));
    testHeapSortHeapCase1SubCase1(generateRandomInt(3));
    testHeapSortHeapCase1SubCase1(generateRandomInt(4));
    testHeapSortHeapCase1SubCase1(generateRandomInt(5));
    testHeapSortHeapCase1SubCase1(generateRandomInt(6));
    testHeapSortHeapCase1SubCase1(generateRandomInt(7));
    testHeapSortHeapCase1SubCase1(generateRandomInt(8));
    testHeapSortHeapCase1SubCase1(generateRandomInt(9));
    testHeapSortHeapCase1SubCase1(generateRandomInt(10));
    testHeapSortHeapCase1SubCase1(generateRandomInt(29));
    testHeapSortHeapCase1SubCase1(generateRandomInt(37));
    testHeapSortHeapCase1SubCase1(generateRandomInt(41));
    testHeapSortHeapCase1SubCase1(generateRandomInt(52));
    testHeapSortHeapCase1SubCase1(generateRandomInt(68));
    testHeapSortHeapCase1SubCase1(generateRandomInt(83));
    testHeapSortHeapCase1SubCase1(generateRandomInt(93));
    testHeapSortHeapCase1SubCase1(generateRandomInt(109));
    testHeapSortHeapCase1SubCase1(generateRandomInt(263));
    testHeapSortHeapCase1SubCase1(generateRandomInt(571));
    testHeapSortHeapCase1SubCase1(generateRandomInt(622));
    testHeapSortHeapCase1SubCase1(generateRandomInt(899));
    testHeapSortHeapCase1SubCase1(generateRandomInt(911));
}

//================================================================================

void testHeap()
{
    testHeapIsHeapCase1();
    testHeapIsHeapCase2();

    testHeapMakeHeapCase1();
    testHeapMakeHeapCase2();


    testHeapPushHeapCase1();

    testHeapPopHeapCase1();


    testHeapSortHeapCase1();
}



}

