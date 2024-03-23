#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "dataBase.h"
#include "utils.h"
#include "person.h"

// utilizada para validar uma data no formato dd/mm/aaaa, retorna true caso a data seja valida, false caso contrario. Caso seja valida escreve a data no parametro birth
// birth deve ter ao menos 3 posicoes, e birthStr ao menos 10 posicoes
bool validateBirth(int* birth, const char* birthStr){
  int daysByMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  //Valida o formato XX/XX/XXXX
  if(birthStr[2] != '/' || birthStr[5] != '/'){
    printf("Digite uma data valida dd/mm/yyyy, formato invalido\n");
    return false;
  }

  int day = convertStrToInt(birthStr, 0, 1);
  int month = convertStrToInt(birthStr, 3, 4);
  int year = convertStrToInt(birthStr, 6, 9);
  if(day == -1 || month == -1 || year == -1){
    printf("Digite uma data valida, caracteres nao numericos encontrados\n");
    return false;
  }
  // Valida o ano
  // O ano eh validado por 
  // Valida o mes
  if(month < 1 || month > 12){
    printf("Mês invalido!\n");
    return false;
  }
  int lastTwoDigitsYear = year % 100;
  if(lastTwoDigitsYear == 0){
    if(year % 400 == 0){
      daysByMonth[1] = 29;
    }
  }
  else if(lastTwoDigitsYear % 4 == 0){
    daysByMonth[1] = 29;
  }
  // Valida o dia
  if(day < 1 || day > daysByMonth[month - 1]){
    printf("Dia invalido!\n");
    return false;
  }

  birth[0] = day;
  birth[1] = month;
  birth[2] = year;
  return true;
}

// Calcula a idade de uma pessoa a partir de uma data de nascimento, se ela for uma idade valida retorna true e guarda o valor em *age, caso contrario retorna false e imprime um erro
// birth deve ter ao menos 3 posicoes
bool validateAge(int *age, const int* birth){
  const int MAX_AGE = 120;
  const int MIN_AGE = 5;

  time_t currentTime = time(NULL);
  struct tm *timeInfo = localtime(&currentTime);

  int temp_age = timeInfo -> tm_year + 1900 - birth[2];

  //checa se o mes do aniversario ja passou ou é o mesmo do aniversario e o dia do aniversario ja passou nessa ordem. Caso contrario, a idade eh decrementada em 1
  if (timeInfo->tm_mon + 1 < birth[1] ||  (timeInfo->tm_mon + 1 == birth[1] && timeInfo->tm_mday < birth[0])){
    temp_age--;
  }

  if(temp_age < MIN_AGE || temp_age > MAX_AGE){
    printf("Idade invalida!\n");
    if(temp_age < 0){
      printf("Idade negativa, impossivel nascer no futuro!\n");
    }
    else if(temp_age < MIN_AGE){
      printf("Idade abaixo do minimo permitido!\n");
    }
    else{
      printf("Idade acima do maximo permitido!\n");
    }
    return false;
  }

  *age = temp_age;
  return true;
}



// Utilizada para validar um cpf, retorna true caso o cpf seja valido. Caso seja invalido imprime um erro e retorna false
bool validateCpf(const char *cpf){
  int num1 = 0, num2 = 0;
  int size = customStrlen(cpf);

  if(size != 11){
    printf("CPF invalido, deve conter 11 digitos\n");  
    return false;
  }

  if(convertStrToInt(cpf, 0, size-1) == -1){
    printf("CPF invalido, digite apenas numeros\n");
    return false;
  }
  //Checa se todos os caracteres de um vetor sao iguais
  int i = 0;
  for (i = 1; i < size; i++){
    if(cpf[i] != cpf[0]){
      break;
    }
  }
  if (i == size) {
    printf("CPF invalido, todos os digitos nao podem ser iguais\n");
    return false;  
  }
  // Nota: Podemos tentar unir a verificacao dos dois digitos verificadores em uma funcao
  //Validação do primeiro dígito: Primeiramente multiplica-se os 9 primeiros dígitos pela sequência decrescente de números de 10 à 2 e soma os resultados.
  for(int j = 0; j < size - 2; j++){
    num1 += convertStrToInt(cpf, j , j) * (10 - j);
  }
  num1 %= 11;
  num1 = (num1 < 2) ? 0 : 11 - num1;
  if(num1 != convertStrToInt(cpf, 9, 9)){
    printf("CPF invalido, primeiro digito verificador invalido\n");
    return false;
  }
  //Validação do segundo dígito: Multiplica-se os 10 primeiros dígitos
  for(int j = 0; j < size - 1; j++){
    num2 += convertStrToInt(cpf, j, j) * (11 - j);
  }
  num2 %= 11;
  num2 = (num2 < 2) ? 0 : 11 - num2;
  if(num2 != convertStrToInt(cpf, 10, 10)){
    printf("CPF invalido, segundo digito verificador invalido\n");
    return false;
  }
  return true;
}

