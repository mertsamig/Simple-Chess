#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void display();
void change(int, int, int, int);
void pawnb(int, int);
void pawnw(int, int);
void rookb(int, int);
void rookw(int, int);
void horseb(int, int);
void horsew(int, int);
void camelb(int, int);
void camelw(int, int);
void kingb(int, int);
void kingw(int, int);
void queenb(int, int);
void queenw(int, int);
void white();
void black();
int checkforw(int, int);
int checkforb(int, int);

int pwmoves[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int pbmoves[8] = {0, 0, 0, 0, 0, 0, 0, 0};

char board[8][8] = {{'R', 'H', 'C', 'K', 'Q', 'C', 'H', 'R'},
                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                    {'r', 'h', 'c', 'k', 'q', 'c', 'h', 'r'}};

main() {
  int x = 0;
  char ch;
  do {
    x++;
    system("cls");
    display();
    if ((x % 2) == 0) {
      black();
    } else {
      white();
    }
    printf(" \n\nPress Enter To Continue ! \n\n ");
    ch = getch();
  } while (ch == 13);
}

void display() {
  int i, j, k;
  printf(" ");
  for (i = 0; i < 8; i++) printf("    %d", i);
  printf("\n");
  for (k = 0; k < 8; k++) {
    printf("  ");
    for (i = 0; i < 42; i++) {
      printf("-");
    }
    printf("\n");
    printf("%d ", k);
    for (j = 0; j < 8; j++) {
      printf("|| %c ", board[k][j]);
    }
    printf("|| \n");
  }
  printf("  ");
  for (i = 0; i < 42; i++) {
    printf("-");
  }
  printf("\n");
}

void change(int r1, int c1, int r2, int c2) {
  char temp;
  if (board[r2][c2] != ' ') {
    temp = board[r1][c1];
    board[r1][c1] = ' ';
    board[r2][c2] = temp;
  }
  if (board[r2][c2] == ' ') {
    temp = board[r1][c1];
    board[r1][c1] = board[r2][c2];
    board[r2][c2] = temp;
  }
}

int checkforw(int x, int y) {
  switch (board[x][y]) {
    case 'p':
    case 'r':
    case 'h':
    case 'c':
    case 'k':
    case 'q':
      return 1;
      break;
    default:
      return 0;
  }
}

int checkforb(int x, int y) {
  switch (board[x][y]) {
    case 'P':
    case 'R':
    case 'H':
    case 'C':
    case 'K':
    case 'Q':
      return 1;
      break;
    default:
      return 0;
  }
}
void pawnb(int r1, int c1) {
  pbmoves[c1]++;
  printf("Available are: \n");
  if (pbmoves[c1] == 1) {
    if (board[r1 - 1][c1] == ' ') printf("%d%d , ", r1 - 1, c1);
    if (board[r1 - 2][c1] == ' ') printf("%d%d , ", r1 - 2, c1);
  } else {
    if (board[r1 - 1][c1] == ' ') printf("%d%d , ", r1 - 1, c1);
    if (checkforb(r1 - 1, c1 - 1) == 1) printf("%d%d! , ", r1 - 1, c1 - 1);
    if (checkforb(r1 - 1, c1 + 1) == 1) printf("%d%d! , ", r1 - 1, c1 + 1);
  }
}

void pawnw(int r1, int c1) {
  pwmoves[c1]++;
  printf("Available are: \n");
  if (pwmoves[c1] == 1) {
    if (board[r1 + 1][c1] == ' ') printf("%d%d , ", r1 + 1, c1);
    if (board[r1 + 2][c1] == ' ') printf("%d%d , ", r1 + 2, c1);
  } else {
    if (board[r1 + 1][c1] == ' ') printf("%d%d , ", r1 + 1, c1);
    if (checkforw(r1 + 1, c1 + 1) == 1) printf("%d%d! , ", r1 + 1, c1 + 1);
    if (checkforw(r1 + 1, c1 - 1) == 1) printf("%d%d! , ", r1 + 1, c1 - 1);
  }
}

void rookb(int r1, int c1) {
  int i, j, n;
  printf("Available are: \n");
  n = c1;
  printf("Horizontally: \n");
  while (board[r1][n - 1] == ' ') {
    if (n == 0) {
      break;
    }
    printf("%d%d , ", r1, n - 1);
    n--;
  }
  if (checkforb(r1, n - 1) == 1) {
    printf("%d%d! , ", r1, n - 1);
  }
  n = c1;
  while (board[r1][n + 1] == ' ' && (n + 1) <= 7) {
    printf("%d%d , ", r1, n + 1);
    ++n;
  }
  if (checkforb(r1, n + 1) == 1) {
    printf("%d%d! , ", r1, n + 1);
  }
  printf("\nVertically:\n");
  n = r1;
  while (board[n - 1][c1] == ' ' && n > -1) {
    printf("%d%d , ", n - 1, c1);
    --n;
  }
  if (checkforb(n - 1, c1) == 1) {
    printf("%d%d! , ", n - 1, c1);
  }
  n = r1;
  while ((board[n + 1][c1] == ' ') && ((n) <= 7)) {
    printf("%d%d , ", n + 1, c1);
    ++n;
  }
  if (checkforb(n + 1, c1) == 1) {
    printf("%d%d! , ", n + 1, c1);
  }
}

void rookw(int r1, int c1) {
  int i, j, n;
  printf("Available are: \n");
  n = c1;
  printf("Horizontally: \n");
  while (board[r1][n - 1] == ' ') {
    if (n == 0) {
      break;
    }
    printf("%d%d , ", r1, n - 1);
    n--;
  }
  if (checkforw(r1, n - 1) == 1) {
    printf("%d%d! , ", r1, n - 1);
  }
  n = c1;
  while (board[r1][n + 1] == ' ' && (n + 1) <= 7) {
    printf("%d%d , ", r1, n + 1);
    ++n;
  }
  if (checkforw(r1, n + 1) == 1) {
    printf("%d%d! , ", r1, n + 1);
  }
  printf("\nVertically:\n");
  n = r1;
  while (board[n - 1][c1] == ' ' && n > -1) {
    printf("%d%d , ", n - 1, c1);
    --n;
  }
  if (checkforw(n - 1, c1) == 1) {
    printf("%d%d! , ", n - 1, c1);
  }
  n = r1;
  while ((board[n + 1][c1] == ' ') && ((n) <= 7)) {
    printf("%d%d , ", n + 1, c1);
    ++n;
  }
  if (checkforw(n + 1, c1) == 1) {
    printf("%d%d! , ", n + 1, c1);
  }
}

void horseb(int r1, int c1) {
  printf("Available are: ");
  if (board[r1 + 2][c1 + 1] == ' ') printf("%d%d, ", r1 + 2, c1 + 1);
  if (board[r1 + 2][c1 - 1] == ' ') {
    if ((c1 - 1) > -1) printf("%d%d, ", r1 + 2, c1 - 1);
  }
  if (board[r1 + 1][c1 + 2] == ' ') {
    if ((c1 + 2) != 8) printf("%d%d, ", r1 + 1, c1 + 2);
  }
  if (board[r1 - 1][c1 + 2] == ' ') {
    printf("%d%d, ", r1 - 1, c1 + 2);
  }
  if (board[r1 - 2][c1 - 1] == ' ') {
    if ((c1 - 1) != -1) printf("%d%d, ", r1 - 2, c1 - 1);
  }
  if (board[r1 - 2][c1 + 1] == ' ') printf("%d%d, ", r1 - 2, c1 + 1);
  if (board[r1 + 1][c1 - 2] == ' ') printf("%d%d, ", r1 + 1, c1 - 2);
  if (board[r1 - 1][c1 - 2] == ' ') {
    if ((c1 - 2) != -1) printf("%d%d, ", r1 - 1, c1 - 2);
  }
  if (checkforb(r1 + 2, c1 + 1) == 1) {
    printf("%d%d! , ", r1 + 2, c1 + 1);
  }
  if (checkforb(r1 + 2, c1 - 1) == 1) {
    printf("%d%d! , ", r1 + 2, c1 - 1);
  }
  if (checkforb(r1 + 1, c1 + 2) == 1) {
    printf("%d%d! , ", r1 + 1, c1 + 2);
  }
  if (checkforb(r1 - 1, c1 + 2) == 1) {
    printf("%d%d! , ", r1 - 1, c1 + 2);
  }
  if (checkforb(r1 - 2, c1 - 1) == 1) {
    printf("%d%d! , ", r1 - 2, c1 - 1);
  }
  if (checkforb(r1 - 2, c1 + 1) == 1) {
    printf("%d%d! , ", r1 - 2, c1 + 1);
  }
  if (checkforb(r1 + 1, c1 - 2) == 1) {
    printf("%d%d! , ", r1 + 1, c1 - 2);
  }
  if (checkforb(r1 - 1, c1 - 2) == 1) {
    printf("%d%d! , ", r1 - 1, c1 - 2);
  }
}

void horsew(int r1, int c1) {
  printf("Available are: ");
  if (board[r1 + 2][c1 + 1] == ' ') printf("%d%d, ", r1 + 2, c1 + 1);
  if (board[r1 + 2][c1 - 1] == ' ') {
    if ((c1 - 1) > -1) printf("%d%d, ", r1 + 2, c1 - 1);
  }
  if (board[r1 + 1][c1 + 2] == ' ') {
    if ((c1 + 2) != 8) printf("%d%d, ", r1 + 1, c1 + 2);
  }
  if (board[r1 - 1][c1 + 2] == ' ') {
    printf("%d%d, ", r1 - 1, c1 + 2);
  }
  if (board[r1 - 2][c1 - 1] == ' ') {
    if ((c1 - 1) != -1) printf("%d%d, ", r1 - 2, c1 - 1);
  }
  if (board[r1 - 2][c1 + 1] == ' ') printf("%d%d, ", r1 - 2, c1 + 1);
  if (board[r1 + 1][c1 - 2] == ' ') printf("%d%d, ", r1 + 1, c1 - 2);
  if (board[r1 - 1][c1 - 2] == ' ') {
    if ((c1 - 2) != -1) printf("%d%d, ", r1 - 1, c1 - 2);
  }
  if (checkforw(r1 + 2, c1 + 1) == 1) {
    printf("%d%d! , ", r1 + 2, c1 + 1);
  }
  if (checkforw(r1 + 2, c1 - 1) == 1) {
    printf("%d%d! , ", r1 + 2, c1 - 1);
  }
  if (checkforw(r1 + 1, c1 + 2) == 1) {
    printf("%d%d! , ", r1 + 1, c1 + 2);
  }
  if (checkforw(r1 - 1, c1 + 2) == 1) {
    printf("%d%d! , ", r1 - 1, c1 + 2);
  }
  if (checkforw(r1 - 2, c1 - 1) == 1) {
    printf("%d%d! , ", r1 - 2, c1 - 1);
  }
  if (checkforw(r1 - 2, c1 + 1) == 1) {
    printf("%d%d! , ", r1 - 2, c1 + 1);
  }
  if (checkforw(r1 + 1, c1 - 2) == 1) {
    printf("%d%d! , ", r1 + 1, c1 - 2);
  }
  if (checkforw(r1 - 1, c1 - 2) == 1) {
    printf("%d%d! , ", r1 - 1, c1 - 2);
  }
}

void camelb(int r1, int c1) {
  int a, b, c, d;
  printf("Available are: \n");
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 - a, c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 + b) == 1) {
    printf("%d%d! , ", r1 - a, c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 + a, c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 - b) == 1) {
    printf("%d%d! , ", r1 + a, c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 + a, c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 + b) == 1) {
    printf("%d%d! , ", r1 + a, c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 - a, c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 - b) == 1) {
    printf("%d%d! , ", r1 - a, c1 - b);
  }
}

