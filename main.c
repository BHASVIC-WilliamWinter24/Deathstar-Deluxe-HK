#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int users[6][6] = {{0, 0, 0, 0, 0, 0}, // Room 1: dateOfBirth, adults, children, boardType, newspaper, lengthOfStay
                  {0, 0, 0, 0, 0, 0},  // Room 2
                  {0, 0, 0, 0, 0, 0},  // Room 3
                  {0, 0, 0, 0, 0, 0},  // Room 4
                  {0, 0, 0, 0, 0, 0},  // Room 5
                  {0, 0, 0, 0, 0, 0}};  // Room 6

char names[6][2][20]; // [roomNumber-1][f/s][max characters]
char IDs[6][23]; // [roomNumber-1][max characters]

// CHECK IN SUBROUTINES //
void checkIn();
// CHECK OUT SUBROUTINES //
void checkOut();
int getBoardType(int *boardType);
void calculateRoomCost(int roomNumber, float *roomCost, int days);
float applyMainUserDiscount(float *finalRoomCost, int mainUserAge, float roomCost);
float applyAdultMealCost(int boardType, int days, int adults, float *boardCostAdult);
float applyChildrenDiscount(int boardType, int children, int days, float *boardCostChildren);
float newspaperCostTotal(char newspaperChoice, float *newspaperCost);
// BOOK TABLE SUBROUTINES //
void bookTable();
void inputId();
int checkValid(char id[23]);
void displayAvailableTables();
int inputTable();
int inputTime();
int updateTables(char id[23], int table, int time);
void displayBookedTables();

int main(void) {
  char choice;
  int loop = 1;
  do {
    printf("Welcome to Hotel Kashyyyk, property of Deathstar Deluxe!\n");
    printf("Would you like to:\nCheck In (1)\nBook a Table (2)\nCheck Out (3)\nQuit (4)\n");
    fflush(stdin);
    scanf("%d", &choice);
    if (choice == 1) {
      checkIn();
    }
    else if (choice == 2) {
      //bookTable();
    }
    else if (choice == 3) {
      checkOut();
    }
    else if (choice == 4) {
      printf("Quitting Program...\n\n\n\n");
    }
    else {
      printf("Please enter 1, 2, 3, or 4\n");
    }
    loop = 1;
  } while (loop == 1); // loop infinitely
  return 0;
}

