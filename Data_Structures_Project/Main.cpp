#include<iostream>
#include<conio.h>
#include<string>
#include<ctime>
#include<regex>
#include <sstream>
#include "HashMap.h"
#include "Graph.h"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


using namespace std;


void showError(string s) {
    cout << RED << s << RESET << endl;
}

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
            cout << temp->data << "" << endl;
            temp = temp->next;
        }
    }
    // Return the top element of the stack (no modification)
    string gettop() {
        Node* temp=top;
        if (!temp) return "";  // Return an empty string if stack is empty
        return temp->data;  // Return the data of the top node
    }
    // Copy function to create and return a new stack
    Stack copy() const {
        Stack newStack;
        if (!top) return newStack; // Return empty stack if the original is empty

        // Use a temporary stack to reverse the order of elements
        Stack tempStack;

        // Traverse the original stack and push elements into tempStack
        Node* current = top;
        while (current) {
            tempStack.push(current->data);
            current = current->next;
        }

        // Pop elements from tempStack into newStack to maintain original order
        while (!tempStack.isEmpty()) {
            newStack.push(tempStack.pop());
        }

        return newStack;
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

    void displayAndClear() {
        if (!front)
        {
            cout << "No Notifications to show." << endl;
        }
        while (front) {
            cout << front->data << "" << endl;
            front = front->next;
        }
        front = rear = nullptr;
    }

    void display() {
        Node* temp = front;
        while (temp) {
            cout << temp->data << "" << endl;
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
            cout << node->username << "" << endl;
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
    
    bool isEmpty() {
        return root == nullptr;
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
        cout << "Messages with " << friendUsername << ":" << endl;
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
    Stack timeline;
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
    //void createPost(const string& content);
    void createPost(const std::string& content, Graph* relationshipGraph);
    void viewPosts();
    void viewNotifications();
    void getStatus();
    bool isActive();
    void viewTimeline();
    time_t getCurrentTime1();
    void logout();
    Stack getPosts();
    void populateTimeline(Graph* relationshipGraph);
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
        cout << RED << "[ USER NAME ALREADY TAKEN ... ENTER NEW USER NAME ]"  << RESET<< endl;
        cout << "Enter username: ";
        cin >> username;
    }
    newUser = new User(username, password, city, email, &userBST);
    userBST.insert(username, newUser);  // Store the User object in the BST
    userCredentials.insert(username, password);
    userRelations.addVertex(username);
    cout << GREEN << "[ Signup successful for " << username << " ]" << RESET << endl;
}

User* MiniInstagram::login(string& username, string password) {
    
    // Search for the user in the BST
    string pass = userCredentials.search(username);
    if (pass == "[Not Found]")
    {
        cout << RED << "[ USER DOES NOT EXIST ... INVALID USER NAME]" << RESET << endl;
        return nullptr;
    }

      User* user = userBST.search(username);
    if (pass == password)
    {
        User* user = userBST.search(username);
        user->login();  // Set the last login time
        cout << GREEN <<  "Login successful for " << username << RESET << endl;
        return user;  // Exit immediately if login is successful
    }

    cout << RED << "[ PASSWORD INCORRECT ]" << RESET << endl;

    while (true) {  // Loop until successful login or user exits
        // Ask for password reset option
        cout << "Forgot Password? (y/n): ";
        char resetChoice;
        resetChoice = _getch();
        cout << endl;
        //cin >> resetChoice;
        

        if (resetChoice == 'y' || resetChoice == 'Y') {
            string security, emailPassword, newPassword;
            cout << "Enter answer of Security Question" << endl;
            cout << "What is your pet's name : ";
            cin >> security;

            if (security == user->getSecurity()) {

                    cout << "Security Verification Passed." << endl;
                    cout << "Enter a new password: ";
                    cin >> newPassword;
                    user->resetPassword(newPassword);
                    cout << "Password successfully reset." << endl;

                    // Retry login with new credentials
                    cout << "Enter the username and new password to login." << endl;
                    cin >> username >> password;

                    if (user && user->validatePassword(password)) {
                        user->login();  // Set the last login time
                        cout << "Login successful for " << username << "" << endl;
                        return user;  // Exit the function after successful login
                    }
            }
            else {
                cout << RED << "[ INCORRECT ANSWER ]" << RESET << endl;
            }
        }
        else {
            // Retry entering the password
            cout << "Re-Enter password :" << endl;
            cin >> password;

            if (user && user->validatePassword(password)) {
                user->login();  // Set the last login time
                cout << GREEN << "Login successful for " << username << RESET << endl;;
                return user;  // Exit the function after successful login
            }
            else {
                cout << RED << "[ INVALID PASSWORD ]" << RESET << endl;;
            }
        }
    }
}
// Password reset logic
void  User::resetPassword(const string& newPassword) {

    password = newPassword;  // Reset the password
    cout << "Password reset successful." << endl;

}
bool User::checkemailpass(string email, string emailPassword)
{
    if (this->security == email && this->password == emailPassword) {
        return true;
    }
    else return false;
}
Stack User::getPosts()
{
     if (!posts.isEmpty())
     {
         return posts;
     }
     else cout << "Ther is no post.";
     return posts;
}
void User::populateTimeline(Graph* relationshipGraph) {
    // Clear the current timeline
    while (!timeline.isEmpty()) {
        timeline.pop();
    }

    // Get the list of followers
    std::vector<std::string> followers = relationshipGraph->getFollowers(username);
    if (followers.empty()) {
        std::cout << "No followers to fetch posts from." << endl;
        return;
    }

    // Fetch posts from each follower and push them to the timeline
    for (const std::string& follower : followers) {
        Vertex* followerVertex = relationshipGraph->findVertex(follower);
        if (!followerVertex) continue;

        // Assuming we can access the `posts` stack of a user (retrieve by username)
        User* followerUser = platformBST->search(follower); // Platform BST to retrieve user by username
        if (!followerUser) continue;

        Stack followerPosts = followerUser->getPosts(); // Assume `getPosts` returns the stack of posts
        Stack tempPosts; // Temporary stack to reverse order (latest posts first)

        // Reverse order to maintain chronological order in timeline
        while (!followerPosts.isEmpty()) {
            tempPosts.push(followerPosts.gettop());
            followerPosts.pop();
        }

        // Push reversed posts into timeline
        while (!tempPosts.isEmpty()) {
            timeline.push(follower + ": " + tempPosts.gettop());
            tempPosts.pop();
        }
    }

    std::cout << "Timeline updated successfully." << endl;
}

void MiniInstagram::showUsers() {
    if (userBST.isEmpty())
    {
        cout << "[ NO USER REGISTEED ]" << endl;
        return;
    }
    cout << "All users:" << endl;
    userBST.displayAll();
}
Graph* MiniInstagram::getRelations()
{
    return &userRelations;
}
void User::viewTimeline() {
    if (timeline.isEmpty()) {
        std::cout << "Your timeline is empty." << endl;
        return;
    }

    std::cout << "Your timeline:" << endl;
    Stack tempTimeline = timeline.copy(); // Copy stack to display without modifying it

    while (!tempTimeline.isEmpty()) {
        std::cout << tempTimeline.gettop() << "" << endl;
        tempTimeline.pop();
    }
}


void User::sendFriendRequest(User* toUser) {
    if (toUser) {
        toUser->friendRequests.enqueue(username);
        toUser->notifications.enqueue(username + " Sent you a friend request.");
        cout << "Friend request sent to " << toUser->getUsername() << "." << endl;
    }
}


time_t User:: getCurrentTime1() {
    return time(0); // Get current time as time_t
}


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
    cout << "User " << username << " has been logged out." << endl;
}

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
        cout << "[ No pending friend requests. ]" << endl;
        return;
    }

    cout << "Pending friend requests:" << endl;
    friendRequests.display();

    cout << "Do you want to manage requests? (y/n): ";
    char choice = _getche();
    cout << endl;
    //cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        string request = friendRequests.dequeue();
        cout << "Processing: Request from " << request << "" << endl;
        cout << "Accept (a) or Reject (r)? ";
        char action = _getche();
        //cin >> action;
        cout << endl;

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
                cout << GREEN << "You are now friends with " << request << "." << RESET << endl;
            }
            else {
                cout << request << " Started following you " << "." << endl;
            }
        }
        else {
            G->deleteEdge(request, username);
            cout << "Friend request rejected." << endl;
        }
    }
}

