#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 51 // Including null terminator
#define DATE_LENGTH 11
#define REGISTRATION_LENGTH 11
#define PROGRAM_CODE_LENGTH 5

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    char dateOfBirth[DATE_LENGTH];
    char registrationNumber[REGISTRATION_LENGTH];
    char programCode[PROGRAM_CODE_LENGTH];
    float annualTuition;
    struct Node* next;
} Node;

// Function prototypes
Node* createStudent();
void readStudents(Node *head);
void updateStudent(Node *head);
void deleteStudent(Node **head);
void searchStudentByRegNumber(Node *head);
void sortStudents(Node *head);
void exportStudentsToFile(Node *head);

int main() {
    Node *head = NULL;
    int choice;

    do {
        printf("\n--------STUDENT MANAGEMENT SYSTEM_GROUP 10--------\n");
        printf("\nMain Menu\n");
        printf("1. Create student\n");
        printf("2. Read students\n");
        printf("3. Update student\n");
        printf("4. Delete student\n");
        printf("5. Search student by registration number\n");
        printf("6. Sort students\n");
        printf("7. Export students to file\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = createStudent(head);
                break;
            case 2:
                readStudents(head);
                break;
            case 3:
                updateStudent(head);
                break;
            case 4:
                deleteStudent(&head);
                break;
            case 5:
                searchStudentByRegNumber(head);
                break;
            case 6:
                sortStudents(head);
                break;
            case 7:
                exportStudentsToFile(head);
                break;
            case 8:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }
    } while (choice != 8);

    // Free memory before exiting
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

Node* createStudent(Node *head) {
    Node *newStudent = (Node*)malloc(sizeof(Node));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        return head; // Return the current head unchanged
    }

    printf("Enter name (up to 50 characters, alphabetic characters only): ");
    getchar(); // Clearing input buffer
    fgets(newStudent->name, MAX_NAME_LENGTH, stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0'; // Removing trailing newline

    // Validate name - ensure no numeric characters
    bool validName = true;
    for (int i = 0; newStudent->name[i] != '\0'; i++) {
        if (!isalpha(newStudent->name[i])) {
            validName = false;
            break;
        }
    }

    if (!validName) {
        printf("Invalid name. Please enter alphabetic characters only.\n");
        free(newStudent);
        return head; // Return the current head unchanged
    }

    bool validDate = false;
    while (!validDate) {
        printf("Enter date of birth (YYYY-MM-DD): ");
        scanf("%s", newStudent->dateOfBirth);

        // Validate date format (YYYY-MM-DD)
        int year, month, day;
        if (sscanf(newStudent->dateOfBirth, "%d-%d-%d", &year, &month, &day) == 3) {
            if (month >= 1 && month <= 12) {
                // Check day based on month (considering up to 30 days for simplicity)
                if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day >= 1 && day <= 31)) {
                    validDate = true;
                } else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day >= 1 && day <= 30)) {
                    validDate = true;
                } else if (month == 2 && (day >= 1 && day <= 28)) {
                    validDate = true;
                } else {
                    printf("Invalid day for the given month. Please enter a valid date (YYYY-MM-DD).\n");
                }
            } else {
                printf("Invalid month. Please enter a valid date (YYYY-MM-DD).\n");
            }
        } else {
            printf("Invalid date format. Please enter date in the format YYYY-MM-DD.\n");
        }

        // Clear input buffer in case of invalid input
        while (getchar() != '\n');
    }

    bool validRegistration = false;
    while (!validRegistration) {
        printf("Enter registration number (10 digits): ");
        scanf("%s", newStudent->registrationNumber);

        // Check if registration number is exactly 10 digits
        if (strlen(newStudent->registrationNumber) == 10) {
            // Validate that all characters are digits
            bool allDigits = true;
            for (int i = 0; i < 10; i++) {
                if (!isdigit(newStudent->registrationNumber[i])) {
                    allDigits = false;
                    break;
                }
            }
            if (allDigits) {
                validRegistration = true;
            } else {
                printf("Invalid registration number. Please enter exactly 10 digits.\n");
            }
        } else {
            printf("Invalid registration number length. Please enter exactly 10 digits.\n");
        }

        // Clear input buffer in case of invalid input
        while (getchar() != '\n');
    }

    bool validProgramCode = false;
    while (!validProgramCode) {
        printf("Enter program code (exactly 4 characters): ");
        scanf("%s", newStudent->programCode);

        // Check if program code is exactly 4 characters long
        if (strlen(newStudent->programCode) == 4) {
            validProgramCode = true;
        } else {
            printf("Invalid program code length. Please enter exactly 4 characters.\n");
        }

        // Clear input buffer in case of invalid input
        while (getchar() != '\n');
    }

    bool validTuition = false;
    while (!validTuition) {
        printf("Enter annual tuition (non-zero): ");
        if (scanf("%f", &newStudent->annualTuition) == 1 && newStudent->annualTuition > 0) {
            validTuition = true;
        } else {
            printf("Invalid tuition amount. Please enter a valid non-zero numerical value.\n");

            // Clear input buffer in case of invalid input
            while (getchar() != '\n');
        }
    }

    newStudent->next = NULL; // New node will be the last node

    if (head == NULL) {
        // If the list is empty, make the new node the head
        return newStudent;
    } else {
        // Traverse to the end of the list to append the new node
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent; // Append new node to the end
        return head; // Return the head of the updated list
    }
}

