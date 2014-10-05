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
	/**��data���л������file*/
	template<typename T>
	void save(const T& data, string file)
	{
		std::ofstream ofs(file.c_str(), std::ios::binary);
		cereal::BinaryOutputArchive oa(ofs); //�ı�������鵵�࣬ʹ��һ��ostream������
		oa(data);
	}

	template<typename T>
	void save_xml(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		 cereal::XMLOutputArchive oa(ofs); //�ı�������鵵�࣬ʹ��һ��ostream������
		 oa(CEREAL_NVP(data));
	}
	
	//ceral�������binary,json,xml��boost��binary,text,xml����text����json����
	template<typename T>
	void save_text(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		cereal::JSONOutputArchive oa(ofs); //�ı�������鵵�࣬ʹ��һ��ostream������
		oa(CEREAL_NVP(data));
	}

	template<typename T>
	void save_json(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		cereal::JSONOutputArchive oa(ofs); //�ı�������鵵�࣬ʹ��һ��ostream������
		oa(CEREAL_NVP(data));
	}

	/**���л���file��file�ж���data*/
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
			cereal::BinaryInputArchive ia(ifs); //�ı�������鵵�࣬ʹ��һ��ostream������
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
			cereal::XMLInputArchive ia(ifs); //�ı�������鵵�࣬ʹ��һ��ostream������
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
			cereal::JSONInputArchive ia(ifs); //�ı�������鵵�࣬ʹ��һ��ostream������
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
			cereal::JSONInputArchive ia(ifs); //�ı�������鵵�࣬ʹ��һ��ostream������
			ia(data);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	
	/**���л���file��file�ж���data*/
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
