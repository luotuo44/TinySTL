//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testStack.h"



#include<assert.h>


#include<string>

#include"../stack"



namespace stl
{


template<typename T>
bool stackEqualJudge(stl::stack<T> lhs, stl::stack<T> rhs)
{
    if( lhs.size() != rhs.size() )
        return false;

    while(!lhs.empty())
    {
        if( lhs.top() != rhs.top() )
            return false;

        lhs.pop();
        rhs.pop();
    }

    return true;
}


template<typename T>
void testStackConstructorCase1()
{
    stl::stack<T> st;
    assert(st.empty());
}



template<typename T>
void testStackPushPopCase1(const T *arr, size_t n)
{
    stl::stack<T> st;
    for(size_t i = 0; i < n; ++i)
    {
        st.push(arr[i]);
        assert(st.top() == arr[i]);
    }

    for(size_t i = n-1; !st.empty(); --i)
    {
        assert(st.top() == arr[i]);
        st.pop();
    }
}






//============================================================================

void testStack()
{
    testStackConstructorCase1<int>();
    testStackConstructorCase1<double>();
    testStackConstructorCase1<char>();
    testStackConstructorCase1<std::string>();


    int a1[] = {1, 3, 5, 2, 6, 7, 8, 4, 9};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    std::string a2[] = {"vector", "list", "deque", "stack"};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    testStackPushPopCase1(a1, n1);
    testStackPushPopCase1(a2, n2);

}

}
