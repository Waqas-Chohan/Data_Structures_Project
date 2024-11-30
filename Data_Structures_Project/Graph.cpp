#include "Graph.h"

// Constructor
Graph::Graph() : head(nullptr) {}

// Destructor
Graph::~Graph() {
    Vertex* current = head;
    while (current) {
        Vertex* temp = current;
        current = current->next;
        deleteEdges(temp->adjacencyList);
        delete temp;
    }
}

// Add a vertex
void Graph::addVertex(const std::string& username) {
    if (findVertex(username)) {
        std::cout << "Vertex with username " << username << " already exists.\n";
        return;
    }

    Vertex* newVertex = new Vertex(username);
    newVertex->next = head;
    head = newVertex;
}

// Add an edge
void Graph::addEdge(const std::string& from, const std::string& to,
    RelationStatus relationStatus) {
    Vertex* fromVertex = findVertex(from);
    Vertex* toVertex = findVertex(to);

    if (!fromVertex || !toVertex) {
        std::cout << "One or both vertices not found.\n";
        return;
    }

    // Check if the edge already exists
    Edge* current = fromVertex->adjacencyList;
    while (current) {
        if (current->targetUsername == to) {
            std::cout << "Edge from " << from << " to " << to << " already exists.\n";
            return;
        }
        current = current->next;
    }

    // Add the edge
    Edge* newEdge = new Edge(to, relationStatus);
    newEdge->next = fromVertex->adjacencyList;
    fromVertex->adjacencyList = newEdge;
}

// Display the graph
void Graph::displayGraph() const {
    Vertex* current = head;
    while (current) {
        std::cout << "Vertex: " << current->username << "\nEdges:\n";
        Edge* edge = current->adjacencyList;
        while (edge) {
            std::cout << "  -> " << edge->targetUsername
                << " [Relation: " << relationStatusToString(edge->relationStatus) << "]\n";
            edge = edge->next;
        }
        current = current->next;
        std::cout << "\n";
    }
}

// Friend Suggestions
void Graph::friendSuggestions(const std::string& username) const {
    Vertex* userVertex = findVertex(username);
    if (!userVertex) {
        std::cout << "User " << username << " not found.\n";
        return;
    }

    // Array-based visited map (naive implementation)
    const int MAX_USERS = 100; // Assume max 100 users for simplicity
    std::string visited[MAX_USERS];
    int visitedCount = 0;

    // Mark direct friends as visited
    Edge* edge = userVertex->adjacencyList;
    while (edge) {
        visited[visitedCount++] = edge->targetUsername;
        edge = edge->next;
    }

    // Find friends of friends
    std::cout << "Friend suggestions for " << username << ":\n";
    edge = userVertex->adjacencyList;
    while (edge) {
        Vertex* friendVertex = findVertex(edge->targetUsername);
        if (friendVertex) {
            Edge* friendEdge = friendVertex->adjacencyList;
            while (friendEdge) {
                // If not a direct friend and not already suggested
                bool isVisited = false;
                for (int i = 0; i < visitedCount; i++) {
                    if (visited[i] == friendEdge->targetUsername || friendEdge->targetUsername == username) {
                        isVisited = true;
                        break;
                    }
                }
                if (!isVisited) {
                    visited[visitedCount++] = friendEdge->targetUsername;
                    std::cout << "  -> " << friendEdge->targetUsername << "\n";
                }
                friendEdge = friendEdge->next;
            }
        }
        edge = edge->next;
    }
}

// Mutual Friends
void Graph::mutualFriends(const std::string& user1, const std::string& user2) const {
    Vertex* user1Vertex = findVertex(user1);
    Vertex* user2Vertex = findVertex(user2);

    if (!user1Vertex || !user2Vertex) {
        std::cout << "One or both users not found.\n";
        return;
    }

    std::cout << "Mutual friends between " << user1 << " and " << user2 << ":\n";

    // Compare adjacency lists for mutual friends
    Edge* edge1 = user1Vertex->adjacencyList;
    while (edge1) {
        Edge* edge2 = user2Vertex->adjacencyList;
        while (edge2) {
            if (edge1->targetUsername == edge2->targetUsername) {
                std::cout << "  -> " << edge1->targetUsername << "\n";
            }
            edge2 = edge2->next;
        }
        edge1 = edge1->next;
    }
}

// Delete a vertex
void Graph::deleteVertex(const std::string& username) {
    Vertex* current = head;
    Vertex* prev = nullptr;

    while (current) {
        if (current->username == username) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                head = current->next;
            }

            // Delete edges of this vertex
            deleteEdges(current->adjacencyList);
            delete current;
            std::cout << "Vertex " << username << " deleted.\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    std::cout << "Vertex " << username << " not found.\n";
}

// Delete an edge
void Graph::deleteEdge(const std::string& from, const std::string& to) {
    Vertex* fromVertex = findVertex(from);
    if (!fromVertex) {
        std::cout << "Vertex " << from << " not found.\n";
        return;
    }

    Edge* current = fromVertex->adjacencyList;
    Edge* prev = nullptr;

    while (current) {
        if (current->targetUsername == to) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                fromVertex->adjacencyList = current->next;
            }
            delete current;
            std::cout << "Edge from " << from << " to " << to << " deleted.\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    std::cout << "Edge from " << from << " to " << to << " not found.\n";
}

// Helper to find a vertex
Vertex* Graph::findVertex(const std::string& username) const {
    Vertex* current = head;
    while (current) {
        if (current->username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Helper to delete all edges
void Graph::deleteEdges(Edge* edge) {
    while (edge) {
        Edge* temp = edge;
        edge = edge->next;
        delete temp;
    }
}

// Helper to convert RelationStatus enum to string
std::string Graph::relationStatusToString(RelationStatus rs) const {
    switch (rs) {
    case FRIEND: return "Friend";
    case FAMILY: return "Family";
    case BLOCKED: return "Blocked";
    case ACTIVE: return "Active";
    case PENDING: return "Pending";
    default: return "Unknown";
    }
}
