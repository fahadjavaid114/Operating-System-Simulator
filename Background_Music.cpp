#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <sys/shm.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

void playBeep() {
    cout << "Beep sound playing in background...\n";
    for (int i = 0; i < 5; ++i) {
#ifdef _WIN32
        Beep(523, 500); // Windows only
#else
        cout << "\a"; // Cross-platform, console beep
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
#endif
    }
}

int main() {
    cout << "\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "\t\t\tWELCOME TO BACKGROUND MUSIC!" << endl;
    cout << "\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;

    // Decrement shared memory (RAM usage)
    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    int new_data = *shared_memory - 11; // ramUse for "background music" is 11
    *shared_memory = new_data;
    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    int choice;
    do {
        cout << "Press 1 to play beep sound" << endl;
        cout << "Press 0 to exit" << endl;
        cin >> choice;
        if (choice == 1) {
            playBeep();
        }
        if (choice != 0 && choice != 1) {
            choice = 0;
        }
    } while (choice == 1);

    sleep(4); // Simulate processing time

    // Increment shared memory (restore RAM)
    shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    new_data = *shared_memory + 11;
    *shared_memory = new_data;
    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    return 0;
}