void camelw(int r1, int c1) {
  int a, b, c, d;
  printf("Available are: \n");
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 - a, c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 + b) == 1) {
    printf("%d%d! , ", r1 - a, c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 + a, c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 - b) == 1) {
    printf("%d%d! , ", r1 + a, c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 + a, c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 + b) == 1) {
    printf("%d%d! , ", r1 + a, c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 - a, c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 - b) == 1) {
    printf("%d%d! , ", r1 - a, c1 - b);
  }
}

void kingb(int r1, int c1) {
  printf("Available are: ");
  if (board[r1][c1 + 1] == ' ') printf("%d%d , ", r1, c1 + 1);
  if (checkforb(r1, c1 + 1) == 1) printf("%d%d! , ", r1, c1 + 1);
  if (board[r1][c1 - 1] == ' ') printf("%d%d , ", r1, c1 - 1);
  if (checkforb(r1, c1 - 1) == 1) printf("%d%d! , ", r1, c1 - 1);
  if (board[r1 + 1][c1] == ' ') printf("%d%d , ", r1 + 1, c1);
  if (checkforb(r1 + 1, c1) == 1) printf("%d%d! , ", r1 + 1, c1);
  if (board[r1 - 1][c1] == ' ') printf("%d%d , ", r1 - 1, c1);
  if (checkforb(r1 - 1, c1) == 1) printf("%d%d! , ", r1 - 1, c1);
  if (board[r1 + 1][c1 + 1] == ' ') printf("%d%d , ", r1 + 1, c1 + 1);
  if (checkforb(r1 + 1, c1 + 1) == 1) printf("%d%d! , ", r1 + 1, c1 + 1);
  if (board[r1 - 1][c1 - 1] == ' ') printf("%d%d , ", r1 - 1, c1 - 1);
  if (checkforb(r1 - 1, c1 - 1) == 1) printf("%d%d! , ", r1 - 1, c1 - 1);
  if (board[r1 - 1][c1 + 1] == ' ') printf("%d%d , ", r1 - 1, c1 + 1);
  if (checkforb(r1 - 1, c1 + 1) == 1) printf("%d%d! , ", r1 - 1, c1 + 1);
  if (board[r1 + 1][c1 - 1] == ' ') printf("%d%d , ", r1 + 1, c1 - 1);
  if (checkforb(r1 + 1, c1 + 1) == 1) printf("%d%d! , ", r1 + 1, c1 - 1);
}

