#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct _treeNode_ {
    struct _treeNode_ *l, *r;
    void *data;
} TNode;

TNode* abpCreate();
TNode* abpInsert(TNode* t, void*data);
void exibirPreOrdem(TNode *pRaiz);
char token;
void error();
void match(char expectedToken);
int expe();
int term();
int factor();



int main()
{
    int result;
    token = getchar();
    TNode *T = abpCreate(token);
    result = expe();
    if(token == '\n')
    {
        exibirPreOrdem(T);
        printf("Result = %d\n", result);
    }else
    {
        error();
    }

return 0;
}



TNode* abpCreate(){
    return NULL;
}

TNode* abpInsert(TNode* t, void*data)
{
    TNode *newt;
    if(t!= NULL){
            t->l = abpInsert(t->l,data);
            t->r = abpInsert(t->r,data);
            return t;
        }else{
        newt=(TNode*)malloc(sizeof(TNode));
        if (newt != NULL){
            newt->data = data;
            newt->l = NULL;
            newt->r = NULL;
            return newt;
        }
    }
    return NULL;
}

void exibirPreOrdem(TNode *TNode){
    if(TNode != NULL){
        printf("\n%i", TNode->data);
        exibirPreOrdem(TNode->l);
        exibirPreOrdem(TNode->r);
    }
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



TNode *exp()
{
    int temp = term();
    while((token == '+')  || (token == '-'))
    switch(token)
    {
    case'+':
        match('+');
        TNode *NewNode = abpCreate();
        NewNode = abpInsert(NewNode, '+');
        TNode *Fesq = term();
        TNode *Fdir = temp;
        temp = NewNode;
        break;
    /*case'-':
        match('-');
        temp -= term();
        break;*/
    return temp;
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
    if(token == '/')
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
