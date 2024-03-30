#include <stdio.h>
#include <stdlib.h>
#include "dataBase.h"
#include "person.h"
#include "subject.h"

const char FORMAT_STUDENT_READ[] = "Student: %d; %d; %d; %d; %d; %c; %[^;]; %s\n";
const char FORMAT_STUDENT_WRITE[] = "Student: %d; %d; %d; %d; %d; %c; %s; %s\n";
const char FORMAT_TEACHER_READ[] = "Teacher: %d; %d; %d; %d; %d; %c; %[^;]; %s\n";
const char FORMAT_TEACHER_WRITE[] = "Teacher: %d; %d; %d; %d; %d; %c; %s; %s\n";
const char FORMAT_SUBJECT_READ[] = "Subject: %d; %d; %d; %d; %[^;];";
const char FORMAT_SUBJECT_WRITE[] = "Subject: %d; %d; %d; %d; %s;";

//ISSO É PRA LER O ARQUIVO DE DADOS  // o ponteiro file vai apontar para o arquivo de dados por meio da funcao fopen
//(caminhoDoArquivo/nomeDoArquivo.txt  ou nomeDoArquivo.txt(cria o arq no diretorio onde ta o programa em c esta, arq.fonte) e depois o modo de acesso ao arquivo(6 letras: r-read, w-write, a-append, r+, w+, a+)
void readDataBaseFromFile(DataBase *db, const char* arqDados){

  FILE *file = fopen(arqDados, "r");
  // se o arquivo nao existir, a funcao fopen retorna NULL
  if(file == NULL){
    printf("Erro ao abrir o arquivo.\n");

    exit(1);
  }
  while(fscanf(file, FORMAT_STUDENT_READ,
    &db->students[db->studentsCount].regist,
    &db->students[db->studentsCount].age,
    &db->students[db->studentsCount].birth[0],
    &db->students[db->studentsCount].birth[1],
    &db->students[db->studentsCount].birth[2],
    &db->students[db->studentsCount].gender,
    db->students[db->studentsCount].name,
    db->students[db->studentsCount].cpf) == 8){
    db->studentsCount++;
  }
  //rewind(file);
  while(fscanf(file, FORMAT_TEACHER_READ,
    &db->teachers[db->teachersCount].regist,
    &db->teachers[db->teachersCount].age,
    &db->teachers[db->teachersCount].birth[0],
    &db->teachers[db->teachersCount].birth[1],
    &db->teachers[db->teachersCount].birth[2],
    &db->teachers[db->teachersCount].gender,
    db->teachers[db->teachersCount].name,
    db->teachers[db->teachersCount].cpf) == 8){
    db->teachersCount++;
  }

  while(fscanf(file, FORMAT_SUBJECT_READ,
  &db->subjects[db->subjectsCount].code,
  &db->subjects[db->subjectsCount].period,
  &db->subjects[db->subjectsCount].number_of_students,
  &db->subjects[db->subjectsCount].teacherRegist,
  db->subjects[db->subjectsCount].name
  ) == 5){
    int i = 0;
    while(fscanf(file, " %d", &db->subjects[db->subjectsCount].studentsRegisters[i]) == 1 && i < MAX_STUDENTS_CLASS){
      i++;
      db->subjects[db->subjectsCount].number_of_students = i;
    }
    db->subjectsCount++;
  }
  fclose(file);

}

void saveDataBaseToFile(DataBase *db, const char* arqDados){
  FILE *file = fopen(arqDados, "w");
  if(file == NULL){
   printf("Erro ao abrir o arquivo.\n");
    getchar();
    exit(1);
  }
  for(int i = 0; i < db->studentsCount; i++){
    fprintf(file, FORMAT_STUDENT_WRITE,
      db->students[i].regist,
      db->students[i].age,
      db->students[i].birth[0],
      db->students[i].birth[1],
      db->students[i].birth[2],
      db->students[i].gender,
      db->students[i].name,
      db->students[i].cpf);
  }
  for(int i = 0; i < db->teachersCount; i++){
    fprintf(file, FORMAT_TEACHER_WRITE,
    db->teachers[i].regist,
    db->teachers[i].age,
    db->teachers[i].birth[0],
    db->teachers[i].birth[1],
    db->teachers[i].birth[2],
    db->teachers[i].gender,
    db->teachers[i].name,
    db->teachers[i].cpf);
  }

  for(int i = 0; i < db->subjectsCount; i++){
    fprintf(file, FORMAT_SUBJECT_WRITE,
    db->subjects[i].code,
    db->subjects[i].period,
    db->subjects[i].number_of_students,
    db->subjects[i].teacherRegist,
    db->subjects[i].name);
    for(int j = 0; j < db->subjects[i].number_of_students; j++){
      fprintf(file," %d", db->subjects[i].studentsRegisters[j]);
    }
    fprintf(file, "\n");
  }
  fclose(file);
}