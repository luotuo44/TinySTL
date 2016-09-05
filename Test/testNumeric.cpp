//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testNumeric.h"

#include<assert.h>
#include<time.h>
#include<stdlib.h>

#include<numeric>
#include<vector>
#include<iterator>
#include<functional>


#include"../bits/stl_numeric.h"


namespace stl
{

void testAccumulateCase1()
{
    std::vector<int> vec;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec.push_back(rand()%1000);
    }

    int sum1 = std::accumulate(vec.begin(), vec.end(), 0);
    int sum2 = stl::accumulate(vec.begin(), vec.end(), 0);
    assert(sum1 == sum2);


    sum1 = std::accumulate(vec.begin(), vec.begin(), 10);
    sum2 = stl::accumulate(vec.begin(), vec.begin(), 10);
    assert(sum1 == sum2);


    sum1 = std::accumulate(vec.begin(), ++vec.begin(), 10);
    sum2 = stl::accumulate(vec.begin(), ++vec.begin(), 10);
    assert(sum1 == sum2);
}




void testAccumulateCase2()
{
    std::vector<int> vec;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec.push_back(rand()%1000);
    }

    int sum1 = std::accumulate(vec.begin(), vec.end(), 0, std::minus<int>());
    int sum2 = stl::accumulate(vec.begin(), vec.end(), 0, std::minus<int>());
    assert(sum1 == sum2);


    sum1 = std::accumulate(vec.begin(), vec.begin(), 10, std::minus<int>());
    sum2 = stl::accumulate(vec.begin(), vec.begin(), 10, std::minus<int>());
    assert(sum1 == sum2);


    sum1 = std::accumulate(vec.begin(), ++vec.begin(), 10, std::minus<int>());
    sum2 = stl::accumulate(vec.begin(), ++vec.begin(), 10, std::minus<int>());
    assert(sum1 == sum2);
}


void testInnerProductCase1()
{
    std::vector<int> vec1, vec2;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
        vec2.push_back(rand()%1000);
    }


    int sum1 = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
    int sum2 = stl::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
    assert(sum1 == sum2);


    sum1 = std::inner_product(vec1.begin(), vec1.begin(), vec2.begin(), 10);
    sum2 = stl::inner_product(vec1.begin(), vec1.begin(), vec2.begin(), 10);
    assert(sum1 == sum2);


    sum1 = std::inner_product(vec1.begin(), ++vec1.begin(), vec2.begin(), 90);
    sum2 = stl::inner_product(vec1.begin(), ++vec1.begin(), vec2.begin(), 90);
    assert(sum1 == sum2);
}



void testInnerProductCase2()
{
    std::vector<int> vec1, vec2;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%100);
        vec2.push_back(rand()%100);
    }


    int sum1 = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0, std::multiplies<int>(), std::plus<int>());
    int sum2 = stl::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0, std::multiplies<int>(), std::plus<int>());
    assert(sum1 == sum2);


    sum1 = std::inner_product(vec1.begin(), vec1.begin(), vec2.begin(), 10, std::multiplies<int>(), std::plus<int>());
    sum2 = stl::inner_product(vec1.begin(), vec1.begin(), vec2.begin(), 10, std::multiplies<int>(), std::plus<int>());
    assert(sum1 == sum2);


    sum1 = std::inner_product(vec1.begin(), ++vec1.begin(), vec2.begin(), 90, std::multiplies<int>(), std::plus<int>());
    sum2 = stl::inner_product(vec1.begin(), ++vec1.begin(), vec2.begin(), 90, std::multiplies<int>(), std::plus<int>());
    assert(sum1 == sum2);
}



