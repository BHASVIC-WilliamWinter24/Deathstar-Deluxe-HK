#include <stdio.h>

// Function to get board type and ensure valid input
int getBoardType(int *boardType) {
    do {
        printf("Enter the board type (1 for Full Board, 2 for Half Board, 3 for Bed and Breakfast): ");
        fflush(stdin);
        scanf("%d", boardType);
        // Validate the board type input
        if (*boardType < 1 || *boardType > 3) {
            printf("Invalid board type. Please enter 1, 2, or 3.\n");
        }
    } while (*boardType < 1 || *boardType > 3);
    return *boardType;
}

// Function to calculate the room cost based on room number
int calculateRoomCost(int roomNumber, float *roomCost, int days) {
    do {
        printf("Enter the room number your stay was in (1-6): ");
        fflush(stdin);
        scanf("%d", &roomNumber);
        // Validate room number input
        if (roomNumber > 6 || roomNumber < 1) {
            printf("Error: Room number must be between 1 and 6.\n");
        }
    } while (roomNumber > 6 || roomNumber < 1);

    printf("The room number of your stay is: %d\n", roomNumber);

    // Assign room cost based on room number
    if (roomNumber == 1 || roomNumber == 2) {
        *roomCost = 100.0 * days;
    } else if (roomNumber == 3) {
        *roomCost = 85.0 * days;
    } else if (roomNumber == 4 || roomNumber == 5) {
        *roomCost = 75.0 * days;
    } else if (roomNumber == 6) {
        *roomCost = 50.0 * days;
    }

    return 0;
}

// Function to apply a discount based on the main user's age
float applyMainUserDiscount(float *finalRoomCost, int mainUserAge, float roomCost) {
    do {
        printf("Enter the main user's age (must be at least 18): ");
        fflush(stdin);
        scanf("%d", &mainUserAge);
        // Ensure the main user's age is at least 18
        if (mainUserAge < 18) {
            printf("Error: Age must be 18 or older.\n");
        }
    } while (mainUserAge < 18);

    // If the main user is older than 65, apply a 10% discount
    if (mainUserAge > 65) {
        printf("Due to being older than 65, you are eligible for a 10%% discount on your room rate.\n");
        *finalRoomCost = roomCost * 0.9;
    } else {
        printf("As you are younger than 66, you are not eligible for a 10%% discount on your room.\n");
        *finalRoomCost = roomCost;
    }
    printf("Your room cost is therefore: %.2f\n", *finalRoomCost);
    return *finalRoomCost;
}

// Function to calculate adult meal costs based on board type and number of guests
float applyAdultMealCost(int boardType, int days, int adults, float *boardCostAdult) {
    do {
        printf("How many adults are in your group: ");
        fflush(stdin);
        scanf("%d", &adults);
        // Ensure at least one adult is in the group
        if (adults <= 0) {
            printf("Invalid number. There must be at least one adult.\n");
        }
    } while (adults <= 0);

    printf("You have %d adult guests.\n", adults);

    // Calculate the meal costs for adults based on board type
    if (boardType == 1) {
        *boardCostAdult = (20.0 * days) * adults;
    } else if (boardType == 2) {
        *boardCostAdult = (15.0 * days) * adults;
    } else if (boardType == 3) {
        *boardCostAdult = (5.0 * days) * adults;
    }

    printf("Total cost for your adults' board meals is: %.2f\n", *boardCostAdult);
    return *boardCostAdult;
}

// Function to apply a discount for children’s meal costs based on board type
float applyChildrenDiscount(int boardType, int children, int days, float *boardCostChildren) {
    do {
        printf("How many children are in your group: ");
        fflush(stdin);
        scanf("%d", &children);
        // Ensure the number of children is non-negative
        if (children < 0) {
            printf("Invalid number. Please enter 0 or a positive number.\n");
        }
    } while (children < 0);

    if (children > 0) {
        printf("You are eligible for a 50%% discount on each of your children's meal board cost.\n");

        // Calculate the meal cost for children based on board type and apply the discount
        if (boardType == 1) {
            *boardCostChildren = ((20 * days) * 0.5) * children;
        } else if (boardType == 2) {
            *boardCostChildren = ((15 * days) * 0.5) * children;
        } else if (boardType == 3) {
            *boardCostChildren = ((5 * days) * 0.5) * children;
        }
        printf("Total cost for your children's board meals is: %.2f\n", *boardCostChildren);
    } else {
        *boardCostChildren = 0;
        printf("You have no children in your group, so there is no additional cost.\n");
    }

    return *boardCostChildren;
}

// Function to handle the newspaper cost based on user choice
float newspaperCostTotal(char newspaperChoice, float *newspaperCost) {
    do {
        printf("Have you bought a newspaper (Y/N): ");
        fflush(stdin);
        scanf(" %c", &newspaperChoice);

        if (newspaperChoice == 'Y' || newspaperChoice == 'y') {
            *newspaperCost = 5.50;
            break;
        } else if (newspaperChoice == 'N' || newspaperChoice == 'n') {
            *newspaperCost = 0.00;
            break;
        } else {
            printf("Invalid input. Please enter 'Y' for yes or 'N' for no.\n");
        }
    } while (1);

    return *newspaperCost;
}

int main(void) {
    int roomNumber, mainUserAge, children, days, adults, boardType;
    float roomCost, finalRoomCost, boardCostAdult, totalBoardCost, boardCostChildren = 0, finalBill, newspaperCost = 0.0;
    char newspaperChoice;
    int bookingID;

    // Collecting booking ID and days stayed
    printf("Enter main user's booking ID (4 digits): ");
    fflush(stdin);
    scanf("%d", &bookingID);

    printf("Enter how many days you have stayed: ");
    fflush(stdin);
    scanf("%d", &days);

    // Function calls to collect information and calculate costs
    calculateRoomCost(roomNumber, &roomCost, days);
    applyMainUserDiscount(&finalRoomCost, mainUserAge, roomCost);
    getBoardType(&boardType);
    applyChildrenDiscount(boardType, children, days, &boardCostChildren);
    applyAdultMealCost(boardType, days, adults, &boardCostAdult);
    newspaperCostTotal(newspaperChoice, &newspaperCost);

    // Total board cost
    totalBoardCost = boardCostAdult + boardCostChildren;

    // Final bill calculation
    finalBill = finalRoomCost + totalBoardCost + newspaperCost;

    // Displaying the final bill information
    printf("\n-------- Billing Information --------\n");
    printf("+----------------------------------+\n");
    printf("| Booking ID:              %-6d |\n", bookingID);
    printf("| Room Cost:            C%7.2f |\n", finalRoomCost);
    printf("| Adult Meal Cost:      C%7.2f |\n", boardCostAdult);
    printf("| Children Meal Cost:   C%7.2f |\n", boardCostChildren);
    printf("| Newspaper Cost:       C%7.2f |\n", newspaperCost);
    printf("+----------------------------------+\n");
    printf("| Total Final Bill:     C%7.2f |\n", finalBill);
    printf("+----------------------------------+\n");

    return 0;
}