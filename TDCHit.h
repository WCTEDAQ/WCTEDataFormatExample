#ifndef TDC_HIT_H
#define TDC_HIT_H

#include <iostream>
#include <BitFunctions.h>

class TDCHit{
  
public:
  TDCHit() {
    std::fill(std::begin(data), std::end(data), 0);
  };
  
  TDCHit(uint32_t header, uint32_t measurement, uint32_t extended_time) {
    std::fill(std::begin(data), std::end(data), 0);
    SetGEO(bits<0, 4>(header));
    SetEvent(bits<5, 26>(header));
    SetMeasurement(bits<0, 20>(measurement));
    SetChannel(bits<21, 25>(measurement));
    SetTrailing(bits<26, 26>(measurement));
    SetExtendedTime(bits<0, 26>(extended_time));
  };
  
  uint32_t GetMeasurement() const {
    return bits<0, 20>(data);
  };
  
  void SetMeasurement(uint32_t measurement) {
    set_bits<0, 20>(data, measurement);
  };
  
  uint32_t GetExtendedTime() const {
    return bits<21, 47>(data);
  };
  
  void SetExtendedTime(uint32_t time) {
    set_bits<21, 47>(data, time);
  };

  uint64_t GetValue() const {
    return bits<0, 47>(data);
  };
  
  void SetValue(uint64_t value) {
    set_bits<0, 47>(data, value);
  };
  
  uint32_t GetEvent() const {
    return bits<48, 69>(data);
  };
  
  void SetEvent(uint32_t event) {
    set_bits<48, 69>(data, event);
  };
  
  uint16_t GetChannel() const {
    return bits<72, 76>(data);
  };
  
  void SetChannel(uint8_t channel) {
    set_bits<72, 76>(data, channel);
  };
  
  bool GetTrailing() const {
    return bits<77, 77>(data);
  };
  
  void SetTrailing(bool trailing) {
    set_bits<77, 77>(data, trailing);
  };

  uint8_t GetGEO() const {
    return bits<80, 84>(data);
  };
  
  void SetGEO(uint8_t geo) {
    set_bits<80, 84>(data, geo);
  };
  
  void Print(std::ostream& output = std::cout) const {
    output << "measurement = " << GetMeasurement() << std::endl;
    output << "extended_time = " << GetExtendedTime() << std::endl;
    output << "value = " << GetValue() << std::endl;
    output << "event = " << GetEvent() << std::endl;
    output << "channel = " << GetChannel() << std::endl;
    output << "trailing = " << GetTrailing() << std::endl;
    output << "geo = " << static_cast<int>(GetGEO()) << std::endl;
  };

private:
  /* bits     width   field
   *  0 - 20  21      measurement
   * 21 - 47  27      extended time
   * 48 - 69  22      event
   * 72 - 76   5      channel
   * 77 - 77   1      trailing
   * 80 - 84   5      geo
   
      01234567
    0 mmmmmmmm         0 = zero
    1 mmmmmmmm         m = measurement
    2 mmmmmTTT         c = channel
    3 TTTTTTTT         t = trailing
    4 TTTTTTTT         C = event
    5 TTTTTTTT         T = extended time
    6 CCCCCCCC
    7 CCCCCCCC
    8 CCCCCC00
    9 ccccct00
   10 ggggg000
  */
  uint8_t data[11];
};


#endif
