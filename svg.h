#ifndef SVG_H
#define SVG_H

#include "figure.h" // Dependência para o tipo 'Figure'
#include "queue.h"  // Dependência para o tipo 'Queue'
#include <stdio.h>

/**
 * @brief Escreve o cabeçalho SVG (tag <svg>) em um arquivo.
 * @param svgFile Ponteiro para o arquivo SVG (aberto para escrita).
 */
void svgInit(FILE *svgFile);

/**
 * @brief Escreve o rodapé SVG (tag </svg>) em um arquivo.
 * @param svgFile Ponteiro para o arquivo SVG.
 */
void svgClose(FILE *svgFile);

/**
 * @brief Desenha uma única figura no arquivo SVG.
 * * Esta função chama a função 'getter' apropriada de 'figure.h'
 * para determinar o tipo da figura (getFigureShape) e, em seguida,
 * chama os getters específicos (getCircleX, getRectangleW, getTextTxt, etc.)
 * para desenhar o elemento SVG correspondente.
 *
 * @param svgFile Ponteiro para o arquivo SVG.
 * @param f A figura (Figure) a ser desenhada.
 */
void svgDrawFigure(FILE *svgFile, Figure f);

/**
 * @brief Itera sobre uma fila de figuras (usando queue.h) e
 * desenha cada uma (usando svgDrawFigure).
 * * Preserva a fila original ao final da execução.
 *
 * @param svgFile Ponteiro para o arquivo SVG.
 * @param figureList A fila (Queue) contendo as figuras (Figure).
 */
void svgDrawAll(FILE *svgFile, Queue figureList);

#endif // SVG_H
