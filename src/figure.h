#ifndef FIGURE_H
#define FIGURE_H

// --- Tipos de Figuras ---
// Removidos pontos e vírgulas extra
#define CIRCLE 1
#define RECTANGLE 2
#define LINE 3
#define TEXT 4

/**
 * @brief Um tipo opaco para uma figura geométrica.
 * A implementação real (struct figure) está escondida em figure.c.
 */
typedef void *Figure;

/**
 * @brief Aloca e inicializa uma nova figura do tipo especificado.
 * @param shape O tipo da figura (CIRCLE, RECTANGLE, LINE, TEXT).
 * @return Um ponteiro (Figure) para a nova figura, ou NULL se a alocação falhar
 * ou o tipo for inválido.
 */
Figure figureInit(int shape);

/**
 * @brief Liberta toda a memória associada a uma figura.
 * @param f A figura a ser libertada.
 */
void figureFree(Figure f);

/**
 * @brief Configura as propriedades de uma figura do tipo Círculo.
 * @param f A figura (deve ser do tipo CIRCLE).
 * @param id ID numérico da figura.
 * @param x Coordenada X do centro.
 * @param y Coordenada Y do centro.
 * @param r Raio do círculo.
 * @param colorB Cor da borda (formato hexadecimal, ex: "#FF0000").
 * @param colorF Cor de preenchimento (formato hexadecimal).
 */
void setCircle(Figure f, int id, double x, double y, double r,
               const char *colorB, const char *colorF);

/**
 * @brief Configura as propriedades de uma figura do tipo Retângulo.
 * @param f A figura (deve ser do tipo RECTANGLE).
 * @param id ID numérico da figura.
 * @param x Coordenada X do canto superior esquerdo.
 * @param y Coordenada Y do canto superior esquerdo.
 * @param w Largura (width) do retângulo.
 * @param h Altura (height) do retângulo.
 * @param colorB Cor da borda (formato hexadecimal).
 * @param colorF Cor de preenchimento (formato hexadecimal).
 */
void setRectangle(Figure f, int id, double x, double y, double w, double h,
                  const char *colorB, const char *colorF);

/**
 * @brief Configura as propriedades de uma figura do tipo Linha.
 * @param f A figura (deve ser do tipo LINE).
 * @param id ID numérico da figura.
 * @param x1 Coordenada X do ponto inicial.
 * @param y1 Coordenada Y do ponto inicial.
 * @param x2 Coordenada X do ponto final.
 * @param y2 Coordenada Y do ponto final.
 * @param color Cor da linha (formato hexadecimal).
 */
void setLine(Figure f, int id, double x1, double y1, double x2, double y2,
             const char *color);

/**
 * @brief Configura as propriedades de uma figura do tipo Texto.
 * @param f A figura (deve ser do tipo TEXT).
 * @param id ID numérico da figura.
 * @param x Coordenada X do ponto de âncora.
 * @param y Coordenada Y do ponto de âncora.
 * @param colorB Cor da borda/contorno do texto.
 * @param colorF Cor de preenchimento do texto.
 * @param anchor Ponto de âncora do texto ('i' - início, 'm' - meio, 'f' - fim).
 * @param txt O conteúdo do texto.
 */
void setText(Figure f, int id, double x, double y, const char *colorB,
             const char *colorF, const char anchor, const char *txt);

/**
 * @brief Cria e retorna um clone (cópia profunda) de uma figura.
 * @param f A figura a ser clonada.
 * @return Uma nova figura (Figure) que é uma cópia de f, ou NULL se falhar.
 */
Figure fClone(Figure f);

/**
 * @brief Move a figura para uma nova posição (x, y).
 * Para linhas, move o ponto (x1, y1) para (x, y) e translada (x2, y2)
 * mantendo o vetor.
 * @param f A figura a ser movida.
 * @param x Nova coordenada X de referência.
 * @param y Nova coordenada Y de referência.
 */
