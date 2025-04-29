#include <iostream>
#include <cstdlib>
#include <semaphore.h>
#include<string>
#include<string.h>
#include <pthread.h>
#include <chrono>
#include <unistd.h>
#include <list>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <iomanip>

using namespace std;
// Variables
long int RAM = 0;
long int HDD = 0;
long int CORES = 0;
int choice=0;
bool boolexitflag=false;
pthread_mutex_t mutex1,mutex2,mutex3; 
string process_str[] =
      { "CALCULATOR", "TICTAC", "CLOCK", "NOTEPAD", "TODO",  "CREATE", "DELETE", "RENAME","MUSIC","CALENDER","RANDOMNO","UNITCONVERT"};
 string temp;
const int maxprocess = 12;
sem_t semaphore;
bool kernel_mode = false;
pthread_t ptid;
pthread_t dispatch;
pthread_t shift;
pthread_t displaythread;

pthread_t timethread;
long int needOfProcesses[maxprocess]; // Ram Required-Turnaround
int threads_per_core=2;
int runningProcessestimes[maxprocess] = {0};
int** runningCores;
list<int> readyQueue;
list<int> waitingQueue;

time_t now;
struct tm* current_time;
// Functions
enum Processes {
  Calculator,
  TicTacToe,
  Clock,
  Notepad,
  TODO,
  Create,
  Delete,
  Rename,
  Music,
  Calender,
  Random_No_Generator,
  Unit_Converter


};
void displayMessageCentered(string message,int windowWidth) {

    int messageWidth = message.length();
    int leftMargin = (windowWidth - messageWidth) / 2;
    for (int i = 0; i < leftMargin; i++) {
        cout << " ";
    }
    cout << message << endl;
}

bool checkfreecores()
{
  for (int i = 0; i < CORES; i++){
    for (int j = 0; j < threads_per_core; j++){
      if (runningCores[i][j] ==  -1){
        return true;
      }
    }
   
  }
  return false;
}
void MainMenu()
{

  system("tput setaf 4");
  cout<<endl;
  displayMessageCentered("************************************************************",165);
   cout <<  endl;
  displayMessageCentered("************************ MAIN MENU *************************",165);
    cout << endl;
  displayMessageCentered("************************************************************",165);
    cout <<  endl << endl;

  system("tput sgr0");
   displayMessageCentered(" | 1-Calculator | 2-Tic Tac Toe | 3-Clock | 4-Notepad | 5-TO-DO List |",165);
    cout <<endl;
   displayMessageCentered("| 6-Create A File | 7-Delete A File | 8-Rename A File | 9-Play Music | ",165);
    cout<<endl;
      displayMessageCentered("| 10-Calender | 11-Random No Generator | 12-Unit Converter |",165);
    cout<<endl;
   displayMessageCentered("-> Enter: ",165);
}
void displayTime() {
  system("tput setaf 7");
    now = time(nullptr);
    current_time = localtime(&now);
    string time_str = "| Current Time: ";
    time_str += to_string(current_time->tm_hour) + ":";
    time_str += to_string(current_time->tm_min)+" |";
    // Output the string
   
    displayMessageCentered(time_str,165);
    cout<<endl<<endl;
  
}
void currentlyrunningcores(){
for (int i = 0; i < CORES; i++){
    for (int j = 0; j < threads_per_core; j++){
      if (runningCores[i][j] !=  -1)
      {
        displayMessageCentered("-----------------------------------------------------------------------",0);
        cout << endl;
        temp="Core: " + to_string(i+1) + " is Executing "+process_str[runningCores[i][j]];
        displayMessageCentered(temp,0);
        cout <<endl;
        displayMessageCentered("-----------------------------------------------------------------------",0);
        cout << endl;
      }
    }
}

}

