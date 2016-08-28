#define private public
#define protected public
#include "python_util.h"
// This file has been generated by Py++.

#include "boost/python.hpp"

#include "boost/python/suite/indexing/vector_indexing_suite.hpp"

#include "common_util.h"

#include "Identifer.h"
const int gezi::Identifer::NullId;

#include "nlp/Vocabulary.h"

#include "nlp/WordCounter.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(libword_counter){
DEF_VEC(ivec);
DEF_VEC(dvec);
DEF_VEC(uvec);
DEF_VEC(svec);
DEF_VEC(ulvec);
DEF_MAP(id_map);
DEF_MAP(sd_map);
DEF_MAP(si_map);
DEF_MAP(ss_map);
DEF_PAIR(ii_pair);
DEF_PAIR(si_pair);
DEF_PAIR(wsi_pair);
DEF_VEC(si_pair_vec);
DEF_VEC(wsi_pair_vec);
DEF_SET(iset);
DEF_SET(lset);
DEF_SET(ulset);

{ //::std::vector< std::string >
typedef bp::class_< std::vector< std::string > > vector_less__std_scope_string__greater__exposer_t;
vector_less__std_scope_string__greater__exposer_t vector_less__std_scope_string__greater__exposer = vector_less__std_scope_string__greater__exposer_t( "vector_less__std_scope_string__greater_" );
bp::scope vector_less__std_scope_string__greater__scope( vector_less__std_scope_string__greater__exposer );
vector_less__std_scope_string__greater__exposer.def( bp::vector_indexing_suite< ::std::vector< std::string >, true >() )
VEC_METHOD(::std::vector< std::string >);
}

