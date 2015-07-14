#define private public
#define protected public
#include "python_util.h"
// This file has been generated by Py++.

#include "boost/python.hpp"

#include "boost/python/suite/indexing/vector_indexing_suite.hpp"

#include "common_util.h"

#include "Segmentor.h"
const int gezi::SegHandle::SEG_BUFF_SIZE;

namespace bp = boost::python;

struct SegHandle_wrapper : gezi::SegHandle, bp::wrapper< gezi::SegHandle > {

SegHandle_wrapper(gezi::SegHandle const & arg )
: gezi::SegHandle( arg )
, bp::wrapper< gezi::SegHandle >(){
// copy constructor

}

SegHandle_wrapper( )
: gezi::SegHandle( )
, bp::wrapper< gezi::SegHandle >(){
// null constructor

}

SegHandle_wrapper(int bufsize )
: gezi::SegHandle( bufsize )
, bp::wrapper< gezi::SegHandle >(){
// constructor

}

static ::scw_out_t * get_pout(gezi::SegHandle const & inst ){
return inst.pout;
}

static void set_pout( gezi::SegHandle & inst, ::scw_out_t * new_value ){
inst.pout = new_value;
}

static ::token_t * get_tokens(gezi::SegHandle const & inst ){
return inst.tokens;
}

static void set_tokens( gezi::SegHandle & inst, ::token_t * new_value ){
inst.tokens = new_value;
}

};

