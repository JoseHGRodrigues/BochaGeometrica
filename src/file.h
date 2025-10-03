#ifndef FILE_H
#define FILE_H

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * @brief Opens a file from a path
 */
FILE fileOPen(const char *path, const char mode);

/*
 * @brief Closes the file
 */
void fileClose(FILE f);

/*
 * @Brief Read a line from the file
 */
void fileReadLine(FILE f, List l);

/*
 * @brief Read all the file
 */
List fileReadAll(FILE f);

#endif // !DEBUG
