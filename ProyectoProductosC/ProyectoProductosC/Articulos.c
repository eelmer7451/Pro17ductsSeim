#include "Articulos.h"

void fFormularioArticulo()
{
	system("cls");
	printf("\t\tFICHERO DE ARTICULOS\n\n");
	printf("Nº Articulo   \t: \n");
	printf("Denominacion  \t: \n");
	printf("Precio Coste  \t: \n");
	printf("P.V.P.        \t: \n");
}

void fExisteFicheroArticulos()
{
	FILE *pf;
	char c;
	pf = fopen(RUTAARTICULOS, "rb");
	if (pf == NULL)
	{
		printf("El archivo de Articulos no existe.\n");
		printf("¿Quieres crearlo? ");
		c = tolower(getch());
		if (c == 's')
			pf = fopen(RUTAARTICULOS, "wb");
		fclose(pf);
		return;
	}
	printf("El archivo de Articulos existe.");
	fclose(pf);
}


int fCalcularTamanoFicheroArticulos(FILE * pf)
{
	int tamArchivo, tamFinal, tamInicio;
	ARTICULO reg;
	fseek(pf, 0, SEEK_END);
	tamFinal = ftell(pf);
	fseek(pf, 0, SEEK_SET);
	tamInicio = ftell(pf);
	tamArchivo = (tamFinal - tamInicio) / sizeof(reg);
	return tamArchivo;
}

int fCalcularNumeroArticulo(FILE * pf)
{
	ARTICULO reg;
	int id = -1, i, tamArchivo;
	tamArchivo = fCalcularTamanoFicheroArticulos(pf);
	for (i = 0; i < tamArchivo && id == -1; i++) {
		fread(&reg, sizeof(reg), 1, pf);
		if (reg.estado == 0) {
			id = i;
		}
	}
	if (id == -1)
		id = i;
	return id;
}

void fAltaArticulo()
{
	FILE *pf;
	ARTICULO reg;
	char c;
	pf = fopen(RUTAARTICULOS, "rb+");
	if (pf == NULL) {
		printf("ERROR al abrir el archivo");
		getch();
		return;
	}
	reg.nArticulo = fCalcularNumeroArticulo(pf);
	reg.estado = 1;
	fFormularioArticulo();
	GoToXY(19, 2);
	printf("%d", reg.nArticulo);
	GoToXY(19, 3);
	gets(reg.denominacion);
	GoToXY(19, 4);
	scanf("%f%c", &reg.precioCoste, &c);
	GoToXY(19, 5);
	scanf("%f,%c", &reg.pvp, &c);
	fseek(pf, reg.nArticulo * sizeof(reg), SEEK_SET);
	fwrite(&reg, sizeof(reg), 1, pf);
	fclose(pf);
}

void fBajaArticulo()
{
	FILE *pf;
	ARTICULO reg;
	int nArticulo; char confirmacion;
	pf = fopen(RUTAARTICULOS, "rb+");
	if (pf == NULL) {
		printf("ERROR al abrir el archivo");
		getch();
		return;
	}
	nArticulo = fPedirPosArticulo(pf);
	fseek(pf, (nArticulo - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado != 0) {
		system("cls");
		printf("\t\tArticulo");
		printf("\tNumero Articulo: %d\tNombre: %s\n", reg.nArticulo, reg.denominacion);
		printf("¿Estas seguro que quieres borrar el cliente? ");
		confirmacion = tolower(getche());
		if (confirmacion == 's') {
			reg.estado = 0;
			fseek(pf, (nArticulo - 1) * sizeof(reg), SEEK_SET);
			fwrite(&reg, sizeof(reg), 1, pf);
			printf("El articulo se ha eliminado correctamente.\n");
			getch();
		}
	}
	else {
		printf("El articulo seleccionado no existe");
		getch();
	}
	fclose(pf);
}

void fModificarArticulo()
{
	FILE *pf;
	ARTICULO reg;
	int nArticulo, elecMod; char confirmacion, c;
	pf = fopen(RUTAARTICULOS, "rb+");
	if (pf == NULL) {
		printf("ERROR al abrir el archivo");
		getch();
		return;
	}
	nArticulo = fPedirPosArticulo(pf);
	fseek(pf, (nArticulo - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado != 0) {
		fFormularioCliente();
		GoToXY(19, 2);
		printf("%d", reg.nArticulo);
		GoToXY(19, 3);
		printf("%s", reg.denominacion);
		GoToXY(19, 4);
		printf("%s", reg.precioCoste);
		GoToXY(18, 5);
		printf("%s", reg.pvp);
		elecMod = fMenu("\n\n¿Que dato quieres modificar?\n\t0.-Nada\n\t1.-Denominacion\n\t2.-Precio Coste\n\t3.- P.V.P.\n\t\tEleccion: ",0,3);
		while (elecMod != 0) {
			switch (elecMod) {
			case 1:
				GoToXY(18, 3);
				gets(reg.denominacion);
				break;
			case 2:
				GoToXY(18, 4);
				scanf("%f%c", &reg.precioCoste, &c);
				break;
			case 3:
				GoToXY(18, 5);
				scanf("%f%c", &reg.pvp, &c);
				break;
			}
			GoToXY(0, 5);
			elecMod = fMenu("\n\n¿Que dato quieres modificar?\n\t0.-Nada\n\t1.-Denominacion\n\t2.-Precio Coste\n\t3.- P.V.P.\n\t\tEleccion: ", 0, 3);
		}
		fseek(pf, (nArticulo - 1) * sizeof(reg), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);
		fclose(pf);
	}
	else {
		printf("El articulo seleccionado no existe");
		getch();
	}
	fclose(pf);
}

void fInformeArticulo()
{
	FILE *pf;
	ARTICULO reg;
	int nArticulo;
	char res;
	pf = fopen(RUTAARTICULOS, "rb");
	if (pf == NULL) {
		printf("Error al abrir el archivo.");
		getch();
		return;
	}
	nArticulo = fPedirPosArticulo(pf);
	fseek(pf, (nArticulo - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, 1, sizeof(reg), pf);
	if (reg.estado == 0) {
		printf("El articulo ha sido dado de baja.\n");
	}
	else {
		fFormularioCliente();
		GoToXY(19, 2);
		printf("%d", reg.nArticulo);
		GoToXY(19, 3);
		printf("%s", reg.denominacion);
		GoToXY(19, 4);
		printf("%s", reg.precioCoste);
		GoToXY(19, 5);
		printf("%s", reg.pvp);
		getch();
	}
	fclose(pf);
}

int fPedirPosArticulo(FILE *pf)
{
	int pos;
	char c;
	do {
		printf("Introduce la posicion del Articulo: ");
		scanf("%d%c", &pos, &c);
	} while (pos<1 || pos>fCalcularTamanoFicheroArticulos(pf));
	return pos;
}
