#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 10

// Structure to represent a user and password
typedef struct {
    char username[20];
    char password[20];
    float wallet;
} User;

// Structure to represent a movie ticket 
typedef struct {
    char movieName[50];
    int numSeats;
    float pricePerSeat;
} Ticket;

// Function to authenticate users
bool authenticate(User *users, int numUsers, char *username, char *password) {
    int i;
    for (i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

// Function to book a ticket
void bookTicket(Ticket *tickets, int numTickets, User *currentUser) {
    char movie[50];
    int seats;
    printf("Enter movie name: ");
    scanf("%s", movie);
    
    int i;
    for (i = 0; i < numTickets; ++i) {
        if (strcmp(tickets[i].movieName, movie) == 0) {
            printf("Enter number of seats: ");
            scanf("%d", &seats);
            if (tickets[i].numSeats >= seats) {
                float totalCost = seats * tickets[i].pricePerSeat;
                if (currentUser->wallet >= totalCost) {
                    printf("Total cost: $%.2f\n", totalCost);
                    tickets[i].numSeats -= seats;
                    currentUser->wallet -= totalCost;
                    printf("Tickets booked successfully!\n");
                } else {
                    printf("Not enough balance in wallet.\n");
                }
                return;
            } else {
                printf("Not enough seats available.\n");
                return;
            }
        }
    }
    printf("Movie not found.\n");
}

// Function to display available tickets

void displayTickets(Ticket *tickets, int numTickets) {
    printf("Available tickets:\n");
    printf("Movie Name\t\tSeats Available\t\tPrice per Seat\n");
    int i;
    for (i = 0; i < numTickets; ++i) {
        printf("%-20s\t\t%d\t\t\t$%.2f\n", tickets[i].movieName, tickets[i].numSeats, tickets[i].pricePerSeat);
    }
}

int main() {
    User users[MAX_USERS] = {
        {"user1", "password1", 100.0},
        {"user2", "password2", 200.0}
        // Add more users here
    };
    int numUsers = 2; // Number of users in the system

    Ticket tickets[] = {
        {"Avengers: Endgame", 100, 10.0},
        {"Joker", 50, 8.0},
        {"The Shawshank Redemption", 70, 7.5}
    };
    int numTickets = sizeof(tickets) / sizeof(tickets[0]);

    char username[20];
    char password[20];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    User *currentUser = NULL;
    int i;
    for (i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            currentUser = &users[i];
            break;
        }
    }

    if (currentUser != NULL) {
        printf("Authentication successful.\n");

        int choice;
        do {
            printf("\nCinema Ticket Booking System\n");
            printf("1. Book Ticket\n");
            printf("2. Display Available Tickets\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    bookTicket(tickets, numTickets, currentUser);
                    break;
                case 2:
                    displayTickets(tickets, numTickets);
                    break;
                case 3:
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 3);
    } else {
        printf("Authentication failed. Invalid username or password.\n");
    }

    return 0;
}

// Any mistake by me ? then you can contact me on X
