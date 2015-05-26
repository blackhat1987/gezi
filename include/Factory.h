/**
 *  ==============================================================================
 *
 *          \file   Factory.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-23 21:00:41.689816
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FACTORY_H_
#define FACTORY_H_
#include <map>
#include <string>
namespace gezi {

	template<typename Ptr, typename Key = std::string>
	class Factory
	{
	public:
		void Register(Key id, Ptr ptr)
		{
			_map[id] = ptr;
		}

		void Create(Key id)
		{
			return _map[id];
		}
	protected:
	private:
		std::map<Key, Ptr> _map;
	};

}  //----end of namespace gezi

#endif  //----end of FACTORY_H_
