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
  -std=c++0x \
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
  -std=c++0x \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs \
  -fopenmp
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I../../../include \
  -I../../../utils \
  -I../../../output \
  -I../../../output/include \
  -I../../../include/feature \
  -I../../../include/model \
  -I../../../include/numeric \
  -I./include/
DEP_INCPATH=-I../../../../../../../../app/search/sep/anti-spam/melt \
  -I../../../../../../../../app/search/sep/anti-spam/melt/include \
  -I../../../../../../../../app/search/sep/anti-spam/melt/output \
  -I../../../../../../../../app/search/sep/anti-spam/melt/output/include \
  -I../../../../../../../../com/btest/gtest \
  -I../../../../../../../../com/btest/gtest/include \
  -I../../../../../../../../com/btest/gtest/output \
  -I../../../../../../../../com/btest/gtest/output/include \
  -I../../../../../../../../lib2-64/bsl \
  -I../../../../../../../../lib2-64/bsl/include \
  -I../../../../../../../../lib2-64/bsl/output \
  -I../../../../../../../../lib2-64/bsl/output/include \
  -I../../../../../../../../lib2-64/ccode \
  -I../../../../../../../../lib2-64/ccode/include \
  -I../../../../../../../../lib2-64/ccode/output \
  -I../../../../../../../../lib2-64/ccode/output/include \
  -I../../../../../../../../lib2-64/dict \
  -I../../../../../../../../lib2-64/dict/include \
  -I../../../../../../../../lib2-64/dict/output \
  -I../../../../../../../../lib2-64/dict/output/include \
  -I../../../../../../../../lib2-64/libcrf \
  -I../../../../../../../../lib2-64/libcrf/include \
  -I../../../../../../../../lib2-64/libcrf/output \
  -I../../../../../../../../lib2-64/libcrf/output/include \
  -I../../../../../../../../lib2-64/nlp/compact-trie \
  -I../../../../../../../../lib2-64/nlp/compact-trie/include \
  -I../../../../../../../../lib2-64/nlp/compact-trie/output \
  -I../../../../../../../../lib2-64/nlp/compact-trie/output/include \
  -I../../../../../../../../lib2-64/others-ex \
  -I../../../../../../../../lib2-64/others-ex/include \
  -I../../../../../../../../lib2-64/others-ex/output \
  -I../../../../../../../../lib2-64/others-ex/output/include \
  -I../../../../../../../../lib2-64/postag \
  -I../../../../../../../../lib2-64/postag/include \
  -I../../../../../../../../lib2-64/postag/output \
  -I../../../../../../../../lib2-64/postag/output/include \
  -I../../../../../../../../lib2-64/text-util \
  -I../../../../../../../../lib2-64/text-util/include \
  -I../../../../../../../../lib2-64/text-util/output \
  -I../../../../../../../../lib2-64/text-util/output/include \
  -I../../../../../../../../lib2-64/ullib \
  -I../../../../../../../../lib2-64/ullib/include \
  -I../../../../../../../../lib2-64/ullib/output \
  -I../../../../../../../../lib2-64/ullib/output/include \
  -I../../../../../../../../lib2-64/wordseg \
  -I../../../../../../../../lib2-64/wordseg/include \
  -I../../../../../../../../lib2-64/wordseg/output \
  -I../../../../../../../../lib2-64/wordseg/output/include \
  -I../../../../../../../../ps/se/dict-set \
  -I../../../../../../../../ps/se/dict-set/include \
  -I../../../../../../../../ps/se/dict-set/output \
  -I../../../../../../../../ps/se/dict-set/output/include \
  -I../../../../../../../../ps/se/include \
  -I../../../../../../../../ps/se/include/include \
  -I../../../../../../../../ps/se/include/output \
  -I../../../../../../../../ps/se/include/output/include \
  -I../../../../../../../../public/comlog-plugin \
  -I../../../../../../../../public/comlog-plugin/include \
  -I../../../../../../../../public/comlog-plugin/output \
  -I../../../../../../../../public/comlog-plugin/output/include \
  -I../../../../../../../../public/configure \
  -I../../../../../../../../public/configure/include \
  -I../../../../../../../../public/configure/output \
  -I../../../../../../../../public/configure/output/include \
  -I../../../../../../../../public/connectpool \
  -I../../../../../../../../public/connectpool/include \
  -I../../../../../../../../public/connectpool/output \
  -I../../../../../../../../public/connectpool/output/include \
  -I../../../../../../../../public/odict \
  -I../../../../../../../../public/odict/include \
  -I../../../../../../../../public/odict/output \
  -I../../../../../../../../public/odict/output/include \
  -I../../../../../../../../public/spreg \
  -I../../../../../../../../public/spreg/include \
  -I../../../../../../../../public/spreg/output \
  -I../../../../../../../../public/spreg/output/include \
  -I../../../../../../../../public/uconv \
  -I../../../../../../../../public/uconv/include \
  -I../../../../../../../../public/uconv/output \
  -I../../../../../../../../public/uconv/output/include \
  -I../../../../../../../../public/urlparser \
  -I../../../../../../../../public/urlparser/include \
  -I../../../../../../../../public/urlparser/output \
  -I../../../../../../../../public/urlparser/output/include \
  -I../../../../../../../../quality/autotest/reportlib/cpp \
  -I../../../../../../../../quality/autotest/reportlib/cpp/include \
  -I../../../../../../../../quality/autotest/reportlib/cpp/output \
  -I../../../../../../../../quality/autotest/reportlib/cpp/output/include \
  -I../../../../../../../../st/nlp/lm-score \
  -I../../../../../../../../st/nlp/lm-score/include \
  -I../../../../../../../../st/nlp/lm-score/output \
  -I../../../../../../../../st/nlp/lm-score/output/include \
  -I../../../../../../../../third-64/boost \
  -I../../../../../../../../third-64/boost/include \
  -I../../../../../../../../third-64/boost/output \
  -I../../../../../../../../third-64/boost/output/include \
  -I../../../../../../../../third-64/gflags \
  -I../../../../../../../../third-64/gflags/include \
  -I../../../../../../../../third-64/gflags/output \
  -I../../../../../../../../third-64/gflags/output/include \
  -I../../../../../../../../third-64/glog \
  -I../../../../../../../../third-64/glog/include \
  -I../../../../../../../../third-64/glog/output \
  -I../../../../../../../../third-64/glog/output/include \
  -I../../../../../../../../third-64/pcre \
  -I../../../../../../../../third-64/pcre/include \
  -I../../../../../../../../third-64/pcre/output \
  -I../../../../../../../../third-64/pcre/output/include \
  -I../../../../../../../../third-64/tcmalloc \
  -I../../../../../../../../third-64/tcmalloc/include \
  -I../../../../../../../../third-64/tcmalloc/output \
  -I../../../../../../../../third-64/tcmalloc/output/include \
  -I../../../../../../../../third-64/zlib \
  -I../../../../../../../../third-64/zlib/include \
  -I../../../../../../../../third-64/zlib/output \
  -I../../../../../../../../third-64/zlib/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=aff8186d0dfb0d0db6eb4935d9403478  COMAKE


