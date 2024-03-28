#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dataBase.h"
#include "person.h"
#include "utils.h"
#include "subject.h"

bool validateCode(const int code){
  if(code <=0){
    printf("Codigo da disciplina invalido!\n");
    return false;
  }
  return true;
}

bool validatePeriod(int period){
  if(period <= 0){
    printf("Periodo da disciplina invalido!\n");
    return false;
  }
  return true;
}


void setCode(int* code){
  do{
    printf("Digite o codigo da Disciplina: ");
    scanf("%d", code);

  }while(!validateCode(*code));

}

void setPeriod(int* period){
  do{
    printf("Digite o periodo da disciplina: ");
    scanf("%d", period);
  }while(!validatePeriod(*period));
}

Subject* getSubjectByCode(const Subject* subjects, const int actualSize, const int code){
  for(int i = 0; i < actualSize; i++){
    if(subjects[i].code == code){
      return (Subject *)&subjects[i];
    }
  }
  return NULL;
}

void addTeacherToSubject(Subject* subject, Person* teachers, int* numberOfTeachers){
  int choice;
  int regist;
  do{
    printf("Deseja cadastrar um professor para esta disciplina? (1 - Sim, 0 - Não): ");
    scanf("%d", &choice);
    cleanStream();
    if(choice == 1){
      getRegistration(&regist);
      if(getPersonByRegist(teachers, *numberOfTeachers, regist) != NULL){
        subject->teacherRegist = regist;
        printf("Professor cadastrado na disciplina com Sucesso!.\n");
        break;
      }
      else{
        printf("Matricula do professor nao encontrada! Tente novamente.\n");
      }
    }
  }while(choice == 1);
}
void addStudentsToSubject(Subject* subject, Person* students, int* numberOfStudents){
  int choice;
  int regist;
  do{
    printf("Deseja cadastrar um aluno para esta disciplina? (1 - Sim, 0 - Não): ");
    scanf("%d", &choice);
    cleanStream();
    if(choice == 1){
      getRegistration(&regist);
      // Primeira condicao verifica se o estudante existe em db, a segunda verifica se a materia comporta mais estudantes
      if(subject->number_of_students == MAX_STUDENTS_CLASS){
        printf("Não é possível adicionar mais alunos à disciplina. Limite excedido.\n");
        break;
      }
      if(getPersonByRegist(students,*numberOfStudents, regist) != NULL){
        int i;

        for(i = 0; i < subject->number_of_students; i++){
          if(subject->studentsRegisters[i] == regist){
            printf("Aluno já matriculado na disciplina.\n");
            break;
          }
        }
        if(i == subject->number_of_students){
          subject->studentsRegisters[subject->number_of_students++] = regist;
          printf( "Aluno matriculado à disciplina.\n");
        }
      }
      else{
        printf("Matricula do aluno nao encontrada! Tente novamente.\n");
      }
    }
  }while(choice == 1);
}

void removeStudentFromSubject(Subject* subject, int regist){
  int i;
  for(i = 0; i < subject->number_of_students; i++){
    if(subject->studentsRegisters[i] == regist){
      subject->studentsRegisters[i] = subject->studentsRegisters[--subject->number_of_students];
      printf( "Aluno removido da disciplina.\n"); 
    }
  }
  if(i == subject->number_of_students){
    printf("Aluno nao encontrado na disciplina.\n");
  }
}

void removeTeacherFromSubject(Subject* subject, Person* teachers, int* numberOfTeacher){
  Person* teacher = getPersonByRegist(teachers, *numberOfTeacher,subject->teacherRegist);
  if(teacher == NULL){
    printf( "Professor não encontrado!.\n");
    return;
  }
  subject->teacherRegist = 0;
  printf( "Professor removido da disciplina.\n");
}

Subject createSubject(DataBase *db){
  Subject subject = {.number_of_students = 0};
  printf("===========================================\n");
  printf("|        Cadastro de Disciplina           |\n");
  printf("|-----------------------------------------|\n");
  cleanStream();
  setName(subject.name);
  setCode(&subject.code);
  setPeriod(&subject.period);
  addTeacherToSubject(&subject, db->teachers, &db->teachersCount);
  addStudentsToSubject(&subject,db->students, &db->studentsCount);

  printf("Cadastro da disciplina realizado com sucesso!\n");
  return subject;
}

void addSubject(DataBase *db, const int maxSize) {
    if (db->subjectsCount == maxSize) {
        printf("Nao eh possivel adicionar mais disciplinas, limite atingido!\n");
        return;
    }
    Subject subject = createSubject(db);
    db->subjects[db->subjectsCount++] = subject;
}


