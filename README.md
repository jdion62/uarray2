# uarray2
An implementation of an array using Hanson's Interface

Made in collaboration with Jason Gwozdz

Jason Gwozdz Jacob Dion

we didnt recieve any help to get our specific solutions

everything has been correctly implemented

1. What is the abstract thing you’re trying to represent?
We are trying to represent a two dimensional array within Hanson’s Interface. Bit2_T, as
it will be called, will represent a table-like format to store data in two dimensions and
will hold Hanson’s Bit_T type as a way to store its contents.
2. What are the functions that you will offer and what are the contracts of that those
functions must meet?
● Bit_T Bit2_new(int height, int width); will be used to allocate memory for an
array and return a the created array.
● void Bit2_free(Bit_T a); will be used to free the allocated memory that array a
currently takes up.
● int Bit2_width(Bit2_T a); will be used to receive the width (number of columns)
in the array a.
● int Bit2_height(Bit2_T a); will be used to receive the height (number of rows) in
the array a.
● int Bit2_get(Bit_T a, int row, int col); points to the element in array a at position
row, col and return the value of that element.
● int Bit2_put(Bit_T a, int row, int col, int bit); points to the element in array a at
position row, col and changes the value of that element to ‘bit’ and returns the
previous value of the element.
● void Bit2_map_col_major(Bit2_T a, void (*func)(int, int, int))); calls the func function
on every element in array a in order of columns top to bottom, left to right.  The element is passed and the row an column are passed

● void Bit2_map_row_major(Bit2_T a, void (*func)(int, int, int)); calls the func function
on every element in array a in order of rows left to right, top to bottom.  The element is passed and the row an column are passed

● void Bit2_map_col_major_opp(Bit2_T a, void (*func)(int, int, int))); calls the func function
on every element in array a in order of columns top to bottom, left to right starting from the end.  The element is passed and the row an column are passed

● void Bit2_map_row_major_opp(Bit2_T a, void (*func)(int, int, int)); calls the func function
on every element in array a in order of rows left to right, top to bottom starting from the end.  The element is passed and the row an column are passed

3. What examples do you have of what the functions are supposed to do?
Bit2_T a = Bit2_new(4, 5); //creates a 2d array of height 4 and width 5 with the
inner arrays elements being the size of a char
int w = Bit2_width(a); // returns the width of a (should be 5)
int h = Bit2_height(a); // returns the height of a (should be 4)
char c = Bit2_at(a, 1, 2); // returns a pointer to the the 3rd element in the 2nd array
Bit2_map_row_major(a, func); // calls the passed function in each element in the
array in a row major order.
Bit2_map_col_major(a, func); // calls the passed function in each element in the
array in a col major order
Bit2_free(a); //frees the pointers in the inner arrays and the outer array
4. What representation will you use, and what invariants will it satisfy?
We will use a row major 2d array representation.
Invariants:
● The arrays total length will always be height * width.
● The size of the elements in the array will always be the same (now 1 bit)
● An element at position (row, col) will be stored in the array at position
(row * width + col)
5. When a representation satisfies all invariants, what abstract thing from step [<-] does it
represent?
All invariants will be satisfied once a Bit2_T is declared and initialized. Once this happens, the
size of the elements, and the length and width of the array will be set and remain that way until
freed.
6. What test cases have you devised?
7. What programming idioms will you need?
● The idiom for allocating and initializing pointers to structures
● The idiom for accessing elements in a 1D array as if it were a 2D arrays

1. What is the abstract thing you’re trying to represent?
We are trying to represent a two dimensional array within Hanson’s Interface.
UArray2_T, as it will be called, will represent a table-like format to store data in two
dimensions and will hold any type handed to it into Hanson’s UArray_T type.
2. What are the functions that you will offer and what are the contracts of that those
functions must meet?
- UArray2_T UArray2_new(int height, int width, int size); will be used to allocate
memory for an array and return a the created array.
- void UArray2_free(UArray_T a); will be used to free the allocated memory that
array a currently takes up.
- int UArray2_width(UArray2_T a); will be used to receive the width (number of
columns) in the array a.
- int UArray2_height(UArray2_T a); will be used to receive the height (number of
rows) in the array a.
- int UArray2_size(UArray2_T a); will be used to receive the size of each element
in the array a.
- void* UArray2_at(UArray_T a, int row, int col); points to the element in array a
at position row, col and return a pointer to that element.
- void UArray2_map_col_major(UArray2_T a, void (*func)(void*, int, int)); calls the func
function on every element in array a in order of columns top to bottom, left to
right.  passes the current element and the row and column to the function
- void UArray2_map_row_major(UArray2_T a, void (*func)(void*,int, int)); calls the func
function on every element in array a in order of rows left to right, top to bottom. passes the current element and the row and column to the function
3. What examples do you have of what the functions are supposed to do?
UArray2_T a = UArray2_new(4, 5, sizeof(char)); //creates a 2d array of height 4
and width 5 with the inner arrays elements being the size of a char
int w = UArray2_width(a); // returns the width of a
int h = UArray2_height(a); // returns the height of a
int s = UArray2_size(a); // returns the size of the elements in the inner array of a
char* c = Uarray2_at(a, 1, 2); // returns a pointer to the the 3rd element in the 2nd
array
*c = ‘c’; //sets c, and therefore the 3rd element in the 2nd array, to the letter ‘c’
UArray2_map_row_major(a, func); // calls the passed function in each element in
the array in a row major order.
UArray2_map_col_major(a, func); // calls the passed function in each element in
the array in a col major order
UArray2_free(a); //frees the pointers in the inner arrays and the outer array
4. What representation will you use, and what invariants will it satisfy?

We will use a row major 2d array representation.
Invariants:
● The arrays total length will always be height * width.
● The size of the elements in the array will always be the same
● An element at position (row, col) will be stored in the array at position
(row * width + col)
5. When a representation satisfies all invariants, what abstract thing from step [<-] does it
represent?
All invariants will be satisfied once a UArray2_T is declared and initialized. Once this happens,
the size of the elements, and the length and width of the array will be set and remain that way
until freed.
6. What test cases have you devised?
7. What programming idioms will you need?
● The idiom for allocating and initializing pointers to structures
● The idiom for accessing elements in a 1D array as if it were a 2D array

hours spent: 15

