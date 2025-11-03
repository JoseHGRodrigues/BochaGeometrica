#ifndef QRY_H
#define QRY_H

#include "queue.h"
#include <stdio.h>

/**
 * @brief Processa um arquivo de consulta .qry, executando os comandos
 * e atualizando o estado do jogo.
 *
 * Esta função lê o arquivo .qry linha por linha, interpreta os comandos
 * (pd, lc, atch, shft, dsp, rjd, calc) e utiliza as estruturas de dados
 * (pilhas, filas, figuras) para simular o jogo "Bocha Geométrica".
 *
 * A função primeiro determina o ID máximo das figuras presentes na fila 'chao'
 * para garantir que os clones gerados tenham IDs únicos.
 *
 * @param chao A fila (Queue) de figuras (Figure) que representa o "chão".
 * Figuras são removidas desta fila pelo comando 'lc'
 * e retornadas a ela pelo comando 'calc'.
 * @param qryPath O caminho do arquivo .qry a ser lido.
 * @param txtPath O caminho do arquivo .txt de log a ser escrito.
 * @param svgPath O caminho do arquivo .svg onde anotações (como disparos
 * e formas esmagadas) serão escritas.
 */
void processQryFile(Queue ground, const char *qryPath, FILE *txtFile,
                    FILE *svgFile);

#endif // QRY_H