void updateSubject(DataBase *db, int code){
  Subject* subject = getSubjectByCode(db->subjects, db->subjectsCount, code);
  if(subject == NULL){
    printf("Disciplina nao encontrada.\n");
    return;

  }
  while(true){
    system("clear");
    int choice;
    listOneSubjectData(subject, db);
    printf("=============================================\n");
    printf("|      Atualização de Disciplina            |\n");
    printf("|-------------------------------------------|\n");
    printf("|  0 - Voltar                               |\n");
    printf("|  1 - Atualizar Nome da Disciplina         |\n");
    printf("|  2 - Atualizar Período da Disciplina      |\n");
    printf("|  3 - Adicionar Professor na Disciplina    |\n");
    printf("|  4 - Remover Professor da Disciplina      |\n");
    printf("|  5 - Adicionar Aluno na Disciplina        |\n");
    printf("|  6 - Remover Aluno da Disciplina          |\n");
    printf("=============================================\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);
    cleanStream();
    printf("\n");
    if(choice == 0){
      break;
    }
    int regist;
    switch(choice){
      case 1:
        setName(subject->name);
        break;
      case 2:
        setPeriod(&subject->period);
        break;
      case 3:
        addTeacherToSubject(subject, db->teachers, &db->teachersCount);
        break;
      case 4:

        removeTeacherFromSubject(subject, db->teachers, &db->teachersCount);
        addTeacherToSubject(subject, db->teachers, &db->teachersCount);
        break;
      case 5:
        addStudentsToSubject(subject, db->students, &db->studentsCount);
        break;
      case 6:
        getRegistration(&regist);
        removeStudentFromSubject(subject,regist);
        break;
    }

  }

}


void removeSubject(Subject* subjects, int* numberOfSubjects) {
  int code;
  printf("Digite o codigo da disciplina a ser removida: ");
  scanf("%d", &code);

  int i;
  for (i = 0; i < *numberOfSubjects; i++) {
    if (subjects[i].code == code) {
      subjects[i] = subjects[(*numberOfSubjects) - 1]; 
      (*numberOfSubjects)--; 
      printf("Disciplina removida com sucesso!\n");
      return;
    }
  }
  printf("Disciplina nao encontrada!\n");
}



void listSubjects(Subject* subjects, int numberOfSubjects, Person* teachers, int numberOfTeachers){
  if(numberOfSubjects == 0){
    printf("Nao ha disciplinas cadastradas!\n");
  }
  for(int i = 0; i < numberOfSubjects; i++){
    printf("Disciplina %d:\n", i + 1);
    printf("Nome: %s\n", subjects[i].name);
    printf("Codigo: %d\n", subjects[i].code);
    printf("Periodo: %d\n", subjects[i].period);
    Person* teacher = getPersonByRegist(teachers, numberOfTeachers, subjects[i].teacherRegist);
    if(teacher != NULL){
      printf("Professor: %s\n", teacher->name );
    }
    else{
      printf("Professor: Nao cadastrado\n");
    }
  }
}

void listOneSubjectData(Subject* subject, DataBase *db){
  Person students[subject->number_of_students];
  printf("========================================\n");
  printf("|          Dados da Disciplina          |\n");
  printf("|--------------------------------------|\n");
  listSubjects(subject, 1, db->teachers, db->teachersCount);
  printf("\n");
  printf("========================================\n");
  printf("|        Alunos Matriculados           |\n");
  printf("|--------------------------------------|\n");
  for(int i = 0; i < subject->number_of_students; i++){
    Person* student = getPersonByRegist(db->students, db->studentsCount, subject->studentsRegisters[i]);
    students[i] = *student;
    printf("----------------------------------------\n");
  }
  listPersons(students, subject->number_of_students);
}



void listStudentsEnrolledInLessThanThreeSubjects(const DataBase *db) {
  bool found = false;
  printf("=============================================================\n");
  printf("|   Alunos Matriculados em Menos de 3 Disciplinas          |\n");
  printf("|-----------------------------------------------------------|\n");
  for (int i = 0; i < db->studentsCount; i++) {
    int subjectCount = 0;
      for (int j = 0; j < db->subjectsCount; j++) {
        for (int k = 0; k < db->subjects[j].number_of_students; k++) {
          if (db->students[i].regist == db->subjects[j].studentsRegisters[k]) {
            subjectCount++;
            break; 
          }
        }
      }
      if (subjectCount < 3) {
        printf("- %s (Matricula: %d) - Matriculado em %d disciplina(s)\n", db->students[i].name, db->students[i].regist, subjectCount);
        found = true;
      }
  }

  if (!found) {
    printf("Nenhum aluno matriculado em menos de 3 disciplinas.\n");
  }
}

void listSubjectsExceedingCapacity(const DataBase *db) {
  bool found = false;

  for (int i = 0; i < db->subjectsCount; i++) {
    if (db->subjects[i].number_of_students > 2) {
      printf("- Disciplina: %s (Codigo: %d, Periodo: %d)\n", db->subjects[i].name, db->subjects[i].code, db->subjects[i].period);
      printf("  Vagas Preenchidas: %d\n", db->subjects[i].number_of_students);
      found = true;
    }
  }

  if (!found) {
    printf("Nenhuma disciplina com mais de 40 vagas preenchidas.\n");
  }
}

