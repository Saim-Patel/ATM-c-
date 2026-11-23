/*
 * Project: ATM Simulation System
 * Level: First Semester C Programming
 * Path: C:\Users\Anurag Tewary\Documents\C_Assignments\ATM\atm_simulation.c
 *
 * Included Functional Modules:
 * 1. PIN Authentication (with max 3 attempts)
 * 2. Check Account Balance
 * 3. Cash Deposit
 * 4. Cash Withdrawal (with multiple-of-100 and balance check)
 * 5. Fast Cash (Pre-set withdrawal options)
 * 6. Fund Transfer (Simulated destination account transfer)
 * 7. Mini Statement (Last 5 transactions log)
 * 8. Change PIN
 * 9. Session Termination / Exit
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_TRANSACTIONS 5

/* Function prototypes */
int verifyPin(int correctPin);
void displayMenu(void);
void checkBalance(float balance);
float depositMoney(float balance, float history[], int *historyCount);
float withdrawMoney(float balance, float history[], int *historyCount);
float fastCash(float balance, float history[], int *historyCount);
float transferMoney(float balance, float history[], int *historyCount);
void showMiniStatement(float history[], int historyCount);
int changePin(int currentPin);
void recordTransaction(float amount, float history[], int *historyCount);

int main(void) {
    int pin = 1234;                  /* Default initial PIN */
    float balance = 10000.0f;        /* Default starting balance */
    float transactionHistory[MAX_TRANSACTIONS];
    int historyCount = 0;
    int choice;
    int authenticated = 0;

    printf("==========================================\n");
    printf("        WELCOME TO ATM SIMULATION         \n");
    printf("==========================================\n");

    /* Step 1: User Authentication */
    authenticated = verifyPin(pin);
    if (!authenticated) {
        printf("\nCard blocked due to 3 consecutive failed attempts.\n");
        printf("Please contact your branch administrator.\n");
        return 0;
    }

    /* Step 2: Main Processing Loop */
    do {
        displayMenu();
        printf("Enter your choice (1-8): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Clearing buffer...\n");
            while (getchar() != '\n'); /* Flush input stream */
            continue;
        }

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;

            case 2:
                balance = depositMoney(balance, transactionHistory, &historyCount);
                break;

            case 3:
                balance = withdrawMoney(balance, transactionHistory, &historyCount);
                break;

            case 4:
                balance = fastCash(balance, transactionHistory, &historyCount);
                break;

            case 5:
                balance = transferMoney(balance, transactionHistory, &historyCount);
                break;

            case 6:
                showMiniStatement(transactionHistory, historyCount);
                break;

            case 7:
                pin = changePin(pin);
                break;

            case 8:
                printf("\n==========================================\n");
                printf("Thank you for using the ATM. Goodbye!\n");
                printf("==========================================\n");
                break;

            default:
                printf("\n[ERROR] Invalid choice. Please select an option from 1 to 8.\n");
                break;
        }

    } while (choice != 8);

    return 0;
}

/*
 * Verifies user PIN with a limit of 3 attempts.
 * Returns 1 on success, 0 on exhaustion.
 */
int verifyPin(int correctPin) {
    int enteredPin;
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts) {
        printf("Enter your 4-digit PIN: ");
        if (scanf("%d", &enteredPin) != 1) {
            while (getchar() != '\n');
            printf("Invalid format. Numerical PIN only.\n");
            attempts++;
            continue;
        }

        if (enteredPin == correctPin) {
            printf("Authentication successful.\n");
            return 1;
        } else {
            attempts++;
            printf("Incorrect PIN. Attempts remaining: %d\n", maxAttempts - attempts);
        }
    }
    return 0;
}

/*
 * Displays primary user interface menu.
 */
void displayMenu(void) {
    printf("\n------------------------------------------\n");
    printf("             ATM MAIN MENU                \n");
    printf("------------------------------------------\n");
    printf("1. Check Balance\n");
    printf("2. Deposit Cash\n");
    printf("3. Withdraw Cash\n");
    printf("4. Fast Cash\n");
    printf("5. Transfer Money\n");
    printf("6. Mini Statement\n");
    printf("7. Change PIN\n");
    printf("8. Exit\n");
    printf("------------------------------------------\n");
}

/*
 * Displays current account balance.
 */
void checkBalance(float balance) {
    printf("\n--- Account Balance ---\n");
    printf("Current Available Balance: $%.2f\n", balance);
}

/*
 * Deposits valid monetary quantity into balance.
 */
float depositMoney(float balance, float history[], int *historyCount) {
    float depositAmount;

    printf("\n--- Deposit Cash ---\n");
    printf("Enter deposit amount: $");
    if (scanf("%f", &depositAmount) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid numeric input.\n");
        return balance;
    }

    if (depositAmount <= 0.0f) {
        printf("[ERROR] Deposit amount must be greater than zero.\n");
        return balance;
    }

    balance += depositAmount;
    recordTransaction(depositAmount, history, historyCount);
    printf("Successfully deposited $%.2f.\n", depositAmount);
    printf("Updated Balance: $%.2f\n", balance);

    return balance;
}

/*
 * Withdraws funds with validity and balance checks.
 */
