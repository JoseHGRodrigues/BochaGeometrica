#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collision.h"
#include "figure.h"
#include "queue.h"
#include "stack.h"
#include "svg.h"

typedef struct {
  unsigned int id;
  Stack st;
} Mag;

typedef struct {
  unsigned id;
  double x;
  double y;
  Mag *left;
  Mag *right;
  Figure onTrigger;
} Trigger;

typedef struct {
  Queue ground;
  Queue arena;
  Trigger **t;
  int lent;
  int maxt;
  Mag **m;
  int lenm;
  int maxm;
  double points;
  int totalIns;
  int totalSho;
  int totalSma;
  int totalClo;
  FILE *svg;
  FILE *txt;
} Game;

static Game *gameInit() {
  Game *g = (Game *)malloc(sizeof(Game));
  g->ground = NULL;
  g->arena = queueInit();
  if (!g->arena)
    return NULL;
  g->lent = 0;
  g->maxt = 10;
  g->t = (Trigger **)malloc(g->maxt * sizeof(Trigger *));
  if (!g->t)
    return NULL;
  g->lenm = 0;
  g->maxm = 10;
  g->m = (Mag **)malloc(g->maxm * sizeof(Mag *));
  if (!g->m)
    return NULL;
  g->points = 0;
  g->totalIns = 0;
  g->totalSho = 0;
  g->totalSma = 0;
  g->totalClo = 0;
  g->svg = NULL;
  g->txt = NULL;
  return g;
}

static void gameFree(Game *g) {
  for (int i = 0; i < g->lenm; i++) {
    while (!stackIsEmpty(g->m[i])) {
      Figure f = stackPop(g->m[i]);
      figureFree(f);
    }
    stackFree(g->m[i]);
  }
  for (int i = 0; i < g->lent; i++) {
    figureFree(g->t[i]->onTrigger);
    free(g->t[i]);
  }
}

static Trigger *triggerInit() {
  Trigger *t = (Trigger *)malloc(sizeof(Trigger));
  if (!t)
    return NULL;
  t->id = 0;
  t->x = 0;
  t->y = 0;
  t->left = NULL;
  t->right = NULL;
  t->onTrigger = NULL;
  return t;
}

static Mag *magInit() {
  Mag *m = (Mag *)malloc(sizeof(Mag));
  if (!m)
    return NULL;
  m->st = stackInit();
  if (!m->st) {
    free(m);
    return NULL;
  }
  return m;
}

static Trigger *triggerFind(Game *g, int id) {
  for (int i = 0; i < g->lent; i++) {
    if (g->t[i]->id == (unsigned int)id) {
      return g->t[i];
    }
  }
  return NULL;
}

static void gameAddTrigger(Game *g, Trigger *t) {
  if (g->lent == g->maxt) {
    g->maxt *= 2;
    g->t = (Trigger **)realloc(g->t, g->maxt * sizeof(Trigger *));
    if (!g->t)
      return;
  }
  g->t[g->lent] = t;
  g->lent++;
}

static Mag *magFind(Game *g, int id) {
  for (int i = 0; i < g->lenm; i++) {
    if (g->m[i]->id == (unsigned int)id) {
      return g->m[i];
    }
  }
  return NULL;
}

static void gameAddMag(Game *g, Mag *m) {
  if (g->lenm == g->maxm) {
    g->maxm *= 2;
    g->m = (Mag **)realloc(g->m, g->maxm * sizeof(Mag *));
    if (!g->m)
      return;
  }
  g->m[g->lenm] = m;
  g->lenm++;
}

static void processPd(Game *g, const char *params) {
  int id;
  double x, y;
  if (sscanf(params, "%d %lf %lf", &id, &x, &y) != 3) {
    printf("%d\n", sscanf(params, "%d %lf %lf", &id, &x, &y));
    return;
  }
  Trigger *t = triggerFind(g, id);
  if (!t) {
    t = triggerInit();
    t->id = id;
    if (!t)
      return;
    gameAddTrigger(g, t);
  }
  t->x = x;
  t->y = y;
}

