#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -O3 \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -O3 \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I./include \
  -I./utils \
  -I./output \
  -I./output/include \
  -I./include/feature \
  -I./include/model
DEP_INCPATH=-I../../../../../com/btest/gtest \
  -I../../../../../com/btest/gtest/include \
  -I../../../../../com/btest/gtest/output \
  -I../../../../../com/btest/gtest/output/include \
  -I../../../../../lib2-64/bsl \
  -I../../../../../lib2-64/bsl/include \
  -I../../../../../lib2-64/bsl/output \
  -I../../../../../lib2-64/bsl/output/include \
  -I../../../../../lib2-64/ccode \
  -I../../../../../lib2-64/ccode/include \
  -I../../../../../lib2-64/ccode/output \
  -I../../../../../lib2-64/ccode/output/include \
  -I../../../../../lib2-64/dict \
  -I../../../../../lib2-64/dict/include \
  -I../../../../../lib2-64/dict/output \
  -I../../../../../lib2-64/dict/output/include \
  -I../../../../../lib2-64/libcrf \
  -I../../../../../lib2-64/libcrf/include \
  -I../../../../../lib2-64/libcrf/output \
  -I../../../../../lib2-64/libcrf/output/include \
  -I../../../../../lib2-64/others-ex \
  -I../../../../../lib2-64/others-ex/include \
  -I../../../../../lib2-64/others-ex/output \
  -I../../../../../lib2-64/others-ex/output/include \
  -I../../../../../lib2-64/postag \
  -I../../../../../lib2-64/postag/include \
  -I../../../../../lib2-64/postag/output \
  -I../../../../../lib2-64/postag/output/include \
  -I../../../../../lib2-64/ullib \
  -I../../../../../lib2-64/ullib/include \
  -I../../../../../lib2-64/ullib/output \
  -I../../../../../lib2-64/ullib/output/include \
  -I../../../../../lib2-64/wordseg \
  -I../../../../../lib2-64/wordseg/include \
  -I../../../../../lib2-64/wordseg/output \
  -I../../../../../lib2-64/wordseg/output/include \
  -I../../../../../public/comlog-plugin \
  -I../../../../../public/comlog-plugin/include \
  -I../../../../../public/comlog-plugin/output \
  -I../../../../../public/comlog-plugin/output/include \
  -I../../../../../public/configure \
  -I../../../../../public/configure/include \
  -I../../../../../public/configure/output \
  -I../../../../../public/configure/output/include \
  -I../../../../../public/connectpool \
  -I../../../../../public/connectpool/include \
  -I../../../../../public/connectpool/output \
  -I../../../../../public/connectpool/output/include \
  -I../../../../../public/odict \
  -I../../../../../public/odict/include \
  -I../../../../../public/odict/output \
  -I../../../../../public/odict/output/include \
  -I../../../../../public/spreg \
  -I../../../../../public/spreg/include \
  -I../../../../../public/spreg/output \
  -I../../../../../public/spreg/output/include \
  -I../../../../../public/uconv \
  -I../../../../../public/uconv/include \
  -I../../../../../public/uconv/output \
  -I../../../../../public/uconv/output/include \
  -I../../../../../quality/autotest/reportlib/cpp \
  -I../../../../../quality/autotest/reportlib/cpp/include \
  -I../../../../../quality/autotest/reportlib/cpp/output \
  -I../../../../../quality/autotest/reportlib/cpp/output/include \
  -I../../../../../third-64/boost \
  -I../../../../../third-64/boost/include \
  -I../../../../../third-64/boost/output \
  -I../../../../../third-64/boost/output/include \
  -I../../../../../third-64/gflags \
  -I../../../../../third-64/gflags/include \
  -I../../../../../third-64/gflags/output \
  -I../../../../../third-64/gflags/output/include \
  -I../../../../../third-64/glog \
  -I../../../../../third-64/glog/include \
  -I../../../../../third-64/glog/output \
  -I../../../../../third-64/glog/output/include \
  -I../../../../../third-64/libcurl \
  -I../../../../../third-64/libcurl/include \
  -I../../../../../third-64/libcurl/output \
  -I../../../../../third-64/libcurl/output/include \
  -I../../../../../third-64/pcre \
  -I../../../../../third-64/pcre/include \
  -I../../../../../third-64/pcre/output \
  -I../../../../../third-64/pcre/output/include \
  -I../../../../../third-64/tcmalloc \
  -I../../../../../third-64/tcmalloc/include \
  -I../../../../../third-64/tcmalloc/output \
  -I../../../../../third-64/tcmalloc/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=b53330a66897c84ff33b2cd5ee397ee3  COMAKE


