/**
 * @file   Model.h
 * @author zhoushu
 * @date   Mon Mar 26 15:30:43 2012
 * 
 * @brief  
 * 
 * 
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include "feature/Feature.h"
#include "Score.h"

using gezi::Feature;
class Model
{
public:

    /**
     *
     * @param const char*: 模型路径
     */
//    Model(const char* path);

    /** 
     * 模型加载接口
     * 
     * @param const char * 
     * 
     * @return 
     */

    virtual int load(const char*) = 0;
    virtual ~Model(){}
    /** 
     * 模型初始化接口
     * 
     * 
     * @return 
     */
    int init()
    {
      return 0;
    }

    /** 
     * 预测接口
     * 
     * @param Feature * 
     * @param  Score * 
     * 
     * @return 
     */
    virtual int predict(Feature *, Score *) = 0;

    /** 
     * 清理接口
     * 
     */
    virtual void finalize()
    {
      
    }
    
    //Feature::nodes() not const TODO
    double predict(Feature& feature)
    {
      Score score;
      predict(&feature, &score);
      return score.itemAtIndex(0);
    }
    
    double predict(Feature* feature)
    {
      Score score;
      predict(feature, &score);
      return score.itemAtIndex(0);
    }

    /**
     * 设置model id
     *
     */
    virtual void setModelId(int id)
    {
        modelId_ = id;	    
    }
    
    void setModelType(std::string type)
    {
      modelType_ = type;
    }
    
    void setModelPath(std::string path)
    {
      modelPath_ = path;
    }
    /**
     * 获取model_id
     *
     */
    virtual int getModelId() const
    {
        return modelId_;
    }
    
    std::string getModelPath()
    {
      return modelPath_;
    }
    std::string getModelType()
    {
      return modelType_;
    }
    inline void printInfo()
    {
      LOG_TRACE("The model id [%d] model type [%s] model path [%s]", modelId_, modelType_.c_str(), modelPath_.c_str());
    }

private:
    int modelId_;
    std::string modelType_;
    std::string modelPath_;
};

#endif
