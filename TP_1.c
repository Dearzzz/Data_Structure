#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 5

struct Employee
{
    int employeeID;
    char fullName[31];
    char birthPlace[31];
    char dateOfBirth[11];
    char position[51];
    struct Employee *next;
};

struct Employee *head = NULL;

int countEmployees()
{
    int count = 0;
    struct Employee *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}
void pushEmployee()
{
    if (countEmployees() == MAX_EMPLOYEES)
    {
        printf("================================\n");
        printf("Maximum number of employees reached.\n");
        printf("================================\n");
        return;
    }

    struct Employee *newEmployee = (struct Employee *)malloc(sizeof(struct Employee));

    printf("Enter Employee ID (max 5 digits): ");
    scanf("%d", &newEmployee->employeeID);
    while (newEmployee->employeeID < 0 || newEmployee->employeeID > 99999)
    {
        printf("================================\n");
        printf("Invalid Employee ID. Please enter a number (0-99999): ");
        scanf("%d", &newEmployee->employeeID);
    }

    printf("Enter Full Name (max 30 characters): ");
    scanf(" %[^\n]s", newEmployee->fullName);
    while (strlen(newEmployee->fullName) > 30)
    {
        printf("================================\n");
        printf("Invalid Full Name. Please enter a name with max 30 characters: ");
        scanf(" %[^\n]s", newEmployee->fullName);
    }

    printf("Enter Birth Place (max 30 characters): ");
    scanf(" %[^\n]s", newEmployee->birthPlace);
    while (strlen(newEmployee->birthPlace) > 30)
    {
        printf("================================\n");
        printf("Invalid Birth Place. Please enter a place with max 30 characters: ");
        scanf(" %[^\n]s", newEmployee->birthPlace);
    }

    printf("Enter Date of Birth (DD/MM/YYYY): ");
    scanf("%s", newEmployee->dateOfBirth);

    while (strlen(newEmployee->dateOfBirth) != 10)
    {
        printf("================================\n");
        printf("Invalid Input. Please enter a Date Of Birth with a right format: ");
        scanf(" %[^\n]s", newEmployee->dateOfBirth);
    }

    printf("Enter Position (max 50 characters): ");
    scanf(" %[^\n]s", newEmployee->position);
    while (strlen(newEmployee->position) > 50)
    {
        printf("================================\n");
        printf("Invalid Position. Please enter a position with max 50 characters: ");
        scanf(" %[^\n]s", newEmployee->position);
    }

    newEmployee->next = head;
    head = newEmployee;
    printf("\n================================");
    printf("\nEmployee added successfully.\n");
    printf("================================\n");
}

void displayEmployees()
{
    if (head == NULL)
    {
        printf("\n================================\n");
        printf("No employees in the database.\n");
        printf("================================\n");
        return;
    }

    struct Employee *temp = head;
    printf("\nEmployee ID\tFull Name\t\tBirth Place\tDate of Birth\tPosition\n");
    printf("------------\t----------\t\t-----------\t------------\t--------\n");

    while (temp != NULL)
    {
        printf("%d\t\t%s\t\t%s\t%s\t%s\n", temp->employeeID, temp->fullName, temp->birthPlace, temp->dateOfBirth, temp->position);
        temp = temp->next;
    }
}

void deleteEmployee()
{
    if (head == NULL)
    {
        printf("================================\n");
        printf("No employees in the database.\n");
        printf("================================");

        return;
    }

    int employeeID;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &employeeID);

    if (head->employeeID == employeeID)
    {
        struct Employee *temp = head;
        head = head->next;
        free(temp);
        printf("================================\n");
        printf("Employee deleted successfully.\n");
        printf("================================\n");

        return;
    }

    struct Employee *temp = head;
    while (temp->next != NULL)
    {
        if (temp->next->employeeID == employeeID)
        {
            struct Employee *toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete);
            printf("================================\n");
            printf("Employee deleted successfully.\n");
            printf("================================\n");
            return;
        }
        temp = temp->next;
    }
    printf("================================\n");
    printf("Employee not found in the database.\n");
    printf("================================\n");
}

void deleteAllEmployees()
{
    if (head == NULL)
    {
        printf("=============================\n");
        printf("No employees in the database.\n");
        printf("=============================\n");
        return;
    }

    while (head != NULL)
    {
        struct Employee *temp = head;
        head = head->next;
        free(temp);
    }
    printf("===================================\n");
    printf("All employees deleted successfully.\n");
    printf("===================================\n");
}

int main()
{
    int choice;
    do
    {
        printf("\nEmployee Database Menu:\n");
        printf("1. Push Employee\n");
        printf("2. Display Employees\n");
        printf("3. Delete Employee\n");
        printf("4. Delete All Employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            pushEmployee();
            break;
        case 2:
            displayEmployees();
            break;
        case 3:
            deleteEmployee();
            break;
        case 4:
            deleteAllEmployees();
            break;
        case 5:
            printf("\nExiting program...\n");
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}