void currentlyrunningprocess(){
  system("tput setaf 1");
   if(kernel_mode==false){
     cout<<"[ USER MODE ]"<<endl<<endl;
     displayTime();
    }
    else{
     cout<<"[ KERNEL MODE ]"<<endl<<endl;
        displayTime();
    }
  bool anyrunningprocess=false;
   system("tput setaf 3");
   cout<<endl<<endl;
  displayMessageCentered("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",0);
   cout<<endl;
  displayMessageCentered("++++++++++++++++ CURRENTLY RUNNING PROCESSES +++++++++++++++",0);
    cout<<endl;
  displayMessageCentered("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",0);
   cout<<endl<<endl;
  temp="Available RAM: " + to_string(RAM) + " MB";
  displayMessageCentered(temp,0);
    cout<<endl;
  temp="Available Storage: " + to_string(HDD) + " MB";
  displayMessageCentered(temp,0);
    cout<<endl;
  temp="Available Cores: " + to_string(CORES);
  displayMessageCentered(temp,0);
    cout<<endl;
    currentlyrunningcores();
    for(int i=0;i<maxprocess;i++){
      if(runningProcessestimes[i]!=0){
        temp=process_str[i]+" is Currenlty Running "+to_string(runningProcessestimes[i]) + " times";
        displayMessageCentered(temp,0);
        cout<<endl;
        anyrunningprocess=true;
      }
    }
    if(anyrunningprocess==false){
      displayMessageCentered("Currently No Process is Running !",0);
      cout<<endl;
    }
     system("tput sgr0");

}
void *display(void*arg){
  while(boolexitflag!=true){
    system("clear");
     currentlyrunningprocess();
     MainMenu();
     sleep(4);
  }
  return 0;
}
void processscheduler(){
 int choice=0 ;    //change if process increased
  while(true)
  {
    system("clear");
    cin>>choice;
   if(choice==0){
    kernel_mode=true;
    boolexitflag=true;
  system("clear");
     cout<<"[ KERNEL MODE ]"<<endl<<endl;
        displayTime();
  pthread_cancel(ptid);
  pthread_cancel(dispatch);
  pthread_cancel(shift);
  cout<<endl<<endl<<endl;
   displayMessageCentered("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",165);
   cout<<endl;
   displayMessageCentered("---------------- Closing all Processes & Exiting ----------------",165);
   cout<<endl;
   displayMessageCentered("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",165);
   sleep(2);
    system("tput sgr0");
   system("clear");
  system(" chmod a+x ./shutdown.sh");
  system("./shutdown.sh");
  system("killall -9 gnome-terminal-server");
  exit(0);
  }
   if(choice<=maxprocess&&choice>=1)
   {
    //first come first serve algorithm and resouce management & check
    if((RAM>=needOfProcesses[choice-1]) && checkfreecores()==true){
      readyQueue.push_back(choice);   // ready queue process inserted from rear-fcfs
    }
    else{
   system("zenity --warning --width=500 --height=200 --text 'WARNING ! Not Enough RAM OR cores Available Process has been added to Waiting Queue'");
     waitingQueue.push_back(choice);   // waiting queue when ready queue is full process inserted in it
      continue;
    }
   }

  }
}
void assign_core(int process)
{
  for (int i = 0; i < CORES; i++){
    for (int j = 0; j < threads_per_core; j++){
      if (runningCores[i][j] ==  -1)
      {
        runningCores[i][j] = process;
        return;
      }
    }
  }
}
void dealloc_core(int process)
{
  for (int i = 0; i < CORES; ++i){
    for (int j = 0; j < threads_per_core; j++){
      if (runningCores[i][j] ==  process)
      {
        runningCores[i][j] = -1;
        return;
      }
    }
  }
}
// release allocated resources
void release_resources(char* str)
{
  string str1, str2;
  int index;
    for (int i = 0;i <maxprocess;i++)
    {
    str1 = string(process_str[i]);
    str2 = string(str);
    
      if (!str1.compare(str2))
      {
        index = i;
        break;
      }
    }
    system("clear");
    dealloc_core(index);
    sem_wait(&semaphore);
    runningProcessestimes[index]--;
    RAM += needOfProcesses[index];
    sem_post(&semaphore);
    system("clear");

}
// thread function for interterminal communication
void * thread_for_inter_terminal_comm(void * arg)
{
  int fd;
 char myfifo[] = "/tmp/myfifo";
  mkfifo(myfifo, 0666); //giving permissions

  char arr1[80], arr2[80];
  while (true)
  {
    //pthread_mutex_lock(&mutex3); 
    fd = open(myfifo, O_RDONLY);
    // Read from FIFO
    read(fd, arr1, sizeof(arr1));
    string temp = "notify-send '"+ string(arr1) +" Has Been Closed!'";
    system(temp.c_str());
    release_resources(arr1);
    close(fd);
     //pthread_mutex_lock(&mutex3); 
  }
}


