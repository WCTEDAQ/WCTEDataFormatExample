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
    SetGEO(bits(header, 0, 4));
    SetEvent(bits(header, 5, 26));
    SetMeasurement(bits(measurement, 0, 20));
    SetChannel(bits(measurement, 21, 25));
    SetTrailing(bits(measurement, 26, 26));
    SetExtendedTime(bits(extended_time, 0, 26));
  };
  
  uint32_t GetMeasurement() const {
    return bits(data, 0, 20);
  };
  
  void SetMeasurement(uint32_t measurement) {
    set_bits(data, 0, 20, measurement);
  };
  
  uint32_t GetExtendedTime() const {
    return bits(data, 21, 47);
  };
  
  void SetExtendedTime(uint32_t time) {
    set_bits(data, 21, 47, time);
  };

  uint64_t GetValue() const {
    return bits(data, 0, 47);
  };
  
  void SetValue(uint64_t value) {
    set_bits(data, 0, 47, value);
  };
  
  uint32_t GetEvent() const {
    return bits(data, 48, 69);
  };
  
  void SetEvent(uint32_t event) {
    set_bits(data, 48, 69, event);
  };
  
  uint16_t GetChannel() const {
    return bits(data, 72, 76);
  };
  
  void SetChannel(uint8_t channel) {
    set_bits(data, 72, 76, channel);
  };
  
  bool GetTrailing() const {
    return bits(data, 77, 77);
  };
  
  void SetTrailing(bool trailing) {
    set_bits(data, 77, 77, trailing);
  };

  uint8_t GetGEO() const {
    return bits(data, 80, 84);
  };
  
  void SetGEO(uint8_t geo) {
    set_bits(data, 80, 84, geo);
  };
  
  void Print(std::ostream& output = std::cout) const {
    output << "measurement = " << GetMeasurement() << std::endl;
    output << "extended_time = " << GetExtendedTime() << std::endl;
    output << "value = " << GetValue() << std::endl;
    output << "event = " << GetEvent() << std::endl;
    output << "channel = " << GetChannel() << std::endl;
    output << "trailing = " << GetTrailing() << std::endl;
    output << "geo = " << GetGEO() << std::endl;
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