.PHONY:all
all:comake2_makefile_check get_urate_infos urate_train urate_predicts_from_file urate_reducer img_reducer lou_reducer test_langmodel liburate_train.a 
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
	rm -rf get_urate_infos
	rm -rf ./output/bin/get_urate_infos
	rm -rf urate_train
	rm -rf ./output/bin/urate_train
	rm -rf urate_predicts_from_file
	rm -rf ./output/bin/urate_predicts_from_file
	rm -rf urate_reducer
	rm -rf ./output/bin/urate_reducer
	rm -rf img_reducer
	rm -rf ./output/bin/img_reducer
	rm -rf lou_reducer
	rm -rf ./output/bin/lou_reducer
	rm -rf test_langmodel
	rm -rf ./output/bin/test_langmodel
	rm -rf liburate_train.a
	rm -rf ./output/lib/liburate_train.a
	rm -rf get_urate_infos_get_urate_infos.o
	rm -rf urate_train_urate_train.o
	rm -rf urate_predicts_from_file_urate_predicts_from_file.o
	rm -rf urate_reducer_urate_reducer.o
	rm -rf img_reducer_img_reducer.o
	rm -rf lou_reducer_lou_reducer.o
	rm -rf test_langmodel_test_langmodel.o
	rm -rf src/urate_train_urate_train.o

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

