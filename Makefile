CXX=g++
CXFLAGS=-std=c++11 -g #-O3 -Wall

CBDEPS_DIR=/Users/$(USER)/.cbdepscache/
DYLD_LIBRARY_PATH=/Users/$(USER)/.cbdepscache/lib
CMD_DIR=cmd/producer/

LDFLAGS=-luv -ljemalloc -L$(CBDEPS_DIR)lib/debug/ -lv8

SOURCES=consumer/src/client.cc consumer/src/commands.cc \
				consumer/src/message.cc consumer/src/v8worker.cc

INCLUDE_DIRS=-I$(CBDEPS_DIR) -I/usr/local/include/hiredis -I consumer/include/

OUT=$(CMD_DIR)client.bin

build:
	$(CXX) $(CXFLAGS) $(SOURCES) $(INCLUDE_DIRS) $(LDFLAGS) -o $(OUT)
	cd $(CMD_DIR); go build

allopt:
	$(CXX) $(CXFLAGS) $(SOURCES) $(INCLUDE_DIRS) $(LDFLAGS) -O3 -o $(OUT)
	cd $(CMD_DIR); go build
	cd $(CMD_DIR); ./producer -kv 127.0.0.1:11210 -n 127.0.0.1:8091

run: build
	cd $(CMD_DIR); ./producer -kv 127.0.0.1:11210 -n 127.0.0.1:8091

clean:
	rm -rf $(OUT)
