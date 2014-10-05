/**
 *  ==============================================================================
 *
 *          \file   serialize_cereal.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-01 21:47:08.615737
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SERIALIZE_CEREAL_H_
#define SERIALIZE_CEREAL_H_

#include <fstream>
#include <iostream>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>

namespace serialize_util {
	using std::string;
	/**将data序列化输出到file*/
	template<typename T>
	void save(const T& data, string file)
	{
		std::ofstream ofs(file.c_str(), std::ios::binary);
		cereal::BinaryOutputArchive oa(ofs); //文本的输出归档类，使用一个ostream来构造
		oa(data);
	}

	template<typename T>
	void save_xml(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		 cereal::XMLOutputArchive oa(ofs); //文本的输出归档类，使用一个ostream来构造
		 oa(CEREAL_NVP(data));
	}
	
	//ceral的输出是binary,json,xml而boost是binary,text,xml这里text按照json处理
	template<typename T>
	void save_text(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		cereal::JSONOutputArchive oa(ofs); //文本的输出归档类，使用一个ostream来构造
		oa(CEREAL_NVP(data));
	}

	template<typename T>
	void save_json(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		cereal::JSONOutputArchive oa(ofs); //文本的输出归档类，使用一个ostream来构造
		oa(CEREAL_NVP(data));
	}

	/**序列化从file中file中读出data*/
	template<typename T>
	bool load(string file, T& data)
	{
		std::ifstream ifs(file.c_str(), std::ios::binary);
		if (!ifs.is_open())
		{
			return false;
		}
		try
		{
			cereal::BinaryInputArchive ia(ifs); //文本的输出归档类，使用一个ostream来构造
			ia(data);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	template<typename T>
	bool load_xml(string file, T& data)
	{
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		try
		{
			cereal::XMLInputArchive ia(ifs); //文本的输出归档类，使用一个ostream来构造
			ia(CEREAL_NVP(data));
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	template<typename T>
	bool load_text(string file, T& data)
	{
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		try
		{
			cereal::JSONInputArchive ia(ifs); //文本的输出归档类，使用一个ostream来构造
			ia(data);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	template<typename T>
	bool load_json(string file, T& data)
	{
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		try
		{
			cereal::JSONInputArchive ia(ifs); //文本的输出归档类，使用一个ostream来构造
			ia(data);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	
	/**序列化从file中file中读出data*/
	template<typename T>
	bool load(T& data, string file)
	{
		return load(file, data);
	}

	template<typename T>
	bool load_xml(T& data, string file)
	{
		return load_xml(file, data);
	}

	template<typename T>
	bool load_text(T& data, string file)
	{
		return load_text(file, data);
	}

	template<typename T>
	bool load_json(T& data, string file)
	{
		return load_json(file, data);
	}

}  //----end of namespace gezi

#endif  //----end of SERIALIZE_CEREAL_H_
