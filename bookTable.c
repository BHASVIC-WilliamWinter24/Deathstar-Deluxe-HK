#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int user[6][6]={};
char bookedTables[3][2][24];
char IDs[6][23];
char id[23];

void inputId();
int checkValid(char id[23]);
void displayAvailableTables();
int inputTable();
int inputTime();
int updateTables(char id[23], int table, int time);
void displayBookedTables();

int main(void)
{
    //example user data added for testing
    scanf("%22s",&IDs[0]);

    user[0][3]=2;
    user[1][3]=0;
    user[2][3]=1;
    user[3][3]=2;

    int valid=0;
    int table=0;
    int time=0;
    int choice=0;
    // this loop repeats the code, allowing the next user to book a table
    do {
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
    }while(choice!=2);
return 0;
}

// returns 0 if the entered id does not exist, 1 if it is a user with breakfast board, and 2 if it is a user with a different board
int checkValid(char id[23]) {
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
    return 0;
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
void inputId() {
    char idInput[23];
    int valid=0;
    printf("Please enter booking id: \n");
    do {
        fflush(stdin);
        scanf("%s[22]", &idInput);
        if(idInput==0) {
            valid=0;
        }
        else {
            valid=checkValid(idInput);
        }
        if(valid==0) {
            printf("Booking id not found, please try again \n");
        }
        if(valid==2) {
            printf("User must have breakfast board, please try again \n");
        }
    }
    while(valid!=1);
    for(int i=0;i<22;i++)
    {
        id[i]=idInput[i];
    }

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