void txtCir(FILE *txt, Figure f) {
  char colorB[8], colorF[8];
  double x, y;
  getFigureColors(f, colorB, colorF);
  getFigureXY(&x, &y, f);
  fprintf(
      txt,
      "\tCIRCULO %d x %lf y: %lf, raio: %lf, cor borda: %s cor preen.: %s\n",
      getFigureId(f), x, y, getCircleR(f), colorB, colorF);
}

void txtRect(FILE *txt, Figure f) {
  char colorB[8], colorF[8];
  double x, y, w, h;
  getFigureColors(f, colorB, colorF);
  getFigureXY(&x, &y, f);
  getRectangleWH(f, &w, &h);
  fprintf(txt,
          "\tRETANGULO %d x: %lf y: %lf w: %lf h: %lf cor borda: %s cor "
          "preen.: %s\n",
          getFigureId(f), x, y, w, h, colorB, colorF);
}

static void txtLine(FILE *txt, Figure f) {
  char colorB[8], colorDummy[8];
  double x1, y1, x2, y2;
  getFigureColors(f, colorB, colorDummy);
  getLineP(f, &x1, &y1, &x2, &y2);
  fprintf(txt, "\tLINHA %d x1: %lf y1: %lf x2: %lf y2: %lf cor: %s\n",
          getFigureId(f), x1, y1, x2, y2, colorB);
}

static void txtTxt(FILE *txt, Figure f) {
  char colorB[8], colorF[8], text[100], family[64], weight[3];
  double x, y;
  getFigureColors(f, colorB, colorF);
  getFigureXY(&x, &y, f);
  getTextWgt(f, weight);
  getTextFml(f, family);
  getTextTXT(f, text);
  fprintf(txt,
          "\tTEXTO %d x: %lf y: %lf a: %c cor borda: %s cor preen.: %s family: "
          "%s weight: %s size: %d txt: %s\n",
          getFigureId(f), x, y, getTextA(f), colorB, colorF, family, weight,
          getTextSize(f), text);
}

void txtFigInfo(FILE *txt, Figure f) {
  if (!txt || !f)
    return;

  int shape = getFigureShape(f);
  switch (shape) {
  case CIRCLE:
    txtCir(txt, f);
    break;
  case RECTANGLE:
    txtRect(txt, f);
    break;
  case LINE:
    txtLine(txt, f);
    break;
  case TEXT:
    txtTxt(txt, f);
    break;
  default:
    exit(EXIT_FAILURE);
  }
}

static void processLc(Game *g, const char *params) {
  int id, n;
  if (sscanf(params, "%d %d", &id, &n) != 2)
    return;
  Mag *m = magFind(g, id);
  if (!m) {
    m = magInit();
    m->id = id;
  }
  fprintf(g->txt, "LC: Carregador %d\n", id);
  for (int i = 0; i < n; i++) {
    Figure f = (Figure)queueDequeue(g->ground);
    if (!f)
      return;
    stackPush(m->st, f);
    txtFigInfo(g->txt, f);
  }
  printf("stack: %d\n", stackGetSize(m->st));
  gameAddMag(g, m);
}

