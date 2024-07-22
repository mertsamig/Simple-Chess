#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Function prototypes
void display();
void change(int, int, int, int);
void pawn(int, int, int);
void rook(int, int, int);
void horse(int, int, int);
void camel(int, int, int);
void king(int, int, int);
void queen(int, int, int);
void playerTurn(int);
int checkValidMove(int, int, int);
int possibleMoves[9999];
int moveCount = 0;

// Chessboard representation
char board[8][8] = {{'r', 'h', 'c', 'k', 'q', 'c', 'h', 'r'},
                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                    {'R', 'H', 'C', 'K', 'Q', 'C', 'H', 'R'}};

int main() {
  int turn = 1; // Player 1's turn
  char ch;
  do {
    system("cls"); // Clear the console
    display();

    playerTurn(turn);

    printf("\n\nPress enter to continue\n\n");
    ch = getch();
    turn = (turn % 2) + 1; // Switch to the other player
  } while (ch == 13);
  return 0;
}

// Function to check if a move is valid
int checkValidMove(int r1, int c1, int pos) {
  int r2 = pos / 10;
  int c2 = pos % 10;

  // Check if the destination is within the board boundaries
  if (r2 < 0 || r2 > 7 || c2 < 0 || c2 > 7) return 0;

  // Check for valid movement
  if (board[r2][c2] == ' ' || board[r1][c1] == board[r2][c2]) return 1;

  // Check if the destination cell contains an enemy piece
  if ((board[r1][c1] >= 'A' && board[r2][c2] >= 'a' && board[r2][c2] <= 'z') ||
      (board[r1][c1] >= 'a' && board[r2][c2] >= 'A' && board[r2][c2] <= 'Z')) {
    return 1;
  }

  return 0;
}

// Function to display the chessboard
void display() {
  int i, j, k;
  printf("\nChess Board (t=%d)\n\n", moveCount);
  printf(" ");
  for (i = 0; i < 8; i++) printf("    %d", i);
  printf("\n");
  for (k = 0; k < 8; k++) {
    printf("  ");
    printf("\n");
    printf("%d ", k);
    for (j = 0; j < 8; j++) {
      printf("   %c", board[k][j]);
    }
    printf("   \n");
  }
  printf("  ");
  printf("\n");
}

// Function to move a piece
void change(int r1, int c1, int r2, int c2) {
  char temp = board[r1][c1];
  board[r1][c1] = ' ';
  board[r2][c2] = temp;

  printf("\nMove: %d %c -> %d %c\n", (r1 * 10) + c1, board[r2][c2], (r2 * 10) + c2, board[r2][c2]);

  if (board[r2][c2] >= 'a' && board[r2][c2] <= 'z')
    printf("Elimination: %d %c\n", (r2 * 10) + c2, board[r2][c2]);
}

// Function for pawn movements
void pawn(int r1, int c1, int isWhite) {
  int i, j, direction = isWhite ? -1 : 1;
  if ((r1 + direction) >= 0 && (r1 + direction) < 8) {
    // Move one step forward
    if (board[r1 + direction][c1] == ' ') {
      possibleMoves[moveCount++] = ((r1 + direction) * 10) + c1;
    }

    // Move two steps forward if starting position
    if ((r1 == 1 && !isWhite) || (r1 == 6 && isWhite)) {
      if (board[r1 + direction][c1] == ' ' &&
          board[r1 + 2 * direction][c1] == ' ') {
        possibleMoves[moveCount++] = ((r1 + 2 * direction) * 10) + c1;
      }
    }
    // Attack diagonal movements
    for (j = -1; j <= 1; j += 2) {
      if ((c1 + j) >= 0 && (c1 + j) < 8 &&
          checkValidMove(r1, c1, ((r1 + direction) * 10) + (c1 + j))) {
        possibleMoves[moveCount++] = ((r1 + direction) * 10) + (c1 + j);
      }
    }
  }
}

// Function for rook movements
void rook(int r1, int c1, int isWhite) {
  int i;
  // Move right
  for (i = c1 + 1; i < 8; i++) {
    if (checkValidMove(r1, c1, (r1 * 10) + i))
      possibleMoves[moveCount++] = (r1 * 10) + i;
    else break;
  }
  // Move left
  for (i = c1 - 1; i >= 0; i--) {
    if (checkValidMove(r1, c1, (r1 * 10) + i))
      possibleMoves[moveCount++] = (r1 * 10) + i;
    else break;
  }
  // Move down
  for (i = r1 + 1; i < 8; i++) {
    if (checkValidMove(r1, c1, (i * 10) + c1))
      possibleMoves[moveCount++] = (i * 10) + c1;
    else break;
  }
  // Move up
  for (i = r1 - 1; i >= 0; i--) {
    if (checkValidMove(r1, c1, (i * 10) + c1))
      possibleMoves[moveCount++] = (i * 10) + c1;
    else break;
  }
}

