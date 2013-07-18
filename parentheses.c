/*
 * Question:
 * Implement an algorithm to print all valid (e.g., properly opened and closed)
 * combinations of n-pairs of parentheses.
 *
 * */
#include <stdlib.h>
#include <stdio.h>

int parentheses(int n, int l, int r, char *output);

int main()
{
	int n = 3;
	char *output = malloc(sizeof(char)*(1+n));
	output[n] = '\0';
	int ret = parentheses(n, 0, 0, output);
	printf("\n# of parentheses = %d\n", ret);
	return 0;
}


int parentheses(int n, int l, int r, char *output)
{
	int rvl = 0;
	if (l == n)
	{
		while (n - r)
		{
			output[l + r] = ')';
			r++;
		}
		rvl += 1;
		int i;
		printf("%s, ", output);
	}
	else
	{
		output[l + r] = '(';
		rvl += parentheses(n, l + 1, r, output);
		if (l > r)
		{
			output[l + r] = ')';
			rvl += parentheses(n, l, r + 1, output);
		}
	}

	return rvl;
}