void checkIn() {
  char firstname[20], surname[20];
  memset(firstname, 0, strlen(firstname)); // sets firstname to empty
  char bookingID[23]; // max length of surname + 6 random digits
  int dateOfBirth, adults, children, boardType, lengthOfStay, newspaper, roomNumber;
  int valid; // for validation checks
  int complete; // to finalise data
  printf("\n\n\n----CHECK IN----\n\n");
  printf("Enter your first name (20 chars cutoff): ");
  fflush(stdin);
  fgets(firstname, 20, stdin); // takes input of max 20 to firstname
  printf("Enter your surname (20 chars cutoff): ");
  fflush(stdin);
  fgets(surname, 20, stdin); // takes input of max 20 to surname
  do { // loop, with condition at the end
    valid = 1; // currently valid
    printf("\nEnter your date of birth in the form DDMMYY: ");
    fflush(stdin);
    scanf("%d", &dateOfBirth); // take input to date of birth variabl
    if (dateOfBirth >= 1000000 || dateOfBirth <= 100000) { // if the length is above or below 6 digits
      printf("Input is not in the form DDMMYY\n");
      valid = 0; // not a valid input
    }
  } while (valid == 0); // loop while invalid
  do {
    valid = 1; // currently valid
    printf("\nEnter number of adults in your room:");
    fflush(stdin);
    scanf("%d", &adults); // take int to adults
    printf("Enter number of children in your room:");
    fflush(stdin);
    scanf("%d", &children); // take int to children
    if (adults < 0 || children < 0 || adults + children > 4 || adults + children <= 0) {
      printf("Invalid data");
      valid = 0; // invalid
    }
    else if (adults == 0) {
      printf("There are no adults in your room.");
      valid = 0; // invalid
    }
  } while (valid == 0); // loop while invalid
  printf("\n\nBoard rates are measured per person, per day.\n Full Board (1) = 20 creds  |  Half Board (2) = 15 creds  |  Bed & Breakfast (3) = 5 creds");
  do {
    valid = 1; // currently valid
    printf("\nEnter number of board type: ");
    fflush(stdin);
    scanf("%d", &boardType); // take input to boardType
    if (boardType != 1 && boardType != 2 && boardType != 3) { // if not one of the three types
      printf("Please input 1, 2, or 3.");
      valid = 0; // invalid
    }
  } while (valid == 0); // loop while invalid
  printf("\nHow long is your stay in days? ");
  fflush(stdin);
  scanf("%d", &lengthOfStay); // take length of stay input
  do {
    valid = 1;
    printf("\nIf you would like a newspaper, enter 1. If not, enter 0.");
    fflush(stdin);
    scanf("%d", &newspaper); // take input to newspaper
    if (newspaper != 0 && newspaper != 1) { // if neither 0 nor 1 entered
      printf("Invalid input. Please enter 0 or 1.");
      valid = 0;
    }
  } while (valid == 0); // loop while invalid
  printf("\n\nAvailable Rooms:");
  for (int i = 0; i < 6; i++) { // iterate through the rooms
    if (users[i][5] == 0) { // if room is empty (no length of stay)
      if (i == 0) { // this if statement shows which rooms are available, and their prices
        printf("\nRoom 1 - 100 creds per day");
      }
      else if (i == 1) {
        printf("\nRoom 2 - 100 creds per day");
      }
      else if (i == 2) {
        printf("\nRoom 3 - 85 creds per day");
      }
      else if (i == 3) {
        printf("\nRoom 4 - 75 creds per day");
      }
      else if (i == 4) {
        printf("\nRoom 5 - 75 creds per day");
      }
      else if (i == 5) {
        printf("\nRoom 6 - 60 creds per day");
      }
    }
  }
  do {
    valid = 1; //currently valid
    printf("\n\nEnter desired room number: ");
    fflush(stdin);
    scanf("%d", &roomNumber); // int input to roomNumber
    if (roomNumber < 1 || roomNumber > 6) { // if input is not 1 to 6
      printf("Not an applicable room.");
      valid = 0; // invalid
    }
    else {
      if (users[roomNumber-1][5] != 0) { // if lengthOfStay for that room is not zero - it is in use
        printf("Room number %d is already in use", roomNumber);
        valid = 0; // invalid
      }
    }
  } while (valid == 0);  // loops while invalid
  printf("\n\n--Check In complete!--\nData is as follows:\n");
  printf("Firstname: %sSurname: %sDate of Birth: %d\nGuests: %d adults & %d child(ren)\n", firstname, surname, dateOfBirth, adults, children);
  if (boardType == 1) { // if board is FB
    printf("Board: Full Board\n");
  }
  else if (boardType == 2) { // if board is HB
    printf("Board: Half Board\n");
  }
  else if (boardType == 3) { // if board is B&B
    printf("Board: Bed & Breakfast\n");
  }
  if (newspaper == 0) { // if no newspaper
    printf("Newspaper: No\n");
  }
  else if (newspaper == 1) { // if newspaper
    printf("Newspaper: Yes\n");
  }
  printf("Staying for %d day(s)\nRoom Number: %d\n\n", roomNumber, lengthOfStay);
  do {
    valid = 1;
    printf("If any details are wrong, please enter 0. If not, enter 1.\n");
    fflush(stdin);
    scanf("%d", &complete); // take int to complete
    if (complete == 0) { // if not complete
      checkIn(); // start again
    }
    else if (complete == 1) { // if complete
      printf("\nExcellent!\n");
    }
    else { // if invalid input
      printf("Invalid input. Please enter 0 or 1");
      valid = 0; // invalid
    }
  } while (valid == 0); // loops while invalid
  // GENERATE BOOKING ID
  srand(time(NULL));
  for (int i = 0; i < strlen(surname); i++) {
    bookingID[i] = surname[i]; // set beginning of bookingID to surname
  }
  for (int i = strlen(surname)-1; i < 23; i++) {
    bookingID[i] = '\000'; // clear all past word itself (including newline)
  }
  printf("\nCheck In Complete!");
  printf("\nCreating Booking ID... Please Wait");
  for (int i = 0; i < 3; i++) { // generate and append three random digits
    sleep(2);
    switch (rand() % 10) {
      case 0:
        bookingID[strlen(surname)-1+i] = '0';
      break;
      case 1:
        bookingID[strlen(surname)-1+i] = '1';
      break;
      case 2:
        bookingID[strlen(surname)-1+i] = '2';
      break;
      case 3:
        bookingID[strlen(surname)-1+i] = '3';
      break;
      case 4:
        bookingID[strlen(surname)-1+i] = '4';
      break;
      case 5:
        bookingID[strlen(surname)-1+i] = '5';
      break;
      case 6:
        bookingID[strlen(surname)-1+i] = '6';
      break;
      case 7:
        bookingID[strlen(surname)-1+i] = '7';
      break;
      case 8:
        bookingID[strlen(surname)-1+i] = '8';
      break;
      case 9:
        bookingID[strlen(surname)-1+i] = '9';
      break;
      default:
        exit(1); // Exit Code 1 if random num from 0-9 not generated
    }
    printf("."); // to output loading string
  }
  printf("\nLoading Complete!\n Booking ID is: ");
  for (int i = 0; i < strlen(bookingID); i++) { // print booking ID
    printf("%c", bookingID[i]);
  }
  users[roomNumber-1][0] = dateOfBirth;
  users[roomNumber-1][1] = adults;
  users[roomNumber-1][2] = children;
  users[roomNumber-1][3] = boardType;
  users[roomNumber-1][4] = newspaper;
  users[roomNumber-1][5] = lengthOfStay;
  for (int i = 0; i < 20; i++) {
    names[roomNumber-1][0][i] = firstname[i];
    names[roomNumber-1][1][i] = surname[i];
  }
  for (int i = 0; i < 23; i++) {
    IDs[roomNumber-1][i] = bookingID[i];
  }
}

// CHECK OUT //

void checkOut() {
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
}

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
void calculateRoomCost(int roomNumber, float *roomCost, int days) {
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

// BOOK TABLE //

void bookTable() {
  int valid=0;
  int table=0;
  int time=0;
  int choice=0;
  // this loop repeats the code, allowing the next user to book a table

  printf("Would you like to view bookings(0), book a table(1) or quit (2) \n");
  fflush(stdin);
  scanf("%d",&choice);
  if(choice==2) {
    exit(0);
  }
  if (choice==0) {
    displayBookedTables();
  }
  if(choice==1) {
    inputId();
    //this loop checks if the selected table is already booked based on the value returned by updateTables() function
    do {
      displayAvailableTables();
      table=inputTable();
      time=inputTime();
      valid=updateTables(id,table,time);
    }while(valid!=1);
  }
}

// returns 0 if the entered id does not exist, 1 if it is a user with breakfast board, and 2 if it is a user with a different board
void checkValid(char id[23]) {
  //checks if the entered id exists within the system
  for(int i=0;i<6;i++) {
    if (strcmp(id,IDs[i])==0){
      // checks the board of the user
      if(user[i][3]==2) {
        return 1;
      }
      return 2;
    }
  }
}