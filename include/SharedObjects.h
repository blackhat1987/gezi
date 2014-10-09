/**
 *  ==============================================================================
 *
 *          \file   SharedObjects.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 14:47:56.279435
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SHARED_OBJECTS_H_
#define SHARED_OBJECTS_H_
#include "common_util.h"
namespace gezi {

	template<typename Obj>
	static Obj ConstructObj(string path)
	{
		Obj obj;
		obj.Load(path);
		return obj;
	}

	template<typename Obj, typename Func>
	static Obj ConstructObj(Func func)
	{
		string path = func();
		Obj obj;
		obj.Load(path);
		return obj;
	}
	//代价是需要一次map查询 几乎可以忽略
	template<typename T>
	class SharedObjects
	{
	public:
		static T& Instance(string path)
		{
			static map<string, T> _objectMap;
			auto iter = _objectMap.find(path);
			if (iter != _objectMap.end())
			{
				return iter->second;
			}
			else
			{
				auto& object = _objectMap[path];
				object.Load(path);
				return object;
			}
		}

		//这样支持PrecitorFactory::LoadPredictor类似这样的函数 其实object.init等等也可以lambda传入
		//甚至Load可以加其它参数 但是注意理论安全的做法是path+参数一样的才是一个object 从资源的角度
		//一个path就对应一个object 只读
		template<typename Func>
		static T& Instance(string path, Func func)
		{
			static map<string, T> _objectMap;
			auto iter = _objectMap.find(path);
			if (iter != _objectMap.end())
			{
				return iter->second;
			}
			else
			{
				return _objectMap[path] = func(path);
			}
		}

		static T& instance(string path)
		{
			static map<string, T> _objectMap;
			auto iter = _objectMap.find(path);
			if (iter != _objectMap.end())
			{
				return iter->second;
			}
			else
			{
				auto& object = _objectMap[path];
				object.load(path);
				return object;
			}
		}
	protected:
	private:

	};

}  //----end of namespace gezi

#endif  //----end of SHARED_OBJECTS_H_
