#include <iostream>
#include <fstream>

using namespace std;


int mkFile(int size,string filename){
  char* memblock;
  memblock = new char[size];
  for( int i = 0; i < size; i++){ //fill up some space with random data
    memblock[i] = rand()%255; 
  }
  ofstream file (filename, ios::out | ios::trunc | ios::binary); //file writing sequence
  if (file.is_open()){
    file.write(memblock, size);
    file.close();
  }
  delete[] memblock;
  return 0;
}


int main(int argc, char* argv[]){
  string filename = "testing.bin";//default file name and size if none are given
  int fileSize = 1024;
  if ( argc > 1 ){      //first argument becomes filename
    filename = argv[1];
  }
  if ( argc > 2 ){      //second argument becomes filesize 
    fileSize = stoi (argv[2],nullptr); // string to int function
  }
  
  mkFile(fileSize,filename);//see defenition above
  return 0;
}


