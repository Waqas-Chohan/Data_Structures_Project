#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>

// HashNode structure for the linked list
struct HashNode {
    std::string key;
    std::string value;
    HashNode* next;

    // Constructor to initialize a HashNode
    HashNode(const std::string& k, const std::string& v);
};

// HashMap class declaration
class HashMap {
private:
    static const int HASH_TABLE_SIZE = 10; // Size of the hash table
    HashNode* hashTable[HASH_TABLE_SIZE];     // Array of linked list heads

    // Hash function to compute the index for a given key
    int hashFunction(const std::string& key);

public:
    // Constructor
    HashMap();

    // Insert a key-value pair
    void insert(const std::string& key, const std::string& value);

    // Search for a key
    std::string search(const std::string& key);

    // Remove a key-value pair
    void remove(const std::string& key);

    // Display the contents of the hash map
    void display();

    // Destructor
    ~HashMap();
};

#endif // HASHMAP_H
