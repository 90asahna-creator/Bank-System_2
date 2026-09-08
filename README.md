# Bank-System_2 🏦

An extended C++ console application designed for bank client management and account transactions. This project builds upon foundational CRUD operations by introducing a dedicated **Transactions Management Module**, enabling real-time deposit/withdrawal operations and automatic data persistence using flat-file storage.

---

## 🌟 Key Features

### 📋 Main Management Menu
* **Show Client List:** Tabular view displaying all client records (Account Number, Pin Code, Name, Phone, and Balance).
* **Add New Client:** Add unique account numbers with automated duplicate validation.
* **Delete Client:** Mark and remove specific client records safely from flat-file storage.
* **Update Client Info:** Edit personal details and PIN codes while preserving system consistency.
* **Find Client:** Instant lookup by account number with formatted output.

### 💳 Transactions Sub-Menu
* **Deposit Money:** Increase account balance with instant record saving.
* **Withdraw Money:** Process withdrawals with dynamic balance restriction checks (prevents overdrawing).
* **Total Balances:** View aggregated balances for all accounts along with total system liquidity.

---

## 🛠️ Technical Highlights

* **Language:** C++
* **Data Storage:** Flat-file system (`Clients.text`) using `#//#` record delimiters.
* **Data Structures:** Dynamic collections via `std::vector` and custom `struct` representations (`stClient`).
* **Input Validation:** Stream manipulation, input sanitation, and account existence verifications.
* **UI/UX Formats:** `std::setw` formatting for clean alignment in console outputs.

---

📁 File Structure

```text
├── Bank System Project 2.cpp  # Main C++ Source Code
├── Clients.text               # Flat-file database for storing client data
└── README.md                  # Project documentation
---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone [https://github.com/90asahna-creator/Bank-System_2.git](https://github.com/90asahna-creator/Bank-System_2.git)
g++ -o BankSystem "Bank System Project 2.cpp"
./BankSystem
