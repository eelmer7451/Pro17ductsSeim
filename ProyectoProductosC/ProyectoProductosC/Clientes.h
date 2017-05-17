#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define RUTAFICHEROCLIENTES "Clientes.dat"

#include <stdio.h>

typedef struct
{
	int nCliente;
	char nombre[20];
	char domicilio[20];
	char codigoPostal[6];
	char municipio[15];
	char nif[10];
	int estado;
}CLIENTE;

void fFormularioCliente();
void fExisteFicheroClientes();
int fCalcularTamanoFicheroCliente(FILE *pf);
int fCalcularNumeroCliente(FILE *pf);
void fAltaCliente();
void fBajaCliente();
void fModificarCliente();
void fInformeCliente();
int fPedirPosCliente(FILE *pf);