void readStudents(Node *head) {
    if (head == NULL) {
        printf("No students to display.\n");
        return;
    }

    Node *current = head;
    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Date of Birth: %s\n", current->dateOfBirth);
        printf("Registration Number: %s\n", current->registrationNumber);
        printf("Program Code: %s\n", current->programCode);
        printf("Annual Tuition: %.2f\n", current->annualTuition);
        printf("\n");

        current = current->next;
    }
}

void updateStudent(Node *head) {
    if (head == NULL) {
        printf("No students to update.\n");
        return;
    }

    char regNum[REGISTRATION_LENGTH];
    printf("Enter registration number of the student to update: ");
    scanf("%s", regNum);

    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->registrationNumber, regNum) == 0) {
            printf("Enter new name (up to 50 characters): ");
            getchar(); // Clearing input buffer
            fgets(current->name, MAX_NAME_LENGTH, stdin);
            current->name[strcspn(current->name, "\n")] = '\0'; // Removing trailing newline

            printf("Enter new date of birth (YYYY-MM-DD): ");
            scanf("%s", current->dateOfBirth);

            printf("Enter new program code (up to 4 characters): ");
            scanf("%s", current->programCode);

            printf("Enter new annual tuition (non-zero): ");
            scanf("%f", &current->annualTuition);

            printf("Student information updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Student with registration number %s not found.\n", regNum);
}

void deleteStudent(Node **head) {
    if (*head == NULL) {
        printf("No students to delete.\n");
        return;
    }

    char regNum[REGISTRATION_LENGTH];
    printf("Enter registration number of the student to delete: ");
    scanf("%s", regNum);

    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->registrationNumber, regNum) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Student deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Student with registration number %s not found.\n", regNum);
}

void searchStudentByRegNumber(Node *head) {
    if (head == NULL) {
        printf("No students to search.\n");
        return;
    }

    char regNum[REGISTRATION_LENGTH];
    printf("Enter registration number of the student to search: ");
    scanf("%s", regNum);

    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->registrationNumber, regNum) == 0) {
            printf("Name: %s\n", current->name);
            printf("Date of Birth: %s\n", current->dateOfBirth);
            printf("Program Code: %s\n", current->programCode);
            printf("Annual Tuition: %.2f\n", current->annualTuition);
            return;
        }
        current = current->next;
    }

    printf("Student with registration number %s not found.\n", regNum);
}

void sortStudents(Node *head) {
    if (head == NULL || head->next == NULL) {
        printf("No students to sort or only one student in the list.\n");
        return;
    }

    Node *ptr1, *ptr2;
    int swapped;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != NULL) {
            ptr2 = ptr1->next;
            if (strcmp(ptr1->name, ptr2->name) > 0) {
                // Swap data
                Node temp = *ptr1;
                *ptr1 = *ptr2;
                *ptr2 = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
    } while (swapped);
}

void exportStudentsToFile(Node *head) {
    if (head == NULL) {
        printf("No students to export.\n");
        return;
    }

    FILE *file = fopen("students.csv", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Node *current = head;
    while (current != NULL) {
        fprintf(file, "%s,%s,%s,%s,%.2f\n", current->name, current->dateOfBirth,
                current->registrationNumber, current->programCode, current->annualTuition);
        current = current->next;
    }

    fclose(file);
    printf("Students exported to file successfully.\n");
}
