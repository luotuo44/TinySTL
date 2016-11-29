//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testQueue.h"

#include<assert.h>

#include<string>

#include"../queue"



namespace stl
{


template<typename ForwardIterator>
bool queueEqualJudge(queue<typename iterator_traits<ForwardIterator>::value_type> qu, ForwardIterator first, ForwardIterator last )
{
    size_t n = stl::distance(first, last);
    if( qu.size() != n )
        return false;

    for(; first != last; ++first)
    {
        if( qu.front() != *first)
            return false;

        qu.pop();
    }

    return true;
}



template<typename T>
void testQueueCostructorCase1()
{
    stl::queue<T> qu;
    assert(qu.empty() && qu.size() == 0);
}



template<typename T>
void testQueuePushCase1(const T *arr, size_t n)
{
    stl::queue<T> qu;
    for(size_t i = 0; i < n; )
    {
        qu.push(arr[i++]);
        assert(qu.back()==arr[i-1] && queueEqualJudge(qu, arr, arr+i));
    }
}



template<typename T>
void testQueuePopCase1(const T *arr, size_t n)
{
    stl::queue<T> qu;
    for(size_t i = 0; i < n; )
    {
        qu.push(arr[i++]);
    }

    for(size_t i = 0; i < n; ++i)
    {
        assert(queueEqualJudge(qu, arr+i, arr+n));
        qu.pop();
    }


    size_t i = 0;
    while(i < n/2 )
    {
        qu.push(arr[i++]);
    }

    qu.pop();
    assert(queueEqualJudge(qu, arr+1, arr+i));


    qu.pop();
    assert(queueEqualJudge(qu, arr+2, arr+i));


    qu.push(arr[i++]);
    assert(queueEqualJudge(qu, arr+2, arr+i));

    qu.pop();
    assert(queueEqualJudge(qu, arr+3, arr+i));


    qu.push(arr[i++]);
    assert(queueEqualJudge(qu, arr+3, arr+i));
    qu.push(arr[i++]);
    assert(queueEqualJudge(qu, arr+3, arr+i));
    qu.pop();
    assert(queueEqualJudge(qu, arr+4, arr+i));
    qu.pop();
    assert(queueEqualJudge(qu, arr+5, arr+i));
}



void testQueueSwapCase1()
{
    stl::queue<std::string> qu1;
    stl::queue<std::string> qu2;

    qu1.swap(qu2);
    assert(qu1.empty() && qu2.empty());

    qu1.push("deque");
    qu2.swap(qu1);
    assert(qu1.empty() && qu2.size()==1 && qu2.back()=="deque" && qu2.front()=="deque");


    qu1.push("queue");
    qu1.swap(qu2);

    assert(qu1.size()==1 && qu1.front()=="deque" && qu1.back()=="deque");
    assert(qu2.size()==1 && qu2.front()=="queue" && qu2.back()=="queue");
}



void testQueueRelationalOperatorCase1()
{
    stl::queue<int> qu1;
    stl::queue<int> qu2;

    qu1.push(1);qu1.push(2);
    qu2.push(1);

    assert(qu1 != qu2);
    assert(!(qu1 == qu2));

    assert(qu1 >= qu2);
    assert(qu1 > qu2);

    assert(qu2 < qu1);
    assert(qu2 <= qu1);


    qu2.push(2);
    assert(qu1 == qu2);


    qu2.pop();
    assert(qu1 != qu2);
    assert(qu1 < qu2);
    assert(qu1 <= qu2);
    assert(qu2 >= qu1);
    assert(qu2 > qu1);
}


//==================================================================================

void testQueue()
{
    testQueueCostructorCase1<int>();
    testQueueCostructorCase1<double>();
    testQueueCostructorCase1<char>();
    testQueueCostructorCase1<std::string>();

    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    std::string a2[] = { "C++", "STL", "vector", "list", "deque", "stack", "queue"};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    testQueuePushCase1(a1, n1);
    testQueuePushCase1(a2, n2);


    testQueuePopCase1(a1, n1);
    testQueuePopCase1(a2, n2);


    testQueueSwapCase1();

    testQueueRelationalOperatorCase1();
}

}
