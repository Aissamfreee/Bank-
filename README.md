# Bank Management System (C++)

## Project Description

A **console-based Bank Management System** built using **C++**.
This application simulates a simple banking system where administrators can manage clients, handle transactions, and control user access using a permission-based system.

The system uses **text files as a database** to store client and user information.

---

## Key Features

### Client Management

* Display all clients
* Add new client accounts
* Delete existing clients
* Update client information
* Search for a client using the account number

### Transaction System

* Deposit money into client accounts
* Withdraw money from client accounts
* Display total balances of all clients

### User Management

* Create system users
* Update user information
* Delete users
* Search for users
* Display all users

### Authentication & Security

* Login system using **username and password**
* **Permission-based access control**
* Admin users can assign permissions to other users

---

## Permission System

The system implements a **bitwise permission system** to control user access.

Each permission is represented by a specific value:

| Permission    | Value |
| ------------- | ----- |
| Show Clients  | 1     |
| Add Client    | 2     |
| Delete Client | 4     |
| Update Client | 8     |
| Find Client   | 16    |
| Transactions  | 32    |
| Manage Users  | 64    |

Users can have:

* **Full access**
* **Specific permissions**

---

## Technologies Used

* C++
* File Handling (`fstream`)
* Structs
* Vectors
* Enumerations
* Bitwise operations
* Console-based UI

---

## Project Structure

```
Bank-Management-System
│
├── main.cpp
├── Clients.txt
├── Users.txt
└── README.md
```

---

## Example Operations

The system allows administrators to perform operations such as:

* Creating client accounts
* Depositing and withdrawing money
* Managing system users
* Controlling access using permissions

---

## Learning Goals

This project was developed to practice:

* File-based data storage
* Menu-driven console applications
* Struct-based data modeling
* User authentication systems
* Permission management

---

## Future Improvements

Possible enhancements for the system:

* Implementing a **Graphical User Interface**
* Using a **database instead of text files**
* Encrypting passwords
* Splitting the code into multiple modules

---

## Author

**Aissam**
Computer Science Student | Learning C++ and Software Development
