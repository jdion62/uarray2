#include <stdlib.h>
#include <stdio.h>
#include "pnmrdr.h"
#include "uarray2.h"

//checks rows for repeats
void check_rows(UArray2_T a){
    int *current_element; //the current element that is compared against every element in the current row
    int *checking_element; 
    for(int i=0;i<a->height;i++){
        for(int j=0;j<a->width;j++){
            current_element = UArray2_at(a, i, j);
            for(int c = 0;c<a->width;c++){
                if(c != j){
                    checking_element = UArray2_at(a, i, c);
                    if(*current_element == *checking_element){ //exit(1) if a match is found
                        exit(1);
                    }
                }
            }
        }
    }
}

//checks columns for repeats
void check_cols(UArray2_T a){
    int *current_element;  //the current element that is compared against every element in the current column
    int *checking_element;
    for(int i=0;i<a->width;i++){
        for(int j=0;j<a->height;j++){
            current_element = UArray2_at(a, j, i);
            for(int c = 0;c<a->height;c++){
                if(c != j){
                    checking_element = UArray2_at(a, c, i);
                    if(*current_element == *checking_element){ //exit(1) if a match is found
                        exit(1);
                    }
                }
            }
        }
    }
}

//seperates the matrix into 3x3 
void check_3by3(UArray2_T a){
    for(int i=0;i<a->height;i++){
        for(int j=0;j<a->width;j++){
            int *current_element = UArray2_at(a, i, j); //the current element that is compared against every element in the current column
            int num_curr = 0; //counts number of occurences of the current elemenet in the 3x3.  WE do this so we dont have to worry about keeping track of where the current element is.
            for(int ii=0;ii<3;ii++){
                for(int jj=0;jj<3;jj++){
                    int *checking_element = UArray2_at(a, (i-i%3)+ii, (j-j%3)+jj);
                    if(*current_element == *checking_element){
                        num_curr++;
                    }
                    if(num_curr>1){ //exit 1 if we hit the current number more then once
                        exit(1);
                    }
                }
            }
        }
    }
}

//simple function that just calls each check function
void check_solution(UArray2_T a){
    check_3by3(a);
    check_rows(a);
    check_cols(a);
}

//converts the pnm to a uarray2_T
UArray2_T pnm_to_2darray(Pnmrdr_T rdr){
    Pnmrdr_mapdata mdata = Pnmrdr_data(rdr);
    if(mdata.height != 9 || mdata.width != 9 || mdata.denominator != 9){
        exit(1);
    }
    int height = mdata.height;
    int width = mdata.width;
    UArray2_T array = UArray2_new(height, width, sizeof(int));
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int *e = UArray2_at(array, i, j);
            int n = Pnmrdr_get(rdr);
            if(n > 9 || n < 1){
                exit(1);
            }
            *e = n;
        }
    } 
    return array;
}

int main(int argc, char** argv){
    FILE *fp = NULL;
    if(argc == 1){
        char buffer[2050];
        char* str = fgets(buffer, 1025, stdin);
        char *newlinecheck = strchr(str, '\n');
        if (newlinecheck)
            *newlinecheck = '\0';
        fp=fopen(str,"r");
    }else if(argc == 2){
        fp = fopen(argv[1], "r");
    }else if(argc > 2){
        exit(1);
    }
    if (fp == NULL){
        exit(1);
    }
    Pnmrdr_T rdr = Pnmrdr_new(fp);
    if(rdr == NULL){
        exit(1);
    }
    UArray2_T array = pnm_to_2darray(rdr);
    if(fp){
        fclose(fp);
    }
    check_solution(array);
    UArray2_free(&array);
    Pnmrdr_free(&rdr);
    exit(0);
}