get_urate_infos:get_urate_infos_get_urate_infos.o \
  ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mget_urate_infos[0m']"
	$(CXX) get_urate_infos_get_urate_infos.o -Xlinker "-(" ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a ../../../../../../../../app/search/sep/anti-spam/melt/libblas.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/liblinear.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libmelt.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsofia.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsvm.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libvw.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../../public/configure/libconfig.a \
  ../../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../../public/odict/libodict.a \
  ../../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a \
  ../../../../../../../../third-64/zlib/lib/libz.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic \
  -lssl \
  -lcrypto \
  -lgomp -Xlinker "-)" -o get_urate_infos
	mkdir -p ./output/bin
	cp -f --link get_urate_infos ./output/bin

urate_train:urate_train_urate_train.o \
  ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40murate_train[0m']"
	$(CXX) urate_train_urate_train.o -Xlinker "-(" ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a ../../../../../../../../app/search/sep/anti-spam/melt/libblas.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/liblinear.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libmelt.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsofia.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsvm.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libvw.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../../public/configure/libconfig.a \
  ../../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../../public/odict/libodict.a \
  ../../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a \
  ../../../../../../../../third-64/zlib/lib/libz.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic \
  -lssl \
  -lcrypto \
  -lgomp -Xlinker "-)" -o urate_train
	mkdir -p ./output/bin
	cp -f --link urate_train ./output/bin

urate_predicts_from_file:urate_predicts_from_file_urate_predicts_from_file.o \
  ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40murate_predicts_from_file[0m']"
	$(CXX) urate_predicts_from_file_urate_predicts_from_file.o -Xlinker "-(" ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a ../../../../../../../../app/search/sep/anti-spam/melt/libblas.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/liblinear.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libmelt.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsofia.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsvm.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libvw.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../../public/configure/libconfig.a \
  ../../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../../public/odict/libodict.a \
  ../../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a \
  ../../../../../../../../third-64/zlib/lib/libz.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic \
  -lssl \
  -lcrypto \
  -lgomp -Xlinker "-)" -o urate_predicts_from_file
	mkdir -p ./output/bin
	cp -f --link urate_predicts_from_file ./output/bin

urate_reducer:urate_reducer_urate_reducer.o \
  ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40murate_reducer[0m']"
	$(CXX) urate_reducer_urate_reducer.o -Xlinker "-(" ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a ../../../../../../../../app/search/sep/anti-spam/melt/libblas.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/liblinear.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libmelt.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsofia.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsvm.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libvw.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../../public/configure/libconfig.a \
  ../../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../../public/odict/libodict.a \
  ../../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a \
  ../../../../../../../../third-64/zlib/lib/libz.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic \
  -lssl \
  -lcrypto \
  -lgomp -Xlinker "-)" -o urate_reducer
	mkdir -p ./output/bin
	cp -f --link urate_reducer ./output/bin

img_reducer:img_reducer_img_reducer.o \
  ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mimg_reducer[0m']"
	$(CXX) img_reducer_img_reducer.o -Xlinker "-(" ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a ../../../../../../../../app/search/sep/anti-spam/melt/libblas.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/liblinear.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libmelt.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsofia.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsvm.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libvw.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../../public/configure/libconfig.a \
  ../../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../../public/odict/libodict.a \
  ../../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a \
  ../../../../../../../../third-64/zlib/lib/libz.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic \
  -lssl \
  -lcrypto \
  -lgomp -Xlinker "-)" -o img_reducer
	mkdir -p ./output/bin
	cp -f --link img_reducer ./output/bin

lou_reducer:lou_reducer_lou_reducer.o \
  ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlou_reducer[0m']"
	$(CXX) lou_reducer_lou_reducer.o -Xlinker "-(" ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a ../../../../../../../../app/search/sep/anti-spam/melt/libblas.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/liblinear.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libmelt.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsofia.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsvm.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libvw.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../../public/configure/libconfig.a \
  ../../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../../public/odict/libodict.a \
  ../../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a \
  ../../../../../../../../third-64/zlib/lib/libz.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic \
  -lssl \
  -lcrypto \
  -lgomp -Xlinker "-)" -o lou_reducer
	mkdir -p ./output/bin
	cp -f --link lou_reducer ./output/bin

test_langmodel:test_langmodel_test_langmodel.o \
  ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_langmodel[0m']"
	$(CXX) test_langmodel_test_langmodel.o -Xlinker "-(" ../../../libgezi_common.a \
  ../../../libgezi_json.a \
  ../../../libgezi_cppformat.a ../../../../../../../../app/search/sep/anti-spam/melt/libblas.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/liblinear.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libmelt.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsofia.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libsvm.a \
  ../../../../../../../../app/search/sep/anti-spam/melt/libvw.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest.a \
  ../../../../../../../../com/btest/gtest/output/lib/libgtest_main.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_ResourcePool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_archive.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_buffer.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_check_cast.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_exception.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_pool.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_utils.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_implement.a \
  ../../../../../../../../lib2-64/bsl/lib/libbsl_var_utils.a \
  ../../../../../../../../lib2-64/ccode/lib/libulccode.a \
  ../../../../../../../../lib2-64/dict/lib/libuldict.a \
  ../../../../../../../../lib2-64/libcrf/lib/libcrf.a \
  ../../../../../../../../lib2-64/nlp/compact-trie/lib/libctrie.a \
  ../../../../../../../../lib2-64/others-ex/lib/libullib_ex.a \
  ../../../../../../../../lib2-64/postag/lib/libpostag.a \
  ../../../../../../../../lib2-64/text-util/lib/libtextutil.a \
  ../../../../../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../../../../../lib2-64/wordseg/libsegment.a \
  ../../../../../../../../ps/se/dict-set/libdictset.a \
  ../../../../../../../../public/comlog-plugin/libcomlog.a \
  ../../../../../../../../public/comlog-plugin/output/lib/libdfsappender.a \
  ../../../../../../../../public/configure/libconfig.a \
  ../../../../../../../../public/connectpool/libconnectpool.a \
  ../../../../../../../../public/odict/libodict.a \
  ../../../../../../../../public/spreg/libspreg.a \
  ../../../../../../../../public/uconv/libuconv.a \
  ../../../../../../../../public/urlparser/libnewurl.a \
  ../../../../../../../../quality/autotest/reportlib/cpp/libautotest.a \
  ../../../../../../../../st/nlp/lm-score/output/lib/libScoreCal.a \
  ../../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../../third-64/boost/lib/libboost_wserialization.a \
  ../../../../../../../../third-64/gflags/lib/libgflags.a \
  ../../../../../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../../../../../third-64/glog/lib/libglog.a \
  ../../../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a \
  ../../../../../../../../third-64/zlib/lib/libz.a -lpthread \
  -lrt \
  -ldl \
  -lldap \
  -lcurl \
  -rdynamic \
  -lssl \
  -lcrypto \
  -lgomp -Xlinker "-)" -o test_langmodel
	mkdir -p ./output/bin
	cp -f --link test_langmodel ./output/bin

liburate_train.a:src/urate_train_urate_train.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mliburate_train.a[0m']"
	ar crs liburate_train.a src/urate_train_urate_train.o
	mkdir -p ./output/lib
	cp -f --link liburate_train.a ./output/lib

get_urate_infos_get_urate_infos.o:get_urate_infos.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mget_urate_infos_get_urate_infos.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o get_urate_infos_get_urate_infos.o get_urate_infos.cc

urate_train_urate_train.o:urate_train.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40murate_train_urate_train.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o urate_train_urate_train.o urate_train.cc

urate_predicts_from_file_urate_predicts_from_file.o:urate_predicts_from_file.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40murate_predicts_from_file_urate_predicts_from_file.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o urate_predicts_from_file_urate_predicts_from_file.o urate_predicts_from_file.cc

urate_reducer_urate_reducer.o:urate_reducer.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40murate_reducer_urate_reducer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o urate_reducer_urate_reducer.o urate_reducer.cc

img_reducer_img_reducer.o:img_reducer.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mimg_reducer_img_reducer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o img_reducer_img_reducer.o img_reducer.cc

lou_reducer_lou_reducer.o:lou_reducer.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlou_reducer_lou_reducer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o lou_reducer_lou_reducer.o lou_reducer.cc

test_langmodel_test_langmodel.o:test_langmodel.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_langmodel_test_langmodel.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_langmodel_test_langmodel.o test_langmodel.cc

src/urate_train_urate_train.o:src/urate_train.cpp
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/urate_train_urate_train.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o src/urate_train_urate_train.o src/urate_train.cpp

endif #ifeq ($(shell uname -m),x86_64)


