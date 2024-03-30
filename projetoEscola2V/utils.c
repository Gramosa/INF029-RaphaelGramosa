#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "utils.h"

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

// Utilizada para limpar o buffer (stdin) e remover possiveis quebra de linha deixadas pelo scanf, e que podem ser lidas erroneamente pelo fgets
// Usar apos um scanf, ou antes de um fgets. Usar APENAS caso tenha certeza que um \n foi deixado no buffer
void cleanStream(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// Versao customizada do pow, mais limitado ja que aceita apenas expoentes inteiros e positivos
double customPow(double base, unsigned int exp){
  double value = 1;
  for(int i = 0; i < exp; i++){
    value *= base;
  }
  return value;
}

// utilizada para converter uma regiao de uma string para inteiro, retorna -1 caso a regiao da string contenha qualquer caractere que nao seja um numero
int convertStrToInt(const char* array, int start, int end){
  int value = 0;
  for(int i = end; i >= start; i--){
    int equivalentInt = array[i] - '0';
    if(equivalentInt < 0 || equivalentInt > 9){
      return -1;
    }
    // end - i eh sempre > 0
    value += equivalentInt * customPow(10, end - i);
  }
  return value;
}

// Versao customizada do strlen, simplismente retorna o tamanho da string finalizada em \0
unsigned int customStrlen(const char *string){
  int i = 0;
  while(string[i] != '\0'){
    i++;
  }
  return i;
}

// Versao customizada do strcmp, retorna 0 se string1 == string2, <0 se string1 < string2, e >0 se string1 > string2
int customStrcmp(const char *string1, const char *string2){
  // Primeiro nome
  int i = 0;
  while(string1[i] != '\0' && string2[i] != '\0'){
    if(string1[i] != string2[i]){
      return string1[i] - string2[i];
    }
    i++;
  }
  return string1[i] - string2[i];
}

char customToLower(char letter){
  if(letter >= 'A' && letter <= 'Z'){
    return letter + 32;
  }
  return letter;
}

// Versao customizada do strstr, retorna o endereco da primeira ocorrencia de string2 em string1, ou NULL caso nao exista. IMPORTANTE: Essa versão NÃO é case sensitive
char* customStrstr(const char *string1, const char *string2){
  int len1 = customStrlen(string1);
  int j = 0;
  for(int i = 0; i < len1; i++){
    if(customToLower(string1[i]) == customToLower(string2[j])){
      j++;
    }
    else{
      j = 0;
    }
    if(string2[j] == '\0'){
      return (char*)string1 + i - (j - 1);
    }
  }
  return NULL;
}

// Imprime a data atual no formato dd/mm/yyyy
void showTime(){
    time_t t = time(NULL);
    struct tm timeInfo = *localtime(&t);
    printf("Data Atual: %02d/%02d/%04d\n", timeInfo.tm_mday, timeInfo.tm_mon + 1, timeInfo.tm_year + 1900);
}

int getActualMonth(){
  time_t t = time(NULL);
  struct tm timeInfo = *localtime(&t);
  return timeInfo.tm_mon + 1;
}

bool validateName(char* name){
  if(name[0] == '\0'){
    printf("O nome não pode ser vazio!\n");
    return false;
  }
  int i = 0;
  bool found_letter = false;
  while(name[i] != '\0'){
    if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')){
      if(!found_letter && name[i] >= 'a'){
        name[i] -= 32;
      }
      found_letter = true;
    }
    else if(name[i] == ' '){
      if(!found_letter){
        printf("Nome invalido, espaco em branco encontrado em local indevido!\n");
        return false;
      }
      found_letter = false;
    }
    else{
      printf("Nome invalido, caracter invalido encontrado (Deve ser A-Z, a-z ou espaco)!\n");
      return false;
    }

    i++;
  }

  return true;
}