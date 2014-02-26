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
   * @param const char*: ģ��·��
   */
  //    Model(const char* path);

  /** 
   * ģ�ͼ��ؽӿ�
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
   * ģ�ͳ�ʼ���ӿ�
   * 
   * 
   * @return 
   */
  int init()
  {
    return 0;
  }

  /** 
   * Ԥ��ӿ�  ���ݾɽӿ�, ScoreҲ��Ϊ�˼��ݾɽӿ� 
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

  //�½ӿ�

  virtual void predict(Feature& feature, vector<double>& result)
  {

  }

	//��򵥽ӿ�
	virtual double Predict(Feature& feature)
	{
		return 0;
	}

  /** 
   * ����ӿ�
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
   * ����model id
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
   * ��ȡmodel_id
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
