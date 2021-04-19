
#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#include "array.h"


typedef struct UArray2_T *UArray2_T;

struct UArray2_T {
    int width;
    int height;
    int size;
    Array_T array;
};
extern UArray2_T UArray2_new(int height, int width, int size);
extern void UArray2_free(UArray2_T *uarray2);

extern int UArray2_height(UArray2_T uarray2);
extern int UArray2_width(UArray2_T uarray2);
extern int UArray2_size(UArray2_T uarray2);

extern void* UArray2_at(UArray2_T uarray2, int row, int col);

extern void UArray2_map_col_major(UArray2_T uarray2, void (*func)(void*, int, int));
extern void UArray2_map_row_major(UArray2_T UArray2, void (*func)(void*, int, int));

#endif