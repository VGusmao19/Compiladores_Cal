#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



char token;
void error();
void match(char expectedToken);
int expe();
int term();
int temp();
int factor();


int main()
{
    int result;
    token = getchar();
    result = expe();
    if(token == '\n')
    {
        printf("Result = %d\n", result);
    }else
    {
        error();
    }

return 0;
}


void error()
{
    fprintf(stderr, "Error\n");
    exit(1);
}

void match(char expectedToken)
{
    if(token == expectedToken)
    {
        token = getchar();
    }else
    {
        error();
    }
}

int expe()
{
    int temp = term();
    while((token == '+')  || (token == '-') || (token == '/') || (token == '%'))
    switch(token)
    {
    case'+':
        match('+');
        temp += term();
        break;
    case'-':
        match('-');
        temp -= term();
        break;
    case'/':
        match('/');
        temp /= term();
    case'%':
        match('%');
        temp = temp%term();
    }
    return temp;
}

int term()
{
    int temp = factor();
    while(token == '*')
    {
        match('*');
        temp *= factor();
    }
    while(token == '/')
    {
        match('/');
        temp /= factor();
    }
    return temp;
}

int factor()
{
    int temp;
    if(token == '(')
    {
        match('(');
        temp = expe();
        match(')');
    }else if(isdigit(token))
    {
        ungetc(token, stdin);
        scanf("%d", &temp);
        token = getchar();
    }
    else error();
    return temp;
}
