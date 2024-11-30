#include<iostream>
#include<string>
#include<ctime>

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
    void display () {
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
            cout << temp->data << "\n";
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
    Conversation(string friendName) : friendUsername(friendName),next(NULL) {}

    string getFriendUsername() const {
        return friendUsername;
    }

    void sendMessage(string message) {
        messages.push(message);
    }

    void displayMessages()  {
        cout << "Messages with " << friendUsername << ":\n";
        messages.display();
    }

    bool hasMessages()  {
        return !messages.isEmpty();
    }
};

class User
{
    string username;
    string password;
    string city;
    string lastLogin;
    string email;
    Queue friendRequests;
    Stack posts;
    Queue notifications;
    BST* platformBST;
    // A linked list of Conversation objects (each conversation is between this user and their friend)
    Conversation* conversations;
public:
    User(string uname, string pwd, string c,string em ,BST* bst) : username(uname), password(pwd), city(c), platformBST(bst), email(em),conversations(nullptr) {}

    bool validatePassword(const string pass) { return pass ==password ; }
    string getUsername() { return username; }
    string getEmail() { return email; }
    void resetPassword( const string& newPassword);
    void login() { lastLogin = getCurrentTime(); }
    void addPost(const string& postContent) { posts.push(postContent); }
    void showProfile();
    void sendMessage(const string& toUser, const string& message);
    void viewMessages(const string& friendUsername);
    void sendFriendRequest(User* toUser);
    void viewFriendRequests();
    bool checkemailpass(string email,string emailPassword);
    void createPost(const string& content);
    void viewPosts();
    void viewNotifications();
    // Helper function to find a conversation with a specific friend
    Conversation* findConversation(const string& friendUsername);
    // Helper function to add a new conversation to the list
    void addConversation(Conversation* conversation);
    friend class MiniInstagram;
};
// Class representing the platform's graph (MiniInstagram)
class MiniInstagram {
   
public:
    BST userBST;
    MiniInstagram() {}

    void signup(const string& username, const string& password, const string& city, const string& email, User* newUser);
    User* login( string& username,  string password);
    void showUsers();
};
// Implementing MiniInstagram methods
void MiniInstagram::signup(const string& username, const string& password, const string& city, const string& email, User* newUser) {
    newUser = new User(username, password, city,email, &userBST);
    userBST.insert(username, newUser);  // Store the User object in the BST
    cout << "Signup successful for " << username << "\n";
}

User* MiniInstagram::login(string& username, string password) {
    // Search for the user in the BST
    User* user = userBST.search(username);
    if (!user) {
        cout << "User does not exist.\n";
        return nullptr;
    }

    // Validate the password
    if (user && user->validatePassword(password)) {
        user->login();  // Set the last login time
        cout << "Login successful for " << username << "\n";
        return user;  // Exit immediately if login is successful
    }

    cout << "Sorry, your password was incorrect. Please double-check your password.\n";

    while (true) {  // Loop until successful login or user exits
        // Ask for password reset option
        cout << "Forgot Password? (y/n): ";
        char resetChoice;
        cin >> resetChoice;

        if (resetChoice == 'y' || resetChoice == 'Y') {
            string email, emailPassword, newPassword;
            cout << "Enter the email linked to your account: ";
            cin >> email;

            if (email == user->getEmail()) {
                // Simulating email verification
                cout << "Enter password/verification code sent to your email: ";
                cin >> emailPassword;

                if (user->checkemailpass(email, emailPassword)) {
                    cout << "Email Verified.\n";
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
                }
                else {
                    cout << "Unable to reset password. Incorrect email or verification code.\n";
                }
            }
            else {
                cout << "Incorrect email linked to the account.\n";
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
bool User:: checkemailpass(string email,string emailPassword)
{
    if (this->email == email && this->password == emailPassword) {
        return true;
    }
    else return false;
}
void MiniInstagram::showUsers() {
    cout << "All users:\n";
    userBST.displayAll();
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
        toUser->friendRequests.enqueue("Friend request from " + username);
        cout << "Friend request sent to " << toUser->getUsername() << ".\n";
    }
}

void User::viewFriendRequests() {
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
        cout << "Processing: " << request << "\n";
        cout << "Accept (a) or Reject (r)? ";
        char action;
        cin >> action;

        if (action == 'a' || action == 'A') {
            notifications.enqueue("You are now friends with " + request);
            cout << "Friend request accepted.\n";
        }
        else {
            cout << "Friend request rejected.\n";
        }
    }
}
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
    cout << "Email: " << email << "\n";
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
    Conversation* conversation = findConversation(toUser);
    if (!conversation) {
        conversation = new Conversation(toUser);
        addConversation(conversation);  // Add the new conversation to the list
    }
    conversation->sendMessage(message);
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
            << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string username, password, city,email;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter city: ";
            cin >> city;
            cout << "Enter email:";
            cin >> email;
            User* newUser = nullptr;
            platform.signup(username, password, city,email, newUser);
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
                currentUser->viewFriendRequests();
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
    }

    return 0;
	
}