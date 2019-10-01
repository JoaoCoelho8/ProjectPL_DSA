//
//  arraysort.h
//  sortarrays_app
//
//  Created by José Manuel Torres on 05/12/14.
//  Copyright (c) 2014 ___JOSETORRES___. All rights reserved.
//

#ifndef __sortarrays_app__arraysort__
#define __sortarrays_app__arraysort__

#include <stdio.h>

#define CUTOFF_MERGESORT 6

void sortSelection(int v[],int N);
void sortInsertion(int v[],int N);
int sortInsertion1(int v[],int N,int flags);
int testSorting(int v[],int N);
int countInversions(int v[],int N);
void listInversions(int v[],int N);
void sortInsertionLH(int v[],int lo, int hi);


/* merge sort */
void mergesort_run(int a[], int n, int flag_cutoff);
void mergesort_recursivo(int a[], int aux[], int lo, int hi);
void mergesort_recursivo_cutoff(int a[], int aux[], int lo, int hi);
void merge_array(int a[], int aux[], int lo, int mid, int hi);
void merge_array_inplace(int a[], int b[], int N);

/* quicksort */
void quicksort(int a[], int lo, int hi);
int partitionQuicksort(int a[], int lo, int hi);
void shuffleArray(int a[], int N);
int partitionQuicksort_Print(int a[], int lo, int hi);


/* Pointer version of array sorting algorithms */
void sortInsertionLH_PInt(int * v[], int lo, int hi);


/* clients */
void clientSortingInsertion_PInt(); // ref sorting

void clientSorting1();
void clientSortingInsertion();
void clientSorting2();
void clientSorting3(); // test mergesort
void clientSorting4(); // test inplace merge
void clientSorting5(); // test quicksort 1
void clientSorting6(); // test quicksort 2
void clientSorting7(); // test quicksort

void client_PartitionQuicksort_ex3fev2016();

#endif /* defined(__sortarrays_app__arraysort__) */
