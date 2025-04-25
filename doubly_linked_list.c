#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef struct queue_t {
    int data;
    struct queue_t *next;
    struct queue_t *prev;
} queue_t;


int queue_size (queue_t *queue) {
    int size = 0;
    queue_t* current = queue;
    queue_t* head =  queue;

    if (queue == NULL) return 0; // Caso a lista esteja vazia 

    while (current->next != head) {
        size++;
        current = current->next;
    }

    return size+1;
}


int queue_append (queue_t **queue, queue_t *elem) {
    // Deferencia o ponteiro o ponteiro de ponteiro
    queue_t *head = *queue;
    queue_t *current = *queue;

    // Trata o caso da lista estar vazia
    if ((*queue) == NULL) {
        
        (*queue) = elem; // Utiliza o espaço alocado para 'elem'
        (*queue)->data = elem->data;
        (*queue)->next = (*queue);
        (*queue)->prev = (*queue);
        
        return 0;
    }

    else {
        // Percorre a lista até encontrar a cauda dela        
        while (current->next != head) {
            current = current->next;
        }
        // Adiciona elem ao último nó da lista
        current->next = elem;
        elem->prev = current;
        elem->next = head;
    }
    
    if (elem->prev == current && elem->next == head) {
        return 0;
    }
    else return -1;
}


void print_elem (void *ptr) {
    queue_t* elem = (queue_t*) ptr; // Atribui o tipo queue para ptr
    printf("%d, ", elem->data);
    return;
}


void queue_print (char* name, queue_t *queue, void print_elem (void*) ) {
    queue_t *head = queue;
    queue_t *current =  queue;
    
    // Verifica se a lisra está vazia
    if (queue == NULL) {
        printf("NULL papai");
        return;
    }
    
    else {
        print_elem(current);
        while (current->next != head) {
            current = current->next;
            print_elem(current);
        }
    }
    printf("\n");
}


// Ver se funciona
int queue_remove (queue_t **queue, queue_t *elem) {
    queue_t *head = *queue;
    queue_t *tail = *queue;
    queue_t *current = *queue;
    queue_t *node = NULL;

    if (*queue == NULL) return -1;
    
    else {
        // Verifica se o elem pertence à lista
        while (current->next != head) {
            if (current == elem) {
                node = current;
                current = current->next;
            }
            else current = current->next;
        }
 
        tail = current; // Armazena o valor da cauda da lista

        // Caso em que o elem não pertence à lista
        if (node == NULL) return -1;

        // Caso em que o elem pertece à lista
        else {
            if (node == head) {
                node->next->prev = tail;
                tail->next = node->next;
                head = node->next;
            }
            else if (node == tail) {
                node->prev->next = head;
                head->prev = node->prev;
                tail = node->prev; // Verificar se essa linha faz sentido
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
        }

    }

}


int main() {
    queue_t *head = NULL;
    
    printf("size: %d\n", queue_size(head));

    queue_t* n1 = (queue_t*) malloc(sizeof(queue_t));
    n1->data = 1;
    n1->prev = NULL;
    n1->next = NULL;
    
    int a = queue_append(&head, n1);
    printf("queue apend: %d\n", a);
    queue_print("Lista", head, print_elem);
    printf("size: %d\n", queue_size(head));

    // --------------------------------------------- // 
    queue_t* n2 = (queue_t*) malloc(sizeof(queue_t));
    n2->data = 2;
    n2->prev = NULL;
    n2->next = NULL;
    a = queue_append(&head, n2);

    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);
    printf("size: %d\n", queue_size(head));

    // --------------------------------------------- // 
    queue_t* n3 = (queue_t*) malloc(sizeof(queue_t));
    n3->data = 3;
    n3->prev = NULL;
    n3->next = NULL;
    a = queue_append(&head, n3);

    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);
    printf("size: %d\n", queue_size(head));

    // --------------------------------------------- // 
    queue_t* n4 = (queue_t*) malloc(sizeof(queue_t));
    n4->data = 4;
    n4->prev = NULL;
    n4->next = NULL;
    a = queue_append(&head, n4);

    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);
    printf("size: %d\n", queue_size(head));

    // --------------------------------------------- // 
    queue_t* n5 = (queue_t*) malloc(sizeof(queue_t));
    n5->data = 5;
    n5->prev = NULL;
    n5->next = NULL;
    a = queue_append(&head, n5);

    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);
    printf("size: %d\n", queue_size(head));

    return 0;
}