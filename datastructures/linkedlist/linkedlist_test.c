/*
    Test file for the singly linked list data structure.
    Lines that are commented indicate it results in an (expected) error. */

#include "linkedlist.h"


void printList(LinkedList *list);
void printExpected(char *s, size_t size);


int main()
{
    LinkedList list;
    linkedlist_init(&list);
    
    printf("Expected: 1, Actual: %d\n", linkedlist_is_empty(&list));
    
    //linkedlist_add_at(&list, 1, 100);
    printf("Expected: 1, Actual: %d\n", linkedlist_add_at(&list, 0, 100));
    
    linkedlist_clear(&list);
    printList(&list);
    
    printf("Expected: 1, Actual: %d\n", linkedlist_add_at(&list, 0, 100));
    
    printf("Expected: 1, Actual: %d\n", linkedlist_add(&list, 1));
    printf("Expected: 1, Actual: %d\n", linkedlist_add(&list, 2));
    printf("Expected: 1, Actual: %d\n", linkedlist_add(&list, 3));
    printf("Expected: 1, Actual: %d\n", linkedlist_add(&list, 4));
    printf("Expected: 1, Actual: %d\n", linkedlist_add(&list, 5));
    
    printf("Expected: 1, Actual: %d\n", linkedlist_add_at(&list, 0, -1));
    printf("Expected: 1, Actual: %d\n", linkedlist_add_at(&list, 1, -2));
    //linkedlist_add_at(&list, 9, 999);
    
    printf("Expected: 1, Actual: %d\n", linkedlist_add(&list, 2));
    
    printf("Expected: 0, Actual: %d\n", linkedlist_remove(&list, 0));
    printf("Expected: 1, Actual: %d\n", linkedlist_remove(&list, -1));
    printf("Expected: 1, Actual: %d\n", linkedlist_remove(&list, 2));
    printf("Expected: 1, Actual: %d\n", linkedlist_remove(&list, 2));
    
    //linkedlist_remove_at(&list, 6);
    printf("Expected: 5, Actual: %d\n", linkedlist_remove_at(&list, 5));
    printf("Expected: -2, Actual: %d\n", linkedlist_remove_at(&list, 0));
    
    linkedlist_add(&list, 10);
    
    printf("Expected: 0, Actual: %d\n", linkedlist_is_empty(&list));
    printf("Expected: 5, Actual: %d\n", linkedlist_size(&list));
    
    printf("Expected: 100, Actual: %d\n", linkedlist_get(&list, 0));
    printf("Expected: 3, Actual: %d\n", linkedlist_get(&list, 2));
    printf("Expected: 10, Actual: %d\n", linkedlist_get(&list, 4));
    
    printf("Expected: 100, Actual: %d\n", linkedlist_set(&list, 0, 1000));
    printf("Expected: 3, Actual: %d\n", linkedlist_set(&list, 2, 30));
    printf("Expected: 10, Actual: %d\n", linkedlist_set(&list, 4, 100));
    
    printf("Expected: 1, Actual: %d\n", linkedlist_contains(&list, 1));
    printf("Expected: 0, Actual: %d\n", linkedlist_contains(&list, 25));
    
    printList(&list);
    printExpected("1000 1 30 4 100", 5);
    
    
    
    
    
    ListIterator iterator;
    listiterator_init(&iterator, &list);
    
    while (listiterator_has_next(&iterator))
    {
        element_t element = listiterator_next(&iterator);
        printf(FORMAT_SPECIFIER "\n", element);
    }
    printf("\n");
    
    
    listiterator_init(&iterator, &list);
    
    while (listiterator_has_next(&iterator))
    {
        element_t element = listiterator_next(&iterator);
        printf(FORMAT_SPECIFIER "\n", element);
        
        if (element == 100)
        {
            listiterator_remove(&iterator);
            printf("removed\n");
            //listiterator_remove(&iterator);
        }
    }
    printf("\n");
    
    
    listiterator_init(&iterator, &list);
    
    listiterator_add(&iterator, -1);
    //listiterator_set(&iterator, 0);
    //listiterator_remove(&iterator);
    
    while (listiterator_has_next(&iterator))
    {
        element_t element = listiterator_next(&iterator);
        printf(FORMAT_SPECIFIER "\n", element);
        
        if (element == 1000)
        {
            listiterator_remove(&iterator);
            printList(&list);
            listiterator_add(&iterator, 99);
            listiterator_add(&iterator, 99);
            printList(&list);
            //listiterator_remove(&iterator);
            printList(&list);
        }
    }
    printf("\n");
    
    
    
    
    
    
    printList(&list);
    
    linkedlist_free(&list);
}


void printList(LinkedList *list)
{
    printf("Values: ");
    linkedlist_print(list);
    printf("Size: %u\n", list->size);
}


void printExpected(char *s, size_t size)
{
    printf("Expected values: %s\nExpected size: %u\n", s, size);
}
