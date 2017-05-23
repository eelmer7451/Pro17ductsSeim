#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define RUTARESUMEN "Resumen.dat"
#define IVA 21

#include <stdio.h>
#include <time.h>

#include "Articulos.h"
#include "Clientes.h"
#include "Pedidos.h"
#include "Menu.h"

typedef struct
{
	int nFactura;
	int nCliente;
	float baseImponible;
	float iva;
}FACTURACION;

void fCabeceraFactura();
void fCabeceraResumen();
void fAgregarFactura();
void fInformeResumen();
int fCalcularTamanoFicheroResumen(FILE * pf);