#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define tempValue 30

// Enum that represents the different machine types
typedef enum { 
    TRACTOR, 
    EXCAVATOR, 
    ROLLER, 
    CRANE, 
    MIXER 
} MachineType;

// Enum that represents the categories of machine breakdowns
typedef enum { 
    NEVER, 
    LESS_THAN_THREE, 
    LESS_THAN_FIVE, 
    MORE_THAN_FIVE 
} BreakdownCategory;

// Structure to hold all machine details
typedef struct {
    char chassisNumber[tempValue];
    char make[tempValue];
    char model[tempValue];
    int year;
    float cost;
    float valuation;
    int mileage;
    int nextServiceMileage;
    char ownerName[tempValue];
    char ownerEmail[tempValue];
    char ownerPhone[tempValue];
    MachineType type;
    BreakdownCategory breakdowns;
} Machine;

// Structure for the linked list. 
// Each node holds one Machine and a pointer to the next node.
typedef struct Node{
    Machine machine;
    struct Node* next;
}Node;


// Function prototypes
int menu();
void addNewMachine(Node** head);
void displayAllMachines(Node* head);
void displayMachineDetails(Node* head);
void updateMachine(Node* head);
void deleteMachine(Node** head);


int main() {

    // Variables
    int menuOption;
    Node* head = NULL;

	printf("*****************************************");
	printf("\n*                                       *");
	printf("\n*\tFleet Management Database\t*");
	printf("\n*                                       *");
	printf("\n*****************************************");

    // Do while loop that loops until user exits the application
    do {
        menuOption = menu();

        // Switch to handle the users menu choice
        switch (menuOption) {
        case 1:
            addNewMachine(&head);
            break;
        case 2:
            displayAllMachines(head);
            break;
        case 3:
            displayMachineDetails(head);
            break;
        case 4:
            updateMachine(head);
            break;
        case 5:
            deleteMachine(&head);
            break;
        case 6:
            printf("case6");
            break;
        case 7:
            printf("case7");
            break;
        case 8:
            printf("case8");
            break;
        default:
            break;

        }
    } while (menuOption != 0);

	return 0;
}

// Function to add new machine to the list. It uses strcmp to sort the list as it adds each element.
void addNewMachine(Node** head) {
    // Create new machine newMachine to hold the machine details temporarily
    Machine* newMachine = (Machine*)malloc(sizeof(Machine));
    if (!newMachine) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\n--- New Vehicle ---");

    // Chassis Number
    printf("\nPlease enter machinery chassis number: ");
    scanf("%s", newMachine->chassisNumber);

    // Check if chassis numbeer is unique
    Node* current = *head;
    while (current != NULL) {
        if (strcmp(current->machine.chassisNumber, newMachine->chassisNumber) == 0) {
            printf("Error: Chassis number already exists!\n");
            free(newMachine);
            return;
        }
        current = current->next;
    }

    // Make
    printf("Please enter machinery make: ");
    scanf("%s", newMachine->make);

    // Model
    printf("Please enter machinery model: ");
    scanf("%s", newMachine->model);

    // Year of Manufacture
    printf("Please enter machinery year of manufacture: ");
    scanf("%d", &newMachine->year);

    // Cost
    printf("Please enter machinery cost: ");
    scanf("%f", &newMachine->cost);

    // Current Valuation
    printf("Please enter machinery current valuation: ");
    scanf("%f", &newMachine->valuation);

    // Current Mileage
    printf("Please enter machinery current mileage: ");
    scanf("%d", &newMachine->mileage);

    // Next Service Mileage
    printf("Please enter machinery next service mileage: ");
    scanf("%d", &newMachine->nextServiceMileage);

    // Owner Name
    printf("Please enter machinery owner name: ");
    scanf("%s", newMachine->ownerName);

    // Owner Email
    printf("Please enter machinery owner email: ");
    scanf("%s", newMachine->ownerEmail);

    // Owner Number
    printf("Please enter machinery owner number: ");
    scanf("%s", newMachine->ownerPhone);

    // Type
    printf("Please enter machinery type (0: Tractor, 1: Excavator, 2: Roller, 3: Crane, 4: Mixer): ");
    int typeInput;
    scanf("%d", &typeInput);
    newMachine->type = (MachineType)typeInput;

    // Breakdowns
    printf("Please enter breakdown frequency (0: Never, 1: <3 times, 2: <5 times, 3: >5 times): ");
    int breakdownInput;
    scanf("%d", &breakdownInput);
    newMachine->breakdowns = (BreakdownCategory)breakdownInput;

    // Create new node to store the machine
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed for the new node!\n");
        free(newMachine);
        return;
    }

    // Set the machine details in the new node
    newNode->machine = *newMachine;
    newNode->next = NULL;

    // If list is empty or chassis number is smaller than the first node chassis number insert at the head
    if (*head == NULL || strcmp((*head)->machine.chassisNumber, newMachine->chassisNumber) > 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        // Create temp node which holds the previous node
        Node* temp = NULL;
        current = *head;

        // Traverse to find the correct position for the new node
        while (current != NULL && strcmp(current->machine.chassisNumber, newMachine->chassisNumber) < 0) {
            temp = current;
            current = current->next;
        }
        // Insert the new node
        temp->next = newNode;
        newNode->next = current;
    }

    printf("\nNew machine added successfully!\n");

    // Free memory for the temporary machine object
    free(newMachine);

}

