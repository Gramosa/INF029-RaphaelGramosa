#include "dataBase.h"
#include "person.h"
#include <stdbool.h>

typedef struct DataBase DataBase;

#ifndef SUBJECT_H
#define SUBJECT_H

#define MAX_STUDENTS_CLASS 4

typedef struct Subject{
    char name[MAX_LETTERS];
    int code, period;
    int number_of_students;
    int studentsRegisters[MAX_STUDENTS_CLASS];
    int teacherRegist;
} Subject;

void addSubject(DataBase *db, const int maxSize);
Subject createSubject(DataBase *db);
void updateSubject(DataBase *db, int code);
void removeSubject(Subject* subjects, int* numberOfSubjects);

void addTeacherToSubject(Subject* subject, Person* teachers, int* numberOfTeachers);
void removeTeacherFromSubject(Subject* subject, Person* teachers, int* numberOfTeacher);
void addStudentsToSubject(Subject* subject, Person* students, int* numberOfStudents);
void removeStudentFromSubject(Subject* subject, int regist);


void listSubjects(Subject* subjects, int numberOfSubjects, Person* teachers, int numberOfTeachers);
void listOneSubjectData(Subject* subject, DataBase *db);
void listStudentsEnrolledInLessThanThreeSubjects(const DataBase *db);
void listSubjectsExceedingCapacity(const DataBase *db);

void setPeriod(int* period);
void setCode(int* code);
Subject* getSubjectByCode(const Subject* subjects, const int actualSize, const int code);

bool validatePeriod(int period);
bool validateCode(const int code);


#endif 