{ //::gezi::Identifer
typedef bp::class_< gezi::Identifer, boost::noncopyable > Identifer_exposer_t;
Identifer_exposer_t Identifer_exposer = Identifer_exposer_t( "Identifer", bp::init< >() );
bp::scope Identifer_scope( Identifer_exposer );
Identifer_exposer.def( bp::init< std::string >(( bp::arg("file") )) );
bp::implicitly_convertible< std::string, gezi::Identifer >();
{ //::gezi::Identifer::Load

typedef void ( ::gezi::Identifer::*Load_function_type)( ::std::string ) ;

Identifer_exposer.def(
"Load"
, Load_function_type( &::gezi::Identifer::Load )
, ( bp::arg("path") ) );

}
{ //::gezi::Identifer::Save

typedef void ( ::gezi::Identifer::*Save_function_type)( ::std::string ) ;

Identifer_exposer.def(
"Save"
, Save_function_type( &::gezi::Identifer::Save )
, ( bp::arg("path") ) );

}
{ //::gezi::Identifer::add

typedef ::gezi::Identifer::IdType ( ::gezi::Identifer::*add_function_type)( ::std::string ) ;

Identifer_exposer.def(
"add"
, add_function_type( &::gezi::Identifer::add )
, ( bp::arg("f") ) );

}
{ //::gezi::Identifer::add

typedef ::gezi::Identifer::IdType ( ::gezi::Identifer::*add_function_type)( ::std::string,bool & ) ;

Identifer_exposer.def(
"add"
, add_function_type( &::gezi::Identifer::add )
, ( bp::arg("f"), bp::arg("isnew") ) );

}
{ //::gezi::Identifer::add_unique

typedef ::gezi::Identifer::IdType ( ::gezi::Identifer::*add_unique_function_type)( ::std::string ) ;

Identifer_exposer.def(
"add_unique"
, add_unique_function_type( &::gezi::Identifer::add_unique )
, ( bp::arg("f") ) );

}
{ //::gezi::Identifer::clear

typedef void ( ::gezi::Identifer::*clear_function_type)(  ) ;

Identifer_exposer.def(
"clear"
, clear_function_type( &::gezi::Identifer::clear ) );

}
{ //::gezi::Identifer::empty

typedef bool ( ::gezi::Identifer::*empty_function_type)(  ) const;

Identifer_exposer.def(
"empty"
, empty_function_type( &::gezi::Identifer::empty ) );

}
{ //::gezi::Identifer::has

typedef bool ( ::gezi::Identifer::*has_function_type)( ::std::string ) const;

Identifer_exposer.def(
"has"
, has_function_type( &::gezi::Identifer::has )
, ( bp::arg("f") ) );

}
{ //::gezi::Identifer::id

typedef ::gezi::Identifer::IdType ( ::gezi::Identifer::*id_function_type)( ::std::string ) const;

Identifer_exposer.def(
"id"
, id_function_type( &::gezi::Identifer::id )
, ( bp::arg("f") ) );

}
{ //::gezi::Identifer::id

typedef ::gezi::Identifer::IdType ( ::gezi::Identifer::*id_function_type)( ::std::string,::gezi::Identifer::IdType ) const;

Identifer_exposer.def(
"id"
, id_function_type( &::gezi::Identifer::id )
, ( bp::arg("f"), bp::arg("defaultVal") ) );

}
{ //::gezi::Identifer::key

typedef ::std::string ( ::gezi::Identifer::*key_function_type)( ::gezi::Identifer::IdType ) const;

Identifer_exposer.def(
"key"
, key_function_type( &::gezi::Identifer::key )
, ( bp::arg("id") ) );

}
{ //::gezi::Identifer::key

typedef ::std::string ( ::gezi::Identifer::*key_function_type)( ::gezi::Identifer::IdType,::std::string ) const;

Identifer_exposer.def(
"key"
, key_function_type( &::gezi::Identifer::key )
, ( bp::arg("id"), bp::arg("defualtKey") ) );

}
{ //::gezi::Identifer::keys

typedef ::std::vector< std::string > & ( ::gezi::Identifer::*keys_function_type)(  ) ;

Identifer_exposer.def(
"keys"
, keys_function_type( &::gezi::Identifer::keys )
, bp::return_internal_reference<>());

}
{ //::gezi::Identifer::last

typedef ::std::string ( ::gezi::Identifer::*last_function_type)(  ) ;

Identifer_exposer.def(
"last"
, last_function_type( &::gezi::Identifer::last ) );

}
{ //::gezi::Identifer::load

typedef bool ( ::gezi::Identifer::*load_function_type)( ::std::string,::std::string ) ;

Identifer_exposer.def(
"load"
, load_function_type( &::gezi::Identifer::load )
, ( bp::arg("file"), bp::arg("sep")="\t" ) );

}
{ //::gezi::Identifer::null_id

typedef ::gezi::Identifer::IdType const ( *null_id_function_type )(  );

Identifer_exposer.def(
"null_id"
, null_id_function_type( &::gezi::Identifer::null_id ) );

}
{ //::gezi::Identifer::operator()

typedef ::gezi::Identifer::IdType const ( ::gezi::Identifer::*__call___function_type)( ::std::string ) const;

Identifer_exposer.def(
"__call__"
, __call___function_type( &::gezi::Identifer::operator() )
, ( bp::arg("key") ) );

}
{ //::gezi::Identifer::operator[]

typedef ::std::string ( ::gezi::Identifer::*__getitem___function_type)( int ) const;

Identifer_exposer.def(
"__getitem__"
, __getitem___function_type( &::gezi::Identifer::operator[] )
, ( bp::arg("id") ) );

}
{ //::gezi::Identifer::save

typedef void ( ::gezi::Identifer::*save_function_type)( ::std::string ) ;

Identifer_exposer.def(
"save"
, save_function_type( &::gezi::Identifer::save )
, ( bp::arg("file") ) );

}
{ //::gezi::Identifer::size

typedef ::size_t ( ::gezi::Identifer::*size_function_type)(  ) const;

Identifer_exposer.def(
"size"
, size_function_type( &::gezi::Identifer::size ) );

}
{ //::gezi::Identifer::words

typedef ::std::vector< std::string > & ( ::gezi::Identifer::*words_function_type)(  ) ;

Identifer_exposer.def(
"words"
, words_function_type( &::gezi::Identifer::words )
, bp::return_internal_reference<>());

}
Identifer_exposer.def_readonly( "NullId", &gezi::Identifer::NullId );
Identifer_exposer.staticmethod( "null_id" );
}

