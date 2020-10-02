#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

char palavra[12];
char tentativa[12];
char pilha[10][12] = {"Ferrari", "Mercedes", "RedBull", "AlphaTauri", "RacingPoint", "AlfaRomeo", "Haas", "McLaren", "Renault", "Williams"};
char letrasInseridas[18] = {"-----------------"};
int TAM;
int errosTotal = 0;
int acertos = 0;

int geraSeed() { //Gera um número aleatório
    int num;
    srand(time(NULL));
    num = rand() % 10;
    return num;
}

void preparaTentativa() { //Define qual palavra da pilha será escolhida para o jogo
    int i, seed;

    seed = geraSeed();
    strcpy(palavra, pilha[seed]);
    TAM = strlen(palavra);
    strcpy(tentativa, palavra); //Copia a string "palavra" na string "tentativa" para encaixar o tamanho correto da palavra

    for (i = 0; i < strlen(tentativa); i++) {
        tentativa[i] = '-';
    }
}

void apresentacao() {
    printf("\nTema: Equipes da F1 2020");
    printf("\nA palavra possui %d letras\n", strlen(palavra));
}

char recebeLetra() { //Checa se a letra inserida é um caractere válido (alfabético)
    char letra;
    do {
        printf("\nInsira uma letra: ");
        fflush(stdin);
        letra = getchar();
        if (isalpha(letra) == 0) {
            printf("\nCaractere incorreto, tente novamente\n\n");
        }
    } while (isalpha(letra) == 0);
    return letra;
}

int checkLetraRepetida(char letra, int tentativa) {
    int i;
    if (tentativa == 0) {
        letrasInseridas[tentativa] = letra;
        return 0;
    }
    for (i = 0; i <= tentativa; i++) {
        if (tolower(letrasInseridas[i]) == tolower(letra)) {
            printf("A letra '%c' foi inserida anteriormente, tente novamente", letra);
            return 1;
        }
    }
    letrasInseridas[tentativa] = letra;
    return 0;
}

void printTentativa() {
    int i;
    printf("\nPalavra: %s\n", tentativa);
}

int checkTentativa(char letra) {
    int errosPalavra = 0, i;
    for (i = 0; i < TAM; i++) {
            if (tolower(letra) == tolower(palavra[i])) {
                acertos++;
                tentativa[i] = palavra[i];
            }
            else {
                errosPalavra++;
            }

        }
    if (errosPalavra == TAM) {
        errosTotal++;
        printf("\nLetra incorreta, restam %d erros.\n", 6 - errosTotal);
        printTentativa();
    }
    else {
        printf("\nLetra correta\n");
        printTentativa();
    }
    if (errosTotal == 6) {
        return 1;
    }
    if (acertos == TAM) {
        return 2;
    }
    return 3;
}

int main() {
    char letra;
    int i, j, check, checkTry;

    preparaTentativa();
    apresentacao();

    for (i = 0; i < TAM + 6; i++) {
        do {
            letra = recebeLetra();
            checkTry = checkLetraRepetida(letra, i);
        } while (checkTry != 0);
        check = checkTentativa(letra);
        if (check == 1) {
            printf("\nQue pena, voce perdeu!\n");
            printf("A palavra era %s.\n\n", palavra);
            return 0;
        }
        else {
            if (check == 2) {
                printf("\nParabens, voce ganhou!\n");
                return 0;
            }
        }
    }
    return 0;
}