bool validateGender(const char gender){
  const char possible_values[] = "MFmf";
  int i = 0;
  while(possible_values[i] != '\0'){
    if(possible_values[i] == gender){
      return true;
    }
    i++;
  }
  printf("Sexo invalido!\n");
  return false;
}

bool validateRegistration(const int regist){
  if(regist <= 0){
    printf("Matricula invalida!\n");
    return false;
  }
  return true;
}

void getBirth(int* birth){
  // 12 (10 da data, mais 1 do \n e mais 1 do \0)
  char birthStr[12];
  do{
    printf("Digite a data de nascimento no formato dd/mm/aaaa: ");
    fgets(birthStr, 12, stdin);
    cleanNewLine(birthStr);
  }while(!validateBirth(birth, birthStr));
}

void getAgeAndBirth(int* age, int* birth){
  do{
    getBirth(birth);
  }while(!validateAge(age, birth));
}

void setName(char* name){
  do{
    printf("Digite o nome: ");
    fgets(name, MAX_LETTERS, stdin);
    cleanNewLine(name);
  }while(!validateName(name));
}

void setCpf(char* cpf){
  do{
    printf("Digite o CPF: ");
    fgets(cpf, 13, stdin);
    cleanNewLine(cpf);
  }while(!validateCpf(cpf));
}

void setGender(char* gender){
  do{
    printf("Digite o sexo (M/F): ");
    scanf(" %c", gender);
  } while(!validateGender(*gender));
  cleanStream();
  // Converte para maiusculo
  if(*gender >= 'a'){
    *gender -= 32;
  }
}

void getRegistration(int* regist){
  do{
    printf("Digite o numero da matricula: ");
    scanf("%d", regist);
  } while(!validateRegistration(*regist));
  cleanStream();
}

Person* getPersonByRegist(const Person* persons, const int actualSize, const int regist){
  for(int i = 0; i < actualSize; i++){
    if(persons[i].regist == regist){
      return (Person *)&persons[i];
    }
  }
  return NULL;
}

// Cadastrar
// utilizada para criar um struct do tipo Person, e preencher seus campos com os dados fornecidos pelo usuario.
Person createPerson(Person* persons, int* actualSize){
  Person person;
  printf("=========================================\n");
  printf("|          Cadastro de Pessoa           |\n");
  printf("=========================================\n");
  cleanStream();
  setName(person.name);
  do{
    getRegistration(&person.regist);
    if(getPersonByRegist(persons, *actualSize, person.regist) != NULL){
      printf("Numero de matricula ja cadastrado!\n");
    }
    else{
      break;
    }
  }while(true);
  getAgeAndBirth(&person.age, person.birth);
  setCpf(person.cpf);
  setGender(&person.gender);
  printf("Cadastrado com sucesso!\n");
  return person;
}

//Utilizada para adicionar um struct do tipo Person a um vetor dado
void addPerson(Person* persons, int* actualSize, int maxSize){
  if(*actualSize == maxSize){
    printf("Nao eh possivel adicionar mais pessoas, limite atingido.\n");
    return;
  }
  Person person = createPerson(persons, actualSize);
  persons[(*actualSize)++] = person;
}

void updatePerson(Person* persons, int actualSize, int regist){
  for(int i = 0; i < actualSize; i++){
    if(persons[i].regist == regist){
      while(true){
        listPersons(&persons[i], 1);
        printf("=========================================\n");
        printf("|          Atualização de Pessoa        |\n");
        printf("|---------------------------------------|\n");
        printf("|---------------------------------------|\n");
        printf("|  0 - Voltar                           |\n");
        printf("|  1 - Atualizar Nome                   |\n");
        printf("|  2 - Atualizar Aniversário            |\n");
        printf("|  3 - Atualizar CPF                    |\n");
        printf("|  4 - Atualizar Sexo                   |\n");
        printf("=========================================\n");
        printf("Digite sua escolha: ");
        int choice;
        scanf("%d", &choice);
        cleanStream();
        system("clear");
        if(choice == 0){
          break;
        }
        switch(choice){
          case 1:
            setName(persons[i].name);
            break;
          case 2:
            getAgeAndBirth(&persons[i].age, persons[i].birth);
            break;
          case 3:
            setCpf(persons[i].cpf);
            break;
          case 4:
            setGender(&persons[i].gender);
            break;
        }
        printf("Atualizado com sucesso!\n");
      }
    }
  }
}

