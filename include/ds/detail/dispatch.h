/**
 *  ==============================================================================
 *
 *          \file   detail/dispatch.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-26 15:07:59.565092
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_DETAIL_DISPATCH_H_
#define GEZI_DETAIL_DISPATCH_H_

//-----------------------------Trie
#define GEZI_DATA_TRUE_INDICATOR
#define GEZI_V2F(X) (X).first
#define GEZI_V2S(X) (X).second
#include <ds/detail/TrieImpl.h>
#undef GEZI_DATA_TRUE_INDICATOR
#undef GEZI_V2F
#undef GEZI_V2S

//-----------------------------TrieDict
#define GEZI_DATA_TRUE_INDICATOR
#define GEZI_TRIE_INDEX_IS_VALUE
#define GEZI_V2F(X) (X).first
#define GEZI_V2S(X) (X).second
#include <ds/detail/TrieImpl.h>
#undef  GEZI_TRIE_INDEX_IS_VALUE
#undef GEZI_DATA_TRUE_INDICATOR
#undef GEZI_V2F
#undef GEZI_V2S

//-----------------------------TrieSet
#define GEZI_DATA_FALSE_INDICATOR
#define GEZI_V2F(X) (X)
#define GEZI_V2S(X) (X)
#include <ds/detail/TrieImpl.h>
#undef GEZI_DATA_FALSE_INDICATOR
#undef GEZI_V2F
#undef GEZI_V2S

#endif  //----end of GEZI_DETAIL_DISPATCH_H_
