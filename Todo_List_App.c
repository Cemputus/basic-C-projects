#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

// Structure to represent a task
struct Task {
    char description[200];
    int isComplete;
};

// Function to add a task to the to-do list
void addTask(struct Task toDoList[], int *numTasks) {
    if (*numTasks < MAX_TASKS) {
        printf("Enter task description: ");
        scanf(" %[^\n]", toDoList[*numTasks].description);
        toDoList[*numTasks].isComplete = 0;  // Task starts as incomplete

        (*numTasks)++;
        printf("Task added successfully!\n");
    } else {
        printf("Cannot add more tasks. Limit reached.\n");
    }
}

// Function to display all tasks in the to-do list
void displayTasks(struct Task toDoList[], int numTasks) {
    printf("\nTo-Do List:\n");
    for (int i = 0; i < numTasks; i++) {
        printf("%d. %s - %s\n", i + 1, toDoList[i].isComplete ? "[X]" : "[ ]", toDoList[i].description);
    }
    printf("\n");
}

// Function to mark a task as complete
void markComplete(struct Task toDoList[], int numTasks, int taskNumber) {
    if (taskNumber >= 1 && taskNumber <= numTasks) {
        toDoList[taskNumber - 1].isComplete = 1;
        printf("Task marked as complete!\n");
    } else {
        printf("Invalid task number.\n");
    }
}

// Function to delete a task
void deleteTask(struct Task toDoList[], int *numTasks, int taskNumber) {
    if (taskNumber >= 1 && taskNumber <= *numTasks) {
        // Shift remaining tasks to fill the gap
        for (int i = taskNumber - 1; i < *numTasks - 1; i++) {
            toDoList[i] = toDoList[i + 1];
        }
        (*numTasks)--;
        printf("Task deleted successfully!\n");
    } else {
        printf("Invalid task number.\n");
    }
}

int main() {
    struct Task toDoList[MAX_TASKS];
    int numTasks = 0;
    int choice;

    do {
        printf("\nTo-Do List Application\n");
        printf("1. Add a task\n");
        printf("2. Display tasks\n");
        printf("3. Mark a task as complete\n");
        printf("4. Delete a task\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(toDoList, &numTasks);
                break;
            case 2:
                displayTasks(toDoList, numTasks);
                break;
            case 3:
                int completeTaskNumber;
                printf("Enter the task number to mark as complete: ");
                scanf("%d", &completeTaskNumber);
                markComplete(toDoList, numTasks, completeTaskNumber);
                break;
            case 4:
                int deleteTaskNumber;
                printf("Enter the task number to delete: ");
                scanf("%d", &deleteTaskNumber);
                deleteTask(toDoList, &numTasks, deleteTaskNumber);
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
