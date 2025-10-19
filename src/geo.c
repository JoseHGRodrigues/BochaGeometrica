#include "geo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "figure.h"
#include "list.h"

#define MAX_LINE_BUFFER 512

static Figure processCircle(const char *line) {
  int id;
  double x, y, r;
  char colorB[32], colorF[32];
  if (sscanf(line, "c %d %lf %lf %lf %s %s", &id, &x, &y, &r, colorB, colorF) ==
      6) {
    Figure newFig = figureInit(CIRCLE);
    setCircle(newFig, id, x, y, r, colorB, colorF);
    return newFig;
  }
  return NULL;
}

static Figure processRectangle(const char *line) {
  int id;
  double x, y, w, h;
  char colorB[32], colorF[32];
  if (sscanf(line, "r %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, colorB,
             colorF) == 7) {
    Figure newFig = figureInit(RECTANGLE);
    setRectangle(newFig, id, x, y, w, h, colorB, colorF);
    return newFig;
  }
  return NULL;
}

static Figure processLine(const char *line) {
  int id;
  double x1, y1, x2, y2;
  char color[32];
  if (sscanf(line, "l %d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, color) ==
      6) {
    Figure newFig = figureInit(LINE);
    setLine(newFig, id, x1, y1, x2, y2, color);
    return newFig;
  }
  return NULL;
}

static Figure processText(const char *line) {
  int id;
  double x, y;
  char colorB[32], colorF[32];
  char anchor;
  char text[MAX_LINE_BUFFER];
  if (sscanf(line, "t %d %lf %lf %s %s %c %[^\n]", &id, &x, &y, colorB, colorF,
             &anchor, text) == 7) {
    Figure newFig = figureInit(TEXT);
    setText(newFig, id, x, y, colorB, colorF, anchor, text);
    return newFig;
  }
  return NULL;
}

static void parseGeoLine(char *lineBuffer, List figureList) {
  char command[16];
  Figure newFig = NULL;

  lineBuffer[strcspn(lineBuffer, "\r\n")] = 0;

  if (sscanf(lineBuffer, "%s", command) != 1)
    return;

  if (strcmp(command, "c") == 0)
    newFig = processCircle(lineBuffer);
  else if (strcmp(command, "r") == 0)
    newFig = processRectangle(lineBuffer);
  else if (strcmp(command, "l") == 0)
    newFig = processLine(lineBuffer);
  else if (strcmp(command, "t") == 0)
    newFig = processText(lineBuffer);

  if (newFig)
    listInsertLast(figureList, newFig);
}

void processGeoFile(const char *geoFilePath, List figureList) {
  FILE *file = fopen(geoFilePath, "r");
  if (!file)
    return;
  char line[MAX_LINE_BUFFER];
  while (fgets(line, sizeof(line), file)) {
    parseGeoLine(line, figureList);
  }
  fclose(file);
}
