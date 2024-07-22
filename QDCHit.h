#ifndef QDC_HIT_H
#define QDC_HIT_H

#include <iostream>
#include <BitFunctions.h>

class QDCHit {
  
public:
  QDCHit() {
    std::fill(std::begin(data), std::end(data), 0);
  };
  
  QDCHit(
	 uint32_t header,
	 uint32_t packet,
	 uint32_t trailer
	 ) {
    SetCrate(bits(header, 16, 23));
    SetValue(bits(packet, 0, 11));
    SetOverflow(bits(packet, 12, 12));
    SetUnderThreshold(bits(packet, 13, 13));
    SetChannel(bits(packet, 16, 20));
    SetGEO(bits(packet, 27, 31));
    SetEvent(bits(trailer, 0, 23));
  };
  
  uint16_t GetValue() const {
    return bits(data, 0, 11);
  };
  
  void SetValue(uint16_t value) {
    set_bits(data, 0, 11, value);
  };
  
  bool GetUnderThreshold() const {
    return bits(data, 12, 12);
    };
  
  void SetUnderThreshold(bool ut) {
    set_bits(data, 12, 12, ut);
  };
  
  bool GetOverflow() const {
    return bits(data, 13, 13);
  };
  
  void SetOverflow(bool overflow) {
    set_bits(data, 13, 13, overflow);
  };
  
  uint8_t GetGEO() const {
    return bits(data, 14, 18);
  };
  
  void SetGEO(uint8_t geo) {
      set_bits(data, 14, 18, geo);
  };
  
  uint8_t GetChannel() const {
    return bits(data, 19, 23);
  };
  
  void SetChannel(uint8_t channel) {
    set_bits(data, 19, 23, channel);
  };
  
  uint8_t GetCrate() const {
    return bits(data, 24, 31);
  };
  
  void SetCrate(uint8_t crate) {
    set_bits(data, 24, 31, crate);
  };
  
  uint32_t GetEvent() const {
    return bits(data, 32, 55);
  };
  
  void SetEvent(uint32_t event) {
    set_bits(data, 32, 55, event);
  };
  
  void Print(std::ostream& output = std::cout) const {
      output << "value = " << GetValue() << std::endl;
      output << "under_threshold = " << GetUnderThreshold() << std::endl;
      output << "overflow = " << GetOverflow() << std::endl;
      output << "geo = " << GetGEO() << std::endl;
      output << "channel = " << GetChannel() << std::endl;
      output << "crate = " << GetCrate() << std::endl;
      output << "event = " << GetEvent() << std::endl;
  };
  
private:
  /* bits     width   field
   *  0 - 11   12     value
   * 12 - 12   1      under threshold
   * 13 - 13   1      overflow
   * 14 - 18   5      geo
   * 19 - 23   5      channel
   * 24 - 31   8      crate
   * 32 - 55   24     event
   
   01234567
   0 vvvvvvvv         v = value
   1 vvvvuogg         u = under threshold
   2 gggccccc         o = overflow
   3 CCCCCCCC         g = geo
   4 eeeeeeee         c = channel
   5 eeeeeeee         C = crate
   6 eeeeeeee         e = event
  */
  
  uint8_t data[7];

};


#endif
