// Q8 Batalha Naval
// gcc RaphaelGramosa-20232160031-Q8.c -o jogo1 && ./jogo1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 10
#define N_SHIPS 10
#define MAX_SIZE 4

#define G "\033[32m"
#define W "\033[0m"

typedef struct Point{
  int x;
  int y;
} Point;

typedef struct Board{
  char B[SIZE][SIZE];
  char column_tag;
  char line_tag;
  int intact_pos;
} Board;

typedef struct Ship{
  Point pos;
  bool on_board;
  int direction; //0 horizontal, 1 vertical
  //int status[MAX_SIZE] //0 intacto, 1 danificado
  int size;
} Ship;

bool has_char(const char *str, const char target){
  while(*str != '\0'){
    if(*str == target){
      return true;
    }
    str++;
  }

  return false;
}

bool is_num(const char *str){
    while(*str != '\0'){
    if(!(*str >= '0' && *str <= '9')){
      return false;
    }
    str++;
  }

  return true;
}

int count_digits(int value){
  if(value == 0) return 1;

  int digits = 0;
  while(value != 0){
    digits++;
    value /= 10;
  }
  return digits;
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

void show_ship(const Ship ship){
  for(int i = 0; i < ship.size; i++){
    printf("N");
  }
  printf(" |%s|", (ship.direction == 0) ? "horizontal" : "vertical");
  if(ship.pos.x == -1 || ship.pos.y == -1)
    printf(" ???|");
  else
    printf(" (%c, %d)|", ship.pos.x + 'A', ship.pos.y);
  printf(" [%c]", (ship.on_board) ? '#' : ' ');
}

void show_board(const Board *board, bool as_enemy){
  printf("Tabuleiro %s\n", (as_enemy) ? "inimigo" : "aliado");
  printf("   ");
  for(int i = 0; i < SIZE; i++){
    printf("|%c|", board->column_tag + i);
  }
  printf("\n");
  for(int i = 0; i < SIZE; i++){
    printf("%c |", board->line_tag + i);
    for(int j = 0; j < SIZE; j++){
      const char item = board->B[i][j];
      printf("[");
      if(item == 'N' && as_enemy){
        //printf("[ ]");
        printf(" ");
      }
      else{
        //printf("[%c]", item);
        printf("%c", item);
      }
      printf("]");
    }
    printf("\n");
  }
}

void init_board(Board *board){
  board->column_tag = '0';
  board->line_tag = 'A';
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      board->B[i][j] = ' ';
    }
  }
  board->intact_pos = 0;
}

Ship create_ship(int size){
  Ship ship;
  ship.pos = (Point){-1, -1};
  ship.size = size;
  ship.direction = 0;
  ship.on_board = false;
  /*for(int i = 0; i < size; i++){
    ship.status[i] = 0;
  }*/
  return ship;
}

int convert_axis_to_pos(const char first, const char axis){
  int pos = (int)(axis - first);
  if(pos < 0 || pos > SIZE - 1){
    return -1;
  }
  return pos;
}

Point create_point_from_input(const Board *board){
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
    printf("A linha deve estar entre A e J, valor '%c' eh invalido\n", choice[0]);
  }
  if(p.y == -1){
    printf("A coluna deve estar entre 0 e 9, valor '%c' eh invalido\n", choice[1]);
  }
  return p;
}

int bomb_the_board(Board *board, Point point){
  int status; // 0 - posicao invalida, 1 - errou, 2 - acertou
  
  if(point.x == -1 || point.y == -1){
    return 0;
  }
  
  char* item = &board->B[point.x][point.y];
  switch(*item){
    case ' ':
      *item = 'X';
      status = 1;
      break;
    case 'N':
      *item = 'O';
      status = 2;
      board->intact_pos--;
      break;
    case 'O':
    case 'X':
      printf("Posicao ja foi bombardeada\n");
      status = 0;
      break;
  }
  
  return status;
}

