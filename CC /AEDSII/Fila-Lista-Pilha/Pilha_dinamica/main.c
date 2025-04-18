#include "stack.h"

int main(int argc, char const *argv[]){
    Stack *p = (Stack*)malloc(sizeof(Stack));
    p->top = NULL;
    if (!p){
        printf("error of allocation");
        return 1;
    }
    

    push(p, 1);
    push(p, 2);
    push(p, 3);
    push(p, 4);

    show(p);
    printf("\nPOP: %d\n\n", pop(p));

    show(p);

    free(p);
    return 0;
}
