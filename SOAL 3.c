#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

typedef struct {
    double data[MAX];
    int top;
} Stack;

// Fungsi untuk membuat stack
void initStack(Stack *s) {
    s->top = -1;
}

// Fungsi untuk mengecek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Fungsi untuk menambahkan elemen ke stack
void push(Stack *s, double value) {
    if (s->top < MAX - 1) {
        s->data[++s->top] = value;
    } else {
        printf("Stack overflow!\n");
    }
}

// Fungsi untuk menghapus elemen dari stack
double pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top--];
    } else {
        printf("Stack underflow!\n");
        return 0;
    }
}

// Fungsi untuk mengevaluasi ekspresi postfix
double evaluatePostfix(const char *exp) {
    Stack s;
    initStack(&s);
    printf("Langkah-langkah evaluasi ekspresi postfix:\n");

    for (const char *p = exp; *p != '\0'; p++) {
        if (isspace(*p)) {
            continue; // Lewati spasi
        }

        if (isdigit(*p)) {
            // Ambil angka penuh (jika lebih dari satu digit)
            double num = strtod(p, (char**)&p);
            push(&s, num);
            printf("Push: %.2f\n", num);
            p--; // Kembali satu langkah untuk memperbaiki increment
        } else {
            double op2 = pop(&s);
            double op1 = pop(&s);
            double result;

            switch (*p) {
                case '+':
                    result = op1 + op2;
                    printf("Pop: %.2f, %.2f; Push: %.2f (%.2f + %.2f)\n", op1, op2, result, op1, op2);
                    break;
                case '-':
                    result = op1 - op2;
                    printf("Pop: %.2f, %.2f; Push: %.2f (%.2f - %.2f)\n", op1, op2, result, op1, op2);
                    break;
                case '*':
                    result = op1 * op2;
                    printf("Pop: %.2f, %.2f; Push: %.2f (%.2f * %.2f)\n", op1, op2, result, op1, op2);
                    break;
                case '/':
                    if (op2 != 0) {
                        result = op1 / op2;
                        printf("Pop: %.2f, %.2f; Push: %.2f (%.2f / %.2f)\n", op1, op2, result, op1, op2);
                    } else {
                        printf("Error: Division by zero!\n");
                        return 0;
                    }
                    break;
                case '^':
                    result = pow(op1, op2);
                    printf("Pop: %.2f, %.2f; Push: %.2f (%.2f ^ %.2f)\n", op1, op2, result, op1, op2);
                    break;
                default:
                    printf("Error: Unknown operator %c\n", *p);
                    return 0;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}

int main() {
    char exp[MAX];
    printf("Masukkan ekspresi postfix (contoh: 3 4 + 2 * 7 /): ");
    fgets(exp, sizeof(exp), stdin);

    double result = evaluatePostfix(exp);
    printf("Hasil evaluasi ekspresi postfix: %.2f\n", result);

    return 0;
}
