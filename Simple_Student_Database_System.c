#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to represent a student
struct Student {
    char name[100];
    int id;
    float gpa;
};

// Function to add a student to the database
void addStudent(struct Student database[], int *numStudents) {
    if (*numStudents < MAX_STUDENTS) {
        printf("Enter student name: ");
        scanf("%s", database[*numStudents].name);

        printf("Enter student GPA: ");
        scanf("%f", &database[*numStudents].gpa);

        database[*numStudents].id = *numStudents + 1;  // Assign a unique ID

        (*numStudents)++;
        printf("Student added successfully!\n");
    } else {
        printf("Database is full. Cannot add more students.\n");
    }
}

// Function to display all students in the database
void displayStudents(struct Student database[], int numStudents) {
    printf("\nStudent Database:\n");
    printf("ID\tName\t\tGPA\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%d\t%s\t%.2f\n", database[i].id, database[i].name, database[i].gpa);
    }
    printf("\n");
}

// Function to search for a student by name
void searchStudent(struct Student database[], int numStudents, char searchName[]) {
    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(database[i].name, searchName) == 0) {
            printf("Student found!\n");
            printf("ID: %d\nName: %s\nGPA: %.2f\n", database[i].id, database[i].name, database[i].gpa);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student not found.\n");
    }
}

// Function to update student information by ID
void updateStudent(struct Student database[], int numStudents, int updateID) {
    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (database[i].id == updateID) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", database[i].name);

            printf("Enter new GPA: ");
            scanf("%f", &database[i].gpa);

            printf("Student information updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", updateID);
    }
}

int main() {
    struct Student database[MAX_STUDENTS];
    int numStudents = 0;
    int choice;

    do {
        printf("\nStudent Database System\n");
        printf("1. Add a student\n");
        printf("2. Display all students\n");
        printf("3. Search for a student\n");
        printf("4. Update student information\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(database, &numStudents);
                break;
            case 2:
                displayStudents(database, numStudents);
                break;
            case 3:
                char searchName[100];
                printf("Enter the name to search: ");
                scanf("%s", searchName);
                searchStudent(database, numStudents, searchName);
                break;
            case 4:
                int updateID;
                printf("Enter the ID of the student to update: ");
                scanf("%d", &updateID);
                updateStudent(database, numStudents, updateID);
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