void kingw(int r1, int c1) {
  printf("Available are: ");
  if (board[r1][c1 + 1] == ' ') printf("%d%d , ", r1, c1 + 1);
  if (checkforw(r1, c1 + 1) == 1) printf("%d%d! , ", r1, c1 + 1);
  if (board[r1][c1 - 1] == ' ') printf("%d%d , ", r1, c1 - 1);
  if (checkforw(r1, c1 - 1) == 1) printf("%d%d! , ", r1, c1 - 1);
  if (board[r1 + 1][c1] == ' ') printf("%d%d , ", r1 + 1, c1);
  if (checkforw(r1 + 1, c1) == 1) printf("%d%d! , ", r1 + 1, c1);
  if (board[r1 - 1][c1] == ' ') printf("%d%d , ", r1 - 1, c1);
  if (checkforw(r1 - 1, c1) == 1) printf("%d%d! , ", r1 - 1, c1);
  if (board[r1 + 1][c1 + 1] == ' ') printf("%d%d , ", r1 + 1, c1 + 1);
  if (checkforw(r1 + 1, c1 + 1) == 1) printf("%d%d! , ", r1 + 1, c1 + 1);
  if (board[r1 - 1][c1 - 1] == ' ') printf("%d%d , ", r1 - 1, c1 - 1);
  if (checkforw(r1 - 1, c1 - 1) == 1) printf("%d%d! , ", r1 - 1, c1 - 1);
  if (board[r1 - 1][c1 + 1] == ' ') printf("%d%d , ", r1 - 1, c1 + 1);
  if (checkforw(r1 - 1, c1 + 1) == 1) printf("%d%d! , ", r1 - 1, c1 + 1);
  if (board[r1 + 1][c1 - 1] == ' ') printf("%d%d , ", r1 + 1, c1 - 1);
  if (checkforw(r1 + 1, c1 + 1) == 1) printf("%d%d! , ", r1 + 1, c1 - 1);
}

