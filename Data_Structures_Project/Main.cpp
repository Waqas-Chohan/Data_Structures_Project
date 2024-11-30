#include<iostream>
#include<conio.h>
#include<string>
#include<ctime>
#include <sstream>
#include "HashMap.h"
#include "Graph.h"


using namespace std;


// Utility to get current timestamp
string getCurrentTime() {
    time_t now = time(0);
    char buffer[26];  // Buffer to hold the current time as a string
    ctime_s(buffer, sizeof(buffer), &now);  // Using ctime_s instead of ctime
    return string(buffer);
}
// Node class for linked list (for Stack)
class Node {
public:
    string data;
    Node* next;
    Node(string value) : data(value), next(nullptr) {}
};
// Custom Stack Implementation using Linked List
class Stack {
    Node* top;
public:
    Stack() : top(nullptr) {}

    // Push message onto the stack
    void push(string value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Pop the latest message from the stack
    string pop() {
        if (!top) return "";
        string value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    // Check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Display all messages in the stack (from the latest to the oldest)
    void display() {
        Node* temp = top;
        while (temp) {
            cout << temp->data << "\n";
            temp = temp->next;
        }
    }
};
// Queue implementation using Linked List
class Queue {
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(string value) {
        Node* newNode = new Node(value);
        if (rear) {
            rear->next = newNode;
        }
        else {
            front = newNode;
        }
        rear = newNode;
    }

    string dequeue() {
        if (!front) return "";
        string value = front->data;
        Node* temp = front;
        front = front->next;
        delete temp;
        if (!front) rear = nullptr;
        return value;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void display() {
        Node* temp = front;
        while (temp) {
            cout << "Friend Request from : " << temp->data << "\n";
            temp = temp->next;
        }
    }
};
class User;
// Node for the Binary Search Tree (BST)
class BSTNode {
public:
    string username;
    User* user;  // Pointer to User object
    BSTNode* left;
    BSTNode* right;

    BSTNode(string uname, User* usr) : username(uname), user(usr), left(nullptr), right(nullptr) {}
};
// Custom Binary Search Tree Implementation for user searching
class BST {
    BSTNode* root;
    BSTNode* insert(BSTNode* node, string username, User* user) {
        if (!node) {
            return new BSTNode(username, user);
        }
        if (username < node->username) {
            node->left = insert(node->left, username, user);
        }
        else {
            node->right = insert(node->right, username, user);
        }
        return node;
    }
    BSTNode* search(BSTNode* node, string username) {
        if (!node) return nullptr;
        if (username == node->username) return node;
        if (username < node->username) {
            return search(node->left, username);
        }
        else {
            return search(node->right, username);
        }
    }
    void inOrderTraversal(BSTNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->username << "\n";
            inOrderTraversal(node->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(string username, User* user) {
        root = insert(root, username, user);
    }

    void displayAll() {
        inOrderTraversal(root);
    }

    User* search(string username) {
        BSTNode* node = search(root, username);
        if (node) {
            return node->user;  // Return the User* from the found node
        }
        return nullptr;  // Return nullptr if not found
    }

};
// Class representing a Conversation (between users)
class Conversation {
    string friendUsername;
    Stack messages;  // Stack to store the conversation messages
public:
    Conversation* next;
public:
    Conversation(string friendName) : friendUsername(friendName), next(NULL) {}

    string getFriendUsername() const {
        return friendUsername;
    }

    void sendMessage(string message) {
        messages.push(message);
    }

    void displayMessages() {
        cout << "Messages with " << friendUsername << ":\n";
        messages.display();
    }

    bool hasMessages() {
        return !messages.isEmpty();
    }
};

class User
{
    string username;
    string password;
    string city;
    string lastLogin;
    string security;
    Queue friendRequests;
    Stack posts;
    Queue notifications;
    BST* platformBST;
    // A linked list of Conversation objects (each conversation is between this user and their friend)
    Conversation* conversations;
public:
    time_t lastLogin1;
    User(string uname, string pwd, string c, string sec, BST* bst) : username(uname), password(pwd), city(c), platformBST(bst), security(sec), conversations(nullptr) {}
    User(std::string username) : username(username) {
        lastLogin1 = time(0);  // Store current time as time_t when the user logs in
    }
    bool validatePassword(const string pass) { return pass == password; }
    string getUsername() { return username; }
    string getSecurity() { return security; }
    void resetPassword(const string& newPassword);
    void login() { 
        lastLogin = getCurrentTime(); 
        lastLogin1 = getCurrentTime1();
    }
    void addPost(const string& postContent) { posts.push(postContent); }
    void showProfile();
    void sendMessage(const string& toUser, const string& message);
    void viewMessages(const string& friendUsername);
    void sendFriendRequest(User* toUser);
    void viewFriendRequests(Graph* G);
    bool checkemailpass(string email, string emailPassword);
    void createPost(const string& content);
    void viewPosts();
    void viewNotifications();
    void getStatus();
    bool isActive();
    time_t getCurrentTime1();
    void logout();
    // Helper function to find a conversation with a specific friend
    Conversation* findConversation(const string& friendUsername);
    // Helper function to add a new conversation to the list
    void addConversation(Conversation* conversation);
    friend class MiniInstagram;
};
// Class representing the platform's graph (MiniInstagram)
class MiniInstagram {
private:
    HashMap userCredentials;
public:
    BST userBST;
    Graph userRelations;
    MiniInstagram() {}
    void signup(string& username, const string& password, const string& city, const string& email, User* newUser);
    User* login(string& username, string password);
    void showUsers();
    Graph* getRelations();
};
// Implementing MiniInstagram methods
void MiniInstagram::signup(string& username, const string& password, const string& city, const string& email, User* newUser) {
    while (userBST.search(username) != nullptr)
    {
        cout << "[ USER NAME ALREADY TAKEN ... ENTER NEW USER NAME ]" << endl;
        cout << "Enter username: ";
        cin >> username;
    }
    newUser = new User(username, password, city, email, &userBST);
    userBST.insert(username, newUser);  // Store the User object in the BST
    userCredentials.insert(username, password);
    userRelations.addVertex(username);
    cout << "Signup successful for " << username << "\n";
}

User* MiniInstagram::login(string& username, string password) {
    
    // Search for the user in the BST
    string pass = userCredentials.search(username);
    if (pass == "[Not Found]")
    {
        cout << "[ USER DOES NOT EXIST ... INVALID USER NAME]" << endl;
        return nullptr;
    }

      User* user = userBST.search(username);
    if (pass == password)
    {
        User* user = userBST.search(username);
        user->login();  // Set the last login time
        cout << "Login successful for " << username << "\n";
        return user;  // Exit immediately if login is successful
    }


    //User* user = userBST.search(username);
    //if (!user) {
    //    cout << "User does not exist.\n";
    //    return nullptr;
    //}

    //// Validate the password
    //if (user && user->validatePassword(password)) {
    //    user->login();  // Set the last login time
    //    cout << "Login successful for " << username << "\n";
    //    return user;  // Exit immediately if login is successful
    //}

    cout << "Sorry, your password was incorrect. Please double-check your password.\n";

    while (true) {  // Loop until successful login or user exits
        // Ask for password reset option
        cout << "Forgot Password? (y/n): ";
        char resetChoice;
        resetChoice = _getch();
        cout << endl;
        //cin >> resetChoice;
        

        if (resetChoice == 'y' || resetChoice == 'Y') {
            string security, emailPassword, newPassword;
            cout << "Please Answer Security Question" << endl;
            cout << "Enter your pet name : ";
            cin >> security;

            if (security == user->getSecurity()) {
                // Simulating security verification
               /* cout << "Enter password/verification code sent to your email: ";
                cin >> emailPassword;*/

                //if (user->checkemailpass(security, emailPassword)) {
                    cout << "Security Verification Passed.\n";
                    cout << "Enter a new password: ";
                    cin >> newPassword;
                    user->resetPassword(newPassword);
                    cout << "Password successfully reset.\n";

                    // Retry login with new credentials
                    cout << "Enter the username and new password to login.\n";
                    cin >> username >> password;

                    if (user && user->validatePassword(password)) {
                        user->login();  // Set the last login time
                        cout << "Login successful for " << username << "\n";
                        return user;  // Exit the function after successful login
                    }
                //}

                //else {
                //    cout << "Unable to reset password. Incorrect email or verification code.\n";
                //}
            }
            else {
                cout << "Incorrect answer.\n";
            }
        }
        else {
            // Retry entering the password
            cout << "Enter password again:\n";
            cin >> password;

            if (user && user->validatePassword(password)) {
                user->login();  // Set the last login time
                cout << "Login successful for " << username << "\n";
                return user;  // Exit the function after successful login
            }
            else {
                cout << "Invalid password.\n";
            }
        }
    }
}
// Password reset logic
void  User::resetPassword(const string& newPassword) {

    password = newPassword;  // Reset the password
    cout << "Password reset successful.\n";

}
bool User::checkemailpass(string email, string emailPassword)
{
    if (this->security == email && this->password == emailPassword) {
        return true;
    }
    else return false;
}
void MiniInstagram::showUsers() {
    cout << "All users:\n";
    userBST.displayAll();
}
Graph* MiniInstagram::getRelations()
{
    return &userRelations;
}
//
//// User methods
//void User::showProfile() {
//    cout << "Profile: " << username << "\n";
//    cout << "City: " << city << "\n";
//    cout << "Last Login: " << lastLogin;
//}
/////////////////////////////////////////////
// Friend request functionality in User class
void User::sendFriendRequest(User* toUser) {
    if (toUser) {
        toUser->friendRequests.enqueue(username);
        
        cout << "Friend request sent to " << toUser->getUsername() << ".\n";
    }
}
//bool User:: isActive()
//{
//    time_t now = time(0); // Current time
//    struct tm tmLastLogin = {}; // Structure to hold parsed time
//
//    // Manually parse the date string (assumes "YYYY-MM-DD HH:MM:SS" format)
//    std::stringstream ss(lastLogin);
//    int year, month, day, hour, minute, second;
//
//    ss >> year;
//    ss.ignore(1, '-');
//    ss >> month;
//    ss.ignore(1, '-');
//    ss >> day;
//    ss.ignore(1, ' ');
//    ss >> hour;
//    ss.ignore(1, ':');
//    ss >> minute;
//    ss.ignore(1, ':');
//    ss >> second;
//
//    // Fill the tm structure
//    tmLastLogin.tm_year = year - 1900; // tm_year is years since 1900
//    tmLastLogin.tm_mon = month - 1;    // tm_mon is months since January (0-11)
//    tmLastLogin.tm_mday = day;
//    tmLastLogin.tm_hour = hour;
//    tmLastLogin.tm_min = minute;
//    tmLastLogin.tm_sec = second;
//    tmLastLogin.tm_isdst = -1; // Let mktime determine if daylight saving time is in effect
//
//    // Convert the tm structure to time_t
//    time_t lastActiveTime = mktime(&tmLastLogin);
//
//    if (lastActiveTime == -1) {
//        std::cout << "Error converting tm to time_t.\n";
//        return false;
//    }
//
//    // Check if the user was active within the last 10 seconds
//    return difftime(now, lastActiveTime) <= 10;
//}
// Utility function to get current time

time_t User:: getCurrentTime1() {
    return time(0); // Get current time as time_t
}

//bool User::isActive() {
//    time_t now = getCurrentTime1();  // Get current time
//    double diff = difftime(now, lastLogin1);  // Get difference between now and last login time
//
//    if (diff <= 10) {
//        cout << "The user is being logged in for  " << diff << " seconds.";
//        return true;  // User is active if the difference is less than or equal to 10 seconds
//    }
//    return false;  // User is not active if the difference is greater than 10 seconds
//}
// Check if the user is logged in and calculate login duration
bool User::isActive() {
    if (this == nullptr) {
        return false;  // If the user object is nullptr, they are logged out
    }

    time_t now = getCurrentTime1();  // Get current time
    double diff = difftime(now, lastLogin1);  // Get difference between now and last login time

    if (diff) {
        return true;  // User is active if the difference is less than or equal to 10 seconds
    }
    return false;  // User is not active if the difference is greater 0 seconds
}
void User::logout() {
    // You can add any additional actions needed during logout here
    lastLogin1 = getCurrentTime1();  // Update last login time to current time when the user logs out
    cout << "User " << username << " has been logged out.\n";
}
//string User:: getStatus() {
//    return isActive() ? "Active" : "Offline";
//}
// Function to get the user's status based on whether they are logged in or logged out
void User::getStatus() {
    if (this == nullptr) {
        cout<< "User is logged out"; // User is logged out, since currentUser is nullptr
    }

    time_t now = getCurrentTime1();  // Get current time
    double diff = difftime(now, lastLogin1);  // Get the difference between now and last login/logout time

    if (isActive()) {
        // Check if the time difference is more than or equal to 60 seconds
        if (diff >= 60) {
            int minutes = static_cast<int>(diff) / 60;  // Convert seconds to minutes
            int seconds = static_cast<int>(diff) % 60;  // Get remaining seconds
            cout << "Online (Logged in for " << minutes << " minute(s) and " << seconds << " second(s))" << endl;
        }
        else if (diff < 60) {
            cout << "Online (Logged in for " + to_string(static_cast<int>(diff)) + " seconds)" << endl;
        }
    }
    else {
        // If the user is logged out and the difference is greater than 10 seconds, show Offline
        if (diff > 10) {
            // Check if the time difference is more than or equal to 60 seconds
            if (diff >= 60) {
                int minutes = static_cast<int>(diff) / 60;  // Convert seconds to minutes
                int seconds = static_cast<int>(diff) % 60;  // Get remaining seconds
                cout << "Offline (Logged out for " << minutes << " minute(s) and " << seconds << " second(s))" << endl;
            }
            else {
                cout << "Offline (Logged out for " + to_string(static_cast<int>(diff)) + " seconds)" << endl;
            }
        }
        cout<< "Offline"; // User has been logged out, but it's less than 10 seconds
    }
}
void User::viewFriendRequests(Graph* G) {
    if (friendRequests.isEmpty()) {
        cout << "No pending friend requests.\n";
        return;
    }

    cout << "Pending friend requests:\n";
    friendRequests.display();

    cout << "Do you want to accept/reject a request? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        string request = friendRequests.dequeue();
        cout << "Processing: Request from " << request << "\n";
        cout << "Accept (a) or Reject (r)? ";
        char action;
        cin >> action;

        if (action == 'a' || action == 'A') {
            notifications.enqueue(request + " Started following you.");
            G->addEdge(this->username, request, FOLLOWERS);
            // Update the status of the user who sent the request to FOLLOWING
            if (!G->hasEdge(request, this->username, FOLLOWERS))
            {
                G->modifyRelation(request, this->username, FOLLOWING); // The user who sent the request is now following
            }
            // Check if the other user also follows
            if (G->hasEdge(request, this->username, FOLLOWERS)) {
                
                G->modifyRelation(this->username, request, FRIEND);
                G->modifyRelation(request, this->username, FRIEND);
                cout << "You are now friends with " << request << ".\n";
            }
            else {
                cout << request << " Started following you " << ".\n";
            }
        }
        else {
            cout << "Friend request rejected.\n";
        }
    }
}


//void User::viewFriendRequests(Graph* G) {
//    if (friendRequests.isEmpty()) {
//        cout << "No pending friend requests.\n";
//        return;
//    }
//
//    cout << "Pending friend requests:\n";
//    friendRequests.display();
//
//    cout << "Do you want to accept/reject a request? (y/n): ";
//    char choice;
//    cin >> choice;
//
//    if (choice == 'y' || choice == 'Y') {
//        string request = friendRequests.dequeue();
//        cout << "Processing: Request from " << request << "\n";
//        cout << "Accept (a) or Reject (r)? ";
//        char action;
//        cin >> action;
//
//        if (action == 'a' || action == 'A') {
//            notifications.enqueue("You are now friends with " + request);
//            G->addEdge(this->username, request, FRIEND);
//            cout << "Friend request accepted.\n";
//        }
//        else {
//            cout << "Friend request rejected.\n";
//        }
//    }
//}
// Post functionality in User class
void User::createPost(const string& content) {
    posts.push("Post: " + content + " (" + getCurrentTime() + ")");
    cout << "Post created successfully.\n";
}

void User::viewPosts() {
    if (posts.isEmpty()) {
        cout << "No posts to show.\n";
        return;
    }

    cout << "Your posts:\n";
    posts.display();
}
void User::viewNotifications() {
    if (notifications.isEmpty()) {
        cout << "No notifications.\n";
        return;
    }

    cout << "Notifications:\n";
    notifications.display();
}
void User::showProfile() {
    cout << "Profile of " << username << ":\n";
    cout << "City: " << city << "\n";
    cout << "Email: " << security << "\n";
    cout << "Last Login: " << lastLogin;
    cout << "Recent Posts:\n";
    viewPosts();
    cout << "Notifications:\n";
    viewNotifications();
}

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



// Updated findConversation method
Conversation* User::findConversation(const string& friendUsername) {
    Conversation* current = conversations;
    while (current) {
        if (current->getFriendUsername() == friendUsername) {
            return current;
        }
        current = current->next;  // Move to the next conversation
    }
    return nullptr;
}

// Add new conversation to the linked list
void User::addConversation(Conversation* conversation) {
    if (!conversations) {
        conversations = conversation;
    }
    else {
        Conversation* temp = conversations;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = conversation;
    }
}
void User::sendMessage(const string& toUser, const string& message) {
    // Find the conversation for the friend (create one if not found)
    Conversation* senderConversation = findConversation(toUser);
    if (!senderConversation) {
        senderConversation = new Conversation(toUser);
        addConversation(senderConversation);  // Add the new conversation to the sender's list
    }
    senderConversation->sendMessage("You: " + message);  // Mark as sent by the user

    // Find the recipient user
    User* recipient = platformBST->search(toUser);
    if (recipient) {
        // Find or create the recipient's conversation for the current user
        Conversation* recipientConversation = recipient->findConversation(username);
        if (!recipientConversation) {
            recipientConversation = new Conversation(username);
            recipient->addConversation(recipientConversation);  // Add to recipient's list
        }
        recipientConversation->sendMessage(username + ": " + message);  // Mark as received
    }
    else {
        cout << "Error: Recipient user not found.\n";
    }
}


void User::viewMessages(const string& friendUsername) {
    Conversation* conversation = findConversation(friendUsername);
    if (conversation) {
        conversation->displayMessages();
    }
    else {
        cout << "No conversation with " << friendUsername << ".\n";
    }
}


int main()
{
    MiniInstagram platform;
    User* currentUser = nullptr;

    while (true) {
        int choice;
        cout << "\nMenu:\n"
            << "1. Signup\n"
            << "2. Login\n"
            << "3. Show All Users\n"
            << "4. Send Message\n"
            << "5. View Messages\n"
            << "6. Send Friend Request\n"
            << "7. View Friend Requests\n"
            << "8. Create Post\n"
            << "9. View Posts\n"
            << "10. View Notifications\n"
            << "11. Show Profile\n"
            << "12. Logout\n"
            << "13. Exit\n"
            << "14. Show Relations\n"
            << "15. Modify Relation\n"
            << "16. Show Status\n"
            << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string username, password, city, security;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter city: ";
            cin >> city;
            cout << "Enter your pet name as security answer:";
            cin >> security;
            User* newUser = nullptr;
            platform.signup(username, password, city, security, newUser);
        }
        else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            currentUser = platform.login(username, password);
        }
        else if (choice == 3) {
            platform.showUsers();
        }
        else if (choice == 4) {
            if (currentUser) {
                string friendUsername, message;
                cout << "Enter friend's username: ";
                cin >> friendUsername;
                cout << "Enter your message: ";
                cin >> ws;  // To handle space before message input
                getline(cin, message);
                currentUser->sendMessage(friendUsername, message);
            }
            else {
                cout << "No user currently logged in.\n";
            }
        }
        else if (choice == 5) {
            if (currentUser) {
                string friendUsername;
                cout << "Enter friend's username: ";
                cin >> friendUsername;
                currentUser->viewMessages(friendUsername);
            }
            else {
                cout << "No user currently logged in.\n";
            }
        }
        else if (choice == 6) {
            if (currentUser) {
                string friendUsername;
                cout << "Enter friend's username: ";
                cin >> friendUsername;
                User* friendUser = platform.userBST.search(friendUsername);
                if (friendUser) {
                    currentUser->sendFriendRequest(friendUser);
                    platform.userRelations.addEdge(currentUser->getUsername(), friendUsername, PENDING);
                }
                else {
                    cout << "User not found.\n";
                }
            }
            else {
                cout << "No user currently logged in.\n";
            }
        }
        else if (choice == 7) {
            if (currentUser) {
                currentUser->viewFriendRequests(platform.getRelations());
            }
            else {
                cout << "No user currently logged in.\n";
            }
        }
        else if (choice == 8) {
            if (currentUser) {
                string postContent;
                cout << "Enter post content: ";
                cin >> ws;
                getline(cin, postContent);
                currentUser->createPost(postContent);
            }
            else {
                cout << "No user currently logged in.\n";
            }
        }
        else if (choice == 9) {
            if (currentUser) {
                currentUser->viewPosts();
            }
            else {
                cout << "No user currently logged in.\n";
            }
        }
        else if (choice == 10) {
            if (currentUser) {
                currentUser->viewNotifications();
            }
            else {
                cout << "No user currently logged in.\n";
            }
        }
        else if (choice == 11) {
            if (currentUser) {
                currentUser->showProfile();
            }
            else {
                cout << "No user currently logged in.\n";
            }

        }
        else if (choice == 12) { // Logout
            if (currentUser) {
                currentUser->logout();  // Call logout function if user is logged in
                currentUser = nullptr;  // Set currentUser to nullptr to indicate no user is logged in
                cout << "Logout successful.\n";
            }
            else {
                cout << "No user currently logged in.\n";
            }
            }
        else if (choice == 14) { // Show Relations
            if (currentUser) {
                std::cout << "Relations:\n";
                platform.getRelations()->showRelations(currentUser->getUsername());
            }
            else {
                std::cout << "No user currently logged in.\n";
            }
            }
        else if (choice == 15) { // Modify Relation
                if (currentUser) {
                    std::string friendUsername;
                    int newRelationStatus;
                    std::cout << "Enter username to modify relation: ";
                    std::cin >> friendUsername;

                    std::cout << "Choose new relation status:\n";
                    std::cout << "1. Friend\n";
                    std::cout << "2. Family\n";
                    std::cout << "3. Blocked\n";
                    std::cout << "Choice: ";
                    std::cin >> newRelationStatus;

                    if (newRelationStatus >= 1 && newRelationStatus <= 3) {
                        RelationStatus newStatus = static_cast<RelationStatus>(newRelationStatus - 1);
                        platform.getRelations()->modifyRelation(currentUser->getUsername(), friendUsername, newStatus);
                    }
                    else {
                        std::cout << "Invalid choice.\n";
                    }
                }
                else {
                    std::cout << "No user currently logged in.\n";
                }
                }
        else if (choice == 16) { // Show User Status
                    platform.showUsers();
                    string user;
                    cout << "Enter username to check status: ";
                    cin >> user;
                    User* targetUser = platform.userBST.search(user);
                    if (targetUser) {
                        if (currentUser) {
                            cout << "User " << currentUser->getUsername() << " is currently: ";
                            currentUser->getStatus() ;
                        }
                        else {
                            cout << "No user currently logged in.\n";
                            time_t now = targetUser->getCurrentTime1();  // Get current time
                            double diff = difftime(now, targetUser->lastLogin1);  // Get the difference between now and last login time
                            // Check if the time difference is more than or equal to 60 seconds
                            if (diff >= 60) {
                                int minutes = static_cast<int>(diff) / 60;  // Convert seconds to minutes
                                int seconds = static_cast<int>(diff) % 60;  // Get remaining seconds
                                cout << "Offline (Logged out for " << minutes << " minute(s) and " << seconds << " second(s))" << endl;
                            }
                            else {
                                cout << "Offline (Logged out for " + to_string(static_cast<int>(diff)) + " seconds)" << endl;
                            }
                        }
                    }
                    else {
                        cout << "User not found.\n";
                    }
                    }

    }

    return 0;

}