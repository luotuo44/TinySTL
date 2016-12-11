//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testPriorityQueue.h"


#include<assert.h>
#include<time.h>
#include<stdlib.h>


#include<algorithm>

#include"../queue"
#include"../vector"




namespace stl
{



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



void testPriorityQueueConstructorCase1()
{
    stl::priority_queue<int> pq;
    assert(pq.empty() && pq.size()==0);

    pq.push(1);
    assert(pq.size()==1 && pq.top()==1);

    pq.pop();
    assert(pq.empty() && pq.size()==0);

    pq.push(2);
    assert(pq.size()==1 && !pq.empty() && pq.top()==2);

    pq.push(6);
    assert(pq.size()==2 && !pq.empty() && pq.top()==6);

    pq.push(10);
    assert(pq.size()==3 && !pq.empty() && pq.top()==10);

    pq.push(1);
    assert(pq.size()==4 && !pq.empty() && pq.top()==10);


    pq.pop();
    assert(pq.size()==3 && !pq.empty() && pq.top()==6);
}



void testPriorityQueueConstructorCase2()
{
    int arr[] = {3, 9, 2, 4, 6, 8, 1, 0, 10};
    size_t n = sizeof(arr)/sizeof(arr[0]);

    stl::priority_queue<int> pq(arr, arr+n);
    assert(pq.size()==n && pq.top()==10);
}



void testPriorityQueuePopCase1SubCase1(int *arr, size_t n)
{
    stl::priority_queue<int> pq(arr, arr+n);

    std::sort(arr, arr+n, stl::greater<int>());

    for(size_t i = 0; !pq.empty(); ++i)
    {
        assert(pq.top() == arr[i]);
        pq.pop();
    }
}


void testPriorityQueuePopCase1()
{
    stl::vector<int> vec = generateRandomInt(1);
    testPriorityQueuePopCase1SubCase1(vec.data(), vec.size());

    vec = generateRandomInt(2);
    testPriorityQueuePopCase1SubCase1(vec.data(), vec.size());

    vec = generateRandomInt(3);
    testPriorityQueuePopCase1SubCase1(vec.data(), vec.size());

    vec = generateRandomInt(4);
    testPriorityQueuePopCase1SubCase1(vec.data(), vec.size());

    vec = generateRandomInt(5);
    testPriorityQueuePopCase1SubCase1(vec.data(), vec.size());

    srand(time(NULL) + rand());
    for(int i = 0; i < 33; ++i)
    {
        vec = generateRandomInt(1 + rand()%1000);
        testPriorityQueuePopCase1SubCase1(vec.data(), vec.size());
    }
}



void judgePriorityQueueSeq(stl::priority_queue<int> pq, int *arr, size_t n)
{
    assert(pq.size() == n);

    std::sort(arr, arr+n, stl::greater<int>());
    for(size_t i = 0; !pq.empty(); ++i)
    {
        assert(pq.top() == arr[i]);
        pq.pop();
    }
}


void testPriorityQueuePushCase1()
{
    stl::vector<int> vec = generateRandomInt(308);
    stl::priority_queue<int> pq;

    for(size_t i = 0; i < vec.size(); ++i)
    {
        pq.push(vec[i]);
        judgePriorityQueueSeq(pq, vec.data(), i+1);
    }
}

//============================================================================

void testPriorityQueue()
{
    testPriorityQueueConstructorCase1();
    testPriorityQueueConstructorCase2();


    testPriorityQueuePopCase1();
    testPriorityQueuePushCase1();
}

}
