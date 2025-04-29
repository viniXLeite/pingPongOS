#include <stdio.h>
#include <stdlib.h>
#include "queue.h" // Busca no diretório atual

int main() {
    queue_t *head = NULL;
    
    printf("size: %d\n", queue_size(head));
    queue_print("Lista", head, print_elem);
    printf("\n");

    queue_t* n1 = (queue_t*) malloc(sizeof(queue_t));
    n1->data = 1;
    n1->prev = NULL;
    n1->next = NULL;
    
    int a = queue_append(&head, n1);

    printf("size: %d\n", queue_size(head));
    printf("queue apend: %d\n", a);
    queue_print("Lista", head, print_elem);

    // --------------------------------------------- // 
    queue_t* n2 = (queue_t*) malloc(sizeof(queue_t));
    n2->data = 2;
    n2->prev = NULL;
    n2->next = NULL;
    a = queue_append(&head, n2);

    printf("size: %d\n", queue_size(head));
    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);

    // --------------------------------------------- // 
    queue_t* n3 = (queue_t*) malloc(sizeof(queue_t));
    n3->data = 3;
    n3->prev = NULL;
    n3->next = NULL;
    a = queue_append(&head, n3);

    printf("size: %d\n", queue_size(head));
    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);

    // --------------------------------------------- // 
    queue_t* n4 = (queue_t*) malloc(sizeof(queue_t));
    n4->data = 4;
    n4->prev = NULL;
    n4->next = NULL;
    a = queue_append(&head, n4);

    printf("size: %d\n", queue_size(head));
    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);

    // --------------------------------------------- // 
    queue_t* n5 = (queue_t*) malloc(sizeof(queue_t));
    n5->data = 5;
    n5->prev = NULL;
    n5->next = NULL;
    a = queue_append(&head, n5);

    printf("size: %d\n", queue_size(head));
    printf("queue apend: %d\n", a);
    queue_print("ok", head, print_elem);

    int rm;

    rm = queue_remove(&head, n3);
    printf("rm: %d\n", rm);
    printf("size: %d\n", queue_size(head));
    queue_print("ok", head, print_elem);

    rm = queue_remove(&head, n1);
    printf("rm: %d\n", rm);
    printf("size: %d\n", queue_size(head));
    queue_print("ok", head, print_elem);

    rm = queue_remove(&head, n5);
    printf("rm: %d\n", rm);
    printf("size: %d\n", queue_size(head));
    queue_print("ok", head, print_elem);

    rm = queue_remove(&head, n5);
    printf("rm: %d\n", rm);
    printf("size: %d\n", queue_size(head));
    queue_print("ok", head, print_elem);

    rm = queue_remove(&head, n2);
    printf("rm: %d\n", rm);
    printf("size: %d\n", queue_size(head));
    queue_print("ok", head, print_elem);

    rm = queue_remove(&head, n4);
    printf("rm: %d\n", rm);
    printf("size: %d\n", queue_size(head));
    queue_print("ok", head, print_elem);

    return 0;
}