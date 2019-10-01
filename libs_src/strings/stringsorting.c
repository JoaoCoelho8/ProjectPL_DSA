    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "../lib_util.h"
#include "stringsorting.h"

/*************************************************************************
 * Util functions for struct StringElements and struct StringKeyElements
 ************************************************************************/

void createStringKeyElementsArray(StringKeyElementsArray * si, int N) {
    si->N = N;
    si->str = (char **) malloc(sizeof(char *)*N);
    si->len = (int *) malloc(sizeof(int)*N);
    si->keys = (int *) malloc(sizeof(int)*N);
    return;
}

void createStringKeyElementsArrayAndFill(StringKeyElementsArray * a, int N, char ** strings, int * keys){
    int i;
    createStringKeyElementsArray(a, N);
    for (i = 0; i < N; i++) {
        a->str[i] = strings[i];
        a->len[i] = (int)strlen(strings[i]);
        a->keys[i] = keys[i];
    }
}

void freeStringKeyElementsArray(StringKeyElementsArray * si) {
    free(si->str);
    free(si->len);
    free(si->keys);
    return;
}

void createStringElementsArray(StringElementsArray * si, int N) {
    si->N = N;
    si->str = (char **) malloc(sizeof(char *)*N);
    si->len = (int *) malloc(sizeof(int)*N);
    return;
}

void createStringElementsArrayAndFill(StringElementsArray * si, int N, char ** strings){
    int i;
    createStringElementsArray(si, N);
    for (i = 0; i < N; i++) {
        si->str[i] = strings[i];
        si->len[i] = (int)strlen(strings[i]);
    }
    return;
}

void freeStringElementsArray(StringElementsArray * si) {
    free(si->str);
    free(si->len);
    return;
}

void printStringElementsArray(StringElementsArray * a) {
    int i;
    printf("\n-------------\nStringElementsArray (N=%d):\n",a->N);
    for (i = 0; i < a->N; i++)
        printf("\t%s\t(%d)\n",a->str[i],a->len[i]);
    printf("-------------\n");
}

void printStringElementsArrayProjeto(StringElementsArray * a) {
    int i;
    printf("\n-------------------------------------------------------\n%d palavra(s) para a sopa de letras (Ordenadas por MSD):\n", a->N);
    for (i = 0; i < a->N; i++)
        printf("\t\t%s\n", a->str[i]);
    printf("-------------------------------------------------------\n");
}

int charAt(StringElementsArray * a, int i, int d) {

    return (d < a->len[i]) ? (a->str[i][d]) : STRING_END_CHAR;
}

/**
 *  exchange a[i] and a[j] in collection StringElementsArray *a
 *
 *  @param a strin elements array
 *  @param i
 *  @param j 
 */
void exchStringElementsArray(StringElementsArray *a, int i, int j) {
    char * temp_str = a->str[i];
    a->str[i] = a->str[j];
    a->str[j] = temp_str;
    int temp_len = a->len[i];
    a->len[i] = a->len[j];
    a->len[j] = temp_len;
}



/**
 *  Insertion sort from a[lo] to a[hi], starting at the dth character
 *
 *  @param a  array of strings
 *  @param lo low index of subarray
 *  @param hi high index of subarray (inclusive)
 *  @param d  index of d char for each string
 */
void insertionSort4Strings(StringElementsArray *a, int lo, int hi, int d) {
    int i,j;
    for (i = lo+1; i <= hi; i++)
        for (j = i; j > lo; j--) {
            if (strcmp4Strings(&(a->str[j][d]), &(a->str[j-1][d]), a->len[j] - d, a->len[j-1] - d) < 0)
                exchStringElementsArray(a, j, j-1);
            else break;
        }
}


/**
 *  String compare for strings
 *
 *  @param s1   <#s1 description#>
 *  @param s2   <#s2 description#>
 *  @param len1 <#len1 description#>
 *  @param len2 <#len2 description#>
 *
 *  @return -1 if s1<s2; +1 if s1>s2; 0 if s1==s2
 */
