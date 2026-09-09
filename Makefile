CXX?=g++
LIBHERBCEPTIONSPATH?=

all: bin/runtests bin/runtests_googlebench

bin/%.o: %.cpp
	@mkdir -p bin
	$(CXX) -O3 -std=c++26 -c -W -Wall $(CXXFLAGS-$(basename $@)) -o$@ $<

bin/runtests: bin/main.o bin/exceptions.o bin/leaf.o bin/expected.o bin/herbceptionemulation.o bin/herbceptions.o bin/herbceptionsreal.o bin/outcome.o bin/baseline.o
	$(CXX) -o$@ $^ -L$(LIBHERBCEPTIONSPATH)/lib -lherbceptions

bin/benchmark/src/libbenchmark.a:
	@mkdir -p bin/benchmark
	cmake -E chdir bin/benchmark cmake -DBENCHMARK_ENABLE_TESTING=OFF -DBENCHMARK_ENABLE_EXCEPTIONS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_POSITION_INDEPENDENT_CODE=On ../../thirdparty/benchmark
	cmake --build bin/benchmark --config Release --target benchmark

bin/runtests_googlebench: bin/main_googlebench.o bin/exceptions.o bin/leaf.o bin/expected.o bin/herbceptionemulation.o bin/herbceptions.o bin/herbceptionsreal.o bin/outcome.o bin/baseline.o bin/benchmark/src/libbenchmark.a
	$(CXX) -o$@ $^ $(LDFLAGS-$(basename $@))

CXXFLAGS-bin/leaf:=-w -fno-exceptions -O2 -DNDEBUG -DBOOST_LEAF_CFG_DIAGNOSTICS=0 -DBOOST_LEAF_CFG_CAPTURE=0
CXXFLAGS-bin/herbceptionemulation:=-fno-exceptions
CXXFLAGS-bin/herbceptions:=-fno-exceptions
CXXFLAGS-bin/herbceptionsreal:=-fno-exceptions -fno-rtti -fherbceptions -lherbceptions -L$(LIBHERBCEPTIONSPATH)/lib -I$(LIBHERBCEPTIONSPATH)/include
CXXFLAGS-bin/outcome:=-fno-exceptions
CXXFLAGS-bin/baseline:=-fno-exceptions
CXXFLAGS-bin/main_googlebench:=-Ithirdparty/benchmark/include
LDFLAGS-bin/runtests_googlebench:=-Lbin/benchmark/src -lbenchmark -L$(LIBHERBCEPTIONSPATH)/lib -lherbceptions
