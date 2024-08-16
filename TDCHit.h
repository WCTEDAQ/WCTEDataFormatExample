#ifndef TDC_HIT_H
#define TDC_HIT_H

#include <iostream>
#include <BitFunctions.h>

class TDCHit{
  
public:
  TDCHit() {
    std::fill(std::begin(data), std::end(data), 0);
  };
  
  TDCHit(
      uint32_t header,
      uint32_t measurement,
      uint32_t extended_time,
      uint32_t trailer
  ) {
    data[6] = 0;
    init(header, measurement);
    SetExtendedTime(bits<0, 26>(extended_time) << 5 | bits<0, 4>(trailer));
  };

  // When extended trigger time tag is disabled, trailer is not needed
  TDCHit(uint32_t header, uint32_t measurement) {
    std::fill(data + 6, std::end(data), 0);
    init(header, measurement);
  };

  uint32_t GetValue() const {
    return bits<0, 20>(data);
  };

  void SetValue(uint32_t value) {
    set_bits<0, 20>(data, value);
  };

  uint8_t GetGEO() const {
    return bits<21, 25>(data);
  };

  void SetGEO(uint8_t geo) {
    set_bits<21, 25>(data, geo);
  };

  bool GetTrailing() const {
    return bits<26, 26>(data);
  };

  void SetTrailing(bool trailing) {
    set_bits<26, 26>(data, trailing);
  };

  uint8_t GetChannel() const {
    return bits<27, 31>(data);
  };

  void SetChannel(uint8_t channel) {
    set_bits<27, 31>(data, channel);
  };

  uint32_t GetEvent() const {
    return bits<32, 53>(data);
  };

  void SetEvent(uint32_t event) {
    set_bits<32, 53>(data, event);
  };

  uint32_t GetExtendedTime() const {
    return bits<56, 87>(data);
  };

  void SetExtendedTime(uint32_t time) {
    set_bits<56, 87>(data, time);
  };

  void Print(std::ostream& output = std::cout) const {
    output << "value = " << GetValue() << std::endl;
    output << "geo = " << static_cast<int>(GetGEO()) << std::endl;
    output << "trailing = " << GetTrailing() << std::endl;
    output << "channel = " << GetChannel() << std::endl;
    output << "event = " << GetEvent() << std::endl;
    output << "extended_time = " << GetExtendedTime() << std::endl;
  };

private:
  /* bits     width   field
   *  0 - 20  21      value
   * 21 - 25   5      geo
   * 26 - 26   1      trailing
   * 27 - 31   5      channel
   * 32 - 53  22      event
   * 56 - 87  32      extended trigger time tag
   
      01234567
    0 vvvvvvvv          0 = reserved
    1 vvvvvvvv          v = value
    2 vvvvvggg          g = geo
    3 ggtccccc          t = trailing
    4 EEEEEEEE          c = channel
    5 EEEEEEEE          E = event
    6 EEEEEE00          T = extended trigger time tag
    7 TTTTTTTT
    8 TTTTTTTT
    9 TTTTTTTT
   10 TTTTTTTT
  */
  uint8_t data[11];

  void init(uint32_t header, uint32_t measurement) {
    SetGEO(bits<0, 4>(header));
    SetEvent(bits<5, 26>(header));
    SetValue(bits<0, 20>(measurement));
    SetChannel(bits<21, 25>(measurement));
    SetTrailing(bits<26, 26>(measurement));
  };
};


#endif
