#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} List;

typedef struct {
    Node* current;
} Iterator;

void list_clear(List* list);
void list_delete_after(Node* prev_node);
List* list_create();
size_t list_length(const List* list);
void list_insert_to_begin(const char* data, List* list);
void list_insert_to_end(const char* data, List* list);
void list_insert_after(Node* prev_node, const char* data);
void list_delete_begin(List* list);
void list_delete_end(List* list);
void list_delete_last_k(List* list, size_t k);
void list_print(const List* list);
void list_destroy(List* list);
void print_commands();
int handle_input(char* command, List* list);
int input_option(char* command);


Node* create_node(const char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        exit(1);
    }
    new_node->data = strdup(data);
    new_node->next = NULL;
    return new_node;
}



List* list_create() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        exit(1);
    }
    list->head = NULL;
    return list;
}




Iterator iter_create(const List* list) {
    Iterator iter;
    iter.current = list->head;
    return iter;
}


void iter_next(Iterator* iter) {
    if (iter->current != NULL) {
        iter->current = iter->current->next;
    }
}


const char* iter_get_data(const Iterator* iter) {
    return (iter->current != NULL) ? iter->current->data : NULL;
}


void list_insert_to_begin(const char* data, List* list) {
    Node* new_node = create_node(data);
    new_node->next = list->head;
    list->head = new_node;
}

size_t list_length(const List* list) {
    size_t length = 0;
    Iterator iter = iter_create(list);
    while (iter.current != NULL) {
        length++;
        iter_next(&iter);
    }
    return length;
}


void list_insert_to_end(const char* data, List* list) {
    Node* new_node = create_node(data);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Iterator iter = iter_create(list);
        while (iter.current->next != NULL) {
            iter_next(&iter);
        }
        iter.current->next = new_node;
    }
}


void list_insert_after(Node* prev_node, const char* data) {
    if (prev_node == NULL) {
        printf("pusto\n");
        return;
    }
    Node* new_node = create_node(data);
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}


void list_delete_begin(List* list) {
    if (list->head == NULL) {
        printf("pusto\n");
        return;
    }
    Node* temp = list->head;
    list->head = list->head->next;
    free(temp->data);
    free(temp);
}


void list_delete_end(List* list) {
    if (list->head == NULL) {
        printf("pusto\n");
        return;
    }
    if (list->head->next == NULL) {
        free(list->head->data); 
        free(list->head);
        list->head = NULL;
    } else {
        Iterator iter = iter_create(list);
        while (iter.current->next->next != NULL) {
            iter_next(&iter);
        }
        free(iter.current->next->data); 
        free(iter.current->next);
        iter.current->next = NULL;
    }
}


void list_delete_after(Node* prev_node) {
    if (prev_node == NULL || prev_node->next == NULL) {
        printf("The previous node is NULL or no next node\n");
        return;
    }
    Node* temp = prev_node->next;
    prev_node->next = temp->next;
    free(temp->data);
    free(temp);
}


void list_delete_last_k(List* list, size_t k) {
    if (list->head == NULL) {
        printf("pusto\n");
        return;
    }
    size_t count = 0;
    Iterator iter = iter_create(list);
    while (iter.current != NULL) {
        count++;
        iter_next(&iter);
    }
    if (count < k) {
        printf("small list\n");
        return;
    }

    size_t target = count - k;
    iter = iter_create(list);
    Node* prev_node = NULL;
    for (size_t i = 0; i < target; i++) {
        prev_node = iter.current;
        iter_next(&iter);
    }

    if (prev_node != NULL) {
        Node* temp;
        while (prev_node->next != NULL) {
            temp = prev_node->next;
            prev_node->next = temp->next;
            free(temp->data); 
            free(temp);
        }
    } else {
        list_clear(list);
    }
}


void list_print(const List* list) {
    Iterator iter = iter_create(list);
    while (iter.current != NULL) {
        printf("%s ", iter_get_data(&iter));
        iter_next(&iter);
    }
    printf("\n");
}


void list_clear(List* list) {
    while (list->head != NULL) {
        list_delete_begin(list);
    }
}


void list_destroy(List* list) {
    list_clear(list);
    free(list);
}


void print_commands() {
    printf("Commands:\n");
    printf("print - Print list\n");
    printf("insert_end - Insert to end\n");
    printf("delete_end - Delete from end\n");
    printf("insert_begin - Insert to beginning\n");
    printf("delete_begin - Delete from beginning\n");
    printf("insert_after - Insert after <index>\n");
    printf("delete_after - Delete after <index>\n");
    printf("delete_last_k - Delete last k elements\n");
    printf("length - Print list length\n");
    printf("exit - Exit\n");
}

int handle_input(char* command, List* list) {
    size_t index;
    char value[50];
    size_t k;
    Node* current;
    if (strcmp(command, "print") == 0) {
        list_print(list);
    } else if (strcmp(command, "insert_end") == 0) {
        printf("Enter value: ");
        scanf("%49s", value);
        list_insert_to_end(value, list);
    } else if (strcmp(command, "delete_end") == 0) {
        list_delete_end(list);
    } else if (strcmp(command, "insert_begin") == 0) {
        printf("Enter value: ");
        scanf("%49s", value);
        list_insert_to_begin(value, list);
    } else if (strcmp(command, "delete_begin") == 0) {
        list_delete_begin(list);
    } else if (strcmp(command, "insert_after") == 0) {
        printf("Enter index and value: ");
        scanf("%zu %49s", &index, value);
        current = list->head;
        for (size_t i = 0; i < index && current != NULL; i++) current = current->next;
        if (current) {
            list_insert_after(current, value);
        } else {
            printf("Index out of range\n");
        }
    } else if (strcmp(command, "delete_after") == 0) {
        printf("Enter index: ");
        scanf("%zu", &index);
        current = list->head;
        for (size_t i = 0; i < index && current != NULL; i++) current = current->next;
        if (current) {
            list_delete_after(current);
        } else {
            printf("Index out of range\n");
        }
    } else if (strcmp(command, "delete_last_k") == 0) {
        printf("Enter k: ");
        scanf("%zu", &k);
        list_delete_last_k(list, k);
    } else if (strcmp(command, "length") == 0) {
        printf("List length: %zu\n", list_length(list));
    } else if (strcmp(command, "exit") == 0) {
        list_destroy(list); exit(0);
    } else {
        printf("\n");
    }
    return 0;
} 


int input_option(char* command) {
    if (fgets(command, 50, stdin) == NULL) {
        return EOF;
    }
    command[strcspn(command, "\n")] = '\0'; 
    return 1;
}

int main() {
    List* list = list_create();
    char command[50];
    print_commands();
    while (1) {
        printf("Enter command: ");
        if (input_option(command) == EOF) {
            break;
        }
        handle_input(command, list);
    }
    list_destroy(list);
    return 0;
}