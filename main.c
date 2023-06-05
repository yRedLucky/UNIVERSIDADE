#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <ncurses.h>
#include <math.h> // Incluído para a função sqrt

#define LarguraMapa 72
#define AlturaMapa 50
#define MaxQuartos 150
#define TamanhoMinQuarto 12
#define TamanhoMaxQuarto 25
#define MaxMonstros 30
#define VisaoMonstro 8

typedef struct {
    int x;
    int y;
    int saude;
    char weapon[20]; // Adicionada a variável para a arma atual do jogador
} Jogador;

typedef struct {
    int x;
    int y;
    int largura;
    int altura;
} Quarto;

typedef struct {
    int x;
    int y;
    int saude;
} Monstro;

char mapa[AlturaMapa][LarguraMapa];
Jogador jogador;
Quarto quartos[MaxQuartos];
Monstro monstros[MaxMonstros];
int numQuartos = 0;
int numMonstros = 0;
int numMortes = 0;
int numMonstrosMortos = 0;

void iniciarMapa() {
    for (int y = 0; y < AlturaMapa; y++) {
        for (int x = 0; x < LarguraMapa; x++) {
            mapa[y][x] = ' ';
        }
    }
    // Preencher as paredes horizontais 
    for (int x = 0; x < LarguraMapa; x++) {
        mapa[0][x] = '#';
        mapa[AlturaMapa - 1][x] = '#';
    }

// Preencher as paredes verticais
    for (int y = 0; y < AlturaMapa; y++) {
        mapa[y][0] = '#';
        mapa[y][LarguraMapa - 1] = '#';
    }   

}

int verificarVisibilidade(int x1, int y1, int x2, int y2) { //determina se uma posição (x2, y2) é visível a partir de uma posição inicial (x1, y1) no mapa utilizando ray casting
    int dx = x2 - x1; //indica a quantidade de movimento necessária nas coordenadas x e y para chegar do ponto 1 ao ponto 2
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); ////número de etapas que serão necessárias para percorrer a distância total do ponto 1 ao ponto 2
    //abs - Retorna o valor absoluto da diferença entre as coordenadas dos pontos inicial e final.
    //abs(dx) > abs(dy): Compara as diferenças absolutas entre dx e dy. Se a diferença absoluta de dx for maior que a de dy, a expressão retorna verdadeiro (1), caso contrário, retorna falso (0)
    // "?" -  se for verdadeiro retorna abs(dx) se for falso retorna abs(dy)
    double xIncrement = dx / (double)steps; //calculam o incremento necessário em x e y a cada etapa para percorrer a distância entre os pontos
    double yIncrement = dy / (double)steps;
    double x = x1;
    double y = y1;

    for (int i = 0; i < steps; i++) {
        x += xIncrement; //a cada etapa adicionamos o valor de xIncrement e yIncrement à coordenada
        y += yIncrement;

        int mapX = (int)x; //convertem as coordenadas x e y em números inteiros para obter os índices corretos da matriz mapa
        int mapY = (int)y;

        if (mapa[mapY][mapX] == '#') {
            return 0; // Raio encontrou uma parede, posição não é visível
        }
    }

    return 1; // Raio atingiu a posição sem encontrar paredes, posição é visível
}

