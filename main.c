#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SALAS 15
#define RESET      "\033[0m"
#define BOLD       "\033[1m"
#define UNDERLINE  "\033[4m"
#define ITALIC     "\033[3m"
#define STRIKETHROUGH "\033[9m"
#define INVERT     "\033[7m"
#define HIDDEN     "\033[8m"

// Cores do texto
#define RED        "\033[31m"
#define GREEN      "\033[32m"
#define YELLOW     "\033[33m"
#define BLUE       "\033[34m"
#define MAGENTA    "\033[35m"
#define CYAN       "\033[36m"
#define WHITE      "\033[97m" 
#define BROWN      "\x1b[38;2;165;42;42m"
#define EGYPT      "\x1b[38;5;178m"
// Cores de fundo
#define BG_RED        "\033[41;37m"
#define BG_GREEN      "\033[42;37m"
#define BG_YELLOW     "\033[43;37m"
#define BG_BLUE       "\033[44;37m"
#define BG_MAGENTA    "\033[45;37m"
#define BG_CYAN       "\033[46;37m"
int pontos=0;
//estrutura da sala
typedef struct Sala {
    int numero_sala;
    char descricao[100];
    char palavra[20];
    int enigma_resolvido;
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct Jogador {
    char nome[50];
    int pontuacao;
} Jogador;

char nomeDoJogador[50];
int tentativas;

void salvarPontuacao(char *nomeDoJogador, int pontos) {
    Jogador novato;
    novato.pontuacao = pontos;
    strcpy(novato.nome, nomeDoJogador);

    FILE *arquivo;

    arquivo = fopen("pontuacao.txt", "a+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Jogador jogadores[100];
    int numJogadores = 0;

    while (fscanf(arquivo, "%s %d", jogadores[numJogadores].nome, &jogadores[numJogadores].pontuacao) == 2) {
        numJogadores++;
    }

    // Verifica se o jogador já existe
    for (int i = 0; i < numJogadores; i++) {
        if (strcmp(jogadores[i].nome, novato.nome) == 0) {
            // O jogador já existe
            fclose(arquivo);
            return;
        }
    }

    int i = numJogadores - 1;
    while (i >= 0 && jogadores[i].pontuacao < novato.pontuacao) {
        jogadores[i + 1] = jogadores[i];
        i--;
    }
    jogadores[i + 1] = novato;

    fclose(arquivo);

    arquivo = fopen("pontuacao.txt", "w");

    for (int j = 0; j <= numJogadores; j++) {
        fprintf(arquivo, "%s %d\n", jogadores[j].nome, jogadores[j].pontuacao);
    }

    fclose(arquivo);
}
void imprimirpontuacao(){
    char nomeArquivo[] = "pontuacao.txt";
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        return; // Código de erro
    }

    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

//criar uma sala
void criarSala(Sala** sala, int numero_sala, const char descricao[], const char palavra[]) {
    *sala = (Sala*)malloc(sizeof(Sala));
    if (*sala == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    (*sala)->numero_sala = numero_sala;
    strcpy((*sala)->descricao, descricao);
    strcpy((*sala)->palavra, palavra);
    (*sala)->enigma_resolvido = 0;
    (*sala)->esquerda = NULL;
    (*sala)->direita = NULL;
}

//concectar as salas
void conectarSalas(Sala* de, Sala* sala_esquerda, Sala* sala_direita) {
    de->esquerda = sala_esquerda;
    de->direita = sala_direita;
}

void resetEnigmas(Sala* sala) { //para resetar os enigmas que já foram passados
    if (sala != NULL) {
        sala->enigma_resolvido = 0;
        resetEnigmas(sala->esquerda);
        resetEnigmas(sala->direita);
    }
}

void telaInicial(){
    printf(EGYPT" ___\n");
    printf(EGYPT"                    .\"///\".\n");
    printf(EGYPT"                   /|<> <>!\\\n");
    printf(EGYPT"                  /-|  ^  !-\\\n");
    printf(EGYPT"                 /-- \\_=_/ --\\\n");
    printf(EGYPT"                 )---| W |---(\n");
    printf(EGYPT"                /-\\--| W |--/-\\\n");
    printf(EGYPT"               (_-_--|_-_|--___)\n");
    printf(EGYPT"              (-___  -_-- _-- -_)\n");
    printf(EGYPT"             )-_ _--_ _ ___--__-_(\n");
    printf(EGYPT"            (___ --__  __ __--_ -_)\n");
    printf(EGYPT"           /-_  / __ -_ -__  --___ \\\n");
    printf(EGYPT"          _>/  -- /|___| _ \\ -_ ) _<_\n");
    printf(EGYPT"         /--  _ - _/ _ \\>\\ -  --__ - \\\n");
    printf(EGYPT"        ( / / /   > |~l \\   \\ \\ \\-_-_-)\n");
    printf(EGYPT"        | |-\' | |/  \"\"\"  \\| | __  |-_-|\n");
    printf(EGYPT"        L_|__|__|_/         |__|__|_|_)\n"RESET);
    printf(YELLOW"\t\tBOAS VINDAS AO ENIGMA DA ESFINGE!\n"RESET);
    printf(ITALIC UNDERLINE BOLD WHITE"Digite seu nome: "RESET);
    scanf("%s", nomeDoJogador);
    printf("Escolha a dificuldade:\n");
    printf("1 - Facil.\n");
    printf("2 - Medio.\n");
    printf("3 - Dificil.\n");
    printf("4 - Ver pontuacao.\n");
    printf("5 - Como jogar.\n");
    printf("6 - Sair\n");
}

void telaComoJogar(){
    printf(EGYPT"Este jogos consiste em um labirinto, onde os jogadores devem passar pelas salas e resolver enigmas, apos a resolucao dos enigmas o jogador recebera uma\npalavra que no final forma uma frase (O JOGO TEM 15 SALAS e 15 ENIGMAS), entao voce deve encontrar 15 palavras.\n");
    printf(EGYPT"Este jogo possui 3 niveis de dificuldade: facil, medio e dificil. E ele deve ser jogador individualmente.\n");
    printf(EGYPT"Apos a resolucao de uma enigma duas portas se abrem para voce seguir o seu caminho, a direita ou a esquerda, voce tambem pode voltar para a sala anterior, entao voce decide o caminho que quer seguir, mas.\n\nCUIDADO PARA NAO SE PERDER!!!\n\n");
    printf(EGYPT"Dica:\nPara ajudar com as palavras eh bom estar com papel e caneta na mão, pois VOCE VAI PRECISAR\n");
    printf("APROVEITE O JOGO!!\n");
    printf(YELLOW"\n\t\tBEM VINDO AO ENIGMA DA ESFINGE!\n\n");
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
    criarSala(&sala_8, 8, "Voce esta no comeco do labirinto. SALA 8", "levem");
    criarSala(&sala_5, 5, "SALA 5", "feliz");
    criarSala(&sala_2, 2, "SALA 2", "todos");
    criarSala(&sala_6, 6, "SALA 6", "verdade");
    criarSala(&sala_11, 11, "SALA 11", "faz");
    criarSala(&sala_14, 14, "SALA 14", "que");
    criarSala(&sala_10, 10, "SALA 10", "os");
    criarSala(&sala_1, 1, "Voce esta na ultima sala do labirinto. SALA1", "passos");
    criarSala(&sala_3, 3, "Voce esta na ultima sala do labirinto. SALA 3", "nos");
    criarSala(&sala_4, 4, "Voce esta na ultima sala do labirinto. SALA 4", "para");
    criarSala(&sala_7, 7, "Voce esta na ultima sala do labirinto. SALA 7", "o");
    criarSala(&sala_9, 9, "Voce esta na ultima sala do labirinto. SALA 9", "nossos");
    criarSala(&sala_12, 12, "Voce esta na ultima sala do labirinto. SALA 12", "nos");
    criarSala(&sala_13, 13, "Voce esta na ultima sala do labirinto. SALA 13", "de");
    criarSala(&sala_15, 15, "Voce esta na ultima sala do labirinto. SALA 15", "que");

    //aqui ira conectar as salas
    conectarSalas(sala_8, sala_5, sala_11);
    conectarSalas(sala_5, sala_2, sala_6);
    conectarSalas(sala_11, sala_10, sala_14);
    conectarSalas(sala_2, sala_1, sala_3);
    conectarSalas(sala_6, sala_4, sala_7);
    conectarSalas(sala_10, sala_9, sala_12);
    conectarSalas(sala_14, sala_13, sala_15);

    int jogarNovamente = 1;
    while(jogarNovamente == 1){
        limpaTela();

        Sala* sala_atual = sala_8; //usar isso aqui para saber a posição do enigma

    

        int dificuldade = 0;


        do{
            limpaTela();
            telaInicial();
            scanf("%i",&dificuldade);
            if (dificuldade == 5){
                limpaTela();
                telaComoJogar();
                printf(EGYPT"Pressione ENTER para voltar...");
                scanf("%*c");
                getchar();
                dificuldade = 0;
                limpaTela();
            }
            if (dificuldade == 6){
                liberarArvore(sala_8);
                exit(1);
            } else if (dificuldade == 4){
                imprimirpontuacao();
                printf("Voce quer jogar o jogo novamente?\n");
                printf("1 - sim / 2 - nao\n");
                scanf("%i", &dificuldade);
                if (dificuldade == 2){
                    exit(1);
                } else {
                    dificuldade = 0;
                }
            }
        }while(dificuldade<1 || dificuldade>6);


        int topo = -1;

        //em cima está as perguntas faceis e em baixo estão as respostas
        char listaEnigmaFacil[15][300] = {"Sem asas, eu voo; sem olhos, eu choro. O que sou?", "Sou leve como uma pluma, mas nem o homem mais forte pode me segurar por muito tempo. O que sou?", "Se voce me tiver vai querer me dividir, se me dividir, deixarei de existir. O que sou? ", "Tenho chaves, mas nao abro portas. Tenho espaco, mas nao tenho quartos. O que sou?", "Se voce olhar para o meu rosto, nao encontrara treze em nenhum lugar. O que eu sou?", "Tenho rabo, mas nao sou cao Nao tenho asas, mas sei voar Se me largarem, nao subo, Mas saio ao vento a brincar. Quem sou eu?", "Pode ser atirado do alto de um predio e ficar super bem. Mas quando eh colocado na agua morre pouco tempo depois. O que sou?", "Fica cada vez mais molhado quanto mais a gente seca. O que sou?", "Voce tira a minha pele. Eu nao choro. Voce, sim. O que sou?", "Anda sobre quatro membros de manha, dois a tarde e tres a noite. O que sou?", "Quanto mais voce tira, mais eu cresco. O que sou?", "Nao eh vivo, mas cresce. Nao tem pulmoes, mas precisa de ar. Nao tem boca, mas a agua pode mata-lo. O que sou?", "Sou preto quando voce compra, vermelho quando voce usa e cinza quando voce joga fora. O que sou?", "Faco duas pessoas a partir de uma so. O que sou?", "Sou cheio de furinhos, mas ainda assim consigo segurar agua. O que sou?"};
        char listaRespostaFacil[15][35] = {"nuvem", "pum", "segredo", "teclado", "relogio", "pipa", "papel", "toalha", "cebola", "humano", "buraco", "fogo", "carvao", "espelho", "esponja"};

        //em cima está as perguntas medias e em baixo estão as respontas
        char listaEnigmaMedio[15][450] = {"O que um bom navegador faz quando o barco afunda?", "Como se chama a plantinha que nao enxerga nada?", "Qual a banda preferida dos mortos?", "Qual eh o animal que nao vale mais nada?", "Estou acima do rei. O que sou?", "O que e que e mais rapido do que qualquer pessoa, mas nao pode correr por muito tempo?", "O que e que e pequeno como um rato, mas pode levantar um elefante?", "O que e que e sempre quebrado antes de usarmos?", " O que e que e liquido quando o compra, solido quando o usa e se joga fora quando esta terminado?", "Sou forte, mas posso ser quebrado", "Eu faco a barba, diversas vezes por dia, e continuo barbudo. Quem sou eu?", "Eu sou algo que você pode sentir, mas nao pode ver.", "O que tem um corpo, mas nao tem pernas?", "Dois homens estao no deserto. Ambos estao com uma mochila nas costas. A mochila de um esta aberta e vazia.\n A mochila do outro esta fechada e guarda alguma coisa. Um dos homens esta morto.\n O que ha dentro da mochila fechada?", "Na cidade e uma profissao, na estrada e um perigo e na mata e um inseto."};
        char listaRespostaMedio[15][35] = {"nada", "acelga", "sepultura", "javali", "coroa", "pensamento", "balanca", "ovo", "sabonete", "promessa", "barbeiro", "temperatura", "cobra", "paraquedas", "barbeiro"};

        //em cima está as perguntas dificeis e em baixo estão as respostas
        char listaEnigmaDificil[15][450] = {"O que e algo que as pessoas tem, mas que nunca compartilham?", "Eu falo, mas nao tenho boca. Eu escuto, mas nao tenho ouvidos. Nao tenho corpo, mas vivo com o vento. Quem sou eu?", "Eu sou algo que as pessoas amam ou odeiam. Eu mudo tanto a aparencia das pessoas quanto seus pensamentos.\n Se uma pessoa cuida de si mesma, eu subo ainda mais. Eu engano algumas pessoas. E para outras, sou um verdadeiro misterio.\n Algumas pessoas bem que tentam me esconder, mas uma hora, inevitavelmente, eu apareco.\n Nao importa o que as pessoas tentem, eu jamais cairei. Quem sou eu?", "Quando precisa de mim, voce me atira para longe, ate um lugar onde ninguem pode me ver. Mas quando ja nao precisa mais, você me traz de volta. Quem sou eu?", "Ponha os dedos nos meus olhos que eu abrirei as minhas potentes mandibulas.\n E vou devorar tudo o que vier pela frente: roupas, penas, papeis. Quem sou eu?", "Tenho cidades, mas não tenho casas. Tenho montanhas, mas não tenho árvores. O que sou?", "Voce mede a minha vida em horas e eu te sirvo indo embora. Sou rapida quanto estou magra e devagar quando estou gorda. O vento e o meu maior inimigo. Quem sou eu?", "A mae de Mary teve quatro filhos. Abril, Maio e Junho foram os tres primeiros. Qual o nome da quarta crianca?", "O que pode correr, mas nunca anda; tem leito, mas nunca dorme; nasce, mas nao morre?", "Meu trovao vem antes do relampago, meu raio vem antes das nuvens e minha chuva seca toda terra em que toca. Quem eu sou?", "Posso ser aberto ou fechado, grande ou pequeno. Posso revelar a verdade ou esconde-la. \nQuase sempre sou bem-vindo e posso surgir sem avisar. \nTodo mundo tem, mas nem todos compartilham. Que eu sou?", "O que e sempre velho e algumas vezes novo; nunca chora e sempre murmura; nunca corre, mas anda devagar?", "O que e sempre verde e nunca cresce?", "Sou liquido, mas posso queimar. Em um recipiente, me contenho, mas em liberdade, me transformo em danca. O que sou?", "Sou a ponte entre a terra e o ceu, mas nunca me movo. O que sou?"};
        char listaRespostaDificil[15][35] = {"segredo", "eco", "idade", "ancora", "tesoura", "mapa", "vela", "mary", "rio", "vulcao", "sorriso", "livro", "cor", "gas", "horizonte"};

        char frase[150];
        char FraseCerta[] = "que todos os nossos passos nos levem para o que nos faz feliz de verdade";  


        char palavra[20];

        int escolha;
        while (sala_atual != NULL) {
            limpaTela();
            printf("Sala %i: %s\n", sala_atual->numero_sala, sala_atual->descricao);


            if (!sala_atual->enigma_resolvido){
                if (dificuldade == 1){ //se o jogo for na dificuldade facil
                    do{
                        printf("%s\n",listaEnigmaFacil[sala_atual->numero_sala-1]);
                        scanf("%s", palavra);

                        if(strcmp(palavra, listaRespostaFacil[sala_atual->numero_sala-1]) != 0){ 
                            limpaTela(); //pra cada interação limpar a a tela
                            printf("Resposta Errada.\n");
                        }
                        else{
                            pontos+=1;
                            limpaTela();
                            printf("Palavra da sala:\n");
                            printf("%s\n",sala_atual->palavra);
                            printf("Digite ENTER para continuar...");
                            scanf("%*c");
                            getchar();
                        }

                    }while(strcmp(palavra, listaRespostaFacil[sala_atual->numero_sala-1]) != 0);

                } else if (dificuldade == 2){ //se o jogo for na dificuldade media
                    do{
                        printf("%s\n",listaEnigmaMedio[sala_atual->numero_sala-1]);
                        scanf("%s", palavra);

                        if(strcmp(palavra, listaRespostaMedio[sala_atual->numero_sala-1]) != 0){ 
                            limpaTela(); //pra cada interação limpar a a tela
                            printf("Resposta Errada.\n");
                        }
                        else{
                            pontos+=2;
                            limpaTela();
                            printf("Palavra da sala:\n");
                            printf("%s\n",sala_atual->palavra);
                            printf("Digite ENTER para continuar...");
                            scanf("%*c");
                            getchar();
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
                        else{
                            pontos+=3;
                            limpaTela();
                            printf("Palavra da sala:\n");
                            printf("%s\n",sala_atual->palavra);
                            printf("Digite ENTER para continuar...");
                            scanf("%*c");
                            getchar();
                        }

                    }while(strcmp(palavra, listaRespostaDificil[sala_atual->numero_sala-1]) != 0);
                }
            
            sala_atual->enigma_resolvido = 1;
            limpaTela();

            } else {
                printf("Voce ja resolver esse enigma desta sala. Escolha para onde ir.\n");
            }


            //limpaTela();

            if (sala_atual->esquerda != NULL || sala_atual->direita != NULL) {


                sala_anterior = sala_atual;

                do{
                    printf("0 - para ir pra sala anterior.\n1 - para a sala a esquerda.\n2 - para a sala a direita.\n3 - para sair do jogo.\n4 - para tentar acertar a frase correta.\n");
                    scanf("%i", &escolha);

                    if(escolha == 0 && topo >= 0){ //caso queira voltar para a sala anterior
                        sala_atual = pilha[topo--];
                    } else if (escolha == 1) { //caso queira ir para a esquerda
                        pilha[++topo] = sala_anterior;
                        sala_atual = sala_atual->esquerda;
                    } else if (escolha == 2) { //caso queira ir para a direita
                        pilha[++topo] = sala_anterior;
                        sala_atual = sala_atual->direita;
                    }else if(escolha == 3){
                        //aqui tem que voltar para o inicio do jogo, na tela inicial
                        exit(1);
                        liberarArvore(sala_8);
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
                                pontos+=10;
                                printf(HIDDEN BG_RED "        " BG_YELLOW "        " BG_GREEN "        " BG_BLUE "     " RESET BG_BLUE BOLD "Voce ganhou o jogo!" HIDDEN "      " BG_GREEN "        " BG_YELLOW "        " BG_RED "        " RESET "\n\n");
                                printf("A quantidade de pontos que voce conseguiu foi: %d\n",pontos);
                                escolha = 0;
                                printf("\tTOP JOGADORES:\n");
                                salvarPontuacao(nomeDoJogador,pontos);
                                imprimirpontuacao();
                                //quando ganhar o jogo tem que ir para a tela inicial
                                printf("Voce quer jogar o jogo novamente?\n");
                                printf("1 - sim / 2 - nao\n");
                                scanf("%i", &jogarNovamente);
                                if(jogarNovamente==1){
                                    pontos=0;
                                }

                                sala_atual = NULL;
                            } else {
                                pontos=pontos-3;
                                if(pontos<0){
                                    pontos=0;
                                }
                                printf("Voce quer tentar adivinhar novamente: ");
                                printf("\nDigite 1 para continuar e 0 para sair.\n");
                                scanf("%i", &escolha);

                            }
                        } while (escolha != 0);
                        
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

        resetEnigmas(sala_8);
    }

    printf("Saindo!!");

    liberarArvore(sala_8);

    return 0;
}

