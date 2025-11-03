#include "svg.h"
#include "figure.h"
#include "queue.h"

#include <stdio.h>
#include <string.h>

static void svgDrawCircle(FILE *svgFile, Figure f) {
  char colorB[32], colorF[32];
  double x, y;
  getFigureColors(f, colorB, colorF);
  getFigureXY(&x, &y, f);
  fprintf(
      svgFile,
      "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\"stroke=\"%s\" fill=\"%s\" />\n",
      x, y, getCircleR(f), colorB, colorF);
}

static void svgDrawRectangle(FILE *svgFile, Figure f) {
  char colorB[32], colorF[32];
  double x, y, w, h;
  getFigureColors(f, colorB, colorF);
  getFigureXY(&x, &y, f);
  getRectangleWH(f, &w, &h);

  fprintf(svgFile,
          "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" "
          "stroke=\"%s\" fill=\"%s\" />\n",
          x, y, w, h, colorB, colorF);
}

static void svgDrawLine(FILE *svgFile, Figure f) {
  char colorB[32], colorF_dummy[32];
  double x1, y1, x2, y2;
  getFigureColors(f, colorB, colorF_dummy);
  getLineP(f, &x1, &y1, &x2, &y2);
  fprintf(
      svgFile,
      "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" />\n",
      x1, y1, x2, y2, colorB);
}

static void svgDrawText(FILE *svgFile, Figure f) {
  char colorB[32], colorF[32], txt[256], anchorStr[10];
  char family[64], weightStr[10], svgWeight[10];
  double x, y;
  getFigureColors(f, colorB, colorF);
  getFigureXY(&x, &y, f);
  getTextTXT(f, txt);
  char anchor = getTextA(f);
  getTextFml(f, family);
  getTextWgt(f, weightStr);
  int size = getTextSize(f);
  if (anchor == 'i')
    strcpy(anchorStr, "start");
  else if (anchor == 'f')
    strcpy(anchorStr, "end");
  else
    strcpy(anchorStr, "middle");
  if (strcmp(weightStr, "b") == 0)
    strcpy(svgWeight, "bold");
  else if (strcmp(weightStr, "b+"))
    strcpy(svgWeight, "bolder");
  else if (strcmp(svgWeight, "l"))
    strcpy(svgWeight, "lighter");
  else
    strcpy(svgWeight, "normal");
  fprintf(
      svgFile,
      "\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" text-anchor=\"%s\" "
      "font-family=\"%s\" font-size=\"%d\" font-weight=\"%s\"> %s</text>\n ",
      x, y, colorF, anchorStr, family, size, svgWeight, txt);
}

void svgInit(FILE *svgFile) {
  if (!svgFile)
    return;
  fprintf(svgFile,
          "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

void svgClose(FILE *svgFile) {
  if (!svgFile)
    return;
  fprintf(svgFile, "</svg>\n");
}

void svgDrawFigure(FILE *svgFile, Figure f) {
  if (!svgFile || !f)
    return;
  int shape = getFigureShape(f);
  switch (shape) {
  case CIRCLE:
    svgDrawCircle(svgFile, f);
    break;
  case RECTANGLE:
    svgDrawRectangle(svgFile, f);
    break;
  case LINE:
    svgDrawLine(svgFile, f);
    break;
  case TEXT:
    svgDrawText(svgFile, f);
    break;
  default:
    break;
  }
}

void svgDrawAll(FILE *svgFile, Queue figureList) {
  if (!svgFile || !figureList)
    return;
  Queue auxQueue = queueInit();
  if (!auxQueue) {
    fprintf(stderr, "Erro: Falha ao alocar fila auxiliar para desenho SVG.\n");
    return;
  }
  while (!queueIsEmpty(figureList)) {
    Figure f = queueDequeue(figureList);
    if (f) {
      svgDrawFigure(svgFile, f);
      queueEnqueue(auxQueue, f);
    }
  }
  while (!queueIsEmpty(auxQueue)) {
    queueEnqueue(figureList, queueDequeue(auxQueue));
  }
  queueFree(auxQueue);
}
