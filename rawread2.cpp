#include <iostream>
#include <BinaryStream.h>
#include <DAQHeader.h>
#include <WCTEMPMTPPS.h>

using namespace ToolFramework;


struct MPMTWaveformHeader{

  
  unsigned short GetHeader(){return ((data[0] & 0b11000000) >> 6 );}
  unsigned short GetFlags(){return ((data[0] & 0b00111100) >> 2 );}
  unsigned int GetCoarseCounter(){ return ((data[0] & 0b00000011) << 30 ) | (data[1] << 22) |  (data[2] << 14) | (data[3] << 6) | ((data[4] & 0b11111100) >> 2); }
  unsigned short GetChannel(){return  ((data[4] & 0b00000011) << 3) | ((data[5] & 0b11100000) >> 5 );}
  unsigned short GetNumSamples(){return (( data[5] & 0b00011111) << 11 ) | ( data[6] << 3) |  (( data[7] & 0b11100000) >> 5);}
  unsigned int GetLength(){ return ((data[7] & 0b00011111) << 12 ) | (data[8] << 4) |  ((data[9] & 0b11110000) >> 4); }
  unsigned short GetReserved(){return (data[9] & 0b00001111);}
  static unsigned int GetSize(){return sizeof(data);};
  unsigned char* GetData(){return data;}  
  
  void SetHeader(unsigned short in){ data[0] = (data[0] & 0b00111111) | ((in & 0b00000011) << 6);}
  void SetFlags(unsigned short in){ data[0] = (data[0] & 0b11000011) | ((in & 0b00001111) << 2);}
  void SetCoarseCounter(unsigned int in){
    data[0] = (data[0] & 0b11111100) | (in >> 30);
    data[1] = in >> 22;
    data[2] = in >> 14;
    data[3] = in >> 6;
    data[4] = (data[4] & 0b00000011) | ((in & 0b00111111) << 2);
  }
  void SetChannel(unsigned short in){
    data[4] = (data[4] & 0b11111100) | ((in & 0b00011000) >> 3);
    data[5] = (data[5] & 0b00011111) | ((in & 0b00000111) << 5);
    
  }
  void SetNumSamples(unsigned short in){
    data[5] = (data[5] & 0b11100000) | ((in >> 11) & 0b00011111 );
    data[6] = in >> 3;
    data[7] = (data[7] & 0b00011111) | ((in & 0b00000111) << 5);
  }
  void SetLength(unsigned int in){
    data[7] = (data[7] & 0b11100000) | ((in >> 12) & 0b00011111 );
    data[8] = in >> 4;
    data[9] = (data[9] & 0b00001111) | ((in & 0b00001111) << 4);
  }
  void SetReserved(unsigned short in){data[9] = (data[9] & 0b11110000) | (in & 0b00001111) ; }
  void Print(){
        printf("header = %u\n",GetHeader());
	printf("flags = %u\n",GetFlags());
	printf("coarse_counter = %u\n",GetCoarseCounter());
	printf("channel = %u\n",GetChannel());
	printf("num_samples = %u\n",GetNumSamples());
	printf("length = %u\n",GetLength());
	printf("reserved = %u\n",GetReserved());
    std::cout<<"header = "<<GetHeader()<<std::endl;
    std::cout<<"flags = "<<GetFlags()<<std::endl;
    std::cout<<"coarse_counter = "<<GetCoarseCounter()<<std::endl;
    std::cout<<"channel = "<<GetChannel()<<std::endl;
    std::cout<<"num_samples = "<<GetNumSamples()<<std::endl;
    std::cout<<"length = "<<GetLength()<<std::endl;
    std::cout<<"reserved = "<<GetReserved()<<std::endl;
    
  }
  
  
private:

  unsigned char data[10];
  
};



struct MPMTHit{
  
  unsigned short GetHeader(){return (data[0] & 0b11000000) >> 6; }
  unsigned short GetEventType(){return (data[0] & 0b00111100) >> 2;}
  unsigned short GetChannel(){return ((data[0] & 0b00000011) << 3) | ((data[1] & 0b11100000) >> 5); }
  unsigned short GetFlags(){return (data[1] & 0b00011111);}
  unsigned int GetCoarseCounter(){ return (data[2] << 24) | (data[3] << 16) | (data[4] << 8 ) | (data[5]) ;}
  unsigned short GetFineTime(){return (data[6] << 8) | (data[7]);}
  unsigned short GetCharge(){return (data[8] << 8 ) | data[9] ;}
  unsigned short GetQualityFactor(){return data[10];}
  static unsigned int GetSize(){return sizeof(data);};
  unsigned char* GetData(){return data;}

