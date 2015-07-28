/**
 *  ==============================================================================
 *
 *          \file   ds/trie_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-28 15:18:20.163953
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_DS_TRIE_UTIL_H_
#define GEZI_DS_TRIE_UTIL_H_

namespace gezi {
	namespace trie {
		template <class Map>
		typename Map::mapped_type get_default(
			const Map& map, const typename Map::key_type& key,
			const typename Map::mapped_type& dflt =
			typename Map::mapped_type()) {
			auto pos = map.find(key);
			return (pos != map.end() ? *pos : dflt);
		}
	}  //----end of namespace trie
}  //----end of namespace gezi

#endif  //----end of GEZI_DS_TRIE_UTIL_H_