// shifts process from waiting queue to ready queue upon availability of resources
void * shift_process_state(void * argv)
{
  int process;
  while(true)
  {
     //pthread_mutex_lock(&mutex2); 
     if(!waitingQueue.empty())
     {
      if(needOfProcesses[waitingQueue.front()-1] <= RAM && checkfreecores()==true )
      {
        process = waitingQueue.front();
        waitingQueue.pop_front();
        readyQueue.push_back(process);
      }
   
  }
   //pthread_mutex_unlock(&mutex2); 
  }
}
// thread functions keeps checking ready queue and calls exec file for further executions
void *dispatcher(void*argv){
  pid_t process;
  int currentexec=-1;
  while(true)
  {
     //pthread_mutex_lock(&mutex1); 
    if(!readyQueue.empty()){
  currentexec=readyQueue.front();
  readyQueue.pop_front();
  }
  else{
    currentexec=-1;
  }
  if(currentexec!=-1){
    runningProcessestimes[currentexec-1]++;
    RAM=RAM-needOfProcesses[currentexec-1];
    temp = "notify-send '"+ process_str[currentexec-1] +" dispatched From ReadyQueue For Running!'";
    system(temp.c_str());
    assign_core(currentexec-1);
    system("clear");
   
  }
  if(currentexec==1){   //calculator
   process = fork();
   if (!process){
     system("g++ calculator.cpp -o calculator"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./calculator", temp.c_str(), temp2.c_str(), NULL);
    }

  }
  else if(currentexec==2){   //Tic Tac Toe
  process = fork();
  if (!process){
     system("g++ tictactoe.cpp -o tictactoe"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./tictactoe", temp.c_str(), temp2.c_str(), NULL);
    }
  }
  else if(currentexec==3){ //Clock
  process = fork();
  if (!process){
   system("g++ clock.cpp -o clock"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./clock", temp.c_str(), temp2.c_str(), NULL);
    }

  }
  else if(currentexec==4){ // Notepad
  process = fork();
  if (!process){
    system("g++ notepad.cpp -o notepad"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./notepad", temp.c_str(), temp2.c_str(), NULL);
    }
  }
  else if(currentexec==5){ // Todo list
  process = fork();
  if (!process){
    system("g++ todolist.cpp -o todolist"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./todolist", temp.c_str(), temp2.c_str(), NULL);
    }

  }
  else if(currentexec==6){ // Create File
  process = fork();
  if (!process){
     system("g++ create.cpp -o create"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./create", temp.c_str(), temp2.c_str(), NULL);
    }

  }
  else if(currentexec==7){ // Delete File
  process = fork();
  if (!process){
     system("g++ delete.cpp -o delete"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./delete", temp.c_str(), temp2.c_str(), NULL);
    }

  }
  else if(currentexec==8){ // Rename File
  process = fork();
  if (!process){
     system("g++ rename.cpp -o rename"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./rename", temp.c_str(), temp2.c_str(), NULL);
    }

  }
  else if(currentexec==9){ // Play Music
  process = fork();
  if (!process){
    system("g++ playmusic.cpp -o playmusic"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./playmusic", temp.c_str(), temp2.c_str(), NULL);
    }

  }
   else if(currentexec==10){ // calender
  process = fork();
  if (!process){
     system("g++ calender.cpp -o calender"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./calender", temp.c_str(), temp2.c_str(), NULL);
    }

  }
    else if(currentexec==11){ // random no
  process = fork();
  if (!process){
    system("g++ randomno.cpp -o randomno"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./randomno", temp.c_str(), temp2.c_str(), NULL);
    
    }

  }
    else if(currentexec==12){ // unit converter
  process = fork();
  if (!process){
    system("g++ unitconverter.cpp -o unitconverter"); //compile
      system("g++ exec.cpp -o exec");
    temp=to_string(RAM);
    string temp2=to_string(needOfProcesses[currentexec-1]);
    execl("./exec", "./exec", "./unitconverter", temp.c_str(), temp2.c_str(), NULL);
    
    }

  }
    

  
   //pthread_mutex_unlock(&mutex1); 
  }


}

int main(int argc, char* argv[]){
 //system("rm /tmp/myfifo"); 
  cout<<"Enter RAM size(GB):";
  cin>>RAM;
  cout<<"Enter HDD size(GB):";
  cin>>HDD;
  cout<<"Enter Number of cores :";
  cin>>CORES;
  RAM = 1024*RAM;
  HDD= 1024*HDD;
  
  sem_init(&semaphore, 0, 1);
   system("printf '\e[8;51;165t'"); //set terminal size to 51x165
  system("clear");
  system("./displaybar.sh");
  system("./oslogo.sh");
  system("notify-send 'Hello ! Welcome to OS Simulator'");

  if(argv[1]!=nullptr){
    temp=string(argv[1]);
  }
  if(temp=="kernel" || temp=="KERNEL"){
    kernel_mode = true;
    system("notify-send 'You Are in Kernel Mode'");
     cout << "Please Enter No Of Threads Per Core [Currently In KERNEL MODE]: ";
     cin >> threads_per_core;
  }
  needOfProcesses[0] = 50; //calculator
  needOfProcesses[1] = 100; // TicTacToe
  needOfProcesses[2] = 900; //Clock
  needOfProcesses[3] = 100; //notepad
  needOfProcesses[4] = 50; //To Do list
  needOfProcesses[5] = 50; //Create a File
  needOfProcesses[6] = 50; //Delete a File
  needOfProcesses[7] = 50; //Rename a File
  needOfProcesses[8] = 50; //Music
  needOfProcesses[9] = 50; //calender
  needOfProcesses[10] = 50; //Randomnogenerator
  needOfProcesses[11] = 100; //unitconverter

  
  while(RAM<1||HDD<1||CORES<1) {
    if(RAM<1){
      cout << "ERROR! Not Sufficient RAM Please Allocate AtLeast 1 GB"<<endl;
      cout<<"Enter Ram To Allocate:";
      cin>>RAM;
      RAM=RAM*1024;
      continue;
    }
    if(HDD<1){
      cout << "ERROR! Not Sufficient HARD DISK Please Allocate AtLeast 1 GB"<<endl;
      cout<<"Enter HDD To Allocate:";
      cin>>HDD;
      HDD=HDD*1024;
      continue;
    }
    if(CORES<1){
      cout << "ERROR! Not Sufficient CORES Please Allocate AtLeast 1 Core"<<endl;
      cout<<"Enter Cores To Allocate:";
      cin>>CORES;
      continue;
    }
    if (kernel_mode==true) {
      temp="user";
      cout << "Please Enter No Of Threads Per Core [Currently In KERNEL MODE]: ";
      cin >> threads_per_core;
      if (threads_per_core < 1)
      {
        cout << "Invalid Cores Please Enter Resources Again\n";
        continue;
      }
      
    }
  }
  system("clear");
  cout<<endl<<endl<<endl;
  displayMessageCentered("+++++++++++++++++++++++++++++++++++++++++++++++++++++++",165);
  cout<<endl;
  displayMessageCentered("++++++++++++++++ Allocation Of Resources +++++++++++++++",165);
  cout<<endl;
  displayMessageCentered("++++++++++++++++++++++++++++++++++++++++++++++++++++++++",165);
  cout<<endl;
  temp="Allocated RAM: " + to_string(RAM) + " MB";
  displayMessageCentered(temp,165);
  cout<<endl;
  temp="Allocated Storage: " + to_string(HDD) + " MB";
  displayMessageCentered(temp,165);
  cout<<endl;
  temp="Allocated Cores: " + to_string(CORES);
   displayMessageCentered(temp,165);
  sleep(2);
  pthread_mutex_init(&mutex1, NULL);
 pthread_mutex_init(&mutex2, NULL);
  pthread_mutex_init(&mutex3, NULL);
 // Start the time display thread
 //pthread_create(&timethread,NULL,displayTime,NULL);
  // Wait for the time display thread to finish
  pthread_create(&dispatch, NULL, dispatcher , NULL);
  pthread_create(&shift, NULL, shift_process_state , NULL);
  pthread_create(&ptid,NULL,thread_for_inter_terminal_comm,NULL);
  pthread_create(&displaythread,NULL,display,NULL);




   runningCores=new int*[CORES];
   for(int i=0;i<CORES;i++){
    runningCores[i]=new int[threads_per_core];
   }
   for (int i = 0; i < CORES; i++){
    for (int j = 0; j < threads_per_core; j++){
      runningCores[i][j] = -1;
    }
   }
  processscheduler();

  pthread_join(ptid, NULL);
  pthread_join(dispatch, NULL);
  pthread_join(shift, NULL);
    pthread_join(displaythread, NULL);
  //  pthread_join(timethread, NULL);

 
  return 0;
}





