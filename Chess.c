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
int possible[9999];
int a = 1;
int sayac = 0;
void sifirla();
int checkinput(int);
void kaydet(int);
void sifirla();
void sifirla2();

int pwmoves[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int pbmoves[8] = {0, 0, 0, 0, 0, 0, 0, 0};

char board[8][8] = {{'r', 'h', 'c', 'k', 'q', 'c', 'h', 'r'},
                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                    {'R', 'H', 'C', 'K', 'Q', 'C', 'H', 'R'}};

int main() {
  int x = 0, a = 1;
  char ch;
  do {
    x++;
    system("cls");
    display();
    sifirla();
    if ((x % 2) == 0) {
      black();
    } else {
      white();
    }
    printf("\n\nPress enter to continue\n\n");
    ch = getch();
  } while (ch == 13);
}

int checkinput(int a) {
  if (possible[a] == 0) {
    return 0;
  } else {
    return 1;
  }
}

void display() {
  int i, j, k;
  printf("\nChess Board (t=%d)\n\n", sayac);
  printf(" ");
  for (i = 0; i < 8; i++) printf("    %d", i);
  printf("\n");
  for (k = 0; k < 8; k++) {
    printf("  ");
    printf("\n");
    printf("%d ", k);
    for (j = 0; j < 8; j++) {
      if (board[k][j] == 'p')
        printf("   BP");
      else if (board[k][j] == 'r')
        printf("   BR");
      else if (board[k][j] == 'h')
        printf("   BH");
      else if (board[k][j] == 'c')
        printf("   BC");
      else if (board[k][j] == 'k')
        printf("   BK");
      else if (board[k][j] == 'q')
        printf("   BQ");
      else if (board[k][j] == 'P')
        printf("   WP");
      else if (board[k][j] == 'R')
        printf("   WR");
      else if (board[k][j] == 'H')
        printf("   WH");
      else if (board[k][j] == 'C')
        printf("   WC");
      else if (board[k][j] == 'K')
        printf("   WK");
      else if (board[k][j] == 'Q')
        printf("   WQ");
      else if (board[k][j] == ' ')
        printf("    0");
    }
    printf("   \n");
  }
  printf("  ");
  printf("\n");
}

void change(int r1, int c1, int r2, int c2) {
  char temp;
  if (board[r2][c2] != ' ') {
    printf("\nElimination: %d ", (r1 * 10) + c1);
    if (board[r1][c1] == 'p')
      printf("BP");
    else if (board[r1][c1] == 'r')
      printf("BR");
    else if (board[r1][c1] == 'h')
      printf("BH");
    else if (board[r1][c1] == 'c')
      printf("BC");
    else if (board[r1][c1] == 'k')
      printf("BK");
    else if (board[r1][c1] == 'q')
      printf("BQ");
    else if (board[r1][c1] == 'P')
      printf("WP");
    else if (board[r1][c1] == 'R')
      printf("WR");
    else if (board[r1][c1] == 'H')
      printf("WH");
    else if (board[r1][c1] == 'C')
      printf("WC");
    else if (board[r1][c1] == 'K')
      printf("WK");
    else if (board[r1][c1] == 'Q')
      printf("WQ");
    printf(" -> %d ", (r2 * 10) + c2);
    if (board[r2][c2] == 'p')
      printf("BP");
    else if (board[r2][c2] == 'r')
      printf("BR");
    else if (board[r2][c2] == 'h')
      printf("BH");
    else if (board[r2][c2] == 'c')
      printf("BC");
    else if (board[r2][c2] == 'k')
      printf("BK");
    else if (board[r2][c2] == 'q')
      printf("BQ");
    else if (board[r2][c2] == 'P')
      printf("WP");
    else if (board[r2][c2] == 'R')
      printf("WR");
    else if (board[r2][c2] == 'H')
      printf("WH");
    else if (board[r2][c2] == 'C')
      printf("WC");
    else if (board[r2][c2] == 'K')
      printf("WK");
    else if (board[r2][c2] == 'Q')
      printf("WQ");
    temp = board[r1][c1];
    board[r1][c1] = ' ';
    board[r2][c2] = temp;
  }
  if (board[r2][c2] == ' ') {
    temp = board[r1][c1];
    board[r1][c1] = ' ';
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
    default:
      return 0;
  }
}

void kaydet(int x) {
  possible[a] = x;
  a++;
}

void pawnb(int r1, int c1) {
  pbmoves[c1]++;
  if (pbmoves[c1] == 1) {
    if (board[r1 + 1][c1] == ' ') kaydet(((r1 + 1) * 10) + c1);
    if (board[r1 + 2][c1] == ' ') kaydet(((r1 + 2) * 10) + c1);
  } else {
    if (board[r1 + 1][c1] == ' ') kaydet(((r1 + 1) * 10) + c1);
    if (checkforb(r1 + 1, c1 - 1) == 1) kaydet(((r1 + 1) * 10) + c1 - 1);
    if (checkforb(r1 + 1, c1 + 1) == 1) kaydet(((r1 + 1) * 10) + c1 + 1);
  }
}

void pawnw(int r1, int c1) {
  pwmoves[c1]++;
  if (pwmoves[c1] == 1) {
    if (board[r1 - 1][c1] == ' ') kaydet(((r1 - 1) * 10) + c1);
    if (board[r1 - 2][c1] == ' ') kaydet(((r1 - 2) * 10) + c1);
  } else {
    if (board[r1 - 1][c1] == ' ') kaydet(((r1 - 1) * 10) + c1);
    if (checkforw(r1 - 1, c1 + 1) == 1) kaydet(((r1 - 1) * 10) + c1 + 1);
    if (checkforw(r1 - 1, c1 - 1) == 1) kaydet(((r1 - 1) * 10) + c1 - 1);
  }
}

void rookb(int r1, int c1) {
  int i, j, n;
  n = c1;
  while (board[r1][n - 1] == ' ') {
    if (n == 0) {
      break;
    }
    kaydet(((r1)*10) + n - 1);
    n--;
  }
  if (checkforb(r1, n - 1) == 1) {
    kaydet(((r1)*10) + n - 1);
  }
  n = c1;
  while (board[r1][n + 1] == ' ' && (n + 1) <= 7) {
    kaydet(((r1)*10) + n + 1);
    ++n;
  }
  if (checkforb(r1, n + 1) == 1) {
    kaydet(((r1)*10) + n + 1);
  }
  n = r1;
  while (board[n + 1][c1] == ' ' && (n + 1) < 8) {
    kaydet(((n + 1) * 10) + c1);
    ++n;
  }
  if (checkforb(n + 1, c1) == 1) {
    kaydet(((n + 1) * 10) + c1);
  }
  n = r1;
  while ((board[n - 1][c1] == ' ') && (n - 1) > -1) {
    kaydet(((n - 1) * 10) + c1);
    --n;
  }
  if (checkforb(n - 1, c1) == 1) {
    kaydet(((n - 1) * 10) + c1);
  }
}

void rookw(int r1, int c1) {
  int i, j, n;
  n = c1;
  while (board[r1][n - 1] == ' ') {
    if (n == 0) {
      break;
    }
    kaydet(((r1)*10) + n - 1);
    n--;
  }
  if (checkforw(r1, n - 1) == 1) {
    kaydet(((r1)*10) + n - 1);
  }
  n = c1;
  while (board[r1][n + 1] == ' ' && (n + 1) <= 7) {
    kaydet(((r1)*10) + n + 1);
    ++n;
  }
  if (checkforw(r1, n + 1) == 1) {
    kaydet(((r1)*10) + n + 1);
  }
  n = r1;
  while (board[n + 1][c1] == ' ' && (n + 1) < 8) {
    kaydet(((n + 1) * 10) + c1);
    ++n;
  }
  if (checkforw(n + 1, c1) == 1) {
    kaydet(((n + 1) * 10) + c1);
  }
  n = r1;
  while ((board[n - 1][c1] == ' ') && (n - 1) > -1) {
    kaydet(((n - 1) * 10) + c1);
    --n;
  }
  if (checkforw(n - 1, c1) == 1) {
    kaydet(((n - 1) * 10) + c1);
  }
}

void horseb(int r1, int c1) {
  if (board[r1 - 2][c1 + 1] == ' ' && (r1 - 2) > -1 && (c1 + 1) < 8)
    kaydet(((r1 - 2) * 10) + c1 + 1);
  if (board[r1 - 2][c1 - 1] == ' ' && (r1 - 2) > -1 && (c1 - 1) > -1)
    kaydet(((r1 - 2) * 10) + c1 - 1);
  if (board[r1 - 1][c1 + 2] == ' ' && (r1 - 1) > -1 && (c1 + 2) < 8)
    kaydet(((r1 - 1) * 10) + c1 + 2);
  if (board[r1 + 1][c1 + 2] == ' ' && (r1 + 1) < 8 && (c1 + 2) < 8)
    kaydet(((r1 + 1) * 10) + c1 + 2);
  if (board[r1 + 2][c1 - 1] == ' ' && (r1 + 2) < 8 && (c1 - 1) > -1)
    kaydet(((r1 + 2) * 10) + c1 - 1);
  if (board[r1 + 2][c1 + 1] == ' ' && (r1 + 2) < 8 && (c1 + 1) < 8)
    kaydet(((r1 + 2) * 10) + c1 + 1);
  if (board[r1 - 1][c1 - 2] == ' ' && (r1 - 1) > -1 && (c1 - 2) > -1)
    kaydet(((r1 - 1) * 10) + c1 - 2);
  if (board[r1 + 1][c1 - 2] == ' ' && (r1 + 1) < 8 && (c1 - 2) > -1)
    kaydet(((r1 + 1) * 10) + c1 - 2);
  if (checkforb(r1 - 2, c1 + 1) == 1) {
    kaydet(((r1 - 2) * 10) + c1 + 1);
  }
  if (checkforb(r1 - 2, c1 - 1) == 1) {
    kaydet(((r1 - 2) * 10) + c1 - 1);
  }
  if (checkforb(r1 - 1, c1 + 2) == 1) {
    kaydet(((r1 - 1) * 10) + c1 + 2);
  }
  if (checkforb(r1 + 1, c1 + 2) == 1) {
    kaydet(((r1 + 1) * 10) + c1 + 2);
  }
  if (checkforb(r1 + 2, c1 - 1) == 1) {
    kaydet(((r1 + 2) * 10) + c1 - 1);
  }
  if (checkforb(r1 + 2, c1 + 1) == 1) {
    kaydet(((r1 + 2) * 10) + c1 + 1);
  }
  if (checkforb(r1 - 1, c1 - 2) == 1) {
    kaydet(((r1 - 1) * 10) + c1 - 2);
  }
  if (checkforb(r1 + 1, c1 - 2) == 1) {
    kaydet(((r1 + 1) * 10) + c1 - 2);
  }
}

void horsew(int r1, int c1) {
  if (board[r1 - 2][c1 + 1] == ' ' && (r1 - 2) > -1 && (c1 + 1) < 8)
    kaydet(((r1 - 2) * 10) + c1 + 1);
  if (board[r1 - 2][c1 - 1] == ' ' && (r1 - 2) > -1 && (c1 - 1) > -1)
    kaydet(((r1 - 2) * 10) + c1 - 1);
  if (board[r1 - 1][c1 + 2] == ' ' && (r1 - 1) > -1 && (c1 + 2) < 8)
    kaydet(((r1 - 1) * 10) + c1 + 2);
  if (board[r1 + 1][c1 + 2] == ' ' && (r1 + 1) < 8 && (c1 + 2) < 8)
    kaydet(((r1 + 1) * 10) + c1 + 2);
  if (board[r1 + 2][c1 - 1] == ' ' && (r1 + 2) < 8 && (c1 - 1) > -1)
    kaydet(((r1 + 2) * 10) + c1 - 1);
  if (board[r1 + 2][c1 + 1] == ' ' && (r1 + 2) < 8 && (c1 + 1) < 8)
    kaydet(((r1 + 2) * 10) + c1 + 1);
  if (board[r1 - 1][c1 - 2] == ' ' && (r1 - 1) > -1 && (c1 - 2) > -1)
    kaydet(((r1 - 1) * 10) + c1 - 2);
  if (board[r1 + 1][c1 - 2] == ' ' && (r1 + 1) < 8 && (c1 - 2) > -1)
    kaydet(((r1 + 1) * 10) + c1 - 2);
  if (checkforw(r1 - 2, c1 + 1) == 1) {
    kaydet(((r1 - 2) * 10) + c1 + 1);
  }
  if (checkforw(r1 - 2, c1 - 1) == 1) {
    kaydet(((r1 - 2) * 10) + c1 - 1);
  }
  if (checkforw(r1 - 1, c1 + 2) == 1) {
    kaydet(((r1 - 1) * 10) + c1 + 2);
  }
  if (checkforw(r1 + 1, c1 + 2) == 1) {
    kaydet(((r1 + 1) * 10) + c1 + 2);
  }
  if (checkforw(r1 + 2, c1 - 1) == 1) {
    kaydet(((r1 + 2) * 10) + c1 - 1);
  }
  if (checkforw(r1 + 2, c1 + 1) == 1) {
    kaydet(((r1 + 2) * 10) + c1 + 1);
  }
  if (checkforw(r1 - 1, c1 - 2) == 1) {
    kaydet(((r1 - 1) * 10) + c1 - 2);
  }
  if (checkforw(r1 + 1, c1 - 2) == 1) {
    kaydet(((r1 + 1) * 10) + c1 - 2);
  }
}

void camelb(int r1, int c1) {
  int a, b, c, d;
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    kaydet(((r1 + a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 + b) == 1) {
    kaydet(((r1 + a) * 10) + c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    kaydet(((r1 - a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 - b) == 1) {
    kaydet(((r1 - a) * 10) + c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    kaydet(((r1 - a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 + b) == 1) {
    kaydet(((r1 - a) * 10) + c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    kaydet(((r1 + a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 - b) == 1) {
    kaydet(((r1 + a) * 10) + c1 - b);
  }
}

void camelw(int r1, int c1) {
  int a, b, c, d;
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    kaydet(((r1 + a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 + b) == 1) {
    kaydet(((r1 + a) * 10) + c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    kaydet(((r1 - a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 - b) == 1) {
    kaydet(((r1 - a) * 10) + c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    kaydet(((r1 - a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 + b) == 1) {
    kaydet(((r1 - a) * 10) + c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    kaydet(((r1 + a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 - b) == 1) {
    kaydet(((r1 + a) * 10) + c1 - b);
  }
}

void kingb(int r1, int c1) {
  if (board[r1][c1 + 1] == ' ' && (c1 + 1) < 8) kaydet(((r1)*10) + c1 + 1);
  if (checkforb(r1, c1 + 1) == 1) kaydet(((r1)*10) + c1 + 1);
  if (board[r1][c1 - 1] == ' ' && (c1 - 1) > -1) kaydet(((r1)*10) + c1 - 1);
  if (checkforb(r1, c1 - 1) == 1) kaydet(((r1)*10) + c1 - 1);
  if (board[r1 - 1][c1] == ' ' && (r1 - 1) > -1) kaydet(((r1 - 1) * 10) + c1);
  if (checkforb(r1 - 1, c1) == 1) kaydet(((r1 - 1) * 10) + c1);
  if (board[r1 + 1][c1] == ' ' && (r1 + 1) < 8) kaydet(((r1 + 1) * 10) + c1);
  if (checkforb(r1 + 1, c1) == 1) kaydet(((r1 + 1) * 10) + c1);
  if (board[r1 - 1][c1 + 1] == ' ' && (r1 - 1) > -1 && (c1 + 1) < 8)
    kaydet(((r1 - 1) * 10) + c1 + 1);
  if (checkforb(r1 - 1, c1 + 1) == 1) kaydet(((r1 - 1) * 10) + c1 + 1);
  if (board[r1 + 1][c1 - 1] == ' ' && (r1 + 1) < 8 && (c1 - 1) > -1)
    kaydet(((r1 + 1) * 10) + c1 - 1);
  if (checkforb(r1 + 1, c1 - 1) == 1) kaydet(((r1 + 1) * 10) + c1 - 1);
  if (board[r1 + 1][c1 + 1] == ' ' && (r1 + 1) < 8 && (c1 + 1) < 8)
    kaydet(((r1 + 1) * 10) + c1 + 1);
  if (checkforb(r1 + 1, c1 + 1) == 1) kaydet(((r1 + 1) * 10) + c1 + 1);
  if (board[r1 - 1][c1 - 1] == ' ' && (r1 - 1) > -1 && (c1 - 1) > -1)
    kaydet(((r1 - 1) * 10) + c1 - 1);
  if (checkforb(r1 - 1, c1 - 1) == 1) kaydet(((r1 - 1) * 10) + c1 - 1);
}

void kingw(int r1, int c1) {
  if (board[r1][c1 + 1] == ' ' && (c1 + 1) < 8) kaydet(((r1)*10) + c1 + 1);
  if (checkforw(r1, c1 + 1) == 1) kaydet(((r1)*10) + c1 + 1);
  if (board[r1][c1 - 1] == ' ' && (c1 - 1) > -1) kaydet(((r1)*10) + c1 - 1);
  if (checkforw(r1, c1 - 1) == 1) kaydet(((r1)*10) + c1 - 1);
  if (board[r1 - 1][c1] == ' ' && (r1 - 1) > -1) kaydet(((r1 - 1) * 10) + c1);
  if (checkforw(r1 - 1, c1) == 1) kaydet(((r1 - 1) * 10) + c1);
  if (board[r1 + 1][c1] == ' ' && (r1 + 1) < 8) kaydet(((r1 + 1) * 10) + c1);
  if (checkforw(r1 + 1, c1) == 1) kaydet(((r1 + 1) * 10) + c1);
  if (board[r1 - 1][c1 + 1] == ' ' && (r1 - 1) > -1 && (c1 + 1) < 8)
    kaydet(((r1 - 1) * 10) + c1 + 1);
  if (checkforw(r1 - 1, c1 + 1) == 1) kaydet(((r1 - 1) * 10) + c1 + 1);
  if (board[r1 + 1][c1 - 1] == ' ' && (r1 + 1) < 8 && (c1 - 1) > -1)
    kaydet(((r1 + 1) * 10) + c1 - 1);
  if (checkforw(r1 + 1, c1 - 1) == 1) kaydet(((r1 + 1) * 10) + c1 - 1);
  if (board[r1 + 1][c1 + 1] == ' ' && (r1 + 1) < 8 && (c1 + 1) < 8)
    kaydet(((r1 + 1) * 10) + c1 + 1);
  if (checkforw(r1 + 1, c1 + 1) == 1) kaydet(((r1 + 1) * 10) + c1 + 1);
  if (board[r1 - 1][c1 - 1] == ' ' && (r1 - 1) > -1 && (c1 - 1) > -1)
    kaydet(((r1 - 1) * 10) + c1 - 1);
  if (checkforw(r1 - 1, c1 - 1) == 1) kaydet(((r1 - 1) * 10) + c1 - 1);
}

void queenb(int r1, int c1) {
  int x = 1, y = 1, a, b;
  while (board[r1][c1 - y] == ' ') {
    if ((c1 - y) == -1) break;
    kaydet(((r1)*10) + c1 - y);
    y++;
  }
  if (checkforb(r1, c1 - y) == 1) {
    kaydet(((r1)*10) + c1 - y);
  }
  y = 1;
  while (board[r1][c1 + y] == ' ') {
    if ((c1 + y) == 8) break;
    kaydet(((r1)*10) + c1 + y);
    y++;
  }
  if (checkforb(r1, c1 + y) == 1) {
    kaydet(((r1)*10) + c1 + y);
  }
  x = 1;
  while (board[r1 + x][c1] == ' ') {
    if ((r1 + x) == 8) break;
    kaydet(((r1 + x) * 10) + c1);
    x++;
  }
  if (checkforb(r1 + x, c1) == 1) {
    kaydet(((r1 + x) * 10) + c1);
  }
  x = 1;
  while (board[r1 - x][c1] == ' ') {
    if ((r1 - x) == -1) break;
    kaydet(((r1 - x) * 10) + c1);
    x++;
  }
  if (checkforb(r1 - x, c1) == 1) {
    kaydet(((r1 - x) * 10) + c1);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    kaydet(((r1 + a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 + b) == 1) {
    kaydet(((r1 + a) * 10) + c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    kaydet(((r1 - a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 - b) == 1) {
    kaydet(((r1 - a) * 10) + c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    kaydet(((r1 - a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforb(r1 - a, c1 + b) == 1) {
    kaydet(((r1 - a) * 10) + c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    kaydet(((r1 + a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforb(r1 + a, c1 - b) == 1) {
    kaydet(((r1 + a) * 10) + c1 - b);
  }
}

void queenw(int r1, int c1) {
  int x = 1, y = 1, a, b;
  while (board[r1][c1 - y] == ' ') {
    if ((c1 - y) == -1) break;
    kaydet(((r1)*10) + c1 - y);
    y++;
  }
  if (checkforw(r1, c1 - y) == 1) {
    kaydet(((r1)*10) + c1 - y);
  }
  y = 1;
  while (board[r1][c1 + y] == ' ') {
    if ((c1 + y) == 8) break;
    kaydet(((r1)*10) + c1 + y);
    y++;
  }
  if (checkforw(r1, c1 + y) == 1) {
    kaydet(((r1)*10) + c1 + y);
  }
  x = 1;
  while (board[r1 + x][c1] == ' ') {
    if ((r1 + x) == 8) break;
    kaydet(((r1 + x) * 10) + c1);
    x++;
  }
  if (checkforw(r1 + x, c1) == 1) {
    kaydet(((r1 + x) * 10) + c1);
  }
  x = 1;
  while (board[r1 - x][c1] == ' ') {
    if ((r1 - x) == -1) break;
    kaydet(((r1 - x) * 10) + c1);
    x++;
  }
  if (checkforw(r1 - x, c1) == 1) {
    kaydet(((r1 - x) * 10) + c1);
  }
  a = 1, b = 1;
  while (board[r1 + a][c1 + b] == ' ') {
    if ((r1 + a) == 8 || (c1 + b) == 8) break;
    kaydet(((r1 + a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 + b) == 1) {
    kaydet(((r1 + a) * 10) + c1 + b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 - b] == ' ') {
    if ((r1 - a) == -1 || (c1 - b) == -1) break;
    kaydet(((r1 - a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 - b) == 1) {
    kaydet(((r1 - a) * 10) + c1 - b);
  }
  a = 1, b = 1;
  while (board[r1 - a][c1 + b] == ' ') {
    if ((r1 - a) == -1 || (c1 + b) == 8) break;
    kaydet(((r1 - a) * 10) + c1 + b);
    a++;
    b++;
  }
  if (checkforw(r1 - a, c1 + b) == 1) {
    kaydet(((r1 - a) * 10) + c1 + b);
  }
  a = 1;
  b = 1;
  while (board[r1 + a][c1 - b] == ' ') {
    if ((r1 + a) == 8 || (c1 - b) == -1) break;
    kaydet(((r1 + a) * 10) + c1 - b);
    a++;
    b++;
  }
  if (checkforw(r1 + a, c1 - b) == 1) {
    kaydet(((r1 + a) * 10) + c1 - b);
  }
}

void sifirla() { a = 1; }

void sifirla2() {
  while (a <= 9999) {
    possible[a] = 0;
    a++;
  }
}

void white() {
  int p1, p2, c1, r1, c2, r2, z = 1;
  printf("\nPlayer 1 (W)\n");
again1:
  printf("\nSelect a piece (RC): ");
  scanf("%d", &p1);
  if (p1 > 77) {
    goto again1;
  }
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
      printf("Incorrect selection!");
      goto again1;
  }
  if (possible[1] == 0) {
    printf("\nPlease select a playable piece\n");
    goto again1;
  }
  printf("\nAvailable positions are:\n");
  while (z <= 9999) {
    if (possible[z] == 0) break;
    if (checkforw(possible[z] / 10, possible[z] % 10) == 1) {
      printf("\nEnter %d for position %d*\n", z, possible[z]);
    } else {
      printf("\nEnter %d for position %d\n", z, possible[z]);
    }
    z++;
  }
again3:
  printf("\nEnter a position you want to move the piece to (RC): ");
  scanf("%d", &p2);
  if (checkinput(p2) == 0) {
    printf("Please enter a valid number");
    goto again3;
  }
  if (checkinput(p2) == 1) {
    r2 = possible[p2] / 10;
    c2 = possible[p2] % 10;
    change(r1, c1, r2, c2);
  }
  sifirla();
  sifirla2();
}

void black() {
  int p1, p2, c1, r1, c2, r2, z = 1;
  printf("\nPlayer 2 (B)\n");
again2:
  printf("\nSelect a piece (RC): ");
  scanf("%d", &p1);
  if (p1 > 77) {
    goto again2;
  }
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
      printf("Incorrect selection!");
      goto again2;
  }
  if (possible[1] == 0) {
    printf("\nPlease select a playable piece\n");
    goto again2;
  }
  printf("\nAvailable positions are:\n");
  while (z <= 9999) {
    if (possible[z] == 0) break;
    if (checkforb(possible[z] / 10, possible[z] % 10) == 1) {
      printf("\nEnter %d for position %d*\n", z, possible[z]);
    } else {
      printf("\nEnter %d for position %d\n", z, possible[z]);
    }
    z++;
  }
again3:
  printf("\nEnter a position you want to move the piece to (RC): ");
  scanf("%d", &p2);
  if (checkinput(p2) == 0) {
    printf("Please enter a valid number");
    goto again3;
  }
  if (checkinput(p2) == 1) {
    r2 = possible[p2] / 10;
    c2 = possible[p2] % 10;
    change(r1, c1, r2, c2);
  }
  sifirla();
  sifirla2();
  sayac++;
}
