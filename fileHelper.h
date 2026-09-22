#include <stdbool.h>
#include <stddef.h>

#ifndef FILEHELPER_H_
#define FILEHELPER_H_

bool jsonInit(char *firstName, char* lastName);
bool checkName(char *firstNameMain, size_t firstNameCapacity,
               char *lastNameMain, size_t lastNameCapacity);

#endif // FILEHELPER_H_
