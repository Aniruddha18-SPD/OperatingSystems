#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int (*OP) (int a, int b);

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int exitt(int a, int b);

int main (void)
{
	/* IMPLEMENT ME: Insert your algorithm here */
	int a = 6;
	int b = 3;
	OP operators[5] = {&add, &subtract, &multiply, &divide, &exitt};
	char idx[3];
	while (true) {
		printf("Operand 'a' : %d | Operand 'b' : %d\nSpecify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): ", a, b);
		fgets(idx, 3, stdin);
		printf("X = %d\n", operators[(int)idx[0]-'0'](a, b));
	}
	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int subtract (int a, int b) { printf ("Subtracting 'a' and 'b'\n"); return a - b; }
int multiply (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b; }
int divide (int a, int b) { printf ("Dividing 'a' and 'b'\n"); return a / b; }
int exitt (int a, int b) { exit(0); }