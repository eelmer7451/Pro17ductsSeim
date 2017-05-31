#include "Clientes.h"

void fFormularioCliente()
{
	system("cls");
	printf("\t\tFICHERO DE CLIENTES\n\n");
	printf("Nº Cliente \t: \n");
	printf("Nombre     \t: \n");
	printf("Domicilio  \t: \n");
	printf("Cod. Postal\t: \n");
	printf("Municipio  \t: \n");
	printf("N.I.F.     \t: \n");
}

void fExisteFicheroClientes()
{
	FILE *pf;
	char c;
	pf = fopen(RUTAFICHEROCLIENTES, "rb");
	if (pf == NULL)
	{
		printf("El archivo de clientes no existe.\n");
		printf("¿Quieres crearlo? ");
		c = tolower(getch());
		if (c == 's')
			pf = fopen(RUTAFICHEROCLIENTES, "wb");
		fclose(pf);
		return;
	}
	printf("El archivo de clientes existe.");
	fclose(pf);
}

int fCalcularTamanoFicheroCliente(FILE *pf) {
	int tamArchivo, tamFinal, tamInicio;
	CLIENTE reg;
	fseek(pf, 0, SEEK_END);
	tamFinal = ftell(pf);
	fseek(pf, 0, SEEK_SET);
	tamInicio = ftell(pf);
	tamArchivo = (tamFinal - tamInicio) / sizeof(reg);
	return tamArchivo;
}

