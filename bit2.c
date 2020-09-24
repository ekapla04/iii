#include <stdlib.h>
#include <stdio.h>
#include "bit2.h"
#include "bit.h"
#include "uarray.h"
#include "assert.h"
#include "mem.h"

#define T Bit2_T
struct T {
	int width;
	int height;
	UArray_T outer;
};


T Bit2_new (int width, int height)
{
	assert(width > 0);
	assert(height > 0);

	T bit2 = malloc(sizeof(*bit2));
	assert(bit2 != NULL);

	bit2->width = width; // 5
	bit2->height = height; //7
	bit2->outer = UArray_new(height, sizeof(Bit_T));
	for (int i = 0; i < UArray_length(bit2->outer); i++) {
		Bit_T *inner = UArray_at(bit2->outer, i); // returns pointer to space in memory
		*inner = Bit_new(bit2->width);
	}

	return bit2;
}

extern void Bit2_free (T *bit2)
{
	for (int i = 0; i < UArray_length((*bit2)->outer); i++) {
		Bit_T *inner = UArray_at((*bit2)->outer, i);
		Bit_free(inner);
	}

	UArray_free(&((*bit2)->outer));

	free(*bit2);
}

extern int Bit2_get(T bit2, int col, int row)
{
	Bit_T *inner = UArray_at(bit2->outer, row);
	return Bit_get(*inner, col);
}

extern int Bit2_put(T bit2, int col, int row, int element)
{
	Bit_T *inner = UArray_at(bit2->outer, row);
	return Bit_put(*inner, col, element);
}

extern int Bit2_width (T bit2)
{
    assert(bit2 != NULL);
    return bit2->width;
}

extern int Bit2_height (T bit2)
{
    assert(bit2 != NULL);
    return bit2->height;
}

extern void Bit2_map_row_major(
    	T bit2,
    	void apply(int col, int row, T bit2, int element, void* cl),
    	void *cl)
{
	for (int row = 0; row < bit2->height; row++) {
		for (int col = 0; col < bit2->width; col++) {
			apply(col, row, bit2,
			Bit2_get(bit2, col, row), cl);
		}
	}
}

extern void Bit2_map_col_major(
        	T bit2,
        	void apply(int col, int row, T bit2, int element, void* cl),
        	void *cl)
{
	for (int col = 0; col < bit2->width; col++) {
		for (int row = 0; row < bit2->height; row++) {
			apply(col, row, bit2,
			      Bit2_get(bit2, col, row), cl);
		}
	}
}