// Function to display all machines in the list.
void displayAllMachines(Node* head) {

    Node* temp;
    temp = head;
    int counter = 0;

    if (temp == NULL) {
        printf("\nNo vechicles to display\n");
        return;
    }

    printf("\n--- List of All Machines ---\n");

    while (temp != NULL) {
        counter++;
        printf("\nMachine #%d:", counter);
        printf("\nChassis Number: %s", temp->machine.chassisNumber);
        printf("\nMake: %s", temp->machine.make);
        printf("\nModel: %s", temp->machine.model);
        printf("\nYear: %d", temp->machine.year);
        printf("\nCost: %.2f", temp->machine.cost);
        printf("\nCurrent Valuation: %.2f", temp->machine.valuation);
        printf("\nMileage: %d", temp->machine.mileage);
        printf("\nNext Service Mileage: %d", temp->machine.nextServiceMileage);
        printf("\nOwner Name: %s", temp->machine.ownerName);
        printf("\nOwner Email: %s", temp->machine.ownerEmail);
        printf("\nOwner Phone: %s", temp->machine.ownerPhone);

        // Print Machine Type
        printf("\nMachine Type: ");
        switch (temp->machine.type) {
            case TRACTOR: 
                printf("Tractor"); 
                break;
            case EXCAVATOR: 
                printf("Excavator"); 
                break;
            case ROLLER: 
                printf("Roller"); 
                break;
            case CRANE: 
                printf("Crane"); 
                break;
            case MIXER: 
                printf("Mixer"); 
                break;
            default: 
                printf("Unknown"); 
                break;
        }

        // Print Breakdown Category
        printf("\nBreakdown Frequency: ");
        switch (temp->machine.breakdowns) {
            case NEVER: 
                printf("Never"); 
                break;
            case LESS_THAN_THREE: 
                printf("Less than 3 times"); 
                break;
            case LESS_THAN_FIVE: 
                printf("Less than 5 times"); 
                break;
            case MORE_THAN_FIVE: 
                printf("More than 5 times"); 
                break;
            default: 
                printf("Unknown"); 
                break;
        }

        printf("\n---------------------------\n");

        temp = temp->next;
    }
}

// Function to display a machines details
void displayMachineDetails(Node* head) {

    Node* temp;
    temp = head;

    if (temp == NULL) {
        printf("\nError...No machines in the list...returning\n");
        return;
    }

    char chassisSearch[tempValue];
    printf("\nPlease enter machine chassis number you wish to search: ");
    scanf("%s", chassisSearch);

    while (temp != NULL) {
       
        // I would like to make the output of the machine details into a seperate function as a lot of this code is duplicated 
        // in displayAllMachines above. But since I dont want machine chassis to be printed again I will leave it for now
        if (strcmp(temp->machine.chassisNumber,chassisSearch) == 0) {
            printf("\n--- Details for machine chassis #%s ---\n", temp->machine.chassisNumber);
            printf("\nMake: %s", temp->machine.make);
            printf("\nModel: %s", temp->machine.model);
            printf("\nYear: %d", temp->machine.year);
            printf("\nCost: %.2f", temp->machine.cost);
            printf("\nCurrent Valuation: %.2f", temp->machine.valuation);
            printf("\nMileage: %d", temp->machine.mileage);
            printf("\nNext Service Mileage: %d", temp->machine.nextServiceMileage);
            printf("\nOwner Name: %s", temp->machine.ownerName);
            printf("\nOwner Email: %s", temp->machine.ownerEmail);
            printf("\nOwner Phone: %s", temp->machine.ownerPhone);

            // Print Machine Type
            printf("\nMachine Type: ");
            switch (temp->machine.type) {
            case TRACTOR:
                printf("Tractor");
                break;
            case EXCAVATOR:
                printf("Excavator");
                break;
            case ROLLER:
                printf("Roller");
                break;
            case CRANE:
                printf("Crane");
                break;
            case MIXER:
                printf("Mixer");
                break;
            default:
                printf("Unknown");
                break;
            }

            // Print Breakdown Category
            printf("\nBreakdown Frequency: ");
            switch (temp->machine.breakdowns) {
            case NEVER:
                printf("Never");
                break;
            case LESS_THAN_THREE:
                printf("Less than 3 times");
                break;
            case LESS_THAN_FIVE:
                printf("Less than 5 times");
                break;
            case MORE_THAN_FIVE:
                printf("More than 5 times");
                break;
            default:
                printf("Unknown");
                break;
            }

            printf("\n---------------------------\n");

            return;
        }

        temp = temp->next;
    }
    printf("\n--- Machine Chassis #%s does not exist in the database ---\n", chassisSearch);
}

