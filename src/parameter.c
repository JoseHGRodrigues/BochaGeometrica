#include "parameter.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *dEnt; // Diretorio de Entrada
  char *dGeo; // Diretorio do .geo
  char *dQry; // Diretorio do .qry
  char *dOut; // Diretorio de saida
} Parameter;

void *parametersAlloc() {
  Parameter *p = (Parameter *)malloc(sizeof(Parameter));
  if (!p) {
    printf("Parametros não alocado");
    return NULL;
  }
  memset(p, '\0', sizeof(Parameter));
  return p;
}

void parameterFound(int argc, char *args[]) {
  int found_q = 0, found_e = 0;
  found_f = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-e") == 0)
      found_e = 1;
    else if (strcmp(argv[i], "-q") == 0)
      found_q = 1;
    else if (strcmp(argv[i], "-f") == 0)
      found_f = 1;
  }
}

bool parameterProcess(void *parameter, int argc, char *args[]) {
  if (!parameter) {
    printf("parameter.c: ParameterProcess() - parameter empty");
    return false;
  }

  for (int i = 0; i < argc; i++) {
    if (strcmp(args[i], "-e"))
      parameter->dEnt = args[i + 1];
    if (strcmp(args[i], "-f"))
      parameter->dGeo = args[i + 1];
    if (strcmp(args[i], "-q"))
      parameter->dQry = args[i + 1];
    if (strcmp(args[i], "-o"))
      parameter->dOut = args[i + 1];
  }
}
