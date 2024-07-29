ToolFrameworkPath=../ToolFrameworkCore

CXXFLAGS ?= -O3 -pipe

.PHONY: clean

Example: main.o
	g++ -o $@ $^ -L $(ToolFrameworkPath)/lib -lStore

main.o: main.cpp WCTERawData.h Trigger.h WCTEMPMTHit.h WCTEMPMTWaveform.h \
  WCTEMPMTLED.h HKMPMTHit.h TDCHit.h BitFunctions.h QDCHit.h DAQInfo.h
	g++ -O3 -c $< -I . -I $(ToolFrameworkPath)/include


clean:
	rm -f Example main.o
