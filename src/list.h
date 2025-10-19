#ifndef LIST_H
#define LIST_H

#include <stdbool.h> // Para usar os tipos 'true' e 'false'
#include <stdio.h>

/**
 * @brief Um tipo opaco para uma Lista Simplesmente Ligada (List).
 * A implementação real (struct list) está escondida em list.c.
 */
typedef void *List;

/**
 * @brief Aloca e inicializa uma nova lista vazia.
 * @return Um ponteiro (List) para a nova lista, ou NULL se a alocação falhar.
 */
List listInit();

/**
 * @brief Liberta toda a memória associada à lista (incluindo os nós).
 *
 * @param l A lista a ser libertada.
 * @param freeData Uma função ponteiro (opcional) que será chamada para
 * libertar a memória de cada dado (void*) armazenado na lista.
 * Se for NULL, os dados em si não serão libertados, apenas os nós da lista.
 */
void listFree(List l, void (*freeData)(void *data));

/**
 * @brief Insere um dado (ponteiro) no final da lista (append).
 * Esta é a única forma de inserção nesta implementação.
 *
 * @param l A lista.
 * @param data O ponteiro (void*) para o dado a ser armazenado.
 * @return 1 em caso de sucesso, 0 se a lista for NULL ou falhar a alocação.
 */
int listInsertLast(List l, void *data);

/**
 * @brief Remove e retorna o dado (ponteiro) do início da lista.
 * Esta é a única forma de remoção nesta implementação.
 *
 * @param l A lista.
 * @return O ponteiro (void*) que estava no início, ou NULL se a lista
 * estiver vazia ou for NULL.
 */
void *listRemoveFirst(List l);

/**
 * @brief Retorna o dado (ponteiro) do início da lista SEM o remover.
 * @param l A lista.
 * @return O ponteiro (void*) que está no início, ou NULL se a lista
 * estiver vazia ou for NULL.
 */
void *listGetFirst(List l);

/**
 * @brief Retorna o dado (ponteiro) do final da lista SEM o remover.
 * @param l A lista.
 * @return O ponteiro (void*) que está no final, ou NULL se a lista
 * estiver vazia ou for NULL.
 */
void *listGetLast(List l);

/**
 * @brief Verifica se a lista está vazia.
 * @param l A lista.
 * @return true (verdadeiro) se a lista estiver vazia ou for NULL,
 * false (falso) caso contrário.
 */
bool listIsEmpty(List l);

#endif // LIST_H
