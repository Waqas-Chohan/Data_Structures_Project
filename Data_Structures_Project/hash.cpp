//#include "HashMap.h"
//#include <iostream>
//#include <limits> // For clearing input buffer
//
//using namespace std;
//
//// Function to display the menu
//void displayMenu() {
//    cout << "\n--- HashMap Menu ---\n";
//    cout << "1. Insert Key-Value Pair\n";
//    cout << "2. Search for a Key\n";
//    cout << "3. Remove a Key\n";
//    cout << "4. Display HashMap\n";
//    cout << "5. Exit\n";
//    cout << "Enter your choice: ";
//}
//
//int main() {
//    HashMap map; // Create an instance of HashMap
//    int choice;
//    string key, value;
//
//    do {
//        displayMenu();
//        cin >> choice;
//        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
//
//        switch (choice) {
//        case 1: // Insert Key-Value Pair
//            cout << "Enter key: ";
//            getline(cin, key); // Allow keys with spaces
//            cout << "Enter value: ";
//            getline(cin, value); // Allow values with spaces
//            map.insert(key, value);
//            cout << "Key-Value pair inserted.\n";
//            break;
//
//        case 2: // Search for a Key
//            cout << "Enter key to search: ";
//            getline(cin, key);
//            value = map.search(key);
//            cout << "Search result: " << value << "\n";
//            break;
//
//        case 3: // Remove a Key
//            cout << "Enter key to remove: ";
//            getline(cin, key);
//            map.remove(key);
//            break;
//
//        case 4: // Display HashMap
//            cout << "HashMap contents:\n";
//            map.display();
//            break;
//
//        case 5: // Exit
//            cout << "Exiting the program. Goodbye!\n";
//            break;
//
//        default:
//            cout << "Invalid choice! Please try again.\n";
//        }
//    } while (choice != 5);
//
//    return 0;
//}
