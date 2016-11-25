//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#include<iostream>
#include<vector>
#include<iterator>
#include<sstream>
#include<algorithm>
#include<string>

#include"Test/testAlloc.h"
#include"Test/testAlgorithm.h"
#include"Test/testNumeric.h"
#include"Test/testAlgobase.h"
#include"Test/testAlgo.h"
#include"Test/testFunction.h"
#include"Test/testIterator.h"
#include"Test/testVector.h"
#include"Test/testList.h"
#include"Test/testDeque.h"

using namespace std;



int main()
{
    stl::testAllocator();
    stl::testNumeric();
    stl::testAlgoBase();
    stl::testAlgo();
    stl::testFunction();
    stl::testItertor();
    stl::testVector();
    stl::testList();
    stl::testDeque();

    cout << "Hello World!" << endl;
    return 0;
}

