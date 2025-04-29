#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

struct Song {
    string name;
    string lines;
};

int main() {
        system("clear");
    system(" chmod +x ./welcomeplaymusic.sh");
    system("./welcomeplaymusic.sh");
    Song songs[10];

    songs[0] = {"Song 1", "Line 1 of Song 1."};
    songs[1] = {"Song 2", "Line 1 of Song 2."};
    songs[2] = {"Song 3", "Line 1 of Song 3."};
    songs[3] = {"Song 4", "Line 1 of Song 4."};
    songs[4] = {"Song 5", "Line 1 of Song 5."};
    songs[5] = {"Song 6", "Line 1 of Song 6."};
    songs[6] = {"Song 7", "Line 1 of Song 7."};
    songs[7] = {"Song 8", "Line 1 of Song 8."};
    songs[8] = {"Song 9", "Line 1 of Song 9."};
    songs[9] = {"Song 10", "Line 1 of Song 10."};

    while(true) {
        for(int i = 0; i < 10; i++) {
            cout << songs[i].name << endl;
        }
        int songChoice;
        cout << "Which song would you like to play? (Enter a number between 1 and 10) and -1 to exit: ";
        cin >> songChoice;

        // Check if the input is valid
        if (songChoice < -1 || songChoice > 10) {
            cout << "Invalid song choice!" << endl;
            return 1;
        }
        if(songChoice == -1)
            break;

        // Play the selected song
        cout << "Playing " << songs[songChoice - 1].name << ":" << endl;
        for(int i = 0; i < songs[songChoice - 1].lines.length(); i++) {
            if(songs[songChoice - 1].lines[i] == '.') {
                cout << songs[songChoice - 1].lines[i];
                this_thread::sleep_for(chrono::milliseconds(250)); // Sleep for 250 milliseconds
                cout << endl;
            }
            cout << songs[songChoice - 1].lines[i];
        }
    }

    return 0;
}

