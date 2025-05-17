#include <iostream>
#include <string>
#include <iomanip>
#include<sys/shm.h>
using namespace std;

const int MAX_TRANSACTIONS = 100;

struct Transaction {
    string type;
    double amount;
};

struct Account {
    string name;
    double balance;
    int transaction_count;
    Transaction transactions[MAX_TRANSACTIONS];
};

void displayMenu() {
    cout << "1. Check balance" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Send money" << endl;
    cout << "5. Transaction history" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

double deposit(Account &account, double amount) {
    account.balance += amount;
    Transaction transaction = {"Deposit", amount};
    account.transactions[account.transaction_count++] = transaction;
    return account.balance;
}

double withdraw(Account &account, double amount) {
    if (account.balance >= amount) {
        account.balance -= amount;
        Transaction transaction = {"Withdraw", amount};
        account.transactions[account.transaction_count++] = transaction;
    } else {
        cout << "Insufficient balance!" << endl;
    }
    return account.balance;
}

void sendMoney(Account &sender, Account &receiver, double amount) {
    if (sender.balance >= amount) {
        sender.balance -= amount;
        receiver.balance += amount;
        Transaction sender_transaction = {"Send", amount};
        Transaction receiver_transaction = {"Receive", amount};
        sender.transactions[sender.transaction_count++] = sender_transaction;
        receiver.transactions[receiver.transaction_count++] = receiver_transaction;
    } else {
        cout << "Insufficient balance!" << endl;
    }
}

void printTransactionHistory(Account &account) {
    cout << "Transaction history for " << account.name << ":" << endl;
    for (int i = 0; i < account.transaction_count; i++) {
        cout << setw(10) << left << account.transactions[i].type
             << setw(10) << right << account.transactions[i].amount << endl;
    }
}

int main() 
{
        cout<<"\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
	cout << "\t\t\tWELCOME TO BANKING SYSTEM PROCCESS!"<<endl;
	cout<<"\t\t-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;

int *shared_memory;
int shmid;
shmid=shmget((key_t)1122,sizeof(int),0666);

shared_memory=(int*)shmat(shmid,NULL,0);
int new_data =*shared_memory-2 ;
*shared_memory=new_data;

if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }
    
    
    Account usman = {"usman", 1000, 0};
    Account nalain = {"nalain", 500, 0};
    Account abdullah = {"abdullah", 500, 0};
    Account alishba = {"alishba", 500, 0};
    
    
    int choice;
    double amount;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Current balance: $" << laiba.balance << endl;
                break;
            case 2:
                cout << "Enter deposit amount: ";
                cin >> amount;
                deposit(laiba, amount);
                break;
            case 3:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                withdraw(laiba, amount);
                break;
            case 4:
                cout << "Enter amount to send to kamla: ";
                cin >> amount;
                sendMoney(laiba, kamla, amount);
                break;
            case 5:
                printTransactionHistory(laiba);
                break;
            case 6:
                  {
                     int *shared_memory;
                      int shmid;
                     shmid=shmget((key_t)1122,sizeof(int),0666);
                     shared_memory=(int*)shmat(shmid,NULL,0);
                      int new_data =*shared_memory+2 ;
                      *shared_memory=new_data;
                      if (shmdt(shared_memory) == -1) 
                      {
                        perror("shmdt error");
                        exit(1);
                      }
                   }
                cout << "GoodBye!" << endl;
                return 0;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}