void imprimirMapa() {
    for (int y = 0; y < AlturaMapa; y++) { //percorre as coordenas do mapa
        for (int x = 0; x < LarguraMapa; x++) {
            int dx = x - jogador.x; //faz a diferença das coordenadas atuais com as do jogador
            int dy = y - jogador.y;
            double distancia = sqrt(dx * dx + dy * dy); //calcula a distância euclidiana (para determinar se a posição está dentro do campo de visão do jogador) entre a diferença feita em cima usando o teorema de Pitágoras (sqrt faz a raiz quadrada)

            if (distancia <= 7) { // Alterado o campo de visão para um círculo com raio 7
                if (x == jogador.x && y == jogador.y) { //verifica se a posição atual corresponde à posição do jogador. Se for o caso, o caractere '@' é exibido
                    printw("@ "); 
                } else {
                    int ehMonstro = 0;
                    for (int i = 0; i < numMonstros; i++) {  //Caso contrário, é verificado se a posição atual corresponde à posição de algum monstro
                        if (x == monstros[i].x && y == monstros[i].y) {
                            ehMonstro = 1;
                            break;
                        }
                    }
                    if (ehMonstro) {
                        printw("M ");
                    } else { //caso não seja de um jogador nem de um monstro
                        if (verificarVisibilidade(jogador.x, jogador.y, x, y)) { //verifica se a posição está dentro da visibilidade do jogador
                            printw("%c ", mapa[y][x]);
                        } else {
                            printw("# "); // Exibe uma parede se estiver fora da visibilidade
                        }
                    }
                }
            } else {
                printw("  "); // Espaço em branco para áreas fora do campo de visão
            }
        }
        printw("\n");
    }
    printw("Vida do jogador: %d\n", jogador.saude);
    printw("Arma atual: %s\n", jogador.weapon); // Exibe a arma atual do jogador
    printw("Número de Monstros mortos: %d / 5\n", numMonstrosMortos);
    refresh();
}

void criarQuarto(Quarto quarto) {  //é utilizada durante a geração do mapa para preencher os quartos com '.' antes de criar túneis e conexões entre eles
    for (int y = quarto.y + 1; y < quarto.y + quarto.altura - 1; y++) { //percorre todas as coordenadas dentro dos limites do quarto, excluindo as bordas
       for (int x = quarto.x + 1; x < quarto.x + quarto.largura - 1; x++) {
        mapa[y][x] = '.'; //cada coordenada do quarto é preenchida com o caractere '.'
       }
    } 
}

void criarTunelHorizontal(int x1, int x2, int y) {
    int salaAdjacente = 0;
    for (int x = x1; x <= x2; x++) { //verifica se já existe uma sala adjacente ao túnel sendo criado
        if (mapa[y][x] == '.') //se em algum ponto do percurso, o caractere correspondente na posição [y][x] do mapa for igual a '.', significa que já existe uma sala adjacente ao túnel
            salaAdjacente = 1;
        mapa[y][x] = '.';
        mapa[y+1][x] = '.';
    }
    if (!salaAdjacente) {
        int x = (x1 + x2) / 2; //se não houver uma sala adjacente ao túnel, é criado um ponto intermediário no meio do túnel para garantir a conectividade do mapa
        mapa[y][x] = '.';
        mapa[y+1][x] = '.';
    }
}

void criarTunelVertical(int y1, int y2, int x) {
    int salaAdjacente = 0;
    for (int y = y1; y <= y2; y++) { //verifica se já existe uma sala adjacente ao túnel sendo criado
        if (mapa[y][x] == '.') //se em algum ponto do percurso, o caractere correspondente na posição [y][x] do mapa for igual a '.', significa que já existe uma sala adjacente ao túnel
            salaAdjacente = 1;
        mapa[y][x] = '.';
        mapa[y][x+1] = '.';
    }
    if (!salaAdjacente) {
        int y = (y1 + y2) / 2; //se não houver uma sala adjacente ao túnel, é criado um ponto intermediário no meio do túnel para garantir a conectividade do mapa
        mapa[y][x] = '.';
        mapa[y][x+1] = '.';
    }
}

