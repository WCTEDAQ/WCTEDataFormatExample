ToolFrameworkPath=../WCTEDAQ/Dependencies/ToolFrameworkCore

CXXFLAGS ?= -O3 -pipe

.PHONY: clean test

Example: main.o
	g++ -o $@ $^ -L $(ToolFrameworkPath)/lib -lStore

main.o: main.cpp WCTERawData.h TriggerType.h ReadoutWindow.h WCTEMPMTHit.h WCTEMPMTWaveform.h \
  WCTEMPMTLED.h HKMPMTHit.h TDCHit.h BitFunctions.h QDCHit.h DAQInfo.h
	g++ -O3 -c $< -I . -I $(ToolFrameworkPath)/include

test-bits: test-bits.o
	g++ -o $@ $^ -L $(ToolFrameworkPath)/lib -lStore

test-bits.o: test-bits.cpp DAQHeader.h HKMPMTHit.h QDCHit.h TDCHit.h WCTEMPMTHit.h \
  WCTEMPMTLED.h WCTEMPMTPPS.h WCTEMPMTWaveform.h BitFunctions.h
	g++ -O3 -c $< -I . -I $(ToolFrameworkPath)/include

rawread: rawread.cpp 
	 g++ -O3  -o $@ $^ -I . -I $(ToolFrameworkPath)/include -L $(ToolFrameworkPath)/lib -lStore

rawread2: rawread2.cpp 
	 g++ -O3  -o $@ $^ -I . -I $(ToolFrameworkPath)/include -L $(ToolFrameworkPath)/lib -lStore -I ../WCTEDAQ/DataModel

clean:
	rm -f Example main.o test-bits test-bits.o

test: test-bits
	LD_LIBRARY_PATH=$(ToolFrameworkPath)/lib ./test-bits 0xffffffffffffffff 0xbaad1337deadbeef 0x1234567890abcdef 0x499602d2
