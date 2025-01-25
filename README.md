# GitLite - Simplified Version Control System

GitLite is a lightweight, educational version control system that mimics the core functionalities of Git while demonstrating advanced data structure and algorithm implementation techniques. This project was developed as part of a 3rd-semester Data Structures course to showcase mastery over concepts such as AVL Trees, Red-Black Trees, and custom-built libraries, all while avoiding the use of dynamic memory or built-in libraries. The entire project operates file-based, ensuring persistence and efficient management of data on the hard disk.

---

## Features

### Version Control Functionalities
- **Repository Management**: Create and initialize repositories.
- **Branching**: Manage branches for version isolation.
- **Update and Delete**: Handle file updates and deletions within repositories.
- **Commit Tracking**: Maintain a log of commits and changes.

### Data Structures
- **AVL Trees**: Efficient handling of ordered data for fast retrieval.
- **Red-Black Trees**: Balanced tree structure for enhanced performance.

### Unique Aspects
- **File-Based System**: All data operations are handled using files on the hard disk, eliminating the need for dynamic memory.
- **Custom Libraries**: No reliance on standard libraries, including the string library. All functionality is implemented from scratch.
- **CSV File Handling**: Efficient parsing and management of large CSV files.

---

## Technical Highlights
- **No Dynamic Memory Usage**: All data management is handled through file I/O operations, demonstrating a deep understanding of low-level data handling.
- **Custom String Library**: Built from scratch, showcasing the ability to create fundamental utilities without external dependencies.
- **Persistent Data**: Leveraging file-based storage ensures data integrity and long-term persistence.
- **Scalable Architecture**: Supports efficient handling of large datasets with custom-built data structures.

---

## How to Use

### Setting Up
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/GitLite-Simplified-Version-Control-System.git
   ```
2. Compile the code:
   ```bash
   g++ -o GitLite main.cpp
   ```
3. Run the program:
   ```bash
   ./GitLite
   ```

### Commands
- **init**: Initialize a new repository.
- **create <branch-name>**: Create a new branch.
- **update <file-name>**: Update a file in the repository.
- **delete <file-name>**: Delete a file from the repository.
- **commit**: Save the current state of the repository.
- **log**: View the commit history.

---

## Why GitLite?
GitLite is an excellent learning resource for those looking to:
1. Understand the implementation of advanced data structures like AVL and Red-Black Trees.
2. Explore file-based system design without relying on dynamic memory.
3. Develop foundational programming skills by avoiding built-in libraries.
4. Gain hands-on experience with version control concepts.

---

## Future Improvements
- Adding support for merging branches.
- Enhancing the file parsing capabilities for more complex data formats.
- Optimizing tree operations for even larger datasets.

---

## Acknowledgments
Special thanks to my instructors and peers for their guidance and feedback throughout this project.

---

GitLite is more than a project—it's a showcase of the potential to build something powerful and educational using fundamental programming principles. Explore, contribute, and learn!

