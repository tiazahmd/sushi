#include <stdbool.h>
#include <stdio.h>

bool running = true;
int ip = 0;
int sp = -1;
int stack[256];

typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

// This is to test the program out
const int program [] = {
    PSH, 5,
    PSH, 6,
    PSH, 9,
    PSH, 10,
    POP,
    ADD,
    POP,
    HLT
};

int fetch() {
    return program[ip];
}

void eval(int instr) {
    switch (instr) {
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            sp++;
            stack[sp] = program[++ip];
            break;
        }
        case POP: {
            int val_popped = stack[sp--];
            printf("Popped %d\n", val_popped);
            break;
            }
            case ADD: {
                int a = stack[sp--];
                int b = stack[sp--];
                int result = b + a;
                sp++;
                stack[sp] = result;
                break;
            }
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
}