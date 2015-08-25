/** 
 *  ==============================================================================
 * 
 *          \file   test_map.cc
 *
 *        \author   chenghuige  
 *
 *          \date   2015-08-25 10:24:03.073912
 *  
 *   \Description  
 *
 *  ==============================================================================
 */

#include <iostream>
#include <stdio.h>
#include <map>
#include "common_util.h"
using namespace std;


struct Node
{
	Node() {cout << "construct\n";}
	~Node() {cout << "destruct\n";}
	void load() {cout << "load " << name << "\n";}
	string name;
};

int main(int argc, char *argv[])
{
	{
  map<string, shared_ptr<Node> > m;
	m["a"] = make_shared<Node>();
	m["a"]->load();

	shared_ptr<Node> node = make_shared<Node>();
	node->name = "abc";

	m["a"] = node;
	m["a"]->load();
	cout << "finish\n";
	}
	{
  map<string, Node > m;
	m["a"].load();

	Node node;
	node.name = "abc";

	m["a"] = node;
	m["a"].load();
	cout << "finish\n";
	}
  return 0;
}
