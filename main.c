#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SALAS 15

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
    printf(" ___\n");
    printf("                    .\"///\".\n");
    printf("                   /|<> <>!\\\n");
    printf("                  /-|  ^  !-\\\n");
    printf("                 /-- \\_=_/ --\\\n");
    printf("                 )---| W |---(\n");
    printf("                /-\\--| W |--/-\\\n");
    printf("               (_-_--|_-_|--___)\n");
    printf("              (-___  -_-- _-- -_)\n");
    printf("             )-_ _--_ _ ___--__|\n");
    printf("            (___ --__  __ __--(\n");
    printf("           /-_  / __ -_ -__  \\_\\\n");
    printf("          _>/  -- /|___| _ \\ -_ )\n");
    printf("         /--  _ - _/ _ \\>\\ -  -- \\\n");
    printf("        ( / / /   > |~l \\   \\ \\ \\_)\n");
    printf("     jjs| |-\' | |/  \"\"\"  \\| |   |_|\n");
    printf("        L_|_|_|_/         L_L_|_l_)\n");
    printf("\t\tBOAS VINDAS AO ENIGMA DA ESFINGE!\n");
    printf("Escolha a dificuldade:\n");
    printf("1 - Facil.\n");
    printf("2 - Medio.\n");
    printf("3 - Dificil.\n");
    printf("4 - Sair.\n");
}

void liberarArvore(Sala* sala) {
    if (sala != NULL) {
        liberarArvore(sala->esquerda);
        liberarArvore(sala->direita);
        free(sala);
    }
}