  void SetHeader(unsigned short in){ data[0] = (data[0] & 0b00111111) | ((in & 0b00000011) << 6);}
  void SetEventType(unsigned short in){ data[0] = (data[0] & 0b11000011) | (( in & 0b00001111) << 2) ;}
  void SetChannel(unsigned short in){
    data[0] = (data[0] & 0b11111100) | ((in & 0b00011000) >> 3);
    data[1] = (data[1] & 0b00011111)  | ((in & 0b00000111) << 5);
   }
  void SetFlags(unsigned short in){ data[1] = (data[1] & 0b11100000) | (in & 0b00011111);}
  void SetCoarseCounter(unsigned int in){
    data[2] = in >> 24;
    data[3] = in >> 16;
    data[4] = in >> 8;
    data[5] = in;
  }
  void SetFineTime(unsigned short in){
    data[6] = in >> 8;
    data[7] = in;
  }
  void SetCharge(unsigned short in){
    data[8] = in >> 8;
    data[9] = in;
  }
  void SetQualityFactor(unsigned short in){ data[10] = in;}
  void Print(){
    std::cout<<" header = "<<GetHeader()<<std::endl;
    std::cout<<" event_type = "<<GetEventType()<<std::endl;
    std::cout<<" channel = "<<GetChannel()<<std::endl;
    std::cout<<" flags = "<<GetFlags()<<std::endl;
    std::cout<<" coarse_counter = "<<GetCoarseCounter()<<std::endl;
    std::cout<<" fine_time = "<<GetFineTime()<<std::endl;
    std::cout<<" charge = "<<GetCharge()<<std::endl;
    std::cout<<" quality_factor = "<<GetQualityFactor()<<std::endl;
  }

  unsigned char data[11];
  
};

struct MPMTLED{

  unsigned short GetHeader(){return (data[0] & 0b11000000) >> 6; }
  unsigned short GetEventType(){return (data[0] & 0b00111100) >> 2;}
  unsigned short GetLED(){return ((data[0] & 0b00000011) << 1) | ((data[1] & 0b10000000) >> 7); }
  bool GetGain(){return ((data[1] & 0b01000000) >> 6);}
  unsigned short GetDACSetting(){return ((data[1] & 0b00111111)  << 4 ) | ((data[2] & 0b11110000) >>4 ) ;}
  unsigned short GetType(){return ((data[2] & 0b00001100)  >> 2 );}
  unsigned short GetSequenceNumber(){return ((data[2] & 0b00000011)  << 12 ) | (data[3] << 4 ) | ((data[4] & 0b11110000 ) >> 4 ) ;}
  unsigned int GetCoarseCounter(){ return ((data[4] & 0b00001111) << 28) | (data[5] << 20) | (data[6] << 12 ) | (data[7] << 4) | ((data[8] & 0b11110000 ) >> 4 ) ;}
  unsigned short GetReserved(){return (data[8] & 0b00001111);}
  static unsigned int GetSize(){return sizeof(data);};
  unsigned char* GetData(){return data;}  


  
  void SetHeader(unsigned short in){ data[0] = (data[0] & 0b00111111) | ((in & 0b00000011) << 6);}
  void SetEventType(unsigned short in){ data[0] = (data[0] & 0b11000011) | (( in & 0b00001111) << 2) ;}
  void SetLED(unsigned short in){
    data[0] = (data[0] & 0b11111100) | ((in & 0b00000110) >> 1);
    data[1] = (data[1] & 0b01111111)  | ((in & 0b00000001) << 7);
   }
  void SetGain(bool in){ data[1] = (data[1] & 0b10111111) | ((in & 0b00000001) << 6) ;}
  void SetDACSetting(unsigned short in){
    data[1] = (data[1] & 0b11000000) | ((in >> 4 ) & 0b00111111) ;
    data[2] = (data[2] & 0b00001111)  | ((in & 0b00001111) << 4 );
  }
  void SetType(unsigned short in){ data[2] = (data[2] & 0b11110011) | ((in & 0b00000011) << 2) ;}
  void SetSequenceNumber(unsigned short in){
    data[2] = (data[2] & 0b11111100) | ((in >> 12 ) & 0b00000011) ;
    data[3] = (in >> 4);
    data[4] = (data[4] & 0b00001111)  | ((in & 0b00001111) << 4 );
  }
  void SetCoarseCounter(unsigned int in){
    data[4] = (data[4] & 0b11110000)  | ((in >> 28 ) & 0b00001111);
    data[5] = in >> 20;
    data[6] = in >> 12;
    data[7] = in >> 4;
    data[8] = (data[8] & 0b00001111)  | ((in & 0b00001111) << 4 );
  }
  void SetReserved(unsigned short in){ data[8] = (data[8] & 0b11110000) | (in & 0b00001111) ;}

