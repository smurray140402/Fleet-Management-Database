#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>

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

// Structure that holds the username and password
typedef struct {
    char username[tempValue];
    char password[tempValue];
} User;


// Function prototypes
int menu();
void addNewMachine(Node** head);
void displayAllMachines(Node* head);
void displayMachineDetails(Node* head);
void updateMachine(Node* head);
void deleteMachine(Node** head);
void generateStatistics(Node* head);
void outputReportFile(Node* head);
void listMachinesValuationDesc(Node* head);
bool login();

int main() {

    // Check login credentials before allowing access to the main program
    // Exits program if the login fails
    if (!login()) {
        printf("\n\nInvalid credentials. Exiting the program.\n");
        return 0;
    }

    printf("\n\nLogin Successful\n");

    // Variables
    int menuOption;
    Node* head = NULL;

	printf("\n*****************************************");
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
            generateStatistics(head);
            break;
        case 7:
            outputReportFile(head);
            break;
        case 8:
            listMachinesValuationDesc(head);
            break;
        default:
            break;

        }
    } while (menuOption != 0);

	return 0;
}

// Function to check login credentials
bool login() {

    FILE* loginFile = fopen("login.txt", "r");
    if (loginFile == NULL) {
        printf("Error: Unable to open login file.\n");
        return false;
    }

    // Variables
    User users[3];
    char inputUsername[tempValue];
    char inputPassword[tempValue];
    int userCount = 0;
    char ch;
    int i;

    // Read the login file and store credentials
    while (!feof(loginFile)) {
        fscanf(loginFile, "%s %s", users[userCount].username, users[userCount].password);
        userCount++;
    }

    fclose(loginFile);

    // Ask for username and password
    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");

    // For loop to get the user password inputbut change the values to '*' for security
    // https://c-program-example.com/2011/09/c-program-to-mask-password-text-with-asterisk.html#:~:text=C%20Program%20to%20mask%20password%20text%20with%20asterisk(*),-C%20Program%20to&text=This%20program%20is%20to%20illustrate,is%20replaced%20by%20'*'.
    for (i = 0; i < tempValue; i++)
    {
        ch = _getch();

        if (ch == '\r') {
            break;
        }
        inputPassword[i] = ch;
        ch = '*';
        printf("%c", ch);
        
    }
    inputPassword[i] = '\0';


    // Check if the entered credentials match any in the file
    for (int i = 0; i < userCount; i++) {
        // Valid credentials
        if (strcmp(inputUsername, users[i].username) == 0 && strcmp(inputPassword, users[i].password) == 0) {
            return true;
        }
    }

    // Invalid credentials
    return false;
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

// Function for generating statistics
void generateStatistics(Node* head) {

    // Counters for total machines per type and breakdown categories
    int totals[5] = {0};
    int breakdowns[5][4] = {{0}};

    Node* temp = head;
    while (temp != NULL) {
        int type = temp->machine.type;
        totals[type]++;

        // Breakdown categories
        if (temp->machine.breakdowns == NEVER) breakdowns[type][0]++;
        else if (temp->machine.breakdowns == LESS_THAN_THREE) breakdowns[type][1]++;
        else if (temp->machine.breakdowns == LESS_THAN_FIVE) breakdowns[type][2]++;
        else if (temp->machine.breakdowns == MORE_THAN_FIVE) breakdowns[type][3]++;

        temp = temp->next;
    }

    // Print the stats for each machine type
    const char* machineTypes[] = { "Tractor", "Excavator", "Roller", "Crane", "Mixer" };
    for (int i = 0; i < 5; i++) {
        if (totals[i] == 0) {
            printf("\n--- No Breakdown Stats for %ss---\n", machineTypes[i]);
            continue;
        }

        printf("\n--- %s Breakdown Stats ---\n", machineTypes[i]);
        printf("A. %% with no breakdowns (NEVER): %.2f%%\n", (float)breakdowns[i][0] / totals[i] * 100);
        printf("B. %% with fewer than 3 breakdowns: %.2f%%\n", (float)breakdowns[i][1] / totals[i] * 100);
        printf("C. %% with fewer than 5 breakdowns: %.2f%%\n", (float)breakdowns[i][2] / totals[i] * 100);
        printf("D. %% with more than 5 breakdowns: %.2f%%\n", (float)breakdowns[i][3] / totals[i] * 100);
    }
}

// Function to generate report file
// I understand I am duplicating code here. Might change it around at a later date
void outputReportFile(Node* head) {

    // Counters for total machines per type and breakdown categories
    int totals[5] = { 0 };
    int breakdowns[5][4] = { {0} };

    Node* temp;
    temp = head;
    int counter = 0;

    // Open report file that I will write to
    FILE* report = fopen("reportFile.txt", "w");

    if (temp == NULL) {
        printf("\nNo vechicles to display\n");
        return;
    }

    fprintf(report, "\n--- List of All Machines ---\n");

    while (temp != NULL) {
        counter++;

        int type = temp->machine.type;
        totals[type]++;

        // Breakdown categories
        if (temp->machine.breakdowns == NEVER) breakdowns[type][0]++;
        else if (temp->machine.breakdowns == LESS_THAN_THREE) breakdowns[type][1]++;
        else if (temp->machine.breakdowns == LESS_THAN_FIVE) breakdowns[type][2]++;
        else if (temp->machine.breakdowns == MORE_THAN_FIVE) breakdowns[type][3]++;

        fprintf(report, "\nMachine #%d:", counter);
        fprintf(report, "\nChassis Number: %s", temp->machine.chassisNumber);
        fprintf(report, "\nMake: %s", temp->machine.make);
        fprintf(report, "\nModel: %s", temp->machine.model);
        fprintf(report, "\nYear: %d", temp->machine.year);
        fprintf(report, "\nCost: %.2f", temp->machine.cost);
        fprintf(report, "\nCurrent Valuation: %.2f", temp->machine.valuation);
        fprintf(report, "\nMileage: %d", temp->machine.mileage);
        fprintf(report, "\nNext Service Mileage: %d", temp->machine.nextServiceMileage);
        fprintf(report, "\nOwner Name: %s", temp->machine.ownerName);
        fprintf(report, "\nOwner Email: %s", temp->machine.ownerEmail);
        fprintf(report, "\nOwner Phone: %s", temp->machine.ownerPhone);

        // Print Machine Type
        fprintf(report, "\nMachine Type: ");
        switch (temp->machine.type) {
        case TRACTOR:
            fprintf(report, "Tractor");
            break;
        case EXCAVATOR:
            fprintf(report, "Excavator");
            break;
        case ROLLER:
            fprintf(report, "Roller");
            break;
        case CRANE:
            fprintf(report, "Crane");
            break;
        case MIXER:
            fprintf(report, "Mixer");
            break;
        default:
            fprintf(report, "Unknown");
            break;
        }

        // Print Breakdown Category
        fprintf(report, "\nBreakdown Frequency: ");
        switch (temp->machine.breakdowns) {
        case NEVER:
            fprintf(report, "Never");
            break;
        case LESS_THAN_THREE:
            fprintf(report, "Less than 3 times");
            break;
        case LESS_THAN_FIVE:
            fprintf(report, "Less than 5 times");
            break;
        case MORE_THAN_FIVE:
            fprintf(report, "More than 5 times");
            break;
        default:
            fprintf(report, "Unknown");
            break;
        }

        fprintf(report, "\n---------------------------\n");

        temp = temp->next;
    }

    // Print the stats for each machine type
    const char* machineTypes[] = { "Tractor", "Excavator", "Roller", "Crane", "Mixer" };
    for (int i = 0; i < 5; i++) {
        if (totals[i] == 0) {
            fprintf(report, "\n--- No Breakdown Stats for %ss---\n", machineTypes[i]);
            continue;
        }

        fprintf(report, "\n--- %s Breakdown Stats ---\n", machineTypes[i]);
        fprintf(report, "A. %% with no breakdowns (NEVER): %.2f%%\n", (float)breakdowns[i][0] / totals[i] * 100);
        fprintf(report, "B. %% with fewer than 3 breakdowns: %.2f%%\n", (float)breakdowns[i][1] / totals[i] * 100);
        fprintf(report, "C. %% with fewer than 5 breakdowns: %.2f%%\n", (float)breakdowns[i][2] / totals[i] * 100);
        fprintf(report, "D. %% with more than 5 breakdowns: %.2f%%\n", (float)breakdowns[i][3] / totals[i] * 100);
    }
    fclose(report);
    printf("\n--- Report successfully written to reportFile.txt ---\n");
}

// Function to list all the machinery in order of current valuation
void listMachinesValuationDesc(Node* head) {

    Node* current;
    current = head;

    if (current == NULL) {
        printf("\nNo vehicles to display\n");
        return;
    }

    Node* nextNode;
    Machine tempMachine;

    // Bubble Sort to sort machines by valuation in descending order
    // https://www.geeksforgeeks.org/bubble-sort-algorithm/
    // https://www.programiz.com/dsa/bubble-sort
    for (current = head; current != NULL; current = current->next) {
        for (nextNode = current->next; nextNode != NULL; nextNode = nextNode->next) {
            if (current->machine.valuation < nextNode->machine.valuation) {
                // Swap the machine data is current valuation is less than the next
                tempMachine = current->machine;
                current->machine = nextNode->machine;
                nextNode->machine = tempMachine;
            }
        }
    }

    // Display sorted machines by valuation
    Node* temp = head;
    int counter = 0;

    printf("\n--- Machines Sorted by Valuation (Descending) ---\n");

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

    system("cls");

    return option;
}



