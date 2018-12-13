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
