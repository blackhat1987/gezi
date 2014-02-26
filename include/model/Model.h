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
#include <vector>
using gezi::Feature;
using std::vector;

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

  virtual int load(const char*)
  {
  }

  virtual ~Model()
  {
  }

  Model(string modelType = "", int modelId = 0)
  :_modelType(modelType), _modelId(modelId)
  {
    
  }
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
   * 预测接口  兼容旧接口, Score也是为了兼容旧接口 
   * 
   * @param Feature * 
   * @param  Score * 
   * 
   * @return 
   */
  virtual int predict(Feature *, Score *)
  {
    return 0;
  }

  //新接口

  virtual void predict(Feature& feature, vector<double>& result)
  {

  }

	//最简单接口
	virtual double Predict(Feature& feature)
	{
		return 0;
	}

  /** 
   * 清理接口
   * 
   */
  virtual void finalize()
  {

  }

  //Feature::nodes() not const TODO

  double predict(Feature& feature, int index = 0)
  {
    Score score;
    predict(&feature, &score);
    return score.itemAtIndex(index);
  }

  double predict(Feature* feature, int index = 0)
  {
    Score score;
    predict(feature, &score);
    return score.itemAtIndex(index);
  }

  /**
   * 设置model id
   *
   */
  virtual void setModelId(int id)
  {
    _modelId = id;
  }

  void setModelType(std::string type)
  {
    _modelType = type;
  }

  void setModelPath(std::string path)
  {
    _modelPath = path;
  }

  /**
   * 获取model_id
   *
   */
  virtual int getModelId() const
  {
    return _modelId;
  }

  std::string getModelPath()
  {
    return _modelPath;
  }

  std::string getModelType()
  {
    return _modelType;
  }

  std::string path()
  {
    return _modelPath;
  }

  std::string type()
  {
    return _modelType;
  }
  
  int id()
  {
    return _modelId;
  }

  inline void printInfo()
  {
    LOG_TRACE("The model id [%d] model type [%s] model path [%s]", _modelId, _modelType.c_str(), _modelPath.c_str());
  }

private:
  int _modelId;
  std::string _modelType;
  std::string _modelPath;
};

#endif
