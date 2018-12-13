/*
    Implementation of a singly linked list.
    
    Structure members of the LinkedList struct should not be accessed
    directly by the user. All linked list operations should be done by
    calling one of the functions.
    
    All these functions terminate the program upon receiving a NULL pointer
    where a pointer to a LinkedList is expected.
    
    The functions with an index parameter will terminate the program upon
    receiving an invalid index.
    
    If the program is terminated unexpectedly by a call to these functions,
    an error message is printed to the standard error stream, detailing
    what kind of error occurred, and in which function.
    
    
    Example usage:
    
    LinkedList list;
    linkedlist_init(&list);     // initialize the list
    ...                         // some linked list operations
    linkedlist_free(&list):     // free the list's memory
*/


#include "linkedlist.h"


/* Function prototypes for private functions */
static void linkedlist_check_null(LinkedList *list, char *functionName);
static void linkedlist_check_index_bounds(LinkedList *list,
        size_t index, char *functionName);


/*
 * Initialize the linked list.
 *
 * params:
 * list: the list to be initialized
 *
 * returns: N/A
 */
void linkedlist_init(LinkedList *list)
{
    linkedlist_check_null(list, "linkedlist_init");
    
    list->head = NULL;
    list->size = 0;
}


/*
 * Free the memory of a list.
 *
 * params:
 * list: the list to be freed
 *
 * returns: N/A
 */
void linkedlist_free(LinkedList *list)
{
    linkedlist_check_null(list, "linkedlist_free");
    
    Node *previous = NULL;
    Node *current = list->head;
    
    while (current != NULL)
    {
        previous = current;
        current = current->next;
        
        free(previous);
    }
    
    list->head = NULL;
    list->size = 0;
}


/*
 * Add an element to the end of the list.
 *
 * params:
 * list: the list to append to
 * element: the element to add to the list
 *
 * returns:
 * true if the element was added to the list
 */
bool linkedlist_add(LinkedList *list, element_t element)
{
    linkedlist_check_null(list, "linkedlist_add");
    
    bool added = false;
    
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    if (newNode != NULL)
    {
        newNode->data = element;
        newNode->next = NULL;
        
        // if the list is empty
        if (list->head == NULL)
        {
            list->head = newNode;
        }
        else
        {
            Node *current = list->head;
            
            // traverse until the end of the list
            while (current->next != NULL)
            {
                current = current->next;
            }
            
            // current is now the last node in the list
            // add the new node at the end of the list
            current->next = newNode;
        }
        
        list->size++;
        added = true;
    }
    
    return added;
}


/*
 * Add an element to the list at a specified index.
 *
 * params:
 * list: the list to add to
 * index: the index in the list at which to add an element
 * element: the element to add to the list
 *
 * returns:
 * true if the element was added to the list
 */
bool linkedlist_add_at(LinkedList *list, size_t index, element_t element)
{
    /* Normally an index equal to the size of the list is invalid, but not
       for this function, so return early otherwise the upcoming check for
       out of bounds will trigger an error that will terminate the program */
    if (index == list->size)
    {
        return linkedlist_add(list, element);
    }
    
    linkedlist_check_null(list, "linkedlist_add_at");
    linkedlist_check_index_bounds(list, index, "linkedlist_add_at");
    
    bool added = false;
    
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    if (newNode != NULL)
    {
        newNode->data = element;
        
        // add at the beginning of the list
        if (index == 0)
        {
            newNode->next = list->head;     // list[1] = list[0];
            list->head = newNode;           // list[0] = newNode;
        }
        else
        {
            Node *current = list->head;
            
            size_t i;
            for (i = 1; i < index; i++)
            {
                current = current->next;
            }
            
            // current now points to the node at index - 1
            newNode->next = current->next;  // list[index + 1] = list[index];
            current->next = newNode;        // list[index] = newNode;
        }
        
        list->size++;
        added = true;
    }
    
    return added;
}


/*
 * Removes the first occurrence of the specified element from the list,
 * if it exists.
 *
 * params:
 * list: the list to remove from
 * element: the element to remove from the list
 *
 * returns:
 * true if the specified element was contained in the list
 */
bool linkedlist_remove(LinkedList *list, element_t element)
{
    linkedlist_check_null(list, "linkedlist_remove");
    
    bool found = false;
    
    // if the list is not empty
    if (list->head != NULL)
    {
        Node *removedNode;       // the node to remove
        
        // if the element is found in the first node of the list
        if (list->head->data == element)
        {
            removedNode = list->head;
            list->head = removedNode->next;
            found = true;
        }
        else
        {
            Node *current = list->head;
            
            while (current->next != NULL && !found)
            {
                // if the element is found in the node after the current
                if (current->next->data == element)
                {
                    removedNode = current->next;
                    current->next = removedNode->next;
                    found = true;       // exit the loop
                }
                else
                {
                    current = current->next;
                }
            }
        }
        
        if (found)
        {
            free(removedNode);
            list->size--;
        }
    }
    
    return found;
}


/*
 * Removes the element at the specified index in the list.
 *
 * params:
 * list: the list to remove an element from
 * index: the index of the element to remove from the list
 *
 * returns:
 * the element that was removed from the list
 */
