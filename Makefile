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
  -I./third \
  -I./third/folly \
  -I./third/double-conversion/ \
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
COMAKE_MD5=c8434bb2f8655c038270d40c93ac8489  COMAKE


.PHONY:all
all:comake2_makefile_check libgezi_cppformat.a copy-pinyin-lib libgezi_common.a libgezi_json.a copy-cppformat copy-eigen copy-folly copy-double-conversion 
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
	rm -rf copy-cppformat
	rm -rf output/cppformat
	rm -rf copy-eigen
	rm -rf output/Eigen
	rm -rf copy-folly
	rm -rf output/folly
	rm -rf copy-double-conversion
	rm -rf output/double-conversion/
	rm -rf third/cppformat/gezi_cppformat_format.o
	rm -rf third/cppformat/gezi_cppformat_posix.o
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

libgezi_cppformat.a:third/cppformat/gezi_cppformat_format.o \
  third/cppformat/gezi_cppformat_posix.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibgezi_cppformat.a[0m']"
	ar crs libgezi_cppformat.a third/cppformat/gezi_cppformat_format.o \
  third/cppformat/gezi_cppformat_posix.o
	mkdir -p ./output/lib
	cp -f libgezi_cppformat.a ./output/lib

copy-pinyin-lib:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcopy-pinyin-lib[0m']"
	mkdir -p output/lib
	cp ./include/tools/pinyin/libPYNotation.a ./output/lib/

libgezi_common.a:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibgezi_common.a[0m']"
	ar crs libgezi_common.a 
	mkdir -p ./output/lib
	cp -f libgezi_common.a ./output/lib

libgezi_json.a:src/json/gezi_json_json_reader.o \
  src/json/gezi_json_json_value.o \
  src/json/gezi_json_json_writer.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibgezi_json.a[0m']"
	ar crs libgezi_json.a src/json/gezi_json_json_reader.o \
  src/json/gezi_json_json_value.o \
  src/json/gezi_json_json_writer.o
	mkdir -p ./output/lib
	cp -f libgezi_json.a ./output/lib

copy-cppformat:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcopy-cppformat[0m']"
	mkdir -p output/cppformat
	cp -rf third/cppformat/*.h output/cppformat

copy-eigen:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcopy-eigen[0m']"
	mkdir -p output/Eigen
	cp -rf third/Eigen/* output/Eigen

copy-folly:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcopy-folly[0m']"
	mkdir -p output/folly
	cp -rf third/folly/folly/* output/folly

copy-double-conversion:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcopy-double-conversion[0m']"
	mkdir -p output/double-conversion
	cp -rf third/double-conversion/double-conversion/* output/double-conversion

third/cppformat/gezi_cppformat_format.o:third/cppformat/format.cc \
  third/cppformat/format.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mthird/cppformat/gezi_cppformat_format.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o third/cppformat/gezi_cppformat_format.o third/cppformat/format.cc

third/cppformat/gezi_cppformat_posix.o:third/cppformat/posix.cc \
  third/cppformat/posix.h \
  third/cppformat/format.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mthird/cppformat/gezi_cppformat_posix.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -O3 \
  -DNDEBUG $(CXXFLAGS)  -o third/cppformat/gezi_cppformat_posix.o third/cppformat/posix.cc

src/json/gezi_json_json_reader.o:src/json/json_reader.cpp \
  include/json/reader.h \
  include/json/features.h \
  include/json/forwards.h \
  include/json/config.h \
  include/json/value.h \
  include/json/value.h \
  src/json/json_tool.h \
  include/encoding_convert.h \
  include/string_def.h \
  include/encoding_def.h \
  include/common_define.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_json_reader.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -DNDEBUG $(CXXFLAGS)  -o src/json/gezi_json_json_reader.o src/json/json_reader.cpp

src/json/gezi_json_json_value.o:src/json/json_value.cpp \
  include/common_util.h \
  include/common_def.h \
  include/format.h \
  include/common_define.h \
  third/cppformat/format.h \
  include/convert_type.h \
  include/hashmap_util.h \
  third/folly/folly/Foreach.h \
  third/folly/folly/small_vector.h \
  third/folly/folly/FormatTraits.h \
  third/folly/folly/Malloc.h \
  third/folly/folly/detail/Malloc.h \
  third/folly/folly/Portability.h \
  third/folly/folly/CPortability.h \
  third/folly/folly/detail/FunctionalExcept.h \
  third/folly/folly/SmallLocks.h \
  third/folly/folly/MicroSpinLock.h \
  third/folly/folly/detail/Sleeper.h \
  third/folly/folly/PicoSpinLock.h \
  third/folly/folly/MapUtil.h \
  third/folly/folly/Conv.h \
  third/folly/folly/FBString.h \
  third/folly/folly/Traits.h \
  third/folly/folly/Hash.h \
  third/folly/folly/SpookyHashV1.h \
  third/folly/folly/SpookyHashV2.h \
  third/folly/folly/ScopeGuard.h \
  third/folly/folly/Preprocessor.h \
  third/folly/folly/detail/UncaughtExceptionCounter.h \
  third/folly/folly/Likely.h \
  third/folly/folly/Range.h \
  third/folly/folly/CpuId.h \
  third/double-conversion/double-conversion/double-conversion.h \
  third/double-conversion/double-conversion/utils.h \
  third/folly/folly/Optional.h \
  third/folly/folly/FBVector.h \
  third/folly/folly/Memory.h \
  include/vector_def.h \
  include/string_def.h \
  include/string_util.h \
  include/encoding_convert.h \
  include/encoding_def.h \
  include/wstring_util.h \
  include/reg_util.h \
  include/stl_util.h \
  include/map_util.h \
  include/log_util.h \
  include/conf_util.h \
  include/debug_util.h \
  include/Exception.h \
  include/serialize_util.h \
  include/serialize_cereal.h \
  include/cereal/types/unordered_map.hpp \
  include/cereal/cereal.hpp \
  include/cereal/macros.hpp \
  include/cereal/details/traits.hpp \
  include/cereal/access.hpp \
  include/cereal/details/helpers.hpp \
  include/cereal/details/static_object.hpp \
  include/cereal/types/base_class.hpp \
  include/cereal/types/common.hpp \
  include/cereal/types/unordered_set.hpp \
  include/cereal/types/deque.hpp \
  include/cereal/types/vector.hpp \
  include/cereal/types/map.hpp \
  include/cereal/types/set.hpp \
  include/cereal/types/list.hpp \
  include/cereal/types/string.hpp \
  include/cereal/types/memory.hpp \
  include/cereal/types/polymorphic.hpp \
  include/cereal/details/util.hpp \
  include/cereal/details/polymorphic_impl.hpp \
  include/cereal/archives/binary.hpp \
  include/cereal/archives/json.hpp \
  include/cereal/external/rapidjson/prettywriter.h \
  include/cereal/external/rapidjson/writer.h \
  include/cereal/external/rapidjson/rapidjson.h \
  include/cereal/external/rapidjson/internal/stack.h \
  include/cereal/external/rapidjson/internal/strfunc.h \
  include/cereal/external/rapidjson/genericstream.h \
  include/cereal/external/rapidjson/reader.h \
  include/cereal/external/rapidjson/internal/pow10.h \
  include/cereal/external/rapidjson/document.h \
  include/cereal/external/rapidjson/reader.h \
  include/cereal/external/base64.hpp \
  include/cereal/archives/xml.hpp \
  include/cereal/external/rapidxml/rapidxml.hpp \
  include/cereal/external/rapidxml/rapidxml_print.hpp \
  include/cereal/external/rapidxml/rapidxml.hpp \
  include/cereal/types/eigen.hpp \
  third/Eigen/Dense \
  third/Eigen/Core \
  third/Eigen/src/Core/util/DisableStupidWarnings.h \
  third/Eigen/src/Core/util/Macros.h \
  third/Eigen/src/Core/util/MKL_support.h \
  third/Eigen/src/Core/util/Constants.h \
  third/Eigen/src/Core/util/ForwardDeclarations.h \
  third/Eigen/src/Core/util/Meta.h \
  third/Eigen/src/Core/util/StaticAssert.h \
  third/Eigen/src/Core/util/XprHelper.h \
  third/Eigen/src/Core/util/Memory.h \
  third/Eigen/src/Core/NumTraits.h \
  third/Eigen/src/Core/MathFunctions.h \
  third/Eigen/src/Core/GenericPacketMath.h \
  third/Eigen/src/Core/arch/SSE/PacketMath.h \
  third/Eigen/src/Core/arch/SSE/MathFunctions.h \
  third/Eigen/src/Core/arch/SSE/Complex.h \
  third/Eigen/src/Core/arch/Default/Settings.h \
  third/Eigen/src/Core/Functors.h \
  third/Eigen/src/Core/DenseCoeffsBase.h \
  third/Eigen/src/Core/DenseBase.h \
  third/Eigen/src/plugins/BlockMethods.h \
  third/Eigen/src/Core/MatrixBase.h \
  third/Eigen/src/plugins/CommonCwiseUnaryOps.h \
  third/Eigen/src/plugins/CommonCwiseBinaryOps.h \
  third/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
  third/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
  third/Eigen/src/Core/EigenBase.h \
  third/Eigen/src/Core/Assign.h \
  third/Eigen/src/Core/util/BlasUtil.h \
  third/Eigen/src/Core/DenseStorage.h \
  third/Eigen/src/Core/NestByValue.h \
  third/Eigen/src/Core/ForceAlignedAccess.h \
  third/Eigen/src/Core/ReturnByValue.h \
  third/Eigen/src/Core/NoAlias.h \
  third/Eigen/src/Core/PlainObjectBase.h \
  third/Eigen/src/Core/Matrix.h \
  third/Eigen/src/Core/Array.h \
  third/Eigen/src/Core/CwiseBinaryOp.h \
  third/Eigen/src/Core/CwiseUnaryOp.h \
  third/Eigen/src/Core/CwiseNullaryOp.h \
  third/Eigen/src/Core/CwiseUnaryView.h \
  third/Eigen/src/Core/SelfCwiseBinaryOp.h \
  third/Eigen/src/Core/Dot.h \
  third/Eigen/src/Core/StableNorm.h \
  third/Eigen/src/Core/MapBase.h \
  third/Eigen/src/Core/Stride.h \
  third/Eigen/src/Core/Map.h \
  third/Eigen/src/Core/Block.h \
  third/Eigen/src/Core/VectorBlock.h \
  third/Eigen/src/Core/Ref.h \
  third/Eigen/src/Core/Transpose.h \
  third/Eigen/src/Core/DiagonalMatrix.h \
  third/Eigen/src/Core/Diagonal.h \
  third/Eigen/src/Core/DiagonalProduct.h \
  third/Eigen/src/Core/PermutationMatrix.h \
  third/Eigen/src/Core/Transpositions.h \
  third/Eigen/src/Core/Redux.h \
  third/Eigen/src/Core/Visitor.h \
  third/Eigen/src/Core/Fuzzy.h \
  third/Eigen/src/Core/IO.h \
  third/Eigen/src/Core/Swap.h \
  third/Eigen/src/Core/CommaInitializer.h \
  third/Eigen/src/Core/Flagged.h \
  third/Eigen/src/Core/ProductBase.h \
  third/Eigen/src/Core/GeneralProduct.h \
  third/Eigen/src/Core/TriangularMatrix.h \
  third/Eigen/src/Core/SelfAdjointView.h \
  third/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
  third/Eigen/src/Core/products/Parallelizer.h \
  third/Eigen/src/Core/products/CoeffBasedProduct.h \
  third/Eigen/src/Core/products/GeneralMatrixVector.h \
  third/Eigen/src/Core/products/GeneralMatrixMatrix.h \
  third/Eigen/src/Core/SolveTriangular.h \
  third/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
  third/Eigen/src/Core/products/SelfadjointMatrixVector.h \
  third/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
  third/Eigen/src/Core/products/SelfadjointProduct.h \
  third/Eigen/src/Core/products/SelfadjointRank2Update.h \
  third/Eigen/src/Core/products/TriangularMatrixVector.h \
  third/Eigen/src/Core/products/TriangularMatrixMatrix.h \
  third/Eigen/src/Core/products/TriangularSolverMatrix.h \
  third/Eigen/src/Core/products/TriangularSolverVector.h \
  third/Eigen/src/Core/BandMatrix.h \
  third/Eigen/src/Core/CoreIterators.h \
  third/Eigen/src/Core/BooleanRedux.h \
  third/Eigen/src/Core/Select.h \
  third/Eigen/src/Core/VectorwiseOp.h \
  third/Eigen/src/Core/Random.h \
  third/Eigen/src/Core/Replicate.h \
  third/Eigen/src/Core/Reverse.h \
  third/Eigen/src/Core/ArrayBase.h \
  third/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
  third/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
  third/Eigen/src/Core/ArrayWrapper.h \
  third/Eigen/src/Core/GlobalFunctions.h \
  third/Eigen/src/Core/util/ReenableStupidWarnings.h \
  third/Eigen/LU \
  third/Eigen/src/misc/Solve.h \
  third/Eigen/src/misc/Kernel.h \
  third/Eigen/src/misc/Image.h \
  third/Eigen/src/LU/FullPivLU.h \
  third/Eigen/src/LU/PartialPivLU.h \
  third/Eigen/src/LU/Determinant.h \
  third/Eigen/src/LU/Inverse.h \
  third/Eigen/src/LU/arch/Inverse_SSE.h \
  third/Eigen/Cholesky \
  third/Eigen/src/Cholesky/LLT.h \
  third/Eigen/src/Cholesky/LDLT.h \
  third/Eigen/QR \
  third/Eigen/Jacobi \
  third/Eigen/src/Jacobi/Jacobi.h \
  third/Eigen/Householder \
  third/Eigen/src/Householder/Householder.h \
  third/Eigen/src/Householder/HouseholderSequence.h \
  third/Eigen/src/Householder/BlockHouseholder.h \
  third/Eigen/src/QR/HouseholderQR.h \
  third/Eigen/src/QR/FullPivHouseholderQR.h \
  third/Eigen/src/QR/ColPivHouseholderQR.h \
  third/Eigen/SVD \
  third/Eigen/src/SVD/JacobiSVD.h \
  third/Eigen/src/SVD/UpperBidiagonalization.h \
  third/Eigen/Geometry \
  third/Eigen/src/Geometry/OrthoMethods.h \
  third/Eigen/src/Geometry/EulerAngles.h \
  third/Eigen/src/Geometry/Homogeneous.h \
  third/Eigen/src/Geometry/RotationBase.h \
  third/Eigen/src/Geometry/Rotation2D.h \
  third/Eigen/src/Geometry/Quaternion.h \
  third/Eigen/src/Geometry/AngleAxis.h \
  third/Eigen/src/Geometry/Transform.h \
  third/Eigen/src/Geometry/Translation.h \
  third/Eigen/src/Geometry/Scaling.h \
  third/Eigen/src/Geometry/Hyperplane.h \
  third/Eigen/src/Geometry/ParametrizedLine.h \
  third/Eigen/src/Geometry/AlignedBox.h \
  third/Eigen/src/Geometry/Umeyama.h \
  third/Eigen/src/Geometry/arch/Geometry_SSE.h \
  third/Eigen/Eigenvalues \
  third/Eigen/src/Eigenvalues/Tridiagonalization.h \
  third/Eigen/src/Eigenvalues/RealSchur.h \
  third/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
  third/Eigen/src/Eigenvalues/EigenSolver.h \
  third/Eigen/src/Eigenvalues/RealSchur.h \
  third/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
  third/Eigen/src/Eigenvalues/Tridiagonalization.h \
  third/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
  third/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
  third/Eigen/src/Eigenvalues/ComplexSchur.h \
  third/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
  third/Eigen/src/Eigenvalues/ComplexSchur.h \
  third/Eigen/src/Eigenvalues/RealQZ.h \
  third/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
  third/Eigen/src/Eigenvalues/RealQZ.h \
  third/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
  include/Matrix.h \
  include/sort_util.h \
  include/statistic_util.h \
  include/common_util.h \
  include/Numeric/find_bins.h \
  include/common_def.h \
  include/sort_util.h \
  include/datetime_util.h \
  include/time_util.h \
  include/ProgressBar.h \
  include/file_util.h \
  include/linq.h \
  include/linq/cpplinq.hpp \
  include/LoadSave.h \
  include/WithArgs.h \
  include/WithHelp.h \
  include/sort_map_by_value.h \
  include/openmp_util.h \
  include/ThreadLocalAnyMap.h \
  include/SharedAnyMap.h \
  include/Singleton.h \
  include/Identifer.h \
  include/SharedIdentifers.h \
  include/SharedObjects.h \
  include/encoding_convert.h \
  include/json/value.h \
  include/json/forwards.h \
  include/json/config.h \
  include/json/writer.h \
  include/json/value.h \
  src/json/json_batchallocator.h \
  src/json/json_valueiterator.inl
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_json_value.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -DNDEBUG $(CXXFLAGS)  -o src/json/gezi_json_json_value.o src/json/json_value.cpp

src/json/gezi_json_json_writer.o:src/json/json_writer.cpp \
  include/json/writer.h \
  include/json/value.h \
  include/json/forwards.h \
  include/json/config.h \
  src/json/json_tool.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/json/gezi_json_json_writer.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\" \
  -DNDEBUG $(CXXFLAGS)  -o src/json/gezi_json_json_writer.o src/json/json_writer.cpp

endif #ifeq ($(shell uname -m),x86_64)


