#include "Consola.h"

void GoToXY(int x, int y) {
	COORD punto;//Structura COORD
	HANDLE h;//Manejador
	punto.X = x;
	punto.Y = y;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, punto);
}