static void processAtch(Game *g, const char *params) {
  int tid, mlid, mrid;
  if (sscanf(params, "%d %d %d", &tid, &mlid, &mrid) != 3)
    return;
  Trigger *t = triggerFind(g, tid);
  if (!t)
    return;
  Mag *ml = magFind(g, mlid);
  if (!ml) {
    ml = magInit();
    if (!ml)
      return;
  }
  Mag *mr = magFind(g, mrid);
  if (!mr) {
    mr = magInit();
    if (!mr)
      return;
  }
  t->left = ml;
  t->right = mr;
}
static void processShft(Game *g, const char *params) {
  int tid, n;
  char d;
  if (sscanf(params, "%d %c %d", &tid, &d, &n) != 3)
    exit(EXIT_FAILURE);
  Trigger *t = triggerFind(g, tid);
  if (!t)
    exit(EXIT_FAILURE);
  if (d != 'e' && d != 'd')
    exit(EXIT_FAILURE);
  if (n < 1)
    exit(EXIT_FAILURE);
  Stack from = (d == 'e') ? t->left->st : t->right->st;
  Stack to = (d == 'e') ? t->right->st : t->left->st;
  for (int i = 0; i < n; i++) {
    Figure figMove = stackPop(from);
    if (!figMove)
      exit(EXIT_FAILURE);
    if (t->onTrigger)
      stackPush(to, t->onTrigger);
    t->onTrigger = figMove;
  }
  fprintf(g->txt, "SHFT: Disparador %d\n", tid);
  txtFigInfo(g->txt, t->onTrigger);
}

static void processDsp(Game *g, const char *params) {
  int tid;
  double dx, dy;
  char m;
  if (sscanf(params, "%d %lf %lf %c", &tid, &dx, &dy, &m) != 4)
    return;
  Trigger *t = triggerFind(g, tid);
  if (!t)
    return;

  if (!t->onTrigger)
    return;

  printf("%d", getFigureId(t->onTrigger));

  printf("\tt\n");
  fMoveTo(t->onTrigger, t->x + dx, t->y + dy);
  queueEnqueue(g->arena, t->onTrigger);
  fprintf(g->txt, "DSP: Disparador %d\n", tid);
  txtFigInfo(g->txt, t->onTrigger);
  if (m == 'v')
    fprintf(g->svg,
            "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" "
            "stroke-dasharray=\"5,5\" stroke=\"red\" fill=\"blue\" "
            "fill-opacity=\"0\"/>\n",
            t->x, t->y, t->x + dx, t->y + dy);
  g->totalSho++;
  t->onTrigger = NULL;
}

static void processRjd(Game *g, char *params) {
  int tid;
  char d;
  double dx, dy, ix, iy;

  if (sscanf(params, "%d %c %lf %lf %lf %lf", &tid, &d, &dx, &dy, &ix, &iy) !=
      6)
    return;

  Trigger *t = triggerFind(g, tid);
  if (!t)
    return;

  if (d != 'd' && d != 'e')
    return;

  Stack from = (d == 'e') ? t->left->st : t->right->st;
  int i = 1;
  fprintf(g->txt, "RJD: Disparador %d\n", tid);
  printf("right: %d\n", stackGetSize(t->right->st));
  printf("left: %d\n", stackGetSize(t->left->st));
  if (t->onTrigger != NULL) {
    txtFigInfo(g->txt, t->onTrigger);
    fMoveTo(t->onTrigger, t->x + dx + i * ix, t->y + dy + i * iy);
    queueEnqueue(g->arena, t->onTrigger);
    g->totalSho++;
    i++;
  }
  printf("from: %d\n", stackGetSize(from));
  printf("não passou\n");
  while (!stackIsEmpty(from)) {
    t->onTrigger = stackPop(from);
    printf("passou\n");
    if (!t->onTrigger)
      break;

    txtFigInfo(g->txt, t->onTrigger);
    fMoveTo(t->onTrigger, t->x + dx + i * ix, t->y + dy + i * iy);
    queueEnqueue(g->arena, t->onTrigger);
    i++;
    g->totalSho++;
  }
  t->onTrigger = NULL;
}