bool place_ship_on_board(Board *board, Ship ship){
  if(ship.pos.x == -1 || ship.pos.y == -1){
    printf("Barco com posicao inicial invalida\n");
    return false;
  }

  int end_x = (ship.direction == 0) ? ship.pos.x : ship.pos.x + (ship.size - 1);
  int end_y = (ship.direction == 0) ? ship.pos.y + (ship.size - 1) : ship.pos.y;

  if(end_x >= SIZE || end_y >= SIZE){
    printf("Os limites do barco excedem os limites do tabuleiro\n");
    return false;
  }

  //Esse for aninhado e o seguinte, sempre agem de forma linear, ja que caso end_x > ship.pos.x, o end_y = ship.pos.y e vice-versa
  for(int i = ship.pos.x; i <= end_x; i++){
    for(int j = ship.pos.y; j <= end_y; j++){
    if(board->B[i][j] != ' '){
      printf("O espaco destinado ao barco ja esta ocupado\n");
        return false;
      }
    }
  }

  for(int i = ship.pos.x; i <= end_x; i++){
    for(int j = ship.pos.y; j <= end_y; j++){
      board->B[i][j] = 'N';
    }
  }
  board->intact_pos += ship.size;
  return true;
}

//Funcao nao implementada
bool remove_ship_from_board(Board *board, const Ship ship){
  return true;
}

void place_ships_randomly(Board *board, Ship ships[]){
  srand(time(NULL));

  int i = 0;
  while(i < N_SHIPS){
    if(ships[i].on_board){
      i++;
      continue;
    }
    int x = rand() % 10;
    int y = rand() % 10;
    ships[i].pos = (Point){x, y};
    ships[i].direction = rand() % 2;
    if(place_ship_on_board(board, ships[i])){
      ships[i].on_board = true;
      i++;
    }
  }
  //Uma gambiarra para limpar as tentativas falhas de posicionar o barco
  system("clear");
}

void ship_config_menu(Board * bd, Ship *sp){
  int choice;
  while(true){
    show_board(bd, false);
    show_ship(*sp);
    printf("\n");
    printf("0 - voltar\n");
    printf("1 - adicionar\n");
    //printf("2 - remover\n");
    printf("2 - posicao\n");
    printf("3 - direcao\n");
    printf(">>> ");
    scanf("%d", &choice);
    cleanStream();
    system("clear");
    if(choice == 0){
      break;
    }
    else if(choice == 1){
      if(sp->on_board){
        printf("Barco ja adicionado no tabuleiro!\n");
        continue;
      }
      if(place_ship_on_board(bd, *sp)){
        sp->on_board = true;
        return;
      }
    }
    // else if(choice == 2){
    //   if(!sp->on_board){
    //     printf("Barco nao esta no tabuleiro!\n");
    //     continue;
    //   }
    //   remove_ship_from_board(bd, *sp);
    //   sp->on_board = false;
    // }
    else if(choice == 2){
      if(sp->on_board){
        //printf("Remova o barco antes mudar a posicao\n");
        //continue;
        printf("Nao eh possivel editar um barco que ja foi adicionado.\n");
        break;
      }
      printf("Digite as coordenas do primeiro ponto: ");
      Point p = create_point_from_input(bd);
      if(p.x == -1 || p.y == -1){
        continue;
      }
      sp->pos = p;
    }
    else if(choice == 3){
      if(sp->on_board){
        //printf("Remova o barco antes de mudar a direcao\n");
        //continue;
        printf("Nao eh possivel editar um barco que ja foi adicionado.\n");
        break;
      }
      sp->direction = sp->direction ^ 1; // XOR operacao
    }
    else{
      printf("Opcao invalida!\n");
    }
  }
}

void action_minimenu(Board *bd, Board *enemy_bd){
  int choice;
  while(true){
    printf("1 - Meu tabuleiro (cuidado, o outro jogador nao deve ver)\n");
    printf("2 - Jogar\n");
    printf(">> ");
    scanf("%d", &choice);
    system("clear");
    cleanStream();
    if(choice == 1){
      show_board(bd, false);
    }
    else if(choice == 2){
      Point p = (Point){-1, -1};
      int result = 0;
      //show_board(enemy_bd, true);
      while(true){
        show_board(enemy_bd, true);
        printf("Qual posicao deseja atacar?!\n");
        printf(">> ");
        p = create_point_from_input(enemy_bd);
        result = bomb_the_board(enemy_bd, p);
        system("clear");
        switch(result){
          case 0:
            printf("Digite uma celula valida e vazia!\n");
            break;
          case 1:
            printf("Errou, voce acaba de acertar a agua!\n");
            break;
          case 2:
            printf("Acertou, voce acaba de atingir um navio inimigo\n");
            break;
        }
        //chama duas vezes para mostrar o resultado
        if(result == 1)
          show_board(enemy_bd, true);
        //so vai sair quando errar ou nao tiver mais posicoes validas
        if(enemy_bd->intact_pos == 0 || result == 1){
          return;
        }
      }
    }
  }
}

