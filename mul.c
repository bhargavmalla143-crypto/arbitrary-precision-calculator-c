#include "apc.h"

// insert at last
int insert_last(node **head, node **tail, int data) // logic: since we are inserting at the end, we can directly use tail pointer to insert new node
{
    node *new = malloc(sizeof(node));

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail)->next = new;
        *tail = new;
    }

    return 0;
}

node *find_tail(node *head) // logic: to find tail, we can traverse the list until we reach the end (where next is NULL)
{
    while (head->next != NULL)
        head = head->next;
    return head;
}

void multiplication(node *tail1, node *tail2, node **headR1, node **tailR1)
{
    int count = 0;

    node *headR2 = NULL, *tailR2 = NULL;
    node *head_AR = NULL, *tail_AR = NULL;

    node *temp2 = tail2;

    while (temp2 != NULL) // logic: for each digit of operand2, we multiply it with all digits of operand1 and store the result in a temporary list, then we add the temporary list to the final result list (headR1) with appropriate shifting (adding zeros at the end) based on the position of the digit in operand2
    {
        int carry = 0;

        headR2 = NULL;
        tailR2 = NULL;

        node *temp1 = tail1;

        // store digits in reverse first (temporary)
        node *rev_head = NULL, *rev_tail = NULL;

        while (temp1 != NULL) // logic: multiply current digit of operand2 with each digit of operand1 and store the result in reverse order in a temporary list (rev_head, rev_tail)
        {
            int mul = (temp1->data * temp2->data) + carry;

            carry = mul / 10;
            mul = mul % 10;

            insert_last(&rev_head, &rev_tail, mul);

            temp1 = temp1->prev;
        }

        if (carry > 0) //  if there is a carry left after the last multiplication, insert it at the end of the temporary list (rev_head, rev_tail)
        {
            insert_last(&rev_head, &rev_tail, carry);
        }

        // reverse the temporary list into correct order
        node *temp = rev_tail;
        while (temp != NULL)
        {
            insert_last(&headR2, &tailR2, temp->data);
            temp = temp->prev;
        }

        // add zeros (shift)
        for (int i = 0; i < count; i++)
        {
            insert_last(&headR2, &tailR2, 0);
        }

        // first result
        if (*headR1 == NULL)
        {
            *headR1 = headR2;

            *tailR1 = find_tail(*headR1);
        }
        else
        {
            head_AR = NULL;
            tail_AR = NULL;

            node *new_tailR1 = find_tail(*headR1);
            node *new_tailR2 = find_tail(headR2);

            addition(new_tailR1, new_tailR2, &head_AR, &tail_AR);

            *headR1 = head_AR;

            *tailR1 = find_tail(*headR1);
        }

        temp2 = temp2->prev;
        count++;
    }
}