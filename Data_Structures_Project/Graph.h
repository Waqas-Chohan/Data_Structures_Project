#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>

// Enum for relation type and status
enum RelationStatus {
    FRIEND,      // Relation type
    FAMILY,      // Relation type
    BLOCKED,     // Status
    ACTIVE,      // Status
    PENDING,     // Status
    FOLLOWING,
    FOLLOWERS
};



// Define edge relationship structure
struct Edge {
    std::string targetUsername;
    RelationStatus relationStatus; // FRIEND or FAMILY
    Edge* next;

    Edge(const std::string& target, RelationStatus type)
        : targetUsername(target), relationStatus(type), next(nullptr) {}
};

// Define vertex structure
struct Vertex {
    std::string username;
    Edge* adjacencyList; // Linked list of edges
    Vertex* next;

    Vertex(const std::string& name) : username(name), adjacencyList(nullptr), next(nullptr) {}
};

// Define Graph class
class Graph {
private:
    Vertex* head; // Head of the vertex linked list

public:
    Graph();
    ~Graph();

    void addVertex(const std::string& username);
    void addEdge(const std::string& from, const std::string& to, RelationStatus relationStatus);
    void displayGraph() const;
    void deleteVertex(const std::string& username);
    void deleteEdge(const std::string& from, const std::string& to);
    void friendSuggestions(const std::string& username) const;
    void mutualFriends(const std::string& user1, const std::string& user2) const;
    void modifyRelation(const std::string& from, const std::string& to, RelationStatus newStatus);
    void showRelations(const std::string& username)const;
    bool hasEdge(const std::string& from, const std::string& to, RelationStatus relationStatus) const;

private:
    Vertex* findVertex(const std::string& username) const;
    void deleteEdges(Edge* edge);
    std::string relationStatusToString(RelationStatus rs) const;
};

#endif // GRAPH_H
