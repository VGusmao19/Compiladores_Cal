#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tree
{
  int num;
  struct tree* sad;
  struct tree* sae;
} Tree;



char token;
void error();
void match(char expectedToken);
int expe();
int temp();
int factor();
Tree* createTree();
void showTree(Tree* t);
int treeIsEmpty(Tree* t);

Tree* createTree()
{
  /* Uma árvore é representada pelo endereço do nó raiz,
     essa função cria uma árvore com nenhum elemento,
     ou seja, cria uma árvore vazia, por isso retorna NULL. */
  return NULL;
}

void showTree(Tree* t)
{
  /* Essa função imprime os elementos de forma recursiva */

  printf("<"); /* notação para organizar na hora de mostrar os elementos */
  if(!treeIsEmpty(t)) /* se a árvore não for vazia... */
  {
    /* Mostra os elementos em pré-ordem */
    printf("%d", t->num); /* mostra a raiz */
    showTree(t->sae); /* mostra a sae (subárvore à esquerda) */
    showTree(t->sad); /* mostra a sad (subárvore à direita) */
  }
  printf(">"); /* notação para organizar na hora de mostrar os elementos */
}

int treeIsEmpty(Tree* t)
{
  /* Retorna 1 se a árvore for vazia e 0 caso contrário */
  return t == NULL;

}

void insertTree(Tree** t, int num)
{
  /* Essa função insere os elementos de forma recursiva */
  if(*t == NULL)
  {
    *t = (Tree*)malloc(sizeof(Tree)); /* Aloca memória para a estrutura */
    (*t)->sae = NULL; /* Subárvore à esquerda é NULL */
    (*t)->sad = NULL; /* Subárvore à direita é NULL */
    (*t)->num = num; /* Armazena a informação */
  } else {
    if(num < (*t)->num) /* Se o número for menor então vai pra esquerda */
    {
      /* Percorre pela subárvore à esquerda */
      insertTree(&(*t)->sae, num);
    }
    if(num > (*t)->num) /* Se o número for maior então vai pra direita */
    {
      /* Percorre pela subárvore à direita */
      insertTree(&(*t)->sad, num);
    }
  }
}

Tree *exp()
{
    Tree *novatemp = createTree();
    int temp = term();
    while((token == '+')  || (token == '-'))
    switch(token)
    {
    case'+':
        insertTree(novatemp, '+');
        match('+');
        insertTree(novatemp, temp);
        insertTree(novatemp, term());
        //temp = novatemp;
        break;
    case'-':
        insertTree(novatemp, '-');
        match('-');
        insertTree(novatemp, temp);
        insertTree(novatemp, term());
        //temp = novatemp;
        break;
    }
    return novatemp;
}



int main()
{
    int result;
    token = getchar();
    result = expe();
    Tree *teste = createTree();
    teste = exp();
    if(token == '\n')
    {
        printf("Result = %d\n", result);
        if(teste == NULL)
        {
            printf("esta vazia");
        }
        showTree(teste);
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
        temp = temp/term();
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
    //else error();
    return temp;
}



