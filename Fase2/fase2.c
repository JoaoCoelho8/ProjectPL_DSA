//
// Created by pacm1 on 28/11/2018.
//

#include <ctype.h>
#include "fase2.h"

int main_fase2(int argc, const char*argv[])
{
    functionPalavra_fase2();
    return 0;
}

/**
 * Requisito 5
 * função inicial que cria a lista de palavras. Esta lista poderá ser criada através do input (manualmente) ou através da leitura de um txt guardado pelo utilizador
 * possui um menu para que o utilizador escolha entre as duas opções referidas acima
 */
void functionPalavra_fase2()
{
    char option='\0';
    PALAVRAS *p=NULL;



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
            case 'a':
            {
                p=ler_manual();
                MergeSort(&p);
                showlist(p);
                functionMatrix2(p);
                break;
            }

            case 'b':
            {
                p=ler_txt();
                MergeSort(&p);
                showlist(p);
                functionMatrix2(p);
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
                functionPalavra_fase2();
                break;
            }
        }
    }
}

/**
 * Requisito 5.a
 * função que lê as palavras introduzidas manualmente pelo utilizador, cria a estrutura e liga esta às restantes criando assim uma lista ligada
 * @return apontador para a primeira palavra
 */
PALAVRAS * ler_manual(){
    PALAVRAS *p=NULL, *aux=NULL;
    int number;
    printf(" _________________________________________________\n");
    printf("|Insira o numero de palavras que pretende inserir |\n");
    printf("|_________________________________________________|\n");
    scanf("%d", &number);
    char buff[50];
    char *palavra;
    for (int i = 0; i < number; i++)
    {
        printf("Introduza a %d palavra: ", i + 1);
        fflush(stdin); //limpar o buffer
        fgets(buff, 100, stdin);
        strtok(buff, "\n");
        int tamanho = strlen(buff) + 1;
        palavra = malloc(tamanho * sizeof(char));
        strcpy(palavra, buff);
        //adicionar_palavra(p, aux, palavra);
        if(p==NULL){
            //reservar memoria do tipo de estruct PALAVRA
            p=(PALAVRAS*)malloc (1*sizeof(PALAVRAS));
            //enviar palavra para o estrutua criada em memoria
            p->palavra=palavra;
            //declarar "a seta" da proxima estrutura a NULL (vazio)
            p->next=NULL;
            //a partir de agr o aux é a nossa lista (p -> cabeca da lista)
            aux=p;
        }
        else {
            aux->next=(PALAVRAS*)malloc (1*sizeof(PALAVRAS));
            aux=aux->next;
            aux->palavra=palavra;
            aux->next=NULL;
        }
    }
    return p;
}

/**
 * Requisito 5.b
 * função que lê as palavras introduzidas através pelo utilizador, cria a estrutura e liga esta às restantes criando assim uma lista ligada
 * @return apontador para a primeira palavra
 */
PALAVRAS * ler_txt(){
    PALAVRAS *p=NULL,*aux=NULL;
    FILE *f;
    char buff[50];
    char *palavra;
    //abrir o ficheiro de dados
    f=fopen("../data/palavras.txt","r");
    //verificar se o ficheiro existe
    if(f==NULL)
        printf("Ficheiro nao encontrado\n");

    while(fscanf (f, "%s", buff)!=EOF){
        int tamanho = strlen(buff) + 1;
        palavra = malloc(tamanho * sizeof(char));
        strcpy(palavra, buff);
        //adicionar_palavra(p, aux, palavra);
        //se a lista estiver vazia, inserimos na 1 posicao
        if(p==NULL){
            //reservar memoria do tipo de estruct PALAVRA
            p=(PALAVRAS*)malloc (1*sizeof(PALAVRAS));
            //enviar palavra para o estrutua criada em memoria
            p->palavra=palavra;
            //declarar "a seta" da proxima estrutura a NULL (vazio)
            p->next=NULL;
            //a partir de agr o aux é a nossa lista (p -> cabeca da lista)
            aux=p;
        }
        else {
            aux->next=(PALAVRAS*)malloc (1*sizeof(PALAVRAS));
            aux=aux->next;
            aux->palavra=palavra;
            aux->next=NULL;
        }
    }

    return p;
}

