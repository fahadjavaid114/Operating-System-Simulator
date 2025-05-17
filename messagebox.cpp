#include <iostream>
#include <string>
#include <cstring>
#include<sys/shm.h>
using namespace std;

const int MAX_USERS = 10;
const int MAX_MESSAGES = 10;

struct Message {
    std::string sender;
    std::string content;
};

struct User {
    std::string name;
    Message messages[MAX_MESSAGES];
    int message_count;
};

User users[MAX_USERS];
int user_count = 0;

void addUser(const std::string& name) {
    if (user_count < MAX_USERS) {
        users[user_count].name = name;
        users[user_count].message_count = 0;
        user_count++;
    }
}

int findUser(const std::string& name) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].name == name) {
            return i;
        }
    }
    return -1;
}

void sendMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
    int senderIndex = findUser(sender);
    int receiverIndex = findUser(receiver);

    if (senderIndex == -1 || receiverIndex == -1) {
        std::cout << "User not found." << std::endl;
        return;
    }

    if (users[receiverIndex].message_count < MAX_MESSAGES) {
        users[receiverIndex].messages[users[receiverIndex].message_count].sender = sender;
        users[receiverIndex].messages[users[receiverIndex].message_count].content = message;
        users[receiverIndex].message_count++;
    }
}

void readMessages(const std::string& user) {
    int userIndex = findUser(user);
    if (userIndex == -1) {
        std::cout << "User not found." << std::endl;
        return;
    }

    for (int i = 0; i < users[userIndex].message_count; i++) {
        std::cout << users[userIndex].messages[i].sender << ": " << users[userIndex].messages[i].content << std::endl;
    }
    users[userIndex].message_count = 0;
}

int main() {
int *shared_memory;
int shmid;
shmid=shmget((key_t)1122,sizeof(int),0666);

shared_memory=(int*)shmat(shmid,NULL,0);
int new_data =*shared_memory-30 ;
*shared_memory=new_data;

if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }
    
    addUser("kamla");
    addUser("laiba");
    addUser("ayesha");
    addUser("saad");

    std::string command;
    while (true) {
    	cout<<"You have kamla , laiba , ayesha, saad in you contact list only"<<endl;
        std::cout << "Enter command (send, read, exit): ";
        std::cin >> command;

        if (command == "send") {
            std::string sender, receiver, message;
            std::cout << "Enter sender: ";
            std::cin >> sender;
            std::cout << "Enter receiver: ";
            std::cin >> receiver;
            std::cin.ignore();
            std::cout << "Enter message: ";
            std::getline(std::cin, message);
            sendMessage(sender, receiver, message);
        } else if (command == "read") {
            std::string user;
            std::cout << "Enter user: ";
            std::cin >> user;
            readMessages(user);
        } else if (command == "exit") {
        int *shared_memory;
int shmid;
shmid=shmget((key_t)1122,sizeof(int),0666);

shared_memory=(int*)shmat(shmid,NULL,0);
int new_data =*shared_memory+30;
*shared_memory=new_data;

if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }
    return 0;
            break;
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }

    return 0;
}

