#include<iostream>
#include<fstream>
#include<string>
using namespace std;


int main()
{
string fileName;
string extention;
int choice;
system("clear");
system(" chmod +x ./welcomedelete.sh");
system("./welcomedelete.sh");

cout << "Enter File Name: ";
cin >> fileName;
do{
  cout << "Select extention " << endl
  << "1. Text (.txt)" << endl
  << "2. Data (.dat) " << endl
  << "choice: " ;
  cin >> choice;
  if(choice == 1)
  {
    extention = ".txt";
  }
  else if (choice == 2)
  {
    extention = ".dat";
  }
  else
  {
    cout << "Wrong Extention" << endl;
  }
}while(choice < 1 || choice > 2);

  fileName = fileName+extention;
  ifstream temp;
  temp.open(fileName);
  if (temp.fail())
  {
    cout << "No file of this name exists" << endl;
  }
  else
  {
    remove(fileName.c_str());
  }
  
    cin.ignore();
  cout <<"\t\t\t" << "Press any key to Exit..." << endl;
  cin.get();
  system("./dealloc_resource DELETE");
  return 0;
}