void User::createPost(const std::string& content, Graph* relationshipGraph) {
    // Add post to the user's own posts stack
    std::string post = "Post: " + content + " (" + getCurrentTime() + ")";
    posts.push(post);
    std::cout << "Post created successfully." << endl;

    // Push the post to followers' timelines
    std::vector<std::string> followers = relationshipGraph->getFollowers(username);
    for (const std::string& follower : followers) {
        User* followerUser = platformBST->search(follower);
        if (followerUser) {
            followerUser->timeline.push(username + ": " + post);
        }
    }
}

void User::viewPosts() {
    if (posts.isEmpty()) {
        cout << "[ No posts to show. ]" << endl;
        return;
    }

    cout << "Your posts:" << endl;
    posts.display();
}
void User::viewNotifications() {
    if (notifications.isEmpty()) {
        cout << "[ No notifications. ]" << endl;
        return;
    }

    cout << "Notifications:" << endl;
    notifications.displayAndClear();
}
void User::showProfile() {
    cout << "Profile of " << username << ":" << endl;
    cout << "City: " << city << "" << endl;
    cout << "Email: " << security << "" << endl;
    cout << "Last Login: " << lastLogin;
    cout << "Recent Posts:" << endl;
    viewPosts();
    cout << "Notifications:" << endl;
    viewNotifications();
}




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
        recipient->notifications.enqueue(username + " sent you a message.");
    }
    else {
        showError("[ Recipient user not found. ]");
    }
}
void signup(MiniInstagram& platform) {
    string username, password, city, security;

    cout << "Enter username: ";
    cin >> username;

    while (true) { // Loop until the user enters a valid password
        cout << "Enter password (must be 8+ characters, no spaces, at least one number): ";
        cin >> ws; // Clear any leading whitespace
        getline(cin, password); // Read the entire line, including spaces if any

        bool hasNumber = std::regex_search(password, std::regex("\\d")); // At least one number
        bool hasNoSpaces = !std::regex_search(password, std::regex("\\s")); // No spaces
        bool hasMinLength = password.length() >= 8; // At least 8 characters

        if (hasNumber && hasNoSpaces && hasMinLength) {
            cout << "Password is valid.\n";
            break;
        }
        else {
            cout << "Invalid password!\n";
            if (!hasMinLength)
                cout << "- Password must be at least 8 characters long.\n";
            else if (!hasNoSpaces)
                cout << "- Password must not contain spaces.\n";
            else if (!hasNumber)
                cout << "- Password must include at least one number.\n";
        }
    }

    cout << "Enter city: ";
    cin >> city;
    cout << "Enter your pet name as security answer: ";
    cin >> security;

    User* newUser = nullptr;
    platform.signup(username, password, city, security, newUser);
}

