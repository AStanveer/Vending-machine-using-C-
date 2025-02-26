#include <iostream>
#include <string>
using namespace std;
#define MAX 100

class TestKit {
private:
    int id;
public:
    TestKit(int id = 0) : id(id) {}

    int getId() const {
        return id;
    }

    void display() const {
        cout << "ID: " << id << endl;
    }
};

class Queue {
private:
    TestKit kits[MAX];
    int front;
    int rear;
    int count;

public:
    Queue() : front(0), rear(-1), count(0) {}

    bool isFull() {
        return count == MAX;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool hasID(const int id) {
        for (int i = 0; i < count; i++) {
            if (kits[(front + i) % MAX].getId() == id) {
                return true;
            }
        }
        return false;
    }

    void enqueue(const TestKit& kit) {
        if (isFull()) {
            cout << "Swab test kit fully stocked..cannot add more to the stock!\n";
            return;
        }
        rear = (rear + 1) % MAX;
        kits[rear] = kit;
        count++;
    }

    TestKit dequeue() {
        if (isEmpty()) {
            cout << "Swab test kit out of stock!\n";
            return TestKit(); // Return a default TestKit
        }
        TestKit kit = kits[front];
        front = (front + 1) % MAX;
        count--;
        return kit;
    }

    TestKit peek() {
        if (isEmpty()) {
            cout << "Swab test kit out of stock!\n";
            return TestKit(); // Return a default TestKit
        }
        return kits[front];
    }

    void display() {
        if (isEmpty()) {
            cout << "Swab test kit out of stock!\n";
            return;
        }
        cout << "Swab test kits available:\n";
        for (int i = 0; i < count; i++) {
            kits[(front + i) % MAX].display();
        }
    }
};

class Payment {
public:
    static bool makePayment() {
        string duit;
        cout << "Cost of Swab Test kit is RM 50\n";
        
        // Keep asking for duit account number until it's len is 8 or more and less than 13
        while (true) {
            cout << "Enter your 8 digit duit account number: ";
            cin >> duit;

            if (duit.length() != 8 ) {
                cout << "Invalid duit account number! Please enter again.\n";
            } 
            else {
                cout << "Payment successful!\n";
                return true; // Payment was successful
            }
        }
    }
};


int main() {
    Queue swabTestMachine;
    int totalProfit = 0; // Track total profit
    int choice, choice2, kitId;

    do {
        cout << "\nSwab Test Vendor Machine\n";
        cout << "1. Vendor\n";
        cout << "2. Buyer\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Vendor
                do {
                    cout << "\nVendor Menu\n";
                    cout << "1. Load Test Kit\n";
                    cout << "2. View Profits\n";
                    cout << "3. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice2;

                    switch (choice2) {
                        case 1:
                            do {
                                cout << "Enter test kit ID: ";
                                cin >> kitId;
                                cin.ignore(); // Clear newline from buffer

                                if (swabTestMachine.hasID(kitId)) {
                                    cout << "Test kit with the same ID already exists. Please enter a different ID.\n";
                                } 
                                else {
                                    swabTestMachine.enqueue(TestKit(kitId));
                                    break; // Exit the loop when a valid ID is entered
                                }
                            }
                            while (true); // Keep looping until valid input is provided
                            break;

                        case 2:
                            cout << "Total profit: RM " << totalProfit << endl;
                            break;

                        case 3:
                            cout << "Exiting...\n";
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }
                } 
                while (choice2 != 3);
                break;

            case 2: // Buyer
                do {
                    cout << "\nBuyer Menu\n";
                    cout << "1. Dispense Test Kit\n";
                    cout << "2. View Next Test Kit\n";
                    cout << "3. View All Available Kits\n";
                    cout << "4. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice2;

                    switch (choice2) {
                        case 1:
                            if (Payment::makePayment()) { // Make payment for dispense
                                TestKit dispensedKit = swabTestMachine.dequeue();
                                if (dispensedKit.getId() != 0) {
                                    cout << "Dispensed test kit:\n";
                                    dispensedKit.display();
                                    totalProfit += 50; // Add to total profit after successful payment
                                }
                            }
                            break;
                        case 2:
                            {
                                TestKit nextKit = swabTestMachine.peek();
                                if (nextKit.getId() != 0) {
                                    cout << "Next test kit to dispense:\n";
                                    nextKit.display();
                                }
                            }
                            break;
                        case 3:
                            swabTestMachine.display();
                            break;
                        case 4:
                            cout << "Exiting...\n";
                            break;
                        default:
                            cout << "Invalid choice!\n";
                    }
                } 
                while (choice2 != 4);
                break;

            case 3:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } 
    while (choice != 3);

    return 0;
}
