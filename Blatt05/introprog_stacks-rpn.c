#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // definiert den speziellen Wert NaN für floats
#include "introprog_input_stacks-rpn.h"

typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};


void stack_push(stack* astack, float value)
{
    stack_element* new_element = malloc(sizeof(stack_element));
    new_element->value = value;

    new_element->next = astack->top;
    astack->top = new_element;
}


float stack_pop(stack* astack)
{
    stack_element* element;
    float value;

    if (astack->top == NULL)
    {
        /* Stack is empty, return NaN */
        value = NAN;
    }
    else
    {
        element = astack->top;
        astack->top = element->next;
        value = element->value;
        free(element);
    }

    return value;
}


void process(stack* astack, char* token)
{
    float value;
    float operand1;
    float operand2;
    float result = 0.0;

    if (is_number(token))
    {
        value = atof(token);
        stack_push(astack, value);
    }
    else if (is_add(token) || is_sub(token) || is_mult(token))
    {
        operand2 = stack_pop(astack);
        operand1 = stack_pop(astack);

        if (is_add(token))
        {
            result = operand1 + operand2;
        }
        else if (is_sub(token))
        {
            result = operand1 - operand2;
        }
        else if (is_mult(token))
        {
            result = operand1 * operand2;
        }

        stack_push(astack, result);
    }
    else
    {
        printf("\n<Logik fehlt!>\n");
        return;

    }
}




/* 
 * Debugausgabe des Stack
 * Diese Funktion kannst du zum debugging des Stack verwenden.
 *
 * astack - Ein Pointer auf den Stack
 */
void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
    printf(" | Nr. | Adresse           | Next              | Wert    |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element* elem=astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %7.3f |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
}


stack* stack_erstellen() {
    // Create a new stack structure
    stack* s = malloc(sizeof(stack));
    // Reset the elements of the Stack
    s->top = NULL;
    // Return a pointer to the Stack
    return s;
}

int main(int argc, char** args)
{
    stack* astack = stack_erstellen();
    char zeile[MAX_STR];
    char* token;

    intro();
    while (taschenrechner_input(zeile) == 0) {
        // Erstes Token einlesen
        token = strtok(zeile, " ");

        while (token != NULL) {
            printf("Token: %s\n", token);
            // Stackoperationen durchführen
            process(astack, token);
            // Nächstes Token einlesen
            token = strtok(NULL, " ");
            print_stack(astack);
        }

        printf("\nExtrahiere Resultat\n");
        float result = stack_pop(astack);
        print_stack(astack);

        if (astack->top != NULL) {
            while (astack->top != NULL) {
                stack_pop(astack);   //Räume Stack auf
            }
            printf("\nDoes not Compute: Stack nicht leer!\n");
        } else if (result != result) {
            printf("\nDoes not Compute: Berechnung fehlgeschlagen!\n");
        } else {
            printf("\nDein Ergebnis:\t%7.3f\n\n", result);
        }
    }
    free(astack);
}