void testPartialSumCase1()
{
    std::vector<int> vec1, vec2, vec3;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
    }

    vec2.resize(vec1.size());
    vec3.resize(vec1.size());


    std::partial_sum(vec1.begin(), vec1.end(), vec2.begin());
    stl::partial_sum(vec1.begin(), vec1.end(), vec3.begin());
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));



    std::partial_sum(vec1.begin(), vec1.begin(), vec2.begin());
    stl::partial_sum(vec1.begin(), vec1.begin(), vec3.begin());
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));

    std::partial_sum(vec1.begin(), ++vec1.begin(), vec2.begin());
    stl::partial_sum(vec1.begin(), ++vec1.begin(), vec3.begin());
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));
}


template<typename T>
inline T XOR(const T &a, const T &b)
{
    return a ^ b;
}



void testPartialSumCase2()
{
    std::vector<int> vec1, vec2, vec3;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
    }

    vec2.resize(vec1.size());
    vec3.resize(vec1.size());


    std::partial_sum(vec1.begin(), vec1.end(), vec2.begin(), XOR<int>);
    stl::partial_sum(vec1.begin(), vec1.end(), vec3.begin(), XOR<int>);
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));



    std::partial_sum(vec1.begin(), vec1.begin(), vec2.begin(), XOR<int>);
    stl::partial_sum(vec1.begin(), vec1.begin(), vec3.begin(), XOR<int>);
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));

    std::partial_sum(vec1.begin(), ++vec1.begin(), vec2.begin(), XOR<int>);
    stl::partial_sum(vec1.begin(), ++vec1.begin(), vec3.begin(), XOR<int>);
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));
}




void testAdjacentDifferenceCase1()
{
    std::vector<int> vec1, vec2, vec3;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
    }

    vec2.resize(vec1.size());
    vec3.resize(vec1.size());


    std::adjacent_difference(vec1.begin(), vec1.end(), vec2.begin());
    stl::adjacent_difference(vec1.begin(), vec1.end(), vec3.begin());
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));



    std::adjacent_difference(vec1.begin(), vec1.begin(), vec2.begin());
    stl::adjacent_difference(vec1.begin(), vec1.begin(), vec3.begin());
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));

    std::adjacent_difference(vec1.begin(), ++vec1.begin(), vec2.begin());
    stl::adjacent_difference(vec1.begin(), ++vec1.begin(), vec3.begin());
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));
}



void testAdjacentDifferenceCase2()
{
    std::vector<int> vec1, vec2, vec3;
    srand(time(NULL));

    for(int i = 0; i < 100; ++i)
    {
        vec1.push_back(rand()%1000);
    }

    vec2.resize(vec1.size());
    vec3.resize(vec1.size());


    std::adjacent_difference(vec1.begin(), vec1.end(), vec2.begin(), XOR<int>);
    stl::adjacent_difference(vec1.begin(), vec1.end(), vec3.begin(), XOR<int>);
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));



    std::adjacent_difference(vec1.begin(), vec1.begin(), vec2.begin(), XOR<int>);
    stl::adjacent_difference(vec1.begin(), vec1.begin(), vec3.begin(), XOR<int>);
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));

    std::adjacent_difference(vec1.begin(), ++vec1.begin(), vec2.begin(), XOR<int>);
    stl::adjacent_difference(vec1.begin(), ++vec1.begin(), vec3.begin(), XOR<int>);
    assert(std::equal(vec2.begin(), vec2.end(), vec3.begin()));
}


void testIotaCase1()
{
    std::vector<int> vec;
    vec.resize(10);

    stl::iota(vec.begin(), vec.end(), 0);

    int a = 0;
    std::vector<int>::const_iterator it, end = vec.end();
    for(it = vec.begin(); it != end; ++it)
    {
        assert( *it == a++);
    }
}

void testNumeric()
{
    testAccumulateCase1();
    testAccumulateCase2();


    testInnerProductCase1();
    testInnerProductCase2();


    testPartialSumCase1();
    testPartialSumCase2();


    testAdjacentDifferenceCase1();
    testAdjacentDifferenceCase2();

    testIotaCase1();
}


}
