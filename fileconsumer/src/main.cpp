#include <iostream>
#include <fstream>

using namespace std;

int cpuAddOneToArray(char* array, int size){
  for (int i = 0; i < size; i++){
    array[i]++;
  }
  return 0;
}


int main(int argc, char* argv[]){
  char * memblock;
  streamsize size;
  string filename = "testing.bin";
  if ( argc > 1 ){
    filename = argv[1];
  }

  ifstream file (filename,ios::in | ios::ate | ios::binary);
  if (file.is_open()){
    size = file.tellg();
    file.seekg (0, ios::beg);
    memblock = new char[size];
    file.read(memblock, size);
    file.close();
    cout << "the size is: " << size << endl;
  }
  
  cpuAddOneToArray(memblock,size);

  ofstream wfile (filename,ios::out | ios::trunc | ios::binary);
  if(wfile.is_open()){
    wfile.write(memblock, size);
    wfile.close();
  }

  
  return 0;
}


