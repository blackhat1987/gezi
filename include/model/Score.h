/**
 * @file   Score.h
 * @author zhoushu
 * @date   Mon Mar 26 15:46:20 2012
 * 
 * @brief  
 * 
 * 
 */

#ifndef _SCORE_H_
#define _SCORE_H_
class Score
{
public:
    Score();
    /** 
     * 添加分值
     * 
     * @param item 
     */
    void addItem(double item);

    /** 
     * 获取分值个数
     * 
     * 
     * @return 
     */
    int getItemNum();
    
    /** 
     * 返回第n个分值
     * 
     * @param n 
     * 
     * @return 
     */
    double itemAtIndex(int n);
    
    inline double& operator[](int index)
    {
      return _items[index];
    }

    inline double value(int index = 0)
    {
      return _items[index];
    }
public:
    virtual ~Score();

private:
    double *_items;
    int _nitem;
    int _size;
};

#endif
