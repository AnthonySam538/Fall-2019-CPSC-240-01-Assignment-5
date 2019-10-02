#include <iostream>

using namespace std;

int i, i2, total;
int a[3][3][2] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 }; //assuming colors are rows, sizes are columns, and sleeves are layers

int main()
{
	//Total number of all shirts
	_asm
	{
		mov i, 0; //i is the amount of numbers that've been added
		mov eax, 0; //eax will hold the total
		lea esi, [a]; //esi = a (load effective address)

	ForLoop:
		cmp i, 18;
		je ExitLoop;

		add eax, [esi];

		inc i;
		add esi, 4; //increment by 4 since integers are 4 bytes
		jmp ForLoop;
	ExitLoop:
		mov total, eax;
	}
	cout << "Total number of shirts: " << total << endl;

	//Total number of medium size shirts
	_asm
	{
		mov eax, 0;
		lea esi, [a];
		add esi, 8; //start at the first medium shirt

		mov i, 0; //i is used for color
	ForLoopM:
		cmp i, 3;
		je ExitForLoopM;

		mov i2, 0; //i2 is used for the inner loop, sleeves
	ForLoopM2:
		cmp i2, 2;
		je ExitForLoopM2;

		add eax, [esi];

		inc i2;
		add esi, 4;
		jmp ForLoopM2;
	ExitForLoopM2:
		inc i;
		add esi, 16; //1 layer: shift 2 | 2 layers: shift 4 | 3 layers: shift 6 | 4 layers: shift 8 | 5 layers: shift 10
		jmp ForLoopM;
	ExitForLoopM:
		mov total, eax;
	}
	cout << "Total number of medium shirts: " << total << endl;

	//Total number of short sleeves shirts
	_asm
	{
		mov i, 0; //i is the amount of numbers added
		mov eax, 0;
		lea esi, [a];

	ForLoopS:
		cmp i, 9;
		je ExitForLoopS;

		add eax, [esi];

		inc i;
		add esi, 8;
		jmp ForLoopS;
	ExitForLoopS:
		mov total, eax;
	}
	cout << "Total number of short sleeves shirts: " << total << endl;

	//Total number of red shirts
	_asm
	{
		mov i, 0; //i is the amount of numbers added
		mov eax, 0;
		lea esi, [a];

	ForLoopR:
		cmp i, 6;
		je ExitForLoopR;

		add eax, [esi];

		inc i;
		add esi, 4;
		jmp ForLoopR;
	ExitForLoopR:
		mov total, eax;
	}
	cout << "Total number of red shirts: " << total << endl;

	return 0;
}

// [0]	[0]	[0]	Red,   Small,  Short Sleeve		esi+0
// [0]	[0]	[1]	Red,   Small,  Long Sleeve		esi+4
// [0]	[1]	[0]	Red,   Medium, Short Sleeve		esi+8
// [0]	[1]	[1]	Red,   Medium, Long Sleeve		esi+12
// [0]	[2]	[0]	Red,   Large,  Short Sleeve		esi+16
// [0]	[2]	[1]	Red,   Large,  Long Sleeve		esi+20
// [1]	[0]	[0]	Blue,  Small,  Short Sleeve		esi+24
// [1]	[0]	[1]	Blue,  Small,  Long Sleeve		esi+28
// [1]	[1]	[0]	Blue,  Medium, Short Sleeve		esi+32
// [1]	[1]	[1]	Blue,  Medium, Long Sleeve		esi+36
// [1]	[2]	[0]	Blue,  Large,  Short Sleeve		esi+40
// [1]	[2]	[1]	Blue,  Large,  Long Sleeve		esi+44
// [2]	[0]	[0]	Black, Small,  Short Sleeve		esi+48
// [2]	[0]	[1]	Black, Small,  Long Sleeve		esi+52
// [2]	[1]	[0]	Black, Medium, Short Sleeve		esi+56
// [2]	[1]	[1]	Black, Medium, Long Sleeve		esi+60
// [2]	[2]	[0]	Black, Large,  Short Sleeve		esi+64
// [2]	[2]	[1]	Black, Large,  Long Sleeve		esi+68

// 4*6	4*2	4*1 (To get the second number, count the number of 0s at the very top of the column)
// 24	8	4