/**
 * função que imprime as palavras das listas ligadas
 * @param p (apontador para a primeira estrutura da lista ligada)
 */
void showlist(PALAVRAS *p){
    if(p==NULL){
        printf("A Lista esta vazia\n");
        return;
    }
    else {
        while(p!=NULL){
            printf("%s\n",p->palavra);
            p=p->next;
        }
    }
}

/**
 * Requisito 6
 * função que ordena as palavras alfabeticamente utilizando o mergeSort
 * @param list (apontador para a primeira palavra)
 */
void MergeSort(PALAVRAS** list)
{
    PALAVRAS* aux = *list;
    PALAVRAS* a;
    PALAVRAS* b;

    /* Base case -- length 0 or 1 */
    if ((aux == NULL) || (aux->next == NULL))
    {
        return;
    }

    /* Split aux into 'a' and 'b' sublists */
    FrontBackSplit(aux, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *list = Merge(a, b);
}

/**
 * função auxiliar do mergeSort
 * @param a
 * @param b
 * @return
 */
PALAVRAS* Merge(PALAVRAS *a, PALAVRAS *b)
{
    PALAVRAS* result = NULL;

    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    if (strcmp(a->palavra,b->palavra) < 0) {
        result = a;
        result->next = Merge(a->next, b);

    } else {
        result = b;
        result->next = Merge(a, b->next);
    }
    return(result);
}

/**
 * função auxiliar do mergeSort
 * @param source
 * @param frontRef
 * @param backRef
 */
void FrontBackSplit(PALAVRAS* source,
                    PALAVRAS** frontRef, PALAVRAS** backRef) {
    PALAVRAS *fast;
    PALAVRAS *slow;
    if (source == NULL || source->next == NULL) {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;

        /* Advance 'fast' two nodes, and advance 'slow' one node */
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        /* 'slow' is before the midpoint in the list, so split it in two
          at that point. */
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

/**
 * Requisito 8
 * função que cria o tabuleiro de listas ligadas através da leitura de um ficheiro txt, guardado pelo utilizador, ou através de um dicionário de palavras (a partir deste dicionário, uma função irá criar um tabuleiro onde existirão essas palavras) [esta função não está implementada]
 * possui um menu para que o utilizador escolha entre as duas opções referidas acima
 * é possível escolher a opção para, depois de termos construido o tabuleiro, permitir retornar um conjunto de caracteres, dado um conjunto de movimentos e uma posição inicial
 * @param p (lista das palavras, apontador para a primeira estrutura [não utilizada mas necessária para posteriormente enviar para a função da pesquisa)
 */
void functionMatrix2(PALAVRAS *p)
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
        printf("|   **clique (a) para introduzir a matriz atraves de txt               **     |\n");
        printf("|   **clique (b) para introduzir a matriz atraves de um dicionario     **     |\n");
        printf("|   **Clique (c) para voltar ao inicio                                 **     |\n");
        printf("|_____________________________________________________________________________|\n");
        scanf(" %c", &option);
        option = tolower(option);
        switch(option) {
            case 'a':
            {
                fp= fopen("../data/matriz.txt","r");
                if(fp!=NULL)
                {
                    fscanf(fp, "%d %d", &cols, &lines);
                    printf("    ______________________________________\n");
                    printf("   |        Dimensao da matriz %dx%d:      |\n", cols, lines);
                    printf("   |______________________________________|\n");
                    char **matrix= create_matrix2(lines, cols);
                    for(i=0; i<lines; i++)
                    {
                        for(j=0; j<cols; j++)
                        {
                            fscanf(fp, " %c", &(*(*(matrix+i)+j)));
                        }
                    }

                    CELULA *pfirst=ler_matriz(matrix, lines, cols);
                    print_lists(pfirst, lines, cols);
                    free(matrix);
                    fclose(fp);
                    /**< Inicio do menu3 */
                    printf(" _____________________________________________________________________________\n");
                    printf("|                            **Sopa de Letras**                               |\n");
                    printf("|   **clique (a) para continuar                                        **     |\n");
                    printf("|   **clique (b) para introduzir direcoes                              **     |\n");
                    printf("|_____________________________________________________________________________|\n");
                    scanf(" %c", &option);
                    option = tolower(option);
                    switch(option) {
                        case 'a': {
                            pesquisa2(p, pfirst);

                            printf(" _____________________________________________________________________________\n");
                            printf("|                            **Sopa de Letras**                               |\n");
                            printf("|   **clique (a) para voltar a pesquisar                               **     |\n");
                            printf("|   **clique (b) para voltar ao inicio                                 **     |\n");
                            printf("|_____________________________________________________________________________|\n");
                            scanf(" %c", &option);
                            option = tolower(option);
                            switch(option) {
                                case 'a': {
                                    pesquisa2(p, pfirst);
                                    break;
                                }

                                case 'b': {
                                    functionPalavra_fase2();
                                    break;
                                }
                            }
                            break;
                        }

                        case 'b': {
                            imprimir_caraters_por_direcoes(pfirst);
                            break;
                        }
                    }
                } else{
                    printf("Ficheiro nao encontrado\n");
                }
                break;
            }

            case 'b':
            {
                printf("Por fazer!!!\n");
                break;
            }

            case 'c':
            {
                free(p);
                functionPalavra_fase2();
                break;
            }

            default:
            {
                printf(" __________________________\n");
                printf("|Letra ou caracter invalido|\n");
                printf("|__________________________|\n");
                system("pause");
                system("cls");
                functionPalavra_fase2();
                break;
            }
        }
    }
}

/**
 * função que cria espaço para uma matriz que irá auxiliar a nossa construção do tabuleiro
 * @param l (número de linhas da sopa de letras)
 * @param c (número de colunas da sopa de letras)
 * @return
 */
char ** create_matrix2(int l, int c)
{
    char **pmatrix=(char**)malloc(l* sizeof(char*));
    for(int i=0; i<l; i++)
    {
        *(pmatrix+i)=(char*)malloc(c* sizeof(char));
    }
    return pmatrix;
}

/**
 * Requisito 8.a
 * função que cria listas ligadas (com 8 apontadores [N,NE,E,SE,S,SO,O,NO]) que será a sopa de letras
 * @param matrix (matriz que já contém os caracteres da sopa de letras
 * @param lines (número de linhas do tabuleiro)
 * @param cols (número de colunas do tabuleiro)
 * @return apontador para a primeira CELULA
 */
CELULA * ler_matriz(char **matrix, int lines, int cols)
{
    CELULA *first=NULL, *linha_anterior, *coluna_anterior;
    linha_anterior=(CELULA*)malloc (1*sizeof(CELULA));
    coluna_anterior=(CELULA*)malloc (1*sizeof(CELULA));
    first=(CELULA*)malloc (1*sizeof(CELULA));
    first->N=NULL;
    first->NE=NULL;
    first->E=NULL;
    first->SE=NULL;
    first->S=NULL;
    first->SO=NULL;
    first->O=NULL;
    first->NO=NULL;
    first->caracter=*(*(matrix));
    first->cache_celula= (CACHE*) malloc(sizeof(CACHE));
    first->cache_celula->palavra=NULL;
    first->cache_celula->direcoes=NULL;
    first->cache_celula->next=NULL;

    for(int i=0; i<lines; i++) {
        for (int j = 0; j < cols; j++) {
            if(i==0 && j==0)
            {
                coluna_anterior=first;
            }
            else if(i==0)
            {
                CELULA *c=(CELULA*)malloc (1*sizeof(CELULA));
                c->N=NULL;
                c->NE=NULL;
                c->E=NULL;
                c->SE=NULL;
                c->S=NULL;
                c->SO=NULL;
                c->O=coluna_anterior;
                coluna_anterior->E=c;
                c->NO=NULL;
                c->caracter=*(*(matrix + i) + j);
                c->cache_celula= (CACHE*) malloc(sizeof(CACHE));
                c->cache_celula->palavra=NULL;
                c->cache_celula->direcoes=NULL;
                c->cache_celula->next=NULL;
                coluna_anterior=coluna_anterior->E;
            }
            else if(j==0)
            {
                CELULA *c=(CELULA*)malloc (1*sizeof(CELULA));
                c->N=linha_anterior;
                linha_anterior->S=c;
                c->NE=linha_anterior->E;
                linha_anterior->SO=c;
                c->E=NULL;
                c->SE=NULL;
                c->S=NULL;
                c->SO=NULL;
                c->O=NULL;
                c->NO=NULL;
                c->caracter=*(*(matrix + i) + j);
                c->cache_celula= (CACHE*) malloc(sizeof(CACHE));
                c->cache_celula->palavra=NULL;
                c->cache_celula->direcoes=NULL;
                c->cache_celula->next=NULL;
                coluna_anterior=c;
            }
            else if(j==9)
            {
                CELULA *c=(CELULA*)malloc (1*sizeof(CELULA));
                c->N=coluna_anterior->NE;
                coluna_anterior->NE->S=c;
                c->E=NULL;
                c->SE=NULL;
                c->S=NULL;
                c->SO=NULL;
                c->O=coluna_anterior;
                coluna_anterior->E=c;
                c->NO=coluna_anterior->N;
                coluna_anterior->N->SE=c;
                c->caracter=*(*(matrix + i) + j);
                c->cache_celula= (CACHE*) malloc(sizeof(CACHE));
                c->cache_celula->palavra=NULL;
                c->cache_celula->direcoes=NULL;
                c->cache_celula->next=NULL;
                coluna_anterior=coluna_anterior->E;
            }
            else{
                CELULA *c=(CELULA*)malloc (1*sizeof(CELULA));
                c->N=coluna_anterior->NE;
                coluna_anterior->NE->S=c;
                c->NE=coluna_anterior->NE->E;
                coluna_anterior->NE->E->SO=c;
                c->E=NULL;
                c->SE=NULL;
                c->S=NULL;
                c->SO=NULL;
                c->O=coluna_anterior;
                coluna_anterior->E=c;
                c->NO=coluna_anterior->N;
                coluna_anterior->N->SE=c;
                c->caracter=*(*(matrix + i) + j);
                c->cache_celula= (CACHE*) malloc(sizeof(CACHE));
                c->cache_celula->palavra=NULL;
                c->cache_celula->direcoes=NULL;
                c->cache_celula->next=NULL;
                coluna_anterior=coluna_anterior->E;
            }
        }
        if(i==0)
        {
            linha_anterior=first;

        }else{
            linha_anterior=linha_anterior->S;
        }
    }
    return first;
}

/**
 * função que imprime o tabuleiro
 * @param c (apontador para a primeira celula)
 * @param lines (número de linhas do tabuleiro)
 * @param cols (número de colunas do tabuleiro)
 */
void print_lists(CELULA *c, int lines, int cols)
{
    CELULA *linha= c;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%c    ", c->caracter);
            c=c->E;
        }
        linha=linha->S;
        c=linha;
        printf("\n\n");
    }
}

