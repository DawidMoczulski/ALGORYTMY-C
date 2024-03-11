#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct stackNode
{
    char* value;
    struct stackNode *next;
} stack;

typedef stack *node;

//Funkcje do obslugi stosu

void push(node* head, char* val)
{
    node new_node=(stack*)malloc(sizeof(stack));
    new_node->value = val;
    new_node->next = *head;
    *head = new_node;
}
char* pop(node* head)
{
    if (*head == NULL) 
    {
        printf ("Blad. Przepelnienie stosu.\n");
        return NULL;
    }
    char *val = (*head)->value;
    node temp = *head;
    *head=(*head)->next;
    free(temp);
    return val;
}

// Funkcje pomocnicze do wykonania kalkulacji

int isOperator(char c)
{
    return (c == '-' || c == '+' || c == '*' || c == '/' || c == 'n');
}

float performOperation (float operand1, float operand2, char operator)
{
    switch (operator)
    {
    case '-': return operand1 - operand2;
    case '+': return operand1 + operand2;
    case '*': return operand1 * operand2;
    case '/': return operand1 / operand2;
    case 'n': return -operand1;

    default:
        printf("Nieprawidlowa operacja.\n");
        break;
    }
    exit(EXIT_FAILURE);
}

// Funkcja prawidlowa

float calculate(char* expression)
{
    node stackHead = NULL;
    char* token = strtok(expression, " "); // strtok w tym wypadku usuwa spacje i zamienia na znak terminala
        while (token != NULL) 
        {
            // isdigit sprawdza czy jest to cyfra
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) push(&stackHead, token);
            else if (isOperator(token[0])) 
            {
                if (strcmp(token, "neg") == 0) 
                {
                    float operand = atof(pop(&stackHead));
                    float result = performOperation(operand, 0, 'n');
                    char resultStr[20];
                    snprintf(resultStr, sizeof(resultStr), "%.2f", result);
                    push(&stackHead, strdup(resultStr));
                }
                else
                {
                    float operand2 = atof(pop(&stackHead)); //  atof - zmienia ciag znakow na float
                    float operand1 = atof(pop(&stackHead));
                    float result = performOperation(operand1, operand2, token[0]);
                    char resultStr[20];
                    // snprintf - zapisuje sformatowane dane do ciagu, 1 parametr gdzie, 2 wiekosc, 3 jakiego typu, 4 skad
                    snprintf(resultStr, sizeof(resultStr), "%.2f", result); 
                    push(&stackHead, strdup(resultStr));  //strdup duplikuje stringa podanego jako argumnet
                }
            } 
            else 
            {
                printf("BLAD: Nieprawidłowy znak w wyrazeniu.\n");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " "); // kontynuuje podzial lancucha kod kolejnego momnetu cos ala obrot petli
        }
    float finalResult = atof(pop(&stackHead));
    if (stackHead != NULL) 
    {
        printf("BLAD. Nieprawidlowe wyrazenie\n");
        exit(EXIT_FAILURE);
    }
    return finalResult;
}



int main()
{
    char expression[] = "3 4 + 7 * ";
    float result = calculate(expression);
    printf("Wynik: %.1f\n", result);

    return 0;
}