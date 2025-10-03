#ifndef FILE_H
#define FILE_H

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

FILE fileOPen(const char *filename, const char mode);

void fileClose(FILE f);

void fileReadLine(FILE f, List l);

List fileReadAll(FILE f);

#endif // !DEBUG
