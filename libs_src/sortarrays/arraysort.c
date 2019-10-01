//
//  arraysort.c
//  sortarrays_app
//
//  Created by José Manuel Torres on 05/12/14.
//  Copyright (c) 2014 ___JOSETORRES___. All rights reserved.
//

#include "arraysort.h"
#include "../lib_util.h"
#include "../lib_stats.h"

void sortSelection(int v[],int N){
    int i,j,min,aux;
    for (i=0; i<N; i++) {
        min=i;
        for (j=i+1; j<N; j++) {
            if(v[j]<v[min])
                min=j;
        }
        //printf("\n%d <-> %d",v[i], v[min]);
        aux=v[i];
        v[i]=v[min];
        v[min]=aux;

    }
}

int sortInsertion1(int v[],int N, int flags) {
    int i,j,aux;
    int count=0; // regista o número de trocas efectuadas
    for (i=1; i<N; i++) {
        for (j=i; j>0; j--) {
            if(v[j]<v[j-1]) {
                aux=v[j];v[j]=v[j-1];v[j-1]=aux;
                count++; // conta o número de trocas efectuadas
            } else break;
        }
        if (flags==1) printArray(v, N); // imprime array
    }
    return count; // devolve o número de trocas efectuadas
}

void sortInsertion(int v[],int N){
    int i,j,key;
    for (i=1; i<N; i++) {
        key = v[i];
        j = i-1;
        while (j>=0 && v[j] > key) {
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1]=key;
    }
}

void sortInsertionLH(int v[], int lo, int hi){
    int i,j,key;
    for (i=lo+1; i<=hi; i++) {
        key = v[i];
        j = i-1;
        while (j>=lo && v[j] > key) {
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1]=key;
    }
}

/**
  Array sorting: sorting just the pointers and don't change the original values.
  Pointer array works as a secondary (indexed) structure
 */
void sortInsertionLH_PInt(int * v[], int lo, int hi){
    int i,j;
    int *key;
    for (i=lo+1; i<=hi; i++) {
        key = v[i];
        j = i-1;
        while (j>=lo && *v[j] > *key) {
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1]=key;
    }
}


/** verifica se um vector está ordenado (1) ou desordenado (0) */
int testSorting(int v[],int N){
    int i;
    for (i=0; i<N-1; i++) {
        if (v[i+1]<v[i])
            return 0;
    }
    return 1;
}

int countInversions(int v[],int N){
    int i,j,count=0;
    for (i=0; i<N; i++) {
        for (j=i+1; j<N; j++) {
            if (v[j]<v[i])
                count++;
                }
    }
    return count;
}

void listInversions(int v[],int N){
    int i,j;
    for (i=0; i<N; i++) {
        for (j=i+1; j<N; j++) {
            if (v[j]<v[i])
                printf("\n%d <-> %d",v[i],v[j]);
        }
    }
}


/** Ordenação por merge sort **/
void mergesort_run(int *a, int n, int flag_cutoff) {
    int * aux;
    aux = malloc(sizeof(int) * n);
    if (flag_cutoff==1)
        mergesort_recursivo_cutoff(a, aux, 0, n - 1);
    else
        mergesort_recursivo(a, aux, 0, n - 1);
    free(aux);
    return;
}

void mergesort_recursivo(int *a, int *aux, int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    mergesort_recursivo(a, aux, lo, mid);
    mergesort_recursivo(a, aux, mid+1, hi);
    if (*(a+(mid+1)) >= *(a+mid)) return; // improvement
    merge_array(a, aux, lo, mid, hi);
}

void mergesort_recursivo_cutoff(int *a, int *aux, int lo, int hi) {
    if (hi <= lo) return;
    if (hi <= lo + CUTOFF_MERGESORT - 1)
        sortInsertion(&a[lo], hi - lo + 1);
    int mid = lo + (hi - lo) / 2;
    mergesort_recursivo_cutoff(a, aux, lo, mid);
    mergesort_recursivo_cutoff(a, aux, mid+1, hi);
    if (*(a+(mid+1)) >= *(a+mid)) return; // improvement
    merge_array(a, aux, lo, mid, hi);
}