// Function for horse movements
void horse(int r1, int c1, int isWhite) {
  int i, j;
  // Move in L-shape pattern
  for (i = -2; i <= 2; i += 4) {
    for (j = -1; j <= 1; j += 2) {
      if ((r1 + i) >= 0 && (r1 + i) < 8 && (c1 + j) >= 0 && (c1 + j) < 8 &&
          checkValidMove(r1, c1, ((r1 + i) * 10) + (c1 + j))) {
        possibleMoves[moveCount++] = ((r1 + i) * 10) + (c1 + j);
      }
    }
  }
  for (i = -1; i <= 1; i += 2) {
    for (j = -2; j <= 2; j += 4) {
      if ((r1 + i) >= 0 && (r1 + i) < 8 && (c1 + j) >= 0 && (c1 + j) < 8 &&
          checkValidMove(r1, c1, ((r1 + i) * 10) + (c1 + j))) {
        possibleMoves[moveCount++] = ((r1 + i) * 10) + (c1 + j);
      }
    }
  }
}

// Function for camel movements
void camel(int r1, int c1, int isWhite) {
  int i, j;
  for (i = 1; i < 8; i++) {
    // Move diagonally down-right
    if (checkValidMove(r1, c1, ((r1 + i) * 10) + (c1 + i))) {
      possibleMoves[moveCount++] = ((r1 + i) * 10) + (c1 + i);
    } else break;
  }
  for (i = 1; i < 8; i++) {
    // Move diagonally up-left
    if (checkValidMove(r1, c1, ((r1 - i) * 10) + (c1 - i))) {
      possibleMoves[moveCount++] = ((r1 - i) * 10) + (c1 - i);
    } else break;
  }
  for (i = 1; i < 8; i++) {
    // Move diagonally down-left
    if (checkValidMove(r1, c1, ((r1 + i) * 10) + (c1 - i))) {
      possibleMoves[moveCount++] = ((r1 + i) * 10) + (c1 - i);
    } else break;
  }
  for (i = 1; i < 8; i++) {
    // Move diagonally up-right
    if (checkValidMove(r1, c1, ((r1 - i) * 10) + (c1 + i))) {
      possibleMoves[moveCount++] = ((r1 - i) * 10) + (c1 + i);
    } else break;
  }
}

// Function for king movements
void king(int r1, int c1, int isWhite) {
  int i, j;
  // Move one step in all directions
  for (i = -1; i <= 1; i++) {
    for (j = -1; j <= 1; j++) {
      if (i != 0 || j != 0) { // Skip current position
        if (checkValidMove(r1, c1, ((r1 + i) * 10) + (c1 + j))) {
          possibleMoves[moveCount++] = ((r1 + i) * 10) + (c1 + j);
        }
      }
    }
  }
}

// Function for queen movements
void queen(int r1, int c1, int isWhite) {
  // Combine the movements of rook and camel
  rook(r1, c1, isWhite);
  camel(r1, c1, isWhite);
}

// Function to handle player's turn
void playerTurn(int turn) {
  int p1, p2, c1, r1, c2, r2, z = 1, isWhite = turn == 1;

  char playerLabel = isWhite ? 'W' : 'B';
  printf("\nPlayer %d (%c)\n", turn, playerLabel);

again1:
  printf("\nSelect a piece (RC): ");
  scanf("%d", &p1);

  if (p1 > 77) {
    printf("Incorrect piece selection. Try again.\n");
    goto again1;
  }

  c1 = p1 % 10;
  r1 = p1 / 10;

  // Calculate possible moves based on piece type
  moveCount = 0; // Reset the move counter
  switch (board[r1][c1]) {
    case 'p':
      pawn(r1, c1, isWhite);
      break;
    case 'r':
      rook(r1, c1, isWhite);
      break;
    case 'h':
      horse(r1, c1, isWhite);
      break;
    case 'c':
      camel(r1, c1, isWhite);
      break;
    case 'k':
      king(r1, c1, isWhite);
      break;
    case 'q':
      queen(r1, c1, isWhite);
      break;
    default:
      printf("Incorrect piece selection! Try again.\n");
      goto again1;
  }

  if (moveCount == 0) {
    printf("\nSelected piece has no valid moves! Try again.\n");
    goto again1;
  }

  printf("\nAvailable positions are:\n");
  for (z = 0; z < moveCount; z++) {
    if (checkValidMove(r1, c1, possibleMoves[z])) {
      printf("\nEnter %d for position %d*\n", z, possibleMoves[z]);
    } else {
      printf("\nEnter %d for position %d\n", z, possibleMoves[z]);
    }
  }
again3:
  printf("\nEnter a position you want to move the piece to (RC): ");
  scanf("%d", &p2);

  if (p2 < 0 || p2 >= moveCount) {
    printf("Please enter a valid move number.\n");
    goto again3;
  }

  // Perform the move
  r2 = possibleMoves[p2] / 10;
  c2 = possibleMoves[p2] % 10;
  change(r1, c1, r2, c2);

  // Update the game turn
  moveCount = 0;
}
