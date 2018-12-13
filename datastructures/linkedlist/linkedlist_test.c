#include "linkedlist.h"


void printList(LinkedList *list);
void printExpected(char *s, size_t size);


int main()
{
    LinkedList list;
    linkedlist_init(&list);
    
    //linkedlist_add_at(&list, 1, 100);
    linkedlist_add_at(&list, 0, 100);
    
    linkedlist_add(&list, 1);
    linkedlist_add(&list, 2);
    linkedlist_add(&list, 3);
    linkedlist_add(&list, 4);
    linkedlist_add(&list, 5);
    
    linkedlist_add_at(&list, 0, -1);
    linkedlist_add_at(&list, 1, -2);
    //linkedlist_add_at(&list, 9, 999);
    
    linkedlist_add(&list, 20);
    
    printList(&list);
    printExpected("-1 -2 100 1 2 3 4 5 20", 9);
    
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
