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
      return items_[index];
    }

public:
    virtual ~Score();

private:
    double *items_;
    int nitem_;
    int size_;
};

#endif
