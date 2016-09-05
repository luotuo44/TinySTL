//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"testAlloc.h"

#include<assert.h>

#include<string>
#include<vector>
#include<set>
#include<algorithm>

#include"../bits/stl_construct.h"
#include"../bits/stl_uninitialized.h"
#include"../bits/stl_allocator.h"


namespace stl
{

void testConstructCase1()
{
    int a = 45;
    int *p = reinterpret_cast<int*>(malloc(sizeof(int)));
    stl::construct(p, a);
    assert( *p == a);
    free(p);

    std::string str("abcdef");
    std::string *my_str = reinterpret_cast<std::string*>(malloc(sizeof(std::string)));

    stl::construct(my_str, str);
    assert(*my_str == str);
    free(my_str);


    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    std::vector<int> *my_vec = reinterpret_cast<std::vector<int>*>(malloc(sizeof(std::vector<int>)));

    stl::construct(my_vec, vec);
    assert(*my_vec == vec);
    free(my_vec);
}


class CountTest
{
public:
    CountTest(int = 0)
    {
        if(s_num > 15)
            throw std::string("too many object");
        ++s_num;
    }

    CountTest(const CountTest &)
    {
        if(s_num > 15)
            throw std::string("too many object");
        ++s_num;
    }

    ~CountTest()
    {
        --s_num;
    }

    static size_t num()
    {
        return s_num;
    }

