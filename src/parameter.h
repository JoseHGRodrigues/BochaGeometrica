#ifndef PARAMETER_H
#define PARAMETER_H
#include <stdbool.h>

void *parametersAlloc();

bool parameterProcess(void *parameter, int argc, char *args[]);

#endif // !PARAMETER_H