void board_config_menu(Board *bd, Ship ships[]){
  int ship_value = 0;

  while(true){
    show_board(bd, false);
    printf("Barcos disponiveis\n");
    for(int i = 1; i <= N_SHIPS; i++){
      printf("%d | ", i);
      show_ship(ships[i-1]);
      printf("\n");
    }

    printf("Digite o numero do barco que deseja editar\n");
    printf("(0 - finalizar configuracao)\n");
    printf("(-1 - aleatorio)\n");
    printf(">> ");
    scanf("%d", &ship_value);
    cleanStream();
    system("clear");
    if(ship_value == -1){
      place_ships_randomly(bd, ships);
    }
    else if(ship_value == 0){
      bool can_exit = true;
      for(int i = 0; i < N_SHIPS; i++){
        if(ships[i].on_board == false){
          can_exit = false;
          continue;
        }
      }
      if(can_exit){
        break;
      }
      else{
        printf("Todos os barcos devem ser adicionados ao tabuleiro!\n");
        continue;
      }
    }
    else if(ship_value >= 1 && ship_value <= N_SHIPS){
      ship_config_menu(bd, &ships[ship_value - 1]);
    }
  }
}

int main(){
  //variaveis
  Board bd1, bd2;
  Ship sp1[N_SHIPS], sp2[N_SHIPS];
  //1 ou 2, representando cada jogador
  int actual_player = 0; //valor atualizado muda no loop principal do jogo

  //inicializacao dos tabuleiros
  init_board(&bd1);
  init_board(&bd2);

  //criacao dos barcos
  sp1[0] = create_ship(4);
  sp2[0] = create_ship(4);
  sp1[1] = create_ship(3);
  sp2[1] = create_ship(3);
  int i;
  for(i = 2; i < 5; i++){
    sp1[i] = create_ship(1);
    sp2[i] = create_ship(1);
  }
  for(; i < N_SHIPS; i++){
    sp1[i] = create_ship(2);
    sp2[i] = create_ship(2);
  }

  //Saudacao
  printf("Bem vindo(a) ao jogo batalha naval, vencerá o jogador que bombardear todas as posicoes validas do inimigo primeiro.\n");
  printf("Informacoes importantes:\n");
  printf("1 - Após adicionar um barco a uma posicao valida nao sera possivel remover do tabuleiro.\n");
  printf("2 - A coordenada do ponto para o barco deve ser dada na mesma entrada (linha e coluna). ex: a3 ou A3.\n");
  printf("3 - Para barcos com mais de 1 de tamanho, a coordenada representa a primeira posicao.\n");

  //Posicionar os barcos no tabuleiro
  printf("Jogador 1, posicione os barcos no tabuleiro.\n");
  printf("Jogador 2, feche os olhos.\n");
  board_config_menu(&bd1, sp1);

  printf("Jogador 2, posicione os barcos no tabuleiro.\n");
  printf("Jogador 1, feche os olhos.\n");
  board_config_menu(&bd2, sp2);

  //Jogo
  while(bd1.intact_pos > 0 && bd2.intact_pos > 0){
    actual_player = (actual_player % 2) + 1;
    printf("Jogador %d, sua vez:\n", actual_player);
    if(actual_player == 1){
      action_minimenu(&bd1, &bd2);
    }
    else if(actual_player == 2){
      action_minimenu(&bd2, &bd1);
    }
  }

  //Resultado do jogo
  printf("FIM!, Parabens ao jogador %d pela vitoria", actual_player);

  return 0;
}