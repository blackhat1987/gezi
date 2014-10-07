/**
 *  ==============================================================================
 *
 *          \file   file_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-17 16:41:16.127829
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FILE_UTIL_H_
#define FILE_UTIL_H_
#include "common_def.h"
#include "hashmap_util.h"
#include <glog/logging.h>
#define  BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp> //@TODO 尽管define仍然c++0x会造成copy_file失败
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <map>
#include <set>
#include <string>
#include "format.h"
using std::map;
using std::set;
using std::string;

namespace bfs = boost::filesystem;
//---------------------------for file save load
namespace gezi {

	//forced copy
	inline void copy_file(string src, string dest)
	{
		ifstream infile(src, std::ios_base::binary);
		ofstream outfile(dest, std::ios_base::binary);
		outfile << infile.rdbuf();
	}
	inline void try_create_dir(string dir)
	{
		if (!bfs::exists(dir))
		{
			LOG(WARNING) << dir << " not exitst, will create first";
#ifdef __GNUC__
			//mkdir(dir.c_str());            //boost create_directories 是跨平台 但是当前版本有bug
			EXECUTE(format("mkdir {}", dir));
#else
			bfs::create_directories(dir); //@FIXME以前没遇到 现在需要 export LC_ALL="C"
#endif // __GNUC__
		}
	}

	inline std::string read_file(const std::string& infile)
	{
		std::ifstream ifs(infile.c_str());
		return boost::trim_copy(std::string((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>()));
	}

	inline void write_file(string content, string outfile)
	{
		std::ofstream ofs(outfile.c_str());
		ofs << content;
	}

	template<typename Container>
	bool file_to_set(const std::string& infile, Container& container)
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		std::istream_iterator<T> data_begin(ifs);
		std::istream_iterator<T> data_end;
		std::copy(data_begin, data_end, std::inserter(container, container.begin()));
		return true;
	}

	//适用于单列文本

	template<typename Container>
	bool file_to_vec(const std::string& infile, Container& container)
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		if (!ifs.is_open())
		{
			return false;
		}
		std::istream_iterator<T> data_begin(ifs);
		std::istream_iterator<T> data_end;
		std::copy(data_begin, data_end, std::back_inserter(container));

		foreach(T& value, container)
		{
			boost::trim(value);
		}
		return true;
	}

	//@TODO read_lines_safe
	inline vector<string> read_lines(string infile)
	{
		AutoTimer timer("read_lines", 1);
		vector<string> vec;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			vec.push_back(line);
		}
		return vec;
	}

	inline vector<string> read_lines_noempty(string infile)
	{
		vector<string> vec;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			if (!line.empty())
			{
				vec.push_back(line);
			}
		}
		return vec;
	}

	inline vector<string> read_lines(string infile, string ignore)
	{
		AutoTimer timer("read_lines", 3);
		vector<string> vec;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			if (line.empty() || startswith(line, ignore))
			{
				continue;
			}

			vec.push_back(line);
		}
		return vec;
	}

	inline vector<string> read_lines(ifstream& ifs)
	{
		vector<string> vec;
		string line;
		while (getline(ifs, line))
		{
			//boost::trim(line);
			vec.push_back(line);
		}
		return vec;
	}

	inline void read_lines(string infile, vector<string>& vec)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vec.push_back(line);
		}
	}

	template<typename T>
	inline void write_lines(vector<T>& lines, string file)
	{
		std::ofstream ofs(file.c_str());

		foreach(T line, lines)
		{
			ofs << line << endl;
		}
	}


	//单列 file_

	template<typename Set>
	inline void read_set(string infile, Set& container)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			container.insert(line);
		}
	}

	/*namespace file
	{*/
	inline set<string> to_set(string infile)
	{
		set<string> container;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			container.insert(line);
		}
		return container;
	}
	//}

	inline unordered_set<string> to_hashset(string infile)
	{
		unordered_set<string> container;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			container.insert(line);
		}
		return container;
	}

	//多列 read_to

	inline void read_to_set(const std::string& infile, std::set<std::string>& container,
		int index = 0, string sep = "\t ")
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.insert(vec[index]);
		}
	}

	inline void read_to_set(const std::string& infile, unordered_set<std::string>& container,
		int index = 0, string sep = "\t ")
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.insert(vec[index]);
		}
	}

	template<typename Container>
	void read_to_set(const std::string& infile, Container& container, int index = 0, string sep = "\t ")
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.insert(boost::lexical_cast<T>(vec[index]));
		}
	}

	inline void read_to_vec(const std::string& infile, std::vector<std::string>& container,
		int index = 0, string sep = "\t ")
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.push_back(vec[index]);
		}
	}

	inline std::vector<std::string> read_to_vec(const std::string& infile, int index = 0, string sep = "\t ")
	{
		vector<string> container;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.push_back(vec[index]);
		}
		return container;
	}

	template<typename Container>
	void read_to_vec(const std::string& infile, Container& container, int index = 0, string sep = "\t ")
	{
		typedef typename Container::value_type T;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.push_back(boost::lexical_cast<T>(vec[index]));
		}
	}

	template<typename T>
	vector<T> read_to_vec(const std::string& infile, int index = 0, string sep = "\t ")
	{
		vector<T> container;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.push_back(boost::lexical_cast<T>(vec[index]));
		}
		return container;
	}

	template<typename Container, typename Container2>
	void read_to_vec(const std::string& infile, Container& container, Container2& container2, int index = 0, int index2 = 1, string sep = "\t ")
	{
		typedef typename Container::value_type T;
		typedef typename Container2::value_type U;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container.push_back(boost::lexical_cast<T>(vec[index]));
			container2.push_back(boost::lexical_cast<U>(vec[index2]));
		}
	}
	//TODO better method...

	inline void read_map(const std::string& infile, std::map<std::string, std::string>& container,
		string sep = "\t", int key_idx = 0, int value_idx = 1)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container[boost::trim_copy(vec[key_idx])] = boost::trim_copy(vec[value_idx]);
		}
	}

	inline void read_map(const std::string& infile, unordered_map<std::string, std::string>& container,
		string sep = "\t", int key_idx = 0, int value_idx = 1)
	{
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			container[boost::trim_copy(vec[key_idx])] = boost::trim_copy(vec[value_idx]);
		}
	}

	template<typename Container>
	void read_map(const std::string& infile, Container& container, string sep = "\t",
		int key_idx = 0, int value_idx = 1)
	{
		//  typedef typename Container::key_type T;
		typedef typename Container::mapped_type U;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			vector<string> vec;
			boost::split(vec, line, is_any_of(sep));
			//    container[boost::lexical_cast<T>(vec[key_idx])] = boost::lexical_cast<U>(vec[value_idx]);
			container[boost::trim_copy(vec[key_idx])] = boost::lexical_cast<U>(boost::trim_copy(vec[value_idx]));
		}
	}

	inline unordered_map<string, int> to_identifer_hashmap(string infile, int start = 0)
	{
		unordered_map<string, int> m;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			m[line] = start++;
		}
		return m;
	}

	inline map<string, int> to_identifer_map(string infile, int start = 0)
	{
		map<string, int> m;
		std::ifstream ifs(infile.c_str());
		string line;
		while (getline(ifs, line))
		{
			boost::trim(line);
			m[line] = start++;
		}
		return m;
	}

	template<typename Map>
	void write_map(const Map& m, const std::string& ofile, const std::string& sep = "\t")
	{
		ofstream ofs(ofile.c_str());
		typedef typename Map::value_type Pair;

		foreach(Pair& item, m)
		{
			ofs << m.first << sep << m.second << endl;
		}
	}

	/**
	* 注意 write_ve 与 read_vec配合使用, 只适用于_Node 是简单类型的情况比如int,float struct{int,float}
	*/
	template<typename _Node>
	void write_vec(const std::vector<_Node>& vec, const std::string& file)
	{
		//不输出长度
		std::ofstream ofs(file.c_str(), std::ios::binary);
		ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node)* vec.size());
	}

	template<typename _Node>
	bool read_vec(const std::string& file, std::vector<_Node>& vec)
	{
		std::ifstream ifs(file.c_str(), std::ios::binary);
		if (!ifs.is_open())
			return false;
		vec.clear();
		ifs.seekg(0, std::ios::end);
		int length = ifs.tellg(); //FIXME big file?
		ifs.seekg(0, std::ios::beg);
		vec.resize(length / sizeof (_Node));
		ifs.read(reinterpret_cast<char*> (&vec[0]), length);
		return true;
	}

	template<typename T>
	void write_elem(const T& elem, const std::string& file)
	{
		std::ofstream ofs(file.c_str());
		ofs << elem;
	}

	template<typename T>
	bool read_elem(const std::string& file, T& elem)
	{
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
			return false;
		ifs >> elem;
		return true;
	}

	template<typename _Node>
	void write_vec2d(const std::vector<std::vector<_Node> >& vec, std::ofstream& ofs)
	{
		size_t row_len = vec.size();
		if (!row_len)
			return;
		for (size_t i = 0; i < row_len; i++)
		{
			int len = (int)vec[i].size();
			ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
			if (!len)
				continue;
			ofs.write(reinterpret_cast<const char*> (&vec[i][0]), sizeof (_Node)* vec[i].size());
		}
	}

	template<typename _Node>
	void write_vec2d(const std::vector<std::vector<_Node> >& vec, const std::string& file)
	{
		std::ofstream ofs(file.c_str(), std::ios::binary);
		size_t row_len = vec.size();
		ofs.write(reinterpret_cast<const char*> (&row_len), sizeof (row_len));
		write_vec2d(vec, ofs);
	}

	template<typename _Node>
	bool read_vec2d(const std::string& file, std::vector<std::vector<_Node> >& vec)
	{
		std::ifstream ifs(file.c_str(), std::ios::binary);
		if (!ifs.is_open())
			return false;
		vec.clear();
		//size_t total_len;
		int total_len; //TODO check 相关词的时候write 的是int
		ifs.read(reinterpret_cast<char*> (&total_len), sizeof (total_len));
		if (!total_len)
			return false;
		vec.resize(total_len);
		for (int i = 0; i < total_len; i++)
		{
			int len;
			ifs.read(reinterpret_cast<char*> (&len), sizeof (len));
			if (!len)
				continue;
			vec[i].resize(len);
			ifs.read(reinterpret_cast<char*> (&vec[i][0]), sizeof (_Node)* len);
		}
		return true;
	}

	class Vec2dWriter
	{
	public:

		Vec2dWriter(const std::string& file)
			: _ofs(file.c_str(), std::ios::binary)
		{
		}

		template<typename _Node>
		void write(const std::vector<_Node>& vec)
		{
			int len = (int)vec.size();
			_ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
			if (!len)
				return;
			_ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node)* len);
		}

		template<typename _Iter>
		void write(_Iter begin, _Iter end)
		{
			typedef typename _Iter::value_type value_type;
			int len = std::distance(begin, end);
			_ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
			if (!len)
				return;
			while (begin != end)
			{
				_ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
			}
		}

		void close()
		{
			_ofs.close();
		}
	private:
		std::ofstream _ofs;
	};

	class VecWriter
	{
	public:

		VecWriter(const std::string& file)
			: _ofs(file.c_str(), std::ios::binary)
		{
		}

		template<typename _Node>
		void write(const std::vector<_Node>& vec)
		{
			int len = (int)vec.size();
			_ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node)* len);
		}

		template<typename _Iter>
		void write(_Iter begin, _Iter end)
		{
			typedef typename _Iter::value_type value_type;
			while (begin != end)
			{
				_ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
			}
		}

		void close()
		{
			_ofs.close();
		}
	private:
		std::ofstream _ofs;
	};


