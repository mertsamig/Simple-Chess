#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

// Constants for better readability
#define BOARD_SIZE 8
#define MAX_MOVES 200
#define WHITE 1
#define BLACK 2
#define EMPTY ' '

// Game state
typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    int possibleMoves[MAX_MOVES];
    int moveCount;
    bool gameOver;
    char capturedPieces[2][16];  // Track captured pieces
    int captureCount[2];         // Count of captured pieces
} GameState;

// Function prototypes
void initializeGame(GameState* game);
void displayBoard(const GameState* game);
bool isValidPosition(int row, int col);
bool isValidMove(const GameState* game, int r1, int c1, int r2, int c2);
void generateMoves(GameState* game, int r1, int c1);
void movePiece(GameState* game, int r1, int c1, int r2, int c2);
void playerTurn(GameState* game, int player);
bool isPieceOwner(char piece, int player);
void generatePawnMoves(GameState* game, int r1, int c1);
void generateRookMoves(GameState* game, int r1, int c1);
void generateKnightMoves(GameState* game, int r1, int c1);
void generateBishopMoves(GameState* game, int r1, int c1);
void generateKingMoves(GameState* game, int r1, int c1);
void generateQueenMoves(GameState* game, int r1, int c1);
bool isKingInCheck(GameState* game, int player);
void saveGame(GameState* game, int currentPlayer);
bool loadGame(GameState* game, int* currentPlayer);

int main() {
    GameState game;
    int currentPlayer = WHITE;
    char choice;
    
    printf("Chess Game\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("Enter your choice (1/2): ");
    choice = getch();
    
    if (choice == '2') {
        if (!loadGame(&game, &currentPlayer)) {
            initializeGame(&game);
        }
    } else {
        initializeGame(&game);
    }
    
    while (!game.gameOver) {
        system("cls");  // Clear the console
        displayBoard(&game);
        
        playerTurn(&game, currentPlayer);
        
        // Check for checkmate/stalemate conditions (simplified implementation)
        if (isKingInCheck(&game, currentPlayer)) {
            printf("\nPlayer %d is in check!\n", currentPlayer);
        }
        
        printf("\nPress Enter to continue or 'S' to save and quit\n");
        choice = getch();
        if (choice == 's' || choice == 'S') {
            saveGame(&game, currentPlayer);
            break;
        }
        
        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
    }
    
    return 0;
}

// Initialize the game
void initializeGame(GameState* game) {
    // Initialize board with starting positions
    char initialBoard[BOARD_SIZE][BOARD_SIZE] = {
        {'r', 'h', 'c', 'q', 'k', 'c', 'h', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'H', 'C', 'Q', 'K', 'C', 'H', 'R'}
    };
    
    // Copy the initial board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = initialBoard[i][j];
        }
    }
    
    game->moveCount = 0;
    game->gameOver = false;
    game->captureCount[0] = 0;  // WHITE captured pieces
    game->captureCount[1] = 0;  // BLACK captured pieces
}

// Display the chessboard with improved formatting
void displayBoard(const GameState* game) {
    printf("\n  Chess Board\n\n");
    
    // Print column headers
    printf("    ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %c  ", 'a' + i);  // Using letters for columns
    }
    printf("\n");
    
    // Print top border
    printf("    ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("--- ");
    }
    printf("\n");
    
    // Print rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %d | ", BOARD_SIZE - i);  // Using numbers for rows
        
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c |", game->board[i][j]);
        }
        
        printf("\n    ");
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("--- ");
        }
        printf("\n");
    }
    
    // Display captured pieces
    printf("\nCaptured pieces:\n");
    printf("White: ");
    for (int i = 0; i < game->captureCount[0]; i++) {
        printf("%c ", game->capturedPieces[0][i]);
    }
    printf("\nBlack: ");
    for (int i = 0; i < game->captureCount[1]; i++) {
        printf("%c ", game->capturedPieces[1][i]);
    }
    printf("\n");
}

