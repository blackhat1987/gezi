#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=../../../../../../ps/se/toolchain/gcc_only_4.8.2/bin/g++
CXX=../../../../../../ps/se/toolchain/gcc_only_4.8.2/bin/g++
CXXFLAGS=-g \
  -O0 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -std=c++0x \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs
CFLAGS=-g \
  -O0 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -std=c++0x \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I../include \
  -I../utils \
  -I../output \
  -I../output/include \
  -I../include/feature \
  -I../include/model \
  -I../include/numeric
DEP_INCPATH=-I../../../../../../com/btest/gtest \
  -I../../../../../../com/btest/gtest/include \
  -I../../../../../../com/btest/gtest/output \
  -I../../../../../../com/btest/gtest/output/include \
  -I../../../../../../lib2-64/bsl \
  -I../../../../../../lib2-64/bsl/include \
  -I../../../../../../lib2-64/bsl/output \
  -I../../../../../../lib2-64/bsl/output/include \
  -I../../../../../../lib2-64/ccode \
  -I../../../../../../lib2-64/ccode/include \
  -I../../../../../../lib2-64/ccode/output \
  -I../../../../../../lib2-64/ccode/output/include \
  -I../../../../../../lib2-64/dict \
  -I../../../../../../lib2-64/dict/include \
  -I../../../../../../lib2-64/dict/output \
  -I../../../../../../lib2-64/dict/output/include \
  -I../../../../../../lib2-64/libcrf \
  -I../../../../../../lib2-64/libcrf/include \
  -I../../../../../../lib2-64/libcrf/output \
  -I../../../../../../lib2-64/libcrf/output/include \
  -I../../../../../../lib2-64/others-ex \
  -I../../../../../../lib2-64/others-ex/include \
  -I../../../../../../lib2-64/others-ex/output \
  -I../../../../../../lib2-64/others-ex/output/include \
  -I../../../../../../lib2-64/postag \
  -I../../../../../../lib2-64/postag/include \
  -I../../../../../../lib2-64/postag/output \
  -I../../../../../../lib2-64/postag/output/include \
  -I../../../../../../lib2-64/ullib \
  -I../../../../../../lib2-64/ullib/include \
  -I../../../../../../lib2-64/ullib/output \
  -I../../../../../../lib2-64/ullib/output/include \
  -I../../../../../../lib2-64/wordseg \
  -I../../../../../../lib2-64/wordseg/include \
  -I../../../../../../lib2-64/wordseg/output \
  -I../../../../../../lib2-64/wordseg/output/include \
  -I../../../../../../ps/se/toolchain \
  -I../../../../../../ps/se/toolchain/include \
  -I../../../../../../ps/se/toolchain/output \
  -I../../../../../../ps/se/toolchain/output/include \
  -I../../../../../../public/comlog-plugin \
  -I../../../../../../public/comlog-plugin/include \
  -I../../../../../../public/comlog-plugin/output \
  -I../../../../../../public/comlog-plugin/output/include \
  -I../../../../../../public/configure \
  -I../../../../../../public/configure/include \
  -I../../../../../../public/configure/output \
  -I../../../../../../public/configure/output/include \
  -I../../../../../../public/connectpool \
  -I../../../../../../public/connectpool/include \
  -I../../../../../../public/connectpool/output \
  -I../../../../../../public/connectpool/output/include \
  -I../../../../../../public/odict \
  -I../../../../../../public/odict/include \
  -I../../../../../../public/odict/output \
  -I../../../../../../public/odict/output/include \
  -I../../../../../../public/spreg \
  -I../../../../../../public/spreg/include \
  -I../../../../../../public/spreg/output \
  -I../../../../../../public/spreg/output/include \
  -I../../../../../../public/uconv \
  -I../../../../../../public/uconv/include \
  -I../../../../../../public/uconv/output \
  -I../../../../../../public/uconv/output/include \
  -I../../../../../../quality/autotest/reportlib/cpp \
  -I../../../../../../quality/autotest/reportlib/cpp/include \
  -I../../../../../../quality/autotest/reportlib/cpp/output \
  -I../../../../../../quality/autotest/reportlib/cpp/output/include \
  -I../../../../../../third-64/boost \
  -I../../../../../../third-64/boost/include \
  -I../../../../../../third-64/boost/output \
  -I../../../../../../third-64/boost/output/include \
  -I../../../../../../third-64/gflags \
  -I../../../../../../third-64/gflags/include \
  -I../../../../../../third-64/gflags/output \
  -I../../../../../../third-64/gflags/output/include \
  -I../../../../../../third-64/glog \
  -I../../../../../../third-64/glog/include \
  -I../../../../../../third-64/glog/output \
  -I../../../../../../third-64/glog/output/include \
  -I../../../../../../third-64/pcre \
  -I../../../../../../third-64/pcre/include \
  -I../../../../../../third-64/pcre/output \
  -I../../../../../../third-64/pcre/output/include \
  -I../../../../../../third-64/tcmalloc \
  -I../../../../../../third-64/tcmalloc/include \
  -I../../../../../../third-64/tcmalloc/output \
  -I../../../../../../third-64/tcmalloc/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=2c4b1d54e31aac06873e60bcdc992bf2  COMAKE


