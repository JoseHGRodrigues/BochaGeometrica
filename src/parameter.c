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

bool

    bool
    flagsExist(int argc, char *args[]) {
  bool check[3] = {false, false, false};
  for (int i = 0; i < argc; i++) {
    if (strcmp(args[i], "-f")) {
      check[0] = true;
      i++;
    }
    elseif(strcmp(args[i], "-q")) {
      check[1] = true;
      i++;
    }
    elseif(strcmp(args[i], "-o")) {
      check[2] = true;
      i++;
    }
  }
}

bool parameterProcessvoid *parameter, int argc, char *args[]) {
  if (!parameter) {
    printf("parameter.c:\tParameterProcess()\t parameter empty");
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
