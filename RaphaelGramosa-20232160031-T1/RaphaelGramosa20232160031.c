// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Raphael de Jesus Gramosa
//  email: rafagramosa28@gmail.com
//  Matrícula: 20232160031
//  Semestre: 2024.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "RaphaelGramosa20232160031.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

int customIsNum(const char c){
  return c >= '0' && c <= '9';
}

// Adaptada da funcao 'validadeBirth' usada no projeto escola
DataQuebrada validateDate(DataQuebrada dq){
  int daysByMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
  // Valida o ano ?
  
  // Valida o mes
  if(dq.iMes < 1 || dq.iMes > 12){
    // printf("Mês invalido!\n");
    dq.valido = 0;
    return dq;
  }
  int lastTwoDigitsYear = dq.iAno % 100;
  if(lastTwoDigitsYear == 0){
    if(dq.iAno % 400 == 0){
      daysByMonth[1] = 29;
    }
  }
  else if(lastTwoDigitsYear % 4 == 0){
    daysByMonth[1] = 29;
  }
  // Valida o dia
  if(dq.iDia < 1 || dq.iDia > daysByMonth[dq.iMes - 1]){
    // printf("Dia invalido!\n");
    dq.valido = 0;
    return dq;
  }
  
  dq.valido = 1;
  return dq;
}

// Funcao um pouco modificada da original
DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  
  int i;
  for (i = 0; customIsNum(data[i]) && i < 2; i++){
    sDia[i] = data[i];
  }
  if(i > 0 && data[i] == '/'){
    sDia[i] = '\0';
  }
  else{
    dq.valido = 0;
    return dq;
  }
  i++; //anda 1 cada para pular a barra
  int j;
  for(j = 0; customIsNum(data[i]) && j < 2; j++, i++){
    sMes[j] = data[i];
  }
  if(j > 0 && data[i] == '/'){
    sMes[j] = '\0';
  }
  else{
    dq.valido = 0;
    return dq;
  }

  i++; //anda 1 cada para pular a barra
  int k;
  for(k = 0; customIsNum(data[i]) && k < 4; k++, i++){
    sAno[k] = data[i];
  }

  if(k > 0 && data[i] == '\0'){
    sAno[k] = '\0';
  }
  else{
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

  // Para a questão se o ano estiver com 2 digitos, se considera como 2000 + numero
  if(dq.iAno < 100){
    dq.iAno += 2000;
  }
  
  dq.valido = 1;

  return dq;
}



/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]){
  DataQuebrada dq = quebraData(data);
  if(dq.valido == 1){
    dq = validateDate(dq);
  }
  return dq.valido;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{ 
  DiasMesesAnos dma;
  DataQuebrada dqini, dqfim;
  dqini = validateDate(quebraData(datainicial));
  dqfim = validateDate(quebraData(datafinal));
  if(dqini.valido == 0){
    dma.retorno = 2;
    return dma;
  }
  else if(dqfim.valido == 0){
    dma.retorno = 3;
    return dma;
  }
  
  
    // //calcule os dados e armazene nas três variáveis a seguir
    // DiasMesesAnos dma;

    // if (q1(datainicial) == 0){
    //   dma.retorno = 2;
    //   return dma;
    // }else if (q1(datafinal) == 0){
    //   dma.retorno = 3;
    //   return dma;
    // }else{
    //   //verifique se a data final não é menor que a data inicial

    //   //calcule a distancia entre as datas


    //   //se tudo der certo
    //   dma.retorno = 1;
    //   return dma;

    // }
  dma.retorno = 1;
  return dma;
}

char customToUpper(char c){
  if(c >= 'a' && c <= 'z'){
    c -= 32;
  }
  return c;
}

int count_char(char *str, const char c){
  int count = 0;
  while(*str != '\0'){
    if(*str == c){
      count++;
    }
    str++;
  }
  return count;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
  if(!isCaseSensitive){
    char temp_txt[250];
    c = customToUpper(c);
    int i = 0;
    while(texto[i] != '\0'){
      temp_txt[i] = customToUpper(texto[i]);
      i++;
    }
    temp_txt[i] = '\0';
    return count_char(temp_txt, c);
  }

    return count_char(texto, c);
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int count = 0;
  int pos_count = 0;
  int i = 1;
  while(*strTexto != '\0'){
    char *temp_txt = strTexto;
    char *temp_busca = strBusca;
    int first = i;
    int last = i;
    // if(*strTexto == -61){
    //   strTexto++;
    // }
    while(*temp_busca != '\0'){
      if(*temp_txt != *temp_busca){
        break;
      }
      temp_txt++;
      temp_busca++;
      last++;
    }
    if(*temp_busca == '\0'){
      posicoes[pos_count++] = first;
      posicoes[pos_count++] = last-1;
      count++;
    }

    strTexto++;
    i++;
  }
  return count;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int new_num = 0;
  while(num != 0){
    new_num *= 10;
    new_num += num % 10;
    num /= 10;
  }
  return new_num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
  if(numerobase == numerobusca){
    return 1;
  }
  int count = 0;
  while(numerobase != 0){
    int temp_base = numerobase;
    int temp_busca = numerobusca;
    while(temp_base % 10 == temp_busca % 10 && temp_busca != 0){
      temp_base /= 10;
      temp_busca /= 10;
    }
    if(temp_busca == 0){
      count++;
    }
    numerobase /= 10;
  }
  return count;
}