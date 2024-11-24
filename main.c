#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int user[6][6] = {{0, 0, 0, 0, 0, 0}, // Room 1: dateOfBirth, adults, children, boardType, newspaper, lengthOfStay
                  {0, 0, 0, 0, 0, 0},  // Room 2
                  {0, 0, 0, 0, 0, 0},  // Room 3
                  {0, 0, 0, 0, 0, 0},  // Room 4
                  {0, 0, 0, 0, 0, 0},  // Room 5
                  {0, 0, 0, 0, 0, 0}};  // Room 6

char names[6][2][20]; // [roomNumber-1][f/s][max characters]
char IDs[6][23]; // [roomNumber-1][max characters]

char bookedTables[3][2][24]; // for bookTable
char id[23]; // for bookTable

// CHECK IN SUBROUTINES //
void checkIn();
// CHECK OUT SUBROUTINES //
void checkOut();
void calculateRoomCost(int roomNumber, float *roomCost, int days);
float applyMainUserDiscount(float *finalRoomCost, int mainUserAge, float roomCost);
float applyAdultMealCost(int boardType, int days, int adults, float *boardCostAdult);
float applyChildrenDiscount(int boardType, int children, int days, float *boardCostChildren);
float newspaperCostTotal(char newspaperChoice, float *newspaperCost);
// BOOK TABLE SUBROUTINES //
int bookTable();
int inputId();
int checkValid(char id[23]);
void displayAvailableTables();
int inputTable();
int inputTime();
int updateTables(char id[23], int table, int time);
void displayBookedTables();

