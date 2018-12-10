#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// little function to do some processor work
int cpuAddOneToArray(char* array, int size){
  for (int i = 0; i < size; i++){
    array[i]++;
  }
  return 0;
}


int main(int argc, char* argv[]){
  char * memblock;
  streamsize size;
  string filename = "testing.bin";    //default filename 
  if ( argc > 1 ){
    filename = argv[1];
  }

  auto start = chrono::high_resolution_clock::now();  //take starttime
  ifstream file (filename,ios::in | ios::ate | ios::binary); // file reading sequence
  if (file.is_open()){
    size = file.tellg();
    file.seekg (0, ios::beg);
    memblock = new char[size];
    file.read(memblock, size);
    file.close();
  }
  auto finish = chrono::high_resolution_clock::now(); //take endtime
  //print the time it took to the console
  cout << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << "ns\n";
  start = chrono::high_resolution_clock::now();
  cpuAddOneToArray(memblock,size); //room heating :) 
  finish = chrono::high_resolution_clock::now();
  cout << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << "ns\n";
  start = chrono::high_resolution_clock::now();
  ofstream wfile (filename,ios::out | ios::trunc | ios::binary); //file writing sequence
  if(wfile.is_open()){
    wfile.write(memblock, size);
    wfile.close();
  }
  finish = chrono::high_resolution_clock::now();
  cout << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << "ns\n";
  return 0;
}


