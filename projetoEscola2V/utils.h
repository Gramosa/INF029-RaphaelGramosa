#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H

void cleanNewLine(char*);
void cleanStream(void);
int convertStrToInt(const char*, int, int);
unsigned int customStrlen(const char*);
int customStrcmp(const char*, const char*);
char customToLower(char);
char* customStrstr(const char*, const char*);
void showTime(void);
int getActualMonth(void);

bool validateName(char* name);
bool validateCode(const int code);
bool validatePeriod(int period);
void setName(char* name);
#endif // UTILS_H