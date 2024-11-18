
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

// Stack structure
typedef struct {
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

// Function prototypes
void push(Stack *s, int value);
int pop(Stack *s);
int evaluatePostfix(char *expr);

int main() {
    char expr[100];
    printf("Enter a postfix expression: ");
    fgets(expr, sizeof(expr), stdin);

    int result = evaluatePostfix(expr);
    printf("Result: %d\n", result);

    return 0;
}

// Function to push an element onto the stack
void push(Stack *s, int value) {
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

// Function to pop an element from the stack
int pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

// Function to evaluate a postfix expression
int evaluatePostfix(char *expr) {
    Stack s;
    s.top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            push(&s, expr[i] - '0');
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            switch(expr[i]) {
                case '+':
                    push(&s, operand1 + operand2);
                    break;
                case '-':
                    push(&s, operand1 - operand2);
                    break;
                case '*':
                    push(&s, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0) {
                        push(&s, operand1 / operand2);
                    } else {
                        printf("Error: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
            }
        }
    }

    return pop(&s);
}