/**
 * Requisito 10
 * função que dada uma posição inicial (percorre o tabuleiro até essa posição) e um conjunto de direções, imprime um conjunto de caracteres correspondentes às direções introduzidas
 * @param pfirst (apontador para a primeira celula)
 */
void imprimir_caraters_por_direcoes(CELULA *pfirst)
{
    int x, y, i=1;
    char direcao[5];
    char *carateres;
    carateres=(char*)malloc(1* sizeof(char));
    printf("Qual a posicao inicial (x y): \n");
    scanf("%d %d", &x, &y);
    while(x>0)
    {
        pfirst=pfirst->S;
        x--;
    }
    while(y>0)
    {
        pfirst=pfirst->E;
        y--;
    }

    *carateres=pfirst->caracter;
    //fgets(direcao, sizeof(direcao), stdin);
    do {
        printf("Introduza a direcao (\"exit\" para terminar): \n");
        //fgets(direcao, sizeof(direcao), stdin);
        scanf("%s", direcao);
        carateres = (char *) realloc(carateres, (sizeof(carateres) / sizeof(char)) + 1);
        if (strcmp(direcao, "E") == 0) {
            if (pfirst->E == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->E;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
        if (strcmp(direcao, "NE") == 0) {
            if (pfirst->NE == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->NE;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
        if (strcmp(direcao, "N") == 0) {
            if (pfirst->N == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->N;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
        if (strcmp(direcao, "NO") == 0) {
            if (pfirst->NO == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->NO;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
        if (strcmp(direcao, "O") == 0) {
            if (pfirst->O == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->O;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
        if (strcmp(direcao, "SO") == 0) {
            if (pfirst->SO == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->SO;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
        if (strcmp(direcao, "S") == 0) {
            if (pfirst->S == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->S;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
        if (strcmp(direcao, "SE") == 0) {
            if (pfirst->SE == NULL) {
                printf("Fora da matriz\n");
            } else {
                pfirst = pfirst->SE;
                *(carateres + i) = pfirst->caracter;
                i++;
            }
        }
    }while(strcmp(direcao, "exit")!=0);
    for (int j = 0; j < i; j++)
    {
        printf("%c ", *(carateres+j));
    }
    printf("\n");
}

/**
 * Requisito 9
 * função que chama as funções que exportam o jogo para ficheiros txt e bin
 * percorre a estrutura PALAVRAS até ao fim e para cada palavra, irá percorrer o tabuleiro onde irá pesquisar em cada celula se, a partir desta, é possível encontrar a palavra que está a pesquisar
 * limpa da memória (free) os apontadores utilizados
 * @param head (apontador para a primeira PALAVRA)
 * @param first (apontador para a primeira CELULA)
 */
void pesquisa2(PALAVRAS *head, CELULA *first)
{
    save_game(first, head, FILENAME);
    save_game_bin(first, head, FILENAMEBIN);
    while(head!=NULL)
    {
        int tamanho_palavra= strlen(head->palavra)-1;
        char **direcoes=create_arraypalavras2(tamanho_palavra); //criar "array de strings" com tamanho da palavra-1 (ex: OLA - 3letras e 2direcoes(de O para L e de L para A)
        int posicoes[4]; //array para as 4 posições(2 para x e y inicial e +2 para x e y finais)
        int *pposicoes= posicoes;
        //2 ciclos for para percorrer matrix até encontrar primeira letra da iézima palavra
        CELULA *linhafirst=first;
        CELULA *colunafirst=first;
        for (int i = 0; colunafirst!=NULL; ++i)
        {
            for (int j = 0; linhafirst!=NULL ; ++j) {
                if (linhafirst->caracter == head->palavra[0])
                {
                    int flag=0;
                    int m = 0;
                    int *pm = &m; //apontador para variavel que será incrementada na função recursiva

                    //quando encontrar, chamar função que vai ser recursiva para encontrar as restantes letras na matriz (dentro chamar outra função que testa se a posição, que vamos procurar a seguir, é valida)
                    *(posicoes + 0) = i;
                    *(posicoes + 1) = j;

                    CACHE *cache= linhafirst->cache_celula;
                    while(cache->palavra!=NULL  && strcmp(cache->palavra,head->palavra)<=0)
                    {
                        if(strcmp(cache->palavra, head->palavra)==0) {
                            printf("\nCache\n");
                            printf("\n%s: [%d,%d]->[%d,%d] - ", cache->palavra,
                                   cache->xi, cache->yi,
                                   cache->xf, cache->yf);
                            print_array2(cache->direcoes, cache->size_direcoes);
                            cache=cache->next;
                            flag=1;
                        }else {
                            cache=cache->next;
                        }
                    }
                    if(flag==0) {
                        pesquisa_palavra2(head->palavra, i, j, linhafirst, pm, direcoes, pposicoes);
                    }
                }
                linhafirst = linhafirst->E;
            }
            colunafirst=colunafirst->S;
            linhafirst=colunafirst;
        }
        colunafirst=first;
        linhafirst=first;
        //free das direcoes
        free(direcoes);
        free(linhafirst);
        free(colunafirst);
        head=head->next;
    }
    //free da matriz e das palavras
    free(head);
    free(first);
}

/**
 * Requisito 9
 * função recursiva que testará se a posição seguinte no tabuleiro (norte, nordeste, este, sudeste, sul, sudoeste, oeste, noroeste) é igual ao caracter da palavra que estamos a testar e se for guardará no array das direções a direção seguida para avançar para esse caracter no tabuleiro
 * a condição de paragem será quando a palavra acabar (quando o caracter for \0) e quando entrar na condição de paragem, serão guardadas as posições finais e imprimidas estas e as direções. Serão também chamadas as funções que guardam em ficheiros txt e bin as direções da solução
 * no fim da pesquisa introduzimos na cache da CELULA linha as informações requiridas na CACHE
 * @param p (palavra a pesquisar)
 * @param i (posição vertical do tabuleiro onde se encontra a celula a partir da qual iremos pesquisar a palavra)
 * @param j (posição horizontal do tabuleiro onde se encontra a celula a partir da qual iremos pesquisar a palavra)
 * @param linha (CELULA do caracter que iremos começar a procurar a palavra)
 * @param carater (inteiro que serve de contador. Utilizamos para saber qual a letra da palavra que estamos a procurar)
 * @param direcoes (array das direções em que serão introduzidas as direções da palavra no tabuleiro)
 * @param posicoes (array de posições de tamanho 4 [para x e y inicial e x e y final])
 */
void pesquisa_palavra2(char *p, int i, int j, CELULA *linha, int *carater, char **direcoes, int *posicoes)
{
    (*carater)++;
    if(*(p+*carater)=='\0') {
        *(posicoes+2)=i;
        *(posicoes+3)=j;
        printf("\n%s: [%d,%d]->[%d,%d] - ", p, *posicoes, *(posicoes+1), *(posicoes+2), *(posicoes+3));
        print_array2(direcoes, *carater);
        //insert_cache_ordered(linha, p, direcoes, posicoes, *carater);
        save_direcoes(p, direcoes, posicoes, *carater, FILENAME);
        save_direcoes_bin(p, direcoes, posicoes, *carater, FILENAMEBIN);
        printf("\n");
    }
    else{
        //N
        if(linha->N!=NULL) {
            if (linha->N->caracter == *(p + *carater)) {
                char *str = "N";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i - 1, j, linha->N, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
        //NE
        if(linha->NE!=NULL) {
            if (linha->NE->caracter == *(p + *carater)) {
                char *str = "NE";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i - 1, j + 1, linha->NE, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
        //E
        if(linha->E!=NULL) {
            if (linha->E->caracter == *(p + *carater)) {
                char *str = "E";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i, j + 1, linha->E, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
        //SE
        if(linha->SE!=NULL) {
            if (linha->SE->caracter == *(p + *carater)) {
                char *str = "SE";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i + 1, j + 1, linha->SE, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
        //S
        if(linha->S!=NULL) {
            if (linha->S->caracter == *(p + *carater)) {
                char *str = "S";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i + 1, j, linha->S, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
        //SO
        if(linha->SO!=NULL) {
            if (linha->SO->caracter == *(p + *carater)) {
                char *str = "SO";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i + 1, j - 1, linha->SO, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
        //O
        if(linha->O!=NULL) {
            if (linha->O->caracter == *(p + *carater)) {
                char *str = "O";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i, j - 1, linha->O, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
        //NO
        if(linha->NO!=NULL) {
            if (linha->NO->caracter == *(p + *carater)) {
                char *str = "NO";
                *(direcoes + ((*carater) - 1)) = (char *) malloc((strlen(str) + 1) * sizeof(char));
                *(direcoes + ((*carater) - 1)) = str;
                pesquisa_palavra2(p, i - 1, j - 1, linha->NO, carater, direcoes, posicoes);
                free(*(direcoes + ((*carater) - 1)));
                (*carater)--;
            }
        }
    }
}

/**
 * função que aloca espaço para um array de caracteres com tamanho n
 * @param n (tamanho do array)
 * @return
 */
char ** create_arraypalavras2(int n)
{
    char **paux=(char**)malloc(n* sizeof(char*));
    return paux;
}

/**
 * função que imprime um array de caracteres
 * @param array (array de caracteres que desejamos imprimir)
 * @param size (tamanho do array)
 */
void print_array2(char **array, int size)
{
    for(int i = 0; i < size-1; i++)
    {
        printf("[%s]", *(array+i));
    }
}

/**
 * Requisito 11
 * parcialmente implementado
 * esta função introduz na cache de uma celula a palavra que é possível encontrar a partir dessa celula, a posição inicial (posição da celula), posição final, nr de direções e o array das direções
 * a função introduz na cache ordenadamente, ou seja, as palavras que são possíveis encontrar a partir desta celula, estão ordenadas alfabeticamente
 * @param pc (apontador para a primeira CELULA)
 * @param p (palavra que pretendemos guardar na cache)
 * @param direcoes (array das direções que contém a solução da pesquisa da palavra)
 * @param posicoes (posições iniciais [x,y] e finais [x,y])
 * @param size (número de direções necessárias para encontrar palavra)
 */
void insert_cache_ordered(CELULA *pc, char *p, char **direcoes, int *posicoes, int size)
{
    CACHE *temp=(CACHE *)malloc(1*sizeof(CACHE));

    temp->palavra=malloc(sizeof(char)*strlen(p)+1);
    strcpy(temp->palavra, p);

    temp->xi=*(posicoes);
    temp->yi=*(posicoes+1);
    temp->xf=*(posicoes+2);
    temp->yf=*(posicoes+3);

    temp->size_direcoes=size;

    temp->direcoes= alocar_memoria_direcoes(size);
    temp->direcoes= direcoes;

    if(pc->cache_celula->palavra==NULL || strcmp(pc->cache_celula->palavra, p)>0)
    {
        temp->next = pc->cache_celula;
        pc->cache_celula = temp;
    }else{
        CACHE *current = pc->cache_celula;
        while (current->next->palavra!=NULL && strcmp(current->next->palavra, p)<=0)
        {
            current=current->next;
        }
        temp->next=current->next;
        current->next=temp;
    }
}

/**
 * esta função aloca espaço para uma "matriz" de caracteres (irá ser utilizada para alocar espaço para o array das direções)
 * @param size (tamanho que queremos reservar na memória)
 * @return
 */
char ** alocar_memoria_direcoes(int size)
{
    char **pmatrix=(char**)malloc(size* sizeof(char*));
    for(int i=0; i<size; i++)
    {
        *(pmatrix+i)=(char*)malloc(3* sizeof(char));
    }
    return pmatrix;
}

/**
 * Requisito 12
 * esta função exporta para txt o tabuleiro da sopa de letras e as palavras a pesquisar
 * @param first (apontador para a primeira celula)
 * @param p (apontador para a primeira palavra)
 * @param fn (localização onde iremos guardar o ficheiro)
 */
void save_game(CELULA *first, PALAVRAS *p, char *fn)
{
    FILE *fp;
    fp=fopen(fn, "w");
    if(fp!=NULL)
    {
        fprintf(fp, "\t\tSopa de Letras\n");
        CELULA *linha=first;
        CELULA *coluna=first;
        for (int i = 0; coluna!=NULL; ++i)
        {
            for (int j = 0; linha!=NULL ; ++j) {
                fprintf(fp, "%c    ", linha->caracter);
                linha = linha->E;
            }
            fprintf(fp, "\n\n");
            coluna=coluna->S;
            linha=coluna;
        }
        fprintf(fp, "\nPalavras:\n");
        PALAVRAS *temp= p;
        while (temp!=NULL && temp->palavra!=NULL)
        {
            fprintf(fp, "%s\n", temp->palavra);
            temp=temp->next;
        }
        fprintf(fp, "\nSolucoes:\n");
        fclose(fp);
    }else{
        printf("Erro!");
        return;
    }
}

/**
 * Requisito 12
 * esta função exporta para txt (continua a escrever no fim do ficheiro) a palavra pesquisada, posições inicais e finais e as direções
 * @param p (palavra que iremos guardar)
 * @param direcoes (direções da solução da pesquisa da palavra p)
 * @param posicoes (posições inicais e finais da palavra p no tabuleiro)
 * @param size (número de direções)
 * @param fn (localização onde iremos guardar o ficheiro)
 */
void save_direcoes(char *p, char **direcoes, int *posicoes, int size, char *fn)
{
    FILE *fp;
    fp=fopen(fn, "a+");
    if(fp!=NULL)
    {
        fprintf(fp, "%s: [%d,%d]->[%d,%d] - ", p, *posicoes, *(posicoes+1), *(posicoes+2), *(posicoes+3));
        for(int i = 0; i < size-1; i++)
        {
            fprintf(fp, "[%s]", *(direcoes+i));
        }
        fprintf(fp, "\n");
        fclose(fp);
    }
    else{
        printf("Erro!");
        return;
    }
}

/**
 * Requisito 13
 * esta função exporta para um ficheiro binário o tabuleiro da sopa de letras e as palavras a pesquisar
 * @param first (apontador para a primeira CELULA)
 * @param p (apontador para a primeira palavra)
 * @param fn (localização onde iremos guardar o ficheiro)
 */
void save_game_bin(CELULA *first, PALAVRAS *p, char *fn)
{
    FILE *fp;
    fp=fopen(fn, "wb");
    if(fp!=NULL)
    {
        CELULA *linha=first;
        CELULA *coluna=first;
        for (int i = 0; coluna!=NULL; ++i)
        {
            for (int j = 0; linha!=NULL ; ++j) {
                fwrite(&linha->caracter, sizeof(char), 1, fp);
                linha = linha->E;
            }
            coluna=coluna->S;
            linha=coluna;
        }

        PALAVRAS *temp= p;
        while (temp!=NULL && temp->palavra!=NULL)
        {
            fwrite(&temp->palavra, sizeof(char), strlen(temp->palavra)+1, fp);
            temp=temp->next;
        }
        fclose(fp);
    }
    else{
        printf("Erro!");
        return;
    }
}

/**
 * Requisito 13
 * esta função exporta para bin (continua a escrever no fim do ficheiro) a palavra pesquisada, posições inicais e finais e as direções
 * @param p (palavra que iremos guardar)
 * @param direcoes (direções da solução da pesquisa da palavra p)
 * @param posicoes (posições inicais e finais da palavra p no tabuleiro)
 * @param size (número de direções)
 * @param fn (localização onde iremos guardar o ficheiro)
 */
void save_direcoes_bin(char *p, char **direcoes, int *posicoes, int size, char *fn)
{
    FILE *fp;
    fp=fopen(fn, "ab+");
    if(fp!=NULL)
    {
        size_t len= strlen(p)+1;
        fwrite(&len, sizeof(size_t), 1, fp);
        fwrite(&(*posicoes), sizeof(int), 1, fp);
        fwrite(&(*(posicoes+1)), sizeof(int), 1, fp);
        fwrite(&(*(posicoes+2)), sizeof(int), 1, fp);
        fwrite(&(*(posicoes+3)), sizeof(int), 1, fp);
        fwrite(&size, sizeof(int), 1, fp);
        for(int i = 0; i < size-1; i++)
        {
            fprintf(fp, "[%s]", *(direcoes+i));
            fwrite(&(*(direcoes+i)), sizeof(char), 3, fp);
        }
        fclose(fp);
    }else{
        printf("Erro!");
        return;
    }
}