.PHONY:all
all:comake2_makefile_check test_lambda test_bins test_datetime test_content_filter test_regex test_regex2 test_encode test_json test_escape test_other test_feature_selector openmp_hello openmp_test test_exception test_map_util test_seg test_identifer test_linear test_pinyin test_namepattern test_conf test_random test_shared_ptr test_binfinder test_seralize test_string test_bitop test_featurevector test_split test_tieba_get_info test_content_process test_cached_fetcher test_bind test_lrumap test_seralize_xml test_thread_local test_configure test_static test_cpplinq test_partial_sort test_string_util test_mean_var test_const test_matchdict test_sharedobjects test_matchdict test_erase 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf test_lambda
	rm -rf ./output/bin/test_lambda
	rm -rf test_bins
	rm -rf ./output/bin/test_bins
	rm -rf test_datetime
	rm -rf ./output/bin/test_datetime
	rm -rf test_content_filter
	rm -rf ./output/bin/test_content_filter
	rm -rf test_regex
	rm -rf ./output/bin/test_regex
	rm -rf test_regex2
	rm -rf ./output/bin/test_regex2
	rm -rf test_encode
	rm -rf ./output/bin/test_encode
	rm -rf test_json
	rm -rf ./output/bin/test_json
	rm -rf test_escape
	rm -rf ./output/bin/test_escape
	rm -rf test_other
	rm -rf ./output/bin/test_other
	rm -rf test_feature_selector
	rm -rf ./output/bin/test_feature_selector
	rm -rf openmp_hello
	rm -rf ./bin/openmp_hello
	rm -rf openmp_test
	rm -rf ./bin/openmp_test
	rm -rf test_exception
	rm -rf ./bin/test_exception
	rm -rf test_map_util
	rm -rf ./bin/test_map_util
	rm -rf test_seg
	rm -rf ./output/bin/test_seg
	rm -rf test_identifer
	rm -rf ./output/bin/test_identifer
	rm -rf test_linear
	rm -rf ./output/bin/test_linear
	rm -rf test_pinyin
	rm -rf ./output/bin/test_pinyin
	rm -rf test_namepattern
	rm -rf ./output/bin/test_namepattern
	rm -rf test_conf
	rm -rf ./output/bin/test_conf
	rm -rf test_random
	rm -rf ./output/bin/test_random
	rm -rf test_shared_ptr
	rm -rf ./output/bin/test_shared_ptr
	rm -rf test_binfinder
	rm -rf ./output/bin/test_binfinder
	rm -rf test_seralize
	rm -rf ./output/bin/test_seralize
	rm -rf test_string
	rm -rf ./output/bin/test_string
	rm -rf test_bitop
	rm -rf ./output/bin/test_bitop
	rm -rf test_featurevector
	rm -rf ./output/bin/test_featurevector
	rm -rf test_split
	rm -rf ./output/bin/test_split
	rm -rf test_tieba_get_info
	rm -rf ./output/bin/test_tieba_get_info
	rm -rf test_content_process
	rm -rf ./output/bin/test_content_process
	rm -rf test_cached_fetcher
	rm -rf ./output/bin/test_cached_fetcher
	rm -rf test_bind
	rm -rf ./output/bin/test_bind
	rm -rf test_lrumap
	rm -rf ./output/bin/test_lrumap
	rm -rf test_seralize_xml
	rm -rf ./output/bin/test_seralize_xml
	rm -rf test_thread_local
	rm -rf ./output/bin/test_thread_local
	rm -rf test_configure
	rm -rf ./output/bin/test_configure
	rm -rf test_static
	rm -rf ./output/bin/test_static
	rm -rf test_cpplinq
	rm -rf ./output/bin/test_cpplinq
	rm -rf test_partial_sort
	rm -rf ./output/bin/test_partial_sort
	rm -rf test_string_util
	rm -rf ./output/bin/test_string_util
	rm -rf test_mean_var
	rm -rf ./output/bin/test_mean_var
	rm -rf test_const
	rm -rf ./output/bin/test_const
	rm -rf test_matchdict
	rm -rf ./output/bin/test_matchdict
	rm -rf test_sharedobjects
	rm -rf ./output/bin/test_sharedobjects
	rm -rf test_matchdict
	rm -rf ./output/bin/test_matchdict
	rm -rf test_erase
	rm -rf ./output/bin/test_erase
	rm -rf test_lambda_test_lambda.o
	rm -rf test_bins_test_bins.o
	rm -rf test_datetime_test_datetime.o
	rm -rf test_content_filter_test_content_filter.o
	rm -rf test_regex_test_regex.o
	rm -rf ../src/model/test_regex_LinearModel.o
	rm -rf ../src/model/test_regex_ModelFactory.o
	rm -rf ../src/model/test_regex_Predictor.o
	rm -rf ../src/model/test_regex_RandForestModel.o
	rm -rf ../src/model/test_regex_Score.o
	rm -rf ../src/model/test_regex_SharedPredictor.o
	rm -rf ../src/model/test_regex_SvmModel.o
	rm -rf ../src/json/test_regex_json_reader.o
	rm -rf ../src/json/test_regex_json_value.o
	rm -rf ../src/json/test_regex_json_writer.o
	rm -rf test_regex2_test_regex2.o
	rm -rf ../src/model/test_regex2_LinearModel.o
	rm -rf ../src/model/test_regex2_ModelFactory.o
	rm -rf ../src/model/test_regex2_Predictor.o
	rm -rf ../src/model/test_regex2_RandForestModel.o
	rm -rf ../src/model/test_regex2_Score.o
	rm -rf ../src/model/test_regex2_SharedPredictor.o
	rm -rf ../src/model/test_regex2_SvmModel.o
	rm -rf ../src/json/test_regex2_json_reader.o
	rm -rf ../src/json/test_regex2_json_value.o
	rm -rf ../src/json/test_regex2_json_writer.o
	rm -rf test_encode_test_encode.o
	rm -rf ../src/model/test_encode_LinearModel.o
	rm -rf ../src/model/test_encode_ModelFactory.o
	rm -rf ../src/model/test_encode_Predictor.o
	rm -rf ../src/model/test_encode_RandForestModel.o
	rm -rf ../src/model/test_encode_Score.o
	rm -rf ../src/model/test_encode_SharedPredictor.o
	rm -rf ../src/model/test_encode_SvmModel.o
	rm -rf ../src/json/test_encode_json_reader.o
	rm -rf ../src/json/test_encode_json_value.o
	rm -rf ../src/json/test_encode_json_writer.o
	rm -rf test_json_test_json.o
	rm -rf ../src/model/test_json_LinearModel.o
	rm -rf ../src/model/test_json_ModelFactory.o
	rm -rf ../src/model/test_json_Predictor.o
	rm -rf ../src/model/test_json_RandForestModel.o
	rm -rf ../src/model/test_json_Score.o
	rm -rf ../src/model/test_json_SharedPredictor.o
	rm -rf ../src/model/test_json_SvmModel.o
	rm -rf ../src/json/test_json_json_reader.o
	rm -rf ../src/json/test_json_json_value.o
	rm -rf ../src/json/test_json_json_writer.o
	rm -rf test_escape_test_escape.o
	rm -rf ../src/model/test_escape_LinearModel.o
	rm -rf ../src/model/test_escape_ModelFactory.o
	rm -rf ../src/model/test_escape_Predictor.o
	rm -rf ../src/model/test_escape_RandForestModel.o
	rm -rf ../src/model/test_escape_Score.o
	rm -rf ../src/model/test_escape_SharedPredictor.o
	rm -rf ../src/model/test_escape_SvmModel.o
	rm -rf ../src/json/test_escape_json_reader.o
	rm -rf ../src/json/test_escape_json_value.o
	rm -rf ../src/json/test_escape_json_writer.o
	rm -rf test_other_test_other.o
	rm -rf ../src/model/test_other_LinearModel.o
	rm -rf ../src/model/test_other_ModelFactory.o
	rm -rf ../src/model/test_other_Predictor.o
	rm -rf ../src/model/test_other_RandForestModel.o
	rm -rf ../src/model/test_other_Score.o
	rm -rf ../src/model/test_other_SharedPredictor.o
	rm -rf ../src/model/test_other_SvmModel.o
	rm -rf ../src/json/test_other_json_reader.o
	rm -rf ../src/json/test_other_json_value.o
	rm -rf ../src/json/test_other_json_writer.o
	rm -rf test_feature_selector_test_feature_selector.o
	rm -rf ../src/model/test_feature_selector_LinearModel.o
	rm -rf ../src/model/test_feature_selector_ModelFactory.o
	rm -rf ../src/model/test_feature_selector_Predictor.o
	rm -rf ../src/model/test_feature_selector_RandForestModel.o
	rm -rf ../src/model/test_feature_selector_Score.o
	rm -rf ../src/model/test_feature_selector_SharedPredictor.o
	rm -rf ../src/model/test_feature_selector_SvmModel.o
	rm -rf ../src/json/test_feature_selector_json_reader.o
	rm -rf ../src/json/test_feature_selector_json_value.o
	rm -rf ../src/json/test_feature_selector_json_writer.o
	rm -rf openmp/openmp_hello_hello.o
	rm -rf openmp/openmp_test_test.o
	rm -rf ../src/model/openmp_test_LinearModel.o
	rm -rf ../src/model/openmp_test_ModelFactory.o
	rm -rf ../src/model/openmp_test_Predictor.o
	rm -rf ../src/model/openmp_test_RandForestModel.o
	rm -rf ../src/model/openmp_test_Score.o
	rm -rf ../src/model/openmp_test_SharedPredictor.o
	rm -rf ../src/model/openmp_test_SvmModel.o
	rm -rf ../src/json/openmp_test_json_reader.o
	rm -rf ../src/json/openmp_test_json_value.o
	rm -rf ../src/json/openmp_test_json_writer.o
	rm -rf test_exception_test_exception.o
	rm -rf test_map_util_test_map_util.o
	rm -rf test_seg_test_seg.o
	rm -rf ../src/model/test_seg_LinearModel.o
	rm -rf ../src/model/test_seg_ModelFactory.o
	rm -rf ../src/model/test_seg_Predictor.o
	rm -rf ../src/model/test_seg_RandForestModel.o
	rm -rf ../src/model/test_seg_Score.o
	rm -rf ../src/model/test_seg_SharedPredictor.o
	rm -rf ../src/model/test_seg_SvmModel.o
	rm -rf ../src/json/test_seg_json_reader.o
	rm -rf ../src/json/test_seg_json_value.o
	rm -rf ../src/json/test_seg_json_writer.o
	rm -rf test_identifer_test_identifer.o
	rm -rf ../src/model/test_identifer_LinearModel.o
	rm -rf ../src/model/test_identifer_ModelFactory.o
	rm -rf ../src/model/test_identifer_Predictor.o
	rm -rf ../src/model/test_identifer_RandForestModel.o
	rm -rf ../src/model/test_identifer_Score.o
	rm -rf ../src/model/test_identifer_SharedPredictor.o
	rm -rf ../src/model/test_identifer_SvmModel.o
	rm -rf ../src/json/test_identifer_json_reader.o
	rm -rf ../src/json/test_identifer_json_value.o
	rm -rf ../src/json/test_identifer_json_writer.o
	rm -rf test_linear_test_linear.o
	rm -rf ../src/model/test_linear_LinearModel.o
	rm -rf ../src/model/test_linear_ModelFactory.o
	rm -rf ../src/model/test_linear_Predictor.o
	rm -rf ../src/model/test_linear_RandForestModel.o
	rm -rf ../src/model/test_linear_Score.o
	rm -rf ../src/model/test_linear_SharedPredictor.o
	rm -rf ../src/model/test_linear_SvmModel.o
	rm -rf ../src/json/test_linear_json_reader.o
	rm -rf ../src/json/test_linear_json_value.o
	rm -rf ../src/json/test_linear_json_writer.o
	rm -rf test_pinyin_test_pinyin.o
	rm -rf ../src/model/test_pinyin_LinearModel.o
	rm -rf ../src/model/test_pinyin_ModelFactory.o
	rm -rf ../src/model/test_pinyin_Predictor.o
	rm -rf ../src/model/test_pinyin_RandForestModel.o
	rm -rf ../src/model/test_pinyin_Score.o
	rm -rf ../src/model/test_pinyin_SharedPredictor.o
	rm -rf ../src/model/test_pinyin_SvmModel.o
	rm -rf ../src/json/test_pinyin_json_reader.o
	rm -rf ../src/json/test_pinyin_json_value.o
	rm -rf ../src/json/test_pinyin_json_writer.o
	rm -rf test_namepattern_test_namepattern.o
	rm -rf ../src/model/test_namepattern_LinearModel.o
	rm -rf ../src/model/test_namepattern_ModelFactory.o
	rm -rf ../src/model/test_namepattern_Predictor.o
	rm -rf ../src/model/test_namepattern_RandForestModel.o
	rm -rf ../src/model/test_namepattern_Score.o
	rm -rf ../src/model/test_namepattern_SharedPredictor.o
	rm -rf ../src/model/test_namepattern_SvmModel.o
	rm -rf ../src/json/test_namepattern_json_reader.o
	rm -rf ../src/json/test_namepattern_json_value.o
	rm -rf ../src/json/test_namepattern_json_writer.o
	rm -rf test_conf_test_conf.o
	rm -rf ../src/model/test_conf_LinearModel.o
	rm -rf ../src/model/test_conf_ModelFactory.o
	rm -rf ../src/model/test_conf_Predictor.o
	rm -rf ../src/model/test_conf_RandForestModel.o
	rm -rf ../src/model/test_conf_Score.o
	rm -rf ../src/model/test_conf_SharedPredictor.o
	rm -rf ../src/model/test_conf_SvmModel.o
	rm -rf ../src/json/test_conf_json_reader.o
	rm -rf ../src/json/test_conf_json_value.o
	rm -rf ../src/json/test_conf_json_writer.o
	rm -rf test_random_test_random.o
	rm -rf ../src/model/test_random_LinearModel.o
	rm -rf ../src/model/test_random_ModelFactory.o
	rm -rf ../src/model/test_random_Predictor.o
	rm -rf ../src/model/test_random_RandForestModel.o
	rm -rf ../src/model/test_random_Score.o
	rm -rf ../src/model/test_random_SharedPredictor.o
	rm -rf ../src/model/test_random_SvmModel.o
	rm -rf ../src/json/test_random_json_reader.o
	rm -rf ../src/json/test_random_json_value.o
	rm -rf ../src/json/test_random_json_writer.o
	rm -rf test_shared_ptr_test_shared_ptr.o
	rm -rf ../src/model/test_shared_ptr_LinearModel.o
	rm -rf ../src/model/test_shared_ptr_ModelFactory.o
	rm -rf ../src/model/test_shared_ptr_Predictor.o
	rm -rf ../src/model/test_shared_ptr_RandForestModel.o
	rm -rf ../src/model/test_shared_ptr_Score.o
	rm -rf ../src/model/test_shared_ptr_SharedPredictor.o
	rm -rf ../src/model/test_shared_ptr_SvmModel.o
	rm -rf ../src/json/test_shared_ptr_json_reader.o
	rm -rf ../src/json/test_shared_ptr_json_value.o
	rm -rf ../src/json/test_shared_ptr_json_writer.o
	rm -rf test_binfinder_test_binfinder.o
	rm -rf ../src/model/test_binfinder_LinearModel.o
	rm -rf ../src/model/test_binfinder_ModelFactory.o
	rm -rf ../src/model/test_binfinder_Predictor.o
	rm -rf ../src/model/test_binfinder_RandForestModel.o
	rm -rf ../src/model/test_binfinder_Score.o
	rm -rf ../src/model/test_binfinder_SharedPredictor.o
	rm -rf ../src/model/test_binfinder_SvmModel.o
	rm -rf ../src/json/test_binfinder_json_reader.o
	rm -rf ../src/json/test_binfinder_json_value.o
	rm -rf ../src/json/test_binfinder_json_writer.o
	rm -rf test_seralize_test_seralize.o
	rm -rf ../src/model/test_seralize_LinearModel.o
	rm -rf ../src/model/test_seralize_ModelFactory.o
	rm -rf ../src/model/test_seralize_Predictor.o
	rm -rf ../src/model/test_seralize_RandForestModel.o
	rm -rf ../src/model/test_seralize_Score.o
	rm -rf ../src/model/test_seralize_SharedPredictor.o
	rm -rf ../src/model/test_seralize_SvmModel.o
	rm -rf ../src/json/test_seralize_json_reader.o
	rm -rf ../src/json/test_seralize_json_value.o
	rm -rf ../src/json/test_seralize_json_writer.o
	rm -rf test_string_test_string.o
	rm -rf ../src/model/test_string_LinearModel.o
	rm -rf ../src/model/test_string_ModelFactory.o
	rm -rf ../src/model/test_string_Predictor.o
	rm -rf ../src/model/test_string_RandForestModel.o
	rm -rf ../src/model/test_string_Score.o
	rm -rf ../src/model/test_string_SharedPredictor.o
	rm -rf ../src/model/test_string_SvmModel.o
	rm -rf ../src/json/test_string_json_reader.o
	rm -rf ../src/json/test_string_json_value.o
	rm -rf ../src/json/test_string_json_writer.o
	rm -rf test_bitop_test_bitop.o
	rm -rf ../src/model/test_bitop_LinearModel.o
	rm -rf ../src/model/test_bitop_ModelFactory.o
	rm -rf ../src/model/test_bitop_Predictor.o
	rm -rf ../src/model/test_bitop_RandForestModel.o
	rm -rf ../src/model/test_bitop_Score.o
	rm -rf ../src/model/test_bitop_SharedPredictor.o
	rm -rf ../src/model/test_bitop_SvmModel.o
	rm -rf ../src/json/test_bitop_json_reader.o
	rm -rf ../src/json/test_bitop_json_value.o
	rm -rf ../src/json/test_bitop_json_writer.o
	rm -rf test_featurevector_test_featurevector.o
	rm -rf ../src/model/test_featurevector_LinearModel.o
	rm -rf ../src/model/test_featurevector_ModelFactory.o
	rm -rf ../src/model/test_featurevector_Predictor.o
	rm -rf ../src/model/test_featurevector_RandForestModel.o
	rm -rf ../src/model/test_featurevector_Score.o
	rm -rf ../src/model/test_featurevector_SharedPredictor.o
	rm -rf ../src/model/test_featurevector_SvmModel.o
	rm -rf ../src/json/test_featurevector_json_reader.o
	rm -rf ../src/json/test_featurevector_json_value.o
	rm -rf ../src/json/test_featurevector_json_writer.o
	rm -rf test_split_test_split.o
	rm -rf ../src/model/test_split_LinearModel.o
	rm -rf ../src/model/test_split_ModelFactory.o
	rm -rf ../src/model/test_split_Predictor.o
	rm -rf ../src/model/test_split_RandForestModel.o
	rm -rf ../src/model/test_split_Score.o
	rm -rf ../src/model/test_split_SharedPredictor.o
	rm -rf ../src/model/test_split_SvmModel.o
	rm -rf ../src/json/test_split_json_reader.o
	rm -rf ../src/json/test_split_json_value.o
	rm -rf ../src/json/test_split_json_writer.o
	rm -rf test_tieba_get_info_test_tieba_get_info.o
	rm -rf ../src/model/test_tieba_get_info_LinearModel.o
	rm -rf ../src/model/test_tieba_get_info_ModelFactory.o
	rm -rf ../src/model/test_tieba_get_info_Predictor.o
	rm -rf ../src/model/test_tieba_get_info_RandForestModel.o
	rm -rf ../src/model/test_tieba_get_info_Score.o
	rm -rf ../src/model/test_tieba_get_info_SharedPredictor.o
	rm -rf ../src/model/test_tieba_get_info_SvmModel.o
	rm -rf ../src/json/test_tieba_get_info_json_reader.o
	rm -rf ../src/json/test_tieba_get_info_json_value.o
	rm -rf ../src/json/test_tieba_get_info_json_writer.o
	rm -rf test_content_process_test_content_process.o
	rm -rf test_cached_fetcher_test_cached_fetcher.o
	rm -rf ../src/model/test_cached_fetcher_LinearModel.o
	rm -rf ../src/model/test_cached_fetcher_ModelFactory.o
	rm -rf ../src/model/test_cached_fetcher_Predictor.o
	rm -rf ../src/model/test_cached_fetcher_RandForestModel.o
	rm -rf ../src/model/test_cached_fetcher_Score.o
	rm -rf ../src/model/test_cached_fetcher_SharedPredictor.o
	rm -rf ../src/model/test_cached_fetcher_SvmModel.o
	rm -rf ../src/json/test_cached_fetcher_json_reader.o
	rm -rf ../src/json/test_cached_fetcher_json_value.o
	rm -rf ../src/json/test_cached_fetcher_json_writer.o
	rm -rf test_bind_test_bind.o
	rm -rf ../src/model/test_bind_LinearModel.o
	rm -rf ../src/model/test_bind_ModelFactory.o
	rm -rf ../src/model/test_bind_Predictor.o
	rm -rf ../src/model/test_bind_RandForestModel.o
	rm -rf ../src/model/test_bind_Score.o
	rm -rf ../src/model/test_bind_SharedPredictor.o
	rm -rf ../src/model/test_bind_SvmModel.o
	rm -rf ../src/json/test_bind_json_reader.o
	rm -rf ../src/json/test_bind_json_value.o
	rm -rf ../src/json/test_bind_json_writer.o
	rm -rf test_lrumap_test_lrumap.o
	rm -rf ../src/model/test_lrumap_LinearModel.o
	rm -rf ../src/model/test_lrumap_ModelFactory.o
	rm -rf ../src/model/test_lrumap_Predictor.o
	rm -rf ../src/model/test_lrumap_RandForestModel.o
	rm -rf ../src/model/test_lrumap_Score.o
	rm -rf ../src/model/test_lrumap_SharedPredictor.o
	rm -rf ../src/model/test_lrumap_SvmModel.o
	rm -rf ../src/json/test_lrumap_json_reader.o
	rm -rf ../src/json/test_lrumap_json_value.o
	rm -rf ../src/json/test_lrumap_json_writer.o
	rm -rf test_seralize_xml_test_seralize_xml.o
	rm -rf ../src/model/test_seralize_xml_LinearModel.o
	rm -rf ../src/model/test_seralize_xml_ModelFactory.o
	rm -rf ../src/model/test_seralize_xml_Predictor.o
	rm -rf ../src/model/test_seralize_xml_RandForestModel.o
	rm -rf ../src/model/test_seralize_xml_Score.o
	rm -rf ../src/model/test_seralize_xml_SharedPredictor.o
	rm -rf ../src/model/test_seralize_xml_SvmModel.o
	rm -rf ../src/json/test_seralize_xml_json_reader.o
	rm -rf ../src/json/test_seralize_xml_json_value.o
	rm -rf ../src/json/test_seralize_xml_json_writer.o
	rm -rf test_thread_local_test_thread_local.o
	rm -rf ../src/model/test_thread_local_LinearModel.o
	rm -rf ../src/model/test_thread_local_ModelFactory.o
	rm -rf ../src/model/test_thread_local_Predictor.o
	rm -rf ../src/model/test_thread_local_RandForestModel.o
	rm -rf ../src/model/test_thread_local_Score.o
	rm -rf ../src/model/test_thread_local_SharedPredictor.o
	rm -rf ../src/model/test_thread_local_SvmModel.o
	rm -rf ../src/json/test_thread_local_json_reader.o
	rm -rf ../src/json/test_thread_local_json_value.o
	rm -rf ../src/json/test_thread_local_json_writer.o
	rm -rf test_configure_test_configure.o
	rm -rf ../src/model/test_configure_LinearModel.o
	rm -rf ../src/model/test_configure_ModelFactory.o
	rm -rf ../src/model/test_configure_Predictor.o
	rm -rf ../src/model/test_configure_RandForestModel.o
	rm -rf ../src/model/test_configure_Score.o
	rm -rf ../src/model/test_configure_SharedPredictor.o
	rm -rf ../src/model/test_configure_SvmModel.o
	rm -rf ../src/json/test_configure_json_reader.o
	rm -rf ../src/json/test_configure_json_value.o
	rm -rf ../src/json/test_configure_json_writer.o
	rm -rf test_static_test_static.o
	rm -rf ../src/model/test_static_LinearModel.o
	rm -rf ../src/model/test_static_ModelFactory.o
	rm -rf ../src/model/test_static_Predictor.o
	rm -rf ../src/model/test_static_RandForestModel.o
	rm -rf ../src/model/test_static_Score.o
	rm -rf ../src/model/test_static_SharedPredictor.o
	rm -rf ../src/model/test_static_SvmModel.o
	rm -rf ../src/json/test_static_json_reader.o
	rm -rf ../src/json/test_static_json_value.o
	rm -rf ../src/json/test_static_json_writer.o
	rm -rf test_cpplinq_test_cpplinq.o
	rm -rf ../src/model/test_cpplinq_LinearModel.o
	rm -rf ../src/model/test_cpplinq_ModelFactory.o
	rm -rf ../src/model/test_cpplinq_Predictor.o
	rm -rf ../src/model/test_cpplinq_RandForestModel.o
	rm -rf ../src/model/test_cpplinq_Score.o
	rm -rf ../src/model/test_cpplinq_SharedPredictor.o
	rm -rf ../src/model/test_cpplinq_SvmModel.o
	rm -rf ../src/json/test_cpplinq_json_reader.o
	rm -rf ../src/json/test_cpplinq_json_value.o
	rm -rf ../src/json/test_cpplinq_json_writer.o
	rm -rf test_partial_sort_test_partial_sort.o
	rm -rf ../src/model/test_partial_sort_LinearModel.o
	rm -rf ../src/model/test_partial_sort_ModelFactory.o
	rm -rf ../src/model/test_partial_sort_Predictor.o
	rm -rf ../src/model/test_partial_sort_RandForestModel.o
	rm -rf ../src/model/test_partial_sort_Score.o
	rm -rf ../src/model/test_partial_sort_SharedPredictor.o
	rm -rf ../src/model/test_partial_sort_SvmModel.o
	rm -rf ../src/json/test_partial_sort_json_reader.o
	rm -rf ../src/json/test_partial_sort_json_value.o
	rm -rf ../src/json/test_partial_sort_json_writer.o
	rm -rf test_string_util_test_string_util.o
	rm -rf test_mean_var_test_mean_var.o
	rm -rf test_const_test_const.o
	rm -rf test_sharedobjects_test_sharedobjects.o
	rm -rf test_matchdict_test_matchdict.o
	rm -rf test_erase_test_erase.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

