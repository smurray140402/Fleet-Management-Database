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
typedef struct {
    Machine machine;
    struct Node* next;
}Node;

int menu();
void addNewMachine();

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
            printf("case2");
            break;
        case 3:
            printf("case3");
            break;
        case 4:
            printf("case4");
            break;
        case 5:
            printf("case5");
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

void addNewMachine(Node** head) {
    Machine* newMachine = (Machine*)malloc(sizeof(Machine));

    printf("\nNew Vehicle:");

    // Chassis Number
    printf("\nPlease enter machinery chassis number: ");
    scanf("%s", newMachine->chassisNumber);

    // Make
    printf("\nPlease enter machinery make: ");
    scanf("%s", newMachine->make);

    // Model
    printf("\nPlease enter machinery model: ");
    scanf("%s", newMachine->model);

    // Year of Manufacture
    printf("\nPlease enter machinery year of manufacture: ");
    scanf("%d", &newMachine->year);

    // Cost
    printf("\nPlease enter machinery cost: ");
    scanf("%f", &newMachine->cost);

    // Current Valuation
    printf("\nPlease enter machinery current valuation: ");
    scanf("%f", &newMachine->valuation);

    // Current Mileage
    printf("\nPlease enter machinery current mileage: ");
    scanf("%d", &newMachine->mileage);

    // Next Service Mileage
    printf("\nPlease enter machinery next service mileage: ");
    scanf("%d", &newMachine->nextServiceMileage);

    // Owner Name
    printf("\nPlease enter machinery owner name: ");
    scanf("%s", newMachine->ownerName);

    // Owner Email
    printf("\nPlease enter machinery owner email: ");
    scanf("%s", newMachine->ownerEmail);

    // Owner Number
    printf("\nPlease enter machinery owner number: ");
    scanf("%s", newMachine->ownerPhone);

    // Type
    printf("\nPlease enter machinery type (0: Tractor, 1: Excavator, 2: Roller, 3: Crane, 4: Mixer): ");
    int typeInput;
    scanf("%d", &typeInput);
    newMachine->type = (MachineType)typeInput;

    // Breakdowns
    printf("\nPlease enter breakdown frequency (0: Never, 1: <3 times, 2: <5 times, 3: >5 times): ");
    int breakdownInput;
    scanf("%d", &breakdownInput);
    newMachine->breakdowns = (BreakdownCategory)breakdownInput;

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
    printf("\n---------------------------\n\n");

    scanf("%d", &option);

    return option;
}



