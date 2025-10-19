#ifndef GEO_H
#define GEO_H

#include "list.h" // Este módulo precisa saber o que é 'List'

/**
 * @brief Processa um arquivo .geo, lendo as figuras e as adicionando
 * a uma lista.
 *
 * Esta função abre o arquivo .geo, lê cada linha (c, r, l, t)
 *, cria a figura correspondente (usando 'figure.h') e
 * a insere no final da 'figureList' (usando 'list.h').
 *
 * @param geoFilePath O caminho completo para o arquivo .geo a ser lido
 * (ex: "./t-2figs-alet.geo").
 * @param figureList A lista (já inicializada com listInit) onde as
 * figuras criadas serão armazenadas.
 */
void processGeoFile(const char *geoFilePath, List figureList);

#endif // GEO_H
