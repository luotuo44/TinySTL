//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#include"testAlgo.h"

#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include<vector>
#include<iterator>
#include<string>
#include<algorithm>
#include<iostream>
#include<set>
#include<functional>

#include"../bits/stl_algo.h"
#include"../iterator"
#include"../type_traits"
#include"../list"



namespace stl
{

void testSetOpCase1()
{
    int a1[] = {1, 3, 5, 7, 9, 11};
    int a2[] = {1, 1, 2, 3, 5, 8, 13};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    size_t n2 = sizeof(a2)/sizeof(a2[0]);

    std::vector<int> vec1;
    std::vector<int> vec2;

    stl::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();

    //=================================

    stl::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();

    stl::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();

    //=================================

    stl::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec1));
    std::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec1), std::less<int>());
    std::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    //=================================

    stl::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();
}


void testSetOpCase2()
{
    int a1[] = {1, 3, 5, 7, 9, 11};
    int a2[] = {1, 2, 3, 5, 8, 9, 13};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    size_t n2 = sizeof(a2)/sizeof(a2[0]);

    std::vector<int> vec1;
    std::vector<int> vec2;

    stl::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_union(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    //=================================

    stl::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_intersection(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();

    //=================================

    stl::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec1));
    std::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec1), std::less<int>());
    std::set_difference(a2, a2+n2, a1, a1+n1, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    //=================================

    stl::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1));
    std::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2));
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();


    stl::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec1), std::less<int>());
    std::set_symmetric_difference(a1, a1+n1, a2, a2+n2, std::back_inserter(vec2), std::less<int>());
    assert(vec1 == vec2);
    vec1.clear();
    vec2.clear();
}




void testAdjacentFindCase1()
{
    int arr[] = {1, 2, 5, 3, 3, 4, 5};
    assert(adjacent_find(arr, arr+7) == arr+3);

    assert(adjacent_find(arr, arr) == arr);
    assert(adjacent_find(arr, arr+1) == arr+1);
    assert(adjacent_find(arr, arr+3) == arr+3);
    assert(adjacent_find(arr, arr+4) == arr+4);
}


void testAdjacentFindCase2()
{
    int arr[] = {1, 2, 5, 3, 3, 4, 5};
    assert(stl::adjacent_find(arr, arr+7, std::equal_to<int>()) == arr+3);

    assert(stl::adjacent_find(arr, arr, std::equal_to<int>()) == arr);
    assert(stl::adjacent_find(arr, arr+1, std::equal_to<int>()) == arr+1);
    assert(stl::adjacent_find(arr, arr+4, std::equal_to<int>()) == arr+4);

    assert(stl::adjacent_find(arr, arr+7, std::greater<int>()) == arr+2);
    assert(stl::adjacent_find(arr, arr+2, std::less<int>()) == arr);
}


void testCountCase1()
{
    std::vector<int> vec;
    vec.reserve(1010);
    srand(time(NULL) + rand());
    for(int i = 0; i < 1010; ++i)
        vec.push_back(rand()%50);

    assert(stl::count(vec.begin(), vec.end(), 10) == std::count(vec.begin(), vec.end(), 10));
    assert(stl::count(vec.begin(), vec.end(), 139) == std::count(vec.begin(), vec.end(), 139));

    assert(stl::count(vec.begin(), vec.begin(), 10) == 0);
}


void testCountIfCase1()
{
    std::vector<int> vec;
    vec.reserve(1010);
    srand(time(NULL) + rand());
    for(int i = 0; i < 1010; ++i)
        vec.push_back(rand()%50);

    assert(stl::count_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 10))
           == std::count_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 10)));

    assert(stl::count_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 130))
           == std::count_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 130)));

    assert(stl::count_if(vec.begin(), vec.begin(), std::bind2nd(std::equal_to<int>(), 10)) == 0);
}


void testFindCase1()
{
    std::vector<int> vec;
    vec.reserve(1010);
    srand(time(NULL) + rand());
    for(int i = 0; i < 1010; ++i)
        vec.push_back(rand()%50);

    assert(stl::find(vec.begin(), vec.end(), 9) == std::find(vec.begin(), vec.end(), 9));
    assert(stl::find(vec.begin(), vec.end(), 17) == std::find(vec.begin(), vec.end(), 17));
    assert(stl::find(vec.begin(), vec.end(), 100) == std::find(vec.begin(), vec.end(), 100));

    assert(stl::find(vec.begin(), vec.begin(), 8) == vec.begin());
}



