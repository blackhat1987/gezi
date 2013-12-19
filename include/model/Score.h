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
     * ��ӷ�ֵ
     * 
     * @param item 
     */
    void addItem(double item);

    /** 
     * ��ȡ��ֵ����
     * 
     * 
     * @return 
     */
    int getItemNum();
    
    /** 
     * ���ص�n����ֵ
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
