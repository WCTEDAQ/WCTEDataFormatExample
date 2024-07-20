#ifndef TRIGGER_H
#define TRIGGER_H

#include <vector>
#include <string>
#include <SerialisableObject.h>
#include <BinaryStream.h>

#include <WCTEMPMTHit.h>
#include <WCTEMPMTWaveform.h>
#include <WCTEMPMTLED.h>
#include <HKMPMTHit.h>
#include <TDCHit.h>
#include <QDCHit.h>

enum class TriggerType{ LASER, NHITS, LED, BEAM, NONE };

class TriggerInfo : public SerialisableObject{

public:
  
  TriggerType type;
  unsigned long time;
  std::vector<WCTEMPMTLED> mpmt_LEDs;
  
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

class Trigger : SerialisableObject{

public:
  
  std::vector<TriggerInfo> triggers_info;
  std::vector<WCTEMPMTHit> mpmt_hits;  
  std::vector<WCTEMPMTWaveform> mpmt_waveforms;
  std::vector<HKMPMTHit> hk_mpmt_hits;
  std::vector<TDCHit> tdc_hit;
  std::vector<QDCHit> qdc_hit;


  bool Print(){

    std::cout<<"/////////////////////////trigger info//////////////////"<<std::endl;
    for(int i=0; i<triggers_info.size(); i++){ std::cout<<"///["<<i<<"]///"<<std::endl; triggers_info.at(i).Print();}
    std::cout<<"/////////////////////////mpmt hits//////////////////"<<std::endl;
    for(int i=0; i<mpmt_hits.size(); i++){std::cout<<"///["<<i<<"]///"<<std::endl; mpmt_hits.at(i).Print();}
    std::cout<<"/////////////////////////mpmt waveforms//////////////////"<<std::endl;
    for(int i=0; i<mpmt_waveforms.size(); i++){std::cout<<"///["<<i<<"]///"<<std::endl; mpmt_waveforms.at(i).Print();}
    std::cout<<"/////////////////////////hk mpmt hits//////////////////"<<std::endl;
    for(int i=0; i<hk_mpmt_hits.size(); i++){ std::cout<<"///["<<i<<"]///"<<std::endl; hk_mpmt_hits.at(i).Print();}
    std::cout<<"/////////////////////////tdc data//////////////////"<<std::endl;
    for(int i=0; i<tdc_hit.size(); i++){std::cout<<"///["<<i<<"]///"<<std::endl; tdc_hit.at(i).Print();}
    std::cout<<"/////////////////////////qdc data//////////////////"<<std::endl;
    for(int i=0; i<qdc_hit.size(); i++){std::cout<<"///["<<i<<"]///"<<std::endl; qdc_hit.at(i).Print();}
    std::cout<<"///////////////////////////////////////////"<<std::endl;
    
    return true;

  }
  std::string GetVersion(){return "1.0";};
  bool Serialise(BinaryStream &bs){
    
    bs & triggers_info;
    bs & mpmt_hits;
    bs & mpmt_waveforms;
    bs & hk_mpmt_hits;
    bs & tdc_hit;
    bs & qdc_hit;

    return true;
  } 
  
};


#endif
