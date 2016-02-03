/** 
 *  ==============================================================================
 * 
 *          \file   gdb_main.cc
 *
 *        \author   chenghuige  
 *
 *          \date   2016-02-03 12:45:49.750038
 *  
 *   \Description  
 *
 *  ==============================================================================
 */

#include <iostream>
#include <stdio.h>

#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
  vector<float> v = {1, 2, 3, 4, 4.5};
	v[1] += 0.3;
  return 0;
}
