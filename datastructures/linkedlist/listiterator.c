/*
    Iterator to iterate through a linked list in linear time, that is,
    calling next() is guaranteed to provide the next element in the list
    in constant time.
    
    Any LinkedList or ListIterator parameters should not be NULL, otherwise
    the program will terminate prematurely.
    
    
    Example usage:
    
    ListIterator iterator;
    listiterator_init(&iterator, &list);   // list is a previously declared list
    while (listiterator_has_next(&iterator))
    {
        element_t element = listiterator_next(&iterator);
    }
*/


#include "linkedlist.h"


/*
 * Initialize a ListIterator.
 *
 * params:
 * iterator: the iterator to initialize
 * list: the list that this iterator will iterate through
 *
 * returns: N/A
 */
void listiterator_init(ListIterator *iterator, LinkedList *list)
{
    listiterator_check_null(iterator, "listiterator_init");
    linkedlist_check_null(list, "listiterator_init");
    
    iterator->list = list;
    iterator->previous = NULL;
    iterator->current = NULL;
    iterator->next = list->head;
}


/*
 * Determine if the list iterator has a next element.
 *
 * params:
 * iterator: the iterator to test if it has a next element.
 *
 * returns:
 * true if the iterator has a next element.
 */
bool listiterator_has_next(ListIterator *iterator)
{
    listiterator_check_null(iterator, "listiterator_has_next");
    
    return iterator->next != NULL;
}


/*
 * Get the next element.
 *
 * Before calling this method, use listiterator_has_next() to make sure
 * there is a next element, otherwise a fatal error will occur if this
 * function is called and there is no next element.
 *
 * params:
 * iterator: the iterator to get the next element of
 *
 * returns:
 * the next element
 */
element_t listiterator_next(ListIterator *iterator)
{
    listiterator_check_has_next(iterator, "listiterator_next");
    
    // if current is NULL, it was removed or listiterator_next()
    // hasn't been called yet since initialization of the iterator
    if (iterator->current != NULL)
    {
        iterator->previous = iterator->current;
    }
    
    iterator->current = iterator->next;
    iterator->next = iterator->next->next;
    
    return iterator->current->data;
}


/*
 * Remove the element that was last returned by a call to listiterator_next().
 *
 * This call can only be made once after a call to next().
 *
 * params:
 * iterator: the iterator to remove the last returned element from
 *
 * returns: N/A
 */
void listiterator_remove(ListIterator *iterator)
{
    listiterator_check_null(iterator, "listiterator_remove");
    listiterator_check_state(iterator, "listiterator_remove");
    
    Node *remove = iterator->current;
    
    if (iterator->previous == NULL)
    {
        iterator->list->head = remove->next;    // new first node of the list
    }
    else
    {
        iterator->previous->next = remove->next;
    }
    
    free(remove);
    iterator->current = NULL;
    iterator->list->size--;
}


/*
 * Check if a list iterator is NULL.
 * If so, display an error message and terminate the program.
 *
 * params:
 * iterator: the iterator to check if it is NULL
 * functionName: the name of the function calling this one
 *
 * returns: N/A
 */
void listiterator_check_null(ListIterator *iterator, char *functionName)
{
    if (iterator == NULL)
    {
        fprintf(stderr, "%s: NULL pointer: iterator pointer must not be NULL\n",
                functionName);
        exit(NULL_POINTER_ERROR);
    }
}


/*
 * Check if the list iterator has a next element.
 * If it does not, display an error message and terminate the program.
 *
 * params:
 * iterator: the iterator to check if it has a next element
 * functionName: the name of the function calling this one
 *
 * returns: N/A
 */
void listiterator_check_has_next(ListIterator *iterator, char *functionName)
{
    if (!listiterator_has_next(iterator))
    {
        fprintf(stderr, "%s: no such element: use listiterator_has_next()\n",
                functionName);
        exit(NO_SUCH_ELEMENT_ERROR);
    }
}


/*
 * Check if listiterator_next() has not been called, or if
 * listiterator_remove() has already been called.
 * If either is true, display an error message and terminate the program.
 *
 * params:
 * iterator: the iterator to check the state of
 * functionName: the name of the function calling this one
 *
 * returns: N/A
 */
void listiterator_check_state(ListIterator *iterator, char *functionName)
{
    if (iterator->current == NULL)
    {
        fprintf(stderr, "%s: illegal state: must call next()\n", functionName);
        exit(ILLEGAL_STATE_ERROR);
    }
}
