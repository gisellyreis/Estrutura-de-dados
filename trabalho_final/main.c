#include <stdio.h>
#include <stdlib.h>

#include "tree.c"

int main(){
    printf(" Escolha uma Operação\n"); //

	printf("1.Incluir intervalo\n");

	printf("2.Remover intervalo\n");

	printf("3.Buscar intervalo\n"); 

	printf("4.Listar intervalos\n");

	printf("5.Listar Árvore\n");

	nodet *myT=NULL;
    intert *myIp=NULL, myI;
    int value;
    while(TRUE){
        scanf("%d", &value);
        switch(value){
            case 1:
                scanf("%d %d", &myI.a, &myI.b);
                myIp = newInterval();
                *myIp = myI;
                myT = node_insert(myIp, myT);
            break;
            case 2:
                scanf("%d %d", &myI.a, &myI.b);
                myT = node_delete(&myI, myT);
            break;
            case 3:
                scanf("%d %d", &myI.a, &myI.b);
                myIp = search(&myI, myT);
                if(myIp){
                    printf("[%03d,%03d]\n", myIp->a, myIp->b);
                }
                else{
                    printf("NULL\n");
                }
            break;
            case 4:
                scanf("%d %d", &myI.a, &myI.b);
                overlap(&myI, myT);
                printf("\n");
            break;
            case 5:
                inorder(myT);
                //display(myT);
                printf("\n");
            break;
        }
    }
}