void limpaTela(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
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
    criarSala(&sala_1, 1, "Voce esta na ultima sala do labirinto. SALA1");
    criarSala(&sala_3, 3, "Voce esta na ultima sala do labirinto. SALA 3");
    criarSala(&sala_4, 4, "Voce esta na ultima sala do labirinto. SALA 4");
    criarSala(&sala_7, 7, "Voce esta na ultima sala do labirinto. SALA 7");
    criarSala(&sala_9, 9, "Voce esta na ultima sala do labirinto. SALA 9");
    criarSala(&sala_12, 12, "Voce esta na ultima sala do labirinto. SALA 12");
    criarSala(&sala_13, 13, "Voce esta na ultima sala do labirinto. SALA 13");
    criarSala(&sala_15, 15, "Voce esta na ultima sala do labirinto. SALA 15");

    //aqui ira conectar as salas
    conectarSalas(sala_8, sala_5, sala_11);
    conectarSalas(sala_5, sala_2, sala_6);
    conectarSalas(sala_11, sala_10, sala_14);
    conectarSalas(sala_2, sala_1, sala_3);
    conectarSalas(sala_6, sala_4, sala_7);
    conectarSalas(sala_10, sala_9, sala_12);
    conectarSalas(sala_14, sala_13, sala_15);

    Sala* sala_atual = sala_8; //usar isso aqui para saber a posição do enigma

    
    limpaTela();
    telaInicial();

    int dificuldade;

    scanf("%i",&dificuldade);

    if(dificuldade == 4) {
        liberarArvore(sala_8);
        exit(1);
    }

    int topo = -1;

    //em cima está as perguntas faceis e em baixo estão as respostas
    char listaEnigmaFacil[15][150] = {"Sem asas, eu voo; sem olhos, eu choro. O que sou?", "Sou leve como uma pluma, mas nem o homem mais forte pode me segurar por muito tempo. O que sou?", "Sou tirado da terra, mas nunca saio do chao. O que sou?", "Tenho chaves, mas nao abro portas. Tenho espaço, mas nao tenho quartos. O que sou?", "Se voce olhar para o meu rosto, nao encontrara treze em nenhum lugar. O que eu sou?", "Tenho rabo, mas nao sou cao Nao tenho asas, mas sei voar Se me largarem, nao subo, Mas saio ao vento a brincar. Quem sou eu?", "Pode ser atirado do alto de um predio e ficar super bem. Mas quando eh colocado na agua morre pouco tempo depois. O que sou?", "Fica cada vez mais molhado quanto mais a gente seca. O que sou?", "Voce tira a minha pele. Eu não choro. Voce, sim. O que sou?", "Anda sobre quatro membros de manha, dois a tarde e tres a noite. O que sou?", "Quanto mais voce tira, mais eu cresco. O que sou?", "Nao eh vivo, mas cresce. Nao tem pulmoes, mas precisa de ar. Nao tem boca, mas a agua pode mata-lo. O que sou?", "Sou preto quando voce compra, vermelho quando voce usa e cinza quando voce joga fora. O que sou?", "Faco duas pessoas a partir de uma so. O que sou?", "Sou cheio de furinhos, mas ainda assim consigo segurar agua. O que sou?"};
    char listaRespostaFacil[15][20] = {"nuvem", "ar", "foto", "teclado", "relogio", "pipa", "papel", "toalha", "cebola", "humano", "buraco", "fogo", "carvao", "espelho", "esponja"};

    //em cima está as perguntas medias e em baixo estão as respontas
    char listaEnigmaMedio[15][150] = {"O que um bom navegador faz quando o barco afunda?", "Como se chama a plantinha que nao enxerga nada?", "Qual a banda preferida dos mortos?", "Qual eh o animal que nao vale mais nada?", "Estou acima do rei. O que sou?", "PerguntasMedio6", "PerguntasMedio7", "PerguntasMedio8", "PerguntasMedio9", "PerguntasMedio10", "Eu faço a barba, diversas vezes por dia, e continuo barbudo. Quem sou eu?", "PerguntasMedio12", "PerguntasMedio13", "PerguntasMedio14", "PerguntasMedio15"};
    char listaRespostaMedio[15][20] = {"nada", "acelga", "sepultura", "javali", "coroa", "RespostaMedio6", "RespostaMedio7", "RespostaMedio8", "RespostaMedio9", "RespostaMedio10", "barbeiro", "RespostaMedio12", "RespostaMedio13", "RespostaMedio14", "RespostaMedio15"};

    //em cima está as perguntas dificeis e em baixo estão as respostas
    char listaEnigmaDificil[15][150] = {"O que e algo que as pessoas tem, mas que nunca compartilham?", "Eu falo, mas nao tenho boca. Eu ouço, mas nao tenho ouvidos. Não tenho corpo, mas vivo com o vento. Quem sou eu?", "Eu sou algo que as pessoas amam ou odeiam. Eu mudo tanto a aparencia das pessoas quanto seus pensamentos. Se uma pessoa cuida de si mesma, eu subo ainda mais. Eu engano algumas pessoas. E para outras, sou um verdadeiro misterio. Algumas pessoas bem que tentam me esconder, mas uma hora, inevitavelmente, eu apareco. Não importa o que as pessoas tentem, eu jamais cairei. Quem sou eu?", "Quando precisa de mim, voce me atira para longe, ate um lugar onde ninguem pode me ver. Mas quando ja não precisa mais, você me traz de volta. Quem sou eu?", "Ponha os dedos nos meus olhos que eu abrirei as minhas potentes mandibulas. E vou devorar tudo o que vier pela frente: roupas, penas, papeis. Quem sou eu?", "Quem me faz nao diz que faz. Quem me tem nao sabe que tem. E quem sabe nao me quer ter de jeito nenhum. Quem sou eu?", "Voce mede a minha vida em horas e eu te sirvo indo embora. Sou rapida quanto estou magra e devagar quando estou gorda. O vento e o meu maior inimigo. Quem sou eu?", "A mae de Mary teve quatro filhos. Abril, Maio e Junho foram os tres primeiros. Qual o nome da quarta crianca?", "O que pode correr, mas nunca anda; tem leito, mas nunca dorme; nasce, mas nao morre?", "Meu trovao vem antes do relâmpago, meu raio vem antes das nuvens e minha chuva seca toda terra em que toca. Quem eu sou?", "Posso ser aberto ou fechado, grande ou pequeno. Posso revelar a verdade ou escondê-la. Quase sempre sou bem-vindo e posso surgir sem avisar. Todo mundo tem, mas nem todos compartilham. Que eu sou?", "O que é sempre velho e algumas vezes novo; nunca chora e sempre murmura; nunca corre, mas anda devagar?", "O que é sempre verde e nunca cresce?", "Sou liquido, mas posso queimar. Em um recipiente, me contenho, mas em liberdade, me transformo em dança. O que sou?", "Sou a ponte entre a terra e o ceu, mas nunca me movo. O que sou?"};
    char listaRespostaDificil[15][20] = {"segredo", "eco", "idade", "ancora", "tesoura", "dinheiro falso", "vela", "Mary", "rio", "vulcao", "sorriso", "livro", "cor", "gas", "horizontes"};

    char frase[150];
    char FraseCerta[] = "coisas da vida";

    char palavra[20];

    int escolha;
    while (sala_atual != NULL) {
        limpaTela();
        printf("Sala %i: %s\n", sala_atual->numero_sala, sala_atual->descricao);

        if (dificuldade == 1){ //se o jogo for na dificuldade facil
            do{
                printf("%s\n",listaEnigmaFacil[sala_atual->numero_sala-1]);
                scanf("%s", palavra);

                if(strcmp(palavra, listaRespostaFacil[sala_atual->numero_sala-1]) != 0){ 
                    limpaTela(); //pra cada interação limpar a a tela
                    printf("Resposta Errada.\n");
                }

            }while(strcmp(palavra, listaRespostaFacil[sala_atual->numero_sala-1]) != 0);

        } else if (dificuldade == 2){ //se o jogo for na dificuldade media
            do{
                printf("%s\n",listaEnigmaMedio[sala_atual->numero_sala-1]);
                scanf("%s", palavra);

                if(strcmp(palavra, listaRespostaMedio[sala_atual->numero_sala-1]) != 0){ 
                    limpaTela(); //pra cada interação limpar a a tela
                    printf("Resposta Errda.\n");
                }

            }while(strcmp(palavra, listaRespostaMedio[sala_atual->numero_sala-1]) != 0);

        } else if (dificuldade == 3){//se o jogo for na dificuldade dificil
            do{
                printf("%s\n",listaEnigmaDificil[sala_atual->numero_sala-1]);
                scanf("%s", palavra);

                if(strcmp(palavra, listaRespostaDificil[sala_atual->numero_sala-1]) != 0){
                    limpaTela();//para cada interação limpar a tela
                    printf("Resposta Errada.\n");
                }

            }while(strcmp(palavra, listaRespostaDificil[sala_atual->numero_sala-1]) != 0);
        }

        limpaTela();

        if (sala_atual->esquerda != NULL || sala_atual->direita != NULL) {


            sala_anterior = sala_atual;

            do{
                printf("Escolha 0 para ir pra sala anterior, escolha 1 para a sala a esquerda, escolha 2 para a sala a direita, escolha 3 para sair do jogo, e escolha 4 para tentar acertar a frase correta:\n");
                scanf("%i", &escolha);

                if(escolha == 0 && topo >= 0){ //caso queira voltar para a sala anterior
                    sala_atual = pilha[topo--];
                } else if (escolha == 1) { //caso queira ir para a esquerda
                    pilha[++topo] = sala_anterior;
                    sala_atual = sala_atual->esquerda;
                } else if (escolha == 2) { //caso queira ir para a direita
                    pilha[++topo] = sala_anterior;
                    sala_atual = sala_atual->direita;
                }else if(escolha == 3){ //caso queira sair do jogo
                    liberarArvore(sala_8);
                    exit(1);
                } else if (escolha == 4){ //caso queira acertar a frase

                    do
                    {
                        limpaTela();
                        getchar();
                        printf("Tente a certa a frase correta:\n");
                        fgets(frase, sizeof(frase), stdin);

                        if (frase[strlen(frase) - 1] == '\n') {
                            frase[strlen(frase) - 1] = '\0';
                        }

                        if(strcmp(frase, FraseCerta) == 0){
                            printf("Voce ganhou o jogo!\n");
                            escolha = -1;
                        } else {
                            printf("Voce quer tentar adivinhar novamente: ");
                            printf("\nDigite 1 para continuar e 0 para sair.\n");
                            scanf("%i", &escolha);
                        }
                    } while (escolha != -1);
                    
                } else {
                    limpaTela();
                    printf("Escolha invalida. Tente novamente.\n");
                }
            }while(escolha<0 || escolha>4);

        } else {
            printf("Voce chegou a ultima sala do labirinto.\nPressione 0 para voltar a sala anterior.\n");
            scanf("%i",&escolha);
            if(escolha == 0 && topo >= 0){
                sala_atual = pilha[topo--];
            }
        }
    }

    liberarArvore(sala_8);

    return 0;
}

