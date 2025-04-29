#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
#include <cstring>

using namespace std;
long int ram;
long int need;
int main(int argc, char* argv[])
{
    ram=stol(argv[2]);
    need=stol(argv[3]);
    if(need<=ram){
  string temp; 
  temp = "gnome-terminal -- sh -c '" + string(argv[1])  + "'"; 
  system(temp.c_str());
}
else{
      system("notify-send 'NOT ENOUGH RESOURCES'");
}
  return 0;
}

