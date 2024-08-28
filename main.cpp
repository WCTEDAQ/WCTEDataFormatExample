#include <WCTERawData.h>
#include <iostream>
#include <BinaryStream.h>

int main(){

  // opening a new file//
  BinaryStream output;
  output.Bopen("./data.dat", NEW, UNCOMPRESSED); 

  //creating some fake data (not filling out all the feilds but just a couple as an example)
  WCTERawData out_data;
  out_data.daq_info.run_number = 56;
  out_data.daq_info.sub_run_number = 42;

  for(int i=0; i<10; i++){
    ReadoutWindow tmpwindow;
     for(int j=0; j<10; j++){

       WCTEMPMTHit mpmt_hit;
       mpmt_hit.SetChannel(i);
       mpmt_hit.SetCharge(i*100);

       WCTEMPMTWaveform mpmt_waveform;
       mpmt_waveform.header.SetChannel(i);
       for(int k=0; k<j; k++){ 
	 mpmt_waveform.samples.push_back(k*20);
       }
       
       HKMPMTHit hk_mpmt_hit;
       hk_mpmt_hit.SetChannel(i);
       hk_mpmt_hit.SetCharge(i*100);

       TDCHit tdc_hit;
       tdc_hit.SetChannel(i);
       tdc_hit.SetValue(i*100);
       
       QDCHit qdc_hit;
       qdc_hit.SetChannel(i);
       qdc_hit.SetValue(i*100);


       tmpwindow.mpmt_hits.push_back(mpmt_hit);
       tmpwindow.mpmt_waveforms.push_back(mpmt_waveform);
       tmpwindow.hk_mpmt_hits.push_back(hk_mpmt_hit);
       tmpwindow.tdc_hits.push_back(tdc_hit);
       tmpwindow.qdc_hits.push_back(qdc_hit);
     }

     TriggerInfo trigger_info;
     trigger_info.type=TriggerType::BEAM;
     trigger_info.time=324348923904328;
     
     
     tmpwindow.triggers_info.push_back(trigger_info);
     out_data.readout_windows.push_back(tmpwindow);

  }
  
  //saving data and closing file
  output<<out_data; 
  output.Bclose();

  //opening datafile
  BinaryStream input;
  input.Bopen("./data.dat", READ, UNCOMPRESSED); 

  //reading in data
  WCTERawData in_data;
  input>>in_data;

  //printing data
  in_data.Print();
  
  input.Bclose();  
    
  return 0;

}
