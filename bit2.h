#ifndef BIT2_INCLUDED_
#define BIT2_INCLUDED_


#define T Bit2_T
typedef struct T *T;


extern T Bit2_new (int width, int height);
extern void Bit2_free (T *bit2);
extern int Bit2_width (T bit2);
extern int Bit2_height (T bit2);
extern void Bit2_map_row_major( T bit2,
        	void apply(int row, int col, T bit2, int bit, void* cl),
        	void *cl
);
extern void Bit2_map_col_major(T bit2,
        	void apply(int row, int col, T bit2, int bit, void* cl),
        	void *cl
);

/* Purpose : Public "setter" function to insert bit into bit vector
 * Arguments : Bit2, row, column, element/bit that we want to set
 * Returns : Integer representing the previous value of the bit
 * Notes : Assert that Bit2 isnt null and that element is 1 or 0 and
 *     	is to be inserted within the bounds of the vector.
 */
extern int Bit2_put(T bit2, int col, int row, int element);

/* Purpose : Public "getter" function to return bit from bit vector
 * Arguments : Bit2, row, column, element/bit that we want to get
 * Returns : Integer representing the bit of interest
 * Notes : Assert that Bit2 isnt null and that index of interest is within
 *     	bounds of vector.
 */
extern int Bit2_get(T bit2, int col, int row);

#undef T
#endif
