#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100

// Struct to store expense details
typedef struct {
    char category[50];
    float amount;
    char date[15];
} Expense;

Expense expenses[MAX_EXPENSES];
int expense_count = 0;

// Function to add a new expense
void addExpense() {
    if (expense_count >= MAX_EXPENSES) {
        printf("Expense limit reached. Cannot add more.\n");
        return;
    }

    printf("Enter category (e.g., Food, Travel): ");
    scanf(" %[^\n]", expenses[expense_count].category);
    printf("Enter amount: ");
    scanf("%f", &expenses[expense_count].amount);
    printf("Enter date (YYYY-MM-DD): ");
    scanf(" %[^\n]", expenses[expense_count].date);

    expense_count++;
    printf("Expense added successfully!\n");
}

// Function to view all expenses
void viewExpenses() {
    if (expense_count == 0) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("\n--- Expense List ---\n");
    for (int i = 0; i < expense_count; i++) {
        printf("%d. %s - Rs%.2f - %s\n", i + 1, expenses[i].category, expenses[i].amount, expenses[i].date);
    }
}

// Function to save expenses to a file
void saveExpenses() {
    FILE *file = fopen("expenses.txt", "w");
    if (!file) {
        printf("Error saving expenses.\n");
        return;
    }

    for (int i = 0; i < expense_count; i++) {
        fprintf(file, "%s %.2f %s\n", expenses[i].category, expenses[i].amount, expenses[i].date);
    }

    fclose(file);
    printf("Expenses saved successfully!\n");
}

// Function to load expenses from a file
void loadExpenses() {
    FILE *file = fopen("expenses.txt", "r");
    if (!file) {
        printf("No saved expenses found.\n");
        return;
    }

    expense_count = 0;
    while (fscanf(file, " %49s %f %14s", expenses[expense_count].category, &expenses[expense_count].amount, expenses[expense_count].date) != EOF) {
        expense_count++;
    }

    fclose(file);
    printf("Expenses loaded successfully!\n");
}

// Main menu function
void menu() {
    int choice;

    while (1) {
        printf("\n--- Personal Expense Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Save Expenses\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                saveExpenses();
                break;
            case 4:
                printf("Exiting and saving expenses. Goodbye!\n");
                saveExpenses();
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    loadExpenses();  // Load previous data if available
    menu();          // Start the main menu
    return 0;
}
