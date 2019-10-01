#ifndef STRINGSORT_H_INCLUDED
#define STRINGSORT_H_INCLUDED

/**
 @ brief tamanho do alfabeto de chaves/keys {1,2,3,4} *
 */
#define KEY_INDEX_RADIX 4

// tamanho do alfabeto de chars com 8 bits (ASCII)
#define CHAR_8BIT_RADIX 256

// terminate symbol for strings
#define STRING_END_CHAR -1

/**
 *  Used to implement key-index-count algorithm
 */
typedef struct {
    char ** str; // array of strings
    int * len; // array of string lengths
    int * keys; // key arrays de um alfabeto com STR_KEY_RADIX simbolos
    int N; // number of strings (size of array of strings)
} StringKeyElementsArray;

/**
 *  Structure used for LSD, MSD and other
 */
typedef struct {
    char ** str; // array of strings
    int * len; // array of string lengths
    int N; // number of strings (size of array of strings)
} StringElementsArray;

void key_index_counting(StringKeyElementsArray * a, int N, int R);

void lsd_sort(StringElementsArray * a, int W, int R);
void lsd_sort_v2(StringElementsArray * a, int W, int R, char st);
void lsd_sort_ints(int * a, int N);

void createStringKeyElementsArray(StringKeyElementsArray * si, int N);
void createStringKeyElementsArrayAndFill(StringKeyElementsArray * a, int N, char ** strings, int * keys);
void freeStringKeyElementsArray(StringKeyElementsArray * si);

void createStringElementsArrayAndFill(StringElementsArray * si, int N, char ** a);
void createStringElementsArray(StringElementsArray * si, int N);
void freeStringElementsArray(StringElementsArray * si);
void printStringElementsArray(StringElementsArray * a);
void printStringElementsArrayProjeto(StringElementsArray * a);

int charAt(StringElementsArray * a, int i, int d);
void exchStringElementsArray(StringElementsArray *a, int i, int j);
int strcmp4Strings(const char *s1, const char *s2,int len1, int len2);
void insertionSort4Strings(StringElementsArray *a, int lo, int hi, int d); // used for cuttof


void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R);

void sa_createSuffixArray(char * texto, StringElementsArray * sa, int R);
int sa_lcp(StringElementsArray * sa, int i);
int sa_lcp_ij(StringElementsArray * sa, int i, int j);
int sa_index(StringElementsArray * sa, int i);
char * sa_select(StringElementsArray * sa, int i);

int mainClienteMSDSORT_WHITHOUT_CUTOFF();
void mainClienteMSDSORT_WHITHOUT_CUTOFF2();
int mainClienteSUFFIXARRAY_TEST();


int lcp(char * s, char * t);

int mainClienteSTRSORT(int argc, char ** argv);
int mainClienteLPC();
int mainClienteKEYCOUNT();
int mainClienteLSDSORT();

int mainClienteKEYCOUNT1();

int mainClientInsertionSort4Strings();

// file quick3string.c
void quick3sort(StringElementsArray * a, int lo, int hi, int d);
int mainClienteQ3SORT();
void quick3sort_with_cutoff(StringElementsArray *a, int lo, int hi, int d);
int mainClienteQ3SORT_FROMFILE(int argc, char ** argv);

#endif // STRINGSORT_H_INCLUDED