{ //::gezi::ValueIdentifer< unsigned long >
typedef bp::class_< gezi::ValueIdentifer< unsigned long >, bp::bases< gezi::Identifer > > CountIdentifer_exposer_t;
CountIdentifer_exposer_t CountIdentifer_exposer = CountIdentifer_exposer_t( "CountIdentifer", bp::init< >() );
bp::scope CountIdentifer_scope( CountIdentifer_exposer );
CountIdentifer_exposer.def( bp::init< std::string >(( bp::arg("file") )) );
bp::implicitly_convertible< std::string, gezi::ValueIdentifer< unsigned long > >();
{ //::gezi::ValueIdentifer< unsigned long >::Load

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef void ( exported_class_t::*Load_function_type)( ::std::string ) ;

CountIdentifer_exposer.def(
"Load"
, Load_function_type( &::gezi::ValueIdentifer< unsigned long >::Load )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< unsigned long >::Save

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef void ( exported_class_t::*Save_function_type)( ::std::string ) ;

CountIdentifer_exposer.def(
"Save"
, Save_function_type( &::gezi::ValueIdentifer< unsigned long >::Save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< unsigned long >::add

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef void ( exported_class_t::*add_function_type)( ::std::string,long unsigned int ) ;

CountIdentifer_exposer.def(
"add"
, add_function_type( &::gezi::ValueIdentifer< unsigned long >::add )
, ( bp::arg("key"), bp::arg("value") ) );

}
{ //::gezi::ValueIdentifer< unsigned long >::get_value

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef long unsigned int ( exported_class_t::*get_value_function_type)( ::std::string ) const;

CountIdentifer_exposer.def(
"get_value"
, get_value_function_type( &::gezi::ValueIdentifer< unsigned long >::get_value )
, ( bp::arg("key") ) );

}
{ //::gezi::ValueIdentifer< unsigned long >::load

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef bool ( exported_class_t::*load_function_type)( ::std::string,int,::std::string ) ;

CountIdentifer_exposer.def(
"load"
, load_function_type( &::gezi::ValueIdentifer< unsigned long >::load )
, ( bp::arg("file"), bp::arg("index")=(int)(1), bp::arg("sep")="\t" ) );

}
{ //::gezi::ValueIdentifer< unsigned long >::save

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef void ( exported_class_t::*save_function_type)( ::std::string ) ;

CountIdentifer_exposer.def(
"save"
, save_function_type( &::gezi::ValueIdentifer< unsigned long >::save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< unsigned long >::value

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef long unsigned int ( exported_class_t::*value_function_type)( int ) const;

CountIdentifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< unsigned long >::value )
, ( bp::arg("index") ) );

}
{ //::gezi::ValueIdentifer< unsigned long >::value

typedef gezi::ValueIdentifer< unsigned long > exported_class_t;
typedef long unsigned int ( exported_class_t::*value_function_type)( ::std::string ) const;

CountIdentifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< unsigned long >::value )
, ( bp::arg("key") ) );

}
}

//    bp::class_< gezi::PyHack_CountIdentifer, bp::bases< gezi::ValueIdentifer< unsigned long > > >( "PyHack_CountIdentifer" );

{ //::gezi::ValueIdentifer< double >
typedef bp::class_< gezi::ValueIdentifer< double >, bp::bases< gezi::Identifer > > DoubleIdentifer_exposer_t;
DoubleIdentifer_exposer_t DoubleIdentifer_exposer = DoubleIdentifer_exposer_t( "DoubleIdentifer", bp::init< >() );
bp::scope DoubleIdentifer_scope( DoubleIdentifer_exposer );
DoubleIdentifer_exposer.def( bp::init< std::string >(( bp::arg("file") )) );
bp::implicitly_convertible< std::string, gezi::ValueIdentifer< double > >();
{ //::gezi::ValueIdentifer< double >::Load

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef void ( exported_class_t::*Load_function_type)( ::std::string ) ;

DoubleIdentifer_exposer.def(
"Load"
, Load_function_type( &::gezi::ValueIdentifer< double >::Load )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< double >::Save

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef void ( exported_class_t::*Save_function_type)( ::std::string ) ;

DoubleIdentifer_exposer.def(
"Save"
, Save_function_type( &::gezi::ValueIdentifer< double >::Save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< double >::add

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef void ( exported_class_t::*add_function_type)( ::std::string,double ) ;

DoubleIdentifer_exposer.def(
"add"
, add_function_type( &::gezi::ValueIdentifer< double >::add )
, ( bp::arg("key"), bp::arg("value") ) );

}
{ //::gezi::ValueIdentifer< double >::get_value

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef double ( exported_class_t::*get_value_function_type)( ::std::string ) const;

DoubleIdentifer_exposer.def(
"get_value"
, get_value_function_type( &::gezi::ValueIdentifer< double >::get_value )
, ( bp::arg("key") ) );

}
{ //::gezi::ValueIdentifer< double >::load

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef bool ( exported_class_t::*load_function_type)( ::std::string,int,::std::string ) ;

DoubleIdentifer_exposer.def(
"load"
, load_function_type( &::gezi::ValueIdentifer< double >::load )
, ( bp::arg("file"), bp::arg("index")=(int)(1), bp::arg("sep")="\t" ) );

}
{ //::gezi::ValueIdentifer< double >::save

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef void ( exported_class_t::*save_function_type)( ::std::string ) ;

DoubleIdentifer_exposer.def(
"save"
, save_function_type( &::gezi::ValueIdentifer< double >::save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< double >::value

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef double ( exported_class_t::*value_function_type)( int ) const;

DoubleIdentifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< double >::value )
, ( bp::arg("index") ) );

}
{ //::gezi::ValueIdentifer< double >::value

typedef gezi::ValueIdentifer< double > exported_class_t;
typedef double ( exported_class_t::*value_function_type)( ::std::string ) const;

DoubleIdentifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< double >::value )
, ( bp::arg("key") ) );

}
}

//    bp::class_< gezi::PyHack_DoubleIdentifer, bp::bases< gezi::ValueIdentifer< double > > >( "PyHack_DoubleIdentifer" );

{ //::gezi::ValueIdentifer< long long >
typedef bp::class_< gezi::ValueIdentifer< long long >, bp::bases< gezi::Identifer > > Int64Identifer_exposer_t;
Int64Identifer_exposer_t Int64Identifer_exposer = Int64Identifer_exposer_t( "Int64Identifer", bp::init< >() );
bp::scope Int64Identifer_scope( Int64Identifer_exposer );
Int64Identifer_exposer.def( bp::init< std::string >(( bp::arg("file") )) );
bp::implicitly_convertible< std::string, gezi::ValueIdentifer< long long > >();
{ //::gezi::ValueIdentifer< long long >::Load

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef void ( exported_class_t::*Load_function_type)( ::std::string ) ;

Int64Identifer_exposer.def(
"Load"
, Load_function_type( &::gezi::ValueIdentifer< long long >::Load )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< long long >::Save

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef void ( exported_class_t::*Save_function_type)( ::std::string ) ;

Int64Identifer_exposer.def(
"Save"
, Save_function_type( &::gezi::ValueIdentifer< long long >::Save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< long long >::add

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef void ( exported_class_t::*add_function_type)( ::std::string,long long int ) ;

Int64Identifer_exposer.def(
"add"
, add_function_type( &::gezi::ValueIdentifer< long long >::add )
, ( bp::arg("key"), bp::arg("value") ) );

}
{ //::gezi::ValueIdentifer< long long >::get_value

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef long long int ( exported_class_t::*get_value_function_type)( ::std::string ) const;

Int64Identifer_exposer.def(
"get_value"
, get_value_function_type( &::gezi::ValueIdentifer< long long >::get_value )
, ( bp::arg("key") ) );

}
{ //::gezi::ValueIdentifer< long long >::load

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef bool ( exported_class_t::*load_function_type)( ::std::string,int,::std::string ) ;

Int64Identifer_exposer.def(
"load"
, load_function_type( &::gezi::ValueIdentifer< long long >::load )
, ( bp::arg("file"), bp::arg("index")=(int)(1), bp::arg("sep")="\t" ) );

}
{ //::gezi::ValueIdentifer< long long >::save

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef void ( exported_class_t::*save_function_type)( ::std::string ) ;

Int64Identifer_exposer.def(
"save"
, save_function_type( &::gezi::ValueIdentifer< long long >::save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< long long >::value

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef long long int ( exported_class_t::*value_function_type)( int ) const;

Int64Identifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< long long >::value )
, ( bp::arg("index") ) );

}
{ //::gezi::ValueIdentifer< long long >::value

typedef gezi::ValueIdentifer< long long > exported_class_t;
typedef long long int ( exported_class_t::*value_function_type)( ::std::string ) const;

Int64Identifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< long long >::value )
, ( bp::arg("key") ) );

}
}

//    bp::class_< gezi::PyHack_Int64Identifer, bp::bases< gezi::ValueIdentifer< long long > > >( "PyHack_Int64Identifer" );

{ //::gezi::ValueIdentifer< int >
typedef bp::class_< gezi::ValueIdentifer< int >, bp::bases< gezi::Identifer > > IntIdentifer_exposer_t;
IntIdentifer_exposer_t IntIdentifer_exposer = IntIdentifer_exposer_t( "IntIdentifer", bp::init< >() );
bp::scope IntIdentifer_scope( IntIdentifer_exposer );
IntIdentifer_exposer.def( bp::init< std::string >(( bp::arg("file") )) );
bp::implicitly_convertible< std::string, gezi::ValueIdentifer< int > >();
{ //::gezi::ValueIdentifer< int >::Load

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef void ( exported_class_t::*Load_function_type)( ::std::string ) ;

IntIdentifer_exposer.def(
"Load"
, Load_function_type( &::gezi::ValueIdentifer< int >::Load )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< int >::Save

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef void ( exported_class_t::*Save_function_type)( ::std::string ) ;

IntIdentifer_exposer.def(
"Save"
, Save_function_type( &::gezi::ValueIdentifer< int >::Save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< int >::add

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef void ( exported_class_t::*add_function_type)( ::std::string,int ) ;

IntIdentifer_exposer.def(
"add"
, add_function_type( &::gezi::ValueIdentifer< int >::add )
, ( bp::arg("key"), bp::arg("value") ) );

}
{ //::gezi::ValueIdentifer< int >::get_value

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef int ( exported_class_t::*get_value_function_type)( ::std::string ) const;

IntIdentifer_exposer.def(
"get_value"
, get_value_function_type( &::gezi::ValueIdentifer< int >::get_value )
, ( bp::arg("key") ) );

}
{ //::gezi::ValueIdentifer< int >::load

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef bool ( exported_class_t::*load_function_type)( ::std::string,int,::std::string ) ;

IntIdentifer_exposer.def(
"load"
, load_function_type( &::gezi::ValueIdentifer< int >::load )
, ( bp::arg("file"), bp::arg("index")=(int)(1), bp::arg("sep")="\t" ) );

}
{ //::gezi::ValueIdentifer< int >::save

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef void ( exported_class_t::*save_function_type)( ::std::string ) ;

IntIdentifer_exposer.def(
"save"
, save_function_type( &::gezi::ValueIdentifer< int >::save )
, ( bp::arg("file") ) );

}
{ //::gezi::ValueIdentifer< int >::value

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef int ( exported_class_t::*value_function_type)( int ) const;

IntIdentifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< int >::value )
, ( bp::arg("index") ) );

}
{ //::gezi::ValueIdentifer< int >::value

typedef gezi::ValueIdentifer< int > exported_class_t;
typedef int ( exported_class_t::*value_function_type)( ::std::string ) const;

IntIdentifer_exposer.def(
"value"
, value_function_type( &::gezi::ValueIdentifer< int >::value )
, ( bp::arg("key") ) );

}
}

//    bp::class_< gezi::PyHack_IntIdentifer, bp::bases< gezi::ValueIdentifer< int > > >( "PyHack_IntIdentifer" );

{ //::gezi::Vocabulary
typedef bp::class_< gezi::Vocabulary, bp::bases< gezi::ValueIdentifer< unsigned long > > > Vocabulary_exposer_t;
Vocabulary_exposer_t Vocabulary_exposer = Vocabulary_exposer_t( "Vocabulary", bp::init< >() );
bp::scope Vocabulary_scope( Vocabulary_exposer );
Vocabulary_exposer.def( bp::init< std::string >(( bp::arg("file") )) );
bp::implicitly_convertible< std::string, gezi::Vocabulary >();
{ //::gezi::Vocabulary::count

typedef ::size_t ( ::gezi::Vocabulary::*count_function_type)( int ) const;

Vocabulary_exposer.def(
"count"
, count_function_type( &::gezi::Vocabulary::count )
, ( bp::arg("index") ) );

}
{ //::gezi::Vocabulary::count

typedef ::size_t ( ::gezi::Vocabulary::*count_function_type)( ::std::string ) const;

Vocabulary_exposer.def(
"count"
, count_function_type( &::gezi::Vocabulary::count )
, ( bp::arg("key") ) );

}
{ //::gezi::Vocabulary::freq

typedef ::size_t ( ::gezi::Vocabulary::*freq_function_type)( int ) const;

Vocabulary_exposer.def(
"freq"
, freq_function_type( &::gezi::Vocabulary::freq )
, ( bp::arg("index") ) );

}
{ //::gezi::Vocabulary::freq

typedef ::size_t ( ::gezi::Vocabulary::*freq_function_type)( ::std::string ) const;

Vocabulary_exposer.def(
"freq"
, freq_function_type( &::gezi::Vocabulary::freq )
, ( bp::arg("key") ) );

}
}

{ //::gezi::WordCounter
typedef bp::class_< gezi::WordCounter > WordCounter_exposer_t;
WordCounter_exposer_t WordCounter_exposer = WordCounter_exposer_t( "WordCounter", bp::init< bp::optional< bool, std::string, size_t, size_t, bool > >(( bp::arg("addUnknown")=(bool)(true), bp::arg("unknownMark")="<UNK>", bp::arg("mostCommon")=(::size_t)(0), bp::arg("minCount")=(::size_t)(0), bp::arg("saveCountInfo")=(bool)(true) )) );
bp::scope WordCounter_scope( WordCounter_exposer );
bp::implicitly_convertible< bool, gezi::WordCounter >();
{ //::gezi::WordCounter::add

typedef void ( ::gezi::WordCounter::*add_function_type)( ::std::string ) ;

WordCounter_exposer.def(
"add"
, add_function_type( &::gezi::WordCounter::add )
, ( bp::arg("word") ) );

}
{ //::gezi::WordCounter::finish

typedef void ( ::gezi::WordCounter::*finish_function_type)(  ) ;

WordCounter_exposer.def(
"finish"
, finish_function_type( &::gezi::WordCounter::finish ) );

}
{ //::gezi::WordCounter::get_identifer

typedef ::gezi::Identifer ( ::gezi::WordCounter::*get_identifer_function_type)(  ) ;

WordCounter_exposer.def(
"get_identifer"
, get_identifer_function_type( &::gezi::WordCounter::get_identifer ) );

}
{ //::gezi::WordCounter::get_vocabulary

typedef ::gezi::CountIdentifer ( ::gezi::WordCounter::*get_vocabulary_function_type)(  ) ;

WordCounter_exposer.def(
"get_vocabulary"
, get_vocabulary_function_type( &::gezi::WordCounter::get_vocabulary ) );

}
{ //::gezi::WordCounter::min_count

typedef void ( ::gezi::WordCounter::*min_count_function_type)( ::size_t ) ;

WordCounter_exposer.def(
"min_count"
, min_count_function_type( &::gezi::WordCounter::min_count )
, ( bp::arg("minCount") ) );

}
{ //::gezi::WordCounter::most_common

typedef void ( ::gezi::WordCounter::*most_common_function_type)( ::size_t ) ;

WordCounter_exposer.def(
"most_common"
, most_common_function_type( &::gezi::WordCounter::most_common )
, ( bp::arg("topN") ) );

}
{ //::gezi::WordCounter::save

typedef void ( ::gezi::WordCounter::*save_function_type)( ::std::string ) const;

WordCounter_exposer.def(
"save"
, save_function_type( &::gezi::WordCounter::save )
, ( bp::arg("file") ) );

}
{ //::gezi::WordCounter::save

typedef void ( ::gezi::WordCounter::*save_function_type)( ::std::string,::std::string ) ;

WordCounter_exposer.def(
"save"
, save_function_type( &::gezi::WordCounter::save )
, ( bp::arg("binFile"), bp::arg("countFile") ) );

}
{ //::gezi::WordCounter::save_identifer

typedef void ( ::gezi::WordCounter::*save_identifer_function_type)( ::std::string ) const;

WordCounter_exposer.def(
"save_identifer"
, save_identifer_function_type( &::gezi::WordCounter::save_identifer )
, ( bp::arg("file") ) );

}
{ //::gezi::WordCounter::save_text

typedef void ( ::gezi::WordCounter::*save_text_function_type)( ::std::string ) const;

WordCounter_exposer.def(
"save_text"
, save_text_function_type( &::gezi::WordCounter::save_text )
, ( bp::arg("file") ) );

}
{ //::gezi::WordCounter::save_vocabulary

typedef void ( ::gezi::WordCounter::*save_vocabulary_function_type)( ::std::string ) const;

WordCounter_exposer.def(
"save_vocabulary"
, save_vocabulary_function_type( &::gezi::WordCounter::save_vocabulary )
, ( bp::arg("file") ) );

}
}
}