#define OBJ_PATH(obj, path)\
	format("{}/{}.bin", path, gezi::conf_trim(#obj))

#include "serialize_util.h"
	template<typename T>
	inline void save_shared_ptr(T obj, string path, string name)
	{
		string outName = "";
		string outFile = format("{}/{}.bin", path, name);
		if (obj != nullptr)
		{
			//#ifdef NO_CEREAL
			obj->Save(outFile);
			//#else
			//			serialize_util::save(obj, outFile);
			//#endif
			outName = obj->Name();
		}

		write_file(outName, format("{}/{}.name.txt", path, name));
	}

	template<typename T>
	inline void save_shared_ptr_astext(T obj, string name)
	{
		if (obj != nullptr)
		{
			obj->SaveText(name);
		}
	}

	template<typename T>
	inline void save_shared_ptr_asxml(T obj, string name)
	{
		if (obj != nullptr)
		{
			obj->SaveXml(name);
		}
	}

	template<typename T>
	inline void save_shared_ptr_asjson(T obj, string name)
	{
		if (obj != nullptr)
		{
			obj->SaveJson(name);
		}
	}

} //----end of namespace gezi



#define SAVE_SHARED_PTR(obj, path)\
	gezi::save_shared_ptr(obj, path, gezi::conf_trim(#obj))

#define SAVE_SHARED_PTR_ASTEXT(obj, path)\
	gezi::save_shared_ptr_astext(obj, format("{}/{}.txt", path, gezi::conf_trim((#obj))))

#define SAVE_SHARED_PTR_ASXML(obj, path)\
	gezi::save_shared_ptr_asxml(obj,	format("{}/{}.xml", path, gezi::conf_trim((#obj))))

#define SAVE_SHARED_PTR_ASJSON(obj, path)\
	gezi::save_shared_ptr_asjson(obj, format("{}/{}.json", path, gezi::conf_trim((#obj))))

#define  OBJ_NAME_PATH(obj, path)\
	format("{}/{}.name.txt", path, gezi::conf_trim(#obj))

#endif  //----end of FILE_UTIL_H_
