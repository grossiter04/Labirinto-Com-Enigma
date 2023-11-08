#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos a estrutura da sala
typedef struct Sala {
    int numero_sala;
    char descricao[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Função para criar uma sala
void criarSala(Sala** sala, int numero_sala, const char descricao[]) {
    *sala = (Sala*)malloc(sizeof(Sala));
    if (*sala == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }
    (*sala)->numero_sala = numero_sala;
    strcpy((*sala)->descricao, descricao);
    (*sala)->esquerda = NULL;
    (*sala)->direita = NULL;
}

// Função para conectar salas
void conectarSalas(Sala* de, Sala* sala_esquerda, Sala* sala_direita) {
    de->esquerda = sala_esquerda;
    de->direita = sala_direita;
}

int main() {
    //aqui vai iniciar as salas
    Sala* sala_inicial = NULL;
    Sala* sala_esquerda = NULL;
    Sala* sala_direita = NULL;
    Sala* sala_20 = NULL;
    Sala* sala_8 = NULL;

    //aqui voce vai colocar as caracteristicas da sala  (&nomeDaSala, numero da sala, Comentario da sala);
    criarSala(&sala_inicial, 10, "Você está no começo do labirinto. Escolha para onde deseja ir.");
    criarSala(&sala_esquerda, 9, "Você está na sala à esquerda. Há uma porta à direita.");
    criarSala(&sala_direita, 11, "Você está na sala à direita. Há uma porta à esquerda.");
    criarSala(&sala_20, 20, "Voce esta na sala 20");
    criarSala(&sala_8, 8, "voce esta na sala 8");

    //aqui ira conectar as salas
    conectarSalas(sala_inicial, sala_esquerda, sala_direita);
    conectarSalas(sala_direita, sala_8, sala_20);

    Sala* sala_atual = sala_inicial;

    int escolha;
    while (sala_atual != NULL) {
        printf("Sala %i: %s\n", sala_atual->numero_sala, sala_atual->descricao);

        if (sala_atual->esquerda != NULL && sala_atual->direita != NULL) {
            printf("Escolha 1 para ir para a sala à esquerda e 2 para a sala à direita: ");
            scanf("%i", &escolha);

            if (escolha == 1) {
                sala_atual = sala_atual->esquerda;
            } else if (escolha == 2) {
                sala_atual = sala_atual->direita;
            } else {
                printf("Escolha inválida. Tente novamente.\n");
            }
        } else {
            sala_atual = NULL;
            printf("Você chegou ao fim do labirinto.\n");
        }
    }

    return 0;
}
