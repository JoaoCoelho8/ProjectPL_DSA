//
// Created by pacm1 on 30/10/2018.
//

#include "fase1.h"

int main_fase1(int argc, const char*argv[])
{
    functionPalavra();
    return 0;
}

/**
 * Requisito 1
 * função inicial que cria o array de palavras. Este poderá ser criado através do input (manualmente) ou através da leitura de um txt guardado pelo utilizador
 * possui um menu para que o utilizador escolha entre as duas opções referidas acima
 */
void functionPalavra()
{
    char option='\0';
    int number=0;
    int i;
    FILE *fp;

    while (option !='c'){

        /**< Inicio do menu1 */
        printf(" _____________________________________________________________________________\n");
        printf("|                            **Sopa de Letras**                               |\n");
        printf("|   **Vamos introduzir as palavras!                                           |\n");
        printf("|   **clique (a) para introduzir as palavras a procurar manualmente    **     |\n");
        printf("|   **clique (b) para introduzir as palavras a procurar atraves de txt **     |\n");
        printf("|   **Clique (c) para sair do programa                                 **     |\n");
        printf("|_____________________________________________________________________________|\n");
        scanf(" %c", &option);
        option = tolower(option);
        switch(option) {
            //Requisito1.a
            case 'a':
            {
                printf(" _________________________________________________\n");
                printf("|Insira o numero de palavras que pretende inserir |\n");
                printf("|_________________________________________________|\n");
                scanf("%d",&number);
                int numb= number;
                char ** palavras= create_arraypalavras(numb);
                fflush(stdin); //limpar o buffer
                read_dynarray_strings(palavras, numb);
                msd(numb, palavras); //Requisito2
                functionMatrix(palavras, numb);
                break;
            }
                //Requisito1.b
            case 'b':
            {
                fp= fopen("../data/palavras.txt","r");
                if(fp!=NULL)
                {
                    printf(" ________________________________\n");
                    printf("|Introduza o numero de palavras: |\n");
                    printf("|________________________________|\n");
                    scanf("%d",&number);
                    int numb= number;
                    char palavra[100];
                    char ** palavras= create_arraypalavras(numb);
                    system("cls");
                    for(i=0; i<numb; i++)
                    {
                        fscanf(fp, "%s\n", palavra);
                        *(palavras+i)=create_copy_string(palavra);
                    }
                    fclose(fp);
                    msd(numb, palavras); //Requisito2
                    functionMatrix(palavras, numb);
                } else{
                    printf("Ficheiro nao encontrado\n");
                    break;
                }
                break;
            }

            case 'c':
            {
                printf("****Bye Bye****\n");
                exit(0);
            }

            default:
            {
                printf(" __________________________\n");
                printf("|Letra ou caracter invalido|\n");
                printf("|__________________________|\n");
                system("pause");
                system("cls");
                functionPalavra();
                break;
            }
        }
    }

}

/**
 * Requisito 3
 * @param palavras (array das palavras [não utilizado mas necessário para posteriormente enviar para a função da pesquisa)
 * @param quantidadepalavras (quantidade de palavras no array acima)
 * função que cria a matriz, ou aleatoriamente ou através da leitura de um ficheiro txt guardado pelo utilizador
 * possui um menu para que o utilizador escolha entre as duas opções referidas acima
 */
void functionMatrix(char *palavras[], int quantidadepalavras)
{
    char option='\0';
    int lines=0, cols=0;
    int i,j;
    FILE *fp;
    while (option!='c') {
        /**< Inicio do menu2 */
        printf(" _____________________________________________________________________________\n");
        printf("|                            **Sopa de Letras**                               |\n");
        printf("|   **Vamos introduzir a matriz!                                              |\n");
        printf("|   **clique (a) para introduzir a matriz aleatoriamente               **     |\n");
        printf("|   **clique (b) para introduzir a matriz atraves de txt               **     |\n");
        printf("|   **Clique (c) para voltar ao inicio                                 **     |\n");
        printf("|_____________________________________________________________________________|\n");
        scanf(" %c", &option);
        option = tolower(option);
        switch(option) {
            //Requisito3.a
            case 'a':
            {
                printf(" _________________________________________________\n");
                printf("|           Insira a dimensao da matriz (CxL)     |\n");
                printf("|_________________________________________________|\n");
                scanf("%d %d",&cols, &lines);
                char **matrix= create_matrix(lines, cols);
                for(i=0; i<lines; i++)
                {
                    for(j=0; j< cols; j++)
                    {
                        *(*(matrix+i)+j) = random_char();
                    }
                }
                print_matrix(matrix, lines, cols);
                pesquisa(palavras, quantidadepalavras, matrix, lines, cols);
                functionPalavra();
                break;
            }
                //Requisito3.b
            case 'b':
            {
                fp= fopen("../data/matriz.txt","r");
                if(fp!=NULL)
                {
                    fscanf(fp, "%d %d", &cols, &lines);
                    printf(" ______________________________________\n");
                    printf("|        Dimensao da matriz %dx%d:      |\n", cols, lines);
                    printf("|______________________________________|\n");
                    char **matrix= create_matrix(lines, cols);
                    for(i=0; i<lines; i++)
                    {
                        for(j=0; j<cols; j++)
                        {
                            fscanf(fp, " %c", &(*(*(matrix+i)+j)));
                        }
                    }
                    fclose(fp);
                    print_matrix(matrix, lines, cols);
                    pesquisa(palavras, quantidadepalavras, matrix, lines, cols);
                    functionPalavra();
                } else{
                    printf("Ficheiro nao encontrado\n");
                }
                break;
            }

            case 'c':
            {
                functionPalavra();
                break;
            }

            default:
            {
                printf(" __________________________\n");
                printf("|Letra ou caracter invalido|\n");
                printf("|__________________________|\n");
                system("pause");
                system("cls");
                functionPalavra();
                break;
            }
        }
    }
}