float withdrawMoney(float balance, float history[], int *historyCount) {
    float withdrawAmount;

    printf("\n--- Withdraw Cash ---\n");
    printf("Enter amount to withdraw (multiples of 100): $");
    if (scanf("%f", &withdrawAmount) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid numeric input.\n");
        return balance;
    }

    if (withdrawAmount <= 0.0f) {
        printf("[ERROR] Withdrawal amount must be greater than zero.\n");
        return balance;
    }

    if ((int)withdrawAmount % 100 != 0) {
        printf("[ERROR] Please enter an amount in multiples of 100 (e.g., 100, 500, 1000).\n");
        return balance;
    }

    if (withdrawAmount > balance) {
        printf("[ERROR] Insufficient funds. Available balance: $%.2f\n", balance);
        return balance;
    }

    balance -= withdrawAmount;
    recordTransaction(-withdrawAmount, history, historyCount);
    printf("Please collect your cash: $%.2f\n", withdrawAmount);
    printf("Remaining Balance: $%.2f\n", balance);

    return balance;
}

/*
 * Pre-set standard withdrawal options.
 */
float fastCash(float balance, float history[], int *historyCount) {
    int option;
    float selectedAmount = 0.0f;

    printf("\n--- Fast Cash ---\n");
    printf("1. $500\n");
    printf("2. $1000\n");
    printf("3. $2000\n");
    printf("4. $5000\n");
    printf("5. Cancel\n");
    printf("Select Fast Cash Option (1-5): ");

    if (scanf("%d", &option) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid option.\n");
        return balance;
    }

    switch (option) {
        case 1: selectedAmount = 500.0f; break;
        case 2: selectedAmount = 1000.0f; break;
        case 3: selectedAmount = 2000.0f; break;
        case 4: selectedAmount = 5000.0f; break;
        case 5:
            printf("Fast Cash cancelled.\n");
            return balance;
        default:
            printf("[ERROR] Invalid option selected.\n");
            return balance;
    }

    if (selectedAmount > balance) {
        printf("[ERROR] Insufficient funds for Fast Cash of $%.2f.\n", selectedAmount);
        return balance;
    }

    balance -= selectedAmount;
    recordTransaction(-selectedAmount, history, historyCount);
    printf("Dispensed $%.2f successfully.\n", selectedAmount);
    printf("Remaining Balance: $%.2f\n", balance);

    return balance;
}

/*
 * Simulates third-party fund transfer.
 */
float transferMoney(float balance, float history[], int *historyCount) {
    int targetAccount;
    float transferAmount;

    printf("\n--- Transfer Money ---\n");
    printf("Enter destination account number (e.g., 5-digit number): ");
    if (scanf("%d", &targetAccount) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid account number format.\n");
        return balance;
    }

    printf("Enter transfer amount: $");
    if (scanf("%f", &transferAmount) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid numeric input.\n");
        return balance;
    }

    if (transferAmount <= 0.0f) {
        printf("[ERROR] Transfer amount must be positive.\n");
        return balance;
    }

    if (transferAmount > balance) {
        printf("[ERROR] Transfer declined: Insufficient funds. Balance: $%.2f\n", balance);
        return balance;
    }

    balance -= transferAmount;
    recordTransaction(-transferAmount, history, historyCount);
    printf("Successfully transferred $%.2f to Account %d.\n", transferAmount, targetAccount);
    printf("Remaining Balance: $%.2f\n", balance);

    return balance;
}

/*
 * Stores transaction in cyclic FIFO buffer of size MAX_TRANSACTIONS.
 */
void recordTransaction(float amount, float history[], int *historyCount) {
    if (*historyCount < MAX_TRANSACTIONS) {
        history[*historyCount] = amount;
        (*historyCount)++;
    } else {
        /* Shift array left by 1 element to accommodate new entry */
        int i;
        for (i = 0; i < MAX_TRANSACTIONS - 1; i++) {
            history[i] = history[i + 1];
        }
        history[MAX_TRANSACTIONS - 1] = amount;
    }
}

/*
 * Outputs recent transaction events.
 */
void showMiniStatement(float history[], int historyCount) {
    int i;
    printf("\n--- Mini Statement (Last %d Transactions) ---\n", MAX_TRANSACTIONS);
    if (historyCount == 0) {
        printf("No transactions recorded in this session.\n");
        return;
    }

    for (i = 0; i < historyCount; i++) {
        if (history[i] > 0) {
            printf("%d. Deposit:  +$%.2f\n", i + 1, history[i]);
        } else {
            printf("%d. Debit:    -$%.2f\n", i + 1, -history[i]);
        }
    }
}

/*
 * Updates PIN with verification of the existing credential.
 */
int changePin(int currentPin) {
    int oldPin, newPin, confirmPin;

    printf("\n--- Change PIN ---\n");
    printf("Enter your current PIN: ");
    if (scanf("%d", &oldPin) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid format.\n");
        return currentPin;
    }

    if (oldPin != currentPin) {
        printf("[ERROR] Current PIN does not match. Operation aborted.\n");
        return currentPin;
    }

    printf("Enter new 4-digit PIN: ");
    if (scanf("%d", &newPin) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid format.\n");
        return currentPin;
    }

    printf("Confirm new 4-digit PIN: ");
    if (scanf("%d", &confirmPin) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid format.\n");
        return currentPin;
    }

    if (newPin != confirmPin) {
        printf("[ERROR] PINs do not match. PIN change rejected.\n");
        return currentPin;
    }

    if (newPin < 1000 || newPin > 9999) {
        printf("[WARNING] PIN should strictly be a 4-digit integer (1000-9999).\n");
    }

    printf("PIN successfully updated.\n");
    return newPin;
}
