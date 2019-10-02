#include <iostream>

using namespace std;

int i, total;
int b[4][4] = { 10, 20, 30, 40,
				20, 10, 40, 30,
				 5, 15, 20, 25,
				30, 25, 20, 15 };

int main()
{
	//Compute the total number of all shirts
	_asm
	{
		mov i, 0; //i is the amount of numbers that have been added
		mov eax, 0; //eax will hold our total for the time being
		lea esi, [b]; //esi = b  (load effective address)

	ForLoop:
		cmp i, 16; //if 16 numbers have been added by now, exit the loop
		je ExitLoop;

		add eax, [esi]; //add the current element

		inc i;
		add esi, 4; //increment esi by 4 since int-type variables take up 4 bytes
		jmp ForLoop;
	ExitLoop:
		mov total, eax;
	}
	cout << "Total number of shirts: " << total << endl;

	//Compute the total number of medium shirts
	_asm
	{
		mov i, 0;
		mov eax, 0;
		lea esi, [b];
		add esi, 4; //start at Row: 0 Column: 1

	ForLoop2:
		cmp i, 4;
		je ExitLoop2;

		add eax, [esi];

		inc i;
		add esi, 16; //increment row number
		jmp ForLoop2;
	ExitLoop2:
		mov total, eax;
	}
	cout << "Total number of medium shirts: " << total << endl;

	//Compute the total number of blue shirts
	_asm
	{
		mov i, 0;
		mov eax, 0;
		lea esi, [b];
		add esi, 32;

	ForLoop3:
		cmp i, 4;
		je ExitLoop3;

		add eax, [esi];

		inc i;
		add esi, 4; //increment column
		jmp ForLoop3;
	ExitLoop3:
		mov total, eax;
	}
	cout << "Total number of blue shirts: " << total << endl;

	return 0;
}
