/*
 * This array list data structure is made to resemble the functionality
 * of the Java ArrayList.
 *
 * The user will declare a new ArrayList and initialize it by passing the
 * ArrayList to ArrayList_init(). Once the ArrayList is no longer needed,
 * it should be passed to ArrayList_free() to free its memory.
 *
 * The user should make sure that an ArrayList that has already been initialized
 * is not passed to ArrayList_init() again, otherwise the original ArrayList
 * memory will be lost, without having been freed.
 *
 * Once an ArrayList has been freed, either it should be reinitialized
 * with ArrayList_init(), or it should never be used again.
 *
 * ArrayList_free() should not be called on an ArrayList that was not
 * successfully initialized with ArrayList_init();
 *
 * The user should make sure that any ArrayList pointer passed to any of these
 * functions is not NULL, to avoid fatal run-time errors due to attempting to
 * dereference a NULL pointer.
 *
 * ArrayLists should be modified only by calling one of these methods;
 * its structure members should not be accessed directly by the user.
 *
 *
 * Example usage:
 *
 * ArrayList list;                  // declare an ArrayList
 * element_t value = 20;
 * ArrayList_init(&list, 0);        // initialize the ArrayList
 * ArrayList_add(&list, value);     // add a value to the ArrayList
 * ArrayList_free(&list);           // finished with the ArrayList
 */





#include "arraylist.h"


/*
 * Initialize an ArrayList.
 *
 * Use 0 for the initial capacity to set the capacity to a default value.
 *
 * Returns false if memory for the list with the specified initial
 * capacity could not be allocated.
 *
 * params:
 * list: the list to be initialized
 * initialCapacity: initial capacity of the list
 *
 * returns:
 * true if the list was initialized successfully, false otherwise
 */
bool ArrayList_init(ArrayList *list, unsigned int initialCapacity)
{
    bool initialized = false;

    if (initialCapacity <= MAX_CAPACITY)
    {
        if (initialCapacity == 0)
        {
            initialCapacity = DEFAULT_INITIAL_CAPACITY;
        }
        
        list->data = (element_t *)malloc(initialCapacity * sizeof(element_t));
        
        if (list->data != NULL)
        {
            list->size = 0;
            list->capacity = initialCapacity;
            
            initialized = true;
        }
    }
        
    return initialized;
}


/*
 * Free the memory of an ArrayList.
 *
 * The array is set to point to NULL.
 * List size and capacity are set to 0.
 *
 * params:
 * list: the list to be freed
 */
void ArrayList_free(ArrayList *list)
{
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}


/*
 * Add the specified element to the end of the list.
 *
 * If the list is full and extra memory cannot be allocated to it,
 * the element will not be added to the list.
 *
 * params:
 * list: the list to append to
 * element: the element to add to the list
 *
 * returns:
 * true if the element was added to the list, false otherwise
 */
bool ArrayList_add(ArrayList *list, element_t element)
{
    bool added = false;
    
    // if the list is full, increase the capacity
    if (list->size == list->capacity)
    {
        if (list->capacity * CAPACITY_MULTIPLIER <= MAX_CAPACITY)
        {
            ArrayList_ensure_capacity(list,
                    list->capacity * CAPACITY_MULTIPLIER);
        }
        else
        {
            ArrayList_ensure_capacity(list, MAX_CAPACITY);
        }
    }
    
    // make sure the list is not full
    if (list->size < list->capacity)
    {
        list->data[list->size] = element;
        list->size++;
        
        added = true;
    }
    
    return added;
}


/*
 * Add the specified element to the list at the specified index.
 * Shifts the current element at the index and any subsequent elements
 * one index to the right.
 *
 * If the index is out of bounds, the element will not be added to the list.
 *
 * If the list is full and extra memory cannot be allocated to it,
 * the element will not be added to the list.
 *
 * params:
 * list: the list to add an element to
 * index: the index of the list at which the element will be added
 * element: the element to add to the list
 */
bool ArrayList_add_at(ArrayList *list, unsigned int index, element_t element)
{
    bool added = false;
    
    if (index == list->size)
    {
        added = ArrayList_add(list, element);
    }
    // check for out of bounds
    else if (index < list->size)
    {
        // if the list is full, increase the capacity
        if (list->size == list->capacity)
        {
            if (list->capacity * CAPACITY_MULTIPLIER <= MAX_CAPACITY)
            {
                ArrayList_ensure_capacity(list,
                        list->capacity * CAPACITY_MULTIPLIER);
            }
            else
            {
                ArrayList_ensure_capacity(list, MAX_CAPACITY);
            }
        }
        
        // make sure the list is not full
        if (list->size < list->capacity)
        {
            // shift all elements to the right starting from index
            memmove(&list->data[index + 1],
                    &list->data[index],
                    (list->size - index) * sizeof(element_t));
            
            list->data[index] = element;
            list->size++;
            
            added = true;
        }
    }
    
    return added;
}