  void Print(){
    std::cout<<" header = "<<GetHeader()<<std::endl;
    std::cout<<" event_type = "<<GetEventType()<<std::endl;
    std::cout<<" led = "<<GetLED()<<std::endl;
    std::cout<<" gain = "<<GetGain()<<std::endl;
    std::cout<<" dac_setting = "<<GetDACSetting()<<std::endl;
    std::cout<<" type = "<<GetType()<<std::endl;
    std::cout<<" sequence_number = "<<GetSequenceNumber()<<std::endl;
    std::cout<<" coarse_counter = "<<GetCoarseCounter()<<std::endl;
    std::cout<<" reserved = "<<GetReserved()<<std::endl;
  }


  unsigned char data[9];

};






class MPMTMessage : public SerialisableObject{

 public:
  
  unsigned char* daq_header;
  unsigned char* mpmt_data;
  unsigned int size;
  
  bool Print(){ return true;}
  std::string GetVersion(){return "1.0";}
  bool Serialise(BinaryStream &bs){

    unsigned int tmp = 0;
    bs & tmp;
    //printf("daq_header=%u\n",tmp);
    daq_header= new unsigned char[tmp];
    bs.Bread(&daq_header[0], tmp);
    bs & tmp;
    //printf("mpmt_daq=%u\n",tmp);
    mpmt_data = new unsigned char[tmp];
    bs.Bread(&mpmt_data[0],  tmp);
    size=tmp;
    return true;
  }



};

class MPMTCollection : public SerialisableObject{

 public:
  std::vector<MPMTMessage*> mpmt_output;
  
  //  std::vector<TriggerInfo*> triggers_info;
  // std::vector<MPMTHit*> triggers;
  //std::vector<MPMTLED*> leds;
  //  std::mutex mtx;

  bool Print(){ return true;}
  std::string GetVersion(){return "1.0";}
  bool Serialise(BinaryStream &bs){

    unsigned int tmp = 0;
    bs & tmp;
    mpmt_output.resize(tmp);
    for(int i=0; i<mpmt_output.size(); i++){
      mpmt_output.at(i)=new MPMTMessage;
      bs & (*mpmt_output.at(i));
    }

    return true;
  }
  
};