// Check if a position is within board boundaries
bool isValidPosition(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

// Check if a piece belongs to the current player
bool isPieceOwner(char piece, int player) {
    if (player == WHITE) {
        return piece >= 'A' && piece <= 'Z';  // White pieces are uppercase
    } else {
        return piece >= 'a' && piece <= 'z';  // Black pieces are lowercase
    }
}

// Check if a move is valid
bool isValidMove(const GameState* game, int r1, int c1, int r2, int c2) {
    // Check if destination is within board boundaries
    if (!isValidPosition(r2, c2)) {
        return false;
    }
    
    char sourcePiece = game->board[r1][c1];
    char destPiece = game->board[r2][c2];
    
    // Cannot move to a square occupied by own piece
    if (destPiece != EMPTY && 
        ((sourcePiece >= 'A' && sourcePiece <= 'Z' && destPiece >= 'A' && destPiece <= 'Z') ||
         (sourcePiece >= 'a' && sourcePiece <= 'z' && destPiece >= 'a' && destPiece <= 'z'))) {
        return false;
    }
    
    return true;
}

// Move a piece on the board
void movePiece(GameState* game, int r1, int c1, int r2, int c2) {
    char capturedPiece = game->board[r2][c2];
    
    // Track captured pieces
    if (capturedPiece != EMPTY) {
        int captureIndex = isPieceOwner(capturedPiece, WHITE) ? 1 : 0;
        game->capturedPieces[captureIndex][game->captureCount[captureIndex]++] = capturedPiece;
        printf("\nCapture: %c at position %c%d\n", 
               capturedPiece, 'a' + c2, BOARD_SIZE - r2);
    }
    
    // Move the piece
    game->board[r2][c2] = game->board[r1][c1];
    game->board[r1][c1] = EMPTY;
    
    printf("\nMove: %c from %c%d to %c%d\n", 
           game->board[r2][c2], 'a' + c1, BOARD_SIZE - r1, 'a' + c2, BOARD_SIZE - r2);
}

// Generate all possible moves for a pawn
void generatePawnMoves(GameState* game, int r1, int c1) {
    int direction = (game->board[r1][c1] == 'P') ? -1 : 1;  // Direction based on piece color
    
    // Forward move
    if (isValidPosition(r1 + direction, c1) && game->board[r1 + direction][c1] == EMPTY) {
        game->possibleMoves[game->moveCount++] = ((r1 + direction) * 10) + c1;
        
        // Double forward move from starting position
        if ((r1 == 1 && direction == 1) || (r1 == 6 && direction == -1)) {
            if (game->board[r1 + 2 * direction][c1] == EMPTY) {
                game->possibleMoves[game->moveCount++] = ((r1 + 2 * direction) * 10) + c1;
            }
        }
    }
    
    // Diagonal captures
    for (int dc = -1; dc <= 1; dc += 2) {
        if (isValidPosition(r1 + direction, c1 + dc)) {
            char targetPiece = game->board[r1 + direction][c1 + dc];
            if (targetPiece != EMPTY && 
                ((game->board[r1][c1] >= 'A' && game->board[r1][c1] <= 'Z' && targetPiece >= 'a' && targetPiece <= 'z') ||
                 (game->board[r1][c1] >= 'a' && game->board[r1][c1] <= 'z' && targetPiece >= 'A' && targetPiece <= 'Z'))) {
                game->possibleMoves[game->moveCount++] = ((r1 + direction) * 10) + (c1 + dc);
            }
        }
    }
    
    // TODO: Add en passant and promotion logic
}

// Generate all possible moves for a rook
void generateRookMoves(GameState* game, int r1, int c1) {
    const int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // Right, Down, Left, Up
    
    for (int d = 0; d < 4; d++) {
        for (int step = 1; step < BOARD_SIZE; step++) {
            int r2 = r1 + directions[d][0] * step;
            int c2 = c1 + directions[d][1] * step;
            
            if (!isValidPosition(r2, c2)) {
                break;  // Out of board boundaries
            }
            
            if (game->board[r2][c2] == EMPTY) {
                game->possibleMoves[game->moveCount++] = (r2 * 10) + c2;
            } else {
                // Check if capture is possible
                if (isValidMove(game, r1, c1, r2, c2)) {
                    game->possibleMoves[game->moveCount++] = (r2 * 10) + c2;
                }
                break;  // Cannot move further in this direction
            }
        }
    }
}

// Generate all possible moves for a knight
void generateKnightMoves(GameState* game, int r1, int c1) {
    const int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    
    for (int i = 0; i < 8; i++) {
        int r2 = r1 + knightMoves[i][0];
        int c2 = c1 + knightMoves[i][1];
        
        if (isValidMove(game, r1, c1, r2, c2)) {
            game->possibleMoves[game->moveCount++] = (r2 * 10) + c2;
        }
    }
}

// Generate all possible moves for a bishop
void generateBishopMoves(GameState* game, int r1, int c1) {
    const int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};  // Diagonals
    
    for (int d = 0; d < 4; d++) {
        for (int step = 1; step < BOARD_SIZE; step++) {
            int r2 = r1 + directions[d][0] * step;
            int c2 = c1 + directions[d][1] * step;
            
            if (!isValidPosition(r2, c2)) {
                break;  // Out of board boundaries
            }
            
            if (game->board[r2][c2] == EMPTY) {
                game->possibleMoves[game->moveCount++] = (r2 * 10) + c2;
            } else {
                // Check if capture is possible
                if (isValidMove(game, r1, c1, r2, c2)) {
                    game->possibleMoves[game->moveCount++] = (r2 * 10) + c2;
                }
                break;  // Cannot move further in this direction
            }
        }
    }
}

// Generate all possible moves for a queen
void generateQueenMoves(GameState* game, int r1, int c1) {
    // Queen moves like a rook and bishop combined
    generateRookMoves(game, r1, c1);
    generateBishopMoves(game, r1, c1);
}

// Generate all possible moves for a king
void generateKingMoves(GameState* game, int r1, int c1) {
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;  // Skip current position
            
            int r2 = r1 + dr;
            int c2 = c1 + dc;
            
            if (isValidMove(game, r1, c1, r2, c2)) {
                game->possibleMoves[game->moveCount++] = (r2 * 10) + c2;
            }
        }
    }
    
    // TODO: Add castling logic
}

