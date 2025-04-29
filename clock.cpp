#include <iostream>
#include <ctime>
#include <unistd.h> 
#include <cstdlib>  

using namespace std;

int main() {
    system("clear");
    system(" chmod +x ./welcomeclock.sh");
    system("./welcomeclock.sh");
    
    char userInput;
    do {
        // Get the current time
        time_t currentTime = time(0);
        
        // Convert the current time to a string
        char* timeString = ctime(&currentTime);
        
        // Print the current time
        cout << "Current time: " << timeString;
        cout << "Press 't' to exit." << endl;
        
        // Check for user input
        cin >> userInput;
    } while (userInput != 't');
    
    return 0;
}