int main(void) {
  char choice;
  int loop;
  do {
    printf("Welcome to Hotel Kashyyyk, property of Deathstar Deluxe!\n");
    printf("Would you like to:\nCheck In (1)\nBook a Table (2)\nCheck Out (3)\nQuit (4)\n");
    fflush(stdin);
    scanf("%d", &choice);
    if (choice == 1) {
      checkIn();
    }
    else if (choice == 2) {
      bookTable();
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
}

// CHECK IN //

void checkIn() {
  char firstname[20], surname[20];
  memset(firstname, 0, strlen(firstname)); // sets firstname to empty
  char bookingID[23]; // max length of surname + 6 random digits
  int dateOfBirth, adults, children, boardType, days, newspaperChoice, roomNumber;
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
    scanf("%d", &dateOfBirth); // take input to date of birth variable
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
  scanf("%d", &days); // take length of stay input
  do {
    valid = 1;
    printf("\nIf you would like a newspaper, enter 1. If not, enter 0.");
    fflush(stdin);
    scanf("%d", &newspaperChoice); // take input to newspaper
    if (newspaperChoice != 0 && newspaperChoice != 1) { // if neither 0 nor 1 entered
      printf("Invalid input. Please enter 0 or 1.");
      valid = 0;
    }
  } while (valid == 0); // loop while invalid
  printf("\n\nAvailable Rooms:");
  for (int i = 0; i < 6; i++) { // iterate through the rooms
    if (user[i][5] == 0) { // if room is empty (no length of stay)
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
      if (user[roomNumber-1][5] != 0) { // if days for that room is not zero - it is in use
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
  if (newspaperChoice == 0) { // if no newspaper
    printf("Newspaper: No\n");
  }
  else if (newspaperChoice == 1) { // if newspaper
    printf("Newspaper: Yes\n");
  }
  printf("Staying for %d day(s)\nRoom Number: %d\n\n", days, roomNumber);
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
  user[roomNumber-1][0] = dateOfBirth;
  user[roomNumber-1][1] = adults;
  user[roomNumber-1][2] = children;
  user[roomNumber-1][3] = boardType;
  user[roomNumber-1][4] = newspaperChoice;
  user[roomNumber-1][5] = days;
  for (int i = 0; i < 20; i++) {
    names[roomNumber-1][0][i] = firstname[i];
    names[roomNumber-1][1][i] = surname[i];
  }
  for (int i = 0; i < 23; i++) {
    IDs[roomNumber-1][i] = bookingID[i];
  }
  printf("\n\n");
}

// CHECK OUT //

void checkOut() {
  int roomNumber, mainUserAge, children, days, adults, boardType;
  float roomCost, finalRoomCost, boardCostAdult, totalBoardCost, boardCostChildren = 0, finalBill, newspaperCost = 0.0;
  char newspaperChoice;
  char bookingID[23];
  int valid; // for validation checks


  // Collecting booking ID and days stayed
  do {
    valid = 0;
    printf("Enter main user's booking ID: ");
    fflush(stdin);
    scanf("%s[22]", &bookingID);
    for(int i=0; i<6; i++) {
      if (strcmp(bookingID,IDs[i])==0) {
        roomNumber = i+1;
        printf("Valid ID entered\n");
        valid = 1;
      }
    }
    if (valid == 0) {
      printf("Invalid ID entered.\n");
    }
  } while (valid == 0);

  roomNumber = 1;

  // declare variables
  days = user[roomNumber-1][5];
  children = user[roomNumber-1][2];
  adults = user[roomNumber-1][1];
  boardType = user[roomNumber-1][3];
  newspaperChoice = user[roomNumber-1][4];

  // Function calls to collect information and calculate costs
  calculateRoomCost(roomNumber, &roomCost, days);
  applyMainUserDiscount(&finalRoomCost, mainUserAge, roomCost);
  applyChildrenDiscount(boardType, children, days, &boardCostChildren);
  applyAdultMealCost(boardType, days, adults, &boardCostAdult);
  newspaperCostTotal(newspaperChoice, &newspaperCost);

  // Total board cost
  totalBoardCost = boardCostAdult + boardCostChildren;

  // Final bill calculation
  finalBill = finalRoomCost + totalBoardCost + newspaperCost;

  // Displaying the final bill information
  printf("\n-------- Billing Information --------\n");
  printf("+------------------------------------+\n");
  printf("| Booking ID:%23s |\n", bookingID);
  printf("| Room Cost:            C%11.2f |\n", finalRoomCost);
  printf("| Adult Meal Cost:      C%11.2f |\n", boardCostAdult);
  printf("| Children Meal Cost:   C%11.2f |\n", boardCostChildren);
  printf("| Newspaper Cost:       C%11.2f |\n", newspaperCost);
  printf("+------------------------------------+\n");
  printf("| Total Final Bill:     C%11.2f |\n", finalBill);
  printf("+------------------------------------+\n");
  printf("Hope you had a good stay here at Hotel Kashyyyk!\nCome back soon!!!\n\n\n");

  // removes data for checked out user
  for (int i = 0; i < 6; i++) {
    user[roomNumber-1][i] = 0; // user int array
  }
  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < 20; k++) {
      names[roomNumber-1][j][k] = '\000'; // names array
    }
  }
  for (int l = 0; l < 23; l++) {
    IDs[roomNumber-1][l];
  }

}

// Function to calculate the room cost based on room number
void calculateRoomCost(int roomNumber, float *roomCost, int days) {
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
    printf("\nEnter the main user's age (must be at least 18): ");
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
  printf("\nYou have %d adult guests.\n", adults);

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
  if (children > 0) {
    printf("\nYou are eligible for a 50%% discount on each of your children's meal board cost.\n");

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
  if (newspaperChoice == 0) {
    *newspaperCost = 0.00;
  }
  else if (newspaperChoice == 1) {
    *newspaperCost = 5.50;
  }
  return *newspaperCost;
}

// BOOK TABLE //

int bookTable() {
  int valid=0;
  int table=0;
  int time=0;
  int choice=0;
  // this loop repeats the code, allowing the next user to book a table

  printf("Would you like to view bookings(0), book a table(1) or quit (2) \n");
  fflush(stdin);
  scanf("%d",&choice);
  if(choice==2) {
    return 0;
  }
  if (choice==0) {
    displayBookedTables();
  }
  if(choice==1) {
    if (inputId() == -1) {
      return 0;
    }
    //this loop checks if the selected table is already booked based on the value returned by updateTables() function
    do {
      displayAvailableTables();
      table=inputTable();
      time=inputTime();
      valid=updateTables(id,table,time);
    }while(valid!=1);
  }
  return 0;
}

// returns 0 if the entered id does not exist, 1 if it is a user with breakfast board, and 2 if it is a user with a different board
int checkValid(char id[23]) {
  //checks if the entered id exists within the system
  for(int i=0;i<6;i++) {
    if (strcmp(id,IDs[i])==0){
      // checks the board of the user
      if(user[i][3]==3) {
        return 1; // if B&B, return 1
      }
      return 2; // if valid, but any other board
    }
  }
  return 0; // if invalid ID
}

//displays the tables and times that are available to book
void displayAvailableTables() {
  int availableTables=0;
  printf("Available tables: \n");
  for(int i=0;i<3;i++) {
    for(int j=0;j<2;j++) {
      if(bookedTables[i][j][0]==0){
        availableTables++;
        switch(i) {
          case 0:printf("Endor at ");
          break;
          case 1:printf("Naboo at ");
          break;
          case 2:printf("Tatooine at ");
          break;
          default:continue;

        }
        switch(j) {
          case 0:printf("7 pm");
          break;
          case 1:printf("9 pm");
          break;
          default:continue;
        }
        printf("\n");
      }
    }
  }
  if(availableTables==0) {
    printf("No available tables found \n");
  }
}

//prompts the user to enter a valid table
int inputTable() {
  int table=0;
  char tableInput[9];
  do {

    printf("Which table would you like to book? endor(1), naboo(2) or tatooine(3) \n");
    fflush(stdin);
    scanf("%8s",&tableInput);
    for(int i=0;i<8;i++) {
      tableInput[i]=tolower(tableInput[i]);
    }
    if (strncmp(tableInput,"endor",5)==0) {
      table=1;
    }
    if (strncmp(tableInput,"naboo",5)==0) {
      table=2;
    }
    if (strncmp(tableInput,"tatooine",8)==0) {
      table=3;
    }
    if(atoi(tableInput)==1 || atoi(tableInput)==2 || atoi(tableInput)==3) {
      table=atoi(tableInput);
    }
    switch(table) {
      case 0:printf("Invalid input, please try again \n");
      break;
      case 1:printf("Endor selected \n");
      break;
      case 2:printf("Naboo selected \n");
      break;
      case 3:printf("Tatooine selected \n");
      break;
      default:continue;
    }
  }
  while(table==0);
  return table;
}

//prompts the user to enter a valid time
int inputTime() {
  int timeInput=0;
  do {
    printf("Which time would you like to book? \n 1: 7pm \n 2: 9pm \n");
    fflush(stdin);
    scanf("%d",&timeInput);
    if(timeInput!=1 && timeInput!=2) {
      printf("Invalid input, please try again \n");
    }
  }while(timeInput!=1 && timeInput!=2);
  return timeInput;
}

//prompts the user for a booking id which exists in the system, and has breakfast board
int inputId() {
  char idInput[23];
  int valid=0;
  printf("Please enter booking id or enter QUIT to quit: \n");
  do {
    fflush(stdin);
    scanf("%s[22]", &idInput);
    if(idInput==0) {
      valid=0;
    }
    if(strcmp(idInput,"QUIT")==0) {
      return -1;
    }
    else {
      valid = checkValid(idInput);
    }
    if(valid==0) {
      printf("Booking id not found, please try again \n");
    }
    if(valid==1) {
      printf("User must not have breakfast board, please try again \n");
    }
  } while(valid!=2);
  for(int i=0;i<22;i++) {
    id[i]=idInput[i];
  }
  return 0;
}

//updates the list of booked tables with the entered information
int updateTables(char id[23],int table,int time) {
  if (bookedTables[table-1][time-1][0]==1) {
    printf("Table already booked, please enter an available table \n");
    return 0;
  }
  bookedTables[table-1][time-1][0]=1;
  for(int i=0;i<23;i++)
  {
    bookedTables[table-1][time-1][i+1]=id[i];
  }
  printf("Table successfully booked \n\n\n\n");
  return 1;
}

//shows which tables have been booked, and the matching booking id
void displayBookedTables() {
  int numberBooked=0;
  for(int i=0;i<3;i++) {
    for(int j=0;j<2;j++) {
      if(bookedTables[i][j]!=0) {
        numberBooked++;
        switch(i) {
          case 0:printf("Endor at ");
          break;
          case 1:printf("Naboo at ");
          break;
          case 2:printf("Tatooine at ");
          break;
          default:continue;
        }
        switch(j) {
          case 0:printf("7 pm");
          break;
          case 1:printf("9 pm");
          break;
          default:continue;
        }
        printf(":booking id ");
        for(int k=1;bookedTables[i][j][k];k++)
        {
          printf("%c",bookedTables[i][j][k]);
        }
        printf("\n");
      }
    }
  }
  if(numberBooked==0) {
    printf("All tables available \n");
  }
}