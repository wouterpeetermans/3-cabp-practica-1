#include <iostream>
#include <fstream>

using namespace std;


int mkFile(int size,string filename){
  char* memblock;
  memblock = new char[size];
  for( int i = 0; i < size; i++){
    memblock[i] = rand()%255; 
  }
  ofstream file (filename, ios::out | ios::trunc);
  if (file.is_open()){
    file.write(memblock, size);
    file.close();
  }
  delete[] memblock;
  return 0;
}

int cpuAddOneToArray(char* array, int size){
  for (int i = 0; i < size; i++){
    array[i]++;
  }
  return 0;
}



int main(int argc, char* argv[]){
  string filename = "testing.bin";
  if ( argc > 1 ){
    filename = argv[1];
  }
  
  mkFile(1024,filename);
  return 0;
}


