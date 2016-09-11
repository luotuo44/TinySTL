//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#include"testFunction.h"
#include"../bits/stl_function.h"

#include<assert.h>

#include<vector>
#include<string>
#include<list>
#include<set>
#include<iterator>
#include<sstream>
#include<algorithm>

#include"../utility"
#include"../bits/stl_algo.h"

namespace stl
{


void testArithmeticOpCase1()
{
    int ix = 34, iy = 5324;
    double dx = -12.89, dy = 0.2442;

    assert(plus<int>()(ix, iy) == (ix+iy));
    assert(plus<double>()(dx, dy) == (dx+dy));

    assert(minus<int>()(ix, iy) == (ix-iy));
    assert(minus<double>()(dx, dy) == (dx-dy));

    assert(multiplies<int>()(ix, iy) == (ix*iy));
    assert(multiplies<double>()(dx, dy) == (dx*dy));

    assert(divides<int>()(ix, iy) == (ix/iy));
    assert(divides<double>()(dx, dy) == (dx/dy));

    assert(modulus<int>()(ix, iy) == (ix%iy));


    std::string sx("hello"), sy("C++");
    assert(plus<std::string>()(sx, sy) == (sx+sy));
}


void testCompareOpCase1()
{
    int ix = 34, iy = 34;
    double dx = -12.89, dy = 0.2442;

    assert(equal_to<int>()(ix, iy) == (ix==iy));
    assert(equal_to<double>()(dx, dy) == (dx==dy));

    assert(not_equal_to<int>()(ix, iy) == (ix!=iy));
    assert(not_equal_to<double>()(dx, dy) == (dx!=dy));

    assert(less<int>()(ix, iy) == (ix<iy));
    assert(less<double>()(dx, dy) == (dx<dy));

    assert(greater<int>()(ix, iy) == (ix>iy));
    assert(greater<double>()(dx, dy) == (dx>dy));

    assert(less_equal<int>()(ix, iy) == (ix<=iy));
    assert(less_equal<double>()(dx, dy) == (dx<=dy));

    assert(greater_equal<int>()(ix, iy) == (ix>=iy));
    assert(greater_equal<double>()(dx, dy) == (dx>=dy));


    std::string sx("hello"), sy("C++");
    assert(equal_to<std::string>()(sx, sy) == (sx==sy));
    assert(not_equal_to<std::string>()(sx, sy) == (sx!=sy));
    assert(less<std::string>()(sx, sy) == (sx<sy));
    assert(greater<std::string>()(sx, sy) == (sx>sy));
    assert(less_equal<std::string>()(sx, sy) == (sx<=sy));
    assert(greater_equal<std::string>()(sx, sy) == (sx>=sy));
}



void testLogicalOpCase1()
{
    int ix = 15, iy = 0;
    bool bx = true, by = true;

    assert(logical_and<int>()(ix, iy) == (ix&&iy));
    assert(logical_and<bool>()(bx, by) == (bx&&by));

    assert(logical_or<int>()(ix, iy) == (ix||iy));
    assert(logical_or<bool>()(bx, by) == (bx||by));

    assert(logical_not<int>()(ix) == (!ix));
    assert(logical_not<int>()(iy) == (!iy));

    assert(logical_not<bool>()(bx) == (!bx));
    assert(logical_not<bool>()(by) == (!by));
}



void testBitOpCase1()
{
    int ix = 15, iy = 32;
    bool bx = true, by = false;

    assert(bit_and<int>()(ix, iy) == (ix&iy));
    assert(bit_and<bool>()(bx, by) == (bx&by));

    assert(bit_or<int>()(ix, iy) == (ix|iy));
    assert(bit_or<bool>()(bx, by) == (bx|by));


    assert(bit_xor<int>()(ix, iy) == (ix^iy));
    assert(bit_xor<bool>()(bx, by) == (bx^by));
}



void testIspCase1()
{
    int ix = 7, iy = 23;
    double dx = 4.231, dy = -0.232;

    assert(identity<int>()(ix) == ix);
    assert(identity<double>()(dy) == dy);


    assert((project1st<int, double>()(ix, dy)) == ix);
    assert((project2nd<int, double>()(iy, dx)) == dx);


    char c = 'c';
    std::string str("C++");
    pair<char, std::string> p(c, str);

    assert((select1st<pair<char, std::string> >()(p)) == c);
    assert((select2nd<pair<char, std::string> >()(p)) == str);
}



bool isOdd(int x)
{
    return x&1;
}


bool isEqual(int x, int y)
{
    return x == y;
}


bool minusOneEqual(int x, int y)
{
    return x-1 == y;
}


bool plusOneEqual(int x, int y)
{
    return x+1 == y;
}


void testBaseAdapterCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);

    assert(find_if(a1, a1+n1, bind2nd(greater<int>(), 4)) == a1+4);
    assert(find_if(a1, a1+n1, bind1st(less<int>(), 10)) == a1+n1);

    assert(find_if(a1, a1+n1, not1(bind2nd(greater<int>(), 4))) == a1);


    int a2[] = {-1, 0, 3, 4, 5, 6};

    pair<int*, int*> match_p = mismatch(a1, a1+n1, a2, not2(equal_to<int>()));
    assert(*match_p.first == 3 && *match_p.second == 3);


    assert(find_if(a1, a1+n1, not1(ptr_fun(isOdd))) == a1+1);
    match_p = mismatch(a1, a1+n1, a2, not2(ptr_fun(isEqual)));
    assert(*match_p.first == 3 && *match_p.second == 3);


    std::vector<int> vec;
    stl::transform(a1, a1+n1, std::back_inserter(vec), stl::compose1(stl::bind2nd(stl::plus<int>(), 3),  stl::bind2nd(stl::minus<int>(), 2)) );
    assert(vec.size()==n1 && stl::equal(a1, a1+n1, vec.begin(), plusOneEqual));
    vec.clear();


    stl::transform(a1, a1+n1, std::back_inserter(vec), stl::compose2(stl::multiplies<int>(), stl::bind2nd(stl::plus<int>(), 1), stl::bind2nd(stl::minus<int>(), 1)));
    std::vector<int> vec2;
    stl::transform(a1, a1+n1, a1, std::back_inserter(vec2), stl::multiplies<int>());
    //x^2 == (x-1) * (x+1) + 1
    assert(stl::equal(vec.begin(), vec.end(), vec2.begin(), plusOneEqual));
}



