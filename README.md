# C-Based Library Management System

This project is a comprehensive management system developed in C to meet the basic operational needs of a library. It was developed during the first semester of the first year to master basic C programming concepts and file systems.

##  Features
- **Book Management:** Functions to add, delete, search by ID, and list all books.
- **Member Management:** Registration and tracking of members with 11-digit TC identification number validation.
- **Lending Operations:** Book borrowing and return processes with automatic status (Available/On Loan) updates.
- **Reporting:** Categorized lists for available and currently borrowed books.
- **Data Persistence:** All records are stored in `txt` files, ensuring data is preserved even after application exit.

##  Technical Highlights
- **Dynamic Memory Management:** Runtime memory allocation for data using `malloc` and `free`.
- **File I/O Operations:** Implemented using `fopen`, `fprintf`, and `fscanf`, utilizing temporary file logic for secure data updates.
- **Data Structures:** Modeled complex library entities and processes using `struct` types.
- **Input Validation:** Integrated checks for TC identification number length and specific date formats (YYYY-MM-DD).

##  Installation
1. Ensure a C compiler (e.g., GCC) is installed.
2. Compile the source code:
   ```bash
   gcc main.c -o library_system
