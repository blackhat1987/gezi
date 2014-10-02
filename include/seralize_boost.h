/**
 *  ==============================================================================
 *
 *          \file   seralize_boost.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-01 21:46:59.712921
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SERALIZE_BOOST_H_
#define SERALIZE_BOOST_H_

#include <fstream>
#include <iostream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>

//#include "serialization/shared_ptr.hpp"
//#include "serialization/shared_ptr_helper.hpp"
//#include "serialization/unique_ptr.hpp"

#include <boost/serialization/utility.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include "serialization/unordered_map_serialize.h"
#include "serialization/unordered_set_serialize.h"

#include "string_util.h"
#include <boost/serialization/nvp.hpp>
#define GEZI_SERIALIZATION_NVP(name)\
	boost::serialization::make_nvp(gezi::conf_trim(#name).c_str(), name)
//namespace serialize = serialize_util;  //这个地方会和creal冲突。。。 尽量不用这种namespace和函数名容易混淆冲突？
//.. / .. / include / cereal / cereal.hpp : 378 : 18 : error : expected primary - expression before '(' token
//serialize(*self, const_cast<T &>(t));

namespace serialize_util {
	using std::string;
	/**将data序列化输出到file*/
	template<typename T>
	void save(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		boost::archive::binary_oarchive oa(ofs, std::ios::binary); //文本的输出归档类，使用一个ostream来构造
		oa << data;
	}

	template<typename T>
	void save_xml(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		boost::archive::xml_oarchive oa(ofs); //文本的输出归档类，使用一个ostream来构造
		oa & BOOST_SERIALIZATION_NVP(data);
	}

	template<typename T>
	void save_json(const T& data, string file)
	{
		save_xml(data, file);
	}

	//默认是存binary 如果#define XML_SERALIZE则存为xml格式
	template<typename T>
	void Save(const T& data, string file)
	{
#ifndef XML_SERALIZE 
		save(data, file);
#else 
		save_xml(data, file);
#endif
	}

	template<typename T>
	void SaveText(const T& data, string file)
	{
#ifndef XML_SERALIZE 
		save_text(data, file);
#else 
		save_xml(data, file);
#endif
	}

	template<typename T>
	void save_text(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		boost::archive::text_oarchive oa(ofs); //文本的输出归档类，使用一个ostream来构造
		oa << data;
	}

	/**序列化从file中file中读出data*/
	template<typename T>
	bool load(string file, T& data)
	{
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		try
		{
			boost::archive::binary_iarchive ia(ifs, std::ios::binary); //文本的输出归档类，使用一个ostream来构造
			ia >> data;
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
			boost::archive::xml_iarchive ia(ifs); //文本的输出归档类，使用一个ostream来构造
			ia & BOOST_SERIALIZATION_NVP(data);
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
		return load_xml(file, data);
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
			boost::archive::text_iarchive ia(ifs); //文本的输出归档类，使用一个ostream来构造
			ia >> data;
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	template<typename T>
	bool Load(string file, T& data)
	{
#ifndef XML_SERALIZE
		return load(file, data);
#else
		return load_xml(file, data);
#endif
	}

	template<typename T>
	bool LoadText(string file, T& data)
	{
#ifndef XML_SERALIZE
		return load_text(file, data);
#else
		return load_xml(file, data);
#endif
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
	bool load_json(T& data, string file)
	{
		return load_json(file, data);
	}

	template<typename T>
	bool load_text(T& data, string file)
	{
		return load_text(file, data);
	}

	template<typename T>
	bool Load(T& data, string file)
	{
		return Load(file, data);
	}

	template<typename T>
	bool LoadText(T& data, string file)
	{
		return LoadText(file, data);
	}

}

#endif  //----end of SERALIZE_BOOST_H_