void gerarMapa() {
    iniciarMapa();

    srand(time(NULL)); //garante que cada vez que o programa for executado, a sequência de números aleatórios gerada pela função "rand" seja diferente, uma vez que o valor do tempo está em constante mudança.

    int i, larguraQuarto, alturaQuarto, x, y;
    for (i = 0; i < MaxQuartos; i++) { //// Loop para gerar quartos
    // Gerar largura e altura do quarto aleatoriamente dentro de um intervalo específico
        larguraQuarto = rand() % (TamanhoMaxQuarto - TamanhoMinQuarto + 1) + TamanhoMinQuarto;
        alturaQuarto = rand() % (TamanhoMaxQuarto - TamanhoMinQuarto + 1) + TamanhoMinQuarto;
    // Gerar coordenadas (x, y) aleatoriamente dentro do mapa, respeitando as restrições
        x = rand() % (LarguraMapa - larguraQuarto - 1) + 1;
        y = rand() % (AlturaMapa - alturaQuarto - 1) + 1;

        Quarto novoQuarto = { x, y, larguraQuarto, alturaQuarto };

        int falhou = 0;
        for (int j = 0; j < numQuartos; j++) { // Verifica se o novo quarto se sobrepõe a algum quarto existente
            if (novoQuarto.x < quartos[j].x + quartos[j].largura &&
                novoQuarto.x + novoQuarto.largura > quartos[j].x &&
                novoQuarto.y < quartos[j].y + quartos[j].altura &&
                novoQuarto.y + novoQuarto.altura > quartos[j].y) {
                falhou = 1;
                break;
            }
        }

        if (!falhou) { //se nao se sobrepõe entao cria o quarto
            criarQuarto(novoQuarto);

            int xQuartoAnterior, yQuartoAnterior;
            if (numQuartos > 0) {  // Conectar o novo quarto ao quarto anterior (se houver)
                xQuartoAnterior = quartos[numQuartos - 1].x;
                yQuartoAnterior = quartos[numQuartos - 1].y;

                if (rand() % 2 == 0) {  // Escolher aleatoriamente se o túnel será horizontal ou vertical
                    criarTunelHorizontal(xQuartoAnterior, novoQuarto.x + novoQuarto.largura / 2, yQuartoAnterior + quartos[numQuartos - 1].altura / 2);
                    criarTunelVertical(yQuartoAnterior, novoQuarto.y + novoQuarto.altura / 2, novoQuarto.x + novoQuarto.largura / 2);
                } else {
                    criarTunelVertical(yQuartoAnterior, novoQuarto.y + novoQuarto.altura / 2, xQuartoAnterior + quartos[numQuartos - 1].largura / 2);
                    criarTunelHorizontal(xQuartoAnterior, novoQuarto.x + novoQuarto.largura / 2, novoQuarto.y + novoQuarto.altura / 2);
                }
            }

            quartos[numQuartos] = novoQuarto; // Adicionar o novo quarto à lista de quartos
            if (numQuartos > 0) {
                int quartoAnterior = rand() % numQuartos; // Conectar o novo quarto a um quarto anterior aleatoriamente (se houver)
                int xQuartoAnterior = quartos[quartoAnterior].x + quartos[quartoAnterior].largura / 2;
                int yQuartoAnterior = quartos[quartoAnterior].y + quartos[quartoAnterior].altura / 2;

                int xNovoQuarto = novoQuarto.x + novoQuarto.largura / 2;
                int yNovoQuarto = novoQuarto.y + novoQuarto.altura / 2;

                if (rand() % 2 == 0) {  // Escolher aleatoriamente se o túnel será horizontal ou vertical
                   criarTunelHorizontal(xQuartoAnterior, xNovoQuarto, yQuartoAnterior);
                   criarTunelVertical(yQuartoAnterior, yNovoQuarto, xNovoQuarto);
                } else {
                   criarTunelVertical(yQuartoAnterior, yNovoQuarto, xQuartoAnterior);
                   criarTunelHorizontal(xQuartoAnterior, xNovoQuarto, yNovoQuarto);
                }
            }

            numQuartos++;
        }
    }

// Preencher as paredes horizontais
    for (int x = 0; x < LarguraMapa; x++) {
        mapa[0][x] = '#';
        mapa[AlturaMapa - 1][x] = '#';
    }

// Preencher as paredes verticais
    for (int y = 0; y < AlturaMapa; y++) {
        mapa[y][0] = '#';
        mapa[y][LarguraMapa - 1] = '#';
    }
// Definir a posição inicial do jogador no centro do primeiro quarto
    jogador.x = quartos[0].x + quartos[0].largura / 2;
    jogador.y = quartos[0].y + quartos[0].altura / 2;
    jogador.saude = 100;
    strcpy(jogador.weapon, "Faca"); // Define a arma inicial do jogador como "Faca"
// Inicializar os monstros
    for (int i = 0; i < MaxMonstros; i++) {
        monstros[i].x = -1;
        monstros[i].y = -1;
        monstros[i].saude = 0;
    }
}

