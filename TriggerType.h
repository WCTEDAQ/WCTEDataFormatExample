#ifndef TRIGGER_TYPE_H
#define TRIGGER_TYPE_H

#include <vector>
#include <string>
#include <SerialisableObject.h>
#include <BinaryStream.h>
#include <WCTEMPMTLED.h> 

enum class TriggerType{ LASER, NHITS, LED, MAIN, MBEAM, EBEAM, NONE, HARD6 };

class TriggerInfo : public SerialisableObject{

public:
  
  TriggerType type;
  unsigned long time;
  std::vector<WCTEMPMTLED> mpmt_LEDs;
  unsigned long spill_num=0;
  unsigned vme_event_num=0; 
  
  bool Print(){
    std::cout<<"Trigger time = "<<time<<std::endl;
    
    return true;
  }
  std::string GetVersion(){return "1.0";}
  bool Serialise(BinaryStream &bs){
    
    bs & type;
    bs & time;
    bs & mpmt_LEDs;

    return true;
  }
  
};

#endif