void testFindIfCase2()
{
    std::vector<int> vec;
    vec.reserve(1010);
    srand(time(NULL) + rand());
    for(int i = 0; i < 1010; ++i)
        vec.push_back(rand()%50);


    assert(stl::find_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 16))
           == std::find_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 16)));

    assert(stl::find_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 160))
           == std::find_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<int>(), 160)));


    assert(stl::find_if(vec.begin(), vec.begin(), std::bind1st(std::equal_to<int>(), 14)) == vec.begin());
}


void testFindFirstOfCase1()
{
    std::string str("Hello, This is C++ world!");

    std::string s_str1("Java");
    std::string s_str2("C#");

    assert(stl::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.end())
           == std::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.end()));

    assert(stl::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.end())
           == std::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.end()));


    assert(stl::find_first_of(str.begin(), str.begin(), s_str1.begin(), s_str1.end())
           == std::find_first_of(str.begin(), str.begin(), s_str1.begin(), s_str1.end()));

    assert(stl::find_first_of(str.begin(), str.begin(), s_str2.begin(), s_str2.end())
           == std::find_first_of(str.begin(), str.begin(), s_str2.begin(), s_str2.end()));


    assert(stl::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.begin())
           == std::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.begin()));

    assert(stl::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.begin())
           == std::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.begin()));

}




void testFindFirstOfCase2()
{
    std::string str("Hello, This is C++ world!");

    std::string s_str1("Java");
    std::string s_str2("C#");

    assert(stl::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.end(), std::equal_to<char>())
           == std::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.end(), std::equal_to<char>()));

    assert(stl::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.end(), std::equal_to<char>())
           == std::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.end(), std::equal_to<char>()));


    assert(stl::find_first_of(str.begin(), str.begin(), s_str1.begin(), s_str1.end(), std::equal_to<char>())
           == std::find_first_of(str.begin(), str.begin(), s_str1.begin(), s_str1.end(), std::equal_to<char>()));

    assert(stl::find_first_of(str.begin(), str.begin(), s_str2.begin(), s_str2.end(), std::equal_to<char>())
           == std::find_first_of(str.begin(), str.begin(), s_str2.begin(), s_str2.end(), std::equal_to<char>()));



    assert(stl::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.begin(), std::equal_to<char>())
           == std::find_first_of(str.begin(), str.end(), s_str1.begin(), s_str1.begin(), std::equal_to<char>()));

    assert(stl::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.begin(), std::equal_to<char>())
           == std::find_first_of(str.begin(), str.end(), s_str2.begin(), s_str2.begin(), std::equal_to<char>()));
}


template<typename Container, typename T>
class ContainerPushBack
{
public:

    ContainerPushBack(Container & con)
        : m_con(con)
    {}

    void operator()(const T &val)
    {
        m_con.push_back(val);
    }

private:
    Container &m_con;
};


void testForeachCase1()
{
    srand(time(NULL) + rand());
    std::vector<int> vec1;
    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
    }


    std::vector<int> vec2;
    ContainerPushBack<std::vector<int>, int> cp(vec2);

    stl::for_each(vec1.begin(), vec1.end(), cp);

    assert(vec1 == vec2);
}


struct RandomNumber
{
    RandomNumber(int seed)
    {
        srand(seed);
    }

    int operator ()()
    {
        return rand()%1000;
    }
};


void testGenerateCase1()
{
    std::vector<int> vec1, vec2;
    vec1.resize(100);
    vec2.resize(100);

    stl::generate(vec1.begin(), vec1.end(), RandomNumber(34));
    std::generate(vec2.begin(), vec2.end(), RandomNumber(34));
    assert(vec1 == vec2);


    vec1.resize(1);
    vec2.resize(1);
    stl::generate(vec1.begin(), vec1.end(), RandomNumber(7834));
    std::generate(vec2.begin(), vec2.end(), RandomNumber(7834));
    assert(vec1 == vec2);
}


void testGenerateCase2()
{
    std::vector<int> vec1, vec2;

    stl::generate_n(std::back_inserter(vec1), 22, RandomNumber(334));
    std::generate_n(std::back_inserter(vec2), 22, RandomNumber(334));
    assert(vec1 == vec2);



    stl::generate_n(std::back_inserter(vec1), 34, RandomNumber(74));
    std::generate_n(std::back_inserter(vec2), 34, RandomNumber(74));
    assert(vec1 == vec2);
}


void testIncludesCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7};
    int a2[] = {1, 4, 7};
    int a3[] = {2, 7, 9};

    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    size_t n3 = sizeof(a3)/sizeof(a3[0]);

    assert(includes(a1, a1+n1, a2, a2+n2));
    assert(includes(a1, a1+n1, a3, a3+n3) == false);

    assert(includes(a1, a1+n1, a2, a2));


    int a4[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int a5[] = {1, 2, 13, 13};
    int a6[] = {1, 1, 3, 21};

    size_t n4 = sizeof(a4)/sizeof(a4[0]);
    size_t n5 = sizeof(a5)/sizeof(a5[0]);
    size_t n6 = sizeof(a6)/sizeof(a6[0]);

    assert(includes(a4, a4+n4, a5, a5+n5) ==false);
    assert(includes(a4, a4+n4, a6, a6+n6));
}



void testIncludesCase2()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7};
    int a2[] = {1, 4, 7};
    int a3[] = {2, 7, 9};

    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    size_t n3 = sizeof(a3)/sizeof(a3[0]);

    assert(stl::includes(a1, a1+n1, a2, a2+n2, std::less<int>()));
    assert(stl::includes(a1, a1+n1, a3, a3+n3, std::less<int>()) == false);

    assert(stl::includes(a1, a1+n1, a2, a2, std::less<int>()));


    int a4[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int a5[] = {1, 2, 13, 13};
    int a6[] = {1, 1, 3, 21};

    size_t n4 = sizeof(a4)/sizeof(a4[0]);
    size_t n5 = sizeof(a5)/sizeof(a5[0]);
    size_t n6 = sizeof(a6)/sizeof(a6[0]);

    assert(stl::includes(a4, a4+n4, a5, a5+n5, std::less<int>()) ==false);
    assert(stl::includes(a4, a4+n4, a6, a6+n6, std::less<int>()));
}


void testMergeCase1()
{
    int a4[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int a5[] = {1, 2, 13, 13};
    int a6[] = {1, 1, 3, 21};

    size_t n4 = sizeof(a4)/sizeof(a4[0]);
    size_t n5 = sizeof(a5)/sizeof(a5[0]);
    size_t n6 = sizeof(a6)/sizeof(a6[0]);

    int dst1[100];
    int dst2[100];

    int *dd1 = stl::merge(a4, a4+n4, a5, a5+n5, dst1);
    std::merge(a4, a4+n4, a5, a5+n5, dst2);
    assert(std::equal(dst1, dd1, dst2));

    dd1 = stl::merge(a4, a4+n4, a6, a6+n5, dst1);
    std::merge(a4, a4+n4, a6, a6+n6, dst2);
    assert(std::equal(dst1, dd1, dst2));

}


void testMergeCase2()
{
    int a4[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int a5[] = {1, 2, 13, 13};
    int a6[] = {1, 1, 3, 21};

    size_t n4 = sizeof(a4)/sizeof(a4[0]);
    size_t n5 = sizeof(a5)/sizeof(a5[0]);
    size_t n6 = sizeof(a6)/sizeof(a6[0]);

    int dst1[100];
    int dst2[100];

    int *dd1 = stl::merge(a4, a4+n4, a5, a5+n5, dst1, std::less<int>());
    std::merge(a4, a4+n4, a5, a5+n5, dst2, std::less<int>());
    assert(std::equal(dst1, dd1, dst2));

    dd1 = stl::merge(a4, a4+n4, a6, a6+n5, dst1, std::less<int>());
    std::merge(a4, a4+n4, a6, a6+n6, dst2, std::less<int>());
    assert(std::equal(dst1, dd1, dst2));

}


void testMaxEelementCase1()
{
    int a[] = {1, 2, 1, 2, 4, 5, 2, 0, 6};

    assert(*stl::max_element(a, a+sizeof(a)/sizeof(a[0])) == 6);

    assert(*stl::max_element(a, a+1) == 1);
    assert(*stl::max_element(a, a+2) == 2);


    assert(*stl::max_element(a, a+sizeof(a)/sizeof(a[0]), std::less<int>()) == 6);

    assert(*stl::max_element(a, a+1, std::less<int>()) == 1);
    assert(*stl::max_element(a, a+2, std::less<int>()) == 2);
}


void testMinEelementCase1()
{
    int a[] = {1, 2, 1, 2, 4, 5, 2, 0, 6};

    assert(*stl::min_element(a, a+sizeof(a)/sizeof(a[0])) == 0);

    assert(*stl::min_element(a, a+1) == 1);
    assert(*stl::min_element(a, a+2) == 1);


    assert(*stl::min_element(a, a+sizeof(a)/sizeof(a[0]), std::less<int>()) == 0);

    assert(*stl::min_element(a, a+1, std::less<int>()) == 1);
    assert(*stl::min_element(a, a+2, std::less<int>()) == 1);
}



void testPartitionCase1()
{
    srand(time(NULL) + rand());
    std::vector<int> vec;
    vec.resize(100);
    for(int i = 0; i < 100; ++i)
        vec[i] = rand()%1000;


    std::multiset<int> mset1(vec.begin(), vec.end());

    int middle = 500;
    std::vector<int>::iterator it = stl::partition(vec.begin(), vec.end(), std::bind2nd(std::less<int>(), middle));

    assert(stl::find_if(vec.begin(), it, std::bind2nd(std::greater<int>(), middle)) == it);
    assert(stl::find_if(it, vec.end(), std::bind2nd(std::less<int>(), middle)) == vec.end());


    std::multiset<int> mset2(vec.begin(), vec.end());
    assert(mset1 == mset2);//测试分类的时候没有丢失元素


    assert(stl::partition(vec.begin(), vec.end(), std::bind2nd(std::less<int>(), 1000)) == vec.end());
    assert(stl::partition(vec.begin(), vec.end(), std::bind2nd(std::less<int>(), 0)) == vec.begin());
}


void testRemoveCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(remove(a1, a1+n1, 2) == a1+4);
    assert(remove(a1, a1+n1, 6) == a1+n1);

    int a2[] = {2, 2, 2, 2, 2};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    assert(remove(a2, a2+n2, 2) == a2);
}


void testRemoveIfCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(stl::remove_if(a1, a1+n1, std::bind2nd(std::equal_to<int>(), 2)) == a1+4);
    assert(stl::remove_if(a1, a1+n1, std::bind2nd(std::equal_to<int>(), 6)) == a1+n1);

    int a2[] = {2, 2, 2, 2, 2};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    assert(stl::remove_if(a2, a2+n2, std::bind2nd(std::equal_to<int>(), 2)) == a2);
}


void testRemoveCopyCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    std::set<int> sset(a1, a1+n1);
    sset.erase(2);

    std::vector<int> vec;
    stl::remove_copy(a1, a1+n1, std::back_inserter(vec), 2);
    assert(stl::includes(vec.begin(), vec.end(), sset.begin(), sset.end()));
    assert(stl::includes(sset.begin(), sset.end(), vec.begin(), vec.end()));
    vec.clear();


    stl::remove_copy(a1, a1+n1, std::back_inserter(vec), 6);
    assert(std::equal(vec.begin(), vec.end(), a1));
    vec.clear();


    int a2[] = {2, 2, 2, 2, 2};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    stl::remove_copy(a2, a2+n2, std::back_inserter(vec), 2);
    assert(vec.empty());
}



void testRemoveCopyIfCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    std::set<int> sset(a1, a1+n1);
    sset.erase(2);

    std::vector<int> vec;
    stl::remove_copy_if(a1, a1+n1, std::back_inserter(vec), std::bind2nd(std::equal_to<int>(), 2));
    assert(stl::includes(vec.begin(), vec.end(), sset.begin(), sset.end()));
    assert(stl::includes(sset.begin(), sset.end(), vec.begin(), vec.end()));
    vec.clear();


    stl::remove_copy_if(a1, a1+n1, std::back_inserter(vec), std::bind2nd(std::equal_to<int>(), 6));
    assert(std::equal(vec.begin(), vec.end(), a1));
    vec.clear();


    int a2[] = {2, 2, 2, 2, 2};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    stl::remove_copy_if(a2, a2+n2, std::back_inserter(vec), std::bind2nd(std::equal_to<int>(), 2));
    assert(vec.empty());
}



void testReplaceCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    int a2[] = {1, 0, 0, 3, 4, 0, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec1(a1, a1+n1);
    stl::replace(vec1.begin(), vec1.end(), 2, 0);

    assert(std::equal(vec1.begin(), vec1.end(), a2));

    std::vector<int> vec2(a1, a1+n1);
    stl::replace(vec2.begin(), vec2.end(), 6, 0);
    assert(std::equal(vec2.begin(), vec2.end(), a1));


    int a3[] = {2, 2, 2, 2, 2};
    size_t n3 = sizeof(a3)/sizeof(a3[0]);


    std::vector<int> vec3(a3, a3+n3);
    stl::replace(vec3.begin(), vec3.end(), 2, 0);
    assert(vec3.size() == n3);
    assert(stl::count(vec3.begin(), vec3.end(), 0) == static_cast<int>(n3) );
}


void testReplaceIfCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    int a2[] = {1, 0, 0, 3, 4, 0, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec1(a1, a1+n1);
    stl::replace_if(vec1.begin(), vec1.end(), std::bind2nd(std::equal_to<int>(), 2), 0);

    assert(std::equal(vec1.begin(), vec1.end(), a2));

    std::vector<int> vec2(a1, a1+n1);
    stl::replace_if(vec2.begin(), vec2.end(), std::bind2nd(std::equal_to<int>(), 6), 0);
    assert(std::equal(vec2.begin(), vec2.end(), a1));


    int a3[] = {2, 2, 2, 2, 2};
    size_t n3 = sizeof(a3)/sizeof(a3[0]);


    std::vector<int> vec3(a3, a3+n3);
    stl::replace_if(vec3.begin(), vec3.end(), std::bind2nd(std::equal_to<int>(), 2), 0);
    assert(vec3.size() == n3);
    assert(stl::count(vec3.begin(), vec3.end(), 0) == static_cast<int>(n3) );
}



void testReplaceCopyCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    int a2[] = {1, 0, 0, 3, 4, 0, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec;
    stl::replace_copy(a1, a1+n1, std::back_inserter(vec), 2, 0);
    assert(std::equal(vec.begin(), vec.end(), a2));

    vec.clear();
    stl::replace_copy(a1, a1+n1, std::back_inserter(vec), 6, 0);
    assert(std::equal(vec.begin(), vec.end(), a1));
    vec.clear();


    int a3[] = {2, 2, 2, 2, 2};
    size_t n3 = sizeof(a3)/sizeof(a3[0]);

    stl::replace_copy(a3, a3+n3, std::back_inserter(vec), 2, 0);
    assert(vec.size() == n3);
    assert(stl::count(vec.begin(), vec.end(), 0) == static_cast<int>(n3) );
}



