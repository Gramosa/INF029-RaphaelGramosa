// Q7 Jogo da velha
// gcc RaphaelGramosa-20232160031-Q7.c -o jogo && ./jogo
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3
#define G "\033[32m"
#define W "\033[0m"

typedef struct Board{
  char B[SIZE][SIZE];
  char column_tag;
  char line_tag;
} Board;

typedef struct Point{
  int x;
  int y;
} Point;

bool has_char(const char *str, const char target){
  while(*str != '\0'){
    if(*str == target){
      return true;
    }
    str++;
  }

  return false;
}

char customToUpper(char c){
  if(c >= 'a' && c <= 'z'){
    c -= 32;
  }
  return c;
}

// Retirada do projeto escola
// Utilizada para limpar o buffer (stdin) e remover possiveis quebra de linha deixadas pelo scanf, e que podem ser lidas erroneamente pelo fgets
// Usar apos um scanf, ou antes de um fgets. Usar APENAS caso tenha certeza que um \n foi deixado no buffer
void cleanStream(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// Retirada do projeto escola
// Utilizada para remover a quebra de linha (\n) da string, que eh registrada pelo fgets
// Usar apos o uso do fgets
void cleanNewLine(char *string){
  int i = 0;
  while(string[i] != '\0'){
    if(string[i] == '\n'){
      string[i] = '\0';
    }
    i++;
  }
}

void show_board(Board *board){
  printf("  ");
  for(int i = 0; i < SIZE; i++){
    printf("| %c ", board->column_tag + i);
  }
  printf("\n");
  for(int i = 0; i < SIZE; i++){
    printf("--------------\n");
    printf("%c ", board->line_tag + i);
    for(int j = 0; j < SIZE; j++){
      printf("| %c ", board->B[i][j]);
    }
    printf("\n");
  }
}

void init_board(Board *board){
  board->column_tag = '1';
  board->line_tag = 'A';
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      board->B[i][j] = ' ';
    }
  }
}

int convert_axis_to_pos(const char first, const char axis){
  int pos = (int)(axis - first);
  if(pos < 0 || pos > SIZE - 1){
    return -1;
  }
  return pos;
}

Point create_point_from_input(Board *board){
  Point p = {-1, -1};
  char choice[4]; //2 + 1 \n + 1 \0
  fgets(choice, 4, stdin);
  if(!has_char(choice, '\n')){
    printf("A escolha deve ter apenas 2 caracteres (linha e coluna)\n");
    cleanStream();
    return p;
  }
  //cleanNewLine(choice);
  p.x = convert_axis_to_pos(board->line_tag, customToUpper(choice[0]));
  p.y = convert_axis_to_pos(board->column_tag, choice[1]);
  if(p.x == -1){
    printf("A linha deve estar entre A e C, valor '%c' eh invalido\n", choice[0]);
  }
  if(p.y == -1){
    printf("A coluna deve estar entre 1 e 3, valor '%c' eh invalido\n", choice[1]);
  }
  return p;
}

bool place_on_board(Board *board, Point point, const char item){
  if(point.x == -1 || point.y == -1){
    printf("Ponto invalido\n");
    return false;
  }
  board->B[point.x][point.y] = item;
  return true;
}

bool has_winner(Board *board, Point last_pos_played){
  int lin = last_pos_played.x;
  int col = last_pos_played.y;
  char item = board->B[lin][col];
  //diagonal principal
  if(lin - col == 0){
    int i;
    for(i = 0; i < SIZE; i++){
      if(item != board->B[i][i]){
        break;
      }
    }
    if(i == SIZE){
      return true;
    }
  }
  //diagonal secundaria
  if(lin + col == 2){
    int j;
    for(j = 0; j < SIZE; j++){
      if(item != board->B[j][SIZE - j - 1]){
        break;
      }
    }
    if(j == SIZE){
      return true;
    }
  }
  //vertical (k) e horizontal (l)
  int k;
  for(k = 0; k < SIZE; k++){
    if(item != board->B[k][col]){
      break;
    }
  }
  if(k == SIZE){
    return true;
  }
  
  int l;
  for(l = 0; l < SIZE; l++){
    if(item != board->B[lin][l]){
      break;
    }
  }
  if(l == SIZE){
    return true;
  }
  
  return false;
}

int main(){
  Board board;
  Point p = {-1, -1};
  int actual_player = 1;
  char item = 'X';
  int number_of_choices = 0;
  init_board(&board);
  do{
    show_board(&board);
    do{
      printf("Jogador %d, jogue: ", actual_player);
      p = create_point_from_input(&board);
    }while(p.x == -1 || p.y == -1);
    if(board.B[p.x][p.y] != ' '){
      printf("Posicao ja jogada, selecione outra posição!\n");
      continue;
    }
    place_on_board(&board, p, item);
    if(actual_player == 1){
      item = 'O';
      actual_player = 2;
    }
    else{
      item = 'X';
      actual_player = 1;
    }
    system("clear||cls");
    number_of_choices++;
  }while(!has_winner(&board, p) && number_of_choices < 9);
  
  printf("FIM DE JOGO\n");
  if(number_of_choices == 9){
    printf("DEU VELHA!\n");
  }
  else if(actual_player == 1){
    printf("O jogador vencedor foi o 2\n");
  }
  else{
    printf("O jogador vencedor foi o 1\n");
  }
}