int fCalcularNumeroCliente(FILE *pf)
{
	CLIENTE reg;
	int id = -1, i, tamArchivo;
	tamArchivo = fCalcularTamanoFicheroCliente(pf);
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

void fAltaCliente()
{
	FILE *pf;
	CLIENTE reg;

	pf = fopen(RUTAFICHEROCLIENTES, "rb+");
	if (pf == NULL) {
		printf("ERROR al abrir el archivo");
		getch();
		return;
	}
	reg.nCliente = fCalcularNumeroCliente(pf);
	reg.estado = 1;
	fFormularioCliente();
	GoToXY(18, 2);
	printf("%d", reg.nCliente);
	GoToXY(18, 3);
	gets(reg.nombre);
	GoToXY(18, 4);
	gets(reg.domicilio);
	GoToXY(18, 5);
	gets(reg.codigoPostal);
	GoToXY(18, 6);
	gets(reg.municipio);
	GoToXY(18, 7);
	gets(reg.nif);
	fseek(pf, reg.nCliente * sizeof(reg), SEEK_SET);
	fwrite(&reg, sizeof(reg), 1, pf);
	fclose(pf);
}

void fBajaCliente()
{
	FILE *pf;
	CLIENTE reg;
	int nCliente; char confirmacion;
	pf = fopen(RUTAFICHEROCLIENTES, "rb+");
	if (pf == NULL) {
		printf("ERROR al abrir el archivo");
		getch();
		return;
	}
	nCliente = fPedirPosCliente(pf);
	fseek(pf, (nCliente - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado != 0) {
		system("cls");
		printf("\t\tCLIENTE");
		printf("\tNumero Cliente: %d\tNombre: %s\n", reg.nCliente, reg.nombre);
		printf("¿Estas seguro que quieres borrar el cliente? ");
		confirmacion = tolower(getche());
		if (confirmacion == 's') {
			reg.estado = 0;
			fseek(pf, (nCliente - 1) * sizeof(reg), SEEK_SET);
			fwrite(&reg, sizeof(reg), 1, pf);
			printf("El cliente se ha eliminado correctamente.\n");
			getch();
		}
	}
	else {
		printf("El cliente seleccionado no existe");
		getch();
	}
	fclose(pf);
}

void fModificarCliente()
{
	FILE *pf;
	CLIENTE reg;
	int nCliente, elecMod; char confirmacion;
	pf = fopen(RUTAFICHEROCLIENTES, "rb+");
	if (pf == NULL) {
		printf("ERROR al abrir el archivo");
		getch();
		return;
	}
	nCliente = fPedirPosCliente(pf);
	fseek(pf, (nCliente - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, sizeof(reg), 1, pf);
	if (reg.estado != 0) {//Imprimir en pantalla los datos del cliente
		fFormularioCliente();
		GoToXY(18, 2);
		printf("%d", reg.nCliente);
		GoToXY(18, 3);
		printf("%s", reg.nombre);
		GoToXY(18, 4);
		printf("%s", reg.domicilio);
		GoToXY(18, 5);
		printf("%s", reg.codigoPostal);
		GoToXY(18, 6);
		printf("%s", reg.municipio);
		GoToXY(18, 7);
		printf("%s", reg.nif);
		elecMod = fMenu("\n\n¿Que dato quieres modificar?\n\t0.-Nada\n\t1.-Nombre\n\t2.-Domicilio\n\t3.- Codigo Postal\n\t4.- Municipio\n\t5.-N.I.F.\n\t\tEleccion: ",0,5);//Menu para elegir el dato a cambiar
		while (elecMod != 0) {
			switch (elecMod) {
			case 1:
				GoToXY(18, 3);
				printf("%30s", "");
				GoToXY(18, 3);
				gets(reg.nombre);
				break;
			case 2:
				GoToXY(18, 4);
				printf("%30s", "");
				GoToXY(18, 4);
				gets(reg.domicilio);
				break;
			case 3:
				GoToXY(18, 5);
				printf("%30s", "");
				GoToXY(18, 5);
				gets(reg.codigoPostal);
				break;
			case 4:
				GoToXY(18, 6);
				printf("%30s", "");
				GoToXY(18, 6);
				gets(reg.municipio);
				break;
			case 5:
				GoToXY(18, 7);
				printf("%30s", "");
				GoToXY(18, 7);
				gets(reg.nif);
				break;
			}
			GoToXY(0, 7);
			elecMod = fMenu("\n\n¿Que dato quieres modificar?\n\t0.-Nada\n\t1.-Nombre\n\t2.-Domicilio\n\t3.- Codigo Postal\n\t4.- Municipio\n\t5.-N.I.F.\n\t\tEleccion: ", 0, 5);
		}
		fseek(pf, (nCliente - 1) * sizeof(reg), SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, pf);//Sobreescribir la estructura en el archivo
		fclose(pf);
	}
	else {
		printf("El cliente seleccionado no existe");
		getch();
	}
	fclose(pf);
}

void fInformeCliente()
{
	FILE *pf;
	CLIENTE reg;
	int nCliente;
	char res;
	pf = fopen(RUTAFICHEROCLIENTES, "rb");
	if (pf == NULL) {
		printf("Error al abrir el archivo.");
		getch();
		return;
	}
	nCliente = fPedirPosCliente(pf);
	fseek(pf, (nCliente - 1) * sizeof(reg), SEEK_SET);
	fread(&reg, 1, sizeof(reg), pf);
	if (reg.estado == 0) {
		printf("El cliente ha sido dado de baja.\n");
	}
	else {
		fFormularioCliente();
		GoToXY(18, 2);
		printf("%d", reg.nCliente);
		GoToXY(18, 3);
		printf("%s", reg.nombre);
		GoToXY(18, 4);
		printf("%s", reg.domicilio);
		GoToXY(18, 5);
		printf("%s", reg.codigoPostal);
		GoToXY(18, 6);
		printf("%s", reg.municipio);
		GoToXY(18, 7);
		printf("%s", reg.nif);
		getch();
	}
	fclose(pf);
}

int fPedirPosCliente(FILE *pf)
{
	int pos;
	char c;
	do {
		printf("Introduce la posicion del Cliente: ");
		scanf("%d%c", &pos, &c);
	} while (pos<1 || pos>fCalcularTamanoFicheroCliente(pf));
	return pos;
}