void testMemFunCase1()
{
    int a1[] = {2, 1, 5 ,6, 4};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    int a2[] = {11, 4, 67, 3, 14, 2};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    std::list<int> s1(a1, a1+n1);
    std::list<int> s2(a2, a2+n2);


    std::list< std::list<int>* > slist;
    slist.push_back(&s1);
    slist.push_back(&s2);

    //R (X::*p)(A)
    //<void, std::list<int, std::allocator<int> >, const int&>
    stl::for_each(slist.begin(), slist.end(), stl::bind2nd(stl::mem_fun(&std::list<int>::push_back), 0));

    assert(slist.front()->back() == 0);
    assert(slist.back()->back() == 0);


    //R (X::*p)()
    stl::for_each(slist.begin(), slist.end(), stl::mem_fun<void, std::list<int, std::allocator<int> > >(&std::list<int>::sort));
    assert(stl::adjacent_find(s1.begin(), s1.end(), stl::greater<int>()) == s1.end());
    assert(stl::adjacent_find(s2.begin(), s2.end(), stl::greater<int>()) == s2.end());


    //R (X::*p)()const
    std::ostringstream oss1;
    stl::transform(slist.begin(), slist.end(), std::ostream_iterator<size_t>(oss1, ""), stl::mem_fun(&std::list<int>::size));

    std::ostringstream oss2;
    std::transform(slist.begin(), slist.end(), std::ostream_iterator<size_t>(oss2, ""), std::mem_fun(&std::list<int>::size));

    assert(oss1.str() == oss2.str());



    //R (X::*p)(A)const
    std::set<int> ss1(a1, a1+n1);
    std::set<int> ss2(a2, a2+n2);
    std::list<std::set<int>* > slist2;
    slist2.push_back(&ss1);
    slist2.push_back(&ss2);

    //std::set::find有两个版本，const和non-const。由于在mem_fun中，没有具体std::set<int>类型变量
    //可以用于deduce，因此直接使用时会出现歧义。所以需要在这里确定使用哪个版本的find
    typedef std::set<int>::iterator (std::set<int>::*ConstFunc)(const int &)const;
    ConstFunc cf = &std::set<int>::find;

    std::list<std::set<int>::iterator> it_list1, it_list2;
    stl::transform(slist2.begin(), slist2.end(), std::back_inserter(it_list1), stl::bind2nd(stl::mem_fun(cf), 5));
    std::transform(slist2.begin(), slist2.end(), std::back_inserter(it_list2), std::bind2nd(std::mem_fun(cf), 5));

    assert(it_list1 == it_list2);
}


