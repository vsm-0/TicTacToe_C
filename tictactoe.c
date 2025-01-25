#include <stdio.h>
#include <ctype.h> // For tolower()

char board[3][3];

// Function to print the board
void printboard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
}

// Function to get markers for the players
void getmarkers(char *m1, char *m2) {
    char marker1;
    while (1) {
        printf("Player 1 choice (X or O): ");
        scanf(" %c", &marker1); // Space before %c skips whitespace
        marker1 = tolower(marker1); // Convert input to lowercase

        if (marker1 == 'x') {
            *m1 = 'X';
            *m2 = 'O';
            break;
        } else if (marker1 == 'o') {
            *m1 = 'O';
            *m2 = 'X';
            break;
        } else {
            printf("Invalid input. Please choose X or O.\n");
        }
    }
}

// Function to get coordinates for a move
int getcoordinates(int *x, int *y) {
    printf("Enter the coordinates (row and column, 0-2): ");
    if (scanf("%d %d", x, y) != 2) {
        printf("Invalid input format. Try again.\n");
        while (getchar() != '\n'); // Clear input buffer
        return 0;
    }
    if (*x >= 0 && *x < 3 && *y >= 0 && *y < 3) {
        return 1;
    } else {
        printf("Invalid Input. Coordinates must be between 0 and 2.\n");
        return 0;
    }
}

// Function to check for a win
int checkforwin() {
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
        // Check columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return 1;
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }
    return 0;
}

// Function to update the board
int updateboard(int chance, char marker, int x, int y) {
    if (board[x][y] == ' ') {
        board[x][y] = marker;
        if (checkforwin()) {
            if (chance) {
                printf("Player 1 wins!\n");
            } else {
                printf("Player 2 wins!\n");
            }
            return 0; // Game over
        }
        return 1; // Valid move, continue game
    } else {
        printf("Invalid Move... Cell already occupied. Try Again.\n");
        return 1; // Invalid move
    }
}

// Main game logic
void playgame() {
    char m1, m2;
    getmarkers(&m1, &m2);
    printf("Player 1: %c, Player 2: %c\n", m1, m2);

    // Initialize the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    int chance = 1; // Player 1 starts
    while (1) {
        printboard();
        int x, y, valid = 0;

        while (!valid) {
            valid = getcoordinates(&x, &y);
        }

        if (chance) {
            if (!updateboard(chance, m1, x, y)) {
                break; // Player 1 wins
            }
        } else {
            if (!updateboard(chance, m2, x, y)) {
                break; // Player 2 wins
            }
        }

        chance = !chance; // Switch turns
    }

    printboard();
}

int main() {
    playgame();
    return 0;
}