// Generate all possible moves for a selected piece
void generateMoves(GameState* game, int r1, int c1) {
    game->moveCount = 0;  // Reset move counter
    
    switch (game->board[r1][c1]) {
        case 'p': case 'P':
            generatePawnMoves(game, r1, c1);
            break;
        case 'r': case 'R':
            generateRookMoves(game, r1, c1);
            break;
        case 'h': case 'H':
            generateKnightMoves(game, r1, c1);
            break;
        case 'c': case 'C':
            generateBishopMoves(game, r1, c1);
            break;
        case 'q': case 'Q':
            generateQueenMoves(game, r1, c1);
            break;
        case 'k': case 'K':
            generateKingMoves(game, r1, c1);
            break;
    }
}

// Simplified check detection (checks if the king is under attack)
bool isKingInCheck(GameState* game, int player) {
    // Find the king's position
    int kingRow = -1, kingCol = -1;
    char kingPiece = (player == WHITE) ? 'K' : 'k';
    
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (game->board[r][c] == kingPiece) {
                kingRow = r;
                kingCol = c;
                break;
            }
        }
        if (kingRow != -1) break;
    }
    
    if (kingRow == -1) return false;  // King not found (shouldn't happen in a valid game)
    
    // Check if any opponent piece can capture the king
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            char piece = game->board[r][c];
            if (piece != EMPTY && isPieceOwner(piece, player == WHITE ? BLACK : WHITE)) {
                // Generate moves for this opponent piece
                GameState tempGame = *game;
                generateMoves(&tempGame, r, c);
                
                // Check if any move can capture the king
                for (int i = 0; i < tempGame.moveCount; i++) {
                    int moveR = tempGame.possibleMoves[i] / 10;
                    int moveC = tempGame.possibleMoves[i] % 10;
                    
                    if (moveR == kingRow && moveC == kingCol) {
                        return true;  // King is in check
                    }
                }
            }
        }
    }
    
    return false;  // King is not in check
}

// Handle player's turn
void playerTurn(GameState* game, int player) {
    printf("\nPlayer %d's turn (%s)\n", player, player == WHITE ? "White" : "Black");
    
    int r1, c1, r2, c2;
    char col1, row1, col2, row2;
    
    while (1) {
        // Get source piece
        printf("\nSelect a piece (e.g., e2): ");
        col1 = getch();
        row1 = getch();
        printf("%c%c\n", col1, row1);
        
        if (col1 < 'a' || col1 > 'h' || row1 < '1' || row1 > '8') {
            printf("Invalid input. Use algebraic notation (e.g., e2).\n");
            continue;
        }
        
        c1 = col1 - 'a';
        r1 = BOARD_SIZE - (row1 - '0');
        
        // Check if selected piece belongs to current player
        if (game->board[r1][c1] == EMPTY || !isPieceOwner(game->board[r1][c1], player)) {
            printf("Not your piece or empty square. Try again.\n");
            continue;
        }
        
        // Generate possible moves
        generateMoves(game, r1, c1);
        
        if (game->moveCount == 0) {
            printf("No valid moves for this piece. Try another piece.\n");
            continue;
        }
        
        // Display possible moves
        printf("\nPossible moves:\n");
        for (int i = 0; i < game->moveCount; i++) {
            int moveR = game->possibleMoves[i] / 10;
            int moveC = game->possibleMoves[i] % 10;
            printf("%d: %c%d\n", i + 1, 'a' + moveC, BOARD_SIZE - moveR);
        }
        
        // Get destination
        printf("\nEnter move number or select another piece (0): ");
        int moveIndex;
        scanf("%d", &moveIndex);
        
        if (moveIndex == 0) {
            continue;  // Select another piece
        }
        
        if (moveIndex < 1 || moveIndex > game->moveCount) {
            printf("Invalid move number. Try again.\n");
            continue;
        }
        
        // Apply the selected move
        int movePos = game->possibleMoves[moveIndex - 1];
        r2 = movePos / 10;
        c2 = movePos % 10;
        
        // Move the piece
        movePiece(game, r1, c1, r2, c2);
        break;
    }
}

// Save the game to a file
void saveGame(GameState* game, int currentPlayer) {
    FILE* file = fopen("chess_save.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }
    
    fwrite(game, sizeof(GameState), 1, file);
    fwrite(&currentPlayer, sizeof(int), 1, file);
    
    fclose(file);
    printf("Game saved successfully.\n");
}

// Load a game from a file
bool loadGame(GameState* game, int* currentPlayer) {
    FILE* file = fopen("chess_save.dat", "rb");
    if (file == NULL) {
        printf("No saved game found.\n");
        return false;
    }
    
    fread(game, sizeof(GameState), 1, file);
    fread(currentPlayer, sizeof(int), 1, file);
    
    fclose(file);
    printf("Game loaded successfully.\n");
    return true;
}
