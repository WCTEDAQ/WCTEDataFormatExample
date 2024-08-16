#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

#include <getopt.h>
#include <signal.h>

#define private public

#include "DAQHeader.h"
#include "HKMPMTHit.h"
#include "QDCHit.h"
#include "TDCHit.h"
#include "WCTEMPMTHit.h"
#include "WCTEMPMTLED.h"
#include "WCTEMPMTPPS.h"
#include "WCTEMPMTWaveform.h"

void usage(const char* argv0) {
  std::cout
    << "This program tests data packets by assigning the fields a value (a pattern) and then reading it back\n"
       "Usage: " << argv0 << " [options] [patterns...]\n"
       "Options:\n"
       "  -d or --debug:   print packet data after each assignment\n"
       "  -h or --help:    show this message\n"
       "  -r or --random:  run an infinite loop testing with random patterns. Use Ctrl-C (SIGINT) to interrupt\n"
       "  -v or --verbose: print successful tests too\n"
       "Each pattern is interpreted as an unsigned 64-bits value\n"
  ;
};

#define CLASSES_(X) \
  X(TDCHit) \
  X(QDCHit); \
  X(DAQHeader); \
  X(HKMPMTHit); \
  X(WCTEMPMTHit); \
  X(WCTEMPMTLED); \
  X(WCTEMPMTPPS); \
  X(WCTEMPMTWaveformHeader)

#define FIELDS_DAQHeader(X) \
  X(MessageNumber,    32); \
  X(CoarseCounter,    32); \
  X(CardType,          2); \
  X(CardID,           12); \
  X(NumberOfWords,    15); \
  X(PayloadEarly,      1); \
  X(DelayedPackets,    1); \
  X(Reserved,          1); \
  X(Version,           8)

#define FIELDS_HKMPMTHit(X) \
  X(Header,         2); \
  X(EventType,      4); \
  X(Channel,        5); \
  X(Flags,          5); \
  X(CoarseCounter, 32); \
  X(FineTime,      16); \
  X(Charge,        16); \
  X(QualityFactor,  8)

#define FIELDS_QDCHit(X) \
  X(Value,          12); \
  X(Overflow,        1); \
  X(UnderThreshold,  1); \
  X(GEO,             5); \
  X(Channel,         5); \
  X(Crate,           8); \
  X(Event,          24)

#define FIELDS_TDCHit(X) \
  X(Value,        21); \
  X(GEO,           5); \
  X(Trailing,      1); \
  X(Channel,       5); \
  X(Event,        22); \
  X(ExtendedTime, 27)

#define FIELDS_WCTEMPMTHit(X) \
  X(Header,         2); \
  X(EventType,      4); \
  X(Channel,        5); \
  X(Flags,          5); \
  X(CoarseCounter, 32); \
  X(FineTime,      16); \
  X(Charge,        16); \
  X(QualityFactor,  8)

#define FIELDS_WCTEMPMTLED(X) \
  X(Header,          2); \
  X(EventType,       4); \
  X(LED,             3); \
  X(Gain,            1); \
  X(DACSetting,     10); \
  X(Type,            2); \
  X(SequenceNumber, 14); \
  X(CoarseCounter,  32); \
  X(Reserved,        4);

#define FIELDS_WCTEMPMTPPS(X) \
  X(Header,                    2); \
  X(EventType,                 4); \
  X(Reserved,                  2); \
  X(PreviousPPSCoarseCounter, 64); \
  X(CurrentPPSCoarseCounter,  64)

#define FIELDS_WCTEMPMTWaveformHeader(X) \
  X(Header,         2); \
  X(Flags,          4); \
  X(CoarseCounter, 32); \
  X(Channel,        5); \
  X(NumSamples,    16); \
  X(Length,        17); \
  X(Reserved,       4)

