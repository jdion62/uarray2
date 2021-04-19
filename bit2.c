#include <stdlib.h>
#include <stdio.h>
#include "bit2.h"

Bit2_T Bit2_new(int height, int width){
    Bit_T a = Bit_new(height*width);
    Bit2_T bit2 = malloc(sizeof(Bit2_T) + ((height*width) * sizeof(int)));
    bit2->height = height;
    bit2->width = width;
    bit2->array = a;
    return bit2;
}

void Bit2_free(Bit2_T *Bit2){
    Bit_free(&(*Bit2)->array);
    free(*Bit2);
}

int Bit2_get(Bit2_T Bit2, int row, int col){
    if(row > Bit2->height-1 || row < 0 || col > Bit2->width || col < 0){
        fprintf(stderr, "Invalid index");
        exit(EXIT_FAILURE);
    }
    int b = Bit_get(Bit2->array, (row*Bit2->width) + col);
    return b;
}

int Bit2_put(Bit2_T Bit2, int row, int col, int bit){
    if(row > Bit2->height-1 || row < 0 || col > Bit2->width || col < 0){
        fprintf(stderr, "Invalid index");
        exit(EXIT_FAILURE);
    }
     int b = Bit_put(Bit2->array, (row*Bit2->width) + col, bit);
     return b;
}

int Bit2_height(Bit2_T Bit2){
    return Bit2->height;
}

int Bit2_width(Bit2_T Bit2){
    return Bit2->width;
}

//column major loop
void Bit2_map_col_major(Bit2_T Bit2, void (*func)(int, int, int)){
    Bit_T a = Bit2->array;
    for(int i = 0;i<Bit2->width;i++){ //column
        for(int j=0;j<Bit2->height;j++){ //row
            int index = (j*Bit2->width) + i;
            int e = Bit_get(a, index);
            func(e, j, i);  //pass in element then row then index
        }
    }
}

//row major loop
void Bit2_map_row_major(Bit2_T Bit2, void (*func)(int, int, int)){
    Bit_T a = Bit2->array;
    for(int i = 0;i<Bit2->height;i++){ //row
        for(int j=0;j<Bit2->width;j++){ //column
            int index = (i*Bit2->width) + j;
            int e = Bit_get(a, index);
            func(e, i, j); //pass in element then row then index
        }
    }
}

//row major opposite loop
void Bit2_map_row_major_opp(Bit2_T Bit2, void (*func)(int, int, int)){
    Bit_T a = Bit2->array;
    for(int i = Bit2->height-1;i>-1;i--){ //row
        for(int j=Bit2->width-1;j>-1;j--){ //column
            int index = (i*Bit2->width) + j;
            int e = Bit_get(a, index);  //pass in element then row then index
            func(e, i, j);
        }
    }
}

//column major opposite loop
void Bit2_map_col_major_opp(Bit2_T Bit2, void (*func)(int, int, int)){
    Bit_T a = Bit2->array;
    for(int i = Bit2->width-1;i>-1;i--){ //width
        for(int j=Bit2->height-1;j>-1;j--){ //height
            int index = (j*Bit2->width) + i;
            int e = Bit_get(a, index);  //pass in element then row then index
            func(e, j, i);
        }
    }
}