void testReplaceCopyIfCase1()
{
    int a1[] = {1, 2, 2, 3, 4, 2, 5};
    int a2[] = {1, 0, 0, 3, 4, 0, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec;
    stl::replace_copy_if(a1, a1+n1, std::back_inserter(vec), std::bind2nd(std::equal_to<int>(), 2), 0);
    assert(std::equal(vec.begin(), vec.end(), a2));

    vec.clear();
    stl::replace_copy_if(a1, a1+n1, std::back_inserter(vec), std::bind2nd(std::equal_to<int>(), 6), 0);
    assert(std::equal(vec.begin(), vec.end(), a1));
    vec.clear();


    int a3[] = {2, 2, 2, 2, 2};
    size_t n3 = sizeof(a3)/sizeof(a3[0]);

    stl::replace_copy_if(a3, a3+n3, std::back_inserter(vec), std::bind2nd(std::equal_to<int>(), 2), 0);
    assert(vec.size() == n3);
    assert(stl::count(vec.begin(), vec.end(), 0) == static_cast<int>(n3) );
}



void testReverseCase1()
{
    srand(time(NULL) + rand());
    std::vector<int> vec;
    vec.reserve(1000);
    for(int i = 0; i < 1000; ++i)
    {
        vec.push_back(rand()%1000);
    }

    std::vector<int> vec_cp(vec);

    stl::reverse(vec.begin(), vec.end());
    std::reverse(vec_cp.begin(), vec_cp.end());
    assert(vec == vec_cp);

    stl::reverse(vec.begin(), vec.begin()+1);
    assert(vec[0] == vec_cp[0]);

    stl::reverse(vec.begin(), vec.begin()+2);
    std::reverse(vec_cp.begin(), vec_cp.begin()+2);
    assert(std::equal(vec.begin(), vec.begin()+3, vec_cp.begin()));


    stl::reverse(vec.begin(), vec.begin()+3);
    std::reverse(vec_cp.begin(), vec_cp.begin()+3);
    assert(std::equal(vec.begin(), vec.begin()+4, vec_cp.begin()));
}



void testReverseCopyCase1()
{
    srand(time(NULL) + rand());
    std::vector<int> vec;
    vec.reserve(1000);
    for(int i = 0; i < 1000; ++i)
    {
        vec.push_back(rand()%1000);
    }

    std::vector<int> vec1;
    stl::reverse_copy(vec.begin(), vec.end(), std::back_inserter(vec1));

    std::reverse(vec1.begin(), vec1.end());
    assert(vec == vec1);


    vec1.clear();
    stl::reverse_copy(vec.begin(), vec.begin()+2, std::back_inserter(vec1));
    std::reverse(vec1.begin(), vec1.end());
    assert(std::equal(vec1.begin(), vec1.end(), vec.begin()));

    vec1.clear();
    stl::reverse_copy(vec.begin(), vec.begin()+3, std::back_inserter(vec1));
    std::reverse(vec1.begin(), vec1.end());
    assert(std::equal(vec1.begin(), vec1.end(), vec.begin()));
}


void testSearchCase1()
{
    srand(time(NULL) + rand());
    std::vector<int> vec;
    vec.reserve(100);
    for(int i = 0; i < 100; ++i)
    {
        vec.push_back(rand()%1000);
    }


    assert(stl::search(vec.begin(), vec.end(), vec.begin()+10, vec.begin()+20) == vec.begin()+10);
    assert(stl::search(vec.begin(), vec.end(), vec.begin(), vec.end()) == vec.begin());


    assert(stl::search(vec.begin()+1, vec.end(), vec.begin(), vec.end()) == vec.end());

    std::vector<int> vec_cp(vec);
    vec_cp.push_back(23);
    assert(stl::search(vec.begin(), vec.end(), vec_cp.begin(), vec_cp.end()) == vec.end());
}


void testSearchCase2()
{
    srand(time(NULL) + rand());
    std::vector<int> vec;
    vec.reserve(100);
    for(int i = 0; i < 100; ++i)
    {
        vec.push_back(rand()%1000);
    }


    assert(stl::search(vec.begin(), vec.end(), vec.begin()+10, vec.begin()+20, std::equal_to<int>()) == vec.begin()+10);
    assert(stl::search(vec.begin(), vec.end(), vec.begin(), vec.end(), std::equal_to<int>()) == vec.begin());


    assert(stl::search(vec.begin()+1, vec.end(), vec.begin(), vec.end(), std::equal_to<int>()) == vec.end());

    std::vector<int> vec_cp(vec);
    vec_cp.push_back(23);
    assert(stl::search(vec.begin(), vec.end(), vec_cp.begin(), vec_cp.end(), std::equal_to<int>()) == vec.end());
}



void testSearchNCase1()
{
    int a1[] = {1, 2, 2, 2, 4, 2, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(search_n(a1, a1+n1, 3, 2) == a1+1);
    assert(search_n(a1, a1+n1, 2, 2) == a1+1);
    assert(search_n(a1, a1+n1, 4, 2) == a1+n1);

    assert(search_n(a1, a1+n1, 3, 6) == a1+n1);
}


void testSearchNCase2()
{
    int a1[] = {1, 2, 2, 2, 4, 2, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(stl::search_n(a1, a1+n1, 3, 2, std::equal_to<int>()) == a1+1);
    assert(stl::search_n(a1, a1+n1, 2, 2, std::equal_to<int>()) == a1+1);
    assert(stl::search_n(a1, a1+n1, 4, 2, std::equal_to<int>()) == a1+n1);

    assert(stl::search_n(a1, a1+n1, 3, 6, std::equal_to<int>()) == a1+n1);
}



void testSwapRangesCase1()
{
    srand(time(NULL) + rand());
    std::vector<int> vec1, vec2;
    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
        vec2.push_back(rand()%1000);
    }

    std::vector<int> vec1_cp(vec1), vec2_cp(vec2);

    stl::swap_ranges(vec1.begin(), vec1.end(), vec2.begin());

    assert(vec1 == vec2_cp  && vec2 == vec1_cp);
}


void testTransformCase1()
{
    srand(time(NULL) + rand());
    std::vector<int> vec1;
    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
    }


    std::vector<int> vec2, vec3;

    stl::transform(vec1.begin(), vec1.end(), std::back_inserter(vec2), std::bind2nd(std::plus<int>(), 10));
    std::transform(vec1.begin(), vec1.end(), std::back_inserter(vec3), std::bind2nd(std::plus<int>(), 10));

    assert(vec2 == vec3);
}



void testTransformCase2()
{
    srand(time(NULL) + rand());
    std::vector<int> vec1, vec2;
    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
        vec2.push_back(rand()%1000);
    }


    std::vector<int> vec3, vec4;

    stl::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(vec3), std::multiplies<int>());
    std::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(vec4), std::multiplies<int>());

    assert(vec3 == vec4);
}



