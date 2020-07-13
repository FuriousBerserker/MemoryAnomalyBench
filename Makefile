CC=clang
CXX=clang++
DISASSEMBLER=llvm-dis
FLAGS_OPENMP=-fopenmp
FLAGS_GPU=${FLAGS_OFFLOAD_OPENMP}
FLAGS_CPU=-fopenmp-targets=x86_64-pc-linux-gnu
CFLAGS+=-g -O0
CXXFLAGS+=-std=c++11 -g
IRFLAGS=-c -emit-llvm -v --save-temps

PREFIX=app
#SRC=$(PREFIX)$(TEST_CASE).c
TARGET_FLAGS=$(FLAGS_$(TARGET))
LIBRARY_TSAN_FLAG=-fsanitize=thread
LIBRARY_ASAN_FLAG=-fsanitize=address -fno-omit-frame-pointer
LIBRARY_MSAN_FLAG=-fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -fsanitize-memory-track-origins=2


ALL_TEST_CASES:=$(sort $(wildcard MAOMP_OMP_*.cc))

all: $(patsubst %.cc,%.tsan.sanity_check.exe,$(ALL_TEST_CASES)) $(patsubst %.cc,%.asan.sanity_check.exe,$(ALL_TEST_CASES)) \
	$(patsubst %.cc,%.msan.sanity_check.exe,$(ALL_TEST_CASES)) $(patsubst %.c,%.exe,$(ALL_TEST_CASES)) native

native: $(patsubst %.cc,%.exe,$(ALL_TEST_CASES))

%.tsan.sanity_check.exe: %.cc
	$(CXX) $(CFLAGS) $(FLAGS_OPENMP)  $(LIBRARY_TSAN_FLAG) $< -o $@

%.asan.sanity_check.exe: %.cc
	$(CXX) $(CFLAGS) $(FLAGS_OPENMP)  $(LIBRARY_ASAN_FLAG) $< -o $@

%.msan.sanity_check.exe: %.cc
	$(CXX) $(CFLAGS) $(FLAGS_OPENMP)  $(LIBRARY_MSAN_FLAG) $< -o $@

%.exe: %.cc
	$(CXX) $(CFLAGS) $(FLAGS_OPENMP) $(TARGET_FLAGS) $< -o $@

.PHONY: run
run: $(APP) libtool.so
	env LD_LIBRARY_PATH=$(LD_LIBRARY_PATH_$(MODE))  OMP_TOOL_LIBRARIES=$(PWD)/libtool.so $<

.PHONY: run-notool
run-notool: $(APP)
	env LD_LIBRARY_PATH=$(LD_LIBRARY_PATH_$(MODE)) $<
    
.PHONY: run-sanitizer
run-sanitizer: $(APP_FOR_SANITY_CHECK)
	env LD_LIBRARY_PATH=$(LD_LIBRARY_PATH_$(MODE)) $<

.PHONY: dump_ir
dump_ir: $(SRC)
	$(CC) $(CFLAGS) $(FLAGS_OPENMP) $(TARGET_FLAGS) $(IRFLAGS) $<

.PHONY: clean
clean:
	$(RM) libtool.so *.exe *~ *.o *.bc *.i *.ll *.so

.PHONY: help
help:
	$(info )
	$(info $(SINGLE_APP_HELP))
	$(info $(ALL_APP_HELP))
