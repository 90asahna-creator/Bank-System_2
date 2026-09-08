# 🏦 Bank System 2

A C++ console-based banking management system for managing client accounts and performing basic banking transactions using file-based data storage.

This project is an extension of the previous Bank System, introducing a dedicated **Transactions Module** while maintaining the existing client management features.

---

## ✨ Features

### 👥 Client Management

- 📋 Show all clients
- ➕ Add new clients
- 🗑️ Delete clients
- ✏️ Update client information
- 🔎 Find clients by account number
- Prevent duplicate account numbers

### 💰 Transactions

- 💵 Deposit money
- 💸 Withdraw money
- 📊 Calculate total balances
- Update and save account balances

---

## 🛠️ Technical Highlights

- **Language:** C++
- **Data Storage:** Text file (`Clients.text`)
- **Data Structure:** `struct` and `std::vector`
- **File Handling:** Reading and writing client records
- **Programming Concepts:**
  - Functions
  - Structs
  - Enums
  - Vectors
  - Loops
  - Conditional Statements
  - File Handling
  - Basic Validation
  - CRUD Operations

> `Clients.text` is created automatically when client data is first saved.

---

## 📁 Project Structure

    Bank-System_2/
    │
    ├── Bank System Project 2.cpp
    ├── README.md
    ├── LICENSE
    └── .gitignore

---

## 🚀 How to Run

### 1. Clone the Repository

    git clone https://github.com/90asahna-creator/Bank-System_2.git

### 2. Navigate to the Project Directory

    cd Bank-System_2

### 3. Compile

    g++ -o BankSystem "Bank System Project 2.cpp"

### 4. Run

**Windows:**

    BankSystem.exe

**Linux/macOS:**

    ./BankSystem

---

## 🎯 Learning Objectives

Through this project, I practiced:

- Building menu-driven console applications.
- Using `struct`, `enum`, and `std::vector`.
- Working with file input/output.
- Implementing CRUD operations.
- Managing and updating persistent data.
- Applying basic banking transaction logic.
- Organizing a larger C++ program using functions.

---

## 🔄 Project Evolution

**Previous Bank System:**

- Client Management
- Add / Delete / Update / Find
- File-based storage

**Bank System 2:**

- Added Deposit
- Added Withdraw
- Added Total Balances
- Added a dedicated Transactions Menu
- Added balance updates and persistence

---

## 🔮 Future Improvements

- Improve input validation and error handling.
- Improve code organization.
- Separate the project into `.h` and `.cpp` files.
- Introduce Object-Oriented Programming.
- Improve security and credential handling.
- Move from text-file storage to a database in a future project.

---

## 👨‍💻 Author

**Anas Ahmed**

This project is part of my ongoing journey to improve my C++ programming skills through practical projects.

---

## 📄 License

This project is licensed under the MIT License.
```