element_t linkedlist_remove_at(LinkedList *list, size_t index)
{
    linkedlist_check_null(list, "linkedlist_remove_at");
    linkedlist_check_index_bounds(list, index, "linkedlist_remove_at");
    
    element_t removedElement;
    Node *removedNode;
    
    // remove the first node of the list
    if (index == 0)
    {
        removedNode = list->head;
        list->head = removedNode->next;
    }
    else
    {
        Node *current = list->head;
        
        size_t i;
        for (i = 1; i < index; i++)
        {
            current = current->next;
        }
        
        // current now points to the node before the one to be removed
        removedNode = current->next;
        current->next = removedNode->next;
    }
    
    removedElement = removedNode->data;
    
    free(removedNode);
    list->size--;
    
    return removedElement;
}


/*
 * Get the element at the specified index of the list.
 *
 * params:
 * list: the list to get an element from
 * index: the index of the element in the list to get
 *
 * returns:
 * the element at the specified index of the list
 */
element_t linkedlist_get(LinkedList *list, size_t index)
{
    linkedlist_check_null(list, "linkedlist_get");
    linkedlist_check_index_bounds(list, index, "linkedlist_get");

    Node *current = list->head;
    
    size_t i;
    for (i = 0; i < index; i++)
    {
        current = current->next;
    }
    
    return current->data;
}


/*
 * Replace an element at the specified position of the list with
 * the specified element.
 *
 * params:
 * list: the list to replace an element in
 * index: the index of the element to replace
 * element: the new element
 *
 * returns:
 * the element that got replaced
 */
element_t linkedlist_set(LinkedList *list, size_t index, element_t element)
{
    linkedlist_check_null(list, "linkedlist_set");
    linkedlist_check_index_bounds(list, index, "linkedlist_set");
    
    element_t oldElement;
    Node *current = list->head;
    
    size_t i;
    for (i = 0; i < index; i++)
    {
        current = current->next;
    }
    
    oldElement = current->data;     // get the previous element at index
    current->data = element;        // replace with the new element
    
    return oldElement;
}


/*
 * Determine if a specified element exists in the list
 *
 * params:
 * list: the list to search an element for
 * element: the element to search for in the list
 *
 * returns:
 * true if the element is found in the list
 */
bool linkedlist_contains(LinkedList *list, element_t element)
{
    bool found = false;
    
    Node *current = list->head;
    
    while (current != NULL && !found)
    {
        if (current->data == element)
        {
            found = true;
        }
        else
        {
            current = current->next;
        }
    }
    
    return found;
}


/*
 * Remove all the elements of the list.
 *
 * params:
 * list: the list to empty
 *
 * returns: N/A
 */
void linkedlist_clear(LinkedList *list)
{
    linkedlist_free(list);
}


/*
 * Determine if the list is empty.
 *
 * params:
 * list: the list to check if it is empty
 *
 * returns:
 * true if the list is empty
 */
bool linkedlist_is_empty(LinkedList *list)
{
    linkedlist_check_null(list, "linkedlist_size");
    
    return list->size == 0;
}


/*
 * Get the size of the list.
 *
 * params:
 * list: the list to get the size of
 *
 * returns:
 * the number of elements in the list
 */
size_t linkedlist_size(LinkedList *list)
{
    linkedlist_check_null(list, "linkedlist_size");
    
    return list->size;
}


/*
 * Print all the elements in the linked list.
 *
 * params:
 * list: the list to print
 *
 * returns: N/A
 */
void linkedlist_print(LinkedList *list)
{
    linkedlist_check_null(list, "linkedlist_print");
    
    Node *current = list->head;
    
    printf("[");
    while (current != NULL)
    {
        if (current == list->head)
        {
            printf(FORMAT_SPECIFIER, current->data);
        }
        else
        {
            printf(", " FORMAT_SPECIFIER, current->data);
        }
        
        current = current->next;
    }
    printf("]\n");
}


/*
 * Check if a list pointer is NULL.
 * If so, display an error message and terminate the program.
 *
 * params:
 * list: the list to check if it is NULL
 * functionName: the name of the function calling this one
 *
 * returns: N/A
 */
static void linkedlist_check_null(LinkedList *list, char *functionName)
{
    if (list == NULL)
    {
        fprintf(stderr, "%s: NULL pointer: list pointer must not be NULL\n",
                functionName);
        linkedlist_free(list);
        exit(NULL_POINTER_ERROR);
    }
}


/*
 * Check if a function was called with an invalid index.
 * If so, display an error message and terminate the program.
 *
 * A valid index range is 0 (inclusive) to the size of the list (exclusive).
 *
 * params:
 * list: the list to check if the index is out of bounds for
 * index: the index to check if it is out of bounds
 * functionName: the name of the function calling this one
 *
 * returns: N/A
 */
static void linkedlist_check_index_bounds(LinkedList *list,
        size_t index, char *functionName)
{
    if (index >= list->size)
    {
        fprintf(stderr, "%s: index out of bounds: index=%u, size=%u\n",
                functionName, index, list->size);
        linkedlist_free(list);
        exit(INDEX_OUT_OF_BOUNDS_ERROR);
    }
}