void preencherVazios() { //preenche os espaços vazios do mapa com o caractere '#'
    for (int y = 0; y < AlturaMapa; y++) {
        for (int x = 0; x < LarguraMapa; x++) {
            if (mapa[y][x] == ' ') {
                mapa[y][x] = '#';
            }
        }
    }
}

void adicionarMonstro(int x, int y) { //adiciona monstros no mapa
    Monstro novoMonstro = { x, y, 20 }; //Monstro com as coordenadas (x, y) fornecidas e uma saúde inicial de 20
    monstros[numMonstros] = novoMonstro;
    numMonstros++;
}

int posicaoValida(int x, int y) {
    if (x < 0 || x >= LarguraMapa || y < 0 || y >= AlturaMapa) {
        return 0; // Fora dos limites do mapa
    }

    if (mapa[y][x] == '.' || mapa[y][x] == '#') {
        return 1; // Posição válida em um quarto ou caverna
    }

    for (int i = 0; i < numMonstros; i++) {
        if (x == monstros[i].x && y == monstros[i].y) {
            return 0; // Há um monstro nessa posição
        }
    }

    return 0; // Não é uma posição válida
}

void colocarMonstros() {
    numMonstros = 0;
    memset(monstros, 0, sizeof(monstros)); //garante que a matriz monstros esteja vazia antes de adicionar novos monstros
    for (int i = 0; i < numQuartos; i++) {
        int numMonstrosNoQuarto = rand() % 3 + 1; //gera um número aleatório de monstros (entre 1 e 3) para serem colocados no quarto atual

        int x, y;
        for (int j = 0; j < numMonstrosNoQuarto; j++) {
            do { //gera coordenadas aleatórias (x, y) dentro do quarto atual e verifica se a posição gerada é válida
//"% (quartos[i].largura - 2)" garante que o valor gerado esteja dentro dos limites da largura do quarto, subtraindo 2 para excluir as bordas do quarto e "+ quartos[i].x + 1" adiciona a coordenada x inicial do quarto ao valor gerado e soma mais 1 para evitar que o valor seja zero
                x = rand() % (quartos[i].largura - 2) + quartos[i].x + 1;
                y = rand() % (quartos[i].altura - 2) + quartos[i].y + 1;
            } while (!posicaoValida(x, y)); // Verifica se a posição gerada é válida

            adicionarMonstro(x, y);

            if (numMonstros >= MaxMonstros) { // Adiciona apenas o número máximo de monstros ao mapa
                return;
            }
        }
    }
}

void moverJogador(int dx, int dy) {
    
    int novaX, novaY;
    novaX = jogador.x + dx;
    novaY = jogador.y + dy;

    if (novaX >= 0 && novaX < LarguraMapa && novaY >= 0 && novaY < AlturaMapa && mapa[novaY][novaX] == '.') { //verifica se o jogador esta nos limites do mapa e se esta num espaço vazio ".""
        jogador.x = novaX;
        jogador.y = novaY;

        for (int i = 0; i < numMonstros; i++) {
            if (monstros[i].x == jogador.x && monstros[i].y == jogador.y) {
                jogador.saude -= 10; // Reduz a vida do jogador ao ser atacado pelo monstro
                if (jogador.saude <= 0) {
                    numMortes++;
                    return;
                }
            }
        }
    }
}

