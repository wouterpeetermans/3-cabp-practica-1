#include <iostream>
#include <fstream>
#include <chrono>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void displayProcessTimes(string msg)
{
  struct tms t;
  clock_t clockTime;
  long clockTicks = 0;

  if (!msg.empty())
  {
    cout << msg << endl;
  }

  if (clockTicks == 0)
  {
    clockTicks = sysconf(_SC_CLK_TCK);
    if (clockTicks == -1)
    {
      exit(EXIT_FAILURE);
    }
  }

  clockTime = clock();
  if (clockTime == -1)
    exit(EXIT_FAILURE);
  printf("        clock() returns: %ld clocks-per-sec (%.2f secs)\n",
         (long)clockTime, (double)clockTime / CLOCKS_PER_SEC);
  if (times(&t) == -1)
    exit(EXIT_FAILURE);
  printf("        times() yields: user CPU=%.2f; system CPU: %.2f\n",
         (double)t.tms_utime / clockTicks,
         (double)t.tms_stime / clockTicks);
}


// little function to do some processor work
int cpuAddOneToArray(char *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    array[i]++;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  char *memblock;
  streamsize size;
  string filename = "testing.bin"; //default filename
  if (argc > 1)
  {
    filename = argv[1];
  }
  displayProcessTimes("at Program start");
  auto start = chrono::high_resolution_clock::now();         //take starttime
  ifstream file(filename, ios::in | ios::ate | ios::binary); // file reading sequence
  if (file.is_open())
  {
    size = file.tellg();
    file.seekg(0, ios::beg);
    memblock = new char[size];
    file.read(memblock, size);
    file.close();
  }
  auto finish = chrono::high_resolution_clock::now(); //take endtime
  //print the time it took to the console
  displayProcessTimes("after reading file");
  cout << "chrono time: " << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << "ns\n";
  start = chrono::high_resolution_clock::now();
  cpuAddOneToArray(memblock, size); //room heating :)
  finish = chrono::high_resolution_clock::now();
  displayProcessTimes("after doing calculations");
  cout << "chrono time: " << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << "ns\n";
  start = chrono::high_resolution_clock::now();
  ofstream wfile(filename, ios::out | ios::trunc | ios::binary); //file writing sequence
  if (wfile.is_open())
  {
    wfile.write(memblock, size);
    wfile.close();
  }
  finish = chrono::high_resolution_clock::now();
  displayProcessTimes("at Program end");
  cout << "chrono time: " << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << "ns\n";
  return 0;
}