/*
 * Add all the elements from a source list to a destination list.
 * The items are appended in the same order, starting at the end
 * of the destination list.
 *
 * If the destination list cannot be expanded to fit all of the elements from
 * the source list, then none are appended, and false is returned.
 *
 * params:
 * dest: the destination list
 * src: the source list
 *
 * returns:
 * true if the elements from src were appended to dest, false otherwise
 */
bool ArrayList_add_all(ArrayList *dest, ArrayList *src)
{
    bool added = false;
    bool hasMinCapacity =
            ArrayList_ensure_capacity(dest, dest->size + src->size);
    
    if (hasMinCapacity)
    {
        memcpy(&dest->data[dest->size],
                &src->data[0],
                src->size * sizeof(element_t));
        
        dest->size += src->size;
        
        added = true;
    }
    
    return added;
}


/*
 * Removes all elements from a list.
 *
 * params:
 * list: the list to clear
 */
void ArrayList_clear(ArrayList *list)
{
    list->size = 0;
}


/*
 * Determine if the list contains the specified element.
 *
 * params:
 * list: the list to search
 * element: the element to search for
 *
 * returns:
 * true if the element is in the list, false if not
 */
bool ArrayList_contains(ArrayList *list, element_t element)
{
    return ArrayList_index_of(list, element) != -1;
}


/*
 * Increase the capacity of a list so that it can hold at least
 * the number of elements specified.
 *
 * If the specified minimum capacity is less than or equal to the current
 * capacity of the list, the capacity remains unchanged.
 *
 * If memory cannot be allocated to reach minCapacity, the capacity
 * remains unchanged, and false is returned.
 *
 * params:
 * list: the list to increase the capacity of
 * minCapacity: the minimum capacity of the list
 *
 * returns:
 * true if the capacity of the list is at least minCapacity, false otherwise
 */
bool ArrayList_ensure_capacity(ArrayList *list, unsigned int minCapacity)
{
    bool hasMinCapacity = false;
    element_t *newData = NULL;
    
    if (minCapacity <= MAX_CAPACITY)
    {
        // if not enough capacity
        if (minCapacity > list->capacity)
        {
            newData = (element_t *)malloc(minCapacity * sizeof(element_t));
            
            if (newData != NULL)
            {
                // copy the old array values into the new memory
                memcpy(newData, list->data, list->size * sizeof(element_t));
                
                free(list->data);
                
                list->data = newData;
                list->capacity = minCapacity;
                
                hasMinCapacity = true;
            }
        }
        else    // already has enough capacity
        {
            hasMinCapacity = true;
        }
    }
    
    return hasMinCapacity;
}


/*
 * Get the element at the specified index from a list.
 *
 * The caller should make sure that the index is >= 0 and less than the size of
 * the list, which can be found using ArrayList_size(), otherwise ERROR_VALUE
 * is returned, which may be confused with a valid element in the list.
 *
 * params:
 * list: the list to get an element from
 * index: the index of the element in the list
 *
 * returns:
 * ERROR_VALUE if the index is not valid,
 * otherwise returns the element at the index
 */
element_t ArrayList_get(ArrayList *list, unsigned int index)
{
    if (index >= list->size)
    {
        return ERROR_VALUE;
    }
    else
    {
        return list->data[index];
    }
}


/*
 * Returns the index of the first occurrence of the specified element in the
 * list, or -1 if the element is not in the list.
 *
 * params:
 * list: the list to search in
 * element: the element to search for
 *
 * returns:
 * the index of the first occurrence of the specified element,
 * -1 if the element is not found in the list
 */
int ArrayList_index_of(ArrayList *list, element_t element)
{
    bool found = false;
    unsigned int index = 0;
    unsigned int size = list->size;
    
    for (index = 0; index < size; index++)
    {
        if (list->data[index] == element)
        {
            found = true;
            break;
        }
    }
    
    return found ? index : -1;
}


/*
 * Determine whether the list is empty.
 *
 * params:
 * list: the list to test if it is empty
 *
 * returns:
 * true if the list is empty, false if not
 */
bool ArrayList_is_empty(ArrayList *list)
{
    return list->size == 0;
}


/*
 * Removes an element at the specified index of the list and returns that value.
 *
 * params:
 * list: the list to remove an item from
 * index: the index of the element to remove
 *
 * returns:
 * the removed element, or ERROR_VALUE if the index was invalid
 */
element_t ArrayList_remove_index(ArrayList *list, unsigned int index)
{
    element_t removed = 0;
    
    if (index < list->size)
    {
        removed = list->data[index];
        
        // shift all elements down by 1 starting from index + 1
        memmove(&list->data[index],
                &list->data[index + 1],
                (list->size - index - 1) * sizeof(element_t));
        
        list->size--;
    }
    else
    {
        removed = ERROR_VALUE;
    }
    
    return removed;
}


