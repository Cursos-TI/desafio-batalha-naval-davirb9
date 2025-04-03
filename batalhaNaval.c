#include <stdio.h>
#include<stdlib.h>

int main() {
    int tamanho = 10;
    int tabuleiro[10][10];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    int navio = 3;

    // --- Posicionamento dos navios ---
    int linhaHorizontal = 2, colunaHorizontal = 4;
    int linhaVertical = 5, colunaVertical = 1;
    int linhaDiag1 = 0, colunaDiag1 = 0;
    int linhaDiag2 = 0, colunaDiag2 = 9;

    int podeColocar = 1;

    // Horizontal
    if (colunaHorizontal + navio <= tamanho) {
        podeColocar = 1;
        for (int i = 0; i < navio; i++) {
            if (tabuleiro[linhaHorizontal][colunaHorizontal + i] != 0) {
                podeColocar = 0;
                break;
            }
        }
        if (podeColocar) {
            for (int i = 0; i < navio; i++) {
                tabuleiro[linhaHorizontal][colunaHorizontal + i] = 3;
            }
        }
    }

    // Vertical
    if (linhaVertical + navio <= tamanho) {
        podeColocar = 1;
        for (int i = 0; i < navio; i++) {
            if (tabuleiro[linhaVertical + i][colunaVertical] != 0) {
                podeColocar = 0;
                break;
            }
        }
        if (podeColocar) {
            for (int i = 0; i < navio; i++) {
                tabuleiro[linhaVertical + i][colunaVertical] = 3;
            }
        }
    }

    // Diagonal ↘
    if (linhaDiag1 + navio <= tamanho && colunaDiag1 + navio <= tamanho) {
        podeColocar = 1;
        for (int i = 0; i < navio; i++) {
            if (tabuleiro[linhaDiag1 + i][colunaDiag1 + i] != 0) {
                podeColocar = 0;
                break;
            }
        }
        if (podeColocar) {
            for (int i = 0; i < navio; i++) {
                tabuleiro[linhaDiag1 + i][colunaDiag1 + i] = 3;
            }
        }
    }

    // Diagonal ↙
    if (linhaDiag2 + navio <= tamanho && colunaDiag2 - (navio - 1) >= 0) {
        podeColocar = 1;
        for (int i = 0; i < navio; i++) {
            if (tabuleiro[linhaDiag2 + i][colunaDiag2 - i] != 0) {
                podeColocar = 0;
                break;
            }
        }
        if (podeColocar) {
            for (int i = 0; i < navio; i++) {
                tabuleiro[linhaDiag2 + i][colunaDiag2 - i] = 3;
            }
        }
    }

    // --- MATRIZES DE HABILIDADE (5x5) ---
    int habilidade[5][5];

    // -- Habilidade Cone --
    // Origem do cone no tabuleiro (linha, coluna)
    int origemConeLinha = 6;
    int origemConeColuna = 5;

    // Gera matriz em forma de cone (ponta no topo)
    for (int i = 0; i < 5; i++) { // linhas
        for (int j = 0; j < 5; j++) { // colunas
            if (j >= 2 - i && j <= 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }

    // Aplica matriz cone no tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha = origemConeLinha + i - 2;
            int coluna = origemConeColuna + j - 2;

            if (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }

    // -- Habilidade Cruz --
    int origemCruzLinha = 3;
    int origemCruzColuna = 3;

    // Gera matriz em forma de cruz
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }

    // Aplica cruz no tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha = origemCruzLinha + i - 2;
            int coluna = origemCruzColuna + j - 2;

            if (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }

    // -- Habilidade Octaedro (Losango) --
    int origemOctLinha = 8;
    int origemOctColuna = 8;

    // Gera losango (vista frontal de um octaedro)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }

    // Aplica octaedro no tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha = origemOctLinha + i - 2;
            int coluna = origemOctColuna + j - 2;

            if (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }

    // --- IMPRESSÃO DO TABULEIRO ---
    printf("   ");
    for (char letra = 'A'; letra <= 'J'; letra++) {
        printf("%c ", letra);
    }
    printf("\n");

    for (int i = 0; i < tamanho; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ ");
            } else if (tabuleiro[i][j] == 3) {
                printf("N ");
            } else if (tabuleiro[i][j] == 5) {
                printf("* ");
            }
        }
        printf("\n");
    }

    return 0;
}