    static bool unique()
    {
        return s_num == 1;
    }

private:
    static size_t s_num;
};

size_t CountTest::s_num = 0;


void testDestroyCase1()
{
    CountTest *a1 = reinterpret_cast<CountTest*>(malloc(sizeof(CountTest)));
    stl::construct(a1, 2);


    CountTest *a2 = reinterpret_cast<CountTest*>(malloc(sizeof(CountTest)));
    stl::construct(a2, 2);

    assert(CountTest::num() == 2);
    stl::destroy(a2);
    assert(CountTest::unique());

    stl::construct(a2, 2);
    assert(CountTest::num() == 2);

    stl::destroy(a1);
    assert(CountTest::unique());
    stl::destroy(a2);
    assert(CountTest::num() == 0);

    free(a2);
    free(a1);
}


void testDestroyCase2()
{
    CountTest *a = reinterpret_cast<CountTest*>(malloc(7*sizeof(CountTest)));
    for(int i = 0; i < 7; ++i)
    {
        stl::construct(&a[i], 2);
    }

    assert(CountTest::num() == 7);

    stl::destroy(a, a + 7);
    assert(CountTest::num() == 0);

    free(a);
}


void testConstruct()
{
    testConstructCase1();
    testDestroyCase1();
    testDestroyCase2();
}


//#######################################################################


void testUninitializedFillCase1()
{
    std::vector<int> intvec;
    intvec.resize(10);

    stl::uninitialized_fill(intvec.begin(), intvec.end(), 13);
    for(std::vector<int>::iterator it = intvec.begin(); it != intvec.end(); ++it)
    {
        assert(*it == 13);
    }

    std::vector<std::string> strvec;
    strvec.resize(5);
    std::string str("abcdefg");
    stl::uninitialized_fill(strvec.begin(), strvec.end(), str);
    for(std::vector<std::string>::iterator it = strvec.begin(); it != strvec.end(); ++it)
    {
        assert(*it == str);
    }
}


//测试回滚
void testUninitializedFillCase2()
{
    CountTest ct;
    CountTest *arr = reinterpret_cast<CountTest*>(malloc(20*sizeof(CountTest)));

    try
    {
        stl::uninitialized_fill(arr, arr + 20, ct);
    }catch(...)
    {

    }

    assert(CountTest::unique());

    stl::uninitialized_fill(arr, arr + 10, ct);
    assert(CountTest::num() == 11);

    stl::destroy(arr, arr + 10);
    assert(CountTest::unique());

    free(arr);
}



void testUninitializedFillNCase1()
{
    std::vector<int> intvec;
    intvec.resize(10);

    stl::uninitialized_fill_n(intvec.begin(), intvec.size(), 13);
    for(std::vector<int>::iterator it = intvec.begin(); it != intvec.end(); ++it)
    {
        assert(*it == 13);
    }

    std::vector<std::string> strvec;
    strvec.resize(5);
    std::string str("abcdefg");
    stl::uninitialized_fill_n(strvec.begin(), strvec.size(), str);
    for(std::vector<std::string>::iterator it = strvec.begin(); it != strvec.end(); ++it)
    {
        assert(*it == str);
    }
}


//测试回滚
void testUninitializedFillNCase2()
{
    CountTest ct;
    CountTest *arr = reinterpret_cast<CountTest*>(malloc(20*sizeof(CountTest)));

    try
    {
        stl::uninitialized_fill_n(arr, 20, ct);
    }catch(...)
    {

    }

    assert(CountTest::unique());

    stl::uninitialized_fill_n(arr, 10, ct);
    assert(CountTest::num() == 11);

    stl::destroy(arr, arr + 10);
    assert(CountTest::unique());

    free(arr);
}



void testUninitializedCopyCase1()
{
    const int SIZE = 7;
    int a[SIZE] = {1, 2, 3, 4, 5, 6, 7};
    int b[SIZE];

    stl::uninitialized_copy(a, a + SIZE, b);
    assert(std::equal(a, a + SIZE, b));


    std::string a_str[SIZE] = {"aa", "BB", "CC", "DD", "EE", "FF", "GG"};
    std::string b_str[SIZE];

    stl::uninitialized_copy(a_str, a_str + SIZE, b_str);
    assert(std::equal(a_str, a_str + SIZE, b_str));
}


//测试回滚
void testUninitializedCopyCase2()
{
    CountTest ct[10];
    CountTest *arr = reinterpret_cast<CountTest*>(malloc(10*sizeof(CountTest)));

    try
    {
        stl::uninitialized_copy(ct, ct + 10, arr);
    }catch(...)
    {

    }

    assert(CountTest::num() == 10);

    stl::uninitialized_copy(ct, ct + 2, arr);
    assert(CountTest::num() == 12);

    stl::destroy(arr, arr + 2);
    assert(CountTest::num() == 10);

    free(arr);
}


void testUninitialized()
{
    testUninitializedFillCase1();
    testUninitializedFillCase2();


    testUninitializedFillNCase1();
    testUninitializedFillNCase2();


    testUninitializedCopyCase1();
    testUninitializedCopyCase2();
}

//------------------------------------------------------------------------------


void testAllocCase1()//测试前后两次分配的内存是否在一个块里面
{
    stl::allocator<int> alloc;

    int *a = alloc.allocate(2);
    int *b = alloc.allocate(2);

    //这里不是2*sizeof(int)。因为指针类型为int*，步伐为4个字节，只需两步即可到达
    assert( b-a == 2);

    alloc.deallocate(a, 1);
    alloc.deallocate(b, 1);
}


void testAllocCase2()//测试回收的内存是否能够重复使用
{
    stl::allocator<int> alloc;
    int *a = alloc.allocate(6);
    int *b = alloc.allocate(6);

    assert( a != b);

    alloc.deallocate(b, 6);
    int *c = alloc.allocate(6);
    assert( b == c);

    alloc.deallocate(a, 6);
    int *d = alloc.allocate(6);
    assert( a == d);

    alloc.deallocate(c, 6);
    alloc.deallocate(d, 6);


    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    std::set<int*> sset;
    for(int i = 0; i < 32; ++i)
    {
        int *p = alloc.allocate(6);
        sset.insert(p);
    }

    assert(sset.size() == 32);

    std::set<int*>::iterator it, end = sset.end();
    for(it = sset.begin(); it != end; ++it)
    {
        alloc.deallocate(*it, 6);
    }

    for(int i = 0; i < 32; ++i)
    {
        int *p = alloc.allocate(6);
        assert( sset.find(p) != sset.end());
    }

    for(it = sset.begin(), end = sset.end(); it != end; ++it)
    {
        alloc.deallocate(*it, 6);
    }
}


void testAllocCase3()//测试用完free_list桶中32个节点
{
    stl::allocator<int> alloc;

    std::set<int*> sset;
    for(int i = 0; i < 32; ++i)
    {
        int *p = alloc.allocate(8);
        sset.insert(p);
    }

    assert(sset.size() == 32);

    for(int i = 0; i < 32; ++i)
    {
        int *p = alloc.allocate(8);
        sset.insert(p);
    }

    assert(sset.size() == 64);

    std::set<int*>::iterator it, end = sset.end();
    for(it = sset.begin(); it != end; ++it)
    {
        alloc.deallocate(*it, 8);
    }

    int *p = alloc.allocate(8);
    assert(sset.find(p) != end);
    alloc.deallocate(p, 8);
}



void testAllocCase4()//测试当分配的内存大于128字节时是否直接使用malloc分配的
{
    stl::allocator<int> alloc;

    int *p = alloc.allocate(100);
    free(p);
}


void testAlloc()
{
    testAllocCase1();
    testAllocCase2();
    testAllocCase3();
    testAllocCase4();
}



void testAllocator()
{
    testUninitialized();
    testConstruct();
    testAlloc();
}


}