test_lambda:test_lambda_test_lambda.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_lambda[0m']"
	$(CXX) test_lambda_test_lambda.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_lambda
	mkdir -p ./output/bin
	cp -f --link test_lambda ./output/bin

test_bins:test_bins_test_bins.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_bins[0m']"
	$(CXX) test_bins_test_bins.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_bins
	mkdir -p ./output/bin
	cp -f --link test_bins ./output/bin

test_datetime:test_datetime_test_datetime.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_datetime[0m']"
	$(CXX) test_datetime_test_datetime.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_datetime
	mkdir -p ./output/bin
	cp -f --link test_datetime ./output/bin

test_content_filter:test_content_filter_test_content_filter.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_content_filter[0m']"
	$(CXX) test_content_filter_test_content_filter.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_content_filter
	mkdir -p ./output/bin
	cp -f --link test_content_filter ./output/bin

test_regex:test_regex_test_regex.o \
  ../src/model/test_regex_LinearModel.o \
  ../src/model/test_regex_ModelFactory.o \
  ../src/model/test_regex_Predictor.o \
  ../src/model/test_regex_RandForestModel.o \
  ../src/model/test_regex_Score.o \
  ../src/model/test_regex_SharedPredictor.o \
  ../src/model/test_regex_SvmModel.o \
  ../src/json/test_regex_json_reader.o \
  ../src/json/test_regex_json_value.o \
  ../src/json/test_regex_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_regex[0m']"
	$(CXX) test_regex_test_regex.o \
  ../src/model/test_regex_LinearModel.o \
  ../src/model/test_regex_ModelFactory.o \
  ../src/model/test_regex_Predictor.o \
  ../src/model/test_regex_RandForestModel.o \
  ../src/model/test_regex_Score.o \
  ../src/model/test_regex_SharedPredictor.o \
  ../src/model/test_regex_SvmModel.o \
  ../src/json/test_regex_json_reader.o \
  ../src/json/test_regex_json_value.o \
  ../src/json/test_regex_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_regex
	mkdir -p ./output/bin
	cp -f --link test_regex ./output/bin

test_regex2:test_regex2_test_regex2.o \
  ../src/model/test_regex2_LinearModel.o \
  ../src/model/test_regex2_ModelFactory.o \
  ../src/model/test_regex2_Predictor.o \
  ../src/model/test_regex2_RandForestModel.o \
  ../src/model/test_regex2_Score.o \
  ../src/model/test_regex2_SharedPredictor.o \
  ../src/model/test_regex2_SvmModel.o \
  ../src/json/test_regex2_json_reader.o \
  ../src/json/test_regex2_json_value.o \
  ../src/json/test_regex2_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_regex2[0m']"
	$(CXX) test_regex2_test_regex2.o \
  ../src/model/test_regex2_LinearModel.o \
  ../src/model/test_regex2_ModelFactory.o \
  ../src/model/test_regex2_Predictor.o \
  ../src/model/test_regex2_RandForestModel.o \
  ../src/model/test_regex2_Score.o \
  ../src/model/test_regex2_SharedPredictor.o \
  ../src/model/test_regex2_SvmModel.o \
  ../src/json/test_regex2_json_reader.o \
  ../src/json/test_regex2_json_value.o \
  ../src/json/test_regex2_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_regex2
	mkdir -p ./output/bin
	cp -f --link test_regex2 ./output/bin

test_encode:test_encode_test_encode.o \
  ../src/model/test_encode_LinearModel.o \
  ../src/model/test_encode_ModelFactory.o \
  ../src/model/test_encode_Predictor.o \
  ../src/model/test_encode_RandForestModel.o \
  ../src/model/test_encode_Score.o \
  ../src/model/test_encode_SharedPredictor.o \
  ../src/model/test_encode_SvmModel.o \
  ../src/json/test_encode_json_reader.o \
  ../src/json/test_encode_json_value.o \
  ../src/json/test_encode_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_encode[0m']"
	$(CXX) test_encode_test_encode.o \
  ../src/model/test_encode_LinearModel.o \
  ../src/model/test_encode_ModelFactory.o \
  ../src/model/test_encode_Predictor.o \
  ../src/model/test_encode_RandForestModel.o \
  ../src/model/test_encode_Score.o \
  ../src/model/test_encode_SharedPredictor.o \
  ../src/model/test_encode_SvmModel.o \
  ../src/json/test_encode_json_reader.o \
  ../src/json/test_encode_json_value.o \
  ../src/json/test_encode_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_encode
	mkdir -p ./output/bin
	cp -f --link test_encode ./output/bin

test_json:test_json_test_json.o \
  ../src/model/test_json_LinearModel.o \
  ../src/model/test_json_ModelFactory.o \
  ../src/model/test_json_Predictor.o \
  ../src/model/test_json_RandForestModel.o \
  ../src/model/test_json_Score.o \
  ../src/model/test_json_SharedPredictor.o \
  ../src/model/test_json_SvmModel.o \
  ../src/json/test_json_json_reader.o \
  ../src/json/test_json_json_value.o \
  ../src/json/test_json_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_json[0m']"
	$(CXX) test_json_test_json.o \
  ../src/model/test_json_LinearModel.o \
  ../src/model/test_json_ModelFactory.o \
  ../src/model/test_json_Predictor.o \
  ../src/model/test_json_RandForestModel.o \
  ../src/model/test_json_Score.o \
  ../src/model/test_json_SharedPredictor.o \
  ../src/model/test_json_SvmModel.o \
  ../src/json/test_json_json_reader.o \
  ../src/json/test_json_json_value.o \
  ../src/json/test_json_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_json
	mkdir -p ./output/bin
	cp -f --link test_json ./output/bin

test_escape:test_escape_test_escape.o \
  ../src/model/test_escape_LinearModel.o \
  ../src/model/test_escape_ModelFactory.o \
  ../src/model/test_escape_Predictor.o \
  ../src/model/test_escape_RandForestModel.o \
  ../src/model/test_escape_Score.o \
  ../src/model/test_escape_SharedPredictor.o \
  ../src/model/test_escape_SvmModel.o \
  ../src/json/test_escape_json_reader.o \
  ../src/json/test_escape_json_value.o \
  ../src/json/test_escape_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_escape[0m']"
	$(CXX) test_escape_test_escape.o \
  ../src/model/test_escape_LinearModel.o \
  ../src/model/test_escape_ModelFactory.o \
  ../src/model/test_escape_Predictor.o \
  ../src/model/test_escape_RandForestModel.o \
  ../src/model/test_escape_Score.o \
  ../src/model/test_escape_SharedPredictor.o \
  ../src/model/test_escape_SvmModel.o \
  ../src/json/test_escape_json_reader.o \
  ../src/json/test_escape_json_value.o \
  ../src/json/test_escape_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_escape
	mkdir -p ./output/bin
	cp -f --link test_escape ./output/bin

test_other:test_other_test_other.o \
  ../src/model/test_other_LinearModel.o \
  ../src/model/test_other_ModelFactory.o \
  ../src/model/test_other_Predictor.o \
  ../src/model/test_other_RandForestModel.o \
  ../src/model/test_other_Score.o \
  ../src/model/test_other_SharedPredictor.o \
  ../src/model/test_other_SvmModel.o \
  ../src/json/test_other_json_reader.o \
  ../src/json/test_other_json_value.o \
  ../src/json/test_other_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_other[0m']"
	$(CXX) test_other_test_other.o \
  ../src/model/test_other_LinearModel.o \
  ../src/model/test_other_ModelFactory.o \
  ../src/model/test_other_Predictor.o \
  ../src/model/test_other_RandForestModel.o \
  ../src/model/test_other_Score.o \
  ../src/model/test_other_SharedPredictor.o \
  ../src/model/test_other_SvmModel.o \
  ../src/json/test_other_json_reader.o \
  ../src/json/test_other_json_value.o \
  ../src/json/test_other_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_other
	mkdir -p ./output/bin
	cp -f --link test_other ./output/bin

test_feature_selector:test_feature_selector_test_feature_selector.o \
  ../src/model/test_feature_selector_LinearModel.o \
  ../src/model/test_feature_selector_ModelFactory.o \
  ../src/model/test_feature_selector_Predictor.o \
  ../src/model/test_feature_selector_RandForestModel.o \
  ../src/model/test_feature_selector_Score.o \
  ../src/model/test_feature_selector_SharedPredictor.o \
  ../src/model/test_feature_selector_SvmModel.o \
  ../src/json/test_feature_selector_json_reader.o \
  ../src/json/test_feature_selector_json_value.o \
  ../src/json/test_feature_selector_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_feature_selector[0m']"
	$(CXX) test_feature_selector_test_feature_selector.o \
  ../src/model/test_feature_selector_LinearModel.o \
  ../src/model/test_feature_selector_ModelFactory.o \
  ../src/model/test_feature_selector_Predictor.o \
  ../src/model/test_feature_selector_RandForestModel.o \
  ../src/model/test_feature_selector_Score.o \
  ../src/model/test_feature_selector_SharedPredictor.o \
  ../src/model/test_feature_selector_SvmModel.o \
  ../src/json/test_feature_selector_json_reader.o \
  ../src/json/test_feature_selector_json_value.o \
  ../src/json/test_feature_selector_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_feature_selector
	mkdir -p ./output/bin
	cp -f --link test_feature_selector ./output/bin

openmp_hello:openmp/openmp_hello_hello.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mopenmp_hello[0m']"
	$(CXX) openmp/openmp_hello_hello.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o openmp_hello
	mkdir -p ./bin
	cp -f --link openmp_hello ./bin

openmp_test:openmp/openmp_test_test.o \
  ../src/model/openmp_test_LinearModel.o \
  ../src/model/openmp_test_ModelFactory.o \
  ../src/model/openmp_test_Predictor.o \
  ../src/model/openmp_test_RandForestModel.o \
  ../src/model/openmp_test_Score.o \
  ../src/model/openmp_test_SharedPredictor.o \
  ../src/model/openmp_test_SvmModel.o \
  ../src/json/openmp_test_json_reader.o \
  ../src/json/openmp_test_json_value.o \
  ../src/json/openmp_test_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mopenmp_test[0m']"
	$(CXX) openmp/openmp_test_test.o \
  ../src/model/openmp_test_LinearModel.o \
  ../src/model/openmp_test_ModelFactory.o \
  ../src/model/openmp_test_Predictor.o \
  ../src/model/openmp_test_RandForestModel.o \
  ../src/model/openmp_test_Score.o \
  ../src/model/openmp_test_SharedPredictor.o \
  ../src/model/openmp_test_SvmModel.o \
  ../src/json/openmp_test_json_reader.o \
  ../src/json/openmp_test_json_value.o \
  ../src/json/openmp_test_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o openmp_test
	mkdir -p ./bin
	cp -f --link openmp_test ./bin

test_exception:test_exception_test_exception.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_exception[0m']"
	$(CXX) test_exception_test_exception.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_exception
	mkdir -p ./bin
	cp -f --link test_exception ./bin

test_map_util:test_map_util_test_map_util.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_map_util[0m']"
	$(CXX) test_map_util_test_map_util.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_map_util
	mkdir -p ./bin
	cp -f --link test_map_util ./bin

test_seg:test_seg_test_seg.o \
  ../src/model/test_seg_LinearModel.o \
  ../src/model/test_seg_ModelFactory.o \
  ../src/model/test_seg_Predictor.o \
  ../src/model/test_seg_RandForestModel.o \
  ../src/model/test_seg_Score.o \
  ../src/model/test_seg_SharedPredictor.o \
  ../src/model/test_seg_SvmModel.o \
  ../src/json/test_seg_json_reader.o \
  ../src/json/test_seg_json_value.o \
  ../src/json/test_seg_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_seg[0m']"
	$(CXX) test_seg_test_seg.o \
  ../src/model/test_seg_LinearModel.o \
  ../src/model/test_seg_ModelFactory.o \
  ../src/model/test_seg_Predictor.o \
  ../src/model/test_seg_RandForestModel.o \
  ../src/model/test_seg_Score.o \
  ../src/model/test_seg_SharedPredictor.o \
  ../src/model/test_seg_SvmModel.o \
  ../src/json/test_seg_json_reader.o \
  ../src/json/test_seg_json_value.o \
  ../src/json/test_seg_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_seg
	mkdir -p ./output/bin
	cp -f --link test_seg ./output/bin

test_identifer:test_identifer_test_identifer.o \
  ../src/model/test_identifer_LinearModel.o \
  ../src/model/test_identifer_ModelFactory.o \
  ../src/model/test_identifer_Predictor.o \
  ../src/model/test_identifer_RandForestModel.o \
  ../src/model/test_identifer_Score.o \
  ../src/model/test_identifer_SharedPredictor.o \
  ../src/model/test_identifer_SvmModel.o \
  ../src/json/test_identifer_json_reader.o \
  ../src/json/test_identifer_json_value.o \
  ../src/json/test_identifer_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_identifer[0m']"
	$(CXX) test_identifer_test_identifer.o \
  ../src/model/test_identifer_LinearModel.o \
  ../src/model/test_identifer_ModelFactory.o \
  ../src/model/test_identifer_Predictor.o \
  ../src/model/test_identifer_RandForestModel.o \
  ../src/model/test_identifer_Score.o \
  ../src/model/test_identifer_SharedPredictor.o \
  ../src/model/test_identifer_SvmModel.o \
  ../src/json/test_identifer_json_reader.o \
  ../src/json/test_identifer_json_value.o \
  ../src/json/test_identifer_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_identifer
	mkdir -p ./output/bin
	cp -f --link test_identifer ./output/bin

test_linear:test_linear_test_linear.o \
  ../src/model/test_linear_LinearModel.o \
  ../src/model/test_linear_ModelFactory.o \
  ../src/model/test_linear_Predictor.o \
  ../src/model/test_linear_RandForestModel.o \
  ../src/model/test_linear_Score.o \
  ../src/model/test_linear_SharedPredictor.o \
  ../src/model/test_linear_SvmModel.o \
  ../src/json/test_linear_json_reader.o \
  ../src/json/test_linear_json_value.o \
  ../src/json/test_linear_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_linear[0m']"
	$(CXX) test_linear_test_linear.o \
  ../src/model/test_linear_LinearModel.o \
  ../src/model/test_linear_ModelFactory.o \
  ../src/model/test_linear_Predictor.o \
  ../src/model/test_linear_RandForestModel.o \
  ../src/model/test_linear_Score.o \
  ../src/model/test_linear_SharedPredictor.o \
  ../src/model/test_linear_SvmModel.o \
  ../src/json/test_linear_json_reader.o \
  ../src/json/test_linear_json_value.o \
  ../src/json/test_linear_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_linear
	mkdir -p ./output/bin
	cp -f --link test_linear ./output/bin

test_pinyin:test_pinyin_test_pinyin.o \
  ../src/model/test_pinyin_LinearModel.o \
  ../src/model/test_pinyin_ModelFactory.o \
  ../src/model/test_pinyin_Predictor.o \
  ../src/model/test_pinyin_RandForestModel.o \
  ../src/model/test_pinyin_Score.o \
  ../src/model/test_pinyin_SharedPredictor.o \
  ../src/model/test_pinyin_SvmModel.o \
  ../src/json/test_pinyin_json_reader.o \
  ../src/json/test_pinyin_json_value.o \
  ../src/json/test_pinyin_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_pinyin[0m']"
	$(CXX) test_pinyin_test_pinyin.o \
  ../src/model/test_pinyin_LinearModel.o \
  ../src/model/test_pinyin_ModelFactory.o \
  ../src/model/test_pinyin_Predictor.o \
  ../src/model/test_pinyin_RandForestModel.o \
  ../src/model/test_pinyin_Score.o \
  ../src/model/test_pinyin_SharedPredictor.o \
  ../src/model/test_pinyin_SvmModel.o \
  ../src/json/test_pinyin_json_reader.o \
  ../src/json/test_pinyin_json_value.o \
  ../src/json/test_pinyin_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_pinyin
	mkdir -p ./output/bin
	cp -f --link test_pinyin ./output/bin

test_namepattern:test_namepattern_test_namepattern.o \
  ../src/model/test_namepattern_LinearModel.o \
  ../src/model/test_namepattern_ModelFactory.o \
  ../src/model/test_namepattern_Predictor.o \
  ../src/model/test_namepattern_RandForestModel.o \
  ../src/model/test_namepattern_Score.o \
  ../src/model/test_namepattern_SharedPredictor.o \
  ../src/model/test_namepattern_SvmModel.o \
  ../src/json/test_namepattern_json_reader.o \
  ../src/json/test_namepattern_json_value.o \
  ../src/json/test_namepattern_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_namepattern[0m']"
	$(CXX) test_namepattern_test_namepattern.o \
  ../src/model/test_namepattern_LinearModel.o \
  ../src/model/test_namepattern_ModelFactory.o \
  ../src/model/test_namepattern_Predictor.o \
  ../src/model/test_namepattern_RandForestModel.o \
  ../src/model/test_namepattern_Score.o \
  ../src/model/test_namepattern_SharedPredictor.o \
  ../src/model/test_namepattern_SvmModel.o \
  ../src/json/test_namepattern_json_reader.o \
  ../src/json/test_namepattern_json_value.o \
  ../src/json/test_namepattern_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_namepattern
	mkdir -p ./output/bin
	cp -f --link test_namepattern ./output/bin

test_conf:test_conf_test_conf.o \
  ../src/model/test_conf_LinearModel.o \
  ../src/model/test_conf_ModelFactory.o \
  ../src/model/test_conf_Predictor.o \
  ../src/model/test_conf_RandForestModel.o \
  ../src/model/test_conf_Score.o \
  ../src/model/test_conf_SharedPredictor.o \
  ../src/model/test_conf_SvmModel.o \
  ../src/json/test_conf_json_reader.o \
  ../src/json/test_conf_json_value.o \
  ../src/json/test_conf_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_conf[0m']"
	$(CXX) test_conf_test_conf.o \
  ../src/model/test_conf_LinearModel.o \
  ../src/model/test_conf_ModelFactory.o \
  ../src/model/test_conf_Predictor.o \
  ../src/model/test_conf_RandForestModel.o \
  ../src/model/test_conf_Score.o \
  ../src/model/test_conf_SharedPredictor.o \
  ../src/model/test_conf_SvmModel.o \
  ../src/json/test_conf_json_reader.o \
  ../src/json/test_conf_json_value.o \
  ../src/json/test_conf_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_conf
	mkdir -p ./output/bin
	cp -f --link test_conf ./output/bin

test_random:test_random_test_random.o \
  ../src/model/test_random_LinearModel.o \
  ../src/model/test_random_ModelFactory.o \
  ../src/model/test_random_Predictor.o \
  ../src/model/test_random_RandForestModel.o \
  ../src/model/test_random_Score.o \
  ../src/model/test_random_SharedPredictor.o \
  ../src/model/test_random_SvmModel.o \
  ../src/json/test_random_json_reader.o \
  ../src/json/test_random_json_value.o \
  ../src/json/test_random_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_random[0m']"
	$(CXX) test_random_test_random.o \
  ../src/model/test_random_LinearModel.o \
  ../src/model/test_random_ModelFactory.o \
  ../src/model/test_random_Predictor.o \
  ../src/model/test_random_RandForestModel.o \
  ../src/model/test_random_Score.o \
  ../src/model/test_random_SharedPredictor.o \
  ../src/model/test_random_SvmModel.o \
  ../src/json/test_random_json_reader.o \
  ../src/json/test_random_json_value.o \
  ../src/json/test_random_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_random
	mkdir -p ./output/bin
	cp -f --link test_random ./output/bin

test_shared_ptr:test_shared_ptr_test_shared_ptr.o \
  ../src/model/test_shared_ptr_LinearModel.o \
  ../src/model/test_shared_ptr_ModelFactory.o \
  ../src/model/test_shared_ptr_Predictor.o \
  ../src/model/test_shared_ptr_RandForestModel.o \
  ../src/model/test_shared_ptr_Score.o \
  ../src/model/test_shared_ptr_SharedPredictor.o \
  ../src/model/test_shared_ptr_SvmModel.o \
  ../src/json/test_shared_ptr_json_reader.o \
  ../src/json/test_shared_ptr_json_value.o \
  ../src/json/test_shared_ptr_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_shared_ptr[0m']"
	$(CXX) test_shared_ptr_test_shared_ptr.o \
  ../src/model/test_shared_ptr_LinearModel.o \
  ../src/model/test_shared_ptr_ModelFactory.o \
  ../src/model/test_shared_ptr_Predictor.o \
  ../src/model/test_shared_ptr_RandForestModel.o \
  ../src/model/test_shared_ptr_Score.o \
  ../src/model/test_shared_ptr_SharedPredictor.o \
  ../src/model/test_shared_ptr_SvmModel.o \
  ../src/json/test_shared_ptr_json_reader.o \
  ../src/json/test_shared_ptr_json_value.o \
  ../src/json/test_shared_ptr_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_shared_ptr
	mkdir -p ./output/bin
	cp -f --link test_shared_ptr ./output/bin

test_binfinder:test_binfinder_test_binfinder.o \
  ../src/model/test_binfinder_LinearModel.o \
  ../src/model/test_binfinder_ModelFactory.o \
  ../src/model/test_binfinder_Predictor.o \
  ../src/model/test_binfinder_RandForestModel.o \
  ../src/model/test_binfinder_Score.o \
  ../src/model/test_binfinder_SharedPredictor.o \
  ../src/model/test_binfinder_SvmModel.o \
  ../src/json/test_binfinder_json_reader.o \
  ../src/json/test_binfinder_json_value.o \
  ../src/json/test_binfinder_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_binfinder[0m']"
	$(CXX) test_binfinder_test_binfinder.o \
  ../src/model/test_binfinder_LinearModel.o \
  ../src/model/test_binfinder_ModelFactory.o \
  ../src/model/test_binfinder_Predictor.o \
  ../src/model/test_binfinder_RandForestModel.o \
  ../src/model/test_binfinder_Score.o \
  ../src/model/test_binfinder_SharedPredictor.o \
  ../src/model/test_binfinder_SvmModel.o \
  ../src/json/test_binfinder_json_reader.o \
  ../src/json/test_binfinder_json_value.o \
  ../src/json/test_binfinder_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_binfinder
	mkdir -p ./output/bin
	cp -f --link test_binfinder ./output/bin

test_seralize:test_seralize_test_seralize.o \
  ../src/model/test_seralize_LinearModel.o \
  ../src/model/test_seralize_ModelFactory.o \
  ../src/model/test_seralize_Predictor.o \
  ../src/model/test_seralize_RandForestModel.o \
  ../src/model/test_seralize_Score.o \
  ../src/model/test_seralize_SharedPredictor.o \
  ../src/model/test_seralize_SvmModel.o \
  ../src/json/test_seralize_json_reader.o \
  ../src/json/test_seralize_json_value.o \
  ../src/json/test_seralize_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_seralize[0m']"
	$(CXX) test_seralize_test_seralize.o \
  ../src/model/test_seralize_LinearModel.o \
  ../src/model/test_seralize_ModelFactory.o \
  ../src/model/test_seralize_Predictor.o \
  ../src/model/test_seralize_RandForestModel.o \
  ../src/model/test_seralize_Score.o \
  ../src/model/test_seralize_SharedPredictor.o \
  ../src/model/test_seralize_SvmModel.o \
  ../src/json/test_seralize_json_reader.o \
  ../src/json/test_seralize_json_value.o \
  ../src/json/test_seralize_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_seralize
	mkdir -p ./output/bin
	cp -f --link test_seralize ./output/bin

test_string:test_string_test_string.o \
  ../src/model/test_string_LinearModel.o \
  ../src/model/test_string_ModelFactory.o \
  ../src/model/test_string_Predictor.o \
  ../src/model/test_string_RandForestModel.o \
  ../src/model/test_string_Score.o \
  ../src/model/test_string_SharedPredictor.o \
  ../src/model/test_string_SvmModel.o \
  ../src/json/test_string_json_reader.o \
  ../src/json/test_string_json_value.o \
  ../src/json/test_string_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_string[0m']"
	$(CXX) test_string_test_string.o \
  ../src/model/test_string_LinearModel.o \
  ../src/model/test_string_ModelFactory.o \
  ../src/model/test_string_Predictor.o \
  ../src/model/test_string_RandForestModel.o \
  ../src/model/test_string_Score.o \
  ../src/model/test_string_SharedPredictor.o \
  ../src/model/test_string_SvmModel.o \
  ../src/json/test_string_json_reader.o \
  ../src/json/test_string_json_value.o \
  ../src/json/test_string_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_string
	mkdir -p ./output/bin
	cp -f --link test_string ./output/bin

test_bitop:test_bitop_test_bitop.o \
  ../src/model/test_bitop_LinearModel.o \
  ../src/model/test_bitop_ModelFactory.o \
  ../src/model/test_bitop_Predictor.o \
  ../src/model/test_bitop_RandForestModel.o \
  ../src/model/test_bitop_Score.o \
  ../src/model/test_bitop_SharedPredictor.o \
  ../src/model/test_bitop_SvmModel.o \
  ../src/json/test_bitop_json_reader.o \
  ../src/json/test_bitop_json_value.o \
  ../src/json/test_bitop_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_bitop[0m']"
	$(CXX) test_bitop_test_bitop.o \
  ../src/model/test_bitop_LinearModel.o \
  ../src/model/test_bitop_ModelFactory.o \
  ../src/model/test_bitop_Predictor.o \
  ../src/model/test_bitop_RandForestModel.o \
  ../src/model/test_bitop_Score.o \
  ../src/model/test_bitop_SharedPredictor.o \
  ../src/model/test_bitop_SvmModel.o \
  ../src/json/test_bitop_json_reader.o \
  ../src/json/test_bitop_json_value.o \
  ../src/json/test_bitop_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_bitop
	mkdir -p ./output/bin
	cp -f --link test_bitop ./output/bin

test_featurevector:test_featurevector_test_featurevector.o \
  ../src/model/test_featurevector_LinearModel.o \
  ../src/model/test_featurevector_ModelFactory.o \
  ../src/model/test_featurevector_Predictor.o \
  ../src/model/test_featurevector_RandForestModel.o \
  ../src/model/test_featurevector_Score.o \
  ../src/model/test_featurevector_SharedPredictor.o \
  ../src/model/test_featurevector_SvmModel.o \
  ../src/json/test_featurevector_json_reader.o \
  ../src/json/test_featurevector_json_value.o \
  ../src/json/test_featurevector_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_featurevector[0m']"
	$(CXX) test_featurevector_test_featurevector.o \
  ../src/model/test_featurevector_LinearModel.o \
  ../src/model/test_featurevector_ModelFactory.o \
  ../src/model/test_featurevector_Predictor.o \
  ../src/model/test_featurevector_RandForestModel.o \
  ../src/model/test_featurevector_Score.o \
  ../src/model/test_featurevector_SharedPredictor.o \
  ../src/model/test_featurevector_SvmModel.o \
  ../src/json/test_featurevector_json_reader.o \
  ../src/json/test_featurevector_json_value.o \
  ../src/json/test_featurevector_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_featurevector
	mkdir -p ./output/bin
	cp -f --link test_featurevector ./output/bin

test_split:test_split_test_split.o \
  ../src/model/test_split_LinearModel.o \
  ../src/model/test_split_ModelFactory.o \
  ../src/model/test_split_Predictor.o \
  ../src/model/test_split_RandForestModel.o \
  ../src/model/test_split_Score.o \
  ../src/model/test_split_SharedPredictor.o \
  ../src/model/test_split_SvmModel.o \
  ../src/json/test_split_json_reader.o \
  ../src/json/test_split_json_value.o \
  ../src/json/test_split_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_split[0m']"
	$(CXX) test_split_test_split.o \
  ../src/model/test_split_LinearModel.o \
  ../src/model/test_split_ModelFactory.o \
  ../src/model/test_split_Predictor.o \
  ../src/model/test_split_RandForestModel.o \
  ../src/model/test_split_Score.o \
  ../src/model/test_split_SharedPredictor.o \
  ../src/model/test_split_SvmModel.o \
  ../src/json/test_split_json_reader.o \
  ../src/json/test_split_json_value.o \
  ../src/json/test_split_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_split
	mkdir -p ./output/bin
	cp -f --link test_split ./output/bin

test_tieba_get_info:test_tieba_get_info_test_tieba_get_info.o \
  ../src/model/test_tieba_get_info_LinearModel.o \
  ../src/model/test_tieba_get_info_ModelFactory.o \
  ../src/model/test_tieba_get_info_Predictor.o \
  ../src/model/test_tieba_get_info_RandForestModel.o \
  ../src/model/test_tieba_get_info_Score.o \
  ../src/model/test_tieba_get_info_SharedPredictor.o \
  ../src/model/test_tieba_get_info_SvmModel.o \
  ../src/json/test_tieba_get_info_json_reader.o \
  ../src/json/test_tieba_get_info_json_value.o \
  ../src/json/test_tieba_get_info_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_tieba_get_info[0m']"
	$(CXX) test_tieba_get_info_test_tieba_get_info.o \
  ../src/model/test_tieba_get_info_LinearModel.o \
  ../src/model/test_tieba_get_info_ModelFactory.o \
  ../src/model/test_tieba_get_info_Predictor.o \
  ../src/model/test_tieba_get_info_RandForestModel.o \
  ../src/model/test_tieba_get_info_Score.o \
  ../src/model/test_tieba_get_info_SharedPredictor.o \
  ../src/model/test_tieba_get_info_SvmModel.o \
  ../src/json/test_tieba_get_info_json_reader.o \
  ../src/json/test_tieba_get_info_json_value.o \
  ../src/json/test_tieba_get_info_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_tieba_get_info
	mkdir -p ./output/bin
	cp -f --link test_tieba_get_info ./output/bin

test_content_process:test_content_process_test_content_process.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_content_process[0m']"
	$(CXX) test_content_process_test_content_process.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_content_process
	mkdir -p ./output/bin
	cp -f --link test_content_process ./output/bin

test_cached_fetcher:test_cached_fetcher_test_cached_fetcher.o \
  ../src/model/test_cached_fetcher_LinearModel.o \
  ../src/model/test_cached_fetcher_ModelFactory.o \
  ../src/model/test_cached_fetcher_Predictor.o \
  ../src/model/test_cached_fetcher_RandForestModel.o \
  ../src/model/test_cached_fetcher_Score.o \
  ../src/model/test_cached_fetcher_SharedPredictor.o \
  ../src/model/test_cached_fetcher_SvmModel.o \
  ../src/json/test_cached_fetcher_json_reader.o \
  ../src/json/test_cached_fetcher_json_value.o \
  ../src/json/test_cached_fetcher_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_cached_fetcher[0m']"
	$(CXX) test_cached_fetcher_test_cached_fetcher.o \
  ../src/model/test_cached_fetcher_LinearModel.o \
  ../src/model/test_cached_fetcher_ModelFactory.o \
  ../src/model/test_cached_fetcher_Predictor.o \
  ../src/model/test_cached_fetcher_RandForestModel.o \
  ../src/model/test_cached_fetcher_Score.o \
  ../src/model/test_cached_fetcher_SharedPredictor.o \
  ../src/model/test_cached_fetcher_SvmModel.o \
  ../src/json/test_cached_fetcher_json_reader.o \
  ../src/json/test_cached_fetcher_json_value.o \
  ../src/json/test_cached_fetcher_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_cached_fetcher
	mkdir -p ./output/bin
	cp -f --link test_cached_fetcher ./output/bin

test_bind:test_bind_test_bind.o \
  ../src/model/test_bind_LinearModel.o \
  ../src/model/test_bind_ModelFactory.o \
  ../src/model/test_bind_Predictor.o \
  ../src/model/test_bind_RandForestModel.o \
  ../src/model/test_bind_Score.o \
  ../src/model/test_bind_SharedPredictor.o \
  ../src/model/test_bind_SvmModel.o \
  ../src/json/test_bind_json_reader.o \
  ../src/json/test_bind_json_value.o \
  ../src/json/test_bind_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_bind[0m']"
	$(CXX) test_bind_test_bind.o \
  ../src/model/test_bind_LinearModel.o \
  ../src/model/test_bind_ModelFactory.o \
  ../src/model/test_bind_Predictor.o \
  ../src/model/test_bind_RandForestModel.o \
  ../src/model/test_bind_Score.o \
  ../src/model/test_bind_SharedPredictor.o \
  ../src/model/test_bind_SvmModel.o \
  ../src/json/test_bind_json_reader.o \
  ../src/json/test_bind_json_value.o \
  ../src/json/test_bind_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_bind
	mkdir -p ./output/bin
	cp -f --link test_bind ./output/bin

test_lrumap:test_lrumap_test_lrumap.o \
  ../src/model/test_lrumap_LinearModel.o \
  ../src/model/test_lrumap_ModelFactory.o \
  ../src/model/test_lrumap_Predictor.o \
  ../src/model/test_lrumap_RandForestModel.o \
  ../src/model/test_lrumap_Score.o \
  ../src/model/test_lrumap_SharedPredictor.o \
  ../src/model/test_lrumap_SvmModel.o \
  ../src/json/test_lrumap_json_reader.o \
  ../src/json/test_lrumap_json_value.o \
  ../src/json/test_lrumap_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_lrumap[0m']"
	$(CXX) test_lrumap_test_lrumap.o \
  ../src/model/test_lrumap_LinearModel.o \
  ../src/model/test_lrumap_ModelFactory.o \
  ../src/model/test_lrumap_Predictor.o \
  ../src/model/test_lrumap_RandForestModel.o \
  ../src/model/test_lrumap_Score.o \
  ../src/model/test_lrumap_SharedPredictor.o \
  ../src/model/test_lrumap_SvmModel.o \
  ../src/json/test_lrumap_json_reader.o \
  ../src/json/test_lrumap_json_value.o \
  ../src/json/test_lrumap_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_lrumap
	mkdir -p ./output/bin
	cp -f --link test_lrumap ./output/bin

test_seralize_xml:test_seralize_xml_test_seralize_xml.o \
  ../src/model/test_seralize_xml_LinearModel.o \
  ../src/model/test_seralize_xml_ModelFactory.o \
  ../src/model/test_seralize_xml_Predictor.o \
  ../src/model/test_seralize_xml_RandForestModel.o \
  ../src/model/test_seralize_xml_Score.o \
  ../src/model/test_seralize_xml_SharedPredictor.o \
  ../src/model/test_seralize_xml_SvmModel.o \
  ../src/json/test_seralize_xml_json_reader.o \
  ../src/json/test_seralize_xml_json_value.o \
  ../src/json/test_seralize_xml_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_seralize_xml[0m']"
	$(CXX) test_seralize_xml_test_seralize_xml.o \
  ../src/model/test_seralize_xml_LinearModel.o \
  ../src/model/test_seralize_xml_ModelFactory.o \
  ../src/model/test_seralize_xml_Predictor.o \
  ../src/model/test_seralize_xml_RandForestModel.o \
  ../src/model/test_seralize_xml_Score.o \
  ../src/model/test_seralize_xml_SharedPredictor.o \
  ../src/model/test_seralize_xml_SvmModel.o \
  ../src/json/test_seralize_xml_json_reader.o \
  ../src/json/test_seralize_xml_json_value.o \
  ../src/json/test_seralize_xml_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_seralize_xml
	mkdir -p ./output/bin
	cp -f --link test_seralize_xml ./output/bin

test_thread_local:test_thread_local_test_thread_local.o \
  ../src/model/test_thread_local_LinearModel.o \
  ../src/model/test_thread_local_ModelFactory.o \
  ../src/model/test_thread_local_Predictor.o \
  ../src/model/test_thread_local_RandForestModel.o \
  ../src/model/test_thread_local_Score.o \
  ../src/model/test_thread_local_SharedPredictor.o \
  ../src/model/test_thread_local_SvmModel.o \
  ../src/json/test_thread_local_json_reader.o \
  ../src/json/test_thread_local_json_value.o \
  ../src/json/test_thread_local_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_thread_local[0m']"
	$(CXX) test_thread_local_test_thread_local.o \
  ../src/model/test_thread_local_LinearModel.o \
  ../src/model/test_thread_local_ModelFactory.o \
  ../src/model/test_thread_local_Predictor.o \
  ../src/model/test_thread_local_RandForestModel.o \
  ../src/model/test_thread_local_Score.o \
  ../src/model/test_thread_local_SharedPredictor.o \
  ../src/model/test_thread_local_SvmModel.o \
  ../src/json/test_thread_local_json_reader.o \
  ../src/json/test_thread_local_json_value.o \
  ../src/json/test_thread_local_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_thread_local
	mkdir -p ./output/bin
	cp -f --link test_thread_local ./output/bin

test_configure:test_configure_test_configure.o \
  ../src/model/test_configure_LinearModel.o \
  ../src/model/test_configure_ModelFactory.o \
  ../src/model/test_configure_Predictor.o \
  ../src/model/test_configure_RandForestModel.o \
  ../src/model/test_configure_Score.o \
  ../src/model/test_configure_SharedPredictor.o \
  ../src/model/test_configure_SvmModel.o \
  ../src/json/test_configure_json_reader.o \
  ../src/json/test_configure_json_value.o \
  ../src/json/test_configure_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_configure[0m']"
	$(CXX) test_configure_test_configure.o \
  ../src/model/test_configure_LinearModel.o \
  ../src/model/test_configure_ModelFactory.o \
  ../src/model/test_configure_Predictor.o \
  ../src/model/test_configure_RandForestModel.o \
  ../src/model/test_configure_Score.o \
  ../src/model/test_configure_SharedPredictor.o \
  ../src/model/test_configure_SvmModel.o \
  ../src/json/test_configure_json_reader.o \
  ../src/json/test_configure_json_value.o \
  ../src/json/test_configure_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_configure
	mkdir -p ./output/bin
	cp -f --link test_configure ./output/bin

test_static:test_static_test_static.o \
  ../src/model/test_static_LinearModel.o \
  ../src/model/test_static_ModelFactory.o \
  ../src/model/test_static_Predictor.o \
  ../src/model/test_static_RandForestModel.o \
  ../src/model/test_static_Score.o \
  ../src/model/test_static_SharedPredictor.o \
  ../src/model/test_static_SvmModel.o \
  ../src/json/test_static_json_reader.o \
  ../src/json/test_static_json_value.o \
  ../src/json/test_static_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_static[0m']"
	$(CXX) test_static_test_static.o \
  ../src/model/test_static_LinearModel.o \
  ../src/model/test_static_ModelFactory.o \
  ../src/model/test_static_Predictor.o \
  ../src/model/test_static_RandForestModel.o \
  ../src/model/test_static_Score.o \
  ../src/model/test_static_SharedPredictor.o \
  ../src/model/test_static_SvmModel.o \
  ../src/json/test_static_json_reader.o \
  ../src/json/test_static_json_value.o \
  ../src/json/test_static_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_static
	mkdir -p ./output/bin
	cp -f --link test_static ./output/bin

test_cpplinq:test_cpplinq_test_cpplinq.o \
  ../src/model/test_cpplinq_LinearModel.o \
  ../src/model/test_cpplinq_ModelFactory.o \
  ../src/model/test_cpplinq_Predictor.o \
  ../src/model/test_cpplinq_RandForestModel.o \
  ../src/model/test_cpplinq_Score.o \
  ../src/model/test_cpplinq_SharedPredictor.o \
  ../src/model/test_cpplinq_SvmModel.o \
  ../src/json/test_cpplinq_json_reader.o \
  ../src/json/test_cpplinq_json_value.o \
  ../src/json/test_cpplinq_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_cpplinq[0m']"
	$(CXX) test_cpplinq_test_cpplinq.o \
  ../src/model/test_cpplinq_LinearModel.o \
  ../src/model/test_cpplinq_ModelFactory.o \
  ../src/model/test_cpplinq_Predictor.o \
  ../src/model/test_cpplinq_RandForestModel.o \
  ../src/model/test_cpplinq_Score.o \
  ../src/model/test_cpplinq_SharedPredictor.o \
  ../src/model/test_cpplinq_SvmModel.o \
  ../src/json/test_cpplinq_json_reader.o \
  ../src/json/test_cpplinq_json_value.o \
  ../src/json/test_cpplinq_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_cpplinq
	mkdir -p ./output/bin
	cp -f --link test_cpplinq ./output/bin

test_partial_sort:test_partial_sort_test_partial_sort.o \
  ../src/model/test_partial_sort_LinearModel.o \
  ../src/model/test_partial_sort_ModelFactory.o \
  ../src/model/test_partial_sort_Predictor.o \
  ../src/model/test_partial_sort_RandForestModel.o \
  ../src/model/test_partial_sort_Score.o \
  ../src/model/test_partial_sort_SharedPredictor.o \
  ../src/model/test_partial_sort_SvmModel.o \
  ../src/json/test_partial_sort_json_reader.o \
  ../src/json/test_partial_sort_json_value.o \
  ../src/json/test_partial_sort_json_writer.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_partial_sort[0m']"
	$(CXX) test_partial_sort_test_partial_sort.o \
  ../src/model/test_partial_sort_LinearModel.o \
  ../src/model/test_partial_sort_ModelFactory.o \
  ../src/model/test_partial_sort_Predictor.o \
  ../src/model/test_partial_sort_RandForestModel.o \
  ../src/model/test_partial_sort_Score.o \
  ../src/model/test_partial_sort_SharedPredictor.o \
  ../src/model/test_partial_sort_SvmModel.o \
  ../src/json/test_partial_sort_json_reader.o \
  ../src/json/test_partial_sort_json_value.o \
  ../src/json/test_partial_sort_json_writer.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_partial_sort
	mkdir -p ./output/bin
	cp -f --link test_partial_sort ./output/bin

test_string_util:test_string_util_test_string_util.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_string_util[0m']"
	$(CXX) test_string_util_test_string_util.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_string_util
	mkdir -p ./output/bin
	cp -f --link test_string_util ./output/bin

test_mean_var:test_mean_var_test_mean_var.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_mean_var[0m']"
	$(CXX) test_mean_var_test_mean_var.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_mean_var
	mkdir -p ./output/bin
	cp -f --link test_mean_var ./output/bin

test_const:test_const_test_const.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_const[0m']"
	$(CXX) test_const_test_const.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_const
	mkdir -p ./output/bin
	cp -f --link test_const ./output/bin

test_matchdict:test_matchdict.h \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_matchdict[0m']"
	$(CXX) test_matchdict.h -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_matchdict
	mkdir -p ./output/bin
	cp -f --link test_matchdict ./output/bin

test_sharedobjects:test_sharedobjects_test_sharedobjects.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_sharedobjects[0m']"
	$(CXX) test_sharedobjects_test_sharedobjects.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_sharedobjects
	mkdir -p ./output/bin
	cp -f --link test_sharedobjects ./output/bin

test_matchdict:test_matchdict_test_matchdict.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_matchdict[0m']"
	$(CXX) test_matchdict_test_matchdict.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_matchdict
	mkdir -p ./output/bin
	cp -f --link test_matchdict ./output/bin

test_erase:test_erase_test_erase.o \
  ../include/tools/pinyin/libPYNotation.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_erase[0m']"
	$(CXX) test_erase_test_erase.o -Xlinker "-(" ../include/tools/pinyin/libPYNotation.a ../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../public/configure/libconfig.a \
  ../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../public/odict/libodict.a \
  ../../../../../../public/spreg/libspreg.a \
  ../../../../../../public/uconv/libuconv.a \
  ../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -rdynamic \
  -lrt \
  -lldap \
  -lcurl \
  -static-libgcc \
  -static-libstdc++ -Xlinker "-)" -o test_erase
	mkdir -p ./output/bin
	cp -f --link test_erase ./output/bin

test_lambda_test_lambda.o:test_lambda.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_lambda_test_lambda.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_lambda_test_lambda.o test_lambda.cc

test_bins_test_bins.o:test_bins.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_bins_test_bins.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_bins_test_bins.o test_bins.cc

test_datetime_test_datetime.o:test_datetime.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_datetime_test_datetime.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_datetime_test_datetime.o test_datetime.cc

test_content_filter_test_content_filter.o:test_content_filter.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_content_filter_test_content_filter.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_content_filter_test_content_filter.o test_content_filter.cc

test_regex_test_regex.o:test_regex.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_regex_test_regex.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_regex_test_regex.o test_regex.cc

../src/model/test_regex_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_regex_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_regex_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex_Predictor.o ../src/model/Predictor.cpp

../src/model/test_regex_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_regex_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex_Score.o ../src/model/Score.cpp

../src/model/test_regex_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_regex_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_regex_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_regex_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_regex_json_reader.o ../src/json/json_reader.cpp

../src/json/test_regex_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_regex_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_regex_json_value.o ../src/json/json_value.cpp

../src/json/test_regex_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_regex_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_regex_json_writer.o ../src/json/json_writer.cpp

test_regex2_test_regex2.o:test_regex2.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_regex2_test_regex2.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_regex2_test_regex2.o test_regex2.cc

../src/model/test_regex2_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex2_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex2_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_regex2_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex2_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex2_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_regex2_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex2_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex2_Predictor.o ../src/model/Predictor.cpp

../src/model/test_regex2_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex2_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex2_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_regex2_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex2_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex2_Score.o ../src/model/Score.cpp

../src/model/test_regex2_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex2_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex2_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_regex2_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_regex2_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_regex2_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_regex2_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_regex2_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_regex2_json_reader.o ../src/json/json_reader.cpp

../src/json/test_regex2_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_regex2_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_regex2_json_value.o ../src/json/json_value.cpp

../src/json/test_regex2_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_regex2_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_regex2_json_writer.o ../src/json/json_writer.cpp

test_encode_test_encode.o:test_encode.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_encode_test_encode.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_encode_test_encode.o test_encode.cc

../src/model/test_encode_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_encode_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_encode_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_encode_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_encode_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_encode_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_encode_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_encode_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_encode_Predictor.o ../src/model/Predictor.cpp

../src/model/test_encode_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_encode_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_encode_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_encode_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_encode_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_encode_Score.o ../src/model/Score.cpp

../src/model/test_encode_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_encode_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_encode_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_encode_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_encode_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_encode_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_encode_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_encode_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_encode_json_reader.o ../src/json/json_reader.cpp

../src/json/test_encode_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_encode_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_encode_json_value.o ../src/json/json_value.cpp

../src/json/test_encode_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_encode_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_encode_json_writer.o ../src/json/json_writer.cpp

test_json_test_json.o:test_json.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_json_test_json.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_json_test_json.o test_json.cc

../src/model/test_json_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_json_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_json_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_json_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_json_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_json_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_json_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_json_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_json_Predictor.o ../src/model/Predictor.cpp

../src/model/test_json_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_json_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_json_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_json_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_json_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_json_Score.o ../src/model/Score.cpp

../src/model/test_json_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_json_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_json_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_json_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_json_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_json_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_json_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_json_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_json_json_reader.o ../src/json/json_reader.cpp

../src/json/test_json_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_json_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_json_json_value.o ../src/json/json_value.cpp

../src/json/test_json_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_json_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_json_json_writer.o ../src/json/json_writer.cpp

test_escape_test_escape.o:test_escape.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_escape_test_escape.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_escape_test_escape.o test_escape.cc

../src/model/test_escape_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_escape_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_escape_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_escape_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_escape_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_escape_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_escape_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_escape_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_escape_Predictor.o ../src/model/Predictor.cpp

../src/model/test_escape_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_escape_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_escape_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_escape_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_escape_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_escape_Score.o ../src/model/Score.cpp

../src/model/test_escape_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_escape_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_escape_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_escape_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_escape_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_escape_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_escape_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_escape_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_escape_json_reader.o ../src/json/json_reader.cpp

../src/json/test_escape_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_escape_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_escape_json_value.o ../src/json/json_value.cpp

../src/json/test_escape_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_escape_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_escape_json_writer.o ../src/json/json_writer.cpp

test_other_test_other.o:test_other.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_other_test_other.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_other_test_other.o test_other.cc

../src/model/test_other_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_other_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_other_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_other_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_other_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_other_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_other_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_other_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_other_Predictor.o ../src/model/Predictor.cpp

../src/model/test_other_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_other_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_other_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_other_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_other_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_other_Score.o ../src/model/Score.cpp

../src/model/test_other_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_other_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_other_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_other_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_other_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_other_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_other_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_other_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_other_json_reader.o ../src/json/json_reader.cpp

../src/json/test_other_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_other_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_other_json_value.o ../src/json/json_value.cpp

../src/json/test_other_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_other_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_other_json_writer.o ../src/json/json_writer.cpp

test_feature_selector_test_feature_selector.o:test_feature_selector.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_feature_selector_test_feature_selector.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_feature_selector_test_feature_selector.o test_feature_selector.cc

../src/model/test_feature_selector_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_feature_selector_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_feature_selector_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_feature_selector_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_feature_selector_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_feature_selector_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_feature_selector_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_feature_selector_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_feature_selector_Predictor.o ../src/model/Predictor.cpp

../src/model/test_feature_selector_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_feature_selector_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_feature_selector_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_feature_selector_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_feature_selector_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_feature_selector_Score.o ../src/model/Score.cpp

../src/model/test_feature_selector_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_feature_selector_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_feature_selector_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_feature_selector_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_feature_selector_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_feature_selector_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_feature_selector_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_feature_selector_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_feature_selector_json_reader.o ../src/json/json_reader.cpp

../src/json/test_feature_selector_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_feature_selector_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_feature_selector_json_value.o ../src/json/json_value.cpp

../src/json/test_feature_selector_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_feature_selector_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_feature_selector_json_writer.o ../src/json/json_writer.cpp

openmp/openmp_hello_hello.o:openmp/hello.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mopenmp/openmp_hello_hello.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o openmp/openmp_hello_hello.o openmp/hello.cc

openmp/openmp_test_test.o:openmp/test.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mopenmp/openmp_test_test.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o openmp/openmp_test_test.o openmp/test.cc

../src/model/openmp_test_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/openmp_test_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/openmp_test_LinearModel.o ../src/model/LinearModel.cpp

../src/model/openmp_test_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/openmp_test_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/openmp_test_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/openmp_test_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/openmp_test_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/openmp_test_Predictor.o ../src/model/Predictor.cpp

../src/model/openmp_test_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/openmp_test_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/openmp_test_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/openmp_test_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/openmp_test_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/openmp_test_Score.o ../src/model/Score.cpp

../src/model/openmp_test_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/openmp_test_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/openmp_test_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/openmp_test_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/openmp_test_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/openmp_test_SvmModel.o ../src/model/SvmModel.cpp

../src/json/openmp_test_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/openmp_test_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/openmp_test_json_reader.o ../src/json/json_reader.cpp

../src/json/openmp_test_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/openmp_test_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/openmp_test_json_value.o ../src/json/json_value.cpp

../src/json/openmp_test_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/openmp_test_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/openmp_test_json_writer.o ../src/json/json_writer.cpp

test_exception_test_exception.o:test_exception.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_exception_test_exception.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_exception_test_exception.o test_exception.cc

test_map_util_test_map_util.o:test_map_util.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_map_util_test_map_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_map_util_test_map_util.o test_map_util.cc

test_seg_test_seg.o:test_seg.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_seg_test_seg.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_seg_test_seg.o test_seg.cc

../src/model/test_seg_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seg_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seg_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_seg_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seg_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seg_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_seg_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seg_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seg_Predictor.o ../src/model/Predictor.cpp

../src/model/test_seg_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seg_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seg_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_seg_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seg_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seg_Score.o ../src/model/Score.cpp

../src/model/test_seg_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seg_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seg_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_seg_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seg_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seg_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_seg_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seg_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seg_json_reader.o ../src/json/json_reader.cpp

../src/json/test_seg_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seg_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seg_json_value.o ../src/json/json_value.cpp

../src/json/test_seg_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seg_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seg_json_writer.o ../src/json/json_writer.cpp

test_identifer_test_identifer.o:test_identifer.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_identifer_test_identifer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_identifer_test_identifer.o test_identifer.cc

../src/model/test_identifer_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_identifer_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_identifer_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_identifer_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_identifer_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_identifer_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_identifer_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_identifer_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_identifer_Predictor.o ../src/model/Predictor.cpp

../src/model/test_identifer_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_identifer_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_identifer_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_identifer_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_identifer_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_identifer_Score.o ../src/model/Score.cpp

../src/model/test_identifer_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_identifer_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_identifer_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_identifer_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_identifer_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_identifer_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_identifer_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_identifer_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_identifer_json_reader.o ../src/json/json_reader.cpp

../src/json/test_identifer_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_identifer_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_identifer_json_value.o ../src/json/json_value.cpp

../src/json/test_identifer_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_identifer_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_identifer_json_writer.o ../src/json/json_writer.cpp

test_linear_test_linear.o:test_linear.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_linear_test_linear.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_linear_test_linear.o test_linear.cc

../src/model/test_linear_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_linear_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_linear_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_linear_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_linear_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_linear_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_linear_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_linear_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_linear_Predictor.o ../src/model/Predictor.cpp

../src/model/test_linear_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_linear_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_linear_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_linear_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_linear_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_linear_Score.o ../src/model/Score.cpp

../src/model/test_linear_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_linear_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_linear_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_linear_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_linear_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_linear_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_linear_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_linear_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_linear_json_reader.o ../src/json/json_reader.cpp

../src/json/test_linear_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_linear_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_linear_json_value.o ../src/json/json_value.cpp

../src/json/test_linear_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_linear_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_linear_json_writer.o ../src/json/json_writer.cpp

test_pinyin_test_pinyin.o:test_pinyin.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_pinyin_test_pinyin.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_pinyin_test_pinyin.o test_pinyin.cc

../src/model/test_pinyin_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_pinyin_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_pinyin_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_pinyin_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_pinyin_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_pinyin_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_pinyin_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_pinyin_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_pinyin_Predictor.o ../src/model/Predictor.cpp

../src/model/test_pinyin_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_pinyin_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_pinyin_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_pinyin_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_pinyin_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_pinyin_Score.o ../src/model/Score.cpp

../src/model/test_pinyin_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_pinyin_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_pinyin_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_pinyin_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_pinyin_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_pinyin_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_pinyin_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_pinyin_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_pinyin_json_reader.o ../src/json/json_reader.cpp

../src/json/test_pinyin_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_pinyin_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_pinyin_json_value.o ../src/json/json_value.cpp

../src/json/test_pinyin_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_pinyin_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_pinyin_json_writer.o ../src/json/json_writer.cpp

test_namepattern_test_namepattern.o:test_namepattern.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_namepattern_test_namepattern.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_namepattern_test_namepattern.o test_namepattern.cc

../src/model/test_namepattern_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_namepattern_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_namepattern_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_namepattern_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_namepattern_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_namepattern_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_namepattern_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_namepattern_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_namepattern_Predictor.o ../src/model/Predictor.cpp

../src/model/test_namepattern_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_namepattern_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_namepattern_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_namepattern_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_namepattern_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_namepattern_Score.o ../src/model/Score.cpp

../src/model/test_namepattern_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_namepattern_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_namepattern_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_namepattern_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_namepattern_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_namepattern_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_namepattern_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_namepattern_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_namepattern_json_reader.o ../src/json/json_reader.cpp

../src/json/test_namepattern_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_namepattern_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_namepattern_json_value.o ../src/json/json_value.cpp

../src/json/test_namepattern_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_namepattern_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_namepattern_json_writer.o ../src/json/json_writer.cpp

test_conf_test_conf.o:test_conf.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_conf_test_conf.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_conf_test_conf.o test_conf.cc

../src/model/test_conf_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_conf_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_conf_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_conf_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_conf_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_conf_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_conf_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_conf_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_conf_Predictor.o ../src/model/Predictor.cpp

../src/model/test_conf_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_conf_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_conf_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_conf_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_conf_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_conf_Score.o ../src/model/Score.cpp

../src/model/test_conf_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_conf_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_conf_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_conf_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_conf_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_conf_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_conf_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_conf_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_conf_json_reader.o ../src/json/json_reader.cpp

../src/json/test_conf_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_conf_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_conf_json_value.o ../src/json/json_value.cpp

../src/json/test_conf_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_conf_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_conf_json_writer.o ../src/json/json_writer.cpp

test_random_test_random.o:test_random.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_random_test_random.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_random_test_random.o test_random.cc

../src/model/test_random_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_random_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_random_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_random_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_random_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_random_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_random_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_random_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_random_Predictor.o ../src/model/Predictor.cpp

../src/model/test_random_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_random_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_random_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_random_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_random_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_random_Score.o ../src/model/Score.cpp

../src/model/test_random_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_random_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_random_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_random_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_random_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_random_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_random_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_random_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_random_json_reader.o ../src/json/json_reader.cpp

../src/json/test_random_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_random_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_random_json_value.o ../src/json/json_value.cpp

../src/json/test_random_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_random_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_random_json_writer.o ../src/json/json_writer.cpp

test_shared_ptr_test_shared_ptr.o:test_shared_ptr.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_shared_ptr_test_shared_ptr.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_shared_ptr_test_shared_ptr.o test_shared_ptr.cc

../src/model/test_shared_ptr_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_shared_ptr_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_shared_ptr_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_shared_ptr_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_shared_ptr_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_shared_ptr_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_shared_ptr_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_shared_ptr_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_shared_ptr_Predictor.o ../src/model/Predictor.cpp

../src/model/test_shared_ptr_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_shared_ptr_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_shared_ptr_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_shared_ptr_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_shared_ptr_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_shared_ptr_Score.o ../src/model/Score.cpp

../src/model/test_shared_ptr_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_shared_ptr_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_shared_ptr_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_shared_ptr_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_shared_ptr_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_shared_ptr_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_shared_ptr_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_shared_ptr_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_shared_ptr_json_reader.o ../src/json/json_reader.cpp

../src/json/test_shared_ptr_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_shared_ptr_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_shared_ptr_json_value.o ../src/json/json_value.cpp

../src/json/test_shared_ptr_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_shared_ptr_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_shared_ptr_json_writer.o ../src/json/json_writer.cpp

test_binfinder_test_binfinder.o:test_binfinder.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_binfinder_test_binfinder.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_binfinder_test_binfinder.o test_binfinder.cc

../src/model/test_binfinder_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_binfinder_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_binfinder_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_binfinder_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_binfinder_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_binfinder_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_binfinder_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_binfinder_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_binfinder_Predictor.o ../src/model/Predictor.cpp

../src/model/test_binfinder_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_binfinder_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_binfinder_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_binfinder_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_binfinder_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_binfinder_Score.o ../src/model/Score.cpp

../src/model/test_binfinder_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_binfinder_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_binfinder_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_binfinder_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_binfinder_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_binfinder_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_binfinder_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_binfinder_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_binfinder_json_reader.o ../src/json/json_reader.cpp

../src/json/test_binfinder_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_binfinder_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_binfinder_json_value.o ../src/json/json_value.cpp

../src/json/test_binfinder_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_binfinder_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_binfinder_json_writer.o ../src/json/json_writer.cpp

test_seralize_test_seralize.o:test_seralize.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_seralize_test_seralize.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_seralize_test_seralize.o test_seralize.cc

../src/model/test_seralize_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_seralize_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_seralize_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_Predictor.o ../src/model/Predictor.cpp

../src/model/test_seralize_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_seralize_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_Score.o ../src/model/Score.cpp

../src/model/test_seralize_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_seralize_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_seralize_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seralize_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seralize_json_reader.o ../src/json/json_reader.cpp

../src/json/test_seralize_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seralize_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seralize_json_value.o ../src/json/json_value.cpp

../src/json/test_seralize_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seralize_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seralize_json_writer.o ../src/json/json_writer.cpp

test_string_test_string.o:test_string.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_string_test_string.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_string_test_string.o test_string.cc

../src/model/test_string_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_string_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_string_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_string_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_string_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_string_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_string_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_string_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_string_Predictor.o ../src/model/Predictor.cpp

../src/model/test_string_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_string_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_string_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_string_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_string_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_string_Score.o ../src/model/Score.cpp

../src/model/test_string_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_string_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_string_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_string_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_string_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_string_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_string_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_string_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_string_json_reader.o ../src/json/json_reader.cpp

../src/json/test_string_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_string_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_string_json_value.o ../src/json/json_value.cpp

../src/json/test_string_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_string_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_string_json_writer.o ../src/json/json_writer.cpp

test_bitop_test_bitop.o:test_bitop.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_bitop_test_bitop.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_bitop_test_bitop.o test_bitop.cc

../src/model/test_bitop_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bitop_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bitop_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_bitop_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bitop_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bitop_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_bitop_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bitop_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bitop_Predictor.o ../src/model/Predictor.cpp

../src/model/test_bitop_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bitop_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bitop_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_bitop_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bitop_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bitop_Score.o ../src/model/Score.cpp

../src/model/test_bitop_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bitop_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bitop_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_bitop_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bitop_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bitop_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_bitop_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_bitop_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_bitop_json_reader.o ../src/json/json_reader.cpp

../src/json/test_bitop_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_bitop_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_bitop_json_value.o ../src/json/json_value.cpp

../src/json/test_bitop_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_bitop_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_bitop_json_writer.o ../src/json/json_writer.cpp

test_featurevector_test_featurevector.o:test_featurevector.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_featurevector_test_featurevector.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_featurevector_test_featurevector.o test_featurevector.cc

../src/model/test_featurevector_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_featurevector_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_featurevector_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_featurevector_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_featurevector_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_featurevector_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_featurevector_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_featurevector_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_featurevector_Predictor.o ../src/model/Predictor.cpp

../src/model/test_featurevector_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_featurevector_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_featurevector_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_featurevector_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_featurevector_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_featurevector_Score.o ../src/model/Score.cpp

../src/model/test_featurevector_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_featurevector_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_featurevector_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_featurevector_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_featurevector_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_featurevector_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_featurevector_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_featurevector_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_featurevector_json_reader.o ../src/json/json_reader.cpp

../src/json/test_featurevector_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_featurevector_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_featurevector_json_value.o ../src/json/json_value.cpp

../src/json/test_featurevector_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_featurevector_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_featurevector_json_writer.o ../src/json/json_writer.cpp

test_split_test_split.o:test_split.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_split_test_split.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_split_test_split.o test_split.cc

../src/model/test_split_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_split_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_split_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_split_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_split_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_split_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_split_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_split_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_split_Predictor.o ../src/model/Predictor.cpp

../src/model/test_split_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_split_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_split_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_split_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_split_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_split_Score.o ../src/model/Score.cpp

../src/model/test_split_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_split_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_split_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_split_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_split_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_split_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_split_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_split_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_split_json_reader.o ../src/json/json_reader.cpp

../src/json/test_split_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_split_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_split_json_value.o ../src/json/json_value.cpp

../src/json/test_split_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_split_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_split_json_writer.o ../src/json/json_writer.cpp

test_tieba_get_info_test_tieba_get_info.o:test_tieba_get_info.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_tieba_get_info_test_tieba_get_info.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_tieba_get_info_test_tieba_get_info.o test_tieba_get_info.cc

../src/model/test_tieba_get_info_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_tieba_get_info_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_tieba_get_info_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_tieba_get_info_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_tieba_get_info_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_tieba_get_info_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_tieba_get_info_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_tieba_get_info_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_tieba_get_info_Predictor.o ../src/model/Predictor.cpp

../src/model/test_tieba_get_info_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_tieba_get_info_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_tieba_get_info_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_tieba_get_info_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_tieba_get_info_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_tieba_get_info_Score.o ../src/model/Score.cpp

../src/model/test_tieba_get_info_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_tieba_get_info_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_tieba_get_info_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_tieba_get_info_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_tieba_get_info_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_tieba_get_info_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_tieba_get_info_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_tieba_get_info_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_tieba_get_info_json_reader.o ../src/json/json_reader.cpp

../src/json/test_tieba_get_info_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_tieba_get_info_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_tieba_get_info_json_value.o ../src/json/json_value.cpp

../src/json/test_tieba_get_info_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_tieba_get_info_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_tieba_get_info_json_writer.o ../src/json/json_writer.cpp

test_content_process_test_content_process.o:test_content_process.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_content_process_test_content_process.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_content_process_test_content_process.o test_content_process.cc

test_cached_fetcher_test_cached_fetcher.o:test_cached_fetcher.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_cached_fetcher_test_cached_fetcher.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_cached_fetcher_test_cached_fetcher.o test_cached_fetcher.cc

../src/model/test_cached_fetcher_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cached_fetcher_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cached_fetcher_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_cached_fetcher_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cached_fetcher_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cached_fetcher_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_cached_fetcher_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cached_fetcher_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cached_fetcher_Predictor.o ../src/model/Predictor.cpp

../src/model/test_cached_fetcher_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cached_fetcher_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cached_fetcher_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_cached_fetcher_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cached_fetcher_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cached_fetcher_Score.o ../src/model/Score.cpp

../src/model/test_cached_fetcher_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cached_fetcher_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cached_fetcher_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_cached_fetcher_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cached_fetcher_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cached_fetcher_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_cached_fetcher_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_cached_fetcher_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_cached_fetcher_json_reader.o ../src/json/json_reader.cpp

../src/json/test_cached_fetcher_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_cached_fetcher_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_cached_fetcher_json_value.o ../src/json/json_value.cpp

../src/json/test_cached_fetcher_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_cached_fetcher_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_cached_fetcher_json_writer.o ../src/json/json_writer.cpp

test_bind_test_bind.o:test_bind.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_bind_test_bind.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_bind_test_bind.o test_bind.cc

../src/model/test_bind_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bind_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bind_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_bind_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bind_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bind_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_bind_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bind_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bind_Predictor.o ../src/model/Predictor.cpp

../src/model/test_bind_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bind_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bind_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_bind_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bind_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bind_Score.o ../src/model/Score.cpp

../src/model/test_bind_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bind_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bind_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_bind_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_bind_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_bind_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_bind_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_bind_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_bind_json_reader.o ../src/json/json_reader.cpp

../src/json/test_bind_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_bind_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_bind_json_value.o ../src/json/json_value.cpp

../src/json/test_bind_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_bind_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_bind_json_writer.o ../src/json/json_writer.cpp

test_lrumap_test_lrumap.o:test_lrumap.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_lrumap_test_lrumap.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_lrumap_test_lrumap.o test_lrumap.cc

../src/model/test_lrumap_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_lrumap_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_lrumap_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_lrumap_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_lrumap_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_lrumap_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_lrumap_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_lrumap_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_lrumap_Predictor.o ../src/model/Predictor.cpp

../src/model/test_lrumap_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_lrumap_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_lrumap_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_lrumap_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_lrumap_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_lrumap_Score.o ../src/model/Score.cpp

../src/model/test_lrumap_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_lrumap_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_lrumap_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_lrumap_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_lrumap_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_lrumap_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_lrumap_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_lrumap_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_lrumap_json_reader.o ../src/json/json_reader.cpp

../src/json/test_lrumap_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_lrumap_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_lrumap_json_value.o ../src/json/json_value.cpp

../src/json/test_lrumap_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_lrumap_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_lrumap_json_writer.o ../src/json/json_writer.cpp

test_seralize_xml_test_seralize_xml.o:test_seralize_xml.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_seralize_xml_test_seralize_xml.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_seralize_xml_test_seralize_xml.o test_seralize_xml.cc

../src/model/test_seralize_xml_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_xml_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_xml_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_seralize_xml_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_xml_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_xml_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_seralize_xml_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_xml_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_xml_Predictor.o ../src/model/Predictor.cpp

../src/model/test_seralize_xml_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_xml_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_xml_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_seralize_xml_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_xml_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_xml_Score.o ../src/model/Score.cpp

../src/model/test_seralize_xml_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_xml_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_xml_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_seralize_xml_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_seralize_xml_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_seralize_xml_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_seralize_xml_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seralize_xml_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seralize_xml_json_reader.o ../src/json/json_reader.cpp

../src/json/test_seralize_xml_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seralize_xml_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seralize_xml_json_value.o ../src/json/json_value.cpp

../src/json/test_seralize_xml_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_seralize_xml_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_seralize_xml_json_writer.o ../src/json/json_writer.cpp

test_thread_local_test_thread_local.o:test_thread_local.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_thread_local_test_thread_local.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_thread_local_test_thread_local.o test_thread_local.cc

../src/model/test_thread_local_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_thread_local_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_thread_local_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_thread_local_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_thread_local_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_thread_local_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_thread_local_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_thread_local_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_thread_local_Predictor.o ../src/model/Predictor.cpp

../src/model/test_thread_local_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_thread_local_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_thread_local_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_thread_local_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_thread_local_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_thread_local_Score.o ../src/model/Score.cpp

../src/model/test_thread_local_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_thread_local_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_thread_local_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_thread_local_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_thread_local_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_thread_local_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_thread_local_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_thread_local_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_thread_local_json_reader.o ../src/json/json_reader.cpp

../src/json/test_thread_local_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_thread_local_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_thread_local_json_value.o ../src/json/json_value.cpp

../src/json/test_thread_local_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_thread_local_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_thread_local_json_writer.o ../src/json/json_writer.cpp

test_configure_test_configure.o:test_configure.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_configure_test_configure.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_configure_test_configure.o test_configure.cc

../src/model/test_configure_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_configure_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_configure_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_configure_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_configure_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_configure_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_configure_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_configure_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_configure_Predictor.o ../src/model/Predictor.cpp

../src/model/test_configure_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_configure_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_configure_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_configure_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_configure_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_configure_Score.o ../src/model/Score.cpp

../src/model/test_configure_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_configure_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_configure_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_configure_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_configure_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_configure_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_configure_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_configure_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_configure_json_reader.o ../src/json/json_reader.cpp

../src/json/test_configure_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_configure_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_configure_json_value.o ../src/json/json_value.cpp

../src/json/test_configure_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_configure_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_configure_json_writer.o ../src/json/json_writer.cpp

test_static_test_static.o:test_static.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_static_test_static.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_static_test_static.o test_static.cc

../src/model/test_static_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_static_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_static_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_static_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_static_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_static_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_static_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_static_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_static_Predictor.o ../src/model/Predictor.cpp

../src/model/test_static_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_static_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_static_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_static_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_static_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_static_Score.o ../src/model/Score.cpp

../src/model/test_static_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_static_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_static_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_static_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_static_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_static_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_static_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_static_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_static_json_reader.o ../src/json/json_reader.cpp

../src/json/test_static_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_static_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_static_json_value.o ../src/json/json_value.cpp

../src/json/test_static_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_static_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_static_json_writer.o ../src/json/json_writer.cpp

test_cpplinq_test_cpplinq.o:test_cpplinq.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_cpplinq_test_cpplinq.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_cpplinq_test_cpplinq.o test_cpplinq.cc

../src/model/test_cpplinq_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cpplinq_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cpplinq_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_cpplinq_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cpplinq_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cpplinq_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_cpplinq_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cpplinq_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cpplinq_Predictor.o ../src/model/Predictor.cpp

../src/model/test_cpplinq_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cpplinq_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cpplinq_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_cpplinq_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cpplinq_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cpplinq_Score.o ../src/model/Score.cpp

../src/model/test_cpplinq_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cpplinq_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cpplinq_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_cpplinq_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_cpplinq_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_cpplinq_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_cpplinq_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_cpplinq_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_cpplinq_json_reader.o ../src/json/json_reader.cpp

../src/json/test_cpplinq_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_cpplinq_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_cpplinq_json_value.o ../src/json/json_value.cpp

../src/json/test_cpplinq_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_cpplinq_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_cpplinq_json_writer.o ../src/json/json_writer.cpp

test_partial_sort_test_partial_sort.o:test_partial_sort.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_partial_sort_test_partial_sort.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_partial_sort_test_partial_sort.o test_partial_sort.cc

../src/model/test_partial_sort_LinearModel.o:../src/model/LinearModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_partial_sort_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_partial_sort_LinearModel.o ../src/model/LinearModel.cpp

../src/model/test_partial_sort_ModelFactory.o:../src/model/ModelFactory.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_partial_sort_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_partial_sort_ModelFactory.o ../src/model/ModelFactory.cpp

../src/model/test_partial_sort_Predictor.o:../src/model/Predictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_partial_sort_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_partial_sort_Predictor.o ../src/model/Predictor.cpp

../src/model/test_partial_sort_RandForestModel.o:../src/model/RandForestModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_partial_sort_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_partial_sort_RandForestModel.o ../src/model/RandForestModel.cpp

../src/model/test_partial_sort_Score.o:../src/model/Score.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_partial_sort_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_partial_sort_Score.o ../src/model/Score.cpp

../src/model/test_partial_sort_SharedPredictor.o:../src/model/SharedPredictor.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_partial_sort_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_partial_sort_SharedPredictor.o ../src/model/SharedPredictor.cpp

../src/model/test_partial_sort_SvmModel.o:../src/model/SvmModel.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/model/test_partial_sort_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/model/test_partial_sort_SvmModel.o ../src/model/SvmModel.cpp

../src/json/test_partial_sort_json_reader.o:../src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_partial_sort_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_partial_sort_json_reader.o ../src/json/json_reader.cpp

../src/json/test_partial_sort_json_value.o:../src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_partial_sort_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_partial_sort_json_value.o ../src/json/json_value.cpp

../src/json/test_partial_sort_json_writer.o:../src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40m../src/json/test_partial_sort_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o ../src/json/test_partial_sort_json_writer.o ../src/json/json_writer.cpp

test_string_util_test_string_util.o:test_string_util.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_string_util_test_string_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_string_util_test_string_util.o test_string_util.cc

test_mean_var_test_mean_var.o:test_mean_var.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_mean_var_test_mean_var.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_mean_var_test_mean_var.o test_mean_var.cc

test_const_test_const.o:test_const.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_const_test_const.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_const_test_const.o test_const.cc

test_sharedobjects_test_sharedobjects.o:test_sharedobjects.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_sharedobjects_test_sharedobjects.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_sharedobjects_test_sharedobjects.o test_sharedobjects.cc

test_matchdict_test_matchdict.o:test_matchdict.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_matchdict_test_matchdict.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_matchdict_test_matchdict.o test_matchdict.cc

test_erase_test_erase.o:test_erase.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_erase_test_erase.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_erase_test_erase.o test_erase.cc

endif #ifeq ($(shell uname -m),x86_64)


