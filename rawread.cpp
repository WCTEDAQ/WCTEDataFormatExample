#include <WCTERawData.h>
#include <iostream>
#include <BinaryStream.h>

int main(){

  //opening datafile
  BinaryStream input;
  input.Bopen("/mnt/nfs/WebServer/html-Detector/Data/dataR407S0P0.dat", READ, UNCOMPRESSED); 

  //reading in data
  WCTERawData in_data;
  input>>in_data;

  unsigned long num_triggers=0;
  unsigned long num_hits=0;
  unsigned long num_waveforms=0;
  unsigned long num_hk_hits=0;
  unsigned long num_extra_hits=0;
  unsigned long num_extra_waveforms=0;
  unsigned long num_tdc_hits=0;
  unsigned long num_qdc_hits=0;
  
  std::cout<<"num_redout_windows = "<<  in_data.readout_windows.size()<<std::endl;

  for (unsigned long i =0; i< in_data.readout_windows.size(); i++){

    if(in_data.readout_windows.at(i).triggers_info.size()){
      num_triggers++;
      std::cout<<"time="<<in_data.readout_windows.at(i).triggers_info.at(0).time<<" spill_num="<<in_data.readout_windows.at(i).triggers_info.at(0).spill_num<<" vme_event_num="<<in_data.readout_windows.at(i).triggers_info.at(0).vme_event_num;
	std::cout<<" Main="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::MAIN);
	std::cout<<" Nhits="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::NHITS);
	std::cout<<" Led="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::LED);
	std::cout<<" Laser="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::LASER);
	std::cout<<" MBeam="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::MBEAM);
	std::cout<<" EBeam="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::EBEAM);
	std::cout<<" None="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::NONE);
	std::cout<<" Hard6="<<(in_data.readout_windows.at(i).triggers_info.at(0).type==TriggerType::HARD6);

	bool empty =(!in_data.readout_windows.at(i).mpmt_hits.size() && !in_data.readout_windows.at(i).mpmt_waveforms.size() && !in_data.readout_windows.at(i).hk_mpmt_hits.size() && !in_data.readout_windows.at(i).extra_hits.size() && !in_data.readout_windows.at(i).extra_waveforms.size() && !in_data.readout_windows.at(i).tdc_hits.size() &&! in_data.readout_windows.at(i).qdc_hits.size()); 
    std::cout<<" empty="<<empty<<std::endl;
    if(empty) exit(0);
	
      for(int j=0 ;j<in_data.readout_windows.at(i).triggers_info.size(); j++){

      }

    }
      if(in_data.readout_windows.at(i).mpmt_hits.size()) num_hits++;
    if(in_data.readout_windows.at(i).mpmt_waveforms.size()) num_waveforms++;
    if(in_data.readout_windows.at(i).hk_mpmt_hits.size()) num_hk_hits++;
    if(in_data.readout_windows.at(i).extra_hits.size()) num_extra_hits++;
    if(in_data.readout_windows.at(i).extra_waveforms.size()) num_extra_waveforms++;
    if(in_data.readout_windows.at(i).tdc_hits.size()) num_tdc_hits++;
    if(in_data.readout_windows.at(i).qdc_hits.size()) num_qdc_hits++;

  }

  
  //printing data
  //    in_data.Print();

  
   for (unsigned long i =0; i< 10; i++){
     in_data.readout_windows.at(i).Print();
     for(int j=0; j<in_data.readout_windows.at(i).extra_waveforms.size(); j++){
       for( int k=0; k<in_data.readout_windows.at(i).extra_waveforms.at(j).samples.size(); k++){

	 std::cout<<((unsigned int)in_data.readout_windows.at(i).extra_waveforms.at(j).samples.at(k))<<" "; 
       }
       std::cout<<std::endl;
     }
   }

//   unsigned long empty=0;
   
//  for (unsigned long i =0; i<in_data.readout_windows.size(); i++){
//  }
   
  input.Bclose();  

  std::cout<<"num_redout_windows = "<<  in_data.readout_windows.size()<<std::endl;
  std::cout<<"num_triggers="<<num_triggers<<std::endl;
  std::cout<<"num_hits="<<num_hits<<std::endl;
  std::cout<<"num_waveforms="<<num_waveforms<<std::endl;
  std::cout<<"num_hk_hits="<<num_hk_hits<<std::endl;
  std::cout<<"num_extra_hits="<<num_extra_hits<<std::endl;
  std::cout<<"num_extra_waveforms="<<num_extra_waveforms<<std::endl;
  std::cout<<"num_tdc_hits="<<num_tdc_hits<<std::endl;
  std::cout<<"num_qdc_hits="<<num_qdc_hits<<std::endl;

  return 0;

}
