//
// Created by pacm1 on 30/10/2018.
//

#ifndef PROJETOLP_AED_FASE1_H
#define PROJETOLP_AED_FASE1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
#include <time.h>
#include <windef.h>
#include "../libs_src/strings/stringsorting.h"

void functionPalavra();
void functionMatrix(char *palavras[], int quantidadepalavras);
void pesquisa(char *p[], int quantidadepalavras, char **matrix, int l, int c);
void pesquisa_palavra(char *p, int j, int k, char **matrix, int l, int c, int *carater, char **direcoes, int *posicoes);
int check_consistency(char **matrix, int j, int k, int l, int c, char p);
void msd(int numb, char * p[]);
char random_char();
void print_matrix(char **matrix, int l, int c);
void print_array(char **array, int size);
char**read_dynarray_strings(char **str, int size);
char *create_copy_string(char *str);
char ** create_arraypalavras(int n);
char ** create_matrix(int l, int c);

int main_fase1(int argc, const char*argv[]);

#endif //PROJETOLP_AED_FASE1_H
