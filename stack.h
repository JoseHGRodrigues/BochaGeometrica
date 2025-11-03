#ifndef STACK_H
#define STACK_H

#include <stdbool.h> // Para usar os tipos 'true' e 'false'
#include <stdio.h>

/**
 * @brief Um tipo opaco para uma pilha (Stack) dinâmica.
 * A implementação real (struct stack) está escondida em stack.c.
 */
typedef void *Stack;

/**
 * @brief Aloca e inicializa uma nova pilha vazia.
 * @return Um ponteiro (Stack) para a nova pilha, ou NULL se a alocação falhar.
 */
Stack stackInit();

/**
 * @brief Liberta toda a memória associada à pilha.
 * Liberta todos os nós internos da pilha.
 *
 * @warning Esta função NÃO liberta a memória dos dados (os ponteiros void*)
 * que foram empilhados. O utilizador é responsável por esvaziar a pilha
 * e libertar os dados (se necessário) antes de chamar esta função.
 *
 * @param s A pilha a ser libertada.
 */
void stackFree(Stack s);

/**
 * @brief Adiciona um item (ponteiro) ao topo da pilha.
 * @param s A pilha.
 * @param data O ponteiro (void*) para o dado a ser armazenado.
 * @return 1 em caso de sucesso, 0 se a pilha for NULL ou falhar a alocação
 * de memória.
 */
int stackPush(Stack s, void *data);

/**
 * @brief Remove e retorna o item (ponteiro) do topo da pilha.
 * @param s A pilha.
 * @return O ponteiro (void*) que estava no topo, ou NULL se a pilha
 * estiver vazia ou for NULL.
 */
void *stackPop(Stack s);

/**
 * @brief Retorna o item (ponteiro) do topo da pilha SEM o remover.
 * @param s A pilha.
 * @return O ponteiro (void*) que está no topo, ou NULL se a pilha
 * estiver vazia ou for NULL.
 */
void *stackTop(Stack s);

/**
 * @brief Verifica se a pilha está vazia.
 * @param s A pilha.
 * @return true (verdadeiro) se a pilha estiver vazia ou for NULL,
 * false (falso) caso contrário.
 */
bool stackIsEmpty(Stack s);

/**
 * @brief Obtém o número atual de elementos na pilha.
 * @param s A pilha.
 * @return O número de elementos, ou -1 se a pilha for NULL.
 */
int stackGetSize(Stack s);

#endif // STACK_H
