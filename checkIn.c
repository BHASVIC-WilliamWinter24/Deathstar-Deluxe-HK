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

void checkIn();

int main(void) {
  checkIn();
  return 0;
}

void checkIn() {
  char firstname[20], surname[20];
  memset(firstname, 0, strlen(firstname)); // sets firstname to empty
  char bookingID[23]; // max length of surname + 6 random digits
  int dateOfBirth, adults, children, boardType, lengthOfStay, newspaper, roomNumber;
  int valid; // for validation checks
  int complete; // to finalise data
  printf("----CHECK IN----\n\n");
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
  printf("User: %s %sDate of Birth: %d\nGuests: %d adults & %d child(ren)\n", firstname, surname, dateOfBirth, adults, children);
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
  printf("Staying for %d day(s)\n\n", lengthOfStay);
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