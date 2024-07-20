#ifndef WCTE_RAW_DATA_H
#define WCTE_RAW_DATA_H

#include <vector>
#include <Trigger.h>
#include <DAQInfo.h>
#include <string>

#include <SerialisableObject.h>
#include <BinaryStream.h>


class WCTERawData : public SerialisableObject{

public:
  
  DAQInfo daq_info;
  std::vector<Trigger> triggers;

  bool Print(){
    daq_info.Print();
    for(unsigned int i=0; i<triggers.size(); i++){
      std::cout<<"///////////////////////////////// "<<std::endl;
      std::cout<<"Trigger "<<i<<std::endl;
      std::cout<<"///////////////////////////////// "<<std::endl;
      triggers.at(i).Print();
      std::cout<<"///////////////////////////////// "<<std::endl<<std::endl;
    }
    
    return true;};
  std::string GetVersion(){return "1.0";}

  bool Serialise(BinaryStream &bs){ 
    
    bs & daq_info;
    bs & triggers;
    
    return true;  
  }
  
};


#endif