static void print_data(const uint8_t* data, unsigned size) {
  for (unsigned i = 0; i < size; ++i) printf("%02hhx", data[i]);
  putchar('\n');
  for (unsigned i = 0; i < size; ++i) printf("%08hhb ", data[i]);
  putchar('\n');
};

static bool report(
    const char* class_,
    const char* field,
    unsigned bits,
    uint64_t expected,
    uint64_t got,
    bool verbose
) {
  uint64_t mask = (1UL << bits) - 1;
  expected = bits == 1 ? !!expected : expected & mask; // single bit is cast to bool
  got &= mask;
  if (expected == got) {
    if (verbose) std::cout << "ok\t" << class_ << "::" << field << std::endl;
    return true;
  };

  std::cout
    << class_
    << "::"
    << field
    << ": expected 0x"
    << std::hex
    << expected
    << ", got 0x"
    << got
    << std::dec
    << " ("
    << bits
    << " bits)"
    << std::endl;
  return false;
};

bool run_tests(uint64_t pattern, bool debug, bool verbose) {
  bool result = true;
  const char* class_;
#define init_field(field, bits) \
  x__.Set ## field(pattern); \
  if (debug) print_data(x__.data, sizeof(x__.data));
#define test_field(field, bits) \
  result =  report(class_, #field, bits, pattern, x__.Get ## field(), verbose) \
         && result;
#define test_class(class) \
  { \
    class_ = #class; \
    class x__; \
    if (debug) print_data(x__.data, sizeof(x__.data)); \
    FIELDS_ ## class(init_field); \
    FIELDS_ ## class(test_field); \
    if (verbose) std::cout << std::endl; \
  }
  CLASSES_(test_class);
#undef test_class
#undef test_field
#undef init_field
  return result;
};

bool sigint = false;

int main(int argc, char** argv) {
  bool debug   = false;
  bool random  = false;
  bool verbose = false;

  while (true) {
    static option options[] = {
      { "debug",   no_argument, nullptr, 'd' },
      { "help",    no_argument, nullptr, 'h' },
      { "random",  no_argument, nullptr, 'r' },
      { "verbose", no_argument, nullptr, 'v' }
    };

    int c = getopt_long(argc, argv, "dhrv", options, nullptr);
    if (c == -1) break;
    switch (c) {
      case 'd':
        debug = true;
        break;
      case 'h':
        usage(argv[0]);
        return 0;
      case 'r':
        random = true;
        break;
      case 'v':
        verbose = true;
        break;
      case '?':
        return 1;
    };
  };

  uint64_t pattern = 0xBAAD1337DEADBEEFUL;
  size_t npatterns = 0;

  bool success = true;
  if (optind >= argc) {
    if (!random) success = run_tests(pattern, debug, verbose);
  } else
    for (int i = optind; i < argc; ++i) {
      char* end;
      pattern = std::strtoul(argv[i], &end, 16);
      if (*end) {
        std::cerr << argv[0] << ": invalid pattern: " << argv[i] << std::endl;
        return 1;
      };
      std::cout << "pattern: " << std::hex << pattern << std::dec << std::endl;
      success = run_tests(pattern, debug, verbose) && success;
      ++npatterns;
    };

  if (random) {
    uint64_t seed;
    {
      std::ifstream dev_random("/dev/random", std::ios::binary);
      dev_random.read(reinterpret_cast<char*>(&seed), sizeof(seed));
    };
    std::mt19937_64 rng(seed);
    signal(SIGINT, [](int) { sigint = true; });
    while (!sigint) {
      pattern = rng();
      if (!run_tests(pattern, false, false)) {
        std::cout
          << "  when testing with pattern "
          << std::hex
          << pattern
          << std::dec
          << std::endl;
        return 1;
      };
      ++npatterns;
    };
  };

  if (npatterns) std::cout << "tested " << npatterns << " patterns\n";
  if (success) std::cout << "success\n";
  return !success;
};

// 1234567890abcdef
// 499602d2
