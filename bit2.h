#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#include "bit.h"


typedef struct Bit2_T *Bit2_T;

struct Bit2_T {
    int width;
    int height;
    Bit_T array;
};
extern Bit2_T Bit2_new(int height, int width);
extern void Bit2_free(Bit2_T *Bit2);

extern int Bit2_height(Bit2_T Bit2);
extern int Bit2_width(Bit2_T Bit2);

extern int Bit2_get(Bit2_T Bit2, int row, int col);
extern int Bit2_put(Bit2_T Bit2, int row, int col, int bit);

extern void Bit2_map_col_major(Bit2_T Bit2, void (*func)(int, int, int));
extern void Bit2_map_row_major(Bit2_T Bit2, void (*func)(int, int, int));
extern void Bit2_map_row_major_opp(Bit2_T Bit2, void (*func)(int, int, int));
extern void Bit2_map_col_major_opp(Bit2_T Bit2, void (*func)(int, int, int));

#endif