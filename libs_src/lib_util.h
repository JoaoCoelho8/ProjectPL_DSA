//
// Created by arpinto on 19-09-2016.
//

#ifndef AULA1_LIB_UTIL_H
#define AULA1_LIB_UTIL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#if defined _WIN64 || defined _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

int readInts(char * filename, int * intvec, int nmax);
int gettimeuseconds(long long * time_usec);
int uniform(int val_min, int val_max);
double uniform_double(void);
double uniform_double_interval(double val_min, double val_max);
double gaussian_normal(void);
double gaussian(double mean, double stddev);
int readIntsHeader(char * filename, int ** intvec);
void printArray(int* a, int N);
void printArrayQuickSort(int *a, int lo, int hi);



int * newIntArray(int N); // alloc new int array
void freeIntArray(int * v); // frees new int array


char * newCharArray(int N);
void freeCharArray(char * v);


int uniformArray(int * a, int N, int val_min, int val_max); // function to fill an array with integer random uniformly distributed values (returns -1 if error)
int uniformDistinctArray(int * a, int N, int val_min, int val_max); // function to fill an array with integer random uniformly distributed distinct values (returns -1 if error)

int compareIntValues(const void * a, const void * b);
void sortIntArray(int * v, int n);
int binarySearch(int a[], int n, int key);

int writeInts(char * filename, int * intvec, int n);
int writeIntsHeader(char * filename, int * intvec, int n);

#endif //AULA1_LIB_UTIL_H