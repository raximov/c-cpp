#ifndef S21_CONTAINERS_H
#define S21_CONTAINERS_H

#include <stdbool.h>
#include <stdlib.h>

// Узел списка для хранения элементов
typedef struct Node {
  int value;
  struct Node* next;
} Node;

// Структура Стек (LIFO)
typedef struct Stack {
  Node* top_node;
  int size;
} Stack;

// Структура Очередь (FIFO)
typedef struct Queue {
  Node* front_node;
  Node* back_node;
  int size;
} Queue;

// Интерфейс Стека по ТЗ
Stack* create_stack();
void push_stack(Stack* s, int value);
int pop_stack(Stack* s);
int top_stack(Stack* s);
bool is_empty_stack(Stack* s);
void free_stack(Stack* s);

// Интерфейс Очереди по ТЗ
Queue* create_queue();
void push_queue(Queue* q, int value);
int pop_queue(Queue* q);
int front_queue(Queue* q);
int back_queue(Queue* q);
bool is_empty_queue(Queue* q);
void free_queue(Queue* q);

#endif  // S21_CONTAINERS_H
