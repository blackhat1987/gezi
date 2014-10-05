/** 
 *  ==============================================================================
 * 
 *          \file   simple.cc
 *
 *        \author   chenghuige  
 *
 *          \date   2014-10-03 22:44:02.086230
 *  
 *   \Description  
 *
 *  ==============================================================================
 */

#include <iostream>
#include <stdio.h>
#include <unordered_map>
using namespace std;

struct Node
{
	int a = 3;
	unordered_map<int,int> m;
};

int main(int argc, char *argv[])
{
  Node node;
	cout << node.a;
  return 0;
}
