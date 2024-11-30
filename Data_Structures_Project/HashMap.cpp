#include "HashMap.h"
#include <iostream>

using namespace std;

// HashNode constructor
HashNode::HashNode(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {}

// HashMap constructor
HashMap::HashMap() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = nullptr;
    }
}

// Hash function
int HashMap::hashFunction(const std::string& key) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash + ch) % HASH_TABLE_SIZE;
    }
    return hash;
}

// Insert function
void HashMap::insert(const std::string& key, const std::string& value) {
    int index = hashFunction(key);
    HashNode* newHashNode = new HashNode(key, value);

    // Insert at the beginning of the linked list at index
    if (hashTable[index] == nullptr) {
        hashTable[index] = newHashNode;
    }
    else {
        HashNode* temp = hashTable[index];
        while (temp->next != nullptr && temp->key != key) {
            temp = temp->next;
        }

        if (temp->key == key) {
            // If key already exists, update the value
            temp->value = value;
            delete newHashNode; // Free memory since we didn't use the new HashNode
        }
        else {
            temp->next = newHashNode;
        }
    }
}

// Search function
std::string HashMap::search(const std::string& key) {
    int index = hashFunction(key);
    HashNode* temp = hashTable[index];

    // Traverse the linked list at the computed index
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }

    return "[Not Found]"; // If key is not found
}

// Remove function
void HashMap::remove(const std::string& key) {
    int index = hashFunction(key);
    HashNode* temp = hashTable[index];
    HashNode* prev = nullptr;

    while (temp != nullptr && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Key not found\n";
        return;
    }

    // Remove the HashNode
    if (prev == nullptr) {
        // HashNode to delete is the head of the list
        hashTable[index] = temp->next;
    }
    else {
        prev->next = temp->next;
    }

    delete temp; // Free memory
    cout << "Key removed\n";
}

// Display function
void HashMap::display() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        cout << "Index " << i << ": ";
        HashNode* temp = hashTable[i];
        while (temp != nullptr) {
            cout << "(" << temp->key << ", " << temp->value << ") -> ";
            temp = temp->next;
        }
        cout << "nullptr\n";
    }
}

// Destructor
HashMap::~HashMap() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode* temp = hashTable[i];
        while (temp != nullptr) {
            HashNode* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
}