/**
 * Requisito 4
 * @param p (array das palavras a pesquisar)
 * @param quantidadepalavras (quantidade das palavras a pesquisar)
 * @param matrix
 * @param l (número de linhas da matriz)
 * @param c (númedo de colunas da matriz)
 * função que usa um ciclo for para cada palavra e para cada palavra criará um array para as posições e para as direções. Posteriormente usa 2 ciclos for para percorrer a matriz até encontrar um caracter que seja igua ao primeiro caracter da palavra a pesquisar
 * faz free do array das direções, array das palavras e da matriz
 */
void pesquisa(char *p[], int quantidadepalavras, char **matrix, int l, int c)
{
    //for para cada palavra(até quantidadepalavras)
    for(int i=0; i<quantidadepalavras; i++)
    {
        int tamanho_palavra= strlen(p[i])-1;
        char **direcoes=create_arraypalavras(tamanho_palavra); //criar "array de strings" com tamanho da palavra-1 (ex: OLA - 3letras e 2direcoes(de O para L e de L para A)
        int posicoes[4]; //array para as 4 posições(2 para x e y inicial e +2 para x e y finais)
        int *pposicoes= posicoes;
        //2 ciclos for para percorrer matrix até encontrar primeira letra da iézima palavra
        for (int j=0; j<l; j++)
        {
            for (int k=0; k<c; k++)
            {
                int m=0;
                int *pm=&m; //apontador para variavel que será incrementada na função recursiva

                if(*(*(matrix+j)+k)==*(*(p+i)))
                {
                    //quando encontrar, chamar função que vai ser recursiva para encontrar as restantes letras na matriz (dentro chamar outra função que testa se a posição, que vamos procurar a seguir, é valida)
                    *(posicoes+0)=k;
                    *(posicoes+1)=j;
                    pesquisa_palavra(p[i], j, k, matrix, l, c, pm, direcoes, pposicoes);
                }
            }
        }
        //free das direcoes
        free(direcoes);
    }
    //free da matriz e das palavras
    free(p);
    free(matrix);
}

/**
 * Requisito 4
 * @param p (palavra a procurar)
 * @param j (posição da linha da matriz em que se encontra a letra inicial desta palavra)
 * @param k (posição da coluna da matriz em que se encontra a letra inicial desta palavra)
 * @param matrix
 * @param l (número de linhas da matriz)
 * @param c (número de colunas da matriz)
 * @param carater (contador usado para saber que caracter da palavra estamos a testar)
 * @param direcoes (array das direções em que serão introduzidas as direções da palavra na matriz)
 * @param posicoes (array de posições de tamanho 4 [para x e y inicial e x e y final])
 * função recursiva que testará se a posição seguinte na matriz (norte, nordeste, este, sudeste, sul, sudoeste, oeste, noroeste) é igual ao caracter da palavra que estamos a testar e se for guardará no array das direções a direção seguida para avançar para esse caracter da matriz
 * a condição de paragem será quando a palavra acabar (quando o caracter for \0) e quando entrar na condição de paragem, serão guardadas as posições finais e imprimidas estas e as direções
 */
