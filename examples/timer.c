#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"

extern void list_insertsort(struct list_head *head);
extern void list_quicksort(struct list_head *head);
extern void list_mergesort(struct list_head *head);

#define ANALYZE(name)                            \
    clock_gettime(CLOCK_REALTIME, &clock_start); \
    list_##name##sort(&name##_list);             \
    clock_gettime(CLOCK_REALTIME, &clock_end);   \
    printf("%lu ", clock_end.tv_nsec - clock_start.tv_nsec)

int main(int argc, char **argv)
{
    uint16_t values[atoi(argv[1])];
    struct list_head insert_list, quick_list, merge_list;
    struct listitem *item1, *item2, *item3;
    struct timespec clock_start, clock_end;

// Initialize unsorted list node
#ifdef RANDOM
    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));
#elif ASC
    ascending_array(values, ARRAY_SIZE(values));
#elif DEC
    decending_array(values, ARRAY_SIZE(values));
#elif SEPERATE
    odd_even_seperate_array(values, ARRAY_SIZE(values));
#endif

    INIT_LIST_HEAD(&insert_list);
    INIT_LIST_HEAD(&quick_list);
    INIT_LIST_HEAD(&merge_list);
    assert(list_empty(&insert_list) && list_empty(&quick_list) &&
           list_empty(&merge_list));

    for (int i = 0; i < ARRAY_SIZE(values); i++) {
        item1 = (struct listitem *) malloc(sizeof(*item1));
        item2 = (struct listitem *) malloc(sizeof(*item2));
        item3 = (struct listitem *) malloc(sizeof(*item3));
        assert(item1 && item2 && item3);
        item1->i = item2->i = item3->i = values[i];
        list_add_tail(&item1->list, &insert_list);
        list_add_tail(&item2->list, &quick_list);
        list_add_tail(&item3->list, &merge_list);
    }
    assert(!list_empty(&insert_list) && !list_empty(&quick_list) &&
           !list_empty(&merge_list));


    // Sorting & Timing
    if (strcmp(argv[2], "all") == 0) {
        ANALYZE(insert);
        ANALYZE(quick);
        ANALYZE(merge);
    } else {
        for (int i = 0; i < strlen(argv[2]); i++) {
            switch (argv[2][i]) {
            case 'i':
                ANALYZE(insert);
                break;
            case 'q':
                ANALYZE(quick);
                break;
            case 'm':
                ANALYZE(merge);
                break;
            default:
                return -1;
            }
        }
    }
}