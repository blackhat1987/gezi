#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I../include \
  -I../utils \
  -I../output \
  -I../output/include \
  -I../include/feature \
  -I../include/model
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
  -I../../../../../../third-64/libcurl \
  -I../../../../../../third-64/libcurl/include \
  -I../../../../../../third-64/libcurl/output \
  -I../../../../../../third-64/libcurl/output/include \
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
COMAKE_MD5=55cd87f2113e6e676ff7a56f4e890a18  COMAKE


.PHONY:all
all:comake2_makefile_check test_bins test_datetime test_content_filter test_regex test_regex2 test_encode test_json test_escape test_other 
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
	rm -rf test_bins_test_bins.o
	rm -rf test_datetime_test_datetime.o
	rm -rf test_content_filter_test_content_filter.o
	rm -rf test_regex_test_regex.o
	rm -rf test_regex2_test_regex2.o
	rm -rf test_encode_test_encode.o
	rm -rf test_json_test_json.o
	rm -rf ../src/json/test_json_json_reader.o
	rm -rf ../src/json/test_json_json_value.o
	rm -rf ../src/json/test_json_json_writer.o
	rm -rf test_escape_test_escape.o
	rm -rf test_other_test_other.o

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

test_bins:test_bins_test_bins.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_bins[0m']"
	$(CXX) test_bins_test_bins.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_bins
	mkdir -p ./output/bin
	cp -f --link test_bins ./output/bin

test_datetime:test_datetime_test_datetime.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_datetime[0m']"
	$(CXX) test_datetime_test_datetime.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_datetime
	mkdir -p ./output/bin
	cp -f --link test_datetime ./output/bin

test_content_filter:test_content_filter_test_content_filter.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_content_filter[0m']"
	$(CXX) test_content_filter_test_content_filter.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_content_filter
	mkdir -p ./output/bin
	cp -f --link test_content_filter ./output/bin

test_regex:test_regex_test_regex.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_regex[0m']"
	$(CXX) test_regex_test_regex.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_regex
	mkdir -p ./output/bin
	cp -f --link test_regex ./output/bin

test_regex2:test_regex2_test_regex2.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_regex2[0m']"
	$(CXX) test_regex2_test_regex2.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_regex2
	mkdir -p ./output/bin
	cp -f --link test_regex2 ./output/bin

test_encode:test_encode_test_encode.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_encode[0m']"
	$(CXX) test_encode_test_encode.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_encode
	mkdir -p ./output/bin
	cp -f --link test_encode ./output/bin

test_json:test_json_test_json.o \
  ../src/json/test_json_json_reader.o \
  ../src/json/test_json_json_value.o \
  ../src/json/test_json_json_writer.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_json[0m']"
	$(CXX) test_json_test_json.o \
  ../src/json/test_json_json_reader.o \
  ../src/json/test_json_json_value.o \
  ../src/json/test_json_json_writer.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_json
	mkdir -p ./output/bin
	cp -f --link test_json ./output/bin

test_escape:test_escape_test_escape.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_escape[0m']"
	$(CXX) test_escape_test_escape.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_escape
	mkdir -p ./output/bin
	cp -f --link test_escape ./output/bin

test_other:test_other_test_other.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_other[0m']"
	$(CXX) test_other_test_other.o -Xlinker "-("  ../../../../../../com/btest/gtest/output/lib/libgtest.a \
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
  ../../../../../../third-64/libcurl/lib/libcurl.a \
  ../../../../../../third-64/pcre/lib/libpcre.a \
  ../../../../../../third-64/pcre/lib/libpcrecpp.a \
  ../../../../../../third-64/pcre/lib/libpcreposix.a \
  ../../../../../../third-64/tcmalloc/lib/libprofiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_and_profiler.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_debug.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal.a \
  ../../../../../../third-64/tcmalloc/lib/libtcmalloc_minimal_debug.a -lpthread \
  -lcrypto \
  -lrt \
  -lssl \
  -lldap \
  -lcurl -Xlinker "-)" -o test_other
	mkdir -p ./output/bin
	cp -f --link test_other ./output/bin

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

test_regex2_test_regex2.o:test_regex2.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_regex2_test_regex2.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_regex2_test_regex2.o test_regex2.cc

test_encode_test_encode.o:test_encode.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_encode_test_encode.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_encode_test_encode.o test_encode.cc

test_json_test_json.o:test_json.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_json_test_json.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_json_test_json.o test_json.cc

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

test_other_test_other.o:test_other.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mtest_other_test_other.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o test_other_test_other.o test_other.cc

endif #ifeq ($(shell uname -m),x86_64)


