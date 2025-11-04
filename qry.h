#ifndef QRY_H
#define QRY_H

#include "queue.h"
#include <stdio.h>

/**
 * @brief Processa um arquivo de consulta .qry, executando os comandos
 * e atualizando o estado do jogo.
 * @param chao A Queue de Figures que representa o "chão".
 * @param qryPath O caminho do arquivo .qry a ser lido.
 * @param txtPath O caminho do arquivo .txt de log a ser escrito.
 * @param svgPath O caminho do arquivo .svg onde anotações serao escritas.
 */
void processQryFile(Queue ground, const char *qryPath, FILE *txtFile,
                    FILE *svgFile);

#endif // QRY_H
