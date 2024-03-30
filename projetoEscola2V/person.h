#ifndef PERSON_H
#define PERSON_H
#include "dataBase.h"
#include <stdbool.h>

#define MAX_LETTERS 32

typedef struct Person {
    int regist, age, birth[3];
    char gender;
    char name[MAX_LETTERS], cpf[13];
} Person;


bool validateBirth(int*, const char*);
bool validateAge(int *, const int *);
bool validateCpf(const char*);
bool validateGender(char);
bool validateRegistration(const int);

void getBirth(int*);
void getAgeAndBirth(int*, int*);
void setName(char*);
void setCpf(char*);
void setGender(char*);
void getRegistration(int*);
Person* getPersonByRegist(const Person* persons, const int actualSize, const int regist);

Person createPerson(Person*, int*);
void addPerson(Person*, int*, int);
void updatePerson(Person*, int, int);
void deletePerson(Person*, int*, int);

void listPersons(const Person*, const int);
void listPersonByGender(const Person*, const int, const char);
void listPersonByName(const Person*, const int);
void listPersonByBirth(const Person*, const int);
void listPersonsBirthOfMonth(const Person*, const int, int);
void listPersonsFromSubstring(const Person*, const int, const char*);

#endif // PERSON_H