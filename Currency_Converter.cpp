#include <iostream>
#include <unistd.h>
#include <sys/shm.h>
using namespace std;

void currencyConverter() {
    double pkr;
    cout << "Enter amount in PKR: ";
    cin >> pkr;
    cout << "USD: " << pkr / 278 << "\n";
    cout << "GBP: " << pkr / 353 << "\n";
}

int main() {
    cout << "\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "\t\t\tWELCOME TO CURRENCY CONVERTER!" << endl;
    cout << "\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;

    // Decrement shared memory (RAM usage)
    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    int new_data = *shared_memory - 40; // ramUse for "currency converter" is 40
    *shared_memory = new_data;
    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    int choice;
    do {
        cout << "Press 1 to convert currency" << endl;
        cout << "Press 0 to exit" << endl;
        cin >> choice;
        if (choice == 1) {
            currencyConverter();
        }
        if (choice != 0 && choice != 1) {
            choice = 0;
        }
    } while (choice == 1);

    sleep(4); // Simulate processing time

    // Increment shared memory (restore RAM)
    shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    new_data = *shared_memory + 40;
    *shared_memory = new_data;
    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    return 0;
}