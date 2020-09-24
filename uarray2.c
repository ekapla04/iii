#include <stdlib.h>
#include <stdio.h>

#include "uarray2.h"
#include "uarray.h"
#include "assert.h"
#include "mem.h"

#define T UArray2_T
struct T {
	int width;
	int height;
	int size;
	UArray_T outer;
};

T UArray2_new (int width, int height, int size)
{
	assert(width > 0);
	assert(height > 0);
	assert(size > 0);

	T uarray2 = malloc(sizeof(*uarray2));
	assert(uarray2 != NULL);

	uarray2->width = width; // 5
	uarray2->height = height; //7
	uarray2->size = size;
	uarray2->outer = UArray_new(height, sizeof(UArray_T));
	for (int i = 0; i < UArray_length(uarray2->outer); i++) {
		UArray_T *inner = UArray_at(uarray2->outer, i); // returns pointer to space in memory
		*inner = UArray_new(uarray2->width, uarray2->size);
	}

	return uarray2;
}

extern void UArray2_free (T *uarray2)
{
    for (int i = 0; i < UArray_length((*uarray2)->outer); i++) {
        UArray_T *inner = UArray_at((*uarray2)->outer, i);
        UArray_free(inner);
    }

    UArray_free(&((*uarray2)->outer));

    free(*uarray2);
}

extern int UArray2_width (T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->width;
}

extern int UArray2_height (T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->height;
}

extern int UArray2_size (T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->size;
}

extern void *UArray2_at (T uarray2, int col, int row)
{
	UArray_T *inner = UArray_at(uarray2->outer, row);
	return UArray_at(*inner, col);
}

extern void UArray2_map_row_major(
    	T uarray2,
    	void apply(int col, int row, T uarray2, void *element, void* cl),
    	void *cl)
{
	for (int row = 0; row < uarray2->height; row++) {
		for (int col = 0; col < uarray2->width; col++) {
			apply(col, row, uarray2,
			      UArray2_at(uarray2, col, row), cl);
		}
	}
}

extern void UArray2_map_col_major(
        	T uarray2,
        	void apply(int col, int row, T uarray2, void *element, void* cl),
        	void *cl)
{
	for (int col = 0; col < uarray2->width; col++) {
		for (int row = 0; row < uarray2->height; row++) {
			apply(col, row, uarray2,
			      UArray2_at(uarray2, col, row), cl);
		}
	}
}
