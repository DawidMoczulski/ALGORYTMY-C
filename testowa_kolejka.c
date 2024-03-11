#include<stdio.h>
#include<stdlib.h>

typedef struct elem{

  int x;
  struct elem *nast;

}el;

typedef el *wel;


int main(){


    wel p,q,r;

    p = (wel)malloc(sizeof(el));
    q = (wel)malloc(sizeof(el));
    r = (wel)malloc(sizeof(el));

    p->x = 200;
    q->x = 250;
    p->nast = q;
    q->nast = NULL;
    r->x = 75;
    r->nast = q;
    p->nast = r;

    printf("%d\n", p->x);
    printf("%d\n", q->x);
    printf("%d\n", r->x);

    return 0;
}