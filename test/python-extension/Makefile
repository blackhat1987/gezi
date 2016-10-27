#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=/opt/compiler/gcc-4.8.2/bin/g++
CXX=/opt/compiler/gcc-4.8.2/bin/g++
CXXFLAGS=-g \
  -O0 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -std=c++11 \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs \
  -fopenmp
CFLAGS=-g \
  -O0 \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  -DHAVE_NETINET_IN_H \
  -Wno-unused-parameter \
  -std=c++11 \
  -fpermissive \
  -Wno-write-strings \
  -Wno-literal-suffix \
  -Wno-unused-local-typedefs \
  -fopenmp
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I/home/users/chenghuige/.jumbo//include/python2.7 \
  -I./
DEP_INCPATH=-I../../../../../../../third-64/boost \
  -I../../../../../../../third-64/boost/include \
  -I../../../../../../../third-64/boost/output \
  -I../../../../../../../third-64/boost/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=6b6ac8d0951cf6e7227fdfb8c70fe747  COMAKE


.PHONY:all
all:comake2_makefile_check libchg.so 
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
	rm -rf libchg.so
	rm -rf ./output/so/libchg.so
	rm -rf chg_chg_py.o
	rm -rf chg_chg.o

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

libchg.so:chg_chg_py.o \
  chg_chg.o \
  ./lib/libboost_python.so \
  ./lib/libpython2.7.so
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibchg.so[0m']"
	$(CXX) -shared chg_chg_py.o \
  chg_chg.o -Xlinker "-(" ./lib/libboost_python.so \
  ./lib/libpython2.7.so ../../../../../../../third-64/boost/lib/libboost_atomic.a \
  ../../../../../../../third-64/boost/lib/libboost_chrono.a \
  ../../../../../../../third-64/boost/lib/libboost_container.a \
  ../../../../../../../third-64/boost/lib/libboost_context.a \
  ../../../../../../../third-64/boost/lib/libboost_coroutine.a \
  ../../../../../../../third-64/boost/lib/libboost_date_time.a \
  ../../../../../../../third-64/boost/lib/libboost_exception.a \
  ../../../../../../../third-64/boost/lib/libboost_filesystem.a \
  ../../../../../../../third-64/boost/lib/libboost_graph.a \
  ../../../../../../../third-64/boost/lib/libboost_locale.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99f.a \
  ../../../../../../../third-64/boost/lib/libboost_math_c99l.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1f.a \
  ../../../../../../../third-64/boost/lib/libboost_math_tr1l.a \
  ../../../../../../../third-64/boost/lib/libboost_mpi.a \
  ../../../../../../../third-64/boost/lib/libboost_mpi_python.a \
  ../../../../../../../third-64/boost/lib/libboost_prg_exec_monitor.a \
  ../../../../../../../third-64/boost/lib/libboost_program_options.a \
  ../../../../../../../third-64/boost/lib/libboost_python.a \
  ../../../../../../../third-64/boost/lib/libboost_random.a \
  ../../../../../../../third-64/boost/lib/libboost_regex.a \
  ../../../../../../../third-64/boost/lib/libboost_serialization.a \
  ../../../../../../../third-64/boost/lib/libboost_signals.a \
  ../../../../../../../third-64/boost/lib/libboost_system.a \
  ../../../../../../../third-64/boost/lib/libboost_test_exec_monitor.a \
  ../../../../../../../third-64/boost/lib/libboost_thread.a \
  ../../../../../../../third-64/boost/lib/libboost_timer.a \
  ../../../../../../../third-64/boost/lib/libboost_unit_test_framework.a \
  ../../../../../../../third-64/boost/lib/libboost_wave.a \
  ../../../../../../../third-64/boost/lib/libboost_wserialization.a -rdynamic \
  -L./ \
  -L./lib \
  -lpython2.7 \
  -lboost_python \
  -Wl,-rpath=./ \
  -lgomp -Xlinker "-)" -o libchg.so
	mkdir -p ./output/so
	cp -f --link libchg.so ./output/so

chg_chg_py.o:chg_py.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mchg_chg_py.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DPYTHON_WRAPPER \
  -DNDEBUG \
  -DBOOST_BIND_PLACEHOLDERS_HPP_INCLUDED $(CXXFLAGS)  -o chg_chg_py.o chg_py.cc

chg_chg.o:chg.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mchg_chg.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DPYTHON_WRAPPER \
  -DNDEBUG \
  -DBOOST_BIND_PLACEHOLDERS_HPP_INCLUDED $(CXXFLAGS)  -o chg_chg.o chg.cc

endif #ifeq ($(shell uname -m),x86_64)


