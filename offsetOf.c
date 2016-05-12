#include <stdio.h>

/*
 * This macro takes two parameters: the first is the structure name, and the second is
 * the name of a member within that same structure. Returns the position in bytes of the
 * member from the beginning of the estructure.
 *
 * 1) (myStruct *)0 Takes the integer zero and casts it as a pointer to "myStruct".
 * 2) ((myStruct *)0)->structMember Dereferences that pointer to point to structure member "structMember".
 * 3) &(((myStruct *)0)->structMember) Computes the address of "structMember".
 * 4) (size_t)&(((myStruct *)0)->structMember) Casts the result to an appropriate data type.
 */
#define offsetOf(myStruct, structMember) (size_t)&(((myStruct *)0)->structMember)

/* User structure */
struct S {
	int field1;
	float field2;
	char field3[10];
	char field4;
};

int main(void) {
	size_t pos = offsetOf(struct S, field3);

	printf("The member \"field3\" begins in the byte %d within the 'S' structure.\n", pos);
	return 0;
}

/*										WIKIPEDIA
Bit-fields are used to define the class members that can occupy less storage than an integral
type. This field is applicable only for integral types (int, char, short, long, etc.) and excludes
float or double.

struct A { 
	unsigned a:2; // Possible values 0..3, occupies first 2 bits of int
	unsigned b:3; // Possible values 0..7, occupies next 3 bits of int
	unsigned :0;  // Moves to end of next integral type
	unsigned c:2; 
	unsigned :4;  // Pads 4 bits in between c & d
	unsigned d:1;
	unsigned e:3;
};

Memory structure:

 4 byte int  4 byte int
[1][2][3][4][5][6][7][8]

[1]                      [2]                      [3]                      [4]
[a][a][b][b][b][ ][ ][ ] [ ][ ][ ][ ][ ][ ][ ][ ] [ ][ ][ ][ ][ ][ ][ ][ ] [ ][ ][ ][ ][ ][ ][ ][ ]

[5]                      [6]                      [7]                      [8]
[c][c][ ][ ][ ][ ][d][e] [e][e][ ][ ][ ][ ][ ][ ] [ ][ ][ ][ ][ ][ ][ ][ ] [ ][ ][ ][ ][ ][ ][ ][ ]
*/

/*										PREGUNTA
¿Es posible utilizar esta macro con estructuras que contengan bit-fields? ¿Porque?

You cannot apply the address operator (&) or the offsetOf macro to a bit-field. Bit-fields generally
do not occupy an addressable location in memory. 
*/