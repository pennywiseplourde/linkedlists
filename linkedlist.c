#include <LNK/linkedlist.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void lnkInit(lnkList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

void lnkPushback(lnkList* list, listType type, listValue data) {
    link* newLink = (link*)malloc(sizeof(link));
    newLink->type = type;
    newLink->data = data;
    newLink->next = NULL;
    newLink->prev = list->tail;

    if (list->tail) {
        list->tail->next = newLink;
    } else {
        list->head = newLink;
    }
    list->tail = newLink;
    list->length++;
}

void lnkPushfront(lnkList* list, listType type, listValue data) {
    link* newLink = (link*)malloc(sizeof(link));
    newLink->type = type;
    newLink->data = data;
    newLink->next = list->head;
    newLink->prev = NULL;

    if (list->head) {
        list->head->prev = newLink;
    } else {
        list->tail = newLink;
    }
    list->head = newLink;
    list->length++;
}

link* lnkGet(lnkList* list, int index) {
    if (index < 0 || index >= list->length) {
        return NULL; // Out of bounds
    }
    link* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

link* lnkSearch(lnkList* list, void* search) {
    link* current = list->head;
    while (current) {
        if (memcmp(&current->data, search, sizeof(listValue)) == 0) {
            return current; // Found a match
        }
        current = current->next;
    }
    return NULL; // No match found
}

void lnkPrintList(lnkList* list) {
    link* current = list->head;
    while (current) {
        switch (current->type) {
            case INT:
                printf("INT: %d\n", current->data.i);
                break;
            case FLOAT:
                printf("FLOAT: %f\n", current->data.f);
                break;
            case STRING:
                printf("STRING: %s\n", current->data.str);
                break;
            case POINTER:
                printf("POINTER: %p\n", current->data.v);
                break;
        }
        current = current->next;
    }
}

void lnkFree(lnkList* list, int freeData, int freeList) {
    link* current = list->head;
    while (current) {
        link* next = current->next;
        if (freeData) {
            if (current->type == STRING) {
                free(current->data.str); // Free string data if type is STRING
            } else if (current->type == POINTER) {
                free(current->data.v); // Free pointer data if type is POINTER
            } // For INT and FLOAT, no need to free as they are stored directly in the union
        }
        free(current); // Free the link itself
        current = next;

        if (freeList) {
            free(list); // Free the list structure itself
        }
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}