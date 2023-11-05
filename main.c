#include <stdio.h>
#include <stdlib.h>

void telaInicial();


int main(){

    int escolha;
    
    do{
        telaInicial();
        scanf("%i",&escolha);

        switch (escolha)
        {
        case 1:
            system("cls");
            printf("Meus livros.\n");
            break;

        case 2:
            system("cls");
            printf("Inserir livro.\n");
            break;

        case 3:
            system("cls");
            printf("Remover um livro.\n");
            break;

        case 4:
            system("cls");
            printf("Informacoes gerais.\n");
            break;

        case 5:
            exit(1);
        default:
            system("cls");
            printf("\t\tOPCAO INCORRETA\n\n");
        
        }
    }while(escolha < 1 || escolha > 5);

    return 0;
}

void telaInicial(){
    printf("\t\tSIMULADOR DE BIBLIOTECA\n");
    printf("Escolha alguma opcao: \n");
    printf("1 - Meus livros.\n");
    printf("2 - Inserir um livro.\n");
    printf("3 - Remover um livro.\n");
    printf("4 - Informacoes gerais.\n");
    printf("5 - Sair.\n");

}