#include <stdio.h>
#include "arraylist.h"


void printList(ArrayList *list);
void printExpected(char *listString, unsigned int size, unsigned int capacity);


/*
    Tested with:
    
    #define DEFAULT_INITIAL_CAPACITY 5
    #define MAX_CAPACITY 10
    #define CAPACITY_MULTIPLIER 2
    #define ERROR_VALUE -1
*/

int main()
{
    ArrayList list;
    
    if (!ArrayList_init(&list, 1))
    {
        return 0;
    }
    
    printf("Expected: 1, Actual: %d\n", ArrayList_add(&list, 5));
    printf("Expected: 1, Actual: %d\n", ArrayList_add(&list, 7));
    printf("Expected: 1, Actual: %d\n", ArrayList_add(&list, 10));
    
    printf("Expected: 1, Actual: %d\n", ArrayList_add_at(&list, 0, 20));
    printf("Expected: 1, Actual: %d\n", ArrayList_add_at(&list, 4, 14));
    printf("Expected: 0, Actual: %d\n", ArrayList_add_at(&list, 6, 20));

    printf("Expected: 5, Actual: %d\n", ArrayList_get(&list, 1));
    printf("Expected: %d, Actual: %d\n", ERROR_VALUE, ArrayList_get(&list, 9));
    
    printf("Expected: 1, Actual: %d\n", ArrayList_ensure_capacity(&list, 7));
    printf("Expected: 1, Actual: %d\n", ArrayList_ensure_capacity(&list, 3));
    
    ArrayList list2;
    ArrayList_init(&list2, 0);
    ArrayList_add(&list2, 1);
    ArrayList_add(&list2, 2);
    ArrayList_add(&list2, 3);
    ArrayList_add(&list2, 4);
    ArrayList_add(&list2, 5);
    ArrayList_add(&list2, 6);
    
    printf("Expected: 0, Actual: %d\n", ArrayList_add_all(&list, &list2));
    printf("Expected: 1, Actual: %d\n", ArrayList_add_all(&list, &list));
    
    printf("Expected: 2, Actual: %d\n", ArrayList_index_of(&list, 7));
    printf("Expected: -1, Actual: %d\n", ArrayList_index_of(&list, 29999));
    printf("Expected: 7, Actual: %d\n", ArrayList_last_index_of(&list, 7));
    printf("Expected: -1, Actual: %d\n", ArrayList_last_index_of(&list, 29999));
    printf("Expected: 1, Actual: %d\n", ArrayList_contains(&list, 10));
    printf("Expected: 0, Actual: %d\n", ArrayList_contains(&list, 29999));
    
    printf("Expected: 14, Actual: %d\n", ArrayList_set(&list, 9, 78));
    printf("Expected: -1, Actual: %d\n", ArrayList_set(&list, 20, 78));
    
    printf("Expected: -1, Actual: %d\n", ArrayList_remove_index(&list, 34));
    printf("Expected: 5, Actual: %d\n", ArrayList_remove_index(&list, 1));
    printf("Expected: 0, Actual: %d\n", ArrayList_remove(&list, 1));
    printf("Expected: 1, Actual: %d\n", ArrayList_remove(&list, 5));
    
    ArrayList list3;
    ArrayList_init(&list3, 0);
    
    ArrayList_add(&list3, 40);
    
    printf("Expected: 0, Actual: %d\n", ArrayList_remove_all(&list, &list3));
    ArrayList_add(&list3, 20);
    printf("Expected: 1, Actual: %d\n", ArrayList_remove_all(&list, &list3));
    
    ArrayList_remove_range(&list, 0, 3);
    ArrayList_remove_range(&list, 1, 1);        // shouldn't do anything
    
    ArrayList_add(&list3, 7);
    ArrayList_add(&list3, 10);
    ArrayList_add(&list3, 78);
    printf("Expected: 0, Actual: %d\n", ArrayList_retain_all(&list, &list3));
    
    ArrayList_clear(&list3);
    ArrayList_add(&list3, 78);
    printf("Expected: 1, Actual: %d\n", ArrayList_retain_all(&list, &list3));
    
    printf("Expected: 1, Actual: %d\n", ArrayList_trim_to_size(&list));
    
    printList(&list);
    printExpected("78", 1, 1);
    
    printf("Expected: 0, Actual: %d\n", ArrayList_is_empty(&list));
    ArrayList_clear(&list);
    printf("Expected: 1, Actual: %d\n", ArrayList_is_empty(&list));
    
    ArrayList_free(&list);
    ArrayList_free(&list2);
}


void printList(ArrayList *list)
{
    unsigned int size = ArrayList_size(list);
    unsigned int index = 0;
    
    printf("Values: ");
    for (index = 0; index < size; index++)
    {
        printf("%d ", ArrayList_get(list, index));
    }
    printf("\nSize: %u\nCapacity: %u\n", size, list->capacity);
}


void printExpected(char *listString, unsigned int size, unsigned int capacity)
{
    printf("Expected values: %s\nExpected size: %u\nExpected capacity: %u\n",
            listString, size, capacity);
}
