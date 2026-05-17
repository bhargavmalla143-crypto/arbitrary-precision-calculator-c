// Malla.Surya bhargav
// Batch:36A
/*This project implements an arbitrary precision calculator using the c language to perform
 arithmetic operations on large numbers that exceed the limits of standard data types*/

#include "apc.h"

int main(int argc, char *argv[])
{
	node *head1 = NULL, *tail1 = NULL;
	node *head2 = NULL, *tail2 = NULL;
	node *headR = NULL, *tailR = NULL;

	int sign1 = 1, sign2 = 1;

	// Validation
	if (cla_validation(argc, argv) == FAILURE)
	{
		return 0;
	}

	// Handle sign of operand1
	if (argv[1][0] == '-')
	{
		sign1 = -1;
		argv[1]++;
	}

	// Handle sign of operand2
	if (argv[3][0] == '-')
	{
		sign2 = -1;
		argv[3]++;
	}

	// Create lists
	create_list(argv[1], &head1, &tail1);
	create_list(argv[3], &head2, &tail2);

	// Remove leading zeros
	remove_pre_zeros(&head1);
	remove_pre_zeros(&head2);

	char oper = argv[2][0];

	switch (oper)
	{
	// ================= ADDITION =================
	case '+':
	{
		if (sign1 == sign2)
		{
			addition(tail1, tail2, &headR, &tailR);

			if (sign1 == -1)
				printf("-");
		}
		else
		{
			int ret = compare_list(head1, head2);

			if (ret == OPERAND1)
			{
				subtraction(tail1, tail2, &headR, &tailR);

				if (sign1 == -1)
					printf("-");
			}
			else if (ret == OPERAND2)
			{
				subtraction(tail2, tail1, &headR, &tailR);

				if (sign2 == -1)
					printf("-");
			}
			else
			{
				insert_first(&headR, &tailR, 0);
			}
		}

		remove_pre_zeros(&headR);
		print_list(headR);
		break;
	}

	// ================= SUBTRACTION =================
	case '-':
	{
		if (sign1 != sign2)
		{
			addition(tail1, tail2, &headR, &tailR);

			if (sign1 == -1)
				printf("-");
		}
		else
		{
			int ret = compare_list(head1, head2);

			if (ret == OPERAND1)
			{
				subtraction(tail1, tail2, &headR, &tailR);

				if (sign1 == -1)
					printf("-");
			}
			else if (ret == OPERAND2)
			{
				subtraction(tail2, tail1, &headR, &tailR);

				if (sign1 == 1)
					printf("-");
			}
			else
			{
				insert_first(&headR, &tailR, 0);
			}
		}

		remove_pre_zeros(&headR);
		print_list(headR);
		break;
	}

	// ================= MULTIPLICATION =================
	case 'x':
	case 'X':
	{
		multiplication(tail1, tail2, &headR, &tailR);

		if (sign1 * sign2 == -1)
			printf("-");

		remove_pre_zeros(&headR);
		print_list(headR);
		break;
	}

	// ================= DIVISION =================
	case '/':
	{
		// division by zero check
		if (head2 == NULL || (head2->data == 0 && head2->next == NULL))
		{
			printf("Error: Division by zero\n");
			return 0;
		}

		division(head1, head2, &headR, &tailR);

		if (sign1 * sign2 == -1)
			printf("-");

		remove_pre_zeros(&headR);
		print_list(headR);
		break;
	}

	default:
		printf("Invalid operator\n");
	}

	return 0;
}