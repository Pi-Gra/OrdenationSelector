#ifndef SORTING_H
#define  SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

void selection_sort(Vector *v);
void bubble_sort(Vector *v);
void merge_sort(Vector *v);
void heapify(Vector *v, int n, int i);
void heap_sort(Vector *v);

#endif