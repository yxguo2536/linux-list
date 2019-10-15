#include <assert.h>
#include <stdlib.h>
#include "common.h"
#include "list.h"

static uint16_t values[256];


void list_mergesort(struct list_head *head)
{
    struct list_head list_left, list_right;
    struct list_head *node;
    struct listitem *left = NULL, *right = NULL;

    if (list_empty(head) || list_is_singular(head))
        return;

    INIT_LIST_HEAD(&list_left);
    INIT_LIST_HEAD(&list_right);

    // Split list to half
    int total = 0;
    list_for_each (node, head) {
        total++;
    }
    int leftSize = total / 2, rightSize = total - total / 2;

    for (int i = 0; i < leftSize; i++)
        list_move_tail(head->next, &list_left);
    for (int i = 0; i < rightSize; i++)
        list_move_tail(head->next, &list_right);


    // Sort each half list
    list_mergesort(&list_left);
    list_mergesort(&list_right);

    // Merge two half list
    left = list_first_entry(&list_left, struct listitem, list);
    right = list_first_entry(&list_right, struct listitem, list);
    while (!(list_empty(&list_left) && list_empty(&list_right))) {
        if (list_empty(&list_right) ||
            (!list_empty(&list_left) && left->i < right->i)) {
            list_move_tail(list_left.next, head);
            left = list_first_entry(&list_left, struct listitem, list);
        } else {
            list_move_tail(list_right.next, head);
            right = list_first_entry(&list_right, struct listitem, list);
        }
    }
}

// int main()
// {
//     struct list_head testlist;
//     struct listitem *item = NULL, *is = NULL;
//     size_t i;

//     random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));

//     INIT_LIST_HEAD(&testlist);

//     assert(list_empty(&testlist));

//     for (i = 0; i < ARRAY_SIZE(values); i++) {
//         item = (struct listitem *) malloc(sizeof(*item));
//         assert(item);
//         item->i = values[i];
//         list_add_tail(&item->list, &testlist);
//     }

//     assert(!list_empty(&testlist));

//     qsort(values, ARRAY_SIZE(values), sizeof(values[0]), cmpint);
//     list_mergesort(&testlist);

//     i = 0;
//     list_for_each_entry_safe (item, is, &testlist, list) {
//         assert(item->i == values[i]);
//         list_del(&item->list);
//         free(item);
//         i++;
//     }

//     assert(i == ARRAY_SIZE(values));
//     assert(list_empty(&testlist));

//     return 0;
// }