#ifndef OVERLAP_H
#define OVERLAP_H

#include "figure.h"

/**
 * @brief Verifica se duas figuras (f1 e f2) se sobrepõem.
 * * Esta função utiliza a geometria de cada figura para determinar a
 * interseção. Círculos, Retângulos e Linhas são tratados por suas definições
 * geométricas.
 * * Convenção para Texto:
 * Conforme especificado, uma figura do tipo TEXTO é tratada como um segmento
 * de linha horizontal para detecção de colisão. A função 'getTextP' de
 * 'figure.h' é usada para obter as coordenadas (x1,y1) e (x2,y2) deste
 * segmento.
 * * @param f1 A primeira figura.
 * @param f2 A segunda figura.
 * @return 1 (verdadeiro) se houver sobreposição, 0 (falso) caso contrário,
 * ou se uma das figuras for NULL.
 */
int figuresOverlap(Figure f1, Figure f2);

#endif // OVERLAP_H
