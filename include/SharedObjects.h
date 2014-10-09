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
	//��������Ҫһ��map��ѯ �������Ժ���
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

		//����֧��PrecitorFactory::LoadPredictor���������ĺ��� ��ʵobject.init�ȵ�Ҳ����lambda����
		//����Load���Լ��������� ����ע�����۰�ȫ��������path+����һ���Ĳ���һ��object ����Դ�ĽǶ�
		//һ��path�Ͷ�Ӧһ��object ֻ��
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
