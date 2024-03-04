#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

// Structure to represent a contact
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

// Function to add a contact to the list
void addContact(struct Contact contacts[], int *numContacts) {
    if (*numContacts < MAX_CONTACTS) {
        printf("Enter contact name: ");
        scanf(" %[^\n]", contacts[*numContacts].name);

        printf("Enter contact phone number: ");
        scanf(" %[^\n]", contacts[*numContacts].phone);

        printf("Enter contact email address: ");
        scanf(" %[^\n]", contacts[*numContacts].email);

        (*numContacts)++;
        printf("Contact added successfully!\n");
    } else {
        printf("Cannot add more contacts. Limit reached.\n");
    }
}

// Function to display all contacts in the list
void displayContacts(struct Contact contacts[], int numContacts) {
    printf("\nContact List:\n");
    for (int i = 0; i < numContacts; i++) {
        printf("%d. Name: %s\n   Phone: %s\n   Email: %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    printf("\n");
}

// Function to search for a contact by name
void searchContact(struct Contact contacts[], int numContacts, char searchName[]) {
    int found = 0;
    for (int i = 0; i < numContacts; i++) {
        if (strstr(contacts[i].name, searchName) != NULL) {
            printf("Contact found!\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
            found = 1;
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

// Function to update contact details by name
void updateContact(struct Contact contacts[], int numContacts, char updateName[]) {
    int found = 0;
    for (int i = 0; i < numContacts; i++) {
        if (strstr(contacts[i].name, updateName) != NULL) {
            found = 1;
            printf("Enter new phone number: ");
            scanf(" %[^\n]", contacts[i].phone);

            printf("Enter new email address: ");
            scanf(" %[^\n]", contacts[i].email);

            printf("Contact details updated successfully!\n");
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

// Function to delete a contact by name
void deleteContact(struct Contact contacts[], int *numContacts, char deleteName[]) {
    int found = 0;
    for (int i = 0; i < *numContacts; i++) {
        if (strstr(contacts[i].name, deleteName) != NULL) {
            found = 1;
            // Shift remaining contacts to fill the gap
            for (int j = i; j < *numContacts - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            (*numContacts)--;
            printf("Contact deleted successfully!\n");
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

int main() {
    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    int choice;

    do {
        printf("\nContact Management System\n");
        printf("1. Add a contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Update contact details\n");
        printf("5. Delete a contact\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(contacts, &numContacts);
                break;
            case 2:
                displayContacts(contacts, numContacts);
                break;
            case 3:
                char searchName[50];
                printf("Enter the name to search: ");
                scanf(" %[^\n]", searchName);
                searchContact(contacts, numContacts, searchName);
                break;
            case 4:
                char updateName[50];
                printf("Enter the name to update: ");
                scanf(" %[^\n]", updateName);
                updateContact(contacts, numContacts, updateName);
                break;
            case 5:
                char deleteName[50];
                printf("Enter the name to delete: ");
                scanf(" %[^\n]", deleteName);
                deleteContact(contacts, &numContacts, deleteName);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