//Utilizada para excluir um struct do tipo Person de um vetor dado
void deletePerson(Person* persons, int* actualSize, int regist){
  if(*actualSize == 0){
    printf("Nao ha pessoas cadastradas.\n");
    return;
  }
  for(int i = 0; i < *actualSize; i++){
    if(persons[i].regist == regist){
      persons[i] = persons[--(*actualSize)];
      printf("Pessoa removida com sucesso!\n");
      return;
    }
  }
  printf("Numero de matricula nao encontrada.\n");
}

// Listar
// utilizada para listar os dados de um struct do tipo Person que esteja em um vetor
void listPersons(const Person* persons, const int actualSize){
  if(actualSize == 0){
    printf("Pessoas nao encontradas.\n");
    return;
  }

  for(int i = 0; i < actualSize; i++){
    printf("Pessoa %d\n", i+1);
    printf("Nome: %s\n", persons[i].name);
    printf("Matricula: %d\n", persons[i].regist);
    printf("CPF: %.3s.%.3s.%.3s-%.2s\n", persons[i].cpf, persons[i].cpf + 3, persons[i].cpf + 6, persons[i].cpf + 9);
    printf("Idade: %d\n", persons[i].age);
    printf("Sexo: %c\n", persons[i].gender);
    printf("Data de nascimento: %02d/%02d/%d\n", persons[i].birth[0], persons[i].birth[1], persons[i].birth[2]);
    printf("\n");
  }
}

void listPersonByGender(const Person* persons, const int actualSize, const char gender){
  Person filtredPersons[actualSize];
  int filtredPersonsSize = 0;
  for(int i = 0; i < actualSize; i++){
    if(persons[i].gender == gender){
      filtredPersons[filtredPersonsSize++] = persons[i];
    }
  }
  listPersons(filtredPersons, filtredPersonsSize);
}


//Lista os structs do tipo Person em ordem alfabetica (tecnicamente usando uma combinacao do algortimo selection sort para os array e ordem lexica para os nomes).
//A ordem lexica eh case sensetive, ou seja, 'A' e 'a' sao considerados diferentes. A menos que nao exista nenhuma letra maiuscula no meio da palavra isso nao vai fazer diferença.
void listPersonByName(const Person* persons, const int actualSize){
  Person ordenedPersons[actualSize];
  for(int i = 0; i < actualSize; i++){
    ordenedPersons[i] = persons[i];
  }
  for(int i = 0; i < actualSize; i++){
    int min_pos = i;
    for(int j = i + 1; j < actualSize; j++){
      if(customStrcmp(ordenedPersons[j].name, ordenedPersons[min_pos].name) < 0){
        min_pos = j;
      }
    }
    if(min_pos != i){
      Person temp = ordenedPersons[i];
      ordenedPersons[i] = ordenedPersons[min_pos];
      ordenedPersons[min_pos] = temp;
    }
  }
  listPersons(ordenedPersons, actualSize);
}

int compareBirthDates(const int* birth1, const int* birth2) {
    // Comparando anos
    if (birth1[2] != birth2[2]) {
        return birth1[2] - birth2[2];
    }
    // Comparando meses
    if (birth1[1] != birth2[1]) {
        return birth1[1] - birth2[1];
    }
    // resta os dias
    return birth1[0] - birth2[0];
}

void listPersonByBirth(const Person* persons, const int actualSize) {
  Person ordenedPersonsByBirth[actualSize];
  for (int i = 0; i < actualSize; i++) {
    ordenedPersonsByBirth[i] = persons[i];
  }

  for (int i = 0; i < actualSize - 1; i++) {
    int youngest_pos = i;
    for (int j = i + 1; j < actualSize; j++) {
      if(compareBirthDates(ordenedPersonsByBirth[j].birth, ordenedPersonsByBirth[youngest_pos].birth) < 0) {
        youngest_pos = j;
      }
    }
    if (youngest_pos != i) {
      Person temp = ordenedPersonsByBirth[i];
      ordenedPersonsByBirth[i] = ordenedPersonsByBirth[youngest_pos];
      ordenedPersonsByBirth[youngest_pos] = temp;
    }
  }
  listPersons(ordenedPersonsByBirth, actualSize);
}

void listPersonsBirthOfMonth(const Person* persons, const int actual_size, int month){
  Person filteredPersons[actual_size];
  int filteredPersonsSize = 0;
  for(int i = 0; i < actual_size; i++){
    if(persons[i].birth[1] == month){
      filteredPersons[filteredPersonsSize++] = persons[i];
    }
  }
  listPersons(filteredPersons, filteredPersonsSize);
}

void listPersonsFromSubstring(const Person* persons, const int actual_size, const char* substring){
  Person filteredPersons[actual_size];
  int filteredPersonsSize = 0;
  for(int i = 0; i < actual_size; i++){
    if(customStrstr(persons[i].name, substring) != NULL){
      filteredPersons[filteredPersonsSize++] = persons[i];
    }
  }
  listPersons(filteredPersons, filteredPersonsSize);
}