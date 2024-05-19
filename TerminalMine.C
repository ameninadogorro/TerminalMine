#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define MINES 5

char board[ROWS][COLS];
char hidden_board[ROWS][COLS];

void initialize_board() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = '-';
            hidden_board[i][j] = '-';
        }
    }
}

void print_board() {
    int i, j;
    printf("  ");
    for (i = 0; i < COLS; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < ROWS; i++) {
        printf("%d ", i);
        for (j = 0; j < COLS; j++) {
            printf("%c ", hidden_board[i][j]);
        }
        printf("\n");
    }
}

void place_mines() {
    srand(time(NULL));
    int i, j;
    for (i = 0; i < MINES; i++) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (hidden_board[row][col] == '*') {
            i--;
        } else {
            hidden_board[row][col] = '*';
        }
    }
}

int count_adjacent_mines(int row, int col) {
    int count = 0;
    int i, j;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (row+i >= 0 && row+i < ROWS && col+j >= 0 && col+j < COLS) {
                if (hidden_board[row+i][col+j] == '*') {
                    count++;
                }
            }
        }
    }
    return count;
}

void reveal(int row, int col) {
    if (hidden_board[row][col] == '*') {
        printf("Game Over! You hit a mine!\n");
        exit(0);
    } else {
        int adj_mines = count_adjacent_mines(row, col);
        hidden_board[row][col] = adj_mines + '0';
        if (adj_mines == 0) {
            int i, j;
            for (i = -1; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                    if (row+i >= 0 && row+i < ROWS && col+j >= 0 && col+j < COLS) {
                        if (hidden_board[row+i][col+j] == '-') {
                            reveal(row+i, col+j);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    initialize_board();
    place_mines();
    int row, col;
    while (1) {
        print_board();
        printf("Enter row and column (separated by space): ");
        scanf("%d %d", &row, &col);
        reveal(row, col);
    }
    return 0;
}
