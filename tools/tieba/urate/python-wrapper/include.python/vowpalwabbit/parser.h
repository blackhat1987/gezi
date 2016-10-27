#pragma once
#include "io_buf.h"
#include "parse_primitives.h"
#include "example.h"
#include "vw.h"
parser* new_parser();
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include "global_data.h"
void enable_sources(vw& all, po::variables_map& vm, bool quiet, size_t passes);
bool examples_to_finish();
void initialize_parser_datastructures(vw& all);
void release_parser_datastructures(vw& all);
void adjust_used_index(vw& all);
void make_example_available();
bool parser_done(parser* p);
void set_done(vw& all);
bool inconsistent_cache(size_t numbits, io_buf& cache);
void reset_source(vw& all, size_t numbits);
void finalize_source(parser* source);
void set_compressed(parser* par);
void initialize_examples(vw& all);
void free_parser(vw& all);
bool parse_atomic_example(vw& all, example* ae, bool do_read);