void merge_array(int *a, int *aux, int lo, int mid, int hi) {
    int k;
    for (k = lo; k <= hi; k++)
        *(aux+k) = *(a+k);
    int i = lo, j = mid+1;
    for (k = lo; k <= hi; k++) {
        if (i > mid) *(a+k) = *(aux+(j++));
        else if (j > hi) *(a+k) = *(aux+(i++));
        else if (*(aux+j) < *(aux+i)) *(a+k) = *(aux+(j++));
        else *(a+k) = *(aux+(i++));
    }
}

/** 
 * Fusão inplace:
 * Fusão dos vectores a[] e b[] com tamanhos 2N e N ambos ordenados ascendentemente.
 * O vector a[] apenas está a ocupar as primeiras N posições, isto é, a segunda
 * metade de a[] está vazia.
 * A fusão é efectuada em directamente em a[] (inplace) sem usar vector auxiliar
 */
void merge_array_inplace(int a[], int b[], int N){
    int i = N-1, j = N-1;
    int k;
    for (k = 2*N - 1; k >= 0 && j >=0; k--) {
        if (i < 0) a[k] = b[j--];
        else if (b[j] > a[i]) a[k] = b[j--];
        else a[k] = a[i--];
    }
}


/** Knuth shuffle (Rearrange an array so that result is a uniformly random permutation) */
void shuffleArray(int a[], int N) {
    int i, aux, r;
    for (i = 0; i < N; i++) {
        r = uniform(0, i); // random uniform between 0 and i
        aux = a[i]; a[i] = a[r]; a[r] = aux; // swap
    }
}

/** quick sort */
void quicksort(int a[], int lo, int hi) {
    if (hi <= lo) return;
    
    // melhoramento pratico do quicksosrt: escolher mediana entre 3 valores para pivot
    //int median = medianOf3(a, lo, lo + (hi - lo)/2, hi);
    //swap(a, lo, median);
    //int v[]={150,210,200,900,12,15,180,21}, N=8;

    int j = partitionQuicksort(a, lo, hi);
    printf("Pivot = %d\n", j);

    printArrayQuickSort(a, lo,hi+1);
    quicksort(a, lo, j-1);
    printArrayQuickSort(a, j+1,hi+1);
    quicksort(a, j+1, hi);
}

int partitionQuicksort(int a[], int lo, int hi) {
    int i = lo, j = hi+1, aux;
    while (1) {
        while (a[++i] < a[lo]){
            // find item on left to swap
            printf("a[++i] < a[lo]? : Sim %d < %d\n", a[i], a[lo]);
            if (i == hi) break;
        }
        while (a[lo] < a[--j]){
            // find item on right to swap
            printf("a[lo] < a[--j]? : Sim %d < %d \n", a[lo], a[j]);
            if (j == lo) break;
        }
        if (i >= j) break; // check if pointers cross

        printf("a[](%d<->%d)= ",i,j);

        aux = a[i];
        a[i] = a[j];
        a[j] = aux; // swap
        printArrayQuickSort(a, lo,hi+1);
    }
    aux = a[lo];
    a[lo] = a[j];
    a[j] = aux; // swap with partitioning item
    return j; // return index of item now known to be in place
}

int partitionQuicksort_Print(int a[], int lo, int hi) {
    int i = lo, j = hi+1, aux;
    printf("\nPartition QuickSort Basic (BEGIN)\n");
    printf(" a[](BEGIN)="); printArrayQuickSort(a, lo, hi+1);
    while (1) {
        while (a[++i] < a[lo])  // find item on left to swap
            if (i == hi) break;
        while (a[lo] < a[--j]) // find item on right to swap
            if (j == lo) break;
        if (i >= j) break; // check if pointers cross
        aux = a[i]; a[i] = a[j]; a[j] = aux; // swap
        printf(" a[%d]=%d<->a[%d]=%d=",i,a[i],j,a[j]); printArrayQuickSort(a, lo, hi+1);
    }
    aux = a[lo]; a[lo] = a[j]; a[j] = aux; // swap with partitioning item
    printf(" a[](%d<->%d)=",lo,j); printArrayQuickSort(a, lo,hi+1);
    printf("Partition QuickSort Basic (END)\n");
    return j; // return index of item now known to be in place
}

void client_PartitionQuicksort_ex3fev2016(){
    int v[]={150,210,200,900,12,15,180,21}, N=8;
    partitionQuicksort_Print(v, 0, N-1);
}







