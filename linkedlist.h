#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef enum {
    INT,
    FLOAT,
    STRING,
    POINTER
} listType; // Type of data stored in a link. Used to determine which member of the union to use. 

typedef union {
    int i;
    float f;
    char* str;
    void* v;
} listValue; // A union which can hold any of the types of data that a link can store.

typedef struct link {
    struct link* next; // Pointer to next link
    struct link* prev; // Pointer to previous link
    listType type; // Type of data stored in this link. Used to determine which member of the union to use.
    listValue data; // Data of the link. Can be an int, float, string, or pointer. Use the appropriate one.
} link; // Constituent element of a linked list

typedef struct {
    link* head; // First link in the list.
    link* tail; // Last link in the list.
    int length; // Number of links in the list.
} lnkList; // A list which only takes as much space as it needs. Must be initilaized.

void lnkInit(lnkList* link); // Initialize a linked list.

void lnkPushback(lnkList* list, listType type, listValue data); // Add a new link to the end of the list. Takes the type and data of the link as arguments.

void lnkPushfront(lnkList* list, listType type, listValue data); // Add a new link to the front of the list. Takes the type and data of the link as arguments.

link* lnkGet(lnkList* list, int index); // Get the pointer to a specific link by index

link* lnkSearch(lnkList* list, void* search); // Search for a link by its data. Returns a pointer to the first link with matching data. Uses memcmp, so it can be used for any type of data.

void lnkPrintList(lnkList* list); // Print the contents of the list. For debugging purposes.

void lnkFree(lnkList* list, int freeData, int freeList); // Free the memory used by a linked list. If freeData is nonzero, also free the data of each link. If freeList is nonzero, also free the list itself. Use with caution, as this can cause double frees if the data is shared between links or other parts of the program.

#endif