void queenb(int r1, int c1) {
  int x = 1, y = 1, a, b;
  printf("Available are: ");
  printf("Horizontal: ");
  while (board[r1][c1 - y] == ' ') {
    if ((c1 - y) == -1) break;
    printf("%d%d , ", r1, c1 - y);
    y++;
  }
  if (checkforb(r1, c1 - y) == 1) {
    printf("%d%d! , ", r1, c1 - y);
  }
  y = 1;
  while (board[r1][c1 + y] == ' ') {
    if ((c1 + y) == 8) break;
    printf("%d%d , ", r1, c1 + y);
    y++;
  }
  if (checkforb(r1, c1 + y) == 1) {
    printf("%d%d! , ", r1, c1 - y);
  }
  printf("Vertical: ");
  x = 1;
  while (board[r1 - x][c1] == ' ') {
    if ((r1 - x) == -1) break;
    printf("%d%d , ", r1 - x, c1);
    x++;
  }
  if (checkforb(r1 - x, c1) == 1) {
    printf("%d%d! , ", r1 - x, c1);
  }
  x = 1;
  while (board[r1 + x][c1] == ' ') {
    if ((r1 + x) == 8) break;
    printf("%d%d , ", r1 + x, c1);
    x++;
  }
  if (checkforb(r1 + x, c1) == 1) {
    printf("%d%d! , ", r1 - x, c1);
  }
  printf("Diagonally: ");
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 - a, c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 + b) == 1) {
    printf("%d%d! , ", r1 - a, c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 + a, c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 - b) == 1) {
    printf("%d%d! , ", r1 + a, c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 + a, c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 + b) == 1) {
    printf("%d%d! , ", r1 + a, c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 - a, c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 - b) == 1) {
    printf("%d%d! , ", r1 - a, c1 - b);
  }
}

