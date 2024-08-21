#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

EstAux* vetorPrincipal[TAM] = {NULL};

EstAux* create_est_aux(int size){
  EstAux* e = malloc(sizeof(EstAux));
  if(e == NULL){
    return NULL;
  }
  e->array = malloc(size * sizeof(int));
  e->pos = -1;
  e->size = size;

  return e;
}

void destroy_est_aux(EstAux* e){
  if(e != NULL){
    free(e->array);
    free(e);
  }
}

int is_empty(EstAux e){
  return e.pos == -1;
}

int is_full(EstAux e){
  return e.pos == e.size - 1;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;
  
  if(tamanho < 1){
    return TAMANHO_INVALIDO;
  }
  
  if(posicao < 0 || posicao >= TAM){
    return POSICAO_INVALIDA;
  }
  
  if(vetorPrincipal[posicao] != NULL){
    return JA_TEM_ESTRUTURA_AUXILIAR;
  }

  EstAux *e = create_est_aux(tamanho);

  if(e == NULL){
    return SEM_ESPACO_DE_MEMORIA;
  }

  vetorPrincipal[posicao] = e;
  
  return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;
  
  if(posicao < 0 || posicao >= TAM){
    return POSICAO_INVALIDA;
  }

  EstAux* e = vetorPrincipal[posicao];
  
  if(e == NULL){
    return SEM_ESTRUTURA_AUXILIAR;
  }
  
  if(is_full(*e)){
    return SEM_ESPACO;
  }

  e->array[++e->pos] = valor;
  
  return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;
  
  if(posicao < 0 || posicao >= TAM){
    return POSICAO_INVALIDA;
  }

  EstAux* e = vetorPrincipal[posicao];

  if(e == NULL){
    return SEM_ESTRUTURA_AUXILIAR;
  }

  if(is_empty(*e)){
    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  e->pos--;
  
  return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;
  
  if(posicao < 0 || posicao >= TAM){
    return POSICAO_INVALIDA;
  }

  EstAux* e = vetorPrincipal[posicao];

  if(e == NULL){
    return SEM_ESTRUTURA_AUXILIAR;
  }

  if(is_empty(*e)){
    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  int i = 0;
  int was_found = 0;
  while(i <= e->pos){
    if(was_found){
      e->array[i-1] = e->array[i];
    }
    else if(e->array[i] == valor){
      was_found = 1;
    }
    i++;
  }
  if(was_found){
    e->pos--;
    return SUCESSO;
  }
  else{
    return NUMERO_INEXISTENTE;
  }
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;
  
  if (posicao < 0 || posicao >= 10)
  {
    return POSICAO_INVALIDA;
  }

  return SUCESSO;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;

  if(posicao < 0 || posicao >= TAM){
    return POSICAO_INVALIDA;
  }

  EstAux* e = vetorPrincipal[posicao];

  if(e == NULL){
    return SEM_ESTRUTURA_AUXILIAR;
  }

  int i = 0;
  while(i <= e->pos){
    vetorAux[i] = e->array[i];
    i++;
  }

  return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
  int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
  if(retorno != SUCESSO){
    return retorno;
  }

  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;

  EstAux* e = vetorPrincipal[posicao];  

  for(int i = 0; i <= e->pos; i++){
    for(int j = i + 1; j <= e->pos; j++){
      if(vetorAux[j] < vetorAux[i]){
        int temp = vetorAux[i];
        vetorAux[i] = vetorAux[j];
        vetorAux[j] = temp;
      }
    }
  }

  return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
  int *backup = vetorAux;
  for(int i = 0; i < TAM; i++){
    EstAux* e = vetorPrincipal[i];
    if(e != NULL && !is_empty(*e)){
      getDadosEstruturaAuxiliar(i+1, vetorAux); //j+1 por causa do posicao-- da funcao
      vetorAux += e->pos + 1;
    }
  }
  if(backup == vetorAux){
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  }
  else{
    return SUCESSO;
  }
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
  int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
  if(retorno != SUCESSO){
    return retorno;
  }

  int total_size = 0;
  for(int i = 0; i < TAM; i++){
    EstAux* e = vetorPrincipal[i];
    if(e != NULL && !is_empty(*e)){
      total_size += e->pos + 1;
    }
  }

  for(int j = 0; j <= total_size; j++){
    for(int k = j + 1; k <= total_size; k++){
      if(vetorAux[k] < vetorAux[j]){
        int temp = vetorAux[j];
        vetorAux[j] = vetorAux[k];
        vetorAux[k] = temp;
      }
    }
  }

  return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;

  if(posicao < 0 || posicao >= TAM){
    return POSICAO_INVALIDA;
  }

  EstAux* e = vetorPrincipal[posicao];

  if(e == NULL){
    return SEM_ESTRUTURA_AUXILIAR;
  }

  int new_size = e->size + novoTamanho;
  
  if(new_size < 1){
    return NOVO_TAMANHO_INVALIDO;
  }

  int *temp = realloc(e->array, new_size * sizeof(int));
  if(temp == NULL){
    return SEM_ESPACO_DE_MEMORIA;
  }

  e->array = temp;
  if(new_size < e->size){
    e->pos = new_size -1;
  }
  e->size = new_size;
  
  return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    xPOSICAO_INVALIDA - posição inválida
    xSEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    xESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
  //para converter da numeracao que comeca em 1, para comecar em 0
  posicao--;

  if(posicao < 0 || posicao >= TAM){
    return POSICAO_INVALIDA;
  }

  EstAux* e = vetorPrincipal[posicao];

  if(e == NULL){
    return SEM_ESTRUTURA_AUXILIAR;
  }

  if(is_empty(*e)){
    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  return e->pos + 1;
}

No* create_no(int value){
  No* no = malloc(sizeof(No));
  no->conteudo = value;
  no->prox = NULL;

  return no;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No* montarListaEncadeadaComCabecote()
{
  No* cabecote = create_no(0);
  No* temp = NULL;
  
  for(int i = 0; i < TAM; i++){
    EstAux* e = vetorPrincipal[i];
    if(e != NULL && !is_empty(*e)){
      int j = 0;
      while(j <= e->pos){
        int value = e->array[j];
        // printf("value = %d\n", value);
        if(temp == NULL){
          temp = create_no(value);
          cabecote->prox = temp;
        }
        else{
          temp->prox = create_no(value);
          temp = temp->prox;
        }
        j++;
      }
    }
  }
  
  return cabecote->prox != NULL ? cabecote->prox : NULL;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
  int i = 0;
  while(inicio != NULL){
    vetorAux[i] = inicio->conteudo;
    inicio = inicio->prox;
    i++;
  }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
  if(inicio != NULL){
    while(*inicio != NULL){
      No *temp = *inicio;
      *inicio = (*inicio)->prox;
      free(temp);
    }
  }
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
  for(int i = 0; i < TAM; i++){
    destroy_est_aux(vetorPrincipal[i]);
  }
}