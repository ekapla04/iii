#ifndef UARRAY2_INCLUDED_
#define UARRAY2_INCLUDED_

#define T UArray2_T
typedef struct T *T;

/* Purpose : Create 2D Uarray by allocating memory for outer and inner
 *       	arrays. Iterates across outer array to intialize each element to
 *       	a Uarray
 * Arguments : Width (number of columns), height (number of rows), size
 *         	(intended size of each element)
 * Returns : A Uarray2
 * Notes : Assert that width and height are greater than 0. Assert that size is
 * 		   greater than 0.
 */
extern T UArray2_new (int width, int height, int size);

/* Purpose : Deallocate memory used for storing Uarray2. Iterate through
 *       	outer Uarray to free the elements of the inner array before
 *  	     freeing the elements of the outer array.
 * Arguments : Pointer to a Uarray2
 * Returns : Nothing
 * Notes : Assert that pointer is not
 */
extern void UArray2_free (T *uarray2);

/* Purpose : Checks width (number of columns) of Uarray2. Serves as public
 *       	"getter" function for width.
 * Arguments : Uarray2
 * Returns : Int representing number of columns
 * Notes : Assert that Uarray2 isnt null
 */
extern int UArray2_width (T uarray2);

/* Purpose : Checks height (number of rows) of Uarray2. Serves as public
 *       	"getter" function for height.
 * Arguments : Uarray2
 * Returns : Int representing number of rows
 * Notes : Assert that Uarray2 isnt null
 */
extern int UArray2_height (T uarray2);


/* Purpose : Checks size of Uarray2. Serves as public "getter" function for
 *       	size.
 * Arguments : Uarray2
 * Returns : Int representing size of Uarray.
 * Notes : Assert that Uarray2 isnt null
 */
extern int UArray2_size (T uarray2);

/* Purpose : Finds element stored at index of Uarray2. Uarray_at as a helper
 *       	function to access element in outer Uarray and then inner
 *       	Uarray.
 * Arguments : Uarray2, row and column of interest
 * Returns : Void pointer to element in Uarray2
 * Notes : Assert that row and columns are within the bounds of the Uarray2.
 *     	Assert that Uarray2 isnt null.
 */
extern void *UArray2_at (T uarray2, int col, int row);

/* Purpose : Mapping function that iterates through every element of Uarray2
 *           and calls apply function for each element. Iterates through rows
 *           before columns.
 * Arguments : Uarray2, Function pointer, closure
 * Returns : Nothing
 * Notes : Assert that Uarray isnt null. Assert that function is not null.
 */
extern void UArray2_map_row_major(
    	T uarray2,
    	void apply(int col, int row, T uarray2, void *element, void* cl),
    	void *cl);

/* Purpose : Mapping function that iterates through every element of Uarray2
 *       	and calls apply function for each element. Iterates through
 *       	columns before rows.
 * Arguments : Uarray2, Function pointer, closure
 * Returns : Nothing
 * Notes : Assert that Uarray isnt null. Assert that function is not null.
 */
extern void UArray2_map_col_major(
        	T uarray2,
        	void apply(int col, int row, T uarray2, void *element, void* cl),
        	void *cl);

#undef T
#endif
