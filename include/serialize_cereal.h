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
#include <sstream>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/vector.hpp>
#ifdef USE_FOLLY_VECTOR
#include <cereal/types/fbvector.hpp>
#endif // USE_FOLLY_VECTOR
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

#include <cereal/types/eigen.hpp>

namespace serialize_util {
	using std::string;

	template<typename T>
	string save(const T& data)
	{
		std::stringstream ss;
		//cereal::JSONOutputArchive oa(ss); //ע�����л���json��string cereal����bug�� ��һ��} ���load��ʱ���쳣
		//oa(CEREAL_NVP(data));
		cereal::BinaryOutputArchive oa(ss);
		oa(data);
		return ss.str();
	}
	
	//template<typename T>
	//T load(string input)
	//{
	//	T data;
	//	std::stringstream ss;
	//	ss << input;
	//	cereal::JSONInputArchive ia(ss); 
	//	ia(data);
	//	return data;
	//}
	template<typename T>
	T load(string input)
	{
		T data;
		std::stringstream ss(input);
		cereal::BinaryInputArchive ia(ss);
		ia(data);
		//cereal::JSONInputArchive ia(ss); 
		//ia(CEREAL_NVP(data));
		return data;
	}

	template<typename T>
	void load_from_str(string input, T& data)
	{
		std::stringstream ss(input);
		cereal::BinaryInputArchive ia(ss);
		ia(data);
		//cereal::JSONInputArchive ia(ss); 
		//ia(CEREAL_NVP(data));
	}

	template<typename T>
	void load_from_str(T& data, string input)
	{
		std::stringstream ss(input);
		cereal::BinaryInputArchive ia(ss);
		ia(data);
		//cereal::JSONInputArchive ia(ss); 
		//ia(CEREAL_NVP(data));
	}

	/**��data���л������file*/
	template<typename T>
	void save(const T& data, string file)
	{
		std::ofstream ofs(file.c_str(), std::ios::binary);
		cereal::BinaryOutputArchive oa(ofs); 
		oa(data);
	}

	template<typename T>
	void save_xml(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		 cereal::XMLOutputArchive oa(ofs); 
		 oa(CEREAL_NVP(data));
	}
	
	//ceral�������binary,json,xml��boost��binary,text,xml����text����json����
	template<typename T>
	void save_text(const T& data, string file)
	{
		std::ofstream ofs(file.c_str());
		cereal::JSONOutputArchive oa(ofs); 
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
			cereal::BinaryInputArchive ia(ifs); 
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
			cereal::XMLInputArchive ia(ifs); 
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
			cereal::JSONInputArchive ia(ifs); 
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
			cereal::JSONInputArchive ia(ifs); 
			ia(CEREAL_NVP(data));
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