// Function that allows user to update machine details
void updateMachine(Node* head)
{
    Node* temp;
    temp = head;

    if (temp == NULL) {
        printf("\nError...No machines in the list...returning\n");
        return;
    }

    char chassisSearch[tempValue];
    printf("\nPlease enter machine chassis number you wish to update: ");
    scanf("%s", chassisSearch);

    while (temp != NULL) {

        // If a chassis number matches the user input it allows the user to update Current Valuation, Current Mileage, Next Service Mileage and Current Breakdowns
        if (strcmp(temp->machine.chassisNumber, chassisSearch) == 0) {
            printf("\n--- Update details for machine chassis #%s ---\n", temp->machine.chassisNumber);

            printf("\nCurrent Valuation: %.2f \nNew Valuation: ", temp->machine.valuation);
            scanf("%f", &temp->machine.valuation);
            printf("\nCurrent Mileage: %d \nNew Mileage: ", temp->machine.mileage);
            scanf("%d", &temp->machine.mileage);
            printf("\nNext Service Mileage: %d \nNew Service Mileage: ", temp->machine.nextServiceMileage);
            scanf("%d", &temp->machine.nextServiceMileage);

            printf("\nCurrent Breakdown Frequency: ");
            switch (temp->machine.breakdowns) {
            case NEVER:
                printf("Never");
                break;
            case LESS_THAN_THREE:
                printf("Less than 3 times");
                break;
            case LESS_THAN_FIVE:
                printf("Less than 5 times");
                break;
            case MORE_THAN_FIVE:
                printf("More than 5 times");
                break;
            default:
                printf("Unknown");
                break;
            }

            printf("\nEnter New Breakdown Frequency (0: Never, 1: <3 times, 2: <5 times, 3: >5 times): ");
            int breakdownInput;
            scanf("%d", &breakdownInput);
            temp->machine.breakdowns = (BreakdownCategory)breakdownInput;

            printf("\n---------------------------\n");

            return;
        }

        temp = temp->next;
    }
    printf("\n--- Machine Chassis #%s does not exist in the database ---\n", chassisSearch);
}

// Function that allows user to delete a machine
void deleteMachine(Node** head)
{
    Node* temp = *head;
    Node* prev = NULL;

    if (temp == NULL) {
        printf("\nError...No machines in the list...returning\n");
        return;
    }

    char chassisSearch[tempValue];
    printf("\nPlease enter machine chassis number you wish to delete: ");
    scanf("%s", chassisSearch);

    while (temp != NULL) {

        if (strcmp(temp->machine.chassisNumber, chassisSearch) == 0) {
            
            // If the node to delete is the first one
            if (prev == NULL) {
                *head = temp->next;
            }
            else {
                prev->next = temp->next;
            }

            free(temp);
            printf("\n--- Machine with chassis number %s deleted successfully! ---\n", chassisSearch);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
    printf("\n--- Machine Chassis #%s does not exist in the database ---\n", chassisSearch);
}


// Function for menu which returns the users choice
int menu() {

    // Variables
    int option;

    printf("\n---------------------------");
    printf("\n(1) ADD NEW MACHINE");
    printf("\n---------------------------");
    printf("\n(2) DISPLAY ALL MACHINES");
    printf("\n---------------------------");
    printf("\n(3) DISPLAY MACHINE DETAILS");
    printf("\n---------------------------");
    printf("\n(4) UPDATE A MACHINE");
    printf("\n---------------------------");
    printf("\n(5) DELETE A MACHINE");
    printf("\n---------------------------");
    printf("\n(6) GENERATE STATISTICS");
    printf("\n---------------------------");
    printf("\n(7) OUTPUT REPORT FILE");
    printf("\n---------------------------");
    printf("\n(8) CURRENT VALUATION LIST");
    printf("\n---------------------------");
    printf("\n(0) EXIT");
    printf("\n---------------------------\nYour choice....");

    scanf("%d", &option);

    return option;
}



