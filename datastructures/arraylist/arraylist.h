#include <stdbool.h>        /* Boolean true and false values */
#include <stdlib.h>         /* Used for dynamic memory allocation */
#include <string.h>         /* Used to copy chunks of memory */


#define DEFAULT_INITIAL_CAPACITY 50
#define MAX_CAPACITY 50000000
#define CAPACITY_MULTIPLIER 2
#define ERROR_VALUE -1


/* The type of data elements that an ArrayList will store */
typedef int element_t;

typedef struct
{
    element_t *data;            // array of elements
    unsigned int size;          // number of elements in the array
    unsigned int capacity;      // total capacity of the array
}
ArrayList;


/* Function prototypes */
bool ArrayList_init(ArrayList *list, unsigned int initialCapacity);
void ArrayList_free(ArrayList *list);
bool ArrayList_add(ArrayList *list, element_t element);
bool ArrayList_add_at(ArrayList *list, unsigned int index, element_t element);
bool ArrayList_add_all(ArrayList *dest, ArrayList *src);
void ArrayList_clear(ArrayList *list);
bool ArrayList_contains(ArrayList *list, element_t element);
bool ArrayList_ensure_capacity(ArrayList *list, unsigned int minCapacity);
element_t ArrayList_get(ArrayList *list, unsigned int index);
int ArrayList_index_of(ArrayList *list, element_t element);
bool ArrayList_is_empty(ArrayList *list);
element_t ArrayList_remove_index(ArrayList *list, unsigned int index);
bool ArrayList_remove(ArrayList *list, element_t element);
bool ArrayList_remove_all(ArrayList *list, ArrayList *list2);
void ArrayList_remove_range(ArrayList *list,
        unsigned int fromIndex, unsigned int toIndex);
bool ArrayList_retain_all(ArrayList *list, ArrayList *list2);
int ArrayList_last_index_of(ArrayList *list, element_t element);
element_t ArrayList_set(ArrayList *list, unsigned int index, element_t element);
unsigned int ArrayList_size(ArrayList *list);
bool ArrayList_trim_to_size(ArrayList *list);
