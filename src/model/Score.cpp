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
  if (NULL != items_)
  {
    delete[] items_;
  }
}

Score::Score()
{
  nitem_ = 0;
  size_ = 100;
  items_ = new double[size_];
}

void Score::addItem(double item)
{
  if (nitem_ == size_)
  {
    double *newbuf = new double[nitem_ + 100];
    memcpy(newbuf, items_, sizeof (double) * nitem_);
    delete[] items_;
    items_ = newbuf;
    size_ += 100;
  }

  items_[nitem_] = item;
  nitem_++;
}

double Score::itemAtIndex(int n)
{
  if (n >= nitem_)
  {
    return items_[nitem_ - 1];
  }

  return items_[n];
}

int Score::getItemNum()
{
  return nitem_;
}



