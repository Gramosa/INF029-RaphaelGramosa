#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dataBase.h"
#include "person.h"
#include "utils.h"
#include "subject.h"

//Menu's
//submenu para cadastrar aluno
void registerStudentMenu(DataBase *db){
  int choice;
  while(true){
    printf("===================================\n");
    printf("|       Registro de Aluno         |\n");
    printf("|---------------------------------|\n");
    printf("|  0 - Voltar                     |\n");
    printf("|  1 - Cadastrar Novo Aluno       |\n");
    printf("|  2 - Atualizar Dados do Aluno   |\n");
    printf("|  3 - Excluir Aluno              |\n");
    printf("===================================\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);
    system("clear");

    if(choice == 0){
      return;
    }
    int regist;
    switch(choice){
      case 1:
        addPerson(db->students, &(db->studentsCount), MAX_STUDENTS);
        break;
      case 2:
        getRegistration(&regist);
        updatePerson(db->students, db->studentsCount, regist);
        break;
      case 3:
        getRegistration(&regist);
        deletePerson(db->students, &(db->studentsCount), regist);
        break;
    }

  }
}

void registerTeacherMenu(DataBase *db){
  int choice;
  while(true){
    printf("======================================\n");
    printf("|      Registro de Professor         |\n");
    printf("|------------------------------------|\n");
    printf("|  0 - Voltar                        |\n");
    printf("|  1 - Cadastrar Novo Professor      |\n");
    printf("|  2 - Atualizar Dados do Professor  |\n");
    printf("|  3 - Excluir Professor             |\n");
    printf("======================================\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);
    system("clear");
    if(choice == 0){
      return;
    }
    int regist;
    switch(choice){
      case 1:
        addPerson(db->teachers, &(db->teachersCount), MAX_TEACHERS);
        break;
      case 2:
        getRegistration(&regist);
        updatePerson(db->teachers, db->teachersCount, regist);
        break;
      case 3:
        getRegistration(&regist);
        deletePerson(db->teachers, &(db->teachersCount), regist);
        break;
    }
  }
}

//submenu para cadastrar disciplina
void registerSubjectMenu(DataBase *db){
  int choice;
  while(true){
    printf("=========================================\n");
    printf("|        Registro de Disciplina         |\n");
    printf("|---------------------------------------|\n");
    printf("|  0 - Voltar                           |\n");
    printf("|  1 - Cadastrar Disciplina             |\n");
    printf("|  2 - Atualizar Disciplina             |\n");
    printf("|  3 - Excluir Disciplina               |\n");
    printf("=========================================\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);
    system("clear");
    if(choice == 0){
      return;
    }
    int code;
    switch(choice){
      case 1:
        addSubject(db, MAX_SUBJECTS);
        break;
      case 2:
        setCode(&code);
        updateSubject(db, code);
      // case 3:
    }

  }
}

//submenu para relatorios
void reportMenu(DataBase *db){
  int choice;
  while(true){
    printf("==========================================\n");
    printf("|               Relatórios               |\n");
    printf("|----------------------------------------|\n");
    printf("|  0  - Voltar                           |\n");
    printf("|  1  - Listar Alunos                    |\n");
    printf("|  2  - Listar Professores               |\n");
    printf("|  3  - Listar Alunos por Sexo           |\n");
    printf("|  4  - Listar Alunos por Nome           |\n");
    printf("|  5  - Listar Alunos por Data Nascimento|\n");
    printf("|  6  - Listar Professores por Sexo      |\n");
    printf("|  7  - Listar Professores por Nome      |\n");
    printf("|  8  - Listar Professores por Data Nasc.|\n");
    printf("|  9  - Aniversariantes do Mês           |\n");
    printf("|  10 - Pesquisar Pessoa por Nome        |\n");
    printf("|  11 - Listar Disciplinas               |\n");
    printf("|  12 - Listar Disciplina com Alunos     |\n");
    printf("|  13 - Alunos Matriculados em Menos de 3|\n");
    printf("|  14 - Disciplinas com Mais de 40 Vagas |\n");
    printf("==========================================\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);
    system("clear");
    cleanStream();
    if(choice == 0){
      return;
    }
    char gender;
    int month = getActualMonth();
    char name[MAX_LETTERS];
    int code;
    switch(choice){
      case 1:
        printf("=== Lista de Alunos ===\n");
        listPersons(db->students, db->studentsCount);
        break;
      case 2:
        printf("=== Lista de Professores ===\n");
        listPersons(db->teachers, db->teachersCount);
        break;
      case 3:
        setGender(&gender);
        printf("=== Lista de Alunos com sexo '%c' ===\n", gender);
        listPersonByGender(db->students, db->studentsCount, gender);
        break;
      case 4:
        printf("=== Lista de Alunos por nome ===\n");
        listPersonByName(db->students, db->studentsCount);
        break;
      case 5:
        printf("=== Lista de Alunos por data de nascimento ===\n");
        listPersonByBirth(db->students, db->studentsCount);
        break;
      case 6:
        setGender(&gender);
        printf("=== Lista de Professores com sexo '%c' ===\n", gender);
        listPersonByGender(db->teachers, db->teachersCount, gender);
        break;
      case 7:
        printf("=== Lista de Professores por nome ===\n");
        listPersonByName(db->teachers, db->teachersCount);
        break;
      case 8:
        printf("=== Lista de Professores por data de nascimento ===\n");
        listPersonByBirth(db->teachers, db->teachersCount);
        break;
      case 9:
        printf("=== Aniversariantes do mes ===\n");
        printf("=== Alunos ===\n");
        listPersonsBirthOfMonth(db->students, db->studentsCount, month);
        printf("=== Professores ===\n");
        listPersonsBirthOfMonth(db->teachers, db->teachersCount, month);
        break;
      case 10:
        do{
          setName(name);
        }while(customStrlen(name) < 3);
        printf("===== Lista de pessoas com nome '%s' ====\n", name);
        printf("=== Alunos ===\n");
        listPersonsFromSubstring(db->students, db->studentsCount, name);
        printf("=== Professores ===\n");
        listPersonsFromSubstring(db->teachers, db->teachersCount, name);
        break;
      case 11:
        printf("=== Lista de Disciplinas ===\n");
        listSubjects(db->subjects, db->subjectsCount, db->teachers, db->teachersCount);
        break;
      case 12:
        setCode(&code);
        Subject* sub = getSubjectByCode(db->subjects, db->subjectsCount, code);
        if(sub != NULL){
          listOneSubjectData(sub, db);
        }
        else{
          printf("Disciplina nao encontrada.\n");
        }
        break;
      case 13:
        printf("=== Lista de alunos matriculados em menos de 3 disciplinas ===\n");
        listStudentsEnrolledInLessThanThreeSubjects(db);
        break;
      case 14:
        printf("=== Lista de disciplinas que extrapolam 40 vagas ===\n");
        listSubjectsExceedingCapacity(db);
        break;
    }
  }
}

void mainMenu(DataBase *db){
  int choice;
  while(true){
    showTime();
    printf("=======================================\n");
    printf("|  * Bem-vindo ao Chat da Escola *    |\n");
    printf("|-------------------------------------|\n");
    printf("|  0 - Sair                           |\n");
    printf("|  1 - Cadastrar Aluno                |\n");
    printf("|  2 - Cadastrar Professor            |\n");
    printf("|  3 - Cadastrar Disciplina           |\n");
    printf("|  4 - Relatórios                     |\n");
    printf("=======================================\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);
    system("clear");
    if(choice == 0){
      break;
    }
    switch(choice){
      case 1:
        registerStudentMenu(db);
        break;
      case 2:
        registerTeacherMenu(db);
        break;
      case 3:
        registerSubjectMenu(db);
        break;
      case 4:
        reportMenu(db);
        break;
    }
  }
}

int main() {
  DataBase dataBase = {.studentsCount = 0, .teachersCount = 0, .subjectsCount = 0};
  readDataBaseFromFile(&dataBase, "dataBase.txt");
  mainMenu(&dataBase);
  saveDataBaseToFile(&dataBase, "dataBase.txt");
  return 0;
}