void User::viewMessages(const string& friendUsername) {
    Conversation* conversation = findConversation(friendUsername);
    if (conversation) {
        conversation->displayMessages();
    }
    else {
        cout << "No conversation with " << friendUsername << "." << endl;
    }
}


int main()
{
    MiniInstagram platform;
    User* currentUser = nullptr;

    while (true) {
        int choice;
        cout << "Menu:" << endl;
        cout << "1. Signup" << endl;
        cout << "2. Login" << endl;
        cout << "3. Show All Users" << endl;
        cout << "4. Send Message" << endl;
        cout << "5. View Messages" << endl;
        cout << "6. Send Friend Request" << endl;
        cout << "7. View Friend Requests" << endl;
        cout << "8. Create Post" << endl;
        cout << "9. View Posts" << endl;
        cout << "10. View Notifications" << endl;
        cout << "11. Show Profile" << endl;
        cout << "12. Logout" << endl;
        cout << "13. Exit" << endl;
        cout << "14. Show Relations" << endl;
        cout << "15. Modify Relation" << endl;
        cout << "16. Show Status" << endl;
        cout << "17. view timeline" << endl;
        cout << "18. Show Followers" << endl;
        cout << "19. Get Friend Suggestions" << endl;
        cout << "20. Find Mutuals" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            signup(platform);
          /*  string username, password, city, security;
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
            break;*/
        }
        case 2:
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            currentUser = platform.login(username, password);
            break;
        }
        case 3:
            platform.showUsers();
            break;
        case 4:
            if (currentUser) {
                string friendUsername, message;
                cout << "Enter friend's username: ";
                cin >> friendUsername;
                cout << "Enter your message: ";
                cin >> ws;
                getline(cin, message);
                currentUser->sendMessage(friendUsername, message);
            }
            else {
                cout << "[ No user currently logged in ]" << endl;
            }
            break;
        case 5:
            if (currentUser) {
                string friendUsername;
                cout << "Enter friend's username: ";
                cin >> friendUsername;
                currentUser->viewMessages(friendUsername);
            }
            else {
                cout << "[ No user currently logged in. ]" << endl;
            }
            break;
        case 6:
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
                    cout << "[User not found.]" << endl;
                }
            }
            else {
                cout << "[No user currently logged in.]" << endl;
            }
            break;
        case 7:
            if (currentUser) {
                currentUser->viewFriendRequests(platform.getRelations());
            }
            else {
                cout << "[No user currently logged in.]" << endl;
            }
            break;
        case 8:
            if (currentUser) {
                string postContent;
                cout << "Enter post content: ";
                cin >> ws;
                getline(cin, postContent);
                currentUser->createPost(postContent, platform.getRelations());
            }
            else {
                cout << "[No user currently logged in.]" << endl;
            }
            break;
        case 9:
            if (currentUser) {
                currentUser->viewPosts();
            }
            else {
                cout << "No user currently logged in." << endl;
            }
            break;
        case 10:
            if (currentUser) {
                currentUser->viewNotifications();
            }
            else {
                cout << "No user currently logged in." << endl;
            }
            break;
        case 11:
            if (currentUser) {
                currentUser->showProfile();
            }
            else {
                cout << "No user currently logged in." << endl;
            }

            break;
        case 12:
            if (currentUser) {
                currentUser->logout();  // Call logout function if user is logged in
                currentUser = nullptr;  // Set currentUser to nullptr to indicate no user is logged in
                cout << "Logout successful." << endl;
            }
            else {
                cout << "No user currently logged in." << endl;
            }
            break;
        case 14:
            if (currentUser) {
                std::cout << "Relations:" << endl;
                platform.getRelations()->showRelations(currentUser->getUsername());
            }
            else {
                std::cout << "No user currently logged in." << endl;
            }
            break;
        case 15:
            if (currentUser) {
                std::string friendUsername;
                int newRelationStatus;
                std::cout << "Enter username to modify relation: ";
                std::cin >> friendUsername;

                std::cout << "Choose new relation status:" << endl;
                std::cout << "1. Friend" << endl;
                std::cout << "2. Family" << endl;
                std::cout << "3. Blocked" << endl;
                std::cout << "Choice: ";
                std::cin >> newRelationStatus;

                if (newRelationStatus >= 1 && newRelationStatus <= 3) {
                    RelationStatus newStatus = static_cast<RelationStatus>(newRelationStatus - 1);
                    platform.getRelations()->modifyRelation(currentUser->getUsername(), friendUsername, newStatus);
                }
                else {
                    std::cout << "Invalid choice." << endl;
                }
            }
            else {
                std::cout << "No user currently logged in." << endl;
            }
            break;
        case 16:
        {
            platform.showUsers();
            string user;
            cout << "Enter username to check status: ";
            cin >> user;
            User* targetUser = platform.userBST.search(user);
            if (targetUser) {
                if (currentUser) {
                    cout << "User " << currentUser->getUsername() << " is currently: ";
                    currentUser->getStatus();
                }
                else {
                    cout << "No user currently logged in." << endl;
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
                cout << "User not found." << endl;
            }
            break;
        }
        case 17:
            if (currentUser) {
                currentUser->viewTimeline();
            }
            else {
                cout << "No user currently logged in." << endl;
            }
            break;
        case 18:
        {
            string user;
            cout << "All users " << endl;
            platform.userBST.displayAll();
            cout << "Enter username to check followers list : ";
            cin >> ws;
            getline(cin, user);
            cout << "Followers : " << endl;
            vector<string> flowers = platform.userRelations.getFollowersList(user);
            for (const std::string& follower : flowers) {
                cout << follower << endl;
            }
            break;
        }
        case 19:
        {
            string user;
            cout << "All users " << endl;
            platform.userBST.displayAll();
            cout << "Enter username to get friend suggestions : ";
            cin >> ws;
            getline(cin, user);
            platform.userRelations.friendSuggestions(user);
            break;
        }
        case 20: {
                string user1, user2;
                cout << "All users " << endl;
                platform.userBST.displayAll();
                cout << "Enter first username: ";
                cin >> ws;
                getline(cin, user1);
                cout << "Enter second username: ";
                cin >> ws;
                getline(cin, user2);
                cout << "Followers : " << endl;
                platform.userRelations.mutualFriends(user1, user2);
                break;
            }
        }
        system("cls");
    }

    return 0;

}