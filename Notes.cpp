#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/shm.h>
using namespace std;

void addNote() {
    ofstream file("notes.txt", ios::app);
    string note;
    cout << "Enter note: ";
    cin.ignore();
    getline(cin, note);
    file << note << "\n";
    file.close();
    cout << "Note saved.\n";
}

void viewNotes() {
    ifstream file("notes.txt");
    string line;
    cout << "Your Notes:\n";
    while (getline(file, line)) {
        cout << "- " << line << "\n";
    }
    file.close();
}

int main() {
    cout << "\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "\t\t\tWELCOME TO NOTES APPLICATION!" << endl;
    cout << "\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;

    // Decrement shared memory (RAM usage)
    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    int new_data = *shared_memory - 30; // ramUse for "notes" is 30
    *shared_memory = new_data;
    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    int choice;
    do {
        cout << "Press 1 to add a note" << endl;
        cout << "Press 2 to view notes" << endl;
        cout << "Press 0 to exit" << endl;
        cin >> choice;
        if (choice == 1) {
            addNote();
        }
        else if (choice == 2) {
            viewNotes();
        }
        else if (choice != 0) {
            choice = 0;
        }
    } while (choice != 0);

    sleep(4); // Simulate processing time

    // Increment shared memory (restore RAM)
    shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    new_data = *shared_memory + 30;
    *shared_memory = new_data;
    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    return 0;
}