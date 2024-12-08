#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct {
  int player;
  int computer;
  int draw;
} Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void input_difficulty();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();

int main() {
  srand(time(NULL));
  int choice;
  input_difficulty();
  do {
    play_game();
    printf("\nScore after this game:\n");
    printf("Player: %d | Computer: %d | Draws: %d\n", score.player, score.computer, score.draw);
    printf("\nPress 1 to play again and 0 to exit: ");
    scanf("%d", &choice);
  } while (choice == 1);
  printf("\nThanks for playing :)\n");
}

void input_difficulty() {
  while (1) {
    printf("\nWelcome to the TIC-TAC-TOE game\n");
    printf("\nSelect difficulty level:");
    printf("\n1. Free Fire Level");
    printf("\n2. God mode");
    printf("\nEnter your choice: ");
    if (scanf("%d", &difficulty) != 1 || (difficulty != 1 && difficulty != 2)) {
      while(getchar() != '\n');
      printf("\nIncorrect choice!\n");
    } else {
      if (difficulty == 2) {
        printf("\nWelcome to my dark world, let's play...\n");
      }
      else if(difficulty == 1){
        printf("\nI'm on! Be a superhero with a heart\n");
        
      }
      break;
    }
  };
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
  printf("\n");

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf(" %c ", board[i][j]);
      if (j < BOARD_SIZE - 1) {
        printf("|");
      }
    }
    if (i < BOARD_SIZE - 1) {
      printf("\n---+---+---");
    }
    printf("\n");
  }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
  return !(row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE || board[row][col] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
  int row, col;
  do {
    printf("\nReady Player One?\n");
    printf("Enter the row and column: ");
    if (scanf("%d %d", &row, &col) != 2) {
      while(getchar() != '\n');
      printf("Invalid input!\n");
      continue;
    }
    row--; col--;
  } while (!is_valid_move(board, row, col));

  board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        if (check_win(board, O)) {
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = X;
        if (check_win(board, X)) {
          board[i][j] = O;
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  if (difficulty == 2) {
    if (board[1][1] == ' ') {
      board[1][1] = O;
      return;
    }

    int corner[4][2] = {
      {0, 0}, {0, 2}, {2, 0}, {2, 2}
    };
    for (int i = 0; i < 4; i++) {
      if (board[corner[i][0]][corner[i][1]] == ' ') {
        board[corner[i][0]][corner[i][1]] = O;
        return;
      }
    }
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        return;
      }
    }
  }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
      return 1;
    }
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
      return 1;
    }
  }

  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
      (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
    return 1;
  }
  return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        return 0;
      }
    }
  }
  return 1;
}

void play_game() {
  char board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
  };
  char current_player = rand() % 2 == 0 ? X : O;

  int game_started = 0;
  
  while (1) {
    if (current_player == X) {
      if (!game_started) {
        print_board(board);
        game_started = 1;
      }
      player_move(board);
      print_board(board);
      if (check_win(board, X)) {
        score.player++;
        printf("7 crore!\n");
        break;
      }
      current_player = O;
    } else {
      computer_move(board);
      print_board(board);
      printf("Computer has made its move!\n");
      if (check_win(board, O)) {
        score.computer++;
        print_board(board);
        printf("Computer wins...\n");
        break;
      }
      current_player = X;
    }

    if (check_draw(board)) {
      score.draw++;
      print_board(board);
      printf("\nIt's a draw!\n");
      break;
    }
  }
}