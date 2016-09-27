/**
 * @file   Score.cpp
 * @author zhoushu
 * @date   Tue Mar 27 16:16:21 2012
 * 
 * @brief  
 * 
 * 
 */

#include "Score.h"
#include "stddef.h"
#include "string.h"

Score::~Score()
{
  if (NULL != _items)
  {
    delete[] _items;
  }
}

Score::Score()
{
  _nitem = 0;
  _size = 100;
  _items = new double[_size];
}

void Score::addItem(double item)
{
  if (_nitem == _size)
  {
    double *newbuf = new double[_nitem + 100];
    memcpy(newbuf, _items, sizeof (double) * _nitem);
    delete[] _items;
    _items = newbuf;
    _size += 100;
  }

  _items[_nitem] = item;
  _nitem++;
}

double Score::itemAtIndex(int n)
{
  if (n >= _nitem)
  {
    return _items[_nitem - 1];
  }

  return _items[n];
}

int Score::getItemNum()
{
  return _nitem;
}