int main(){

  //opening datafile
  BinaryStream input;
  input.Bopen("/mnt/nfs/WebServer/html-Detector/Data/dataR504S0P0.dat", READ, UNCOMPRESSED); 
  
  unsigned long size=0;
  input >>size;
  
  std::map<unsigned int, MPMTCollection> test;
  
  for(unsigned long i=0; i<size; i++){
    unsigned int key;
    MPMTCollection value;
    input >> key;
    input >> value;
    test[key]=value;
  }
  

  std::map<unsigned int, unsigned int> mpmts;
  
  for( std::map<unsigned int, MPMTCollection>::iterator it=test.begin(); it!=test.end(); it++){
    printf("\n\n\nchunk time= %u\n",it->first);
    
    
    std::vector<MPMTHit*> hits;
    std::vector<MPMTWaveformHeader*> waveforms;
    //  std::vector<TriggerInfo*> waveforms;
    
    
    for(unsigned int mpmt=0; mpmt<it->second.mpmt_output.size(); mpmt++){
      DAQHeader* daq_header=reinterpret_cast<DAQHeader*>(&(it->second.mpmt_output.at(mpmt)->daq_header[0]));
      
      unsigned int bin= daq_header->GetCoarseCounter();  
      
      unsigned short card_id = daq_header->GetCardID();
      unsigned short card_type = daq_header->GetCardType();
      printf("cardid=%u : type=%u\n", card_id, card_type);
      if(mpmts.count(card_id)) mpmts[card_id]++;
      else mpmts[card_id]=1;
      
      //  std::vector<MPMTHit*> triggers;
      //std::vector<MPMTLED*> leds;
      // std::vector<TriggerInfo*> triggers_info;
      

      unsigned long bytes=it->second.mpmt_output.at(mpmt)->size;
      unsigned long current_byte=0;

      //printf("bytes=%u\n", bytes);
      unsigned char* mpmt_data= it->second.mpmt_output.at(mpmt)->mpmt_data;
      
      while(current_byte<bytes && (bytes-current_byte)>8){
	if((mpmt_data[current_byte] >> 6) == 0b1){ //its a hit or led or pps
	  //printf("in hit, led or pps \n");
	  if(((mpmt_data[current_byte] >> 2) & 0b00001111 ) == 0U && bytes-current_byte >= MPMTHit::GetSize()){ // its normal mpmt hit
	    //printf("in hit\n");
	    MPMTHit* tmp= reinterpret_cast<MPMTHit*>(&mpmt_data[current_byte]);
	    hits.push_back(tmp);

	    if(card_type=3U && tmp->GetChannel()<10 && tmp->GetChannel()!=6) printf("channel=%u\n",tmp->GetChannel());
	    /*
	    if(tmp->GetChannel()<10){
	      TriggerInfo* trigger_info = new TriggerInfo;
	      switch(tmp->GetChannel()){
		
	      case 0U: //main trigger
		trigger_info->type = TriggerType::MAIN;
		break;
		
	      case 1U: //beam monitor - electron
		trigger_info->type = TriggerType::EBEAM;
		break;
		
	      case 2U: //beam monitor - muon
		trigger_info->type = TriggerType::MBEAM;
		break;
		
	      case 5U: //CDS laser
		trigger_info->type = TriggerType::LASER;
		break;
		
	      case 7U:
		trigger_info->type = TriggerType::HARD6;
		break;
		
	      default:
		trigger_info->type = TriggerType::NONE;
		break;
	      }
	      
	      trigger_info->time= ((daq_header->GetCoarseCounter() & 4294901760U )<<16)  | (tmp->GetCoarseCounter());
	      if((daq_header->GetCoarseCounter() & 65535U) > (tmp->GetCoarseCounter() >>16)) trigger_info->time+=65536U;
	      trigger_info->card_id=card_id;
	      triggers_info.push_back(trigger_info);
	    }
	    */
	    current_byte+=MPMTHit::GetSize();
	    
	  }
	  
	  
	  else if(((mpmt_data[current_byte] >> 2) & 0b00001111 ) == 2U && bytes-current_byte >= MPMTLED::GetSize()){// its LED
	    /*
	    printf("in led \n");
	    
	    MPMTLED* tmp = reinterpret_cast<MPMTLED*>(&mpmt_data[current_byte]);

	    leds.push_back(tmp);
	    
	    TriggerInfo* trigger_info = new TriggerInfo;
	    trigger_info->type= TriggerType::LED;
	    trigger_info->time= ((daq_header->GetCoarseCounter() & 4294901760U )<<16)  | (tmp->GetCoarseCounter());
	    if((daq_header->GetCoarseCounter() & 65535U) > (tmp->GetCoarseCounter() >>16)) trigger_info->time+=65536U;
	    trigger_info->card_id=card_id;
	    triggers_info.push_back(trigger_info);
	    */
	    current_byte+=MPMTLED::GetSize();
	  }
	  
      
	  else if(((mpmt_data[current_byte] >> 2) & 0b00001111 ) == 15U && bytes-current_byte >= WCTEMPMTPPS::GetSize() ){// its PPS
	    //printf("in pps\n");
	    current_byte+=WCTEMPMTPPS::GetSize();
	  }
	  else{
	    
	    printf("none of hit LED or pps despite saying it is\n");
	    break;
	  }
	}
	else if ((mpmt_data[current_byte] >> 6) == 2U && bytes-current_byte >= MPMTWaveformHeader::GetSize()){ //its a waveform
	  MPMTWaveformHeader* tmp = reinterpret_cast<MPMTWaveformHeader*>(&mpmt_data[current_byte]);
	  current_byte+=  MPMTWaveformHeader::GetSize() + tmp->GetLength();
	  waveforms.push_back(tmp);
	  //printf("k2\n");
	}
	else{
	  printf("not a wavefrom despite saying it is\n");
	  break;	  
	}
      }
      
    }

    //print stuff
    printf("hits size=%u\n", hits.size());
    printf("waveforms size=%u\n", waveforms.size());


  }

  for(std::map<unsigned int, unsigned int>::iterator it=mpmts.begin(); it!=mpmts.end(); it++){
    
    printf("%u:%u\n", it->first, it->second);
    
  }
  

  input.Bclose();  
  
  return 0;
  
}