void fMoveTo(Figure f, double x, double y);

/**
 * @brief Calcula a "área" de uma figura.
 * Nota: A definição de área para Linha e Texto é arbitrária neste módulo.
 * (Linha = 2 * comprimento, Texto = 20 * num_caracteres).
 * @param f A figura.
 * @return A área calculada, ou -1 se a figura for NULL.
 */
double figureArea(Figure f);

/**
 * @brief Inverte as cores da figura.
 * - Círculo, Retângulo, Texto: Troca cor de borda (colorB) com preenchimento
 * (colorF).
 * - Linha: Substitui a cor pela sua cor complementar.
 * @param f A figura a ser modificada.
 */
void figureInvertColors(Figure f);

/**
 * @brief Obtém o ID de uma figura.
 * @param f A figura.
 * @return O ID da figura, ou -1 se a figura for NULL.
 */
int getFigureId(Figure f);

/**
 * @brief Obtém a coordenada de referência (x, y) de uma figura.
 * (Centro para Círculo; Canto superior esquerdo para Retângulo; Ponto inicial
 * para Linha; Ponto de âncora para Texto).
 * @param x Ponteiro para armazenar a coordenada X.
 * @param y Ponteiro para armazenar a coordenada Y.
 * @param f A figura.
 */
void getFigureXY(double *x, double *y, Figure f);

/**
 * @brief Obtém as cores de borda e preenchimento de uma figura.
 * @param f A figura.
 * @param colorB Buffer de destino para a cor da borda (deve ter tamanho cLen).
 * @param colorF Buffer de destino para a cor de preenchimento (deve ter tamanho
 * cLen). Para Linha, colorF será preenchido com '\0'.
 */
void getFigureColors(Figure f, char *colorB, char *colorF);

/**
 * @brief Obtém o raio de um círculo.
 * @param f A figura (deve ser do tipo CIRCLE).
 * @return O raio, ou 0 se f não for um Círculo.
 */
double getCircleR(Figure f);

/**
 * @brief Obtém a largura (width) e altura (height) de um retângulo.
 * @param f A figura (deve ser do tipo RECTANGLE).
 * @param w Ponteiro para armazenar a largura.
 * @param h Ponteiro para armazenar a altura.
 */
void getRectangleWH(Figure f, double *w, double *h);

/**
 * @brief Obtém os pontos inicial (x1, y1) e final (x2, y2) de uma linha.
 * @param f A figura (deve ser do tipo LINE).
 * @param x1 Ponteiro para armazenar x1.
 * @param y1 Ponteiro para armazenar y1.
 * @param x2 Ponteiro para armazenar x2.
 * @param y2 Ponteiro para armazenar y2.
 */
void getLineP(Figure f, double *x1, double *y1, double *x2, double *y2);

/**
 * @brief Obtém o caractere de âncora de um texto.
 * @param f A figura (deve ser do tipo TEXT).
 * @return O caractere de âncora ('i', 'm', 'f'), ou '\0' se f não for Texto.
 */
char getTextA(Figure f);

/**
 * @brief Obtém o conteúdo de uma figura de texto.
 * @param f A figura (deve ser do tipo TEXT).
 * @param txt Buffer de destino para o texto (deve ter tamanho 64).
 */
void getTextTXT(Figure f, char *txt);

/**
 * @brief Define as cores de uma figura.
 * (O nome original no .h era figureColor, mas a implementação é
 * putFigureColor).
 * @param f A figura.
 * @param colorB Nova cor de borda (para Linha, esta é a única cor).
 * @param colorF Nova cor de preenchimento.
 */
void putFigureColor(Figure f, const char *colorB, const char *colorF);

/**
 * @brief Obtém o tipo (shape) de uma figura.
 * @param f A figura.
 * @return O tipo (CIRCLE, RECTANGLE, etc.), ou 0 se a figura for NULL.
 */
int getFigureShape(Figure f);

#endif
