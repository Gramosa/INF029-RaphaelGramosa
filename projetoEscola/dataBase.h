#ifndef DATABASE_H
#define DATABASE_H
#include "person.h"
#include "subject.h"

#define MAX_STUDENTS 4
#define MAX_TEACHERS 3
#define MAX_SUBJECTS 4

typedef struct DataBase{
    Person students[MAX_STUDENTS];
    Person teachers[MAX_TEACHERS];
    Subject subjects[MAX_SUBJECTS];
    int studentsCount;
    int teachersCount;
    int subjectsCount;
} DataBase;

#endif