/**
 *  ==============================================================================
 *
 *          \file   Identifer.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 09:53:10.353333
 *
 *  \Description:    @TODO   加入序列化
 *  ==============================================================================
 */

#ifndef IDENTIFER_H_
#define IDENTIFER_H_
#include "common_util.h"
#include "seralize_util.h"
namespace gezi {

	class Identifer
	{
	public:
		typedef int IdType; //may be changed to int64
		typedef std::vector<string>::iterator iterator;
		typedef std::vector<string>::const_iterator const_iterator;
		typedef unordered_map<string, IdType> HashMap;
		typedef HashMap::const_iterator const_mapiter;

	public:

		static const IdType null_id()
		{
			static const IdType _null_id = -1;
			return _null_id;
		}

		vector<string>& words()
		{
			return _index;
		}

#ifndef GCCXML	
		iterator begin()
		{
			return _index.begin();
		}

		iterator end()
		{
			return _index.end();
		}

		const_iterator begin()const
		{
			return _index.begin();
		}

		const_iterator end()const
		{
			return _index.end();
		}
#endif

		size_t size()const
		{
			return _index.size();
		}

		bool empty()const
		{
			return _index.empty();
		}

		void clear()
		{
			_hashdict.clear();
			_index.clear();
		}

		inline string key(int id) const
		{
			return _index[id];
		}

		vector<string>& keys()
		{
			return _index;
		}

		//get a item's id (index in dict),if the item does not exist return null_id()

		inline IdType id(string f) const
		{
			HashMap::const_iterator it = _hashdict.find(f);
			if (it == _hashdict.end())
				return null_id();
			return it->second;
		}

		inline bool has(string f) const
		{
			return _hashdict.find(f) != _hashdict.end();
		}

		inline IdType add(string f)
		{
			HashMap::iterator it = _hashdict.find(f);
			if (it != _hashdict.end())
				return it->second;

			IdType id = _index.size();
			_hashdict[f] = id;
			_index.push_back(f);
			return id;
		}

		inline IdType add(string f, bool& isnew)
		{
			HashMap::iterator it = _hashdict.find(f);
			if (it != _hashdict.end())
			{
				isnew = false;
				return it->second;
			}
			isnew = true;
			IdType id = _index.size();
			_hashdict[f] = id;
			_index.push_back(f);
			return id;
		}

		string last()
		{
			return _index.back();
		}

		inline IdType add_unique(string f)
		{
			int id = _index.size();
			_hashdict[f] = id;
			_index.push_back(f);
			return id;
		}

		bool load(string file, string sep = "\t")
		{
			ifstream ifs(file.c_str());
			CHECK_EQ(ifs.is_open(), true) << file;
			VLOG(3) << "Begin loading " << file;
			string line, key;
			IdType id = 0;
			while (std::getline(ifs, line))
			{
				vector<string> vec = split(line, sep);
				_hashdict[vec[0]] = id++;
			}
			_index.resize(id);
			HashMap::const_iterator iter = _hashdict.begin();
			for (; iter != _hashdict.end(); ++iter)
			{
				_index[iter->second] = iter->first;
			}
			VLOG(3) << "End loading " << file;
			return true;
		}

		void save(string file)
		{
			ofstream ofs(file.c_str());

			int len = int(_index.size());
			for (int i = 0; i < len; i++)
			{
				ofs << _index[i] << std::endl;
			}
		}

		string operator [] (int id) const {
			return _index[id];
		}

		const IdType& operator () (string key) const
		{
			HashMap::const_iterator it = _hashdict.find(key);
			if (it == _hashdict.end())
				return null_id();
			return it->second;
		}

		void Load(string path)
		{
			serialize_util::load(*this, path);
		}

		void Save(string path)
		{
			serialize_util::save(*this, path);
		}

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
		/*	ar & _hashdict;
			ar & _index;*/
			ar & BOOST_SERIALIZATION_NVP(_hashdict);
			ar & BOOST_SERIALIZATION_NVP(_index);
		}
	protected:
		HashMap _hashdict;
		vector<string> _index; //kid->key
	};

	typedef vector<Identifer> Identifers;

	template<typename T>
	class ValueIdentifer : public Identifer
	{
	public:
		bool load(string file, int index = 1, string sep = "\t")
		{
			ifstream ifs(file.c_str());
			CHECK_EQ(ifs.is_open(), true) << file;
			VLOG(3) << "Begin loading " << file;
			string line, key;
			IdType id = 0;
			while (std::getline(ifs, line))
			{
				vector<string> vec = split(line, sep);
				_hashdict[vec[0]] = id++;
				if (index < vec.size())
				{
					try
					{
						_values.push_back(boost::lexical_cast<T>(vec[index]));
					}
					catch (...)
					{
						_values.push_back(1);
					}
				}
				else
				{
					_values.push_back(1);
				}
			}
			_index.resize(id);
			HashMap::const_iterator iter = _hashdict.begin();
			for (; iter != _hashdict.end(); ++iter)
			{
				_index[iter->second] = iter->first;
			}
			VLOG(3) << "End loading " << file;
			return true;
		}

		void Save(string file)
		{
			serialize_util::save(*this, file);
		}

		void Load(string file)
		{
			VLOG(0) << "Identifer Loading " << file;
			serialize_util::load(*this, file);
			VLOG(0) << "Identifer Loading Done size: " << size();
		}

		T value(int index)
		{
			return _values[index];
		}

		//注意 可能 -1 越界
		T get_value(string key)
		{
			return _values[id(key)];
		}

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			/*	ar & boost::serialization::base_object<Identifer>(*this);
				ar & _values;*/
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Identifer);
			ar & BOOST_SERIALIZATION_NVP(_values);
		}

	private:
		vector<T> _values;
	};

	typedef ValueIdentifer<int> IntIdentifer;
	typedef ValueIdentifer<double> DoubleIdentifer;

//#ifdef GCCXML  //奇怪。。 GCCXML没有认出来？ GXXML起不起作用？@FIXME ndef GCCXM起作用 但是def不起作用？
	//py++ work around py++不处理typedef
	class PyIntIndentifer : public IntIdentifer
	{

	};
	class PyDoubleIdentifer : public DoubleIdentifer
	{

	};
//#endif
	
} //----end of namespace gezi

#endif  //----end of IDENTIFER_H_
