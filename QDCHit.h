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
    SetCrate(bits<16, 23>(header));
    SetValue(bits<0, 11>(packet));
    SetOverflow(bits<12, 12>(packet));
    SetUnderThreshold(bits<13, 13>(packet));
    SetChannel(bits<16, 20>(packet));
    SetGEO(bits<27, 31>(packet));
    SetEvent(bits<0, 23>(trailer));
  };
  
  uint16_t GetValue() const {
    return bits<0, 11>(data);
  };
  
  void SetValue(uint16_t value) {
    set_bits<0, 11>(data, value);
  };
  
  bool GetUnderThreshold() const {
    return bits<12, 12>(data);
  };
  
  void SetUnderThreshold(bool ut) {
    set_bits<12, 12>(data, ut);
  };
  
  bool GetOverflow() const {
    return bits<13, 13>(data);
  };
  
  void SetOverflow(bool overflow) {
    set_bits<13, 13>(data, overflow);
  };
  
  uint8_t GetGEO() const {
    return bits<14, 18>(data);
  };
  
  void SetGEO(uint8_t geo) {
    set_bits<14, 18>(data, geo);
  };
  
  uint8_t GetChannel() const {
    return bits<19, 23>(data);
  };
  
  void SetChannel(uint8_t channel) {
    set_bits<19, 23>(data, channel);
  };
  
  uint8_t GetCrate() const {
    return bits<24, 31>(data);
  };
  
  void SetCrate(uint8_t crate) {
    set_bits<24, 31>(data, crate);
  };
  
  uint32_t GetEvent() const {
    return bits<32, 55>(data);
  };
  
  void SetEvent(uint32_t event) {
    set_bits<32, 55>(data, event);
  };
  
  void Print(std::ostream& output = std::cout) const {
      output << "value = " << GetValue() << std::endl;
      output << "under_threshold = " << GetUnderThreshold() << std::endl;
      output << "overflow = " << GetOverflow() << std::endl;
      output << "geo = " << static_cast<int>(GetGEO()) << std::endl;
      output << "channel = " << static_cast<int>(GetChannel()) << std::endl;
      output << "crate = " << static_cast<int>(GetCrate()) << std::endl;
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
