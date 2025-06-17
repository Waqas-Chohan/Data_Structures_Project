Mini-Instagram (C++ Data Structures Project)

A console-based social media simulator implementing core platform features with optimized data structures

Key Features
User Management

    Secure signup/login with regex password validation (8+ chars, no spaces)

    Profile customization (city, security Q/A)

    Activity status tracking (online/offline duration)

Social Interactions

    Graph-based friend system (follow/unfollow, mutual connections)

    Relationship tagging (Friends, Family, Blocked)

    Friend suggestion algorithm

Content System

    BST-organized posts with timestamps

    Timeline view (most recent first using Stack)

    Hashtag support

Messaging

    Hashmap-based message storage (O(1) retrieval)

    Notification queue for new messages/requests

Technical Implementation
Data Structures
Structure	Application	Big-O
Graph	User connections (followers/following)	O(V+E) traversal
BST	User profiles & post indexing	O(log n) search
Hashmap	Message storage	O(1) access
Stack	Timeline post ordering	O(1) push/pop
Queue	Notification management	O(1) enqueue
Libraries Used

    Core: <iostream>, <string>, <ctime>

    Security: <regex> for password validation

    Custom: Graph.h, HashMap.h, Helper.h

    UI: Color-coded console output (error/success/info)
