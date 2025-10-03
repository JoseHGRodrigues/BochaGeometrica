#ifndef FIGURE_H
#define FIGURE_H

#include <stdio.h>

#define CIRCLE 1;
#define RECTANGLE 2;
#define LINE 3;
#define TEXT 4;

typedef void *Figure;

Figure figureInit(int shape);

void figureFree(Figure f);

/*
 * id: integer greater than zero that identifies a geometric shape.
 * x, y: coordinates of a 2d plane.
 * colorB: hex code of the figure border color.
 * colorF: hex code of the figure fill color.
 * r: radius of the circle.
 * w, h: weight and height of the Rectangle.
 * anchor: specific coordinate used as a reference for text positioning.
 *  i: at the beggining of the text.
 *  m: at the the middle of the text.
 *  f: at the end of the text.
 * txt: The text to be displayed.
 * fFamily: Font family
 * fWeight: style of the de font.
 *  n: normal.
 *  b: bold.
 *  b+: bolder.
 *  l: lighter.
 * fSize: Font size.
 */
void setCircle(Figure f, int id, double x, double y, double r,
               const char *colorB, const char *colorF);

void setRectangle(Figure f, int id, double x, double y, double w, double h,
                  const char *colorB, const char *colorF);

void setLine(Figure f, int id, double x1, double y1, double x2, double y2,
             const char *color);

void setText(Figure f, int id, double x, double y, const char *colorB,
             const char *colorF, const char anchor, const char *txt);

void setTextStyle(Figure f, const char *fFamily, const char *fWeight,
                  double fSize);

void figureColor(Figure f, const char *colorB, const char *colorF);

void figureInvertColors(Figure f);

void figureMove(Figure f, double x, double y);

#endif
