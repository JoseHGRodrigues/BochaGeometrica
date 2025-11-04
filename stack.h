#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief tipo opaco para uma stack.
 */
typedef void *Stack;

/**
 * @brief Aloca e inicializa uma nova stack vazia.
 * @return Um ponteiro Stack para a nova stack, ou NULL se a alocação falhar.
 */
Stack stackInit();

/**
 * @brief Liberta toda a memória associada à stack.
 * @param s A stack a ser libertada.
 */
void stackFree(Stack s);

/**
 * @brief Adiciona um item (ponteiro) ao topo da pilha.
 * @param s A stack.
 * @param data O ponteiro (void*) para o dado a ser armazenado.
 * @return 1 em caso de sucesso, 0 se a pilha for NULL ou falhar a alocação
 */
int stackPush(Stack s, void *data);

/**
 * @brief Remove e retorna o item (ponteiro) do topo da stack.
 * @param s A stack.
 * @return O ponteiro (void*) que estava no topo, ou NULL se a stack estiver
 * vazia ou NULL.
 */
void *stackPop(Stack s);

/**
 * @brief Retorna o item (ponteiro) do topo da stack SEM o remover.
 * @param s A stack.
 * @return O ponteiro (void*) que está no topo, ou NULL se a stack
 * estiver vazia ou for NULL.
 */
void *stackTop(Stack s);

/**
 * @brief Verifica se a stack está vazia.
 * @param s A stack.
 * @return true (verdadeiro) se a stack estiver vazia ou for NULL,
 * false (falso) caso contrário.
 */
bool stackIsEmpty(Stack s);

/**
 * @brief Obtém o número atual de elementos na stack.
 * @param s A stack.
 * @return O número de elementos, ou -1 se a stack for NULL.
 */
int stackGetSize(Stack s);

#endif // STACK_H
