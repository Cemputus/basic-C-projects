#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 50

// Structure to represent an employee
struct Employee {
    int employeeID;
    char name[50];
    char position[50];
    float salary;
};

// Function to add a new employee
void addEmployee(struct Employee employees[], int *numEmployees) {
    if (*numEmployees < MAX_EMPLOYEES) {
        printf("Enter employee name: ");
        scanf(" %[^\n]", employees[*numEmployees].name);

        printf("Enter employee position: ");
        scanf(" %[^\n]", employees[*numEmployees].position);

        printf("Enter employee salary: ");
        scanf("%f", &employees[*numEmployees].salary);

        employees[*numEmployees].employeeID = *numEmployees + 1;  // Assign a unique employee ID
        (*numEmployees)++;
        printf("Employee added successfully!\n");
    } else {
        printf("Cannot add more employees. Limit reached.\n");
    }
}

// Function to view all employees
void viewEmployees(struct Employee employees[], int numEmployees) {
    printf("\nEmployee Information:\n");
    for (int i = 0; i < numEmployees; i++) {
        printf("Employee ID: %d\n", employees[i].employeeID);
        printf("Name: %s\n", employees[i].name);
        printf("Position: %s\n", employees[i].position);
        printf("Salary: %.2f\n\n", employees[i].salary);
    }
}

// Function to find an employee by ID
int findEmployee(struct Employee employees[], int numEmployees, int employeeID) {
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].employeeID == employeeID) {
            return i;  // Found the employee
        }
    }
    return -1;  // Employee not found
}

// Function to update employee information
void updateEmployee(struct Employee employees[], int numEmployees) {
    int employeeID;
    printf("Enter the employee ID to update: ");
    scanf("%d", &employeeID);

    int index = findEmployee(employees, numEmployees, employeeID);
    if (index != -1) {
        printf("Enter updated position: ");
        scanf(" %[^\n]", employees[index].position);

        printf("Enter updated salary: ");
        scanf("%f", &employees[index].salary);
        printf("Employee information updated successfully!\n");
    } else {
        printf("Employee not found.\n");
    }
}

// Function to delete an employee
void deleteEmployee(struct Employee employees[], int *numEmployees) {
    int employeeID;
    printf("Enter the employee ID to delete: ");
    scanf("%d", &employeeID);

    int index = findEmployee(employees, *numEmployees, employeeID);
    if (index != -1) {
        // Shift remaining employees to fill the gap
        for (int i = index; i < *numEmployees - 1; i++) {
            employees[i] = employees[i + 1];
        }
        (*numEmployees)--;
        printf("Employee deleted successfully!\n");
    } else {
        printf("Employee not found.\n");
    }
}

int main() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int choice;

    do {
        printf("\nEmployee Management System\n");
        printf("1. Add an employee\n");
        printf("2. View all employees\n");
        printf("3. Update employee information\n");
        printf("4. Delete an employee\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &numEmployees);
                break;
            case 2:
                viewEmployees(employees, numEmployees);
                break;
            case 3:
                updateEmployee(employees, numEmployees);
                break;
            case 4:
                deleteEmployee(employees, &numEmployees);
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
