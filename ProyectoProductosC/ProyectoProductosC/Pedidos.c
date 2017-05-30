#include "Pedidos.h"

void fFormularioPedido()
{
	printf("\t\tFICHERO DE PEDIDOS\n\n");
	printf("Nº Cliente: ");
	printf("\n\n%12s  %20s  %10s  %10s\n","Nº Articulo","Denominacion","P.V.P.","Cantidad");
}

void fAgregarPedido()
{
	system("cls");
	FILE *cpf, *apf, *ppf;
	CLIENTE regCliente;
	ARTICULO regArticulo;
	PEDIDO regPedido;
	int nCliente, nArticulo,numLineas=0;
	char c;
	cpf = fopen(RUTAFICHEROCLIENTES, "rb");
	if (cpf == NULL)
	{
		printf("Error al abrir el fichero %s", RUTAFICHEROCLIENTES);
		getch();
		return;
	}
	apf = fopen(RUTAARTICULOS, "rb");
	if (apf == NULL)
	{
		printf("Error al abrir el fichero %s", RUTAARTICULOS);
		getch();
		fclose(cpf);
		return;
	}
	ppf = fopen(RUTAPEDIDOS, "ab+");
	if (ppf == NULL)
	{
		printf("Error al abrir el fichero %s", RUTAPEDIDOS);
		getch();
		fclose(cpf);
		fclose(apf);
		return;
	}
	fFormularioPedido();
	nCliente = fPedirCliente(cpf,numLineas);
	while (nCliente != 0)
	{
		fseek(cpf, (nCliente - 1) * sizeof(regCliente), SEEK_SET);
		fread(&regCliente, sizeof(regCliente), 1, cpf);
		regPedido.nCliente = regCliente.nCliente;
		GoToXY(18, 2);
		printf("%s", regCliente.nombre);
		nArticulo = fPedirArticulo(apf,numLineas);
		while (nArticulo != 0)
		{
			fseek(apf, (nArticulo - 1) * sizeof(regArticulo), SEEK_SET);
			fread(&regArticulo, sizeof(regArticulo), 1, apf);
			regPedido.nArticulo = regArticulo.nArticulo;
			regPedido.pvp = regArticulo.pvp;
			GoToXY(0, numLineas + 5);
			printf("%12d  %20s  %8.2f  ", regArticulo.nArticulo, regArticulo.denominacion, regArticulo.pvp);
			GoToXY(2, numLineas + 7);
			printf("Introduce la cantidad.");
			GoToXY(47, numLineas + 5);
			scanf("%d%c", &regPedido.cantidad, &c);
			GoToXY(2, numLineas + 7);
			printf("%100s", "");
			GoToXY(2, numLineas + 7);
			printf("¿Estas conforme? ");
			c = tolower(getch());
			if (c == 's')
			{
				fwrite(&regPedido, sizeof(regPedido), 1, ppf);
				GoToXY(2, numLineas + 7);
				printf("%100s", "");
				numLineas++;
				GoToXY(2, numLineas + 7);
				printf("La linea guardada correctamente");
				getch();
			}
			else
			{
				GoToXY(2, numLineas + 5);
				printf("%100s", "");
				GoToXY(2, numLineas + 7);
				printf("La linea no ha sido guardada");
				getch();
			}
			nArticulo = fPedirArticulo(apf,numLineas);
		}
		nCliente = fPedirCliente(cpf,numLineas);
	}
	fclose(cpf);
	fclose(apf);
	fclose(ppf);
}

int fPedirCliente(FILE *pf, int linea)
{
	int opc;
	char c;
	do
	{
		GoToXY(11, 2);
		scanf("%d%c", &opc, &c);
		if (opc > fCalcularTamanoFicheroCliente(pf))
		{
			GoToXY(2, linea + 7);
			printf("Cliente no disponible. Elige otro o pulsa 0 para salir.");
			getch();
		}
	}while (opc<0 || opc>fCalcularTamanoFicheroCliente(pf));
	return opc;
}

int fPedirArticulo(FILE * pf,int linea)
{
	int opc;
	char c;
	do
	{
		GoToXY(2, linea + 5);
		scanf("%d%c", &opc, &c);
		if (opc > fCalcularTamanoFicheroArticulos(pf))
		{
			GoToXY(2, linea + 7);
			printf("Articulo no disponible. Elige otro o pulsa 0 para salir.");
			getch();
		}
	} while (opc<0 || opc>fCalcularTamanoFicheroArticulos(pf));
	return opc;
}

int fCalcularTamanoFicheroPedidos(FILE * pf)
{
	int tamArchivo, tamFinal, tamInicio;
	PEDIDO reg;
	fseek(pf, 0, SEEK_END);
	tamFinal = ftell(pf);
	fseek(pf, 0, SEEK_SET);
	tamInicio = ftell(pf);
	tamArchivo = (tamFinal - tamInicio) / sizeof(reg);
	return tamArchivo;
}

int fExisteFicheroPedidos()
{
	FILE *pf;
	int i;
	pf = fopen(RUTAPEDIDOS, "rb");
	if (pf == NULL)
	{
		system("cls");
		printf("No hay pedidos que facturar.\n");
		getch();
		return 0;
	}
	else
	{
		fclose(pf);
		return 1;
	}
}
