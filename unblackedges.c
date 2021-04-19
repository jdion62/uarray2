#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"

#include "pnmrdr.h"

//origin_array is the original array that is read from the file and it is never changed throught the run of the progm
//current_array is the array that we make changes too and eventually output with all blackedges removed
Bit2_T origin_array = NULL;
Bit2_T current_array = NULL;

//outputs array in pbm format to stdout
void bit2_to_pbm(Bit2_T array){
    printf("P1\n");
    printf("%d %d\n",array->width, array->height);
    for(int i=0;i<array->height;i++){
        if(i != 0){
            printf("\n");
        }
        for(int j=0;j<array->width;j++){
            printf("%d",Bit2_get(array, i, j));
        }
    }
}

//removes edges from the first and last column and first and last row. 
Bit2_T remove_first_edges(Bit2_T array){
    int width = array->width;
    int height = array->height;
    //first and last column
    for(int i = 0;i<height;i++){
        int e1;
        int e2;
        e1 = Bit2_get(array, i, 0);
        e2 = Bit2_get(array, i, array->width-1);
        if(e1 == 1){
            Bit2_put(array, i, 0, 0);
        }
        if(e2 == 1){
            Bit2_put(array, i, array->width-1, 0);
        }
    }
    //first and last row
    for(int i=0;i<width;i++){
        int e1;
        int e2;
        e1 = Bit2_get(array, 0, i);
        e2 = Bit2_get(array, array->height-1, i);
        if(e1 == 1){
            Bit2_put(array, 0, i, 0);
        }
        if(e2 == 1){
            Bit2_put(array, array->height-1, i, 0);
        }
    }
    return array;
}


// called after remove_first_edges
//this function compares the values from the origin_array and current_array
//if a pixel is 1 in origin array but 0 in current array we know that that pixel is a blackedge pixel so we set the current pixel to 0 if it is black
void check_if_blackedge(int b, int row, int col){
    //skip the current element if it is in any of the edges since those have been calculated already
    if(row == 0 || col == 0 || row == origin_array->height-1 || col == origin_array->width-1){
        return;
    }
    if(b == 1){
        int o_above = Bit2_get(origin_array, row-1, col);
        int o_below = Bit2_get(origin_array, row+1, col);
        int o_right = Bit2_get(origin_array, row, col+1);
        int o_left  = Bit2_get(origin_array, row, col-1);

        int c_above = Bit2_get(current_array, row-1, col);
        int c_below = Bit2_get(current_array, row+1, col);
        int c_right = Bit2_get(current_array, row, col+1);
        int c_left =  Bit2_get(current_array, row, col-1);
        if((o_above == 1 && c_above == 0) || (o_below == 1 && c_below == 0) || (o_right == 1 && c_right == 0) || (o_left == 1 && c_left == 0)){
            Bit2_put(current_array, row, col, 0);
        }
    }
}

//converts the pnm file into our bit2 format
//this is where current_array and origin_array are 
void pnm_to_bit2(Pnmrdr_T rdr){
    Pnmrdr_mapdata mdata = Pnmrdr_data(rdr);
    int height = mdata.height;
    int width = mdata.width;
    current_array = Bit2_new(height, width);
    origin_array = Bit2_new(height, width);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int n = Pnmrdr_get(rdr);
            Bit2_put(current_array, i, j, n);
            Bit2_put(origin_array, i, j, n);
        }
    } 
}

int main(int argc, char** argv){
    FILE *fp = NULL;
    Pnmrdr_T rdr = NULL;
    if(argc == 2){
        fp = fopen(argv[1], "r");
        if(fp == NULL){
            exit(1);
        }
        rdr = Pnmrdr_new(fp);
    }else if(argc == 1){
        rdr = Pnmrdr_new(stdin);
    }else if(argc > 2){
        exit(1);
    }
    pnm_to_bit2(rdr);
    current_array = remove_first_edges(current_array);
    //we call each map function and the opposite of it because we want to start from each edge since that is where each black edge starts
    Bit2_map_row_major(origin_array, check_if_blackedge);
    Bit2_map_row_major_opp(origin_array, check_if_blackedge);
    Bit2_map_col_major(origin_array, check_if_blackedge);
    Bit2_map_col_major_opp(origin_array, check_if_blackedge);
    //convert current array to pbm format
    bit2_to_pbm(current_array);
    //free memory
    Bit2_free(&current_array);
    Bit2_free(&origin_array);
    if(rdr){
        Pnmrdr_free(&rdr);
    }
    if(fp){
        fclose(fp);
    }
}