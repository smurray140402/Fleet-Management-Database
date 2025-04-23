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



