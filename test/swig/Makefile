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
DEP_INCPATH=

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=c9a3a865fe62c6f8370231d571449c9a  COMAKE


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
	rm -rf chg_chg_wrap.o
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

libchg.so:chg_chg_wrap.o \
  chg_chg.o \
  ./lib/libpython2.7.so
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibchg.so[0m']"
	$(CXX) -shared chg_chg_wrap.o \
  chg_chg.o -Xlinker "-(" ./lib/libpython2.7.so  -rdynamic \
  -L./ \
  -L./lib \
  -lpython2.7 \
  -Wl,-rpath=./ \
  -lgomp -Xlinker "-)" -o libchg.so
	mkdir -p ./output/so
	cp -f --link libchg.so ./output/so

chg_chg_wrap.o:chg_wrap.cxx
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mchg_chg_wrap.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DPYTHON_WRAPPER \
  -DNDEBUG $(CXXFLAGS)  -o chg_chg_wrap.o chg_wrap.cxx

chg_chg.o:chg.cc
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mchg_chg.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DPYTHON_WRAPPER \
  -DNDEBUG $(CXXFLAGS)  -o chg_chg.o chg.cc

endif #ifeq ($(shell uname -m),x86_64)