void testUniqueCase1()
{
    int a1[] = {1, 2, 2, 2, 3, 3, 4, 5, 5, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec1(a1, a1+n1), vec2(a1, a1+n1);
    std::vector<int>::iterator it1, it2;

    it1 = stl::unique(vec1.begin(), vec1.end());
    it2 = std::unique(vec2.begin(), vec2.end());
    assert(std::equal(vec2.begin(), it2, vec1.begin()));


    vec1.clear();
    vec1.push_back(1);
    vec2.assign(vec1.begin(), vec1.end());

    it1 = stl::unique(vec1.begin(), vec1.end());
    it2 = std::unique(vec2.begin(), vec2.end());
    assert(std::equal(vec2.begin(), it2, vec1.begin()));



    vec1.push_back(1);
    vec2.assign(vec1.begin(), vec1.end());

    it1 = stl::unique(vec1.begin(), vec1.end());
    it2 = std::unique(vec2.begin(), vec2.end());
    assert(std::equal(vec2.begin(), it2, vec1.begin()));
}



void testUniqueCase2()
{
    int a1[] = {1, 2, 2, 2, 3, 3, 4, 5, 5, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec1(a1, a1+n1), vec2(a1, a1+n1);
    std::vector<int>::iterator it1, it2;

    it1 = stl::unique(vec1.begin(), vec1.end(), std::equal_to<int>());
    it2 = std::unique(vec2.begin(), vec2.end(), std::equal_to<int>());

    assert(std::equal(vec2.begin(), it2, vec1.begin()));


    vec1.clear();
    vec1.push_back(1);
    vec2.assign(vec1.begin(), vec1.end());

    it1 = stl::unique(vec1.begin(), vec1.end(), std::equal_to<int>());
    it2 = std::unique(vec2.begin(), vec2.end(), std::equal_to<int>());
    assert(std::equal(vec2.begin(), it2, vec1.begin()));


    vec1.push_back(1);
    vec2.assign(vec1.begin(), vec1.end());

    it1 = stl::unique(vec1.begin(), vec1.end(), std::equal_to<int>());
    it2 = std::unique(vec2.begin(), vec2.end(), std::equal_to<int>());
    assert(std::equal(vec2.begin(), it2, vec1.begin()));
}



void testUniqueCopyCase1()
{
    int a1[] = {1, 2, 2, 2, 3, 3, 4, 5, 5, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec1, vec2;

    stl::unique_copy(a1, a1+n1, std::back_inserter(vec1));
    std::unique_copy(a1, a1+n1, std::back_inserter(vec2));
    assert(vec1 == vec2);


    vec1.clear();
    vec2.clear();
    stl::unique_copy(a1+1, a1+3, std::back_inserter(vec1));
    std::unique_copy(a1+1, a1+3, std::back_inserter(vec2));
    assert(vec1 == vec2);


    vec1.clear();
    vec2.clear();
    stl::unique_copy(a1, a1+1, std::back_inserter(vec1));
    std::unique_copy(a1, a1+1, std::back_inserter(vec2));
    assert(vec1 == vec2);
}



void testUniqueCopyCase2()
{
    int a1[] = {1, 2, 2, 2, 3, 3, 4, 5, 5, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::vector<int> vec1, vec2;

    stl::unique_copy(a1, a1+n1, std::back_inserter(vec1), std::equal_to<int>());
    std::unique_copy(a1, a1+n1, std::back_inserter(vec2), std::equal_to<int>());
    assert(vec1 == vec2);


    vec1.clear();
    vec2.clear();
    stl::unique_copy(a1+1, a1+3, std::back_inserter(vec1), std::equal_to<int>());
    std::unique_copy(a1+1, a1+3, std::back_inserter(vec2), std::equal_to<int>());
    assert(vec1 == vec2);


    vec1.clear();
    vec2.clear();
    stl::unique_copy(a1, a1+1, std::back_inserter(vec1), std::equal_to<int>());
    std::unique_copy(a1, a1+1, std::back_inserter(vec2), std::equal_to<int>());
    assert(vec1 == vec2);
}


void testIsSortCase1()
{
    int a1[] = {1, 2, 3, 4, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(stl::is_sorted_until(a1, a1, stl::less<int>()) == a1);
    assert(stl::is_sorted_until(a1, a1+1, stl::less<int>()) == a1+1);
    assert(stl::is_sorted_until(a1, a1+2, stl::less<int>()) == a1+2);
    assert(stl::is_sorted_until(a1, a1+n1, stl::less<int>()) == a1+n1);

    int a2[] = {1, 2, 2, 3, 4};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    assert(stl::is_sorted_until(a2, a2+2, stl::less<int>()) == a2+2);
    assert(stl::is_sorted_until(a2, a2+3, stl::less<int>()) == a2+3);
    assert(stl::is_sorted_until(a2, a2+n2, stl::less<int>()) == a2+n2);


    int a3[] = {1, 2, 3, 2, 4, 5};
    size_t n3 = sizeof(a3)/sizeof(a3[0]);
    assert(stl::is_sorted_until(a3, a3+2, stl::less<int>()) == a3+2);
    assert(stl::is_sorted_until(a3, a3+3, stl::less<int>()) == a3+3);
    assert(stl::is_sorted_until(a3, a3+4, stl::less<int>()) == a3+3);
    assert(stl::is_sorted_until(a3, a3+n3, stl::less<int>()) == a3+3);
}


void testIsSortCase2()
{
    //内部调用is_sorted_until，所以只需简单测试是否编译通过即可
    int a1[] = {1, 2, 3, 4, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(stl::is_sorted(a1, a1+n1));
    assert(stl::is_sorted(a1, a1+n1, stl::greater<int>()) == false);
    assert(stl::is_sorted_until(a1, a1+n1) == a1+n1);

    int a2[] = {1, 2, 3, 2, 1};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    assert(stl::is_sorted(a2, a2+n2) == false);
    assert(stl::is_sorted(a2, a2+n2, stl::less<int>()) == false);
    assert(stl::is_sorted_until(a2, a2+n2) == a2+3);
}


//测试BidirectionalIterator
void testSortCase1()
{
    int a1[] = {1, 2, 3, 4, 9, 8, 7, 6, 5};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    stl::list<int> alist(a1, a1+n1);
    stl::list<int> alist_cp(alist);

    sort(alist.begin(), alist.end());
    alist_cp.sort();
    assert(alist == alist_cp);

    sort(alist.begin(), alist.end());//对已排序的再次排序
    assert(alist == alist_cp);

    alist.reverse();
    sort(alist.begin(), alist.end());//对倒序的进行排序
    assert(alist == alist_cp);


    int a2[] = {9, 8, 7, 6, 1, 2, 3, 4};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    alist.assign(a2, a2+n2);
    alist_cp = alist;

    sort(alist.begin(), alist.end());
    alist_cp.sort();
    assert(alist == alist_cp);


    //对序列中的部分元素进行排序
    alist.assign(a2, a2+n2);
    sort(alist.begin(), stl::next(alist.begin(), 4));
    int a22[] = {6, 7, 8, 9, 1, 2, 3, 4};
    assert(alist.size()==n2 && stl::equal(a22, a22+n2, alist.begin()));


    int a3[] = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    size_t n3 = sizeof(a3)/sizeof(a3[0]);
    alist.assign(a3, a3+n3);
    alist_cp = alist;

    sort(alist.begin(), alist.end());
    alist_cp.sort();
    assert(alist == alist_cp);


    int a4[] = {2, 4, 6, 8, 1, 3, 5, 7, 9};
    size_t n4 = sizeof(a4)/sizeof(a4[0]);
    alist.assign(a4, a4+n4);
    alist_cp = alist;

    sort(alist.begin(), alist.end());
    alist_cp.sort();
    assert(alist == alist_cp);


    //边界情况
    alist.clear();
    alist.push_back(2);
    sort(alist.begin(), alist.end());
    assert(alist.size()==1 && alist.back()==2);

    alist.push_back(1);
    sort(alist.begin(), alist.end());
    assert(alist.size()==2 && alist.front()==1 && alist.back()==2);

    alist.clear();
    alist.push_back(1);
    alist.push_back(2);
    sort(alist.begin(), alist.end());
    assert(alist.size()==2 && alist.front()==1 && alist.back()==2);


    //测试自定义的比较函数
    alist.assign(a1, a1+n1);
    alist_cp = alist;

    sort(alist.begin(), alist.end(), stl::greater<int>());
    alist_cp.sort();
    assert(alist.size()==n1 && stl::equal(alist.rbegin(), alist.rend(), alist_cp.begin()));
}

//===================================================

void testAlgo()
{
    testSetOpCase1();
    testSetOpCase2();


    testAdjacentFindCase1();
    testAdjacentFindCase2();

    testCountCase1();
    testCountIfCase1();


    testFindCase1();
    testFindIfCase2();


    testFindFirstOfCase1();
    testFindFirstOfCase2();


    testForeachCase1();


    testGenerateCase1();
    testGenerateCase2();


    testIncludesCase1();
    testIncludesCase2();


    testMergeCase1();
    testMergeCase2();


    testMaxEelementCase1();
    testMinEelementCase1();


    testPartitionCase1();

    testRemoveCase1();
    testRemoveIfCase1();


    testRemoveCopyCase1();
    testRemoveCopyIfCase1();


    testReplaceCase1();
    testReplaceIfCase1();


    testReplaceCopyCase1();
    testReplaceCopyIfCase1();


    testReverseCase1();
    testReverseCopyCase1();


    testSearchCase1();
    testSearchCase2();


    testSearchNCase1();
    testSearchNCase2();


    testSwapRangesCase1();

    testTransformCase1();
    testTransformCase2();


    testUniqueCase1();
    testUniqueCase2();

    testUniqueCopyCase1();
    testUniqueCopyCase2();


    testIsSortCase1();
    testIsSortCase2();


    testSortCase1();
}

}