int strcmp4Strings(const char *s1, const char *s2, int len1, int len2) {
    int i=0;
    for ( ; *s1 == *s2; s1++, s2++, i++){
        if (i >= len1 && i >= len2)
            return 0;
        else if (i >= len1)
            return -1;
        else if (i >= len2)
            return +1;
    }
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

/*************************************************************************
 * Longest common prefix (String Sorts)
 ************************************************************************/
int lcp(char * s, char * t) {
    int i, ls, lt;
    ls = (int) strlen(s);
    lt = (int)strlen(t);
    int N = (ls < lt ? ls : lt);
    for (i = 0; i < N; i++)
        if (s[i] != t[i])
            return i;
    return N;
}

int mainClienteLPC() {
    int k;
    k = lcp("aaac","aaabbaa");
    printf("lpc=%d\n",k);
    return 0;
}

/*************************************************************************
 * Key-indexed counting / radix sorting
 ************************************************************************/

void key_index_counting(StringKeyElementsArray * a, int N, int R) {
    int i,r,c;
    int * count = newIntArray(R + 1);
    // reset count[] array
    for (i = 0; i < R + 1; i++)
        count[i]=0;
    StringKeyElementsArray aux; // aux Array
    createStringKeyElementsArray(&aux,N); // create aux array

    // compute frequency counts
    //Frequência absoluta.
    for (i = 0; i < N; i++)
        count[a->keys[i]]++; printArray(count,R);
    // transform counts to indicies
    // Frequências acumuladas.
    for (r = 0; r < R; r++)
        count[r+1] += count[r];
        printArray(count,R);
    // distribute
    
    for (i = 0; i < N; i++) {
        c = a->keys[i] - 1;
        aux.str[count[c]] = a->str[i];
        aux.len[count[c]] = a->len[i];
        aux.keys[count[c]] = a->keys[i];
        count[c]++;
        printArray(count,R);
    }

    // copy back
    for (i = 0; i < N; i++) {
        a->str[i] = aux.str[i];
        a->len[i] = aux.len[i];
        a->keys[i] = aux.keys[i];
    }

    freeStringKeyElementsArray(&aux);
}

int mainClienteKEYCOUNT() {
    int i, N=20;
    char * strings[] = {
        "Anderson",
        "Brown",
        "Davis",
        "Garcia",
        "Harris",
        "Jackson",
        "Johnson",
        "Jones",
        "Martin",
        "Martinez",
        "Miller",
        "Moore",
        "Robinson",
        "Smith",
        "Taylor",
        "Thomas",
        "Thompson",
        "White",
        "Williams",
        "Wilson",
    };
    int keys[] = {2,3,3,4,1,3,4,3,1,2,2,1,2,4,3,4,4,2,3,4};

    StringKeyElementsArray a;
    createStringKeyElementsArrayAndFill(&a, N, strings, keys);
    
    printf("\n-----------------\nInput String-Key List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s, %d\n",a.str[i],a.keys[i]);

    key_index_counting(&a, N, KEY_INDEX_RADIX);

    printf("\n-----------------\nSorted String-Key List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s, %d\n",a.str[i],a.keys[i]);

    return 0;
}

/*************************************************************************
 * LSD Radix Sort
 ************************************************************************/


void lsd_sort(StringElementsArray * a, int W, int R) {
    int i,r,d,c;
    int N = a->N;
    int * count = newIntArray(R + 1);
    StringElementsArray aux; // aux Array
    createStringElementsArray(&aux,N); // create aux array

    for (d = W-1; d >= 0; d--) {

        // reset count[] array
        for (i = 0; i < R+1; i++)
            count[i]=0;

        // compute frequency counts
        for (i = 0; i < N; i++){
            count[a->str[i][d] + 1]++;
        }

        // transform counts to indicies
        for (r = 0; r < R; r++)
            count[r+1] += count[r];

        printArray(count,R);


        // distribute
        for (i = 0; i < N; i++) {
            c = a->str[i][d];
            aux.str[count[c]] = a->str[i];
            aux.len[count[c]] = a->len[i];
            count[c]++;
        }

        // copy back
        for (i = 0; i < N; i++) {
            a->str[i] = aux.str[i];
            a->len[i] = aux.len[i];
        }

        // Trace of iterations for LSD string sort
        printf("\nLSD Sorted List (right to left) after sorting key %d:\n",d);
        for (i = 0; i < N; i++)
            printf("\t%s\n",a->str[i]);
    }
    freeStringElementsArray(&aux);
}


/**
 * Versão modificada em que o alfabeto é composto por R símbolos contíguos
 * da tabela ascii e o primeiro símbolo é st
 **/
void lsd_sort_v2(StringElementsArray * a, int W, int R, char st) {
    int i,r,d,c;
    int N = a->N;
    int * count = malloc((R+1) * sizeof(int));
    StringElementsArray aux; // aux Array
    createStringElementsArray(&aux,N); // create aux array
    
    for (d = W-1; d >= 0; d--) {
        
        // reset count[] array
        for (i = 0; i < R+1; i++)
            count[i]=0;
        
        // compute frequency counts
        for (i = 0; i < N; i++) {
            // first extract order/index of element in the dictionarie. suggestion: use a function for this
            c = (a->str[i][d]) - st;
            // second: update frequency counts
            count[c + 1]++;
        }
        
        // transform counts to indicies
        for (r = 0; r < R; r++)
            count[r+1] += count[r];
        
        // distribute
        for (i = 0; i < N; i++) {
            // first extract order/index of element in the dictionarie. suggestion: use a function for this
            c = (a->str[i][d]) - st;
            // second copy the element of one array structure to another. suggestion: use a function for this
            aux.str[count[c]] = a->str[i];
            aux.len[count[c]] = a->len[i];
            count[c]++;
        }
        
        // copy back
        for (i = 0; i < N; i++) {
            a->str[i] = aux.str[i];
            a->len[i] = aux.len[i];
        }
        
        // Trace of iterations for LSD string sort
        printf("\nLSD Sorted List (right to left) after sorting key %d:\n",d);
        for (i = 0; i < N; i++)
            printf("\t%s\n",a->str[i]);
    }
    freeStringElementsArray(&aux);
    free(count);
}


/**
 * Versão modificada para ordenar ints
 **/
void lsd_sort_ints(int * a, int N) {
    int i,r,d,c,R=10,cond=1,v;
    int * count = malloc((R+1) * sizeof(int));
    int * aux = (int *) malloc(sizeof(int) * N); // create aux dynamic int Array
    
    for (d = 1; cond != 0; d=d*10) {
        cond = 0;
        
        // reset count[] array
        for (i = 0; i < R+1; i++)
            count[i]=0;
        
        // compute frequency counts
        for (i = 0; i < N; i++) {
            // first extract order/index of element in the dictionarie. suggestion: use a function for this
            v = a[i]/d;
            c = v%10;
            if (v>=10) cond = 1;
            // second: update frequency counts
            count[c + 1]++;
        }
        
        // transform counts to indicies
        for (r = 0; r < R; r++)
            count[r+1] += count[r];
        
        // distribute
        for (i = 0; i < N; i++) {
            // first extract order/index of element in the dictionarie. suggestion: use a function for this
            v = a[i]/d;
            c = v%10;
            // second copy the element of one array structure to another. suggestion: use a function for this
            aux[count[c]] = a[i];
            count[c]++;
        }
        
        // copy back
        for (i = 0; i < N; i++) {
            a[i] = aux[i];
        }
        
        // Trace of iterations for LSD string sort
        printf("\nLSD Sorted List (right to left) after sorting key %d:\n",d);
        for (i = 0; i < N; i++)
            printf("\t%8d\n",a[i]);
    }
    free(aux);
    free(count);
}

int mainClienteLSDSORT() {
    int i,N=12,fixed_string_with=3;
    char * strings[] = {
        "dab",
        "add",
        "cab",
        "fad",
        "fee",
        "bad",
        "dad",
        "bee",
        "fed",
        "bed",
        "ebb",
        "ace"
    };

    StringElementsArray a;
    createStringElementsArrayAndFill(&a, N, strings);

    printf("\n-----------------\nLSD Input List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    lsd_sort(&a, fixed_string_with, CHAR_8BIT_RADIX);

    printf("\n-----------------\nLSD Sorted List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    return 0;
}

int mainClienteLSDSORT_6nov2013() {
    int i,N=10,fixed_string_with=3;
    char * strings[] = {
        "dab",
        "add",
        "cab",
        "fad",
        "fee",
        "bad",
        "dad",
        "bee",
        "fed",
        "bed"
    };
    StringElementsArray a;
    createStringElementsArrayAndFill(&a, N, strings);
    
    printf("\n-----------------\nLSD Input List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    lsd_sort(&a, fixed_string_with, CHAR_8BIT_RADIX);

    printf("\n-----------------\nLSD Sorted List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    return 0;
}

int mainClienteLSDSORT_4jul2014() {
    int i,N=12,fixed_string_with=3;
    char * strings[] = {
        "tno",
        "dis",
        "rth",
        "ati",
        "bfo",
        "bal",
        "bgo",
        "dpe",
        "dto",
        "eco",
        "rto",
        "rth"
    };
    StringElementsArray a;
    createStringElementsArrayAndFill(&a, N, strings);

    printf("\n-----------------\nLSD Input List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    lsd_sort(&a, fixed_string_with, CHAR_8BIT_RADIX);

    printf("\n-----------------\nLSD Sorted List:\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    return 0;
}

/*************************************************************************
 * MSD Radix Sort (without cutoff)
 ************************************************************************/

void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R) {
    int i,r,c;
    int * count = newIntArray(R + 2);
    // reset count[] array
    for (i = 0; i < R+2; i++)
        count[i]=0;

    if (hi <= lo) return;
    //if (hi - lo <= cutoff_value) insertion_sort();

    // compute frequency counts
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        count[c + 2]++;
    }

    // transform counts to indicies
    for (r = 0; r < R + 1; r++)
        count[r+1] += count[r];

    // distribute
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        //printf("c = %d i = %d d = %d\n",count[c + 1],i,d);
        aux->str[count[c + 1]] = a->str[i];
        aux->len[count[c + 1]] = a->len[i];
        count[c + 1]++;
    }

    // copy back
    for (i = lo; i <= hi; i++) {
        a->str[i] = aux->str[i-lo];
        a->len[i] = aux->len[i-lo];
    }

    // Trace of recursive calls for MSD string sort (version with no cutoff for small subarrays used!)
    //printf("\n-------------\nMSD Sorted List (left to right) after iteration (lo,hi,d)= %d,%d,%d:\n",lo,hi,d);
    for (i = lo; i <= hi; i++)
        //printf("\t%s\n",a->str[i]);

    // recursively sort for each character

    for (r = 0; r < R; r++)
        msd_sort_whithout_cutoff(a, aux, lo + count[r], lo + count[r+1] - 1, d+1, R);
}


/*************************************************************************
 * Suffix Arrays
 ************************************************************************/

void sa_createSuffixArray(char * texto, StringElementsArray * sa, int R) {
    int i,N;
    StringElementsArray aux; // aux Array
    N = (int)strlen(texto);
    createStringElementsArray(sa,N);
    for (i = 0; i < sa->N; i++) {
        sa->str[i] = &texto[i];
        sa->len[i] = N - i;
    }
    createStringElementsArray(&aux,sa->N); // create aux array
    printf("\n-------------\nUnsorted Suffix Arrays:\n");
    for (i = 0; i < sa->N; i++)
        printf("\t%s, %d\n",sa->str[i],sa->len[i]);
    msd_sort_whithout_cutoff(sa, &aux, 0, N-1, 0, R);
    freeStringElementsArray(&aux);
}

/**
 longest common prefix of suffixes(i) and suffixes(i-1)
*/
int sa_lcp(StringElementsArray * sa, int i) {
    return lcp(sa->str[i], sa->str[i-1]);
}

// longest common prefix of suffixes(i) and suffixes(j)
int sa_lcp_ij(StringElementsArray * sa, int i, int j) {
    return lcp(sa->str[i], sa->str[j]);
}

// index of ith sorted suffix
int sa_index(StringElementsArray * sa, int i) {
    return sa->N - sa->len[i];
}

// ith sorted suffix
char * sa_select(StringElementsArray * sa, int i) {
    return sa->str[i];
}
