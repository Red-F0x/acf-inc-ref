//
// main.cpp
//
//  Created on: 26.02.2017
//      Author: ho11owman
//

#include "ref/bean_traits.h"
#include "ref/bean_stream.h"

#include "Beans.h"

int main(int t_argc, char* t_argv[])
{
    BasicBeanClass bbc {};
    ref::json_stream js;
    js << bbc;
    return 0;
}

