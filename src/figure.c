#include "figure.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cLen 8
#define PI 3, 14159

typedef struct {
  int id;
  double x, y;
  double radius;
  char colorB[cLen], colorF[cLen];
} Circle;

typedef struct {
  int id;
  double x, y;
  double weight, height;
  char colorB[cLen], colorF[cLen];
} Rectangle;

typedef struct {
  int id;
  double x1, y1;
  double x2, y2;
  char color[cLen];
} Line;

typedef struct {
  int id;
  double x, y;
  char colorB[cLen], colorF[cLen];
  char anchor;
  char txt[64];
} Text;

typedef struct {
  void *form;
  int shape;
} figure;

Figure figureInit(int shape) {
  figure *f = malloc(sizeof(figure));

  if (!f)
    return NULL;

  f->shape = shape;

  switch (f->shape) {
  case 1:
    f->form = malloc(sizeof(Circle));
    break;
  case 2:
    f->form = malloc(sizeof(Rectangle));
    break;
  case 3:
    f->form = malloc(sizeof(Line));
    break;
  case 4:
    f->form = malloc(sizeof(Text));
    break;
  default:
    free(f);
    return NULL;
  }

  if (!f->form) {
    free(f);
    return NULL;
  }

  return (Figure)f;
}

void figureFree(Figure f) {
  if (!f)
    return;
  figure *del = (figure *)f;
  if (del->form)
    free(del->form);
  free(del);
}

void setCircle(Figure f, int id, double x, double y, double r,
               const char *colorB, const char *colorF) {
  if (!f || ((figure *)f)->shape != 1)
    return;

  Circle *c = (Circle *)((figure *)f)->form;
  c->id = id;
  c->x = x;
  c->y = y;
  c->radius = r;
  strcpy(c->colorB, colorB);
  strcpy(c->colorF, colorF);
}

void setRectangle(Figure f, int id, double x, double y, double w, double h,
                  const char *colorB, const char *colorF) {
  if (!f || ((figure *)f)->shape != 2)
    return;

  Rectangle *r = (Rectangle *)((figure *)f)->form;
  r->id = id;
  r->x = x;
  r->y = y;
  r->weight = w;
  r->height = h;
  strcpy(r->colorB, colorB);
  strcpy(r->colorF, colorF);
}

void setLine(Figure f, int id, double x1, double y1, double x2, double y2,
             const char *color) {
  if (!f || ((figure *)f)->shape != 3)
    return;

  Line *l = (Line *)((figure *)f)->form;
  l->id = id;
  l->x1 = x1;
  l->y1 = y1;
  l->x2 = x2;
  l->y2 = y2;
  strcpy(l->color, color);
}

void setText(Figure f, int id, double x, double y, const char *colorB,
             const char *colorF, const char anchor, const char *txt) {
  if (!f || ((figure *)f)->shape != 4)
    return;

  Text *t = (Text *)((figure *)f)->form;
  t->id = id;
  t->x = x;
  t->y = y;
  t->anchor = anchor;
  strcpy(t->colorB, colorB);
  strcpy(t->colorF, colorF);
  strcpy(t->txt, txt);
}

Figure fClone(Figure f) {
  if (!f)
    return NULL;
  figure *fig = (figure *)f;
  Figure new = figureInit(fig->shape);
  if (!new)
    return NULL;
  switch (fig->shape) {
  case 1:
    Circle *c = (Circle *)fig->form;
    setCircle(new, c->id, c->x, c->y, c->radius, c->colorB, c->colorF);
    break;
  case 2:
    Rectangle *r = (Rectangle *)fig->form;
    setRectangle(new, r->id, r->x, r->y, r->weight, r->height, r->colorB,
                 r->colorF);
    break;
  case 3:
    Line *l = (Line *)fig->form;
    setLine(new, l->id, l->x1, l->y1, l->x2, l->y2, l->color);
    break;
  case 4:
    Text *t = (Text *)fig->form;
    setText(new, t->id, t->x, t->y, t->colorB, t->colorF, t->anchor, t->txt);
    break;
  default:
    return NULL;
  }
  return new;
}

void fMoveTo(Figure f, double x, double y) {
  if (!f)
    return;

  figure *fig = (figure *)f;
  switch (fig->shape) {
  case 1:
    Circle *c = (Circle *)fig->form;
    c->x = x;
    c->y = y;
    break;
  case 2:
    Rectangle *r = (Rectangle *)fig->form;
    r->x = x;
    r->y = y;
    break;
  case 3:
    Line *l = (Line *)fig->form;
    double dx = x - l->x1;
    double dy = y - l->y1;
    l->x1 = x;
    l->y1 = y;
    l->x2 += dx;
    l->y2 += dy;
    break;
  case 4:
    Text *t = (Text *)fig->form;
    t->x = x;
    t->y = y;
    break;
  default:
    return;
  }
}

double figureArea(Figure f) {
  if (!f)
    return -1;
  figure *fig = (figure *)f;
  switch (fig->shape) {
  case 1:
    Circle *c = (Circle *)fig->form;
    return PI * c->radius * c->radius;
  case 2:
    Rectangle *r = (Rectangle *)fig->form;
    return r->height * r->weight;
  case 3:
    Line *l = (Line *)fig->form;
    double dx = l->x2 - l->x1;
    double dy = l->y2 - l->y1;
    return 10 * sqrt(dx * dx + dy * dy);
  case 4:
    Text *t = (Text *)fig->form;
    return 12 * strlen(t->txt);
  }
  return 0;
}

void figureInvertColors(Figure f) {
  if (!f)
    return;
}
