#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uarray2.h"


UArray2_T UArray2_new(int height, int width, int size){
    if(height == 0 || width == 0){
        return NULL;
    }
    Array_T a = Array_new(height*width, size);
    UArray2_T uarray2 = malloc(sizeof(UArray2_T) + (height*width)*size);
    uarray2->height = height;
    uarray2->width = width;
    uarray2->array = a;
    uarray2->size = size;
    return uarray2;
}

void UArray2_free(UArray2_T *uarray2){
    Array_free(&(*uarray2)->array);
    free(*uarray2);
}

int UArray2_width(UArray2_T uarray2){
    return uarray2->width;
}

int UArray2_height(UArray2_T uarray2){
    return uarray2->height;
}

int UArray2_size(UArray2_T uarray2){
    return Array_size((uarray2->array));
}

void* UArray2_at(UArray2_T uarray2, int row, int col){
    if(row > uarray2->height-1 || row < 0 || col < 0 || col > uarray2->width-1){
        fprintf(stderr, "Invalid index");
        exit(EXIT_FAILURE);
    }
    Array_T a = (uarray2)->array;
    int index = ((row * uarray2->width) + col);
    return(Array_get(a, index));
}

void UArray2_map_col_major(UArray2_T uarray2, void (*func)(void*, int, int)){
    Array_T a = uarray2->array;
    for(int i = 0;i<uarray2->width;i++){ //col
        for(int j=0;j<uarray2->height;j++){ //row
            int index = (j*uarray2->width) + i;
            void* e = Array_get(a, index);
            func(e, j, i);
        }
    }
}

void UArray2_map_row_major(UArray2_T UArray2, void (*func)(void*, int, int)){
    Array_T a = UArray2->array;
    for(int i = 0;i<UArray2->height;i++){ //row
        for(int j=0;j<UArray2->width;j++){ //column
            int index = (i*UArray2->width) + j;
            void* e = Array_get(a, index);
            func(e, i, j);
        }
    }
}