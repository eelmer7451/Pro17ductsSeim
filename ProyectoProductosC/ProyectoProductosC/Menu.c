#include "Menu.h"

int fMenu(char * mensaje, int min, int max)//Funcion general para los Menus
{
	int opc;
	char c;
	do 
	{
		//system("cls");
		printf("%s", mensaje);
		scanf("%d%c", &opc, &c);
	} while (opc<min || opc>max);
	return opc;
}
