#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SALAS 100

//estrutura da sala
typedef struct Sala {
    int numero_sala;
    char descricao[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

//criar uma sala
void criarSala(Sala** sala, int numero_sala, const char descricao[]) {
    *sala = (Sala*)malloc(sizeof(Sala));
    if (*sala == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    (*sala)->numero_sala = numero_sala;
    strcpy((*sala)->descricao, descricao);
    (*sala)->esquerda = NULL;
    (*sala)->direita = NULL;
}

//concectar as salas
void conectarSalas(Sala* de, Sala* sala_esquerda, Sala* sala_direita) {
    de->esquerda = sala_esquerda;
    de->direita = sala_direita;
}

void telaInicial(){
    printf("\t\tBEM VINDO\n");
}

void liberarArvore(Sala* sala) {
    if (sala != NULL) {
        liberarArvore(sala->esquerda);
        liberarArvore(sala->direita);
        free(sala);
    }
}

struct Sala *pilha[MAX_SALAS];

int main() {
    //aqui vai iniciar as salas
    Sala* sala_8 = NULL;
    Sala* sala_5 = NULL;
    Sala* sala_2 = NULL;
    Sala* sala_6 = NULL;
    Sala* sala_11 = NULL;
    Sala* sala_14 = NULL;
    Sala* sala_10 = NULL;
    Sala* sala_1 = NULL;
    Sala* sala_3 = NULL;
    Sala* sala_4 = NULL;
    Sala* sala_7 = NULL;
    Sala* sala_9 = NULL;
    Sala* sala_12 = NULL;
    Sala* sala_13 = NULL;
    Sala* sala_15 = NULL;
    Sala* sala_anterior = NULL;


    //aqui voce cria e coloca as caracteristicas da sala  (&nomeDaSala, numero da sala, Comentario da sala);
    criarSala(&sala_8, 8, "Voce esta no comeco do labirinto. SALA 8");
    criarSala(&sala_5, 5, "SALA 5");
    criarSala(&sala_2, 2, "SALA 2");
    criarSala(&sala_6, 6, "SALA 6");
    criarSala(&sala_11, 11, "SALA 11");
    criarSala(&sala_14, 14, "SALA 14");
    criarSala(&sala_10, 10, "SALA 10");
    criarSala(&sala_1, 1, "SALA 1");
    criarSala(&sala_3, 3, "SALA 3");
    criarSala(&sala_4, 4, "SALA 4");
    criarSala(&sala_7, 7, "SALA 7");
    criarSala(&sala_9, 9, "SALA 9");
    criarSala(&sala_12, 12, "SALA 12");
    criarSala(&sala_13, 13, "SALA 13");
    criarSala(&sala_15, 15, "SALA 15");

    //aqui ira conectar as salas
    conectarSalas(sala_8, sala_5, sala_11);
    conectarSalas(sala_5, sala_2, sala_6);
    conectarSalas(sala_11, sala_10, sala_14);
    conectarSalas(sala_2, sala_1, sala_3);
    conectarSalas(sala_6, sala_4, sala_7);
    conectarSalas(sala_10, sala_9, sala_12);
    conectarSalas(sala_14, sala_13, sala_15);

    Sala* sala_atual = sala_8; //usar isso aqui para saber a posição do enigma

    telaInicial();

    int topo = -1;

    int escolha;
    while (sala_atual != NULL) {
        printf("Sala %i: %s\n", sala_atual->numero_sala, sala_atual->descricao);

        if (sala_atual->esquerda != NULL || sala_atual->direita != NULL || sala_atual->esquerda == NULL || sala_atual->direita == NULL) {
            printf("Escolha 1 para ir para a sala a esquerda e 2 para a sala a direita, e 0 para voltar para sala anterior: ");
            scanf("%i", &escolha);

            sala_anterior = sala_atual;

            if(escolha == 0 && topo >= 0){
                sala_atual = pilha[topo--];
            } else if (escolha == 1) {
                //sala_anterior = sala_atual;
                pilha[++topo] = sala_anterior;
                sala_atual = sala_atual->esquerda;
            } else if (escolha == 2) {
                //sala_anterior = sala_atual;
                pilha[++topo] = sala_anterior;
                sala_atual = sala_atual->direita;
            } else {
                printf("Escolha invalida. Tente novamente.\n");
            }
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        } else {
            sala_atual = NULL;
            printf("Voce chegou ao fim do labirinto.\n");
        }
    }

    liberarArvore(sala_8);

    return 0;
}

