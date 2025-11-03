#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h> // Para usar os tipos 'true' e 'false'
#include <stdio.h>

/**
 * @brief Um tipo opaco para uma fila (Queue) dinâmica.
 * A implementação real (struct queue) está escondida em queue.c.
 */
typedef void *Queue;

typedef void *Data;
/**
 * @brief Aloca e inicializa uma nova fila vazia.
 * @return Um ponteiro (Queue) para a nova fila, ou NULL se a alocação
 * falhar.
 */
Queue queueInit();

/**
 * @brief Liberta toda a memória associada à fila.
 * Liberta todos os nós internos da fila.
 *
 * @warning Esta função NÃO liberta a memória dos dados (os ponteiros void*)
 * que foram enfileirados. O utilizador é responsável por esvaziar a fila
 * e libertar os dados (se necessário) antes de chamar esta função.
 *
 * @param q A fila a ser libertada.
 */
void queueFree(Queue q);

/**
 * @brief Adiciona um item (ponteiro) ao final (rear) da fila.
 * @param q A fila.
 * @param data O ponteiro (void*) para o dado a ser armazenado.
 * @return 1 em caso de sucesso, 0 se a fila for NULL ou falhar a alocação
 * de memória.
 */
int queueEnqueue(Queue q, void *data);

/**
 * @brief Remove e retorna o item (ponteiro) do início (front) da fila.
 * @param q A fila.
 * @return O ponteiro (void*) que estava no início, ou NULL se a fila
 * estiver vazia ou for NULL.
 */
void *queueDequeue(Queue q);

/**
 * @brief Verifica se a fila está vazia.
 * @param q A fila.
 * @return true (verdadeiro) se a fila estiver vazia ou for NULL,
 * false (falso) caso contrário.
 */
bool queueIsEmpty(Queue q);

/**
 * @brief Obtém o número atual de elementos na fila.
 * @param q A fila.
 * @return O número de elementos, ou -1 se a fila for NULL.
 */
int queueGetSize(Queue q);

#endif // QUEUE_H
