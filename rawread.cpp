#include <WCTERawData.h>
#include <iostream>
#include <BinaryStream.h>

int main(){

  //opening datafile
  BinaryStream input;
  input.Bopen("../WCTEDAQ/data/dataR178S0P0.dat", READ, UNCOMPRESSED); 

  //reading in data
  WCTERawData in_data;
  input>>in_data;

  std::cout<<"num_redout_windows = "<<  in_data.readout_windows.size()<<std::endl;
  //printing data
  //  in_data.Print();
  
  input.Bclose();  


  return 0;

}
