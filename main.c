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
    printf("Escolha a dificuldade:\n");
    printf("1 - Facil.\n");
    printf("2 - Medio.\n");
    printf("3 - Dificil.\n");
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

    int dificuldade;

    scanf("%i",&dificuldade);

    int topo = -1;

    //em cima está as perguntas faceis e em baixo estão as respostas
    char listaEnigmaFacil[15][100] = {"PerguntaFacil1", "PerguntaFacil2", "PerguntaFacil3", "PerguntaFacil4", "O que é aquela coisa que pode lá e pelo menos você vê?", "PerguntaFacil6", "PerguntaFacil7", "PerguntaFacil8", "PerguntaFacil9", "PerguntaFacil10", "PerguntaFacil11", "PerguntaFacil12", "PerguntaFacil13", "PerguntaFacil14", "PerguntaFacil15"};
    char listaRespostaFacil[15][20] = {"RespostaFacil1", "RespostaFacil2", "RespostaFacil3", "RespostaFacil4", "escuridao", "RespostaFacil6", "RespostaFacil7", "RespostaFacil8", "RespostaFacil9", "RespostaFacil10", "RespostaFacil11", "RespostaFacil12", "RespostaFacil13", "RespostaFacil14", "RespostaFacil15"};

    //em cima está as perguntas medias e em baixo estão as respontas
    char listaEnigmaMedio[15][100] = {"PerguntasMedio1", "PerguntasMedio2", "PerguntasMedio3", "PerguntasMedio4", "PerguntasMedio5", "PerguntasMedio6", "PerguntasMedio7", "PerguntasMedio8", "PerguntasMedio9", "PerguntasMedio10", "PerguntasMedio11", "PerguntasMedio12", "PerguntasMedio13", "PerguntasMedio14", "PerguntasMedio15"};
    char listaRespostaMedio[15][20] = {"RespostaMedio1", "RespostaMedio2", "RespostaMedio3", "RespostaMedio4", "RespostaMedio5", "RespostaMedio6", "RespostaMedio7", "RespostaMedio8", "RespostaMedio9", "RespostaMedio10", "RespostaMedio11", "RespostaMedio12", "RespostaMedio13", "RespostaMedio14", "RespostaMedio15"};

    //em cima está as perguntas dificeis e em baixo estão as respostas
    char listaEnigmaDificil[15][100] = {"PerguntaDificil1", "PerguntaDificil2", "PerguntaDificil3", "PerguntaDificil4", "PerguntaDificil5", "PerguntaDificil6", "PerguntaDificil7", "PerguntaDificil8", "PerguntaDificil9", "PerguntaDificil10", "PerguntaDificil11", "PerguntaDificil12", "PerguntaDificil13", "PerguntaDificil14", "PerguntaDificil15"};
    char listaRespostaDificil[15][20] = {"RespostaDificil1", "RespostaDificil2", "RespostaDificil3", "RespostaDificil4", "RespostaDificil5", "RespostaDificil6", "RespostaDificil7", "RespostaDificil8", "RespostaDificil9", "RespostaDificil10", "RespostaDificil11", "RespostaDificil12", "RespostaDificil13", "RespostaDificil14", "RespostaDificil15"};


    char palavra[20];

    int escolha;
    while (sala_atual != NULL) {
        printf("Sala %i: %s\n", sala_atual->numero_sala, sala_atual->descricao);

        if (dificuldade == 1){ //se o jogo for na dificuldade facil
            do{
                printf("%s\n",listaEnigmaFacil[sala_atual->numero_sala-1]);
                scanf("%s", palavra);
            }while(strcmp(palavra, listaRespostaFacil[sala_atual->numero_sala-1]) != 0);
        } else if (dificuldade == 2){ //se o jogo for na dificuldade media
            do{
                printf("Resposta do enigma medio:\n");
                scanf("%s", palavra);
            }while(strcmp(palavra, listaRespostaMedio[sala_atual->numero_sala-1]) != 0);
        } else if (dificuldade == 3){//se o jogo for na dificuldade dificil
            do{
                printf("Resposta do enigma Dificil:\n");
                scanf("%s", palavra);
            }while(strcmp(palavra, listaRespostaDificil[sala_atual->numero_sala-1]) != 0);
        }


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