/*
 * Removes the first occurrence of the specified element in the list.
 *
 * params:
 * list: the list to remove an element from
 * element: the element to remove
 *
 * returns:
 * true if the element was in the list, false otherwise
 */
bool ArrayList_remove(ArrayList *list, element_t element)
{
    int index = ArrayList_index_of(list, element);
    
    if (index != -1)
    {
        ArrayList_remove_index(list, index);
    }
    
    return index != -1;
}


/*
 * Removes all the elements from list that are contained in list2.
 *
 * params:
 * list: the list to reduce
 * list2: the list containing elements to remove from list
 *
 * returns:
 * true if the first list changed as a result of this function call
 */
bool ArrayList_remove_all(ArrayList *list, ArrayList *list2)
{
    bool changed = false;
    unsigned int i = 0;
    int index = 0;
    
    for (i = 0; i < list2->size; i++)
    {
        index = ArrayList_index_of(list, list2->data[i]);
        
        while (index != -1)
        {
            ArrayList_remove_index(list, index);
            
            index = ArrayList_index_of(list, list2->data[i]);
            
            changed = true;
        }
    }
    
    return changed;
}


/*
 * Removes a range of elements from the list, starting from fromIndex,
 * inclusive, up to toIndex, exclusive.
 *
 * params:
 * list: the list to remove from
 * fromIndex: starting index, inclusive
 * toIndex: ending index, exclusive
 */
void ArrayList_remove_range(ArrayList *list,
        unsigned int fromIndex, unsigned int toIndex)
{
    if (fromIndex < toIndex && toIndex < list->size)
    {
        memmove(&list->data[fromIndex],
                &list->data[toIndex],
                (list->size - toIndex) * sizeof(element_t));
        
        list->size -= (toIndex - fromIndex);
    }
}


/*
 * Removes from this list all elements that are not in list2.
 *
 * params:
 * list: the list to remove from
 * list2: the list of elements that should be in the first list
 *
 * returns:
 * true if this list changed as a result of this function call
 */
bool ArrayList_retain_all(ArrayList *list, ArrayList *list2)
{
    bool changed = false;
    int i = 0;
    
    for (i = 0; i < list->size; i++)
    {
        if (!ArrayList_contains(list2, list->data[i]))
        {
            ArrayList_remove_index(list, i);
            i--;
            
            changed = true;
        }
    }
    
    return changed;
}


/*
 * Returns the index of the last occurrence of the specified element in the
 * list, or -1 if the element is not in the list.
 *
 * params:
 * list: the list to search in
 * element: the element to search for
 *
 * returns:
 * the index of the last occurrence of the specified element,
 * -1 if the element is not found in the list
 */
int ArrayList_last_index_of(ArrayList *list, element_t element)
{
    bool found = false;
    int index = 0;
    
    for (index = list->size - 1; index >= 0; index--)
    {
        if (list->data[index] == element)
        {
            found = true;
            break;
        }
    }
    
    return found ? index : -1;
}


/*
 * Replace an element in the list at the specified location.
 *
 * Returns the element that was replaced.
 *
 * params:
 * list: the list to replace an element in
 * index: the index of the element to replace
 * element: the replacement element
 *
 * returns:
 * the replaced element, or ERROR_VALUE if the index was invalid
 */
element_t ArrayList_set(ArrayList *list, unsigned int index, element_t element)
{
    element_t previousElement = 0;
    
    if (index < list->size)
    {
        previousElement = list->data[index];
        list->data[index] = element;
    }
    else
    {
        previousElement = ERROR_VALUE;
    }
    
    return previousElement;
}


/*
 * Get the number of elements currently in the list.
 *
 * params:
 * list: the to get the size of
 *
 * returns:
 * the size of the list
 */
unsigned int ArrayList_size(ArrayList *list)
{
    return list->size;
}


/*
 * Trim the capacity of the list down to the list's size.
 * Useful in cases where storage space should be minimized.
 *
 * params:
 * list: the list to trims
 *
 * returns:
 * true if the list's capacity is the same as its size, false otherwise
 */
bool ArrayList_trim_to_size(ArrayList *list)
{
    unsigned int newCapacity = list->size;
    element_t *newData = NULL;
    
    // avoid capacity of 0, which would cause resizing
    // issues in ArrayList_ensure_capacity
    if (newCapacity == 0)
    {
        newCapacity = 1;
    }
    
    if (newCapacity != list->capacity)
    {
        newData = (element_t *)malloc(newCapacity * sizeof(element_t));
        
        if (newData != NULL)
        {
            // copy the old array values into the new memory
            memcpy(newData, list->data, list->size * sizeof(element_t));
            
            free(list->data);
            
            list->data = newData;
            list->capacity = newCapacity;
        }
    }
    
    return list->capacity == newCapacity;
}

