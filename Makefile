#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=/opt/compiler/gcc-4.8.2/bin/g++
CXX=/opt/compiler/gcc-4.8.2/bin/g++
CXXFLAGS=-g \
  -O3 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -Wno-deprecated \
  -std=c++11 \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs \
  -fopenmp
CFLAGS=-g \
  -O3 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -Wno-deprecated \
  -std=c++11 \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs \
  -fopenmp
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I./include/cppformat/ \
  -I. \
  -I./include \
  -I./utils \
  -I./output \
  -I./output/include \
  -I./include/feature \
  -I./include/numeric \
  -I./melt/include/ \
  -I./include/serialization/
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
COMAKE_MD5=f8aa7bb6e8867356d742bd529d689ba5  COMAKE


.PHONY:all
all:comake2_makefile_check libgezi_cppformat.a copy-pinyin-lib libgezi_common.a libgezi_json.a 
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
	rm -rf libgezi_cppformat.a
	rm -rf ./output/lib/libgezi_cppformat.a
	rm -rf copy-pinyin-lib
	rm -rf ./output/lib/libPYNotation.a
	rm -rf libgezi_common.a
	rm -rf ./output/lib/libgezi_common.a
	rm -rf libgezi_json.a
	rm -rf ./output/lib/libgezi_json.a
	rm -rf src/cppformat/gezi_cppformat_format.o
	rm -rf src/cppformat/gezi_cppformat_posix.o
	rm -rf src/json/gezi_json_json_reader.o
	rm -rf src/json/gezi_json_json_value.o
	rm -rf src/json/gezi_json_json_writer.o

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

libgezi_cppformat.a:src/cppformat/gezi_cppformat_format.o \
  src/cppformat/gezi_cppformat_posix.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibgezi_cppformat.a[0m']"
	ar crs libgezi_cppformat.a src/cppformat/gezi_cppformat_format.o \
  src/cppformat/gezi_cppformat_posix.o
	mkdir -p ./output/lib
	cp -f --link libgezi_cppformat.a ./output/lib

copy-pinyin-lib:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcopy-pinyin-lib[0m']"
	mkdir -p output/lib
	cp ./include/tools/pinyin/libPYNotation.a ./output/lib/

libgezi_common.a:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibgezi_common.a[0m']"
	ar crs libgezi_common.a 
	mkdir -p ./output/lib
	cp -f --link libgezi_common.a ./output/lib

libgezi_json.a:src/json/gezi_json_json_reader.o \
  src/json/gezi_json_json_value.o \
  src/json/gezi_json_json_writer.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibgezi_json.a[0m']"
	ar crs libgezi_json.a src/json/gezi_json_json_reader.o \
  src/json/gezi_json_json_value.o \
  src/json/gezi_json_json_writer.o
	mkdir -p ./output/lib
	cp -f --link libgezi_json.a ./output/lib

src/cppformat/gezi_cppformat_format.o:src/cppformat/format.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/cppformat/gezi_cppformat_format.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o src/cppformat/gezi_cppformat_format.o src/cppformat/format.cc

src/cppformat/gezi_cppformat_posix.o:src/cppformat/posix.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/cppformat/gezi_cppformat_posix.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o src/cppformat/gezi_cppformat_posix.o src/cppformat/posix.cc

src/json/gezi_json_json_reader.o:src/json/json_reader.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o src/json/gezi_json_json_reader.o src/json/json_reader.cpp

src/json/gezi_json_json_value.o:src/json/json_value.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o src/json/gezi_json_json_value.o src/json/json_value.cpp

src/json/gezi_json_json_writer.o:src/json/json_writer.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o src/json/gezi_json_json_writer.o src/json/json_writer.cpp

endif #ifeq ($(shell uname -m),x86_64)


