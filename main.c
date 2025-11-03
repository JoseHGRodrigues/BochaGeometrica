#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "figure.h"
#include "geo.h"
#include "qry.h"
#include "queue.h"
#include "svg.h"

typedef struct {
  char *bed;
  char *bsd;
  char *geo_nome;
  char *qry_nome;

  char *full_geo_path;
  char *full_qry_path;

  char *out_geo_svg;
  char *out_qry_svg;
  char *out_qry_txt;

} Config;

static char *getBaseName(const char *filename) {
  const char *filename_part = strrchr(filename, '/');
  if (filename_part) {
    filename_part = filename_part + 1;
  } else {
    filename_part = filename;
  }
  const char *dot = strrchr(filename_part, '.');
  size_t len;
  if (!dot || dot == filename_part) {
    len = strlen(filename_part);
  } else {
    len = dot - filename_part;
  }
  char *basename = (char *)malloc(len + 1);
  if (basename == NULL)
    exit(EXIT_FAILURE);

  strncpy(basename, filename_part, len);
  basename[len] = '\0';
  return basename;
}

void constrNameExit(Config *config) {
  char buffer[1024];
  char *geo_base = getBaseName(config->geo_nome);
  snprintf(buffer, sizeof(buffer), "%s/%s.svg", config->bsd, geo_base);
  config->out_geo_svg = strdup(buffer);
  if (config->qry_nome) {
    char *qry_base = getBaseName(config->qry_nome);
    snprintf(buffer, sizeof(buffer), "%s/%s-%s.svg", config->bsd, geo_base,
             qry_base);
    config->out_qry_svg = strdup(buffer);
    snprintf(buffer, sizeof(buffer), "%s/%s-%s.txt", config->bsd, geo_base,
             qry_base);
    config->out_qry_txt = strdup(buffer);
    free(qry_base);
  }
  free(geo_base);
}

static char *joinPath(const char *base, const char *file) {
  size_t len = strlen(base) + 1 + strlen(file) + 1;
  char *full_path = malloc(len);
  if (!full_path)
    exit(EXIT_FAILURE);
  snprintf(full_path, len, "%s/%s", base, file);
  return full_path;
}

void parseArg(int argc, char *argv[], Config *config) {
  config->bed = ".";
  config->bsd = NULL;
  config->geo_nome = NULL;
  config->qry_nome = NULL;

  char *bed_arg = NULL;
  char *bsd_arg = NULL;
  char *geo_arg = NULL;
  char *qry_arg = NULL;

  int opt;
  while ((opt = getopt(argc, argv, "e:f:o:q:")) != -1) {
    switch (opt) {
    case 'e':
      bed_arg = optarg;
      break;
    case 'f':
      geo_arg = optarg;
      break;
    case 'o':
      bsd_arg = optarg;
      break;
    case 'q':
      qry_arg = optarg;
      break;
    case '?':
      fprintf(stderr,
              "Usage: %s -f <arq.geo> -o <path> [-e <path>] [-q <arq.qry>]\n",
              argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  if (!geo_arg || !bsd_arg)
    exit(EXIT_FAILURE);

  if (bed_arg)
    config->bed = strdup(bed_arg);
  else
    config->bed = strdup(".");

  config->bsd = strdup(bsd_arg);
  config->geo_nome = strdup(geo_arg);
  if (qry_arg)
    config->qry_nome = strdup(qry_arg);

  config->full_geo_path = joinPath(config->bed, config->geo_nome);
  if (config->qry_nome)
    config->full_qry_path = joinPath(config->bed, config->qry_nome);

  constrNameExit(config);
}

void freeConfig(Config *config) {
  free(config->bed);
  free(config->bsd);
  free(config->geo_nome);
  free(config->qry_nome);
  free(config->full_geo_path);
  free(config->full_qry_path);
  free(config->out_geo_svg);
  free(config->out_qry_svg);
  free(config->out_qry_txt);
}

int main(int argc, char *argv[]) {
  Config config = {0};
  parseArg(argc, argv, &config);
  Queue figureList = queueInit();

  FILE *svgGeo = fopen(config.out_geo_svg, "w");
  if (!svgGeo)
    return 1;
  svgInit(svgGeo);

  FILE *svgQry = fopen(config.out_qry_svg, "w");
  if (!svgQry)
    return 1;
  svgInit(svgQry);

  FILE *txtQry = fopen(config.out_qry_txt, "w");
  if (!txtQry)
    return 1;

  processGeoFile(config.full_geo_path, figureList);
  svgDrawAll(svgGeo, figureList);
  svgClose(svgGeo);
  fclose(svgGeo);

  processQryFile(figureList, config.full_qry_path, txtQry, svgQry);
  svgDrawAll(svgQry, figureList);
  svgClose(svgQry);
  fclose(svgQry);
  fclose(txtQry);

  while (!queueIsEmpty(figureList)) {
    Figure f = queueDequeue(figureList);
    figureFree(f);
  }
  queueFree(figureList);
  freeConfig(&config);

  return 0;
}
