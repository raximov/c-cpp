#include "s21_containers.h"

// --- РЕАЛИЗАЦИЯ СТЕКА (LIFO) ---
Stack* create_stack() {
  Stack* s = (Stack*)malloc(sizeof(Stack));
  if (s) {
    s->top_node = NULL;
    s->size = 0;
  }
  return s;
}

void push_stack(Stack* s, int value) {
  if (!s) return;
  Node* new_node = (Node*)malloc(sizeof(Node));
  if (new_node) {
    new_node->value = value;
    new_node->next = s->top_node;
    s->top_node = new_node;
    s->size++;
  }
}

int pop_stack(Stack* s) {
  if (!s || is_empty_stack(s)) return -1;
  Node* temp = s->top_node;
  int val = temp->value;
  s->top_node = s->top_node->next;
  free(temp);
  s->size--;
  return val;
}

int top_stack(Stack* s) {
  if (!s || is_empty_stack(s)) return -1;
  return s->top_node->value;
}

bool is_empty_stack(Stack* s) { return !s || s->size == 0; }

void free_stack(Stack* s) {
  if (!s) return;
  while (!is_empty_stack(s)) {
    pop_stack(s);
  }
  free(s);
}

// --- РЕАЛИЗАЦИЯ ОЧЕРЕДИ (FIFO) ---
Queue* create_queue() {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  if (q) {
    q->front_node = q->back_node = NULL;
    q->size = 0;
  }
  return q;
}

void push_queue(Queue* q, int value) {
  if (!q) return;
  Node* new_node = (Node*)malloc(sizeof(Node));
  if (new_node) {
    new_node->value = value;
    new_node->next = NULL;
    if (q->back_node == NULL) {
      q->front_node = q->back_node = new_node;
    } else {
      q->back_node->next = new_node;
      q->back_node = new_node;
    }
    q->size++;
  }
}

int pop_queue(Queue* q) {
  if (!q || is_empty_queue(q)) return -1;
  Node* temp = q->front_node;
  int val = temp->value;
  q->front_node = q->front_node->next;
  if (q->front_node == NULL) {
    q->back_node = NULL;
  }
  free(temp);
  q->size--;
  return val;
}

int front_queue(Queue* q) {
  if (!q || is_empty_queue(q)) return -1;
  return q->front_node->value;
}

int back_queue(Queue* q) {
  if (!q || is_empty_queue(q)) return -1;
  return q->back_node->value;
}

bool is_empty_queue(Queue* q) { return !q || q->size == 0; }

void free_queue(Queue* q) {
  if (!q) return;
  while (!is_empty_queue(q)) {
    pop_queue(q);
  }
  free(q);
}
