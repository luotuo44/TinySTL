//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#include"testIterator.h"


#include"../iterator"
#include"../algorithm"


#include<assert.h>

#include<vector>
#include<list>
#include<set>

namespace stl
{



void testInserterCase1()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n1 = sizeof(a1)/sizeof(a1[0]);


    std::vector<int> vec;
    stl::copy(a1, a1+n1, stl::back_inserter(vec));

    assert(stl::equal(a1, a1+n1, vec.begin()) && (n1==vec.size()));



    std::list<int> alist;
    stl::copy(a1, a1+n1, stl::front_inserter(alist));
    alist.reverse();

    assert(stl::equal(a1, a1+n1, alist.begin()) && (n1 == alist.size()));


    std::set<int> sset;
    stl::copy(a1, a1+n1, stl::inserter(sset, sset.end()));
    assert(stl::equal(a1, a1+n1, sset.begin()) && (n1 == sset.size()));


    std::vector<int> vv;
    vv.push_back(1);

    //用于测试迭代器失效的情况
    stl::copy(a1, a1+n1, stl::inserter(vv, vv.begin()));
    //vv.pop_back();
    assert(stl::equal(a1, a1+n1, vv.begin()) && (n1==vv.size()-1));
}





//================================================================================

void testItertor()
{
    testInserterCase1();
}


}
