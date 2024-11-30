//#include <iostream>
//#include <string>
//#include <ctime>
//using namespace std;
//
//// Utility to get current timestamp
//string getCurrentTime() {
//    time_t now = time(0);
//    return ctime(&now);
//}
//
//// Node class for linked list (for Stack)
//class Node {
//public:
//    string data;
//    Node* next;
//    Node(string value) : data(value), next(nullptr) {}
//};
//
//// Custom Stack Implementation using Linked List
//class Stack {
//    Node* top;
//public:
//    Stack() : top(nullptr) {}
//
//    // Push message onto the stack
//    void push(string value) {
//        Node* newNode = new Node(value);
//        newNode->next = top;
//        top = newNode;
//    }
//
//    // Pop the latest message from the stack
//    string pop() {
//        if (!top) return "";
//        string value = top->data;
//        Node* temp = top;
//        top = top->next;
//        delete temp;
//        return value;
//    }
//
//    // Check if stack is empty
//    bool isEmpty() {
//        return top == nullptr;
//    }
//
//    // Display all messages in the stack (from the latest to the oldest)
//    void display() {
//        Node* temp = top;
//        while (temp) {
//            cout << temp->data << "\n";
//            temp = temp->next;
//        }
//    }
//};
//// Queue implementation using Linked List
//class Queue {
//    Node* front;
//    Node* rear;
//public:
//    Queue() : front(nullptr), rear(nullptr) {}
//
//    void enqueue(string value) {
//        Node* newNode = new Node(value);
//        if (rear) {
//            rear->next = newNode;
//        }
//        else {
//            front = newNode;
//        }
//        rear = newNode;
//    }
//
//    string dequeue() {
//        if (!front) return "";
//        string value = front->data;
//        Node* temp = front;
//        front = front->next;
//        delete temp;
//        if (!front) rear = nullptr;
//        return value;
//    }
//
//    bool isEmpty() {
//        return front == nullptr;
//    }
//
//    void display() {
//        Node* temp = front;
//        while (temp) {
//            cout << temp->data << "\n";
//            temp = temp->next;
//        }
//    }
//};
//
//// Node for the Binary Search Tree (BST)
//class BSTNode {
//public:
//    string username;
//    BSTNode* left;
//    BSTNode* right;
//    BSTNode(string uname) : username(uname), left(nullptr), right(nullptr) {}
//};
//
//// Custom Binary Search Tree Implementation for user searching
//class BST {
//    BSTNode* root;
//
//    BSTNode* insert(BSTNode* node, string username) {
//        if (!node) return new BSTNode(username);
//        if (username < node->username) {
//            node->left = insert(node->left, username);
//        }
//        else {
//            node->right = insert(node->right, username);
//        }
//        return node;
//    }
//
//    void inOrderTraversal(BSTNode* node) {
//        if (node) {
//            inOrderTraversal(node->left);
//            cout << node->username << "\n";
//            inOrderTraversal(node->right);
//        }
//    }
//
//public:
//    BST() : root(nullptr) {}
//
//    void insert(string username) {
//        root = insert(root, username);
//    }
//
//    void displayAll() {
//        inOrderTraversal(root);
//    }
//
//    bool search(string username) {
//        BSTNode* current = root;
//        while (current) {
//            if (current->username == username) return true;
//            if (username < current->username) {
//                current = current->left;
//            }
//            else {
//                current = current->right;
//            }
//        }
//        return false;
//    }
//};
//
//// Forward declaration of User class
//class User;
//
//// Class representing the platform's graph (MiniInstagram)
//class MiniInstagram {
//    BST userBST;
//public:
//    MiniInstagram() {}
//
//    void signup(const string& username, const string& password, const string& city, User* newUser);
//    User* login(const string& username, const string& password);
//    void showUsers();
//};
//
//// Class representing a Conversation (between users)
//class Conversation {
//    string friendUsername;
//    Stack messages;  // Stack to store the conversation messages
//public:
//    Conversation(string friendName) : friendUsername(friendName) {}
//
//    string getFriendUsername() const {
//        return friendUsername;
//    }
//
//    void sendMessage(string message) {
//        messages.push(message);
//    }
//
//    void displayMessages() const {
//        cout << "Messages with " << friendUsername << ":\n";
//        messages.display();
//    }
//
//    bool hasMessages() const {
//        return !messages.isEmpty();
//    }
//};
//
//// Class representing a User
//class User {
//    string username;
//    string password;
//    string city;
//    string lastLogin;
//    Stack posts;
//    BST* platformBST;
//
//    // A linked list of Conversation objects (each conversation is between this user and their friend)
//    Conversation* conversations;
//public:
//    User(string uname, string pwd, string c, BST* bst) : username(uname), password(pwd), city(c), platformBST(bst), conversations(nullptr) {}
//
//    bool validatePassword(const string& pwd) { return password == pwd; }
//    string getUsername() { return username; }
//    void login() { lastLogin = getCurrentTime(); }
//    void addPost(const string& postContent) { posts.push(postContent); }
//    void showProfile();
//    void sendMessage(const string& toUser, const string& message);
//    void viewMessages(const string& friendUsername);
//
//    // Helper function to find a conversation with a specific friend
//    Conversation* findConversation(const string& friendUsername);
//
//    friend class MiniInstagram;
//};
//
//// Implementing MiniInstagram methods
//void MiniInstagram::signup(const string& username, const string& password, const string& city, User* newUser) {
//    userBST.insert(username);
//    newUser = new User(username, password, city, &userBST);
//    cout << "Signup successful for " << username << "\n";
//}
//
//User* MiniInstagram::login(const string& username, const string& password) {
//    if (!userBST.search(username)) {
//        cout << "User does not exist.\n";
//        return nullptr;
//    }
//    User* user = new User(username, password, "City", &userBST);  // Assume city is "City" for now
//    if (user->validatePassword(password)) {
//        user->login();
//        cout << "Login successful for " << username << "\n";
//        return user;
//    }
//    cout << "Invalid password.\n";
//    return nullptr;
//}
//
//void MiniInstagram::showUsers() {
//    cout << "All users:\n";
//    userBST.displayAll();
//}
//
//// User methods
//void User::showProfile() {
//    cout << "Profile: " << username << "\n";
//    cout << "City: " << city << "\n";
//    cout << "Last Login: " << lastLogin;
//}
//
//void User::sendMessage(const string& toUser, const string& message) {
//    // Find the conversation for the friend (create one if not found)
//    Conversation* conversation = findConversation(toUser);
//    if (!conversation) {
//        conversation = new Conversation(toUser);
//        conversation->sendMessage("Message sent to " + toUser + ": " + message);
//    }
//    else {
//        conversation->sendMessage("Message sent to " + toUser + ": " + message);
//    }
//}
//
//void User::viewMessages(const string& friendUsername) {
//    Conversation* conversation = findConversation(friendUsername);
//    if (conversation) {
//        conversation->displayMessages();
//    }
//    else {
//        cout << "No conversation with " << friendUsername << ".\n";
//    }
//}
//
//// Helper function to find a conversation with a specific friend
//Conversation* User::findConversation(const string& friendUsername) {
//    Conversation* current = conversations;
//    while (current) {
//        if (current->getFriendUsername() == friendUsername) return current;
//        current = current->next;
//    }
//    return nullptr;
//}
//
//// Main Program
//int main() {
//    MiniInstagram platform;
//    User* currentUser = nullptr;
//
//    while (true) {
//        int choice;
//        cout << "\nMenu:\n1. Signup\n2. Login\n3. Show All Users\n4. Send Message\n5. View Messages\n6. Logout\n7. Exit\nChoice: ";
//        cin >> choice;
//
//        if (choice == 1) {
//            string username, password, city;
//            cout << "Enter username: ";
//            cin >> username;
//            cout << "Enter password: ";
//            cin >> password;
//            cout << "Enter city: ";
//            cin >> city;
//            User* newUser = nullptr;
//            platform.signup(username, password, city, newUser);
//        }
//        else if (choice == 2) {
//            string username, password;
//            cout << "Enter username: ";
//            cin >> username;
//            cout << "Enter password: ";
//            cin >> password;
//            currentUser = platform.login(username, password);
//        }
//        else if (choice == 3) {
//            platform.showUsers();
//        }
//        else if (choice == 4) {
//            if (currentUser) {
//                string friendUsername, message;
//                cout << "Enter friend's username: ";
//                cin >> friendUsername;
//                cout << "Enter your message: ";
//                cin >> ws;  // To handle space before message input
//                getline(cin, message);
//                currentUser->sendMessage(friendUsername, message);
//            }
//            else {
//                cout << "No user currently logged in.\n";
//            }
//        }
//        else if (choice == 5) {
//            if (currentUser) {
//                string friendUsername;
//                cout << "Enter friend's username: ";
//                cin >> friendUsername;
//                currentUser->viewMessages(friendUsername);
//            }
//            else {
//                cout << "No user currently logged in.\n";
//            }
//        }
//        else if (choice == 6) {
//            if (currentUser) {
//                cout << "Logged out successfully.\n";
//                currentUser = nullptr;
//            }
//            else {
//                cout << "No user currently logged in.\n";
//            }
//        }
//        else if (choice == 7) {
//            break;
//        }
//    }
//
//    return 0;
//}