void moverMonstros() { // atualiza a posição dos monstros no mapa e verifica se eles colidem com o jogador durante o movimento
    int i, dx, dy, novaX, novaY;
    for (i = 0; i < numMonstros; i++) {
        dx = jogador.x - monstros[i].x; //diferença das coordenadas entre o jogador e o monstro
        dy = jogador.y - monstros[i].y;
        double distancia = sqrt(dx * dx + dy * dy); //calcula a distância euclidiana entre o monstro e o jogador usando o teorema de Pitágoras (sqrt faz a raiz quadrada)

        if (distancia <= VisaoMonstro) {
            dx = (int)(round(dx / distancia)); //arredonda a divisão para o inteiro mais próximo usando a função "round" e dá uma direção de movimento unitário
            dy = (int)(round(dy / distancia));

            novaX = monstros[i].x + dx; //novas coordenadas x e y para onde o monstro se moverá
            novaY = monstros[i].y + dy;

            if (novaX >= 0 && novaX < LarguraMapa && novaY >= 0 && novaY < AlturaMapa && mapa[novaY][novaX] == '.') {
                // Verifica se a nova posição coincide com a posição atual do jogador
                if (novaX != jogador.x || novaY != jogador.y) {
                    monstros[i].x = novaX;
                    monstros[i].y = novaY;
                }

                if (monstros[i].x == jogador.x && monstros[i].y == jogador.y) {
                    jogador.saude -= 10;
                    if (jogador.saude <= 0) {
                        numMortes++;
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    initscr(); //inicializa o modo de tela da ncurses
    keypad(stdscr, TRUE); //permite que a janela stdscr processe códigos especiais de teclas, como setas
    curs_set(0); //tira o cursor do rato da tela
    noecho(); //desativa a exibição de caracteres digitados pelo usuário

    gerarMapa();
    colocarMonstros();
    preencherVazios();

    while (1) {
        clear();
        imprimirMapa();

        int key = getch();

        switch (key) {
            case '8':
            case KEY_UP: moverJogador(0, -1); break;
            case '2':
            case KEY_DOWN: moverJogador(0, 1); break;
            case '4':
            case KEY_LEFT: moverJogador(-1, 0); break;
            case '6':
            case KEY_RIGHT: moverJogador(1, 0); break;
            case KEY_A1: 
            case '7': moverJogador(-1, -1); break;
            case KEY_A3: 
            case '9': moverJogador(1, -1); break;
            case KEY_C1: 
            case '1': moverJogador(-1, 1); break;
            case KEY_C3: 
            case '3': moverJogador(1, +1); break;

            case 'q':
                endwin();
                return 0;

            case 'e':
                for (int i = 0; i < numMonstros; i++) {
                    if (abs(monstros[i].x - jogador.x) <= 1 && abs(monstros[i].y - jogador.y) <= 1) { //se a posição do monstro com o jogador e se tiver a 1 ou menos de distancia ele mata o monstro
                        monstros[i].saude -= 20; // Reduz a saúde do monstro ao atacá-lo
                        if (monstros[i].saude <= 0) {
                            for (int j = i; j < numMonstros - 1; j++) {
                                monstros[j] = monstros[j + 1];
                            }
                            numMonstros--;
                            numMonstrosMortos++;
                        }
                    }
                }
                break;

            default: break; // se pressionar uma tecla que não corresponda a nenhum dos casos anteriores, o programa simplesmente ignora essa entrada e continua no loop while
        }

        if (numMonstrosMortos == 5) {
            clear();
            printw("Parabéns! Você derrotou todos os monstros!\n");
            refresh(); //atualizar a tela
            getch(); //aguarda a entrada
            endwin(); // encerra o modo de janela do ncurses
            return 0;
        }

        moverMonstros();

        if (numMortes > 0) {
            clear();
            printw("Você foi morto por um monstro!\n");
            printw("Número de monstros mortos: %d\n", numMonstrosMortos);
            refresh();
            getch();
            endwin();
            return 0;
        }
    }
}