void testMemFunCase2()
{
    int a1[] = {2, 1, 5 ,6, 4};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);
    int a2[] = {11, 4, 67, 3, 14, 2};
    size_t n2 = sizeof(a2)/sizeof(a2[0]);
    std::list<int> s1(a1, a1+n1);
    std::list<int> s2(a2, a2+n2);


    std::list< std::list<int> > slist;
    slist.push_back(s1);
    slist.push_back(s2);


    //R (X::*p)(A)
    //<void, std::list<int, std::allocator<int> >, const int&>
    stl::for_each(slist.begin(), slist.end(), stl::bind2nd(stl::mem_fun_ref(&std::list<int>::push_back), 0));
    std::for_each(slist.begin(), slist.end(), std::bind2nd(std::mem_fun_ref(&std::list<int>::push_back), 0));
    assert(slist.front().back() == 0);
    assert(slist.back().back() == 0);


    //R (X::*p)()
    stl::for_each(slist.begin(), slist.end(), stl::mem_fun_ref<void, std::list<int, std::allocator<int> > >(&std::list<int>::sort));
    assert(stl::adjacent_find(slist.front().begin(), slist.front().end(), stl::greater<int>()) == slist.front().end());
    assert(stl::adjacent_find(slist.back().begin(), slist.back().end(), stl::greater<int>()) == slist.back().end());


    //R (X::*p)()const
    std::ostringstream oss1;
    stl::transform(slist.begin(), slist.end(), std::ostream_iterator<size_t>(oss1, ""), stl::mem_fun_ref(&std::list<int>::size));

    std::ostringstream oss2;
    std::transform(slist.begin(), slist.end(), std::ostream_iterator<size_t>(oss2, ""), std::mem_fun_ref(&std::list<int>::size));

    assert(oss1.str() == oss2.str());



    //R (X::*p)(A)const
    std::set<int> ss1(a1, a1+n1);
    std::set<int> ss2(a2, a2+n2);
    std::list<std::set<int> > slist2;
    slist2.push_back(ss1);
    slist2.push_back(ss2);


    //std::set::find有两个版本，const和non-const。由于在mem_fun中，没有具体std::set<int>类型变量
    //可以用于deduce，因此直接使用时会出现歧义。所以需要在这里确定使用哪个版本的find
    typedef std::set<int>::iterator (std::set<int>::*ConstFunc)(const int &)const;
    ConstFunc cf = &std::set<int>::find;

    std::list<std::set<int>::iterator> it_list1, it_list2;
    stl::transform(slist2.begin(), slist2.end(), std::back_inserter(it_list1), stl::bind2nd(stl::mem_fun_ref(cf), 5));
    std::transform(slist2.begin(), slist2.end(), std::back_inserter(it_list2), std::bind2nd(std::mem_fun_ref(cf), 5));

    assert(it_list1 == it_list2);
}



void testFunction()
{
    testArithmeticOpCase1();

    testCompareOpCase1();

    testLogicalOpCase1();

    testBitOpCase1();

    testIspCase1();


    testBaseAdapterCase1();

    testMemFunCase1();
    testMemFunCase2();

}

}
