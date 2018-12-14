#include <stdio.h>
#include <stddef.h>         /* Used for size_t definition */
#include <stdbool.h>        /* Used for boolean true and false values */
#include <stdlib.h>         /* For exit() and dynamic memory management */


#define NULL_POINTER_ERROR 1            // program termination status
#define INDEX_OUT_OF_BOUNDS_ERROR 2     // program termination status
#define NO_SUCH_ELEMENT_ERROR 3         // program termination status
#define ILLEGAL_STATE_ERROR 4           // program termination status


/* Used to print the linked list elements of type element_t */
#define FORMAT_SPECIFIER "%d"

/* The type of data that can be stored in a linked list */
typedef int element_t;


/* The user should not need to deal directly with nodes */
typedef struct node Node;

struct node
{
    element_t data;
    Node *next;         // pointer to the next node in the linked list
};


/* The user should use this LinkedList definition */
typedef struct linkedlist LinkedList;

struct linkedlist
{
    Node *head;         // pointer to the first node in the linked list
    size_t size;        // number of elements in the linked list
};


/* Used to iterate through the list linearly */
typedef struct listiterator ListIterator;

struct listiterator
{
    LinkedList *list;
    Node *previous;
    Node *current;
    Node *next;
};


/* Function prototypes (linkedlist.c) */
void linkedlist_init(LinkedList *list);
void linkedlist_free(LinkedList *list);
bool linkedlist_add(LinkedList *list, element_t element);
bool linkedlist_add_at(LinkedList *list, size_t index, element_t element);
bool linkedlist_remove(LinkedList *list, element_t element);
element_t linkedlist_remove_at(LinkedList *list, size_t index);
element_t linkedlist_get(LinkedList *list, size_t index);
element_t linkedlist_set(LinkedList *list, size_t index, element_t element);
bool linkedlist_contains(LinkedList *list, element_t element);
void linkedlist_clear(LinkedList *list);
bool linkedlist_is_empty(LinkedList *list);
size_t linkedlist_size(LinkedList *list);
void linkedlist_print(LinkedList *list);
void linkedlist_check_null(LinkedList *list, char *functionName);
void linkedlist_check_index_bounds(LinkedList *list,
        size_t index, char *functionName);

/* Function prototypes (listiterator.c) */
void listiterator_init(ListIterator *iterator, LinkedList *list);
bool listiterator_has_next(ListIterator *iterator);
element_t listiterator_next(ListIterator *iterator);
void listiterator_remove(ListIterator *iterator);
void listiterator_check_null(ListIterator *iterator, char *functionName);
void listiterator_check_has_next(ListIterator *iterator, char *functionName);
void listiterator_check_state(ListIterator *iterator, char *functionName);