static void processCalc(Game *g) {
  Figure *f1, *f2;
  char colorF[8], colorB[8], dump[8];
  double areaR;
  fprintf(g->txt, "CALC\n");
  while (!queueIsEmpty(g->arena)) {
    areaR = 0;
    printf("\tentrou no while\n");
    int maior, menor;
    f1 = queueDequeue(g->arena);
    if (!f1) {
      printf("\t!f1");
      return;
    }
    printf("\tf1\n");
    f2 = queueDequeue(g->arena);
    if (!f2) {
      queueEnqueue(g->ground, f1);
      return;
    }
    printf("\tf2\n");
    if (!figuresOverlap(f1, f2)) {
      printf("\tnao tem overlap\n");
      queueEnqueue(g->ground, f1);
      queueEnqueue(g->ground, f2);
      continue;
    }
    printf("\ttem overlap\n");
    double area1 = figureArea(f1);
    double area2 = figureArea(f2);
    double x, y;
    if (area1 >= area2) {
      areaR += area2;
      maior = getFigureId(f1);
      menor = getFigureId(f2);
      getFigureXY(&x, &y, f2);
      getFigureColors(f1, dump, colorF);
      getFigureColors(f2, colorB, dump);
      putFigureColor(f2, colorB, colorF);

      Figure clone = fClone(f1);
      figureInvertColors(clone);

      queueEnqueue(g->ground, f1);
      queueEnqueue(g->ground, f2);
      queueEnqueue(g->ground, clone);

      g->points += area2;
      g->totalClo++;
    } else {
      areaR += area1;
      maior = getFigureId(f2);
      menor = getFigureId(f1);
      getFigureXY(&x, &y, f1);
      figureFree(f1);
      queueEnqueue(g->ground, f2);
      g->points += area1;
    }
    fprintf(g->txt, "Figura %d e maior que Figura %d\n", maior, menor);
    fprintf(g->txt, "Area Esmagada Round: %lf\n", areaR);
    fprintf(g->svg, "<circle r=\"5\" x=\"%lf\" y=\"%lf\" fill=\"red\" />\n", x,
            y);
    g->totalSma++;
  }
  fprintf(g->txt, "Area Esmagada total: %lf\n", g->points);
}

static void processQryLine(Game *g, const char *line) {
  char command[6], params[506];
  memset(command, 0, sizeof(command));
  memset(params, 0, sizeof(params));

  sscanf(line, "%5s %505[^\n]", command, params);
  printf("Command: %s\n", command);
  if (!strcmp(command, "pd")) {
    processPd(g, params);
    g->totalIns++;
  } else if (!strcmp(command, "lc")) {
    processLc(g, params);
    g->totalIns++;
  } else if (!strcmp(command, "atch")) {
    processAtch(g, params);
    g->totalIns++;
  } else if (!strcmp(command, "shft")) {
    processShft(g, params);
    g->totalIns++;
  } else if (!strcmp(command, "dsp")) {
    processDsp(g, params);
    g->totalIns++;
  } else if (!strcmp(command, "rjd")) {
    processRjd(g, params);
    g->totalIns++;
  } else if (!strcmp(command, "calc")) {
    processCalc(g);
    g->totalIns++;
  }
}

void processQryFile(Queue ground, const char *qryPath, FILE *txtFile,
                    FILE *svgFile) {
  if (queueIsEmpty(ground))
    return;
  printf("ground");
  Game *game = gameInit();
  game->ground = ground;
  printf(qryPath);
  FILE *qryFile = fopen(qryPath, "r");
  if (!qryFile)
    return;
  printf("qryFile");

  game->svg = svgFile;
  if (!game->svg) {
    fclose(qryFile);
    return;
  }
  printf("svgFile");

  game->txt = txtFile;
  if (!game->txt) {
    fclose(qryFile);
    fclose(game->svg);
    return;
  }

  char line[512];
  while (fgets(line, sizeof(line), qryFile)) {
    processQryLine(game, line);
  }
  fprintf(game->txt,
          "Pontuacao Final: %lf\nTotal de Instrucoes: %d\nTotal Disparos: "
          "%d\nTotal Formas Esmagadas: %d\nTotal Formas Clonadas: %d",
          game->points, game->totalIns, game->totalSho, game->totalSma,
          game->totalClo);
  gameFree(game);
}
