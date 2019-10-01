//
// Created by pacm1 on 28/11/2018.
//

#ifndef PROJETOLP_AED_FASE2_H
#define PROJETOLP_AED_FASE2_H
#define FILENAME "C:\\Users\\pacm1\\CLionProjects\\ProjetoLP_AED\\data\\Jogo.txt"
#define FILENAMEBIN "C:\\Users\\pacm1\\CLionProjects\\ProjetoLP_AED\\data\\JogoBin.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cache{
    char *palavra;
    int xi, xf, yi, yf;
    char **direcoes;
    int size_direcoes;
    struct cache *next;
}CACHE;

typedef struct palavras{
    char *palavra;
    struct palavras *next;
}PALAVRAS;

typedef struct celula{
    char caracter;
    struct celula *N;
    struct celula *NE;
    struct celula *E;
    struct celula *SE;
    struct celula *S;
    struct celula *SO;
    struct celula *O;
    struct celula *NO;
    CACHE *cache_celula;
}CELULA;

void functionPalavra_fase2();
void functionMatrix2(PALAVRAS *p);
PALAVRAS * ler_txt();
PALAVRAS * ler_manual();
void showlist(PALAVRAS *L);
CELULA */* * */ ler_matriz(char **matrix, int lines, int cols);
char ** create_matrix2(int l, int c);
int check_consistency2(int i, int j, int l, int c);
CELULA ** create_matrix_aux(int l, int c);
void pesquisa2(PALAVRAS *head, CELULA *first);
char ** create_arraypalavras2(int n);
void pesquisa_palavra2(char *p, int i, int j, CELULA *linha, int *carater, char **direcoes, int *posicoes);
void print_array2(char **array, int size);
void imprimir_caraters_por_direcoes(CELULA *pfirst);
void insert_cache_ordered(CELULA *pc, char *p, char **direcoes, int *posicoes, int size);
char ** alocar_memoria_direcoes(int size);
void print_lists(CELULA *c, int lines, int cols);
void MergeSort(PALAVRAS** list);
PALAVRAS* Merge(PALAVRAS *a, PALAVRAS *b);
void FrontBackSplit(PALAVRAS* source, PALAVRAS** frontRef, PALAVRAS** backRef);
void save_game(CELULA *first, PALAVRAS *p, char *fn);
void save_direcoes(char *p, char **direcoes, int *posicoes, int size, char *fn);
void save_game_bin(CELULA *first, PALAVRAS *p, char *fn);
void save_direcoes_bin(char *p, char **direcoes, int *posicoes, int size, char *fn);

int main_fase2(int argc, const char*argv[]);

#endif //PROJETOLP_AED_FASE2_H