.PHONY:all
all:comake2_makefile_check libgezi.a 
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
	rm -rf libgezi.a
	rm -rf ./output/lib/libgezi.a
	rm -rf src/gezi_Seg.o
	rm -rf src/gezi_SharedSegmentor.o
	rm -rf src/gezi_conf_util.o
	rm -rf src/gezi_word_seg.o
	rm -rf src/model/gezi_LinearModel.o
	rm -rf src/model/gezi_ModelFactory.o
	rm -rf src/model/gezi_Predictor.o
	rm -rf src/model/gezi_RandForestModel.o
	rm -rf src/model/gezi_Score.o
	rm -rf src/model/gezi_SharedPredictor.o
	rm -rf src/model/gezi_SvmModel.o
	rm -rf src/json/gezi_json_reader.o
	rm -rf src/json/gezi_json_value.o
	rm -rf src/json/gezi_json_writer.o

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

libgezi.a:src/gezi_Seg.o \
  src/gezi_SharedSegmentor.o \
  src/gezi_conf_util.o \
  src/gezi_word_seg.o \
  src/model/gezi_LinearModel.o \
  src/model/gezi_ModelFactory.o \
  src/model/gezi_Predictor.o \
  src/model/gezi_RandForestModel.o \
  src/model/gezi_Score.o \
  src/model/gezi_SharedPredictor.o \
  src/model/gezi_SvmModel.o \
  src/json/gezi_json_reader.o \
  src/json/gezi_json_value.o \
  src/json/gezi_json_writer.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibgezi.a[0m']"
	ar crs libgezi.a src/gezi_Seg.o \
  src/gezi_SharedSegmentor.o \
  src/gezi_conf_util.o \
  src/gezi_word_seg.o \
  src/model/gezi_LinearModel.o \
  src/model/gezi_ModelFactory.o \
  src/model/gezi_Predictor.o \
  src/model/gezi_RandForestModel.o \
  src/model/gezi_Score.o \
  src/model/gezi_SharedPredictor.o \
  src/model/gezi_SvmModel.o \
  src/json/gezi_json_reader.o \
  src/json/gezi_json_value.o \
  src/json/gezi_json_writer.o
	mkdir -p ./output/lib
	cp -f --link libgezi.a ./output/lib

src/gezi_Seg.o:src/Seg.cpp \
  include/Seg.h \
  include/Segmentor.h \
  include/log_util.h \
  include/debug_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/gezi_Seg.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/gezi_Seg.o src/Seg.cpp

src/gezi_SharedSegmentor.o:src/SharedSegmentor.cpp \
  include/SharedSegmentor.h \
  include/Segmentor.h \
  include/log_util.h \
  include/debug_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/gezi_SharedSegmentor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/gezi_SharedSegmentor.o src/SharedSegmentor.cpp

src/gezi_conf_util.o:src/conf_util.cpp \
  include/conf_util.h \
  include/log_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/hashmap_util.h \
  include/conf_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/gezi_conf_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/gezi_conf_util.o src/conf_util.cpp

src/gezi_word_seg.o:src/word_seg.cpp \
  include/word_seg.h \
  include/Segmentor.h \
  include/log_util.h \
  include/debug_util.h \
  include/Segmentor.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/gezi_word_seg.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/gezi_word_seg.o src/word_seg.cpp

src/model/gezi_LinearModel.o:src/model/LinearModel.cpp \
  include/model/LinearModel.h \
  include/model/Model.h \
  include/feature/Feature.h \
  include/common_util.h \
  include/hashmap_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h \
  include/model/Score.h \
  include/feature/Feature.h \
  include/log_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/model/gezi_LinearModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/model/gezi_LinearModel.o src/model/LinearModel.cpp

src/model/gezi_ModelFactory.o:src/model/ModelFactory.cpp \
  include/model/LinearModel.h \
  include/model/Model.h \
  include/feature/Feature.h \
  include/common_util.h \
  include/hashmap_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h \
  include/model/Score.h \
  include/feature/Feature.h \
  include/model/SvmModel.h \
  include/model/ModelFactory.h \
  include/model/RandForestModel.h \
  include/model/FastRankModel.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/model/gezi_ModelFactory.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/model/gezi_ModelFactory.o src/model/ModelFactory.cpp

src/model/gezi_Predictor.o:src/model/Predictor.cpp \
  include/model/Predictor.h \
  include/model/Model.h \
  include/feature/Feature.h \
  include/common_util.h \
  include/hashmap_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h \
  include/model/Score.h \
  include/feature/FeatureNormalizer.h \
  include/feature/Feature.h \
  include/feature/Feature.h \
  include/model/Score.h \
  include/model/ModelFactory.h \
  include/log_util.h \
  include/conf_util.h \
  include/common_util.h \
  include/debug_util.h \
  include/feature/feature_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/model/gezi_Predictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/model/gezi_Predictor.o src/model/Predictor.cpp

src/model/gezi_RandForestModel.o:src/model/RandForestModel.cpp \
  include/model/RandForestModel.h \
  include/model/Model.h \
  include/feature/Feature.h \
  include/common_util.h \
  include/hashmap_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h \
  include/model/Score.h \
  include/feature/Feature.h \
  include/log_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/model/gezi_RandForestModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/model/gezi_RandForestModel.o src/model/RandForestModel.cpp

src/model/gezi_Score.o:src/model/Score.cpp \
  include/model/Score.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/model/gezi_Score.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/model/gezi_Score.o src/model/Score.cpp

src/model/gezi_SharedPredictor.o:src/model/SharedPredictor.cpp \
  include/model/SharedPredictor.h \
  include/model/Predictor.h \
  include/model/Model.h \
  include/feature/Feature.h \
  include/common_util.h \
  include/hashmap_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h \
  include/model/Score.h \
  include/feature/FeatureNormalizer.h \
  include/feature/Feature.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/model/gezi_SharedPredictor.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/model/gezi_SharedPredictor.o src/model/SharedPredictor.cpp

src/model/gezi_SvmModel.o:src/model/SvmModel.cpp \
  include/model/SvmModel.h \
  include/model/Model.h \
  include/feature/Feature.h \
  include/common_util.h \
  include/hashmap_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h \
  include/model/Score.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/model/gezi_SvmModel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/model/gezi_SvmModel.o src/model/SvmModel.cpp

src/json/gezi_json_reader.o:src/json/json_reader.cpp \
  include/json/reader.h \
  include/json/features.h \
  include/json/forwards.h \
  include/json/config.h \
  include/json/value.h \
  include/json/value.h \
  src/json/json_tool.h \
  include/encoding_convert.h \
  include/log_util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/json/gezi_json_reader.o src/json/json_reader.cpp

src/json/gezi_json_value.o:src/json/json_value.cpp \
  include/common_util.h \
  include/hashmap_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/common_util.h \
  include/string_util.h \
  include/wstring_util.h \
  include/encoding_convert.h \
  include/reg_util.h \
  include/serialize_util.h \
  include/unordered_map_serialize.h \
  include/unordered_set_serialize.h \
  include/statistic_util.h \
  include/datetime_util.h \
  include/encoding_convert.h \
  include/json/value.h \
  include/json/forwards.h \
  include/json/config.h \
  include/json/writer.h \
  include/json/value.h \
  src/json/json_batchallocator.h \
  src/json/json_valueiterator.inl
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/json/gezi_json_value.o src/json/json_value.cpp

src/json/gezi_json_writer.o:src/json/json_writer.cpp \
  include/json/writer.h \
  include/json/value.h \
  include/json/forwards.h \
  include/json/config.h \
  src/json/json_tool.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/json/gezi_json_writer.o src/json/json_writer.cpp

endif #ifeq ($(shell uname -m),x86_64)


