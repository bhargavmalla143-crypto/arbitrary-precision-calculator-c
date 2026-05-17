#include "apc.h"

void division(node *head1, node *head2, node **headR, node **tailR)
{
    node *temp = head1;

    node *head_OPR1 = NULL, *tail_OPR1 = NULL;
    node *head_SR = NULL, *tail_SR = NULL;

    int sub_count = 0;

    while (temp != NULL) // logic: we bring down one digit from operand1 at a time and keep subtracting operand2 from it until the result is less than operand2, the number of times we can subtract is the quotient digit for that position, we repeat this process until we exhaust all digits of operand1
    {
        // bring digit
        insert_last(&head_OPR1, &tail_OPR1, temp->data);

        remove_pre_zeros(&head_OPR1);
        tail_OPR1 = find_tail(head_OPR1);

        // repeat subtraction
        while (compare_list(head_OPR1, head2) == OPERAND1 ||
               compare_list(head_OPR1, head2) == SAME)
        {
            head_SR = NULL;
            tail_SR = NULL;

            //  correct tails
            subtraction(tail_OPR1, find_tail(head2), &head_SR, &tail_SR);

            // replace OPR1 with result
            head_OPR1 = head_SR;
            tail_OPR1 = find_tail(head_OPR1);

            remove_pre_zeros(&head_OPR1);

            sub_count++;
        }

        insert_last(headR, tailR, sub_count); // insert quotient digit at the end of the result list

        sub_count = 0;

        temp = temp->next;
    }

    remove_pre_zeros(headR);
}