void pesquisa_palavra(char *p, int j, int k, char **matrix, int l, int c, int *carater, char **direcoes, int *posicoes)
{
    (*carater)++;
    if(*(p+*carater)=='\0') {
        *(posicoes+2)=k;
        *(posicoes+3)=j;
        printf("\n%s: [%d,%d]->[%d,%d] - ", p, *posicoes, *(posicoes+1), *(posicoes+2), *(posicoes+3));
        print_array(direcoes, *carater);
        printf("\n");
    }
    else{
        //N
        if(check_consistency(matrix, j-1, k, l, c, *(p+*carater)))
        {
            char *str= "N";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j-1, k, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
        //NE
        if(check_consistency(matrix, j-1, k+1, l, c, *(p+*carater)))
        {
            char *str= "NE";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j-1, k+1, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
        //E
        if(check_consistency(matrix, j, k+1, l, c, *(p+*carater)))
        {
            char *str= "E";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j, k+1, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
        //SE
        if(check_consistency(matrix, j+1, k+1, l, c, *(p+*carater)))
        {
            char *str= "SE";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j+1, k+1, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
        //S
        if(check_consistency(matrix, j+1, k, l, c, *(p+*carater)))
        {
            char *str= "S";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j+1, k, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
        //SO
        if(check_consistency(matrix, j+1, k-1, l, c, *(p+*carater)))
        {
            char *str= "SO";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j+1, k-1, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
        //O
        if(check_consistency(matrix, j, k-1, l, c, *(p+*carater)))
        {
            char *str= "O";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j, k-1, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
        //NO
        if(check_consistency(matrix, j-1, k-1, l, c, *(p+*carater)))
        {
            char *str= "NO";
            *(direcoes+((*carater)-1))= (char*)malloc((strlen(str)+1)* sizeof(char));
            *(direcoes+((*carater)-1))= str;
            pesquisa_palavra(p, j-1, k-1, matrix, l, c, carater, direcoes, posicoes);
            free(*(direcoes+((*carater)-1)));
            (*carater)--;
        }
    }
}

/**
 * Requisito 4
 * @param matrix
 * @param j (posição da linha da matriz do caracter que está a ser testado)
 * @param k (posição da coluna da matriz do caracter que está a ser testado)
 * @param l (número de linhas da matriz)
 * @param c (número de colunas da matriz)
 * @param p (caracter que ira ser comparado com o caracter da matriz no posição [j,k])
 * @return
 * função que testa se a posição da matriz, recebida através de j e k, é uma posição da matriz (se é maior que 0 e menor que o número de linhas e de colunas) e posteriormente testa se o caracter da matriz, na posição [j,k], é igual ao caracter tambem recebido (p)
 */
int check_consistency(char **matrix, int j, int k, int l, int c, char p)
{
    if(j>=0 && j<l && k>=0 && k<c)  //verifica se as posições a testar estão "dentro" da matriz
    {
        if(*(*(matrix+j)+k)== p) // se o carater da matriz for igual à letra da palavra
        {
            return 1;
        }

    }
    return 0;
}

/**
 * @param numb (número de palavras)
 * @param p ("array das palavras" a ordenar)
 * função que faz a ordenação MSD de um conjunto de palavras
 */
void msd(int numb, char * p[])
{
    StringElementsArray a, aux;
    createStringElementsArrayAndFill(&a, numb, p);
    createStringElementsArray(&aux, numb);
    msd_sort_whithout_cutoff(&a, &aux, 0, (numb-1), 0, CHAR_8BIT_RADIX);
    printStringElementsArrayProjeto(&a);
    for(int i=0; i<numb; i++)
    {
        *(p+i)=a.str[i];
    }
}

/**
 * @return
 * função que cria um caracter aleatório que será introduzido numa posição da matriz
 */
char random_char()
{
    static const char ucase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t ucase_count = sizeof(ucase) - 1;
    char random_char;
    int random_index = rand() % ucase_count;
    random_char = ucase[random_index];
    return random_char;
}

/**
 * @param matrix
 * @param l (número de linhas da matriz)
 * @param c (número de colunas da matriz)
 * função que imprime a matriz (linhas * colunas)
 */
void print_matrix(char **matrix, int l, int c)
{
    for (int i=0; i<l; i++)
    {
        for(int j=0; j<c; j++)
        {
            printf("%c\t", *(*(matrix+i)+j));
        }
        printf("\n");
    }
}

/**
 * @param array ("matriz de direções" de uma palavra onde cada posição tem uma direção)
 * @param size (número de letras da palavra -1)
 * função que imprime as direções
 */
void print_array(char **array, int size)
{
    for(int i = 0; i < size-1; i++)
    {
        printf("[%s]", *(array+i));
    }
}

/**
 * @param str (apontador de apontador para as palavras)
 * @param size (número de palavras)
 * @return
 * função que lê a palavra e guarda a no "array de palavras"
 */
char**read_dynarray_strings(char **str, int size)
{
    char straux[100];
    for(int i=0; i<size; i++)
    {
        printf("Introduza a %da palavra (em maiusculas):",i+1);
        fgets(straux, sizeof(straux), stdin);
        *(str+i)=create_copy_string(straux);
    }
}

/**
 * @param str (string)
 * @return
 * função que aloca memória para uma palavra
 */
char *create_copy_string(char *str)
{
    char *pc= (char*)malloc((strlen(str)+1)* sizeof(char));
    str = strtok(str, "\n");
    strcpy(pc, str);
    return pc;
}

/**
 * @param n (tamanho [número de palavras])
 * @return
 * função que aloca memória para um "array de strings" que mais tarde, em cada posição, terão uma direção
 */
char ** create_arraypalavras(int n)
{
    char **paux=(char**)malloc(n* sizeof(char*));
    return paux;
}

/**
 * @param l (número de linhas da matriz)
 * @param c (número de colunas da matriz)
 * @return
 * função que aloca memória para uma "matriz"
 */
char ** create_matrix(int l, int c)
{
    char **pmatrix=(char**)malloc(l* sizeof(char*));
    for(int i=0; i<l; i++)
    {
        *(pmatrix+i)=(char*)malloc(c* sizeof(char));
    }
    return pmatrix;
}