# Mini Instagram (C++ Data Structures Project)

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Visual Studio](https://img.shields.io/badge/IDE-Visual%20Studio-5C2D91?style=for-the-badge&logo=visual-studio&logoColor=white)](https://visualstudio.microsoft.com/)
[![Console App](https://img.shields.io/badge/Interface-Console-222222?style=for-the-badge&logo=windows-terminal&logoColor=white)]()
[![Data Structures](https://img.shields.io/badge/Data%20Structures-Graph%2C%20BST%2C%20Hashmap%2C%20Stack%2C%20Queue-6E40C9?style=for-the-badge&logo=codefactor&logoColor=white)]()
[![Regex Security](https://img.shields.io/badge/Security-Regex-00BFAE?style=for-the-badge&logo=HackTheBox&logoColor=white)]()
[![License: Educational](https://img.shields.io/badge/License-Educational-FFB300?style=for-the-badge)]()

---

## Overview

**Mini Instagram** is a console-based social media simulator built in modern C++. It mimics core features of popular social platforms while demonstrating efficient, hands-on use of advanced data structures. This project is designed to be educational, showing how graphs, trees, hashmaps, stacks, and queues can be combined to model real-world social interactions, content feeds, messaging, and notifications.

---

## Key Features

### User Management
- **Secure Signup/Login:** Regex-based password validation (8+ chars, no spaces)
- **Profile Customization:** City, security question & answer
- **Activity Status Tracking:** Online/offline duration

### Social Interactions
- **Graph-Based Friend System:** Follow/unfollow, mutual connections
- **Relationship Tagging:** Friends, Family, Blocked
- **Friend Suggestion Algorithm**

### Content System
- **BST-Organized Posts:** Efficient timestamp-based post storage and lookup
- **Timeline View:** Most recent posts first (via Stack)
- **Hashtag Support**

### Messaging & Notifications
- **Hashmap-Based Messaging:** O(1) message retrieval
- **Notification Queue:** For new messages and friend requests

---

## Technical Implementation

### Data Structures Used

| Data Structure | Application                           | Big-O Complexity      |
|----------------|--------------------------------------|----------------------|
| Graph          | User connections (followers/following)| O(V+E) traversal     |
| BST            | User profiles & post indexing         | O(log n) search      |
| Hashmap        | Message storage                       | O(1) access          |
| Stack          | Timeline post ordering                | O(1) push/pop        |
| Queue          | Notification management               | O(1) enqueue         |

### Libraries Used

- **Core:** `<iostream>`, `<string>`, `<ctime>`
- **Security:** `<regex>` for password validation
- **Custom:** `Graph.h`, `HashMap.h`, `Helper.h`
- **UI:** Color-coded console output for error/success/info

---

## Getting Started

### Prerequisites

- [Visual Studio 2019 or later](https://visualstudio.microsoft.com/)
- Desktop development with C++ workload installed

### Steps

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Waqas-Chohan/Data_Structures_Project.git
   ```

2. **Open the Project in Visual Studio:**
   - Launch Visual Studio.
   - Go to `File` > `Open` > `Project/Solution...`
   - Navigate to the cloned repository and open the `.sln` (solution) file.

3. **Build the Project:**
   - Select the desired configuration (`Debug` or `Release`) and platform (`x86` or `x64`).
   - Click **Build Solution** (`Ctrl+Shift+B`).

4. **Run the Application:**
   - Press `F5` to run with debugging or `Ctrl+F5` to run without debugging.
   - Interact with the console-based Mini Instagram features.

---

## Educational Value

This project is intended for students and developers seeking to deepen their understanding of C++ and practical data structures through a real-world scenario.

---

## License

For educational use only.

---
