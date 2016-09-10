//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#include"testFunction.h"
#include"../bits/stl_function.h"

#include<assert.h>

#include<string>

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
}


void testFunction()
{
    testArithmeticOpCase1();

    testCompareOpCase1();

    testLogicalOpCase1();

    testBitOpCase1();

    testIspCase1();


    testBaseAdapterCase1();

}

}