void queenw(int r1, int c1) {
  int x = 1, y = 1, a, b;
  printf("Available are: ");
  printf("Horizontal: ");
  while (board[r1][c1 - y] == ' ') {
    if ((c1 - y) == -1) break;
    printf("%d%d , ", r1, c1 - y);
    y++;
  }
  if (checkforw(r1, c1 - y) == 1) {
    printf("%d%d! , ", r1, c1 - y);
  }
  y = 1;
  while (board[r1][c1 + y] == ' ') {
    if ((c1 + y) == 8) break;
    printf("%d%d , ", r1, c1 + y);
    y++;
  }
  if (checkforw(r1, c1 + y) == 1) {
    printf("%d%d! , ", r1, c1 - y);
  }
  printf("Vertical: ");
  x = 1;
  while (board[r1 - x][c1] == ' ') {
    if ((r1 - x) == -1) break;
    printf("%d%d , ", r1 - x, c1);
    x++;
  }
  if (checkforw(r1 - x, c1) == 1) {
    printf("%d%d! , ", r1 - x, c1);
  }
  x = 1;
  while (board[r1 + x][c1] == ' ') {
    if ((r1 + x) == 8) break;
    printf("%d%d , ", r1 + x, c1);
    x++;
  }
  if (checkforw(r1 + x, c1) == 1) {
    printf("%d%d! , ", r1 - x, c1);
  }
  printf("Diagonally: ");
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 - a, c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 + b) == 1) {
    printf("%d%d! , ", r1 - a, c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 + a, c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 - b) == 1) {
    printf("%d%d! , ", r1 + a, c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    printf("%d%d , ", r1 + a, c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 + b) == 1) {
    printf("%d%d! , ", r1 + a, c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    printf("%d%d , ", r1 - a, c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 - b) == 1) {
    printf("%d%d! , ", r1 - a, c1 - b);
  }
}

void white() {
  int p1, p2, c1, r1, c2, r2;
  printf("\nPLAYER 1 - Big Case\n");
again1:
  printf("\nEnter Position of Element to change ( RC ): ");
  scanf("%d", &p1);
  c1 = p1 % 10;
  r1 = p1 / 10;
  switch (board[r1][c1]) {
    case 'P':
      pawnw(r1, c1);
      break;
    case 'R':
      rookw(r1, c1);
      break;
    case 'H':
      horsew(r1, c1);
      break;
    case 'C':
      camelw(r1, c1);
      break;
    case 'K':
      kingw(r1, c1);
      break;
    case 'Q':
      queenw(r1, c1);
      break;
    default:
      printf("Invalid Position ! ");
      goto again1;
  }
  printf("\nEnter Position of Place to Send ( RC ): ");
  scanf("%d", &p2);
  c2 = p2 % 10;
  r2 = p2 / 10;
  change(r1, c1, r2, c2);
}

void black() {
  int p1, p2, c1, r1, c2, r2;
  printf("\nPLAYER 2 - Small Case \n");
again2:
  printf("\nEnter Position of Element to change ( RC ): ");
  scanf("%d", &p1);
  c1 = p1 % 10;
  r1 = p1 / 10;
  switch (board[r1][c1]) {
    case 'p':
      pawnb(r1, c1);
      break;
    case 'r':
      rookb(r1, c1);
      break;
    case 'h':
      horseb(r1, c1);
      break;
    case 'c':
      camelb(r1, c1);
      break;
    case 'k':
      kingb(r1, c1);
      break;
    case 'q':
      queenb(r1, c1);
      break;
    default:
      printf("Invalid Position ! ");
      goto again2;
  }
  printf("\nEnter Position of Place to Send ( RC ): ");
  scanf("%d", &p2);
  c2 = p2 % 10;
  r2 = p2 / 10;
  change(r1, c1, r2, c2);
}