BOOST_PYTHON_MODULE(libsegment){
DEF_VEC(ivec);
DEF_VEC(dvec);
DEF_VEC(uvec);
DEF_VEC(svec);
DEF_VEC(ulvec);
DEF_MAP(id_map);
DEF_MAP(sd_map);
DEF_MAP(si_map);

{ //::std::vector< token_t >
typedef bp::class_< std::vector< token_t > > vector_less__token_t__greater__exposer_t;
vector_less__token_t__greater__exposer_t vector_less__token_t__greater__exposer = vector_less__token_t__greater__exposer_t( "vector_less__token_t__greater_" );
bp::scope vector_less__token_t__greater__scope( vector_less__token_t__greater__exposer );
//WARNING: the next line of code will not compile, because "::token_t" does not have operator== !
//         vector_less__token_t__greater__exposer.def( bp::vector_indexing_suite< ::std::vector< token_t > >() );
}

bp::class_< std::vector< std::string > >("vector_less__std_scope_string__greater_")
.def( bp::vector_indexing_suite< ::std::vector< std::string >, true >() )
VEC_METHOD(::std::vector< std::string >);

{ //scope begin
typedef bp::class_< std::vector< gezi::SegNode > > vector_less__gezi_scope_SegNode__greater__exposer_t;
vector_less__gezi_scope_SegNode__greater__exposer_t vector_less__gezi_scope_SegNode__greater__exposer = vector_less__gezi_scope_SegNode__greater__exposer_t("vector_less__gezi_scope_SegNode__greater_");
bp::scope vector_less__gezi_scope_SegNode__greater__scope( vector_less__gezi_scope_SegNode__greater__exposer );
//WARNING: the next line of code will not compile, because "::gezi::SegNode" does not have operator== !
//         vector_less__gezi_scope_SegNode__greater__exposer.def( bp::vector_indexing_suite< ::std::vector< gezi::SegNode > >() );
} //scope end

{ //::gezi::SegHandle
typedef bp::class_< SegHandle_wrapper > SegHandle_exposer_t;
SegHandle_exposer_t SegHandle_exposer = SegHandle_exposer_t( "SegHandle", bp::init< >() );
bp::scope SegHandle_scope( SegHandle_exposer );
SegHandle_exposer.def( bp::init< int >(( bp::arg("bufsize") )) );
bp::implicitly_convertible< int, gezi::SegHandle >();
{ //::gezi::SegHandle::clear

typedef void ( ::gezi::SegHandle::*clear_function_type )(  ) ;

SegHandle_exposer.def(
"clear"
, clear_function_type( &::gezi::SegHandle::clear ) );

}
{ //::gezi::SegHandle::init

typedef void ( ::gezi::SegHandle::*init_function_type )( int ) ;

SegHandle_exposer.def(
"init"
, init_function_type( &::gezi::SegHandle::init )
, ( bp::arg("buf_size_")=(int)(gezi::SegHandle::SEG_BUFF_SIZE) ) );

}
SegHandle_exposer.def_readonly( "SEG_BUFF_SIZE", gezi::SegHandle::SEG_BUFF_SIZE );
SegHandle_exposer.def_readwrite( "buf_size", &gezi::SegHandle::buf_size );
SegHandle_exposer.def_readwrite( "nresult", &gezi::SegHandle::nresult );
SegHandle_exposer.add_property( "pout"
, bp::make_function( (::scw_out_t * (*)( ::gezi::SegHandle const & ))(&SegHandle_wrapper::get_pout), bp::return_internal_reference< >() )
, bp::make_function( (void (*)( ::gezi::SegHandle &,::scw_out_t * ))(&SegHandle_wrapper::set_pout), bp::with_custodian_and_ward_postcall< 1, 2 >() ) );
SegHandle_exposer.def_readwrite( "token_vec", &gezi::SegHandle::token_vec );
SegHandle_exposer.add_property( "tokens"
, bp::make_function( (::token_t * (*)( ::gezi::SegHandle const & ))(&SegHandle_wrapper::get_tokens), bp::return_internal_reference< >() )
, bp::make_function( (void (*)( ::gezi::SegHandle &,::token_t * ))(&SegHandle_wrapper::set_tokens), bp::with_custodian_and_ward_postcall< 1, 2 >() ) );
}

bp::class_< gezi::SegNode >( "SegNode", bp::init< >() )
.def( bp::init< std::string, int, int, int >(( bp::arg("word_"), bp::arg("length_"), bp::arg("offset_"), bp::arg("weight_") )) )
.def_readwrite( "length", &gezi::SegNode::length )
.def_readwrite( "offset", &gezi::SegNode::offset )
.def_readwrite( "weight", &gezi::SegNode::weight )
.def_readwrite( "word", &gezi::SegNode::word );

{ //::gezi::Segmentor
typedef bp::class_< gezi::Segmentor > Segmentor_exposer_t;
Segmentor_exposer_t Segmentor_exposer = Segmentor_exposer_t( "Segmentor", bp::init< bp::optional< int > >(( bp::arg("seg_buff_size")=(int)(gezi::SegHandle::SEG_BUFF_SIZE) )) );
bp::scope Segmentor_scope( Segmentor_exposer );
bp::implicitly_convertible< int, gezi::Segmentor >();
{ //::gezi::Segmentor::Init

typedef bool ( *Init_function_type )( int,::std::string,int,::std::string );

Segmentor_exposer.def(
"Init"
, Init_function_type( &::gezi::Segmentor::Init )
, ( bp::arg("seg_buff_size")=(int)(gezi::SegHandle::SEG_BUFF_SIZE), bp::arg("data_dir")="./data/wordseg", bp::arg("type")=(int)(gezi::SEG_USE_DEFAULT), bp::arg("conf_path")="./conf/scw.conf" ) );

}
{ //::gezi::Segmentor::SegFlag

typedef void ( *SegFlag_function_type )( int );

Segmentor_exposer.def(
"SegFlag"
, SegFlag_function_type( &::gezi::Segmentor::SegFlag )
, ( bp::arg("flag_") ) );

}
{ //::gezi::Segmentor::Segment

typedef ::std::vector< std::string > ( *Segment_function_type )( ::std::string,int );

Segmentor_exposer.def(
"Segment"
, Segment_function_type( &::gezi::Segmentor::Segment )
, ( bp::arg("input"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::Segment

typedef bool ( *Segment_function_type )( ::std::string,::std::vector< std::string > &,int );

Segmentor_exposer.def(
"Segment"
, Segment_function_type( &::gezi::Segmentor::Segment )
, ( bp::arg("input"), bp::arg("result"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::Segment

typedef ::std::string ( *Segment_function_type )( ::std::string,::std::string,int );

Segmentor_exposer.def(
"Segment"
, Segment_function_type( &::gezi::Segmentor::Segment )
, ( bp::arg("input"), bp::arg("sep"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::Segment

typedef bool ( *Segment_function_type )( ::std::string,::std::vector< gezi::SegNode > &,int );

Segmentor_exposer.def(
"Segment"
, Segment_function_type( &::gezi::Segmentor::Segment )
, ( bp::arg("input"), bp::arg("result"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::Segment_

typedef bool ( *Segment__function_type )( ::std::string,int );

Segmentor_exposer.def(
"Segment_"
, Segment__function_type( &::gezi::Segmentor::Segment_ )
, ( bp::arg("input"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::Uninit

typedef void ( *Uninit_function_type )(  );

Segmentor_exposer.def(
"Uninit"
, Uninit_function_type( &::gezi::Segmentor::Uninit ) );

}
{ //::gezi::Segmentor::get_handle

typedef ::gezi::SegHandle & ( ::gezi::Segmentor::*get_handle_function_type )(  ) ;

Segmentor_exposer.def(
"get_handle"
, get_handle_function_type( &::gezi::Segmentor::get_handle )
, bp::return_internal_reference<>());

}
{ //::gezi::Segmentor::get_segnodes

typedef ::std::vector< gezi::SegNode > ( *get_segnodes_function_type )( ::gezi::SegHandle & );

Segmentor_exposer.def(
"get_segnodes"
, get_segnodes_function_type( &::gezi::Segmentor::get_segnodes )
, ( bp::arg("handle") ) );

}
{ //::gezi::Segmentor::get_segnodes

typedef ::std::vector< gezi::SegNode > ( ::gezi::Segmentor::*get_segnodes_function_type )(  ) ;

Segmentor_exposer.def(
"get_segnodes"
, get_segnodes_function_type( &::gezi::Segmentor::get_segnodes ) );

}
{ //::gezi::Segmentor::get_tokens

typedef int ( *get_tokens_function_type )( ::gezi::SegHandle &,int );

Segmentor_exposer.def(
"get_tokens"
, get_tokens_function_type( &::gezi::Segmentor::get_tokens )
, ( bp::arg("handle"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::get_tokens

typedef int ( ::gezi::Segmentor::*get_tokens_function_type )( int ) ;

Segmentor_exposer.def(
"get_tokens"
, get_tokens_function_type( &::gezi::Segmentor::get_tokens )
, ( bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::init

typedef bool ( *init_function_type )( ::std::string,int,::std::string );

Segmentor_exposer.def(
"init"
, init_function_type( &::gezi::Segmentor::init )
, ( bp::arg("data_dir")="./data/wordseg", bp::arg("type")=(int)(gezi::SEG_USE_DEFAULT), bp::arg("conf_path")="./conf/scw.conf" ) );

}
{ //::gezi::Segmentor::seg_words

typedef bool ( *seg_words_function_type )( ::std::string,::gezi::SegHandle & );

Segmentor_exposer.def(
"seg_words"
, seg_words_function_type( &::gezi::Segmentor::seg_words )
, ( bp::arg("input"), bp::arg("handle") ) );

}
{ //::gezi::Segmentor::segment

typedef bool ( *segment_function_type )( ::std::string,::gezi::SegHandle &,int );

Segmentor_exposer.def(
"segment"
, segment_function_type( &::gezi::Segmentor::segment )
, ( bp::arg("input"), bp::arg("handle"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::segment

typedef bool ( *segment_function_type )( ::std::string,::gezi::SegHandle &,::std::vector< std::string > &,int );

Segmentor_exposer.def(
"segment"
, segment_function_type( &::gezi::Segmentor::segment )
, ( bp::arg("input"), bp::arg("handle"), bp::arg("result"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::segment

typedef ::std::string ( *segment_function_type )( ::std::string,::gezi::SegHandle &,::std::string,int );

Segmentor_exposer.def(
"segment"
, segment_function_type( &::gezi::Segmentor::segment )
, ( bp::arg("input"), bp::arg("handle"), bp::arg("sep"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::segment

typedef ::std::vector< std::string > ( ::gezi::Segmentor::*segment_function_type )( ::std::string,int ) ;

Segmentor_exposer.def(
"segment"
, segment_function_type( &::gezi::Segmentor::segment )
, ( bp::arg("input"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::segment

typedef bool ( ::gezi::Segmentor::*segment_function_type )( ::std::string,::std::vector< std::string > &,int ) ;

Segmentor_exposer.def(
"segment"
, segment_function_type( &::gezi::Segmentor::segment )
, ( bp::arg("input"), bp::arg("result"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::segment

typedef ::std::string ( ::gezi::Segmentor::*segment_function_type )( ::std::string,::std::string,int ) ;

Segmentor_exposer.def(
"segment"
, segment_function_type( &::gezi::Segmentor::segment )
, ( bp::arg("input"), bp::arg("sep"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::segment

typedef bool ( ::gezi::Segmentor::*segment_function_type )( ::std::string,::std::vector< gezi::SegNode > &,int ) ;

Segmentor_exposer.def(
"segment"
, segment_function_type( &::gezi::Segmentor::segment )
, ( bp::arg("input"), bp::arg("result"), bp::arg("type")=(int)(gezi::SEG_WPCOMP) ) );

}
{ //::gezi::Segmentor::set_flag

typedef ::gezi::Segmentor & ( ::gezi::Segmentor::*set_flag_function_type )( int ) ;

Segmentor_exposer.def(
"set_flag"
, set_flag_function_type( &::gezi::Segmentor::set_flag )
, ( bp::arg("flag_") )
, bp::return_internal_reference<>());

}
{ //::gezi::Segmentor::uninit

typedef void ( *uninit_function_type )(  );

Segmentor_exposer.def(
"uninit"
, uninit_function_type( &::gezi::Segmentor::uninit ) );

}
Segmentor_exposer.staticmethod( "Init" );
Segmentor_exposer.staticmethod( "SegFlag" );
Segmentor_exposer.staticmethod( "Segment" );
Segmentor_exposer.staticmethod( "Segment_" );
Segmentor_exposer.staticmethod( "Uninit" );
Segmentor_exposer.staticmethod( "get_segnodes" );
Segmentor_exposer.staticmethod( "get_tokens" );
Segmentor_exposer.staticmethod( "init" );
Segmentor_exposer.staticmethod( "seg_words" );
Segmentor_exposer.staticmethod( "segment" );
Segmentor_exposer.staticmethod( "uninit" );
}

{ //::gezi::print_seg_result

typedef void ( *print_seg_result_function_type )( ::gezi::SegHandle const & );

bp::def(
"print_seg_result"
, print_seg_result_function_type( &::gezi::print_seg_result )
, ( bp::arg("handle") ) );

}

bp::scope().attr("SEG_BASIC") = gezi::SEG_BASIC;

bp::scope().attr("SEG_HUMAN_NAME") = gezi::SEG_HUMAN_NAME;

bp::scope().attr("SEG_MERGE_NEWWORD") = gezi::SEG_MERGE_NEWWORD;

bp::scope().attr("SEG_NEWWORD") = gezi::SEG_NEWWORD;

bp::scope().attr("SEG_USE_ALL") = gezi::SEG_USE_ALL;

bp::scope().attr("SEG_USE_DEFAULT") = gezi::SEG_USE_DEFAULT;

bp::scope().attr("SEG_USE_POSTAG") = gezi::SEG_USE_POSTAG;

bp::scope().attr("SEG_USE_SPLIT") = gezi::SEG_USE_SPLIT;

bp::scope().attr("SEG_USE_TRIE") = gezi::SEG_USE_TRIE;

bp::scope().attr("SEG_WPCOMP") = gezi::SEG_WPCOMP;
}
