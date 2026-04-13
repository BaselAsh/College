#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

LinkedList *start_linked_list() {
    LinkedList *linked_list = malloc(sizeof(LinkedList));
    linked_list->head = malloc(sizeof(Node));
    linked_list->head->data = 1;
    linked_list->head->next = NULL;
    linked_list->size = 1;
    return linked_list;
}

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void display_linked_list(Node *head) {
    Node *current_node = head;
    while (current_node != NULL) {
        printf("[%d]->", current_node->data);
        current_node = current_node->next;
    }
    printf("NULL\n");
}

void insert_at_beginning(Node *new, LinkedList *linked_list) {
    new->next = linked_list->head;
    linked_list->head = new;
    ++linked_list->size;
}

void insert_at_end(Node *new, LinkedList *linked_list) {
    Node *current_node = linked_list->head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    current_node->next = new;
    ++linked_list->size;
}

void free_linked_list(LinkedList *linked_list) {
    Node *current_node = linked_list->head;
    Node *temp;

    while (current_node != NULL) {
        temp = current_node->next;
        free(current_node);
        current_node = temp;
    }
    free(linked_list);
}

int main(int argc, char **argv) {
    printf("Welcome To Linked List App. :)\n");
    LinkedList *linked_list = start_linked_list();
    Node *new_node = create_node(666);
    Node *end_node = create_node(900);
    insert_at_beginning(new_node, linked_list);
    insert_at_end(end_node, linked_list);
    display_linked_list(linked_list->head);
    printf("Size of Linked List %d\n", linked_list->size);
    free_linked_list(linked_list);
    return 0;
}
