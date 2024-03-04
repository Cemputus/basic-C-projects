#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50

// Structure to represent a student
struct Student {
    int rollNumber;
    char name[50];
    float marks;
};

// Function to add a new student
void addStudent(struct Student students[], int *numStudents) {
    if (*numStudents < MAX_STUDENTS) {
        printf("Enter student name: ");
        scanf(" %[^\n]", students[*numStudents].name);

        printf("Enter roll number: ");
        scanf("%d", &students[*numStudents].rollNumber);

        printf("Enter marks: ");
        scanf("%f", &students[*numStudents].marks);

        (*numStudents)++;
        printf("Student added successfully!\n");
    } else {
        printf("Cannot add more students. Limit reached.\n");
    }
}

// Function to view all students
void viewStudents(struct Student students[], int numStudents) {
    printf("\nStudent Information:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Name: %s\n", students[i].name);
        printf("Marks: %.2f\n\n", students[i].marks);
    }
}

// Function to find a student by roll number
int findStudent(struct Student students[], int numStudents, int rollNumber) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            return i;  // Found the student
        }
    }
    return -1;  // Student not found
}

// Function to update student information
void updateStudent(struct Student students[], int numStudents) {
    int rollNumber;
    printf("Enter the roll number of the student to update: ");
    scanf("%d", &rollNumber);

    int index = findStudent(students, numStudents, rollNumber);
    if (index != -1) {
        printf("Enter updated marks: ");
        scanf("%f", &students[index].marks);
        printf("Student information updated successfully!\n");
    } else {
        printf("Student not found.\n");
    }
}

// Function to delete a student
void deleteStudent(struct Student students[], int *numStudents) {
    int rollNumber;
    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &rollNumber);

    int index = findStudent(students, *numStudents, rollNumber);
    if (index != -1) {
        // Shift remaining students to fill the gap
        for (int i = index; i < *numStudents - 1; i++) {
            students[i] = students[i + 1];
        }
        (*numStudents)--;
        printf("Student deleted successfully!\n");
    } else {
        printf("Student not found.\n");
    }
}

int main() {
    struct Student students[MAX_STUDENTS];
    int numStudents = 0;
    int choice;

    do {
        printf("\nStudent Information System\n");
        printf("1. Add a student\n");
        printf("2. View all students\n");
        printf("3. Update student information\n");
        printf("4. Delete a student\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &numStudents);
                break;
            case 2:
                viewStudents(students, numStudents);
                break;
            case 3:
                updateStudent(students, numStudents);
                break;
            case 4:
                deleteStudent(students, &numStudents);
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
