//
// main.cpp
//
//  Created on: 26.02.2017
//      Author: ho11owman
//

#include "Beans.h"
#include "ref/bean_stream.h"



int main(int t_argc, char* t_argv[])
{
    BasicBeanClass bbc {};
    ref::json_stream js;
    js << bbc;
    return 0;
}

