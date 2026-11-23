# ATM Simulation Project (1st Semester C Programming)

**Location:** `C:\Users\Anurag Tewary\Documents\C_Assignments\ATM\atm_simulation.c`

---

## 1. Project Overview
This is a console-based ATM (Automated Teller Machine) simulation written in C. It is designed to be beginner-friendly while implementing all standard banking operations.

### Default Credentials
- **Initial PIN:** `1234`
- **Initial Balance:** `$10,000.00`
- **Max PIN Retries:** `3 attempts`

---

## 2. Implemented Functions & Features

| # | Functionality | Implemented C Function | Description |
|---|---------------|------------------------|-------------|
| 1 | **PIN Authentication** | `verifyPin()` | Asks for 4-digit PIN with a 3-attempt lock-out mechanism. |
| 2 | **Check Balance** | `checkBalance()` | Displays current available account balance. |
| 3 | **Deposit Cash** | `depositMoney()` | Adds positive amounts to balance and records transaction. |
| 4 | **Withdraw Cash** | `withdrawMoney()` | Validates sufficient funds and enforces multiples of 100. |
| 5 | **Fast Cash** | `fastCash()` | Instant one-touch withdrawals ($500, $1000, $2000, $5000). |
| 6 | **Fund Transfer** | `transferMoney()` | Transfers funds to a destination account number. |
| 7 | **Mini Statement** | `showMiniStatement()` | Shows the last 5 transactions (credits/debits) using an array. |
| 8 | **Change PIN** | `changePin()` | Verifies old PIN before setting and confirming a new PIN. |
| 9 | **Input Protection** | `while (getchar() != '\n');` | Clears input buffer if invalid characters are typed. |

---

## 3. C Programming Concepts Used (1st Semester Syllabus)

1. **Functions & Prototypes:** Modular code divided into single-purpose functions.
2. **Loops:** `do-while` for the continuous main menu; `for` and `while` loops for input checks and transaction shifts.
3. **Decision Making:** `switch-case` for menu navigation; `if-else` for validation checks (balance limits, multiples of 100).
4. **Arrays:** `float history[5]` stores the last 5 transactions.
5. **Basic Pointers:** `int *historyCount` allows updating the count directly inside helper functions.
6. **Input Buffer Handling:** Prevents infinite loops when non-numeric input is entered.

---

## 4. How to Compile and Run

### Using Command Line (GCC)
```powershell
cd "C:\Users\Anurag Tewary\Documents\C_Assignments\ATM"
gcc atm_simulation.c -o atm_simulation.exe
.\atm_simulation.exe
```

### In VS Code
1. Open the folder `C:\Users\Anurag Tewary\Documents\C_Assignments\ATM`.
2. Open `atm_simulation.c`.
3. Press `Ctrl + Shift + B` or click the Run/Play icon.
