//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#include<iostream>
#include<vector>
#include<iterator>
#include<sstream>
#include<algorithm>
#include<string>

#include"memory"
#include"Test/testAlloc.h"
#include"Test/testAlgorithm.h"
#include"Test/testNumeric.h"
#include"Test/testAlgobase.h"
#include"Test/testAlgo.h"
#include"numeric"

using namespace std;



int main()
{
    stl::testAllocator();
    stl::testNumeric();
    stl::testAlgoBase();
    stl::testAlgo();

    cout << "Hello World